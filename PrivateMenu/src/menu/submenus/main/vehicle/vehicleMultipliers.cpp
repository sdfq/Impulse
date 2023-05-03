#include "stdafx.h"
#include "vehicleMultipliers.h"
#include "../vehicleMenu.h"

using namespace VehicleMultipliersMenuVars;

namespace VehicleMultipliersMenuVars {
	Vars vars;
}

void VehicleMultipliersMenu::Init() {
	setParentSubmenu<VehicleMenu>();
	setName("Vehicle multipliers", true, true);

	addOption(NumberOption<int>(SCROLL, "RPM")
		.addNumber(vars.rpm, "%d", 1).addMin(0).addMax(10000).setScrollSpeed(10)
		.addFunction([] { if (GetLocalPlayer().m_isInVehicle) VEHICLE::_SetVehicleEnginePowerMultiplier(GetLocalPlayer().m_vehicle, vars.rpm + 1); })
		.addTooltip("Set the RPM").addTranslation().addHotkey());

	addOption(NumberOption<int>(SCROLL, "Light")
		.addNumber(vars.light, "%d", 1).addMin(0).addMax(10000).setScrollSpeed(10)
		.addFunction([] { if(GetLocalPlayer().m_isInVehicle) VEHICLE::SetVehicleLightMultiplier(GetLocalPlayer().m_vehicle, vars.light); })
		.addTooltip("Set the light intensity").addTranslation().addHotkey());

	addOption(NumberOption<int>(SCROLL, "Torque")
		.addNumber(vars.torque, "%d", 1).addMin(0).addMax(10000).setScrollSpeed(10)
		.addTooltip("Set the torque").addTranslation().addHotkey());

	addOption(NumberOption<float>(TOGGLE, "Acceleration")
		.addNumber(vars.accelerationVal, "%.2f", 0.01f).addMin(0.0f).addMax(10.0f).setScrollSpeed(10)
		.addToggle(vars.acceleration).addTranslation().addHotkey()
		.addTooltip("Acceleration"));

	addOption(NumberOption<float>(TOGGLE, "Brake")
		.addToggle(vars.brake)
		.addNumber(vars.brakeVal, "%.2f", 0.01f).addMin(0.0f).addMax(10.0f).setScrollSpeed(10)
		.addTranslation().addHotkey()
		.addTooltip("Brake"));

	addOption(NumberOption<float>(TOGGLE, "Suspension")
		.addToggle(vars.suspension)
		.addNumber(vars.suspensionVal, "%.2f", 0.01f).addMin(0.0f).addMax(10.0f).setScrollSpeed(10)
		.addTranslation().addHotkey()
		.addTooltip("Suspension"));
}

/*Update once when submenu is opened*/
void VehicleMultipliersMenu::UpdateOnce() {}

/*Update while submenu is active*/
void VehicleMultipliersMenu::Update() {}

/*Background update*/
void VehicleMultipliersMenu::FeatureUpdate() {
	if (GetLocalPlayer().m_isInVehicle) {
		if(vars.torque != 0) VEHICLE::_SetVehicleEngineTorqueMultiplier(GetLocalPlayer().m_vehicle, vars.torque + 1);

		if (vars.acceleration) {
			if (KeyDown(0x57) || PAD::IsDisabledControlPressed(0, 208)) {
				if (VEHICLE::IsVehicleOnAllWheels(GetLocalPlayer().m_vehicle)) {
					ENTITY::ApplyForceToEntity(GetLocalPlayer().m_vehicle, true, 0, vars.accelerationVal / 10, 0, 0, 0, 0, true, true, true, true, false, true);
				}
			}
		}

		if (vars.brake) {
			if (KeyDown(0x53) || PAD::IsDisabledControlPressed(0, 207)) {
				if (VEHICLE::IsVehicleOnAllWheels(GetLocalPlayer().m_vehicle)) {
					ENTITY::ApplyForceToEntity(GetLocalPlayer().m_vehicle, true, 0, ((vars.brakeVal / 10)* -1), 0, 0, 0, 0, true, true, true, true, false, true);
				}
			}
		}

		if (vars.suspension) {
			ENTITY::ApplyForceToEntity(GetLocalPlayer().m_vehicle, true, 0, 0, vars.suspensionVal / 10, 0, 0, 0, true, true, true, true, false, true);
		}
	}
}

/*Singleton*/
VehicleMultipliersMenu* _instance;
VehicleMultipliersMenu* VehicleMultipliersMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new VehicleMultipliersMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
VehicleMultipliersMenu::~VehicleMultipliersMenu() { delete _instance; }