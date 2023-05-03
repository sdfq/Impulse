#include "stdafx.h"
#include "miscProtectionMenu.h"
#include "../protectionMenu.h"
#include "menu\submenus\main\world\pedManagerMenu.h"
#include "menu\submenus\main\world\trafficManagerMenu.h"
#include "menu\submenus\main\session\playerList\player\griefingMenu.h"
#include "menu\submenus\main\local\modelMenu.h"

using namespace MiscProtectionMenuVars;

namespace MiscProtectionMenuVars {
	Vars vars;

	Hash usableWeaponHashes[85] = {
		126349499,
		2694266206,
		1233104067,
		101631238,
		911657153,
		1834241177,
		0x1B06D571,
		0x5EF9FEC4,
		0x22D8FE39,
		0x99AEEB3B,
		0x2BE6766B,
		0x13532244,
		0xBFEFFF6D,
		0x83BF0278,
		0xAF113F99,
		0x9D07F764,
		0x7FD62962,
		0x1D073A89,
		0x7846A318,
		0xE284C527,
		0xC472FE2,
		0x5FC3C11,
		0xA284510B,
		0xB1CA77B1,
		0x42BF8A85,
		0x93E220BD,
		0xFDBC8A50,
		0x2C3731D9,
		0x24B17070,
		0x34A67B97,
		0xFBAB5776,
		0x99B507EA,
		0x678B81B1,
		0x4E875F73,
		0x958A4A8F,
		0x84BD7BFD,
		0x440E4788,
		0xEFE7E2DF,
		0x9D61E50F,
		0xF9E6AA4B,
		0xC0A3098D,
		0xBFD21232,
		0x476BF155,
		0xAF3696A1,
		0xB62D1F67,
		0xD205520E,
		0x7F229F94,
		0x61012683,
		0x83839C4,
		0x92A27487,
		0xA89CB99E,
		0x7F7497E5,
		0x47757124,
		0x3AABBBAA,
		0xC734385A,
		0xAB564B93,
		0x63AB0442,
		0xF9DCBF2D,
		0xA3D4D34,
		0xD8DF3C3C,
		0xDC4DB296,
		0xDD5DF8D9,
		0xDB1AA450,
		0xEF951FBB,
		0x624FE830,
		0x8BB05FD7,
		0xC1B3C3D1,
		0xDFE37640,
		0x78A97CD0,
		0xA914799,
		0x394F415C,
		0x19044EE0,
		0x781FE4A,
		0x12E82D3D,
		0x176898A6,
		0x787F0BB,
		0xE232C28C,
		0xD04C944D,
		0x0A3D4D34,
		0x6D544C99,
		0x2C082D7D,
		0xCD274149,
		0xBD248B55,
		0xBA45E8B8,
		0x94117305,
	};

	ScrollStruct<int> AimProtections[] = {
		TranslationString("Kill", true), 0,
		TranslationString("Blast", true), 1,
		TranslationString("Block", true), 2,
		TranslationString("Set on fire", true), 3,
		TranslationString("Cage", true), 4,
		TranslationString("Teleport away", true), 5,
		TranslationString("Electrocute", true), 6
	};

	Cam SafespaceCamera;
	void SafespaceCam() {
		if (CAM::DoesCamExist(SafespaceCamera)) CAM::SetCamActive(SafespaceCamera, 1);
		else {
			//ENTITY::SetEntityCoords(GetLocalPlayer().m_ped, -730.075f, 1447.014f, 2.657f, 1, 0, 0, 1);
			BRAIN::ClearPedTasksImmediately(GetLocalPlayer().m_ped);
			SafespaceCamera = CAM::CreateCam("DEFAULT_SCRIPTED_CAMERA", 1);
			CAM::AttachCamToEntity(SafespaceCamera, GetLocalPlayer().m_ped, 0.0f, 0.0f, 9999.9f, 1);
			CAM::PointCamAtCoord(SafespaceCamera, GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, -100000000);
			CAM::SetCamActive(SafespaceCamera, 1);
		}
		BRAIN::ClearPedTasksImmediately(GetLocalPlayer().m_ped);
		CAM::RenderScriptCams(1, 0, 3000, 1, 0, 0);
	}

	void SetModelI(Hash model) {
		if (STREAMING::IsModelInCdimage(model)) {
			if (STREAMING::IsModelValid(model)) {
				GetEntityControl()->RequestModel(model, [](int model) {
					PLAYER::SetPlayerModel(GetLocalPlayer().m_id, model);
				});
			}
		}
	}

	void SetModel(const char* model) {
		SetModelI(Utils::GetHashKey(model));
	}

}

void MiscProtectionMenu::Init() {
	setParentSubmenu<ProtectionMenu>();
	setName("Misc protections", true, true);

	addOption(ToggleOption("Block all transactions")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(NetEvent::vars.blockalltransactions)
		.addTooltip("Block any and all transactions")
		.addTranslation().addHotkey());

	addOption(ToggleOption("Safe space")
		.addToggle(vars.safesplace)
		.addFunction([] {
		if (!vars.safesplace) {
			GetFiberPool()->DoJob([=] {
				WAIT(1000);
				PED::SetPedRandomComponentVariation(GetLocalPlayer().m_ped, true);
				PED::SetPedRandomProps(GetLocalPlayer().m_ped);
				int Ammo = -1;
				for (int i = 0; i < 82; i++) {
					WEAPON::GetMaxAmmo(GetLocalPlayer().m_ped, usableWeaponHashes[i], &Ammo);
					WEAPON::GiveWeaponToPed(GetLocalPlayer().m_ped, usableWeaponHashes[i], Ammo, false, true);
				}
			});
			if (PED::IsPedMale(GetLocalPlayer().m_ped)) {
				GetEntityControl()->SimpleRequestModel(MISC::GetHashKey("mp_m_freemode_01"));
				SetModel("mp_m_freemode_01");
				ENTITY::SetEntityCoords(GetLocalPlayer().m_ped, 62.50f, 7184.54f, 2.51f, 1, 0, 0, 1);
				CAM::SetCamActive(SafespaceCamera, 0);
				CAM::DestroyCam(SafespaceCamera, 0);
				GRAPHICS::_StopScreenEffect("DeathFailOut");
				CAM::RenderScriptCams(0, 0, 3000, 1, 0, 0);
			} else {
				GetEntityControl()->SimpleRequestModel(MISC::GetHashKey("mp_f_freemode_01"));
				SetModel("mp_f_freemode_01");
				ENTITY::SetEntityCoords(GetLocalPlayer().m_ped, 62.50f, 7184.54f, 2.51f, 1, 0, 0, 1);
				CAM::SetCamActive(SafespaceCamera, 0);
				CAM::DestroyCam(SafespaceCamera, 0);
				GRAPHICS::_StopScreenEffect("DeathFailOut");
				CAM::RenderScriptCams(0, 0, 3000, 1, 0, 0);
			}
		}
	})
		.addTooltip("Teleport to a safe place, if invisible when turned off change outfit")
		.addTranslation().addHotkey());

	addOption(ToggleOption("Clone")
		.addToggle(vars.clone)
		.addTooltip("Stop modders spawning clones of your player")
		.addTranslation().canBeSaved().addHotkey());

	addOption(ToggleOption("Vehicle network mitigate")
		.addToggle(vars.vehicleNetworkMitigate)
		.addTooltip("Stop modders doing small tasks to your vehicle")
		.addTranslation().canBeSaved().addHotkey());

	/*addOption(ToggleOption("Spoof IP")
	.addRequirement([] { return GetAuth()->IsVIP(); })
	.addToggle(vars.spoofIpt)
	.addFunction([] {
	if (!vars.spoofIpt) {
	for (int i = 0; i < Backend::GetMemoryNameAddresses().size(); i++) {
	*(DWORD*)(Backend::GetMemoryNameAddresses()[i] - 0x38) = vars.originalIp;
	}
	}
	}).addTranslation().canBeSaved().addHotkey()
	.addTooltip("Stop modders sniffing your ip address. Must change session after enabling"));*/

	addOption(ToggleOption("Blame")
	.addToggle(vars.blame)
	.addTooltip("Stop modders blaming you for killing other players")
	.addTranslation().canBeSaved().addHotkey());

	addOption(ScrollOption<int>(TOGGLE, "Aiming protection")
	.addToggle(vars.aimToggle)
	.addScroll(vars.aim, 0, NUMOF(AimProtections) - 1, AimProtections)
	.addTooltip("Punish players who aim at you")
	.addTranslation().canBeSaved().addHotkey());

}

/*Update once when submenu is opened*/
void MiscProtectionMenu::UpdateOnce() {}

/*Update while submenu is active*/
void MiscProtectionMenu::Update() {}

/*Background update*/
void MiscProtectionMenu::FeatureUpdate() {

	if (vars.safesplace) {
		SafespaceCam();
		GRAPHICS::_StartScreenEffect("DeathFailOut", 0, 0);
	}

	if (vars.aimToggle) {
		static int timer;
		Utils::DoTimedFunction(&timer, 250, [] {
			OnlinePlayerCallback(false, [](SPlayer player) {
				if (PLAYER::IsPlayerTargettingEntity(player.m_id, GetLocalPlayer().m_ped) && player.m_id != GetLocalPlayer().m_id) {
					Vector3 theirInfront = ENTITY::GetOffsetFromEntityGivenWorldCoords(player.m_ped, 0, 2, 0);

					switch (vars.aim) {
					case 1:
						FIRE::AddExplosion(player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 18, 0.25f, true, true, 0.f, false);
						break;
					case 2:
						FIRE::AddExplosion(player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 4, 10.f, true, true, 0.f, false);
						break;
					case 3:
						GetEntityControl()->SimpleRequestModel(0x5411322E);
						OBJECT::CreateObject(0x5411322E, theirInfront.x, theirInfront.y, theirInfront.z, 1, 1, 0);
						break;
					case 4:
						FIRE::StartScriptFire(player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 5, true);
						break;
					case 5:
						GriefingMenuVars::CagePlayer(player);
						break;
					case 6:
						Natives::TriggerScriptEvent({ SCRIPTEVENTS::ECLIPSETELEPORT, player.m_id, 0, 0, 95, 95 }, 6, player.m_id);
						
						break;
					case 7:
						if (!WEAPON::HasWeaponAssetLoaded(Utils::GetHashKey("WEAPON_STUNGUN"))) WEAPON::RequestWeaponAsset(Utils::GetHashKey("WEAPON_STUNGUN"), 31, 0);
						Vector3 coords = player.m_coordinates;
						Vector3 bone = PED::GetPedBoneCoords(player.m_ped, 0x322c, 0, 0, 0);
						MISC::ShootSingleBulletBetweenCoords(coords.x, coords.y, coords.z, bone.x, bone.y, bone.z, 0, TRUE, Utils::GetHashKey("WEAPON_STUNGUN"), GetLocalPlayer().m_ped, TRUE, FALSE, -1.f);
						break;
					}
				}
			});
		});
	}

	if (vars.blame) {
		if (NETWORK::NetworkIsSessionActive()) {
			//OnlinePlayerCallback(false, [](SPlayer player) {
			//PED::SetCanAttackFriendly(GetLocalPlayer().m_ped, true, true);
			//PED::SetCanAttackFriendly(GetLocalPlayer().m_id, true, true);
			//PED::SetCanAttackFriendly(player.m_ped, true, true);
			//PED::SetCanAttackFriendly(player.m_id, true, true);
			//NETWORK::NetworkSetFriendlyFireOption(true);
			//});
		}
	}

	if (vars.clone) {
		if (NETWORK::NetworkIsSessionActive()) {
			if (!CUTSCENE::IsCutsceneActive() && !CUTSCENE::IsCutscenePlaying() && !STREAMING::IsNetworkLoadingScene() && !NETWORK::NetworkIsInMpCutscene() && !INTERIOR::IsInteriorScene()) {
				PedManagerMenuVars::RunPedManagerWorker(PED_CLONECREATIONPREVENTION);
			}
		}
	}

	if (vars.vehicleNetworkMitigate) {
		if (NETWORK::NetworkIsSessionActive()) {
			if (GetLocalPlayer().m_isInVehicle && VEHICLE::GetPedInVehicleSeat(GetLocalPlayer().m_vehicle, -1, 0) == GetLocalPlayer().m_ped) {
				NETWORK::SetNetworkIdCanMigrate(NETWORK::NetworkGetNetworkIdFromEntity(GetLocalPlayer().m_vehicle), false);
			}
		}
	}

}

/*Singleton*/
MiscProtectionMenu* _instance;
MiscProtectionMenu* MiscProtectionMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new MiscProtectionMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
MiscProtectionMenu::~MiscProtectionMenu() { delete _instance; }