#include "stdafx.h"
#include "menu/submenus/mainMenu.h"
#include "customSwappingMenu.h"
#include "swappingPresetsMenu.h"
#include "swappedModelsMenu.h"

using namespace SwappingPresetsMenuVars;

namespace SwappingPresetsMenuVars {
	Vars var;

	bool IsPresetActive() {
		if (var.emergencyToTrucks) return true;
		if (var.planesToCargos) return true;
		if (var.planesToTitans) return true;
		if (var.policeToTrucks) return true;
		if (var.superToBuffalos) return true;
		if (var.vansToInsurgents) return true;
		return false;
	}
}

void SwapPresetsMenu::Init() {
	setParentSubmenu<MainMenu>();
	setName("Presets", true, true);

	addOption(SubmenuOption("Custom swapping")
		.addSubmenu<CustomSwappingMenu>()
		.addTooltip("Swap models with whatever you'd like to see")
		.addRequirement([] { return GetAuth()->IsVIP(); }));

	addOption(SubmenuOption("Swapped models")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addSubmenu<SwappedModelsMenu>()
		.addTooltip("Remove (and list) model swaps"));

	addOption(BreakOption("Premade Swaps").addTranslation());

	addOption(ToggleOption("Emergency vehicles turn to monster trucks")
		.addToggle(var.emergencyToTrucks)
		.addFunction([] {
		if (var.emergencyToTrucks) {
			for (String m : emergency) {
				ModelSwapping::ModelSwap(m, "marshall");
			}
		}
		else {
			for (String m : emergency) {
				ModelSwapping::RemoveSwap(m);
			}
		}
	})
		.addTooltip("Turns all emergency vehicles into monster trucks")
		.addTranslation()
		.addHotkey()
		.addRequirement([] { return !IsPresetActive() || var.emergencyToTrucks; }));

	addOption(ButtonOption("~c~Emergency vehicles turn to monster trucks")
		.addRequirement([] { return IsPresetActive() && !var.emergencyToTrucks; }));

	addOption(ToggleOption("Police vehicles turn to monster trucks")
		.addToggle(var.policeToTrucks)
		.addFunction([] {
		if (var.policeToTrucks) {
			for (String m : police) {
				ModelSwapping::ModelSwap(m, "marshall");
			}
		}
		else {
			for (String m : police) {
				ModelSwapping::RemoveSwap(m);
			}
		}
	})
		.addTooltip("Turns all police vehicles into monster trucks")
		.addTranslation()
		.addHotkey()
		.addRequirement([] { return !IsPresetActive() || var.policeToTrucks; }));

	addOption(ButtonOption("~c~Police vehicles turn to monster trucks")
		.addRequirement([] { return IsPresetActive() && !var.policeToTrucks; }));

	addOption(ToggleOption("Supercars turn to buffalos")
		.addToggle(var.superToBuffalos)
		.addFunction([] {
		if (var.superToBuffalos) {
			for (String m : super) {
				ModelSwapping::ModelSwap(m, "buffalo");
			}
		}
		else {
			for (String m : super) {
				ModelSwapping::RemoveSwap(m);
			}
		}
	})
		.addTooltip("Turns all super cars vehicles buffalos")
		.addTranslation()
		.addHotkey()
		.addRequirement([] { return !IsPresetActive() || var.superToBuffalos; }));

	addOption(ButtonOption("~c~Supercars turn to buffalos")
		.addRequirement([] { return IsPresetActive() && !var.superToBuffalos; }));

	addOption(ToggleOption("Planes turn to titans")
		.addToggle(var.planesToTitans)
		.addFunction([] {
		if (var.planesToTitans) {
			for (String m : planes) {
				ModelSwapping::ModelSwap(m, "titan");
			}
		}
		else {
			for (String m : planes) {
				ModelSwapping::RemoveSwap(m);
			}
		}
	})
		.addTooltip("Turns all planes into titans")
		.addTranslation()
		.addHotkey()
		.addRequirement([] { return !IsPresetActive() || var.planesToTitans; }));

	addOption(ButtonOption("~c~Planes turn to titans")
		.addRequirement([] { return IsPresetActive() && !var.planesToTitans; }));

	addOption(ToggleOption("Planes turn to cargoplanes")
		.addToggle(var.planesToCargos)
		.addFunction([] {
		if (var.planesToCargos) {
			for (String m : planes) {
				ModelSwapping::ModelSwap(m, "cargoplane");
			}
		}
		else {
			for (String m : planes) {
				ModelSwapping::RemoveSwap(m);
			}
		}
	})
		.addTooltip("Turns all planes into cargoplanes")
		.addTranslation()
		.addHotkey()
		.addRequirement([] { return !IsPresetActive() || var.planesToCargos; }));

	addOption(ButtonOption("~c~Planes turn to cargoplanes")
		.addRequirement([] { return IsPresetActive() && !var.planesToCargos; }));

	addOption(ToggleOption("Vans turn to insurgents")
		.addToggle(var.vansToInsurgents)
		.addFunction([] {
		if (var.vansToInsurgents) {
			for (String m : van) {
				ModelSwapping::ModelSwap(m, "insurgent");
			}
		}
		else {
			for (String m : van) {
				ModelSwapping::RemoveSwap(m);
			}
		}
	})
		.addTooltip("Turns all vans to insurgents")
		.addTranslation()
		.addHotkey()
		.addRequirement([] { return !IsPresetActive() || var.vansToInsurgents; }));

	addOption(ButtonOption("~c~Vans turn to insurgents")
		.addRequirement([] { return IsPresetActive() && !var.vansToInsurgents; }));

/*
	addOption(ButtonOption("Emergency vehicles turn to monster trucks")
		.addFunction([] {
		for (String m : emergency) {
			ModelSwapping::ModelSwap(m, "Marshall");
		}
	})
		.addTooltip("Turns all emergency vehicles into monster trucks.")
		.addHotkey()
		.addTranslation());

	addOption(ButtonOption("Police vehicles turn to monster trucks")
		.addFunction([] {
		for (String m : police) {
			ModelSwapping::ModelSwap(m, "Marshall");
		}
	})
		.addTooltip("Turns all police vehicles into monster trucks.")
		.addHotkey()
		.addTranslation());

	addOption(ButtonOption("Super cars turn to buffalos")
		.addFunction([] {
		for (String m : super) {
			ModelSwapping::ModelSwap(m, "buffalo");
		}
	})
		.addTooltip("Turns all super cars into buffalos.")
		.addHotkey()
		.addTranslation());

	addOption(ButtonOption("Planes turn to titans")
		.addFunction([] {
		for (String m : planes) {
			ModelSwapping::ModelSwap(m, "titan");
		}
	})
		.addTooltip("All planes become titans.")
		.addHotkey()
		.addTranslation());

	addOption(ButtonOption("Planes turn to cargoplanes")
		.addFunction([] {
		for (String m : planes) {
			ModelSwapping::ModelSwap(m, "cargoplane");
		}
	})
		.addTooltip("All planes become cargoplanes.")
		.addHotkey()
		.addTranslation());

	addOption(ButtonOption("Vans turn to insurgents.")
		.addFunction([] {
		for (String m : van) {
			ModelSwapping::ModelSwap(m, "insurgent");
		}
	})
		.addTooltip("All vans become insurgents.")
		.addHotkey()
		.addTranslation());*/
}

/*Update once when submenu is opened*/
void SwapPresetsMenu::UpdateOnce() {}

/*Update while submenu is active*/
void SwapPresetsMenu::Update() {}

/*Background update*/
void SwapPresetsMenu::FeatureUpdate() {}

/*Singleton*/
SwapPresetsMenu* _instance;
SwapPresetsMenu* SwapPresetsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new SwapPresetsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
SwapPresetsMenu::~SwapPresetsMenu() { delete _instance; }