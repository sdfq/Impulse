#include "stdafx.h"
#include "menu/submenus/main/session/allPlayers/sessionGriefing.h"
#include "sessionDisablesMenu.h"

using namespace DisableActionsLobbyVars;

namespace DisableActionsLobbyVars {
	Vars var;
}

void DisableActionsLobby::Init() {
	setParentSubmenu<SessionGriefingMenu>();
	setName("Disable Actions", true, true);

	addOption(ToggleOption("Disable vehicles")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(var.DisableVehicles)
		.addTooltip("Block the lobby from entering vehicles.")
		.addTranslation());

	addOption(ToggleOption("Disable interiors")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(var.DisableInteriors)
		.addTooltip("Block the lobby from entering map interiors (not apartments).")
		.addTranslation());

	addOption(ToggleOption("Disable weapons")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(var.DisableWeapons)
		.addTooltip("Block the lobby from using weapons at all.")
		.addTranslation());
}

/*Update once when submenu is opened*/
void DisableActionsLobby::UpdateOnce() {}

/*Update while submenu is active*/
void DisableActionsLobby::Update() {}

/*Background update*/
void DisableActionsLobby::FeatureUpdate() {
	static int TIMER;
	static bool update = true;
	Utils::DoTimedFunction(&TIMER, 15, [] {update = true; });
	if (update) {
		if (var.DisableVehicles) {
			OnlinePlayerCallback(false, [](SPlayer player) {
				if (player.m_vehicle != NULL) {
					BRAIN::ClearPedTasksImmediately(player.m_ped);
				}
			});
		}
		if (var.DisableInteriors) {
			OnlinePlayerCallback(false, [](SPlayer player) {
				int Interior = INTERIOR::GetInteriorFromEntity(player.m_ped);
				if (INTERIOR::IsValidInterior(Interior)) {
					FIRE::AddExplosion(player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 29, 1, false, true, 1, false);
				}
			});
		}
		if (var.DisableWeapons) {
			OnlinePlayerCallback(false, [](SPlayer player) {
				Hash removeMe = 0x0000;
				if (WEAPON::GetCurrentPedWeapon(player.m_ped, &removeMe, true)) {
					WEAPON::RemoveWeaponFromPed(player.m_ped, removeMe);
				}
			});
		}
		update = false;
	}
}

/*Singleton*/
DisableActionsLobby* _instance;
DisableActionsLobby* DisableActionsLobby::GetInstance() {
	if (_instance == nullptr) {
		_instance = new DisableActionsLobby();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
DisableActionsLobby::~DisableActionsLobby() { delete _instance; }