#include "stdafx.h"
#include "spawnPedSettingsMenu.h"
#include "../spawnPedMenu.h"

using namespace SpawnPedSettingsMenuVars;

namespace SpawnPedSettingsMenuVars {
	Vars vars;
}

void SpawnPedSettingsMenu::Init() {
	setParentSubmenu<SpawnPedMenu>();
	setName("Spawn ped settings", true, true);

	addOption(ToggleOption("Spawn invincible")
		.addToggle(vars.godmode).canBeSaved().addHotkey()
		.addTooltip("Spawn ped with godmode").addTranslation());

	addOption(ToggleOption("Spawn with blip")
		.addToggle(vars.blip).canBeSaved().addHotkey()
		.addTooltip("Spawn ped with minimap blip").addTranslation());

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
void SpawnPedSettingsMenu::UpdateOnce() {}

/*Update while submenu is active*/
void SpawnPedSettingsMenu::Update() {}

/*Background update*/
void SpawnPedSettingsMenu::FeatureUpdate() {}

/*Singleton*/
SpawnPedSettingsMenu* _instance;
SpawnPedSettingsMenu* SpawnPedSettingsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new SpawnPedSettingsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
SpawnPedSettingsMenu::~SpawnPedSettingsMenu() { delete _instance; }