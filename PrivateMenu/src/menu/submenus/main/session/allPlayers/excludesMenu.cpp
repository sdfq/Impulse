#include "stdafx.h"
#include "excludesMenu.h"
#include "../allPlayersMenu.h"

using namespace ExcludesMenuVars;

namespace ExcludesMenuVars {
	Vars vars;

	bool IsExcluded(SPlayer& p) {
		return (vars.host && p.m_isHost)
			|| (vars.host && p.m_isScriptHost)
			|| (vars.team && GetLocalPlayer().m_team == p.m_team)
			|| (vars.friends && p.m_isFriend)
			|| (vars.evolve && (p.m_isEvolveUser || p.m_isEvolveUserBlock))
			|| (vars.self &&(p.m_id == GetLocalPlayer().m_id));
	}
}

void ExcludesMenu::Init() {
	setParentSubmenu<AllPlayersMenu>();
	setName("Excludes", true, true);

	addOption(ToggleOption("Exclude friends")
		.addToggle(vars.friends)
		.addTranslation().canBeSaved().addHotkey()
		.addTooltip("Exclude friends"));

	addOption(ToggleOption("Exclude modders")
		.addToggle(vars.modders)
		.addTranslation().canBeSaved().addHotkey()
		.addTooltip("Exclude modders"));

	addOption(ToggleOption("Exclude team")
		.addToggle(vars.team)
		.addTranslation().canBeSaved().addHotkey()
		.addTooltip("Exclude team"));

	addOption(ToggleOption("Exclude host")
		.addToggle(vars.host)
		.addTranslation().canBeSaved().addHotkey()
		.addTooltip("Exclude host"));

	addOption(ToggleOption("Exclude self")
		.addToggle(vars.self)
		.addTranslation().canBeSaved().addHotkey()
		.addTooltip("Exclude self"));

	addOption(ToggleOption("Exclude Impulse users")
		.addToggle(vars.evolve)
		.addTranslation().canBeSaved().addHotkey()
		.addTooltip("Exclude Impulse users"));
}

/*Update once when submenu is opened*/
void ExcludesMenu::UpdateOnce() {}

/*Update while submenu is active*/
void ExcludesMenu::Update() {}

/*Background update*/
void ExcludesMenu::FeatureUpdate() {}

/*Singleton*/
ExcludesMenu* _instance;
ExcludesMenu* ExcludesMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new ExcludesMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
ExcludesMenu::~ExcludesMenu() { delete _instance; }