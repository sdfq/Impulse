#include "stdafx.h"
#include "spawnObjectSettingsMenu.h"
#include "../spawnObjectMenu.h"

using namespace SpawnObjectSettingsMenuVars;

namespace SpawnObjectSettingsMenuVars {
	Vars vars;
}

void SpawnObjectSettingsMenu::Init() {
	setParentSubmenu<SpawnObjectMenu>();
	setName("Spawn object settings", true, true);

	addOption(ToggleOption("Spawn object with blip")
		.addToggle(vars.blip).canBeSaved().addHotkey()
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Spawn object with a minimap blip"));

	addOption(ToggleOption("Spawn with particles")
		.addToggle(vars.particles).canBeSaved().addHotkey()
		.addTooltip("Spawn ped with particles").addTranslation());

	/*addOption(ToggleOption("Spawn with fade")
		.addToggle(vars.fade)
		.addTooltip("Spawn ped with fade").addTranslation());*/

	addOption(ToggleOption("Spawn with information")
		.addToggle(vars.information).canBeSaved().addHotkey()
		.addTooltip("Spawn ped with information").addTranslation());
}

/*Update once when submenu is opened*/
void SpawnObjectSettingsMenu::UpdateOnce() {}

/*Update while submenu is active*/
void SpawnObjectSettingsMenu::Update() {}

/*Background update*/
void SpawnObjectSettingsMenu::FeatureUpdate() {}

/*Singleton*/
SpawnObjectSettingsMenu* _instance;
SpawnObjectSettingsMenu* SpawnObjectSettingsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new SpawnObjectSettingsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
SpawnObjectSettingsMenu::~SpawnObjectSettingsMenu() { delete _instance; }