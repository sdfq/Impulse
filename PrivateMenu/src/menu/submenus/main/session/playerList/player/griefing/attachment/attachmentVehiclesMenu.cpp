#include "stdafx.h"
#include "attachmentVehiclesMenu.h"
#include "../attachmentMenu.h"
#include "../../../../../weapon/weaponShootEntities.h"

using namespace AttachmentVehiclesMenuVars;

namespace AttachmentVehiclesMenuVars {
	Vars vars;
}

void AttachmentVehiclesMenu::Init() {
	setParentSubmenu<AttachmentMenu>();
	setName("Vehicles", true, false);

	for (int i = 0; i < NUMOF(WeaponShootEntitiesMenuVars::vehiclePairs) - 1; i++) {
		addOption(ButtonOption(WeaponShootEntitiesMenuVars::vehiclePairs[i].m_name.Get())
			.addFunction([=] { AttachmentMenuVars::AttachVehicleToPlayer(GetSelectedPlayer(), WeaponShootEntitiesMenuVars::vehiclePairs[i].m_result); })
			.addTooltip("Attach this vehicle to this player"));
	}
}

/*Update once when submenu is opened*/
void AttachmentVehiclesMenu::UpdateOnce() {}

/*Update while submenu is active*/
void AttachmentVehiclesMenu::Update() {}

/*Background update*/
void AttachmentVehiclesMenu::FeatureUpdate() {}

/*Singleton*/
AttachmentVehiclesMenu* _instance;
AttachmentVehiclesMenu* AttachmentVehiclesMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new AttachmentVehiclesMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
AttachmentVehiclesMenu::~AttachmentVehiclesMenu() { delete _instance; }