#include "stdafx.h"
#include "vehiclePerformanceMenu.h"
#include "../LSCMenu.h"

using namespace VehiclePerformanceMenuVars;

namespace VehiclePerformanceMenuVars {
	Vars vars;

	ScrollStruct<int> armor[] = {
		TranslationString("None", true), 0,
		TranslationString("Armor Upgrade 20%", true), 1,
		TranslationString("Armor Upgrade 40%", true), 2,
		TranslationString("Armor Upgrade 60%", true), 3,
		TranslationString("Armor Upgrade 80%", true), 4,
		TranslationString("Armor Upgrade 100%", true), 5
	}, engineCustomisation[] = {
		TranslationString("Stock", true), 0,
		TranslationString("EMS Upgrade, Level 1", true), 1,
		TranslationString("EMS Upgrade, Level 2", true), 2,
		TranslationString("EMS Upgrade, Level 3", true), 3,
		TranslationString("EMS Upgrade, Level 4", true), 4
	}, brakes[]{
		TranslationString("Stock brakes", true), 0,
		TranslationString("Street brakes", true), 1,
		TranslationString("Sport brakes", true), 2,
		TranslationString("Race brakes", true), 3
	}, transmission[] = {
		TranslationString("Stock transmission", true), 0,
		TranslationString("Street transmission", true), 1,
		TranslationString("Sport transmission", true), 2,
		TranslationString("Race transmission", true), 3
	}, suspension[] = {
		TranslationString("Stock suspension", true), -1,
		TranslationString("Lowered suspension", true), 0,
		TranslationString("Street suspension", true), 1,
		TranslationString("Sport suspension", true), 2,
		TranslationString("Competition suspension", true), 3
	};

	void MaxVehiclePerformance(Vehicle veh) {
		GetEntityControl()->RequestControl("[MVP]", veh, [](Entity veh) {
			VEHICLE::SetVehicleModKit(veh, 0);
			VEHICLE::SetVehicleMod(veh, 11, VEHICLE::GetNumVehicleMods(veh, 11) - 1, false);
			VEHICLE::SetVehicleMod(veh, 12, VEHICLE::GetNumVehicleMods(veh, 12) - 1, false);
			VEHICLE::SetVehicleMod(veh, 13, VEHICLE::GetNumVehicleMods(veh, 13) - 1, false);
			VEHICLE::SetVehicleMod(veh, 15, VEHICLE::GetNumVehicleMods(veh, 15) - 1, false);
			VEHICLE::SetVehicleMod(veh, 16, VEHICLE::GetNumVehicleMods(veh, 16) - 1, false);
			VEHICLE::ToggleVehicleMod(veh, 18, 1);
		});
	}
}

void VehiclePerformanceMenu::Init() {
	setParentSubmenu<LSCMenu>();
	setName("Performance", true, true);

	addOption(ButtonOption("Fully tune performance")
		.addFunction([] {MaxVehiclePerformance(GetLocalPlayer().m_vehicle); })
		.addHotkey().addTranslation()
		.addTooltip("Max vehicle performance"));

	addOption(ToggleOption("Turbo")
		.addToggle(vars.turbo)
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addOnUpdate([] {vars.turbo = VEHICLE::IsToggleModOn(GetLocalPlayer().m_vehicle, MOD_TURBO); })
		.addFunction([] {VEHICLE::ToggleVehicleMod(GetLocalPlayer().m_vehicle, MOD_TURBO, vars.turbo); })
		.addTooltip("Turbo").addTranslation());

	addOption(ScrollOption<int>(SCROLL, "Engine")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addScroll(vars.engineIndex, 0, NUMOF(engineCustomisation) - 1, engineCustomisation)
		.addOnUpdate([] {vars.engineIndex = VEHICLE::GetVehicleMod(GetLocalPlayer().m_vehicle, MOD_ENGINE) + 1; })
		.addFunction([] { VEHICLE::SetVehicleMod(GetLocalPlayer().m_vehicle, MOD_ENGINE, vars.engineIndex - 1, 0); })
		.addTooltip("Engine").addTranslation());

	addOption(ScrollOption<int>(SCROLL, "Brakes")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addScroll(vars.breaksIndex, 0, NUMOF(brakes) - 1, brakes)
		.addOnUpdate([] {	vars.breaksIndex = VEHICLE::GetVehicleMod(GetLocalPlayer().m_vehicle, MOD_BRAKES) + 1; })
		.addFunction([] { VEHICLE::SetVehicleMod(GetLocalPlayer().m_vehicle, MOD_BRAKES, vars.breaksIndex - 1, 0); })
		.addTooltip("Brakes").addTranslation());

	addOption(ScrollOption<int>(SCROLL, "Transmission")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addScroll(vars.transmissionIndex, 0, NUMOF(transmission) - 1, transmission)
		.addOnUpdate([] {vars.transmissionIndex = VEHICLE::GetVehicleMod(GetLocalPlayer().m_vehicle, MOD_TRANSMISSION) + 1; })
		.addFunction([] { VEHICLE::SetVehicleMod(GetLocalPlayer().m_vehicle, MOD_TRANSMISSION, vars.transmissionIndex - 1, 0); })
		.addTooltip("Transmission").addTranslation());

	addOption(ScrollOption<int>(SCROLL, "Suspension")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addScroll(vars.suspensionIndex, 0, NUMOF(suspension) - 1, suspension)
		.addOnUpdate([] {vars.suspensionIndex = VEHICLE::GetVehicleMod(GetLocalPlayer().m_vehicle, MOD_SUSPENSION) + 1; })
		.addFunction([] { VEHICLE::SetVehicleMod(GetLocalPlayer().m_vehicle, MOD_SUSPENSION, vars.suspensionIndex - 1, 0); })
		.addTooltip("Suspension").addTranslation());

	addOption(ScrollOption<int>(SCROLL, "Armor")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addScroll(vars.armorIndex, 0, NUMOF(armor) - 1, armor)
		.addOnUpdate([] {vars.armorIndex = VEHICLE::GetVehicleMod(GetLocalPlayer().m_vehicle, MOD_ARMOR) + 1; })
		.addFunction([] { VEHICLE::SetVehicleMod(GetLocalPlayer().m_vehicle, MOD_ARMOR, vars.armorIndex - 1, 0); })
		.addTooltip("Armor").addTranslation());
}

/*Update once when submenu is opened*/
void VehiclePerformanceMenu::UpdateOnce() {}

/*Update while submenu is active*/
void VehiclePerformanceMenu::Update() {
	if (!GetLocalPlayer().m_isInVehicle) GetSubmenuHandler()->SetSubPrevious();

	VEHICLE::SetVehicleModKit(GetLocalPlayer().m_vehicle, 0);
}

/*Background update*/
void VehiclePerformanceMenu::FeatureUpdate() {}

/*Singleton*/
VehiclePerformanceMenu* _instance;
VehiclePerformanceMenu* VehiclePerformanceMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new VehiclePerformanceMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
VehiclePerformanceMenu::~VehiclePerformanceMenu() { delete _instance; }