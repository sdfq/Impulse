#include "stdafx.h"
#include "streamermodeMenu.h"
#include "menu/submenus/main/sessionMenu.h"
#include "menu/submenus/main/session/nameMenu.h"

using namespace StreamerModeMenuVars;

namespace StreamerModeMenuVars {
	Vars vars;

	void CustomName() {
		GetMenuInput()->AddToQueue([] {
			string input;
			if (GetMenuInput()->Text("Prefix Name", input, 1, 10)) {
				vars.nameprefix = input;
			}
		});
	}

	void ChangeOwnName() {
		string name = vars.nameprefix.c_str();
		NameMenuVars::setName(name.c_str());
	}
}

void StreamerModeMenu::Init() {
	setParentSubmenu<SessionMenu>();
	setName("Streamer Mode", true, true);

	addOption(ToggleOption("Streamer mode")
		.addToggle(vars.StreamerMode)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Changes all names to player 1, 2, 3 etc. Requires you to switch lobby."));

	addOption(ToggleOption("Change lobby r* ids")
		.addToggle(vars.changelobbyrids)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Changes all rockstar IDs to 1, 2, 3 etc. Requires you to switch lobby."));

	addOption(ButtonOption("Change own name")
		.addFunction(ChangeOwnName)
		.addTranslation().addHotkey()
		.addTooltip("Changes your own name to match playerlist. Requires you to switch lobby."));

	addOption(ButtonOption("")
		.addFunction(CustomName)
		.addOnUpdate([](ButtonOption* option) {
		static int TIMER, offset;
		static char name[50];
		vaBuff(name, 50, "Prefix name: %s", vars.nameprefix.c_str());
		option->setName(name);
	})
		.addTooltip("This will display the name prefix for lobby playernames [default name = player_X]"));
}

/*Update once when submenu is opened*/
void StreamerModeMenu::UpdateOnce() {}

/*Update while submenu is active*/
void StreamerModeMenu::Update() {}

/*Background update*/
void StreamerModeMenu::FeatureUpdate() {}

/*Singleton*/
StreamerModeMenu* _instance;
StreamerModeMenu* StreamerModeMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new StreamerModeMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
StreamerModeMenu::~StreamerModeMenu() { delete _instance; }