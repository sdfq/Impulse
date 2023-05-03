#include "stdafx.h"
#include "developerMenu.h"
#include "../mainMenu.h"
#include "vehicleMenu.h"
#include "vehicle/LSCMenu.h"
#include "spawn/spawnVehicleMenu.h"

using namespace DeveloperMenuVars;

namespace DeveloperMenuVars {
	Vars vars;
	void setVehicleColor(Vehicle veh, Color primary, Color secondary, float fade) {
		VEHICLE::SetVehicleCustomPrimaryColour(veh, primary.m_r, primary.m_g, primary.m_b);
		VEHICLE::SetVehicleCustomSecondaryColour(veh, secondary.m_r, secondary.m_g, secondary.m_b);
		VEHICLE::SetVehicleEnveffScale(veh, fade);
	}
	Vehicle SpawnNewVehicle(char* toSpawn) {
		DWORD model = Utils::GetHashKey(toSpawn);
		Vehicle vehicle;
		float playerHeading = ENTITY::GetEntityHeading(GetLocalPlayer().m_ped);
		if (STREAMING::IsModelInCdimage(model) && STREAMING::IsModelAVehicle(model)) {
			GetEntityControl()->SimpleRequestModel(model);
			vehicle = VEHICLE::CreateVehicle(model, GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, GetLocalPlayer().m_coordinates.z, playerHeading, TRUE, TRUE, TRUE);
			DECORATOR::DecorSetInt(vehicle, "MPBitset", 0);
			LSCMenuVars::MaxVehicle(vehicle);
			VehicleMenuVars::VehicleGodmode(vehicle, true);
			for (size_t i = 0; i < 4; i++) {
				if (VEHICLE::DoesExtraExist(vehicle, i))VEHICLE::SetVehicleExtra(vehicle, i, 1);
			}
			VEHICLE::SetVehicleDirtLevel(vehicle, 0);
			AUDIO::SetVehRadioStation(vehicle, "OFF");
		}
		return vehicle;
	}

	void Spawn1x13() {
		Vehicle veh = SpawnVehicleMenuVars::SpawnVehicle("HYDRA", 1, 1, 0, 1, 0, { 0,0,0,255 }, { 0,0,0,255 }, 1, 0);
		VEHICLE::SetVehicleEnveffScale(veh, 0);

		Vehicle toAttach = SpawnNewVehicle("Jetmax");
		setVehicleColor(toAttach, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0);
		VEHICLE::SetVehicleModColor1(toAttach, 3, 12, 0);
		VEHICLE::SetVehicleModColor2(toAttach, 3, 12);
		VEHICLE::SetVehicleLights(toAttach, 2);
		VEHICLE::SetVehicleModKit(toAttach, 0);
		VEHICLE::ToggleVehicleMod(toAttach, MOD_XENONLIGHTS, 1);
		ENTITY::AttachEntityToEntity(toAttach, veh, 0, 0.0, 2.7f, 0.58f, 0.0, 180, 0, false, true, false, false, 2, true);

		toAttach = SpawnNewVehicle("Jetmax");
		setVehicleColor(toAttach, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0);
		VEHICLE::SetVehicleModColor1(toAttach, 3, 12, 0);
		VEHICLE::SetVehicleModColor2(toAttach, 3, 12);
		VEHICLE::SetVehicleLights(toAttach, 2);
		VEHICLE::SetVehicleModKit(toAttach, 0);
		VEHICLE::ToggleVehicleMod(toAttach, MOD_XENONLIGHTS, 1);
		ENTITY::AttachEntityToEntity(toAttach, veh, 0, 0.0, 2.7f, -0.37f, -3.43f, 0, 0, false, true, false, false, 2, true);

		toAttach = SpawnNewVehicle("Jetmax");
		setVehicleColor(toAttach, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0);
		VEHICLE::SetVehicleModColor1(toAttach, 3, 12, 0);
		VEHICLE::SetVehicleModColor2(toAttach, 3, 12);
		ENTITY::AttachEntityToEntity(toAttach, veh, 0, 0.0, -2.9f, 0.53f, 3.29f, 180, 0, false, true, false, false, 2, true);

		toAttach = SpawnNewVehicle("Squalo");
		setVehicleColor(toAttach, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0);
		VEHICLE::SetVehicleModColor1(toAttach, 3, 12, 0);
		VEHICLE::SetVehicleModColor2(toAttach, 3, 12);
		ENTITY::AttachEntityToEntity(toAttach, veh, 0, 0.0, -3.54f, 0.79f, 3.68f, 180, 0, false, true, false, false, 2, true);
	}

	void StandardMoneyDrop(SPlayer& player) {
		static int TIMER[32];

		GetEntityControl()->SimpleRequestModel(-1666779307);

		Utils::DoTimedFunction(&TIMER[player.m_id], 750, [&] {
			OBJECT::CreateAmbientPickup(0xE175C698, player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 0, 2000, -1666779307, false, true);
		});
	}

	//void test(int iParam0, char* sParam1, int iParam2, int iParam3, int iParam4, int iParam5, int iParam6, int iParam7, int iParam8, int iParam9, int iParam10, int iParam11, int iParam12, int iParam13, int iParam14, int iParam15, int iParam16) {
	//	Global(1364578).At(1).As<int>() = 1;
	//	Global(1364578).At(4388).As<int>() = iParam0;
	//
	//	strcpy(&Global(1364578).At(4388).At(11).As<char>(), sParam1);
	//	Global(1364578).At(4388).At(172).As<int>() = iParam2;
	//	Global(1364578).At(4388).At(216).As<int>() = iParam3;
	//	Global(1364578).At(4388).At(183).As<int>() = iParam4;
	//	Global(1364578).At(4388).At(194).As<int>() = iParam5;
	//	Global(1364578).At(4388).At(249).As<int>() = iParam6;
	//	Global(1364578).At(4388).At(260).As<int>() = iParam7;
	//	Global(1364578).At(4388).At(205).As<int>() = iParam8;
	//	Global(1364578).At(4388).At(314).As<int>() = iParam9;
	//	Global(1364578).At(4388).At(325).As<int>() = iParam10;
	//	Global(1364578).At(4388).At(357).As<int>() = iParam11;
	//	Global(1364578).At(4388).At(238).As<int>() = iParam12;
	//	Global(1364578).At(4388).At(271).As<int>() = iParam13;
	//	Global(1364578).At(4388).At(368).As<int>() = iParam14;
	//	Global(1364578).At(4388).At(379).As<int>() = iParam15;
	//	Global(1364578).At(4388).At(390).As<int>() = iParam16;
	//}

	/*void WhoKilledMe() {
		char buff[0x100];
		int myPlayer = PLAYER::GetPlayerPed(PLAYER::PlayerId()), myHealth = ENTITY::GetEntityHealth(myPlayer), xTimes;
		for (int i = 0; i < 18; i++) {
			if (ENTITY::HasEntityBeenDamagedByEntity(myPlayer, PLAYER::GetPlayerPed(i), true)) {
				if (myHealth <= 0) {
					xTimes++;
					snprintf(buff, 0x100, "%s Killed You\nYou were killed %i times!", PLAYER::GetPlayerName(i), xTimes);
					LOG_PRINT(buff, 3000);
				}
			}
		}
	}*/

}

void DeveloperMenu::Init() {
	setParentSubmenu<MainMenu>();

#ifdef HARD_DEV
	setName("Developer", false, false);

	// 0x87EB7A3FFCB314DB
	addOption(ButtonOption("Get nigger address")
		.addFunction([] {
		LOG_PRINT("nigger: 0x%llx", (uint64_t)Natives::getNativeHandlerCache(0x426141162EBE5CDB) - (uint64_t)GetModuleHandleA(0));
	}));

	addOption(ButtonOption("Open developer log window")
		.addFunction([] { GetWindowManager()->m_frame.addWindow(&GetWindowManager()->m_devLog); })
		.addTooltip("Open developer log window"));

	addOption(ButtonOption("Print my CWorld")
		.addFunction([] { LOG_PRINT("CWorld: 0x%llx", ReClass::GetWorld()); })
		.addTooltip("Prints my cped struct address"));

	addOption(ButtonOption("Print my CPed")
		.addFunction([] { LOG_PRINT("CPed: 0x%llx", ReClass::GetWorld()->LocalPed); })
		.addTooltip("Prints my cped struct address"));

	addOption(ButtonOption("Print my CPlayerInfo")
		.addFunction([] { LOG_PRINT("CPlayerInfo: 0x%llx", ReClass::GetWorld()->LocalPed->PlayerInfo); })
		.addTooltip("Prints my cplayerinfo struct address"));

	addOption(ToggleOption("Standard money drop")
		.addToggle(GetSelectedPlayer().m_standardMoneyDrop)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_standardMoneyDrop); })
		.addTranslation().addTooltip("Standard money drop"));

	addOption(BreakOption("Misc"));
	addOption(ButtonOption("1-x13 v1")
		.addFunction([] {GetFiberPool()->DoJob([] {Spawn1x13(); }); })
		.addHotkey()
		.addTooltip("Spawn the 1-x13 custom plane"));

	addOption(ButtonOption("Print missing canBeSaved")
		.addFunction([] {
		for (auto& s : GetSubmenuHandler()->GetSubmenus()) {
			LOG_PRINT("%s", s->getName().GetOriginal());
			for (shared_ptr<Option> a : s->getOptions()) {
				if (!a->m_canBeSaved && !a->isBreak()) {
					LOG_PRINT("\t%s", a->getName().GetOriginal());
				}
			}
		}
	})
		.addTooltip("Test"));

	addOption(ButtonOption("Print missing hotkeys")
		.addFunction([] {
		for (auto& s : GetSubmenuHandler()->GetSubmenus()) {
			LOG_PRINT("%s", s->getName().GetOriginal());
			for (shared_ptr<Option> a : s->getOptions()) {
				if (!a->m_hasHotkey && !a->isBreak()) {
					LOG_PRINT("\t%s", a->getName().GetOriginal());
				}
			}
		}
	})
		.addTooltip("Test"));

	addOption(ButtonOption("Write entrypoints")
		.addFunction([] {

		ofstream file;
		file.open("EP.txt");
		for (int i = 0; i < 11882; i += 2) {
			auto addr = Natives::getNativeHandlerCache(Crossmap::m_crossmapData[i]);
			file << hex << "0x" << Crossmap::m_crossmapData[i] << " : " << "GTA5.exe+0x" << (uint64_t)addr - (uint64_t)GetModuleHandle(nullptr) << endl;
		}
		file.close();
	})
		.addHotkey()
		.addTooltip("Write entrypoints"));

	addOption(ToggleOption("g_hipsterHeader")
		.addToggle(vars.header));

	addOption(ToggleOption("Log script events")
		.addToggle(NetEvent::vars.ePqGPRWkeLpOicfiJfNO));

	addOption(ToggleOption("Block all net events")
		.addToggle(NetEvent::vars.blockallnetevents));

	addOption(ToggleOption("tweest")
		.addToggle(vars.drop));

	addOption(ToggleOption("Log entities")
		.addToggle(vars.logentities));

	addOption(ToggleOption("Log net events")
		.addTooltip("This will log all net events and print them to your log")
		.addToggle(NetEvent::vars.logallnetevents));

	addOption(ToggleOption("submenu")
		.addToggle(vars.submenu));

	addOption(ToggleOption("testing")
		.addToggle(vars.testing));

	addOption(ButtonOption("Notify")
		.addFunction([] { GetRenderer()->NotifyMap("titties"); }));

	/*addOption(ButtonOption("Patch bonus section")
		.addFunction([] { Backend::GetTunables()->setTunable(555, 555); }));*/

#endif
}

/*Update once when submenu is opened*/
void DeveloperMenu::UpdateOnce() {}

/*Update while submenu is active*/
void DeveloperMenu::Update() {}

/*Background update*/
void DeveloperMenu::FeatureUpdate() {
	//if (vars.testing) WhoKilledMe();

	if (vars.header) {
		//AnimatedImages::g_hipsterHeader.Draw(0.5f, 0.5f, GetRenderer()->m_width, GetRenderer()->m_headerHeight);
	}
	//test(50000, "GC_RE_TMR", 0, 0, -1, 0, 13, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0);
	if (vars.drop) {
		static int TIMER;
		Utils::DoTimedFunction(&TIMER, 500, [] {
			Vector3 coords = GetLocalPlayer().m_coordinates;
			coords.z += 1;
			GetEntityControl()->SimpleRequestModel(-1666779307);
			OBJECT::CreateAmbientPickup(0xE175C698, coords.x, coords.y, coords.z, 0, 3000, -1666779307, false, true);
			//OBJECT::CreateAmbientPickup(0xDE78F17E, coords.x, coords.y, coords.z, 0, 1001, -1332461625, false, true);
			//OBJECT::CreatePickup(0xDE78F17E, coords.x, coords.y, coords.z, 0, 1001, true, -1332461625);
		});
	}

	if (vars.submenu) {
		GetSubmenuHandler()->SetSubPrevious(false);
	}


}

/*Singleton*/
DeveloperMenu* _instance;
DeveloperMenu* DeveloperMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new DeveloperMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
DeveloperMenu::~DeveloperMenu() { delete _instance; }