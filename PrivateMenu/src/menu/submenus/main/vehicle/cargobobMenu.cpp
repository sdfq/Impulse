#include "stdafx.h"
#include "cargobobMenu.h"
#include "../vehicleMenu.h"
#include "../spawn/spawnVehicleMenu.h"
#include "../spawn/vehicle/spawnVehicleSettingsMenu.h"

using namespace CargobobMenuVars;

namespace CargobobMenuVars {

	bool IsInCargobob() {
		return GetLocalPlayer().m_isInVehicle && ENTITY::GetEntityModel(GetLocalPlayer().m_vehicle) == Utils::GetHashKey("CARGOBOB");
	}
}

void CargobobMenu::Init() {
	setParentSubmenu<VehicleMenu>();
	setName("Cargobob", true, true);

	addOption(ButtonOption("Spawn cargobob")
		.addRequirement([] {return !IsInCargobob(); })
		.addFunction([] { 
			bool cache = SpawnVehicleSettingsMenuVars::vars.spawnin; 
			SpawnVehicleSettingsMenuVars::vars.spawnin = true; 
			SpawnVehicleMenuVars::SpawnVehicle("CARGOBOB");
			SpawnVehicleSettingsMenuVars::vars.spawnin = cache;
		})
		.addTooltip("Spawn a cargobob").addTranslation());

	addOption(ButtonOption("Spawn magnet")
		.addRequirement([] {return IsInCargobob(); })
		.addFunction([] { VEHICLE::CreatePickUpRopeForCargobob(GetLocalPlayer().m_vehicle, 1); })
		.addTooltip("Spawn magnet").addTranslation());

	addOption(ButtonOption("Remove magnet")
		.addRequirement([] {return IsInCargobob(); })
		.addFunction([] { VEHICLE::RemovePickUpRopeForCargobob(GetLocalPlayer().m_vehicle); })
		.addTooltip("Remove magnet").addTranslation());
}

/*Update once when submenu is opened*/
void CargobobMenu::UpdateOnce() {}

/*Update while submenu is active*/
void CargobobMenu::Update() {}

/*Background update*/
void CargobobMenu::FeatureUpdate() {}

/*Singleton*/
CargobobMenu* _instance;
CargobobMenu* CargobobMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new CargobobMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
CargobobMenu::~CargobobMenu() { delete _instance; }