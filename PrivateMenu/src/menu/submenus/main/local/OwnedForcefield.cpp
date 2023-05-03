#include "stdafx.h"
#include "OwnedForcefield.h"
#include "menu\submenus\main\localMenu.h"

using namespace OwnedForcefieldVars;

namespace OwnedForcefieldVars {
	Vars vars;
}

void OwnedForcefield::Init() {
	setParentSubmenu<LocalMenu>();
	setName("Owned forcefield", true, true);

	addOption(ToggleOption("Toggle")
		.addToggle(vars.ForcefieldToggle)
		.addTooltip("Turn on the blame function and walk around to kill people in their name")
		.addTranslation().addHotkey());

	addOption(BreakOption());

}

/*Update once when submenu is opened*/
void OwnedForcefield::UpdateOnce() {}

/*Update while submenu is active*/
void OwnedForcefield::Update() {
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
void OwnedForcefield::FeatureUpdate() {
	if (vars.ForcefieldToggle) {
		Vector3 coords = ENTITY::GetEntityCoords(PLAYER::GetPlayerPedScriptIndex(PLAYER::PlayerId()), true);
		GetLocalPlayer().setInvincible(GetLocalPlayer().m_ped);
		Natives::AddOwnedExplosion(vars.targetPlayer.m_ped, coords.x, coords.y, coords.z, 29, 10, false, true, 0);
	}
}

/*Singleton*/
OwnedForcefield* _instance;
OwnedForcefield* OwnedForcefield::GetInstance() {
	if (_instance == nullptr) {
		_instance = new OwnedForcefield();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
OwnedForcefield::~OwnedForcefield() { delete _instance; }