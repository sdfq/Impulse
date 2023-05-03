#include "stdafx.h"
#include "spawnVehicleSettingsMenu.h"
#include "../spawnVehicleMenu.h"

using namespace SpawnVehicleSettingsMenuVars;

namespace SpawnVehicleSettingsMenuVars {
	Vars vars;

	void SetNumberPlate(Vehicle vehicle, String text) {
		VEHICLE::SetVehicleNumberPlateText(vehicle, text);
	}
}

void SpawnVehicleSettingsMenu::Init() {
	setParentSubmenu<SpawnVehicleMenu>();
	setName("Spawn vehicle settings", true, true);

	addOption(ToggleOption("Spawn with blip")
		.addToggle(vars.blip)
		.addTranslation().canBeSaved().addHotkey()
		.addTooltip("Spawn vehicle with a minimap blip"));

	addOption(ToggleOption("Spawn with particles")
		.addToggle(vars.particles).canBeSaved().addHotkey()
		.addTooltip("Spawn ped with particles").addTranslation());

	/*addOption(ToggleOption("Spawn with fade")
		.addToggle(vars.fade)
		.addTooltip("Spawn ped with fade").addTranslation());*/

	addOption(ToggleOption("Spawn with information")
		.addToggle(vars.information).canBeSaved().addHotkey()
		.addTooltip("Spawn ped with information").addTranslation());

	addOption(ToggleOption("Spawn inside vehicle")
		.addToggle(vars.spawnin)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Spawn inside vehicle"));

	addOption(ToggleOption("Spawn invincible")
		.addToggle(vars.spawninvincible)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Spawn invincible"));

	addOption(ToggleOption("Spawn fully tuned")
		.addToggle(vars.spawnmaxed)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Spawn fully tuned"));

	addOption(ToggleOption("Delete old vehicle")
		.addToggle(vars.deleteold)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Delete old vehicle"));

	addOption(ToggleOption("Spawn planes and helicopters in the air")
		.addToggle(vars.spawninair)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Spawn planes and helicopters in the air"));

	addOption(NumberOption<int>(SCROLL, "Spawn speed")
		.addNumber(vars.spawnspeed, "%d", 1).addMin(0).addMax(300)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("The speed at which your spawned vehicle will launch"));

	addOption(NumberOption<float>(SCROLL, "Spawn height")
		.addNumber(vars.spawnheight, "%.2f", 5.0f).addMin(0.0f).addMax(1000.0f)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("The height at which your spawned vehicle will be at"));

	addOption(BreakOption("Color").addTranslation());

	addOption(ToggleOption("Do not spawn with custom colors")
		.addToggle(vars.spawndefault)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("This will leave the vehicle spawn as games default"));

	addOption(ColorOption("Default primary vehicle color")
		.addColor(vars.dprimary)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Set the primary vehicle color"));

	addOption(ColorOption("Default secondary vehicle color")
		.addColor(vars.dsecondary)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Secondary color for vehicles"));
}

/*Update once when submenu is opened*/
void SpawnVehicleSettingsMenu::UpdateOnce() {}

/*Update while submenu is active*/
void SpawnVehicleSettingsMenu::Update() {}

/*Background update*/
void SpawnVehicleSettingsMenu::FeatureUpdate() {}

/*Singleton*/
SpawnVehicleSettingsMenu* _instance;
SpawnVehicleSettingsMenu* SpawnVehicleSettingsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new SpawnVehicleSettingsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
SpawnVehicleSettingsMenu::~SpawnVehicleSettingsMenu() { delete _instance; }