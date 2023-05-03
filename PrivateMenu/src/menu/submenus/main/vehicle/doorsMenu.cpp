#include "stdafx.h"
#include "doorsMenu.h"
#include "../vehicleMenu.h"

using namespace DoorsMenuVars;

namespace DoorsMenuVars {
	Vars vars;
}

void DoorsMenu::Init() {
	setParentSubmenu<VehicleMenu>();
	setName("Vehicle doors", true, true);

	addOption(NumberOption<int>(SCROLL, "Open door").addTranslation().addHotkey()
		.addNumber(vars.openDoor, "%d", 1).addMin(0).addMax(5)
		.addFunction([] { if(GetLocalPlayer().m_isInVehicle) VEHICLE::SetVehicleDoorOpen(GetLocalPlayer().m_vehicle, vars.openDoor, false, false); })
		.addTooltip("Open door"));

	addOption(NumberOption<int>(SCROLL, "Close door").addTranslation().addHotkey()
		.addNumber(vars.closeDoor, "%d", 1).addMin(0).addMax(5)
		.addFunction([] { if (GetLocalPlayer().m_isInVehicle) VEHICLE::SetVehicleDoorShut(GetLocalPlayer().m_vehicle, vars.closeDoor, false); })
		.addTooltip("Close door"));

	addOption(NumberOption<int>(SCROLL, "Delete door").addTranslation().addHotkey()
		.addNumber(vars.deleteDoor, "%d", 1).addMin(0).addMax(5)
		.addFunction([] { if (GetLocalPlayer().m_isInVehicle) VEHICLE::SetVehicleDoorBroken(GetLocalPlayer().m_vehicle, vars.deleteDoor, true); })
		.addTooltip("Delete door"));

	addOption(ButtonOption("Lock doors").addTranslation().addHotkey()
		.addFunction([] { if (GetLocalPlayer().m_isInVehicle) VEHICLE::SetVehicleDoorsLocked(GetLocalPlayer().m_vehicle, 4); })
		.addTooltip("Lock doors"));

	addOption(ButtonOption("Unlock doors").addTranslation().addHotkey()
		.addFunction([] { if (GetLocalPlayer().m_isInVehicle) VEHICLE::SetVehicleDoorsLocked(GetLocalPlayer().m_vehicle, 0); })
		.addTooltip("Unlock doors"));
}

/*Update once when submenu is opened*/
void DoorsMenu::UpdateOnce() {}

/*Update while submenu is active*/
void DoorsMenu::Update() {}

/*Background update*/
void DoorsMenu::FeatureUpdate() {}

/*Singleton*/
DoorsMenu* _instance;
DoorsMenu* DoorsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new DoorsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
DoorsMenu::~DoorsMenu() { delete _instance; }