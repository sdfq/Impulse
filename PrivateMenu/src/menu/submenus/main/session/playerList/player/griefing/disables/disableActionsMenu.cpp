#include "stdafx.h"
#include "menu/submenus/main/session/playerList/player/griefingMenu.h"
#include "disableActionsMenu.h"

using namespace DisableActionsVars;

namespace DisableActionsVars {
	Vars var;
}

void DisableActionsMenu::Init() {
	setParentSubmenu<GriefingMenu>();
	setName("Disable Actions", true, true);

	addOption(ToggleOption("Disable vehicles")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(var.DisableVehicle)
		.addTooltip("Block the user from entering vehicles.")
		.addTranslation());

	addOption(ToggleOption("Disable interiors")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(var.DisableInteriors)
		.addTooltip("Block the user from entering map interiors (not apartments).")
		.addTranslation());

	addOption(ToggleOption("Disable weapons")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(var.DisableWeapons)
		.addTooltip("Block the user from using weapons at all.")
		.addTranslation());

}

/*Update once when submenu is opened*/
void DisableActionsMenu::UpdateOnce() {}

/*Update while submenu is active*/
void DisableActionsMenu::Update() {}

/*Background update*/
void DisableActionsMenu::FeatureUpdate() {
	static int TIMER;
	static bool update = true;
	Utils::DoTimedFunction(&TIMER, 50, [] {update = true; });
	if (update) {
		if (var.DisableInteriors) {
			int Interior = INTERIOR::GetInteriorFromEntity(GetSelectedPlayer().m_ped);
			if (INTERIOR::IsValidInterior(Interior)) {
				FIRE::AddExplosion(GetSelectedPlayer().m_coordinates.x, GetSelectedPlayer().m_coordinates.y, GetSelectedPlayer().m_coordinates.z, 29, 1, false, true, 1, false);
			}
		}
		if (var.DisableVehicle) {
			if (PED::GetVehiclePedIsIn(GetSelectedPlayer().m_ped, false) != NULL) {
				BRAIN::ClearPedTasksImmediately(GetSelectedPlayer().m_ped);
			}
		}
		if (var.DisableWeapons) {
			Hash removeMe = 0x0000;
			if (WEAPON::GetCurrentPedWeapon(GetSelectedPlayer().m_ped, &removeMe, true)) {
				WEAPON::RemoveWeaponFromPed(GetSelectedPlayer().m_ped, removeMe);
			}
		}
		update = false;
	}
}

/*Singleton*/
DisableActionsMenu* _instance;
DisableActionsMenu* DisableActionsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new DisableActionsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
DisableActionsMenu::~DisableActionsMenu() { delete _instance; }