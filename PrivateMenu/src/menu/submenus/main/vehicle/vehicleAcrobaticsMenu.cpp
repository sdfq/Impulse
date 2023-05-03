#include "stdafx.h"
#include "vehicleAcrobaticsMenu.h"
#include "../vehicleMenu.h"

using namespace VehicleAcrobaticsMenuVars;

namespace VehicleAcrobaticsMenuVars {
}

void VehicleAcrobaticsMenu::Init() {
	setParentSubmenu<VehicleMenu>();
	setName("Vehicle acrobatics", true, true);

	addOption(ButtonOption("Front flip").addTranslation()
		.addFunction([] {if (GetLocalPlayer().m_isInVehicle) ENTITY::ApplyForceToEntity(GetLocalPlayer().m_vehicle, true, 0.0f, 0.0f, 20.0f, 0.0f, -2.0f, 0.0f, true, true, true, true, false, true); })
		.addHotkey().addTooltip("Do a front flip"));

	addOption(ButtonOption("Back flip").addTranslation()
		.addFunction([] {if (GetLocalPlayer().m_isInVehicle) ENTITY::ApplyForceToEntity(GetLocalPlayer().m_vehicle, true, 0.0f, 0.0f, 20.0f, 0.0f, 6.0f, 0.0f, true, true, true, true, false, true); })
		.addHotkey().addTooltip("Do a back flip"));

	addOption(ButtonOption("Kick flip").addTranslation()
		.addFunction([] {if (GetLocalPlayer().m_isInVehicle) ENTITY::ApplyForceToEntity(GetLocalPlayer().m_vehicle, 1, 0.0, 0.0, 10.71, 5.0, 0.0, 0.0, 1, false, true, true, true, true); })
		.addHotkey().addTooltip("Do a kick flip"));

	addOption(ButtonOption("Heel flip").addTranslation()
		.addFunction([] {if (GetLocalPlayer().m_isInVehicle) ENTITY::ApplyForceToEntity(GetLocalPlayer().m_vehicle, true, 0.0f, 0.0f, 20.0f, -2.0f, 0.0f, 0.0f, true, true, true, true, false, true); })
		.addHotkey().addTooltip("Do a heel flip"));

	addOption(ButtonOption("Bunny hop").addTranslation()
		.addFunction([] {if (GetLocalPlayer().m_isInVehicle) ENTITY::ApplyForceToEntity(GetLocalPlayer().m_vehicle, true, 0.0f, 0.0f, 6.0f, 0.0f, 0.0f, 0.0f, true, false, true, true, true, true); })
		.addHotkey().addTooltip("Do a bunny hop"));

	addOption(ButtonOption("Slingshot").addTranslation()
		.addFunction([] {if (GetLocalPlayer().m_isInVehicle) ENTITY::ApplyForceToEntity(GetLocalPlayer().m_vehicle, 1, 0, 0, 150, 4, 2, 0, true, true, true, true, false, true); })
		.addHotkey().addTooltip("Fling your vehicle"));
}

/*Update once when submenu is opened*/
void VehicleAcrobaticsMenu::UpdateOnce() {}

/*Update while submenu is active*/
void VehicleAcrobaticsMenu::Update() {}

/*Background update*/
void VehicleAcrobaticsMenu::FeatureUpdate() {}

/*Singleton*/
VehicleAcrobaticsMenu* _instance;
VehicleAcrobaticsMenu* VehicleAcrobaticsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new VehicleAcrobaticsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
VehicleAcrobaticsMenu::~VehicleAcrobaticsMenu() { delete _instance; }