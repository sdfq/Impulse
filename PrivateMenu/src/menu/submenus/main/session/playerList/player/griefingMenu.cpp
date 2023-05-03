#include "stdafx.h"
#include "griefingMenu.h"
#include "griefing/attachmentMenu.h"
#include "griefing/soundMenu.h"
#include "griefing/disables/disableActionsMenu.h"
#include "../../../world/trafficManagerMenu.h"
#include "../../../world/pedManagerMenu.h"
#include "../playerMenu.h"
#include "menu\submenus\main\session\allPlayers\sessionGriefing.h"

using namespace GriefingMenuVars;

static TranslationString strNotHost("Sorry, you're not host", true, true);
namespace GriefingMenuVars {
	Vars vars;

	void Karma(SPlayer& player) {
		if (ENTITY::IsEntityDead(player.m_ped, 1)) {
			Ped killer = PED::GetPedSourceOfDeath(player.m_ped);
			if (!ENTITY::IsEntityDead(killer, 1)) {
				Vector3 Pos = ENTITY::GetEntityCoords(killer, 1);
				FIRE::AddExplosion(Pos.x, Pos.y, Pos.z, 0, 10, 1, 0, 0.0f, false);
			}
		}
	}

	void Hostkick(SPlayer& player) {
		NETWORK::NetworkSessionKickPlayer(player.m_id);
	}

	void CrashPlayer2(SPlayer& player) {
		GetEntityControl()->SimpleRequestModel(Utils::GetHashKey("a_c_poodle")); 
		GetEntityControl()->SimpleRequestModel(Utils::GetHashKey("weapon_machete"));

		Ped ped1 = PED::CreatePed(26, Utils::GetHashKey("a_c_poodle"), player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 1, 1, 0);
		Ped ped2 = PED::CreatePed(21, Utils::GetHashKey("a_c_poodle"), player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 1, 1, 0);
		
		WEAPON::GiveWeaponToPed(ped1, Utils::GetHashKey("weapon_machete"), 1, false, true);
		WEAPON::GiveWeaponToPed(ped2, Utils::GetHashKey("weapon_machete"), 1, false, true);

		PED::SetPedCombatAbility(ped1, 100);
		BRAIN::TaskCombatPed(ped1, player.m_ped, 0, 16);
		PED::SetPedKeepTask(ped1, true);

		PED::SetPedCombatAbility(ped2, 100);
		BRAIN::TaskCombatPed(ped2, player.m_ped, 0, 16);
		PED::SetPedKeepTask(ped2, true);

		GetRenderer()->NotifyBottom("Sent");

	}

	void CrashPlayer(SPlayer& player) {

		if (player.m_id != GetLocalPlayer().m_id && player.m_coordinates.Distance(GetLocalPlayer().m_coordinates) >= 500.f) {

			GetFiberPool()->DoJob([=] {

				GriefingMenuVars::vars.disableCrashProtectionThisFrame = true;

				GetEntityControl()->SimpleRequestModel(0x3F039CBA);
				GetEntityControl()->SimpleRequestModel(0xB881AEE);
				GetEntityControl()->SimpleRequestModel(0x856CFB02);
				GetEntityControl()->SimpleRequestModel(0x2D7030F3);

				Ped pedhandle = PED::CreatePed(26, 0x3F039CBA, player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 1, 1, 0);
				Ped pedhandle2 = PED::CreatePed(21, 0xB881AEE, player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 1, 1, 0);
				Ped pedhandle5 = PED::CreatePed(21, 0x856CFB02, player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 1, 1, 0);
				Ped pedhandle6 = PED::CreatePed(21, 0x2D7030F3, player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 1, 1, 0);
				GetRenderer()->NotifyBottom("Sending crash entity - stay away from their location");
				WAIT(2000);
				GetRenderer()->NotifyBottom("Sent crash entities - cleaning up entities");
				if (ENTITY::DoesEntityExist(pedhandle) && ENTITY::DoesEntityExist(pedhandle2) && ENTITY::DoesEntityExist(pedhandle5) && ENTITY::DoesEntityExist(pedhandle6)) {
					GetRenderer()->NotifyBottom("Sent crash entities - cleaning up");
					GetEntityControl()->DeleteEntity(pedhandle);
					GetEntityControl()->DeleteEntity(pedhandle2);
					GetEntityControl()->DeleteEntity(pedhandle5);
					GetEntityControl()->DeleteEntity(pedhandle6);
				}
				GriefingMenuVars::vars.disableCrashProtectionThisFrame = false;
			});
		} else {
			GetRenderer()->NotifyBottom("Increase your distance from the target - use safe space if possible");
		}
	}

	void Explode(SPlayer& player) {
		if (SessionGriefingMenuVars::vars.explode || player.m_explode) {
			static int TIMER[32];
			Utils::DoTimedFunction(&TIMER[player.m_id], 1000, [=] {
				Vector3 coords = player.m_coordinates;
				FIRE::AddExplosion(coords.x, coords.y, coords.z, 18, 0.25f, true, false, 0.5f, false);
			});
		} else {
			Vector3 coords = player.m_coordinates;
			FIRE::AddExplosion(coords.x, coords.y, coords.z, 18, 0.25f, true, false, 0.5f, false);
		}
	}

	void CloneCrash(SPlayer& player) {
		Ped ped = PED::ClonePed(player.m_ped, 1, 1, 0);
		ENTITY::AttachEntityToEntity(ped, player.m_ped, -1.0f, 0.0f, -0.25f, 0.0f, 0.0f, 0.0f, 1, 1, 0, 0, true, 1, 1);
	}

	ScrollStruct<int> lagvehicle[] = {
		TranslationString("Cargoplanes", true), 0x15F27762,
		TranslationString("Blimps", true), 0xF7004C86,
		TranslationString("Jet", true), 0x3F119114,
	};

	void CargoLag(SPlayer& player) {
		//Vehicle cargoplane = SpawnVehicleMenuVars::SpawnVehiclePlayer(Utils::GetHashKey("cargoplane"), player.m_id, true);
		//ENTITY::SetEntityInvincible(cargoplane, true);
		//ENTITY::FreezeEntityPosition(cargoplane, true);
		//ENTITY::SetEntityVisible(cargoplane, false, 0);
		//ENTITY::SetEntityAlpha(cargoplane, 0.0f, 1);
		static int TIMER[32];
		Utils::DoTimedFunction(&TIMER[player.m_id], 100, [=] {
		Vehicle cargoplane = SpawnVehicleMenuVars::SpawnVehiclePlayer(lagvehicle[vars.lagvehicleselect].m_result, player.m_id, true);
			//ENTITY::SetEntityVisible(cargoplane, false, false);
			ENTITY::SetEntityCollision(cargoplane, true, false);
			//ENTITY::FreezeEntityPosition(cargoplane, true);
			//ENTITY::SetEntityAlpha(cargoplane, 0, true);
		});
	}

	void WaterLoop(SPlayer& player) {
		Vector3 coords = player.m_coordinates;
		FIRE::AddExplosion(coords.x, coords.y, coords.z - 1, 13, 0.5f, true, false, 0.0f, true);
	}

	void FireLoop(SPlayer& player) {
		Vector3 coords = player.m_coordinates;
		FIRE::AddExplosion(coords.x, coords.y, coords.z - 1, 12, 0.5f, true, false, 0.0f, false);

	}

	void SetOnFire(SPlayer& player, bool toggle) {
		if (toggle) player.m_onFireHandle = FIRE::StartScriptFire(player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 5, true);
		else {
			FIRE::StopEntityFire(player.m_ped);
			FIRE::StopEntityFire(player.m_vehicle);
			FIRE::RemoveScriptFire(player.m_onFireHandle);
		}
	}

	void RamWithVehicle(SPlayer& player) {
		Vector3 coords = player.m_coordinates;
		FIRE::AddExplosion(coords.x, coords.y, coords.z - 1, 12, 0.5f, true, false, 0.0f, false);
		static Hash hash = Utils::GetHashKey("bus");
		GetEntityControl()->SimpleRequestModel(hash);
		Vehicle vehicle = VEHICLE::CreateVehicle(hash, coords.x, coords.y, coords.z, 1, 1, 0, 1);
		if (ENTITY::DoesEntityExist(vehicle)) {
			ENTITY::SetEntityHeading(vehicle, player.m_heading);
			VEHICLE::SetVehicleOutOfControl(vehicle, 1, 1);
			VEHICLE::SetVehicleForwardSpeed(vehicle, 200.0F);
		}
	}

	void ClonePlayer(SPlayer& player, bool hostile) {
		Ped ped = PED::ClonePed(player.m_ped, 1, 1, 0);
		if (hostile) {
			WEAPON::GiveWeaponToPed(ped, 0x7FD62962, 9999, true, true);
			BRAIN::TaskCombatPed(ped, player.m_ped, 0, 16);
			PED::SetPedKeepTask(ped, true);
		}
	}

	void BlamePlayer(SPlayer& players) {
		OnlinePlayerCallback(false, [=](SPlayer player) { if (player.m_id != GetLocalPlayer().m_id) Natives::AddOwnedExplosion(players.m_ped, player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 1, 10, 1, 0, 1); });
	}

	void Airstrike(SPlayer& player) {
		Vector3 coords = player.m_coordinates;
		MISC::ShootSingleBulletBetweenCoords(coords.x, coords.y, coords.z + 250, coords.x, coords.y, coords.z, 0, 1, 0x63AB0442, GetLocalPlayer().m_ped, false, 0, -1);
	}

	void Electrocute(SPlayer& player) {
		if (!WEAPON::HasWeaponAssetLoaded(Utils::GetHashKey("WEAPON_STUNGUN")))
			WEAPON::RequestWeaponAsset(Utils::GetHashKey("WEAPON_STUNGUN"), 31, 0);
		static int TIMER[32];
		Utils::DoTimedFunction(&TIMER[player.m_id], 500, [=] {
		Vector3 coords = player.m_coordinates;
		Vector3 bone = PED::GetPedBoneCoords(player.m_ped, 0x322c, 0, 0, 0);
		MISC::ShootSingleBulletBetweenCoords(coords.x, coords.y, coords.z, bone.x, bone.y, bone.z, 0, TRUE, Utils::GetHashKey("WEAPON_STUNGUN"), GetLocalPlayer().m_ped, TRUE, FALSE, -1.f);
		});
	}

	void SWATAttack(SPlayer& player) {
		Vector3 coords = player.m_coordinates;
		GetEntityControl()->RequestModel(0xB3F3EE34, [=](int model) {
			Ped ped = PED::CreatePed(21, model, coords.x, coords.y, coords.z, player.m_heading, true, true);
			if (ENTITY::DoesEntityExist(ped)) {
				NETWORK::PedToNet(ped);
				PED::SetPedCombatAbility(ped, 100);
				BRAIN::TaskCombatPed(ped, player.m_ped, 0, 16);
				PED::SetPedCanSwitchWeapon(ped, false);
				PED::SetPedCanRagdoll(ped, 0);
				PED::SetPedCanRagdollFromPlayerImpact(ped, 0);
				PED::SetPedCanBeKnockedOffVehicle(ped, false);
				WEAPON::GiveDelayedWeaponToPed(ped, 0xB1CA77B1, 9999, 1);
			}
		});
	}

	void JetAttack(SPlayer& player) {
		Vector3 coords = player.m_coordinates;
		GetEntityControl()->SimpleRequestModel(Utils::GetHashKey("lazer"));
		Vector3 pos = ENTITY::GetOffsetFromEntityInWorldCoords(player.m_ped, MISC::GetRandomFloatInRange(-50, 50), MISC::GetRandomFloatInRange(-50, 50), MISC::GetRandomFloatInRange(25, 75));
		Vehicle	veh = VEHICLE::CreateVehicle(Utils::GetHashKey("lazer"), pos.x, pos.y, pos.z, player.m_heading, true, false, 1);
		if (veh != 0) {
			Ped Driver = PED::CreateRandomPedAsDriver(veh, false);
			PED::SetPedIntoVehicle(Driver, veh, -1);
			ENTITY::ApplyForceToEntity(veh, true, 0, 0, 50, 0, 0, 0, false, true, true, true, false, true);
			BRAIN::TaskPlaneChase(Driver, veh, 0, 0, 50);
			VEHICLE::ControlLandingGear(veh, 3);
			BRAIN::TaskCombatPed(Driver, player.m_ped, 0, 0x10);
			PED::SetPedKeepTask(Driver, true);

			vars.JetSwarm++;
		}
	}

	void ExplosiveVehicle(SPlayer& player) {
		Vector3 coords = player.m_coordinates;
		GetEntityControl()->SimpleRequestModel(Utils::GetHashKey("adder"));
		Vector3 pos = ENTITY::GetOffsetFromEntityInWorldCoords(player.m_ped, 0.0, -15.0, 0);
		Vehicle	veh = VEHICLE::CreateVehicle(Utils::GetHashKey("adder"), pos.x, pos.y, pos.z, player.m_heading, true, false, 1);
		if (veh != 0) {
			Ped Driver = PED::CreateRandomPedAsDriver(veh, false);
			PED::SetPedIntoVehicle(Driver, veh, -1);
			PED::SetDriverAggressiveness(Driver, 100);
			BRAIN::TaskVehicleFollow(Driver, veh, player.m_ped, 0, 1000.0f, 0);
			PED::SetPedKeepTask(Driver, true);
			VEHICLE::SetVehicleOutOfControl(veh, 0, 1);
			VEHICLE::SetVehicleForwardSpeed(veh, 30);
		}
	}

	void HostileTraffic(SPlayer& player) {
		TrafficManagerMenuVars::vars.usepools = true;
		static int TIMER[32];
		Utils::DoTimedFunction(&TIMER[player.m_id], 2000, [=] {TrafficManagerMenuVars::RunTrafficManagerWorker(VEHICLE_HOSTILETRAFFIC, player.m_id); });
	}

	void HostilePeds(SPlayer& player) {
		PedManagerMenuVars::vars.usepools = true;
		static int TIMER[32];
		Utils::DoTimedFunction(&TIMER[player.m_id], 2000, [=] {PedManagerMenuVars::RunPedManagerWorker(PED_HOSTILEPEDS, player.m_id); });
	}

	void RainRockets(SPlayer& player) {
		static int TIMER[32];
		Utils::DoTimedFunction(&TIMER[player.m_id], 250, [=] {
			GetFiberPool()->DoJob([=] {
				auto playerPos = player.m_coordinates;
				static auto weaponAssetRocket = Utils::GetHashKey("WEAPON_AIRSTRIKE_ROCKET");
				if (!WEAPON::HasWeaponAssetLoaded(weaponAssetRocket)) {
					WEAPON::RequestWeaponAsset(weaponAssetRocket, 31, 0);
					while (!WEAPON::HasWeaponAssetLoaded(weaponAssetRocket))
						GetFiberManager()->GoToMainFiber();
				}
				playerPos.x += MISC::GetRandomFloatInRange(-20, 20);
				playerPos.y += MISC::GetRandomFloatInRange(-20, 20);
				MISC::ShootSingleBulletBetweenCoords(playerPos.x, playerPos.y, playerPos.z + MISC::GetRandomFloatInRange(50, 150), playerPos.x, playerPos.y, playerPos.z + 1, 250, 1, weaponAssetRocket, GetLocalPlayer().m_id, 1, 0, -1.0);
			});
		});
	}

	void ShakeCamera(SPlayer& player) {
		Vector3 coords = player.m_coordinates;
		FIRE::AddExplosion(coords.x, coords.y, coords.z, 0, 0.0f, false, true, 100.f, true);
	}

	void CagePlayer(SPlayer& player) {
		Vector3 coords = player.m_coordinates;
		Hash Cage = 0x7B059043;
		GetEntityControl()->RequestModel(Cage, [=](int model) {
			Object cage1 = OBJECT::CreateObject(Cage, coords.x, coords.y, coords.z - 1, true, true, false);
			Object cage2 = OBJECT::CreateObject(Cage, coords.x, coords.y, coords.z + 1, true, true, false);
			ENTITY::FreezeEntityPosition(cage1, true);
			ENTITY::FreezeEntityPosition(cage2, true);
			ENTITY::SetEntityRotation(cage2, 0, 180, 90, 0, false);
		});
	}

	void TrapPlayer(SPlayer& player) {
		Vector3 coords = player.m_coordinates;
		Hash Cablecar = Utils::GetHashKey("p_cablecar_s");
		GetEntityControl()->RequestModel(Cablecar, [=](int model) {
			Object Trap1 = OBJECT::CreateObject(Cablecar, coords.x, coords.y, coords.z - 1,  true, true, false);
			Object Trap2 = OBJECT::CreateObject(Cablecar, coords.x, coords.y, coords.z - 1, true, true, false);
			ENTITY::FreezeEntityPosition(Trap1, true);
			ENTITY::FreezeEntityPosition(Trap2, true);
			ENTITY::SetEntityRotation(Trap2, 0, 0, 90, 0, false);
		});
	}

	void Forcefield(SPlayer& player) {
		Vector3 coords = player.m_coordinates;
		FIRE::AddExplosion(coords.x, coords.y, coords.z, 29, 100, false, true, 0.0f, false);
	}

	void SendAttackers(SPlayer& player, int count) {
		DWORD model = 0xB3F3EE34;
		GetEntityControl()->SimpleRequestModel(model);
		for (int i = 0; i < count; i++) {
			Ped ped = PED::CreatePed(21, model, player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 1, 1, 1);
			if (ENTITY::DoesEntityExist(ped)) {
				PED::SetPedCombatAbility(ped, 100);
				BRAIN::TaskCombatPed(ped, player.m_ped, 0, 16);
				PED::SetPedCanSwitchWeapon(ped, false);
				PED::SetPedCanRagdoll(ped, false);
				PED::SetPedCanRagdollFromPlayerImpact(ped, false);
				WEAPON::GiveDelayedWeaponToPed(ped, 0x42BF8A85, 9999, 1);
			}
		}
	}

	void FreezeInPlace(SPlayer& player) {
		static int TIMER[32];
		Utils::DoTimedFunction(&TIMER[player.m_id], 100, [=] {
			BRAIN::ClearPedTasksImmediately(player.m_ped);
		});
	}

	void SmokePlayer(SPlayer& player) {
		static int TIMER[32];

		Utils::DoTimedFunction(&TIMER[player.m_id], 1000, [&] {
			STREAMING::RequestNamedPtfxAsset("scr_exile1");
			GRAPHICS::_UseParticleFxAssetNextCall("scr_exile1");

			GRAPHICS::_StartParticleFxNonLoopedAtCoord2("scr_ex1_dust_impact", player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 0, 0, 0, 0.50f, 0, 0, 0);
			GRAPHICS::_StartParticleFxNonLoopedAtCoord2("scr_ex1_dust_impact", player.m_coordinates.x + 1, player.m_coordinates.y + 1, player.m_coordinates.z + 1, 0, 0, 0, 0.50f, 0, 0, 0);
			GRAPHICS::_StartParticleFxNonLoopedAtCoord2("scr_ex1_dust_impact", player.m_coordinates.x - 1, player.m_coordinates.y - 1, player.m_coordinates.z - 1, 0, 0, 0, 0.50f, 0, 0, 0);
		});
	}

	void AlwaysWanted(SPlayer& player) {
		PLAYER::ReportCrime(player.m_id, 8, PLAYER::GetWantedLevelThreshold(5));
	}

	void FakeMoney(SPlayer& player) {
		GetEntityControl()->SimpleRequestModel(0x113FD533);

		static int TIMER[32];

		Utils::DoTimedFunction(&TIMER[player.m_id], 500, [&] {
			OBJECT::CreateAmbientPickup(0x1E9A99F8, player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 0, 0, 0x113FD533, 0, 1);
		});
	}

	void GlitchPed(SPlayer& player) {
		int back = PED::GetPedBoneIndex(player.m_ped, 23553);// SKEL_Spine0
		Hash attachobject = Utils::GetHashKey("prop_acc_guitar_01");

		GetEntityControl()->SimpleRequestModel(attachobject);

		Entity attachobj = OBJECT::CreateObject(attachobject, player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 1, 1, 0);
		if (ENTITY::DoesEntityExist(attachobj)) {
			Vector3 One, Two;
			One.x = 0.5f;// up & down
			One.y = -0.2f;// Forward & Backward
			One.z = 0.f;// Left & Right
			Two.x = 0.f;
			Two.y = 75.0f;
			Two.z = 0.f;
			ENTITY::SetEntityAlpha(attachobj, 0, 0);
			ENTITY::AttachEntityToEntity(attachobj, player.m_ped, back, One.x, One.y, One.z, Two.x, Two.y, Two.z, true, true, false, true, 1, true);
			ENTITY::SetEntityCollision(attachobj, 1, 1);
		}
	}

	void LagParticle(SPlayer& player) {
			STREAMING::RequestNamedPtfxAsset("scr_exile1");
			GRAPHICS::_UseParticleFxAssetNextCall("scr_exile1");
			GRAPHICS::_StartParticleFxLoopedOnEntity2("scr_ex1_dust_impact", player.m_ped, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0);
			GRAPHICS::_StartParticleFxNonLoopedAtCoord2("scr_ex1_dust_impact", player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 0, 0, 0, 10, 0, 0, 0);
	}

}

void GriefingMenu::Init() {
	setParentSubmenu<PlayerMenu>();
	setName("Griefing", true, false);

	addOption(SubmenuOption("Attachments")
		.addSubmenu<AttachmentMenu>()
		.addTooltip("Attach objects to players").addTranslation());

	addOption(SubmenuOption("Disable actions")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addSubmenu<DisableActionsMenu>()
		.addTooltip("Disable certain player actions").addTranslation());

	addOption(SubmenuOption("Sounds")
		.addSubmenu<SoundMenu>()
		.addTooltip("Play sounds on the player").addTranslation());

	addOption(BreakOption("Troll").addTranslation());

	addOption(ButtonOption("Clone")
		.addFunction([] {ClonePlayer(GetSelectedPlayer(), false); })
		.addTooltip("Clone player").addTranslation());

	addOption(ToggleOption("Freeze in place")
		.addToggle(GetSelectedPlayer().m_disableTasks)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_disableTasks); })
		.addTooltip("Freeze the player in place").addTranslation());

	addOption(ButtonOption("Give wanted level")
		.addFunction([] {AlwaysWanted(GetSelectedPlayer()); })
		.addTooltip("Add wanted level").addTranslation());

	addOption(ToggleOption("Always wanted")
		.addToggle(GetSelectedPlayer().m_alwaysWanted)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_alwaysWanted); })
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addTooltip("Make the player always wanted").addTranslation());

	addOption(ToggleOption("Electrocute player")
		.addToggle(GetSelectedPlayer().m_electrocute)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_electrocute); })
		.addTooltip("This will electrocute the selected player").addTranslation());

	addOption(ScrollOption<int>(TOGGLE, "Lag area")
		.addToggle(vars.laggingPlayer)
		.addScroll(vars.lagvehicleselect, 0, NUMOF(lagvehicle) - 1, lagvehicle)
		.addTooltip("Spam entities on player").addTranslation());

	addOption(ToggleOption("Lag player")
		.addToggle(vars.laggingPlayer2)
		.addTooltip("Spam effects on player").addTranslation());

	addOption(ToggleOption("Make traffic hostile")
		.addToggle(GetSelectedPlayer().m_hostileTraffic)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_hostileTraffic); })
		.addTooltip("Make traffic hostile").addTranslation());

	addOption(ToggleOption("Make pedestrians hostile")
		.addToggle(GetSelectedPlayer().m_hostilePeds)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_hostilePeds); })
		.addTooltip("Make pedestrians hostile").addTranslation());

	addOption(ToggleOption("Fake money")
		.addToggle(GetSelectedPlayer().m_fakeMoney)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_fakeMoney); })
		.addTooltip("Drop money bags with no value").addTranslation());

	addOption(BreakOption("Affect Ped Vision and Movement").addTranslation());

	addOption(ButtonOption("Trap in cage")
		.addFunction([] {CagePlayer(GetSelectedPlayer()); })
		.addTooltip("Trap in cage").addTranslation());

	addOption(ButtonOption("Trap in cable cars")
		.addFunction([] {TrapPlayer(GetSelectedPlayer()); })
		.addTooltip("Trap in cable cars").addTranslation());

	addOption(ButtonOption("Glitch ped")
		.addFunction([] { GlitchPed(GetSelectedPlayer()); })
		.addTooltip("Glitch the players ped").addTranslation());

	addOption(ToggleOption("Shake camera")
		.addToggle(GetSelectedPlayer().m_cameraShake)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_cameraShake); })
		.addTooltip("Shake the player's camera").addTranslation());

	addOption(ToggleOption("Smoke player")
		.addToggle(GetSelectedPlayer().m_smokePlayer)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_smokePlayer); })
		.addTooltip("Spawn loads of smoke on the player").addTranslation());

	addOption(ToggleOption("Spray with water")
		.addToggle(GetSelectedPlayer().m_waterLoop)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_waterLoop); })
		.addTooltip("Spray with water").addTranslation());

	addOption(ToggleOption("Spray with fire")
		.addToggle(GetSelectedPlayer().m_fireLoop)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_fireLoop); })
		.addTooltip("Spray with fire").addTranslation());

	addOption(BreakOption("Deadly Force").addTranslation());

	addOption(ButtonOption("Host kick")
		.addFunction([] {Hostkick(GetSelectedPlayer()); })
		.addTooltip("Host kick player [Must be session host to use this on a player]").addTranslation());

	addOption(ButtonOption("Crash player")
		.addFunction([] {CrashPlayer(GetSelectedPlayer()); })
		.addTooltip("Crash player (be far away from player)").addTranslation());

	addOption(ButtonOption("Crash player 2")
		.addFunction([] {CrashPlayer2(GetSelectedPlayer()); })
		.addTooltip("Crash player (be far away from player)").addTranslation());

	addOption(ButtonOption("Kill")
		.addFunction([] {
		Vector3 coords = GetSelectedPlayer().m_coordinates;
		FIRE::AddExplosion(coords.x, coords.y, coords.z, 29, 100, false, true, 0.0f, false);
		FIRE::AddExplosion(coords.x, coords.y, coords.z - 1, 12, 0.5f, true, false, 0.0f, false);
		FIRE::AddExplosion(coords.x, coords.y, coords.z, 18, 0.25, false, true, 0, false);
	})
		.addTooltip("Kill the player").addTranslation());

	addOption(ButtonOption("Blame kill everyone")
		.addFunction([] {BlamePlayer(GetSelectedPlayer()); })
		.addTooltip("Blame player for killing everyone").addTranslation());

	addOption(ButtonOption("Silent kill")
		.addFunction([] {
		Vector3 coords = GetSelectedPlayer().m_coordinates;
		Natives::AddOwnedExplosion(GetSelectedPlayer().m_ped, coords.x, coords.y, coords.z, 38, 0.1f, false, false, 0.0f);
	}).addTooltip("Peacefully kill the player").addTranslation());

	addOption(ToggleOption("Clone spam")
		.addToggle(vars.cloneCrashing)
		.addTooltip("Clone spam player (be far away from player)").addTranslation());

	addOption(ToggleOption("Set on fire")
		.addToggle(GetSelectedPlayer().m_onFire)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_onFire); })
		.addFunction([] {if (!GetSelectedPlayer().m_onFire) SetOnFire(GetSelectedPlayer(), false); })
		.addTooltip("Spray with fire").addTranslation());

	addOption(ButtonOption("Ram with vehicle")
		.addFunction([] {RamWithVehicle(GetSelectedPlayer()); })
		.addTooltip("Ram player with vehicle").addTranslation());

	addOption(ButtonOption("Explode")
		.addFunction([] {Explode(GetSelectedPlayer()); })
		.addTooltip("Explode player").addTranslation());

	addOption(ToggleOption("Explode loop")
		.addToggle(GetSelectedPlayer().m_explode)
		.addOnUpdate([](ToggleOption* option) {static int TEMP; Utils::DoTimedFunction(&TEMP, 250, [&] { option->addToggle(GetSelectedPlayer().m_explode); }); })
		.addTooltip("Explode player").addTranslation());

	addOption(ToggleOption("Rain rockets")
		.addToggle(GetSelectedPlayer().m_rainRockets)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_rainRockets); })
		.addTooltip("Rain rockets").addTranslation());

	addOption(ToggleOption("Forcefield")
		.addToggle(GetSelectedPlayer().m_forcefield)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_forcefield); })
		.addTooltip("Forcefield").addTranslation());

	addOption(BreakOption("Attackers").addTranslation());

	addOption(NumberOption<int>(SCROLLSELECT, "Send attackers")
		.addNumber(vars.attackerCount, "%d", 1).addMin(1).addMax(20)
		.addFunction([] { SendAttackers(GetSelectedPlayer(), vars.attackerCount); })
		.addTooltip("Send a custom amount of attackers to the player").addTranslation());

	addOption(ButtonOption("Hostile clone")
		.addFunction([] {ClonePlayer(GetSelectedPlayer(), true); })
		.addTooltip("Hostile clone").addTranslation());

	addOption(ButtonOption("Attack with SWAT")
		.addFunction([] {SWATAttack(GetSelectedPlayer()); })
		.addTooltip("Attack with SWAT").addTranslation());

	addOption(ButtonOption("Attack with jet")
		.addFunction([] {JetAttack(GetSelectedPlayer()); })
		.addTooltip("Attack with jet").addTranslation());

	addOption(ButtonOption("Attack with vehicle")
		.addFunction([] {ExplosiveVehicle(GetSelectedPlayer()); })
		.addTooltip("Attack with explosive vehicle").addTranslation());

	addOption(BreakOption("Misc").addTranslation());

	/*addOption(ButtonOption("Kick from vehicle")
		.addFunction([] { BRAIN::ClearPedTasksImmediately(GetSelectedPlayer().m_ped); })
		.addTooltip("Kick the player from their vehicle").addTranslation());*/

	addOption(ButtonOption("Airstrike")
		.addFunction([] {Airstrike(GetSelectedPlayer()); })
		.addTooltip("Airstrike attack player").addTranslation());

	addOption(ButtonOption("Ragdoll player")
		.addFunction([] {
		Vector3 coords = GetSelectedPlayer().m_coordinates;
		FIRE::AddExplosion(coords.x, coords.y, coords.z - 0.2f, 4, 10.f, FALSE, TRUE, 0.f, false);
		})
		.addTooltip("Ragdoll the player").addTranslation());

	addOption(ButtonOption("Attach campfire")
		.addFunction([] {
		Vector3 coords = GetSelectedPlayer().m_coordinates;
		Hash beachfire = Utils::GetHashKey("prop_beach_fire");
		GetEntityControl()->SimpleRequestModel(beachfire);
		int beachfirecre = OBJECT::CreateObject(beachfire, 0, 0, 0, true, 1, 0);
		ENTITY::AttachEntityToEntity(beachfirecre, GetSelectedPlayer().m_ped, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 2, 1);
	}).addTooltip("Attaches a campfire to player that will slowly kill").addTranslation());

	addOption(ToggleOption("Karma")
		.addToggle(GetSelectedPlayer().m_karma)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_karma); })
		.addTooltip("Kill players when they kill you").addTranslation());

}

/*Update once when submenu is opened*/
void GriefingMenu::UpdateOnce() {}

/*Update while submenu is active*/
void GriefingMenu::Update() {}

/*Background update*/
void GriefingMenu::FeatureUpdate() {
	static int TIMER;
	static bool update = true;
	Utils::DoTimedFunction(&TIMER, 50, [] {update = true; });
	if (update) {
		if (vars.cloneCrashing) CloneCrash(GetSelectedPlayer());
		if (vars.laggingPlayer) CargoLag(GetSelectedPlayer());
		if (vars.laggingPlayer2) LagParticle(GetSelectedPlayer());
		update = false;
	}
	OnlinePlayerCallback(false, [](SPlayer player) { if (player.m_karma) Karma(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (player.m_explode) Explode(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (player.m_waterLoop) WaterLoop(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (player.m_fireLoop) FireLoop(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (player.m_onFire) SetOnFire(player, true); });
	OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_hostileTraffic) HostileTraffic(player); });
	OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_hostilePeds) HostilePeds(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (player.m_rainRockets) RainRockets(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (player.m_cameraShake) ShakeCamera(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (player.m_forcefield) Forcefield(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (player.m_disableTasks) FreezeInPlace(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (player.m_smokePlayer) SmokePlayer(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (player.m_alwaysWanted) AlwaysWanted(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (player.m_fakeMoney) FakeMoney(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (player.m_electrocute) Electrocute(player); });
}

/*Singleton*/
GriefingMenu* _instance;
GriefingMenu* GriefingMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new GriefingMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
GriefingMenu::~GriefingMenu() { delete _instance; }