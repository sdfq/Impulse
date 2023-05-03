#include "stdafx.h"
#include "sessionPeacefulMenu.h"
#include "../allPlayersMenu.h"
#include "../playerList/player/peacefulMenu.h"
#include "menu/submenus/main/teleportMenu.h"

using namespace SessionPeacefulMenuVars;

namespace SessionPeacefulMenuVars {
	Vars vars;

	void GiveAllWeapons() {
		GetFiberPool()->DoJob([] {
			for (int i = 0; i < MAXPLAYERS; i++) {
				auto player = GetPlayer(i);
				if (player.m_exists) {
					PeacefulMenuVars::GiveAllWeapons(player);
				} else continue;
				WAIT(500);
			}
		});
	}

	ScrollStruct<int> drops[] = {
		TranslationString("Standard", true), 0,
		TranslationString("Circle", true), 1,
	};

	ScrollStruct<int> presetlocations[] = {
		TranslationString("None", true), 0,
		TranslationString("Maze Bank", true), 1,
		TranslationString("Airport", true), 2,
		TranslationString("Eclipse Towers", true), 3,
		TranslationString("Trevors Airfield", true), 4,
		TranslationString("Dam", true), 5,
		TranslationString("Car Park", true), 6
	};

	ScrollStruct<int> howmanylocs[] = {
		TranslationString("One location", true), 0,
		TranslationString("Two locations", true), 1,
		TranslationString("Three locations", true), 2,
	};
}

void SessionPeacefulMenu::Init() {
	setParentSubmenu<AllPlayersMenu>();
	setName("Peaceful", true, true);

	addOption(ButtonOption("Give all weapons")
		.addFunction([] { GiveAllWeapons(); })
		.addTooltip("Give the session all weapons")
		.addTranslation().addHotkey());

	addOption(ButtonOption("Spawn clone bodyguard")
		.addFunction([] { OnlinePlayerCallback(true, [](SPlayer player) { if(player.m_id != GetLocalPlayer().m_id) PeacefulMenuVars::SpawnCloneBodyguard(player); }); })
		.addTooltip("Spawn clone bodyguard")
		.addTranslation().addHotkey());

	addOption(ButtonOption("Clear area")
		.addFunction([] { OnlinePlayerCallback(true, [](SPlayer player) { MISC::_ClearAreaOfEverything(player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 50.0f, true, true, true, true); }); })
		.addTooltip("CLear the sessions area")
		.addTranslation().addHotkey());

	addOption(ButtonOption("Give players impact bullets")
		.addFunction([] { OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_id != GetLocalPlayer().m_id) PeacefulMenuVars::GiveOptionGun(player); }); })
		.addTooltip("Give player impact ammo")
		.addTranslation().addHotkey());

	addOption(ButtonOption("Remove all players attachments")
		.addFunction([] { OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_id != GetLocalPlayer().m_id) PeacefulMenuVars::RemoveAttachments(player); }); })
		.addTranslation().addHotkey()
		.addTooltip("Clear the players attached entities").addTranslation());

	addOption(BreakOption("Money").addTranslation());

	addOption(NumberOption<int>(SCROLL, "Nearby drop delay (ms)")
		.addNumber(vars.nearbydropdelay, "%i", 50).addMin(200).addMax(5000)
		.addHotkey()
		.addTooltip("Control the speed of the money drops"));

	addOption(ToggleOption("Nearby money drop")
		.addToggle(vars.nearbyMoneyDropnoncir)
		.addTooltip("Drop money to nearby players")
		.addTranslation().addHotkey());

	addOption(ToggleOption("Nearby circle money drop")
		.addToggle(vars.nearbyMoneyDrop)
		.addTooltip("Drop money to nearby players")
		.addTranslation().addHotkey());

	addOption(ToggleOption("Money rain on self")
		.addToggle(vars.selfMoneyDrop)
		.addTooltip("Spawn a money drop above you")
		.addTranslation().addHotkey());

	addOption(BreakOption("Money Location").addTranslation());

	addOption(NumberOption<int>(SCROLL, "Location drop delay (ms)")
		.addNumber(vars.locationmoneydelay, "%i", 50).addMin(200).addMax(5000)
		.addHotkey()
		.addTooltip("Control the speed of the money drops"));

	addOption(ScrollOption<int>(SCROLLSELECT, "Drop at")
		.addScroll(vars.howmanylocsforcus, 0, NUMOF(howmanylocs) - 1, howmanylocs)
		.addFunction([] { TeleportMenuVars::TeleportToCoords(vars.dropposition); })
		.addTooltip("Select how many locations to drop at").addTranslation());

	addOption(ScrollOption<int>(SCROLLSELECT, "Preset locations")
		.addRequirement([] { return vars.howmanylocsforcus == 0; })
		.addScroll(vars.presetdroploc, 0, NUMOF(presetlocations) - 1, presetlocations)
		.addFunction([] { TeleportMenuVars::TeleportToCoords(vars.dropposition); })
		.addTooltip("Slide to select a preset location and enter the location to teleport there").addTranslation());

	addOption(ButtonOption("Set to my location")
		.addRequirement([] { return vars.presetdroploc == 0; })
		.addFunction([] {
		const auto position = ENTITY::GetEntityCoords(PLAYER::PlayerPedId(), !ENTITY::IsEntityDead(PLAYER::PlayerPedId(), false));
		vars.dropposition.x = position.x;
		vars.dropposition.y = position.y;
		vars.dropposition.z = position.z + 1.5f;
		//LOG_PRINT("Loc: %.1f, %.1f, %.1f", position.x, position.y, position.z);
	}).addTranslation().addHotkey()
		.addTooltip("This will set the location for the next money drop"));

	addOption(ButtonOption("Set second to my location")
		.addRequirement([] { return vars.howmanylocsforcus == 1 || vars.howmanylocsforcus == 2; })
		.addFunction([] {
		const auto position2 = ENTITY::GetEntityCoords(PLAYER::PlayerPedId(), !ENTITY::IsEntityDead(PLAYER::PlayerPedId(), false));
		vars.dropposition2.x = position2.x;
		vars.dropposition2.y = position2.y;
		vars.dropposition2.z = position2.z + 1.5f;
		//LOG_PRINT("Loc: %.1f, %.1f, %.1f", position.x, position.y, position.z);
	}).addTranslation().addHotkey()
		.addTooltip("This will set the location for the next money drop"));

	addOption(ButtonOption("Set third to my location")
		.addRequirement([] { return vars.howmanylocsforcus == 2; })
		.addFunction([] {
		const auto position3 = ENTITY::GetEntityCoords(PLAYER::PlayerPedId(), !ENTITY::IsEntityDead(PLAYER::PlayerPedId(), false));
		vars.dropposition3.x = position3.x;
		vars.dropposition3.y = position3.y;
		vars.dropposition3.z = position3.z + 1.5f;
		//LOG_PRINT("Loc: %.1f, %.1f, %.1f", position.x, position.y, position.z);
	}).addTranslation().addHotkey()
		.addTooltip("This will set the location for the next money drop"));

	addOption(ToggleOption("Show marker/s")
		.addToggle(vars.drawDropMarker)
		.addTooltip("Show a marker where you have set your drop location")
		.addTranslation().addHotkey());

	addOption(ScrollOption<int>(TOGGLE, "Money drop at set location/s")
		.addToggle(vars.locationmoneydrop)
		.addScroll(vars.drops, 0, NUMOF(drops) - 1, drops)
		.addTooltip("This will drop money at location, using the method selected, use Money drop time to edit speed")
		.addTranslation().addHotkey());
}

/*Update once when submenu is opened*/
void SessionPeacefulMenu::UpdateOnce() {}

/*Update while submenu is active*/
void SessionPeacefulMenu::Update() {
	if (vars.presetloccheck) {
		if (vars.presetdroploc == 0) {
		}
		if (vars.presetdroploc == 1) {
			vars.dropposition.x = -75.3;
			vars.dropposition.y = -819.1;
			vars.dropposition.z = 326.2 + 1.5f;
		}
		if (vars.presetdroploc == 2) {
			vars.dropposition.x = -1023.6;
			vars.dropposition.y = -2960.6;
			vars.dropposition.z = 13.9 + 1.5f;
		}
		if (vars.presetdroploc == 3) {
			vars.dropposition.x = -772.8;
			vars.dropposition.y = 288.5;
			vars.dropposition.z = 85.8 + 1.5f;
		}
		if (vars.presetdroploc == 4) {
			vars.dropposition.x = 1736.0;
			vars.dropposition.y = 3293.6;
			vars.dropposition.z = 41.2 + 1.5f;
		}
		if (vars.presetdroploc == 5) {
			vars.dropposition.x = 1661.5;
			vars.dropposition.y = -48.1;
			vars.dropposition.z = 168.3 + 1.5f;
		}
		if (vars.presetdroploc == 6) {
			vars.dropposition.x = -332.2;
			vars.dropposition.y = -751.6;
			vars.dropposition.z = 53.2 + 1.5f;
		}
	}
}

/*Background update*/
void SessionPeacefulMenu::FeatureUpdate() {
	if (vars.nearbyMoneyDrop) {
		static int TIMER;
		OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_id != GetLocalPlayer().m_id && player.m_coordinates.Distance(GetLocalPlayer().m_coordinates) <= 75.f)  GRAPHICS::DrawMarker(29, player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z + 1.5f, 0.f, 0.f, 0.f, 0.f, 180.f, 0.f, 0.7f, 0.7f, 0.7f, 255, 0, 0, 200, 1, 1, 1, 1, 0, 0, 0); });
		Utils::DoTimedFunction(&TIMER, vars.nearbydropdelay, [] {
			OnlinePlayerCallback(true, [](SPlayer player) {
				if (player.m_id != GetLocalPlayer().m_id && player.m_coordinates.Distance(GetLocalPlayer().m_coordinates) <= 75.f) {
					GetEntityControl()->SimpleRequestModel(-1666779307);
					OBJECT::CreateMoneyPickups(player.m_coordinates.x + 0.4, player.m_coordinates.y + 0.6, player.m_coordinates.z, 0x1E9A99F8, 2500, -1666779307);
				}
			});
		});
	}

	if (vars.nearbyMoneyDropnoncir) {
		static int TIMER;
		OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_id != GetLocalPlayer().m_id && player.m_coordinates.Distance(GetLocalPlayer().m_coordinates) <= 75.f)  GRAPHICS::DrawMarker(29, player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z + 1.5f, 0.f, 0.f, 0.f, 0.f, 180.f, 0.f, 0.7f, 0.7f, 0.7f, 255, 0, 0, 200, 1, 1, 1, 1, 0, 0, 0); });
		Utils::DoTimedFunction(&TIMER, vars.nearbydropdelay, [] {
			OnlinePlayerCallback(true, [](SPlayer player) {
				if (player.m_id != GetLocalPlayer().m_id && player.m_coordinates.Distance(GetLocalPlayer().m_coordinates) <= 75.f) {
					GetEntityControl()->SimpleRequestModel(-1666779307);
					OBJECT::CreateAmbientPickup(0x1E9A99F8, player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 0, 2500, -1666779307, false, true);
				}
			});
		});
	}

	if (vars.drawDropMarker) {
		GRAPHICS::DrawMarker(21, vars.dropposition.x, vars.dropposition.y, vars.dropposition.z, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f, 0.0f, 0.9f, 0.9f, 0.9f, 255, 0, 0, 255, true, false, 2, true, nullptr, nullptr, false);
		if (vars.howmanylocsforcus == 1 || vars.howmanylocsforcus == 2)
		GRAPHICS::DrawMarker(21, vars.dropposition2.x, vars.dropposition2.y, vars.dropposition2.z, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f, 0.0f, 0.9f, 0.9f, 0.9f, 255, 0, 0, 255, true, false, 2, true, nullptr, nullptr, false);
		if (vars.howmanylocsforcus == 2)
		GRAPHICS::DrawMarker(21, vars.dropposition3.x, vars.dropposition3.y, vars.dropposition3.z, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f, 0.0f, 0.9f, 0.9f, 0.9f, 255, 0, 0, 255, true, false, 2, true, nullptr, nullptr, false);
	}

	if (vars.locationmoneydrop) {
		static int TIMER;
		Utils::DoTimedFunction(&TIMER, vars.locationmoneydelay, [] {
			GetEntityControl()->SimpleRequestModel(-1666779307);
			if (vars.drops == 0) {
				OBJECT::CreateAmbientPickup(0x1E9A99F8, vars.dropposition.x, vars.dropposition.y, vars.dropposition.z, 0, 2500, -1666779307, false, true);
				if (vars.howmanylocsforcus == 1 || vars.howmanylocsforcus == 2)
				OBJECT::CreateAmbientPickup(0x1E9A99F8, vars.dropposition2.x, vars.dropposition2.y, vars.dropposition2.z, 0, 2500, -1666779307, false, true);
				if (vars.howmanylocsforcus == 2)
				OBJECT::CreateAmbientPickup(0x1E9A99F8, vars.dropposition3.x, vars.dropposition3.y, vars.dropposition3.z, 0, 2500, -1666779307, false, true);
			} else if (vars.drops == 1) {
				OBJECT::CreateMoneyPickups(vars.dropposition.x, vars.dropposition.y, vars.dropposition.z, 0x1E9A99F8, 2500, -1666779307);
				if (vars.howmanylocsforcus == 1 || vars.howmanylocsforcus == 2)
				OBJECT::CreateMoneyPickups(vars.dropposition2.x, vars.dropposition2.y, vars.dropposition2.z, 0x1E9A99F8, 2500, -1666779307);
				if (vars.howmanylocsforcus == 2)
				OBJECT::CreateMoneyPickups(vars.dropposition3.x, vars.dropposition3.y, vars.dropposition3.z, 0x1E9A99F8, 2500, -1666779307);
			}
		});
	}

	if (vars.selfMoneyDrop) {
		static int TIMER;
		Utils::DoTimedFunction(&TIMER, vars.nearbydropdelay, [] {
			float RandomX = MISC::GetRandomFloatInRange(-9, 9);
			float RandomY = MISC::GetRandomFloatInRange(-9, 9);
			float RandomZ = MISC::GetRandomFloatInRange(7, 13);
			Vector3 SpawnLocation = ENTITY::GetOffsetFromEntityInWorldCoords(GetLocalPlayer().m_ped, RandomX, RandomY, RandomZ);
			GetEntityControl()->SimpleRequestModel(-1666779307);
			OBJECT::CreateAmbientPickup(0x1E9A99F8, SpawnLocation.x, SpawnLocation.y, SpawnLocation.z, 0, 2500, -1666779307, false, true);
		});
	}
}

/*Singleton*/
SessionPeacefulMenu* _instance;
SessionPeacefulMenu* SessionPeacefulMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new SessionPeacefulMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
SessionPeacefulMenu::~SessionPeacefulMenu() { delete _instance; }