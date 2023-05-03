#include "stdafx.h"
#include "playerSpawnerTypeMenu.h"
#include "playerSpawnVehicleMenu.h"
#include "../../../../spawn/spawnVehicleMenu.h"

using namespace PlayerSpawnerTypeMenuVars;
using namespace PlayerSpawnVehicleMenuVars;

namespace PlayerSpawnerTypeMenuVars {}

void PlayerSpawnerTypeMenu::Init() {
	setParentSubmenu<PlayerSpawnVehicleMenu>();
	
	for (int i = 0; i < m_vehicleAmount; i++) {
		//addOption(ButtonOption(HUD::_GetLabelText(VEHICLE::GetDisplayNameFromVehicleModel(Utils::GetHashKey(m_vehicles[i]))))
		addOption(ButtonOption((string(va("Selected Player: ")) + HUD::_GetLabelText(VEHICLE::GetDisplayNameFromVehicleModel(Utils::GetHashKey(m_vehicles[i])))).c_str())
			.addCurrentOp([=] { GetWindowManager()->m_vehicleInfo.setName(HUD::_GetLabelText(VEHICLE::GetDisplayNameFromVehicleModel(Utils::GetHashKey(m_vehicles[i])))); GetWindowManager()->m_vehicleInfoComp.setModel(Utils::GetHashKey(m_vehicles[i])); })
			.addFunction([=] { GetFiberPool()->DoJob([=] {SpawnVehicleMenuVars::SpawnVehiclePlayer(Utils::GetHashKey(m_vehicles[i]), GetSelectedPlayer().m_id, PlayerSpawnVehicleMenuVars::vars.spawnInvincible); }); })
			.addTooltip((string(va("Vehicle model name: ")) + m_vehicles[i]).c_str())//.addTooltip(m_vehicles[i])
			);
	}
}

void PlayerSpawnerTypeMenu::Update() {}

PlayerSpawnerTypeMenu* PlayerSpawnerTypeMenu::GetInstance() {
	return PlayerSpawnVehicleMenuVars::GetVehicleSub();
}