#include "stdafx.h"
#include "quickActions.h"
#include "../playerMenu.h"
#include "griefingMenu.h"
#include "../../../vehicle/LSCMenu.h"

using namespace QuickActionsVars;

namespace QuickActionsVars {

	Vars var;

	Hash WeaponHashes[86] = {
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
		0x3813FC08,
	};

	void TeleportToPlayer(SPlayer& player) {
		Vector3 coords = player.m_coordinates;
		if (GetLocalPlayer().m_isInVehicle) ENTITY::SetEntityCoords(GetLocalPlayer().m_vehicle, coords.x, coords.y, coords.z, 0, 0, 0, 1);
		else ENTITY::SetEntityCoords(GetLocalPlayer().m_ped, coords.x, coords.y, coords.z, 0, 0, 0, 1);
	}

	void TeleportInPlayersVehicle(SPlayer& player) {
		if (player.m_isInVehicle) {
			PED::SetPedIntoVehicle(GetLocalPlayer().m_ped, player.m_vehicle, Utils::GetFreeSeat(player.m_vehicle));
		} else GetRenderer()->NotifyBottom(va("%s is not in a vehicle", player.m_name));
	}

	void NonHostKick(SPlayer& player) {
		Natives::ObfuscatedTriggerScriptEvent({ SCRIPTEVENTS::NONHOSTKICK1, player.m_id, 48 }, 3, player.m_id);
		Natives::ObfuscatedTriggerScriptEvent({ SCRIPTEVENTS::NONHOSTKICK2, player.m_id }, 2, player.m_id);
		Natives::ObfuscatedTriggerScriptEvent({ SCRIPTEVENTS::NONHOSTKICK3, player.m_id }, 2, player.m_id);
		Natives::ObfuscatedTriggerScriptEvent({ SCRIPTEVENTS::NONHOSTKICK4, player.m_id }, 2, player.m_id);
		Natives::ObfuscatedTriggerScriptEvent({ SCRIPTEVENTS::NONHOSTKICK5, player.m_id }, 2, player.m_id);
		Natives::ObfuscatedTriggerScriptEvent({ 3353227751, player.m_id, 0 }, 3, player.m_id);
	}

	void KickToSingleplayer(SPlayer& player) {
		if (NETWORK::NetworkGetHostOfScript("freemode", -1, 0) == GetLocalPlayer().m_id) {
			NETWORK::NetworkSessionKickPlayer(player.m_id);
		}
		Natives::ObfuscatedTriggerScriptEvent({ SCRIPTEVENTS::KICKTOSP1, player.m_id, 1 }, 3, player.m_id);
		Natives::ObfuscatedTriggerScriptEvent({ SCRIPTEVENTS::KICKTOSP2, player.m_id }, 2, player.m_id);
		Natives::ObfuscatedTriggerScriptEvent({ SCRIPTEVENTS::KICKTOSP3, player.m_id, 0 }, 3, player.m_id);
		Natives::ObfuscatedTriggerScriptEvent({ SCRIPTEVENTS::NONHOSTKICK3, player.m_id, 0 }, 3, player.m_id);
		Natives::ObfuscatedTriggerScriptEvent({ SCRIPTEVENTS::NONHOSTKICK4, player.m_id, 0 }, 3, player.m_id);
		Natives::ObfuscatedTriggerScriptEvent({ SCRIPTEVENTS::NONHOSTKICK6, player.m_id, 0 }, 3, player.m_id);
		Natives::ObfuscatedTriggerScriptEvent({ 1953937033, player.m_id, 0 }, 3, player.m_id);
		Natives::ObfuscatedTriggerScriptEvent({ 2870072008, player.m_id, 0 }, 3, player.m_id);
	}

	void GiveAllWeapons(SPlayer& player) {
		if (player.m_exists) {
			for (Hash& wep : WeaponHashes) {
				if (WEAPON::IsWeaponValid(wep)) {
					WEAPON::GiveDelayedWeaponToPed(player.m_ped, wep, 1000, 0);
				}
			}
		}
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

	void FixVehicle(SPlayer& player) {
		if (!player.m_isInVehicle) return;
		GetEntityControl()->RequestControl("[FV]", player.m_vehicle, [](Entity vehicle) {VEHICLE::SetVehicleFixed(vehicle); });
	}

	void TuneVehicle(SPlayer& player) {
		if (!player.m_isInVehicle) return;
		GetEntityControl()->RequestControl("[TV]", player.m_vehicle, [](Entity vehicle) {LSCMenuVars::MaxVehicle(vehicle); });
	}

	void LaunchVehicle(SPlayer& player) {
		if (!player.m_isInVehicle) return;
		GetEntityControl()->RequestControl("[LV]", player.m_vehicle, [](Entity vehicle) {Utils::ApplyForceToEntity(vehicle, 0, 0, 20); });
	}

	void Hostkick(SPlayer& player) {
		NETWORK::NetworkSessionKickPlayer(player.m_id);
	}

}

void QuickActionsMenu::Init() {
	setParentSubmenu<PlayerMenu>();
	setName("Quick Actions", true, false);

	addOption(ButtonOption("Teleport to player")
		.addFunction([] { TeleportToPlayer(GetSelectedPlayer()); })
		.addTooltip("Teleport to player").addTranslation());

	addOption(ButtonOption("Teleport in players vehicle")
		.addFunction([] { TeleportInPlayersVehicle(GetSelectedPlayer()); })
		.addTooltip("Teleport in players vehicle").addTranslation());

	addOption(ButtonOption("Non host kick & Kick to singleplayer")
		.addFunction([] { NonHostKick(GetSelectedPlayer()); KickToSingleplayer(GetSelectedPlayer()); })
		.addTooltip("Non host kick").addTranslation());

	addOption(ButtonOption("Host kick")
		.addFunction([] {Hostkick(GetSelectedPlayer()); })
		.addTooltip("Host kick player [Must be session host to use this on a player]").addTranslation());

	addOption(ButtonOption("Give all weapons")
		.addFunction([] { GiveAllWeapons(GetSelectedPlayer()); })
		.addTooltip("Give all weapons").addTranslation());

	addOption(ButtonOption("Kick from vehicle")
		.addFunction([] { BRAIN::ClearPedTasksImmediately(GetSelectedPlayer().m_ped); })
		.addTooltip("Kick the player from their vehicle").addTranslation());

	addOption(ButtonOption("Repair vehicle")
		.addFunction([] { FixVehicle(GetSelectedPlayer()); })
		.addTooltip("Repair vehicle").addTranslation());

	addOption(ButtonOption("Fully tune vehicle")
		.addFunction([] { TuneVehicle(GetSelectedPlayer()); })
		.addTooltip("Fully tune vehicle").addTranslation());

	addOption(ButtonOption("Launch vehicle")
		.addFunction([] {LaunchVehicle(GetSelectedPlayer()); })
		.addTooltip("Launch vehicle").addTranslation());

	addOption(ToggleOption("Standard money drop")
		.addToggle(GetSelectedPlayer().m_standardMoneyDrop)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_standardMoneyDrop); })
		.addTranslation().addTooltip("Standard money drop"));

	addOption(ToggleOption("Disable weapons")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(var.DisableWeapons)
		.addTooltip("Block the user from using weapons at all.")
		.addTranslation());

	addOption(ToggleOption("Freeze in place")
		.addToggle(GetSelectedPlayer().m_disableTasks)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_disableTasks); })
		.addTooltip("Freeze the player in place").addTranslation());

	addOption(ToggleOption("Give never wanted")
		.addToggle(GetSelectedPlayer().m_neverWanted)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_neverWanted); })
		.addTooltip("Give Never wanted").addTranslation());

	addOption(ToggleOption("Give off the radar")
		.addToggle(GetSelectedPlayer().m_otr)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_otr); })
		.addTooltip("Give Off the radar").addTranslation());

	addOption(ButtonOption("Crash player")
		.addFunction([] {CrashPlayer(GetSelectedPlayer()); })
		.addTooltip("Crash player").addTranslation());

}

/*Update once when submenu is opened*/
void QuickActionsMenu::UpdateOnce() {}

/*Update while submenu is active*/
void QuickActionsMenu::Update() {}

/*Background update*/
void QuickActionsMenu::FeatureUpdate() {
	static int TIMER;
	static bool update = true;
	Utils::DoTimedFunction(&TIMER, 50, [] {update = true; });
	if (update) {
		if (var.DisableWeapons) {
			Hash removeMe = 0x0000;
			if (WEAPON::GetCurrentPedWeapon(GetSelectedPlayer().m_ped, &removeMe, true)) {
				WEAPON::RemoveWeaponFromPed(GetSelectedPlayer().m_ped, removeMe);
			}
		}
		update = false;
	}
}

/*Singleton*/
QuickActionsMenu* _instance;
QuickActionsMenu* QuickActionsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new QuickActionsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
QuickActionsMenu::~QuickActionsMenu() { delete _instance; }