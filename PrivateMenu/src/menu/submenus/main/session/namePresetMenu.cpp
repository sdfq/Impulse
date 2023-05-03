#include "stdafx.h"
#include "namePresetMenu.h"
#include "nameMenu.h"

using namespace NamePresetMenuVars;

namespace NamePresetMenuVars {
	vector<String> names = {
		"Impulse",
		"Server Admin",
		"Take-Two",
		"ChildForSale",
		"MoneyDrop",
		"Nigger",
		"RacismMyth",
		"Taxation",
		"Religion?",
		"BanRifles",
		"WageGap",
		"EggNog",
		"uWu",
		"666"
	};
}

void NamePresetMenu::Init() {
	setParentSubmenu<NameMenu>();
	setName("Preset names", true, true);

	for (String element : names) {
		addOption(ButtonOption(element)
			.addFunction([=] { NameMenuVars::setName(element); })
			.addTooltip("Set this as your name"));
	}
}

/*Update once when submenu is opened*/
void NamePresetMenu::UpdateOnce() {}

/*Update while submenu is active*/
void NamePresetMenu::Update() {}

/*Background update*/
void NamePresetMenu::FeatureUpdate() {}

/*Singleton*/
NamePresetMenu* _instance;
NamePresetMenu* NamePresetMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new NamePresetMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
NamePresetMenu::~NamePresetMenu() { delete _instance; }