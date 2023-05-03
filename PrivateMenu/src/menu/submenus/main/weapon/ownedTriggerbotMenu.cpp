#include "stdafx.h"
#include "ownedTriggerbotMenu.h"
#include "menu/submenus/main/weaponMenu.h"

using namespace ownedTriggerbotVars;

namespace ownedTriggerbotVars {
	Vars vars;
}

void ownedTriggerbotMenu::Init() {
	setParentSubmenu<WeaponMenu>();
	setName("Owned triggerbot", true, true);

	addOption(ToggleOption("Toggle")
		.addToggle(vars.triggerbotToggle)
		.addTooltip("Turn on the blame function and aim at players to kill people in their name")
		.addTranslation().addHotkey());

	addOption(BreakOption());

	
}

/*Update once when submenu is opened*/
void ownedTriggerbotMenu::UpdateOnce() {}

/*Update while submenu is active*/
void ownedTriggerbotMenu::Update() {
	static int TIMER;
	static bool update = true;
	Utils::DoTimedFunction(&TIMER, 250, [] {update = true; });
	if (update) {
		clearOptionsOffset(2);
		vector<SPlayer> players;
		for (int i = 0; i < MAXPLAYERS; i++) {
			if (GetPlayer(i).m_exists) {
				players.push_back(GetPlayer(i));
			}
		}
		for (SPlayer& player : players) {
			string displayName = player.m_name;
			if (player.m_id == vars.targetPlayer.m_id)
				displayName = "~o~" + displayName;
			addOption(ButtonOption(displayName.c_str())
				.addTooltip("Select this person to use on the blame")
				.addFunction([&] { vars.targetPlayer = player; }));
		}

		if (GetMenu()->m_currentOption > m_options.size()) GetMenu()->ResetCurrentOption();
		update = false;
	}
}

/*Background update*/
void ownedTriggerbotMenu::FeatureUpdate() {
	if (vars.triggerbotToggle) {
		Entity target;
		if (PLAYER::GetEntityPlayerIsFreeAimingAt(GetLocalPlayer().m_id, &target)) {
			Vector3 coords = ENTITY::GetEntityCoords(target, true);
			Natives::AddOwnedExplosion(vars.targetPlayer.m_ped, coords.x, coords.y, coords.z, 36, 10, false, true, 0);
		}
	}
}

/*Singleton*/
ownedTriggerbotMenu* _instance;
ownedTriggerbotMenu* ownedTriggerbotMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new ownedTriggerbotMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
ownedTriggerbotMenu::~ownedTriggerbotMenu() { delete _instance; }