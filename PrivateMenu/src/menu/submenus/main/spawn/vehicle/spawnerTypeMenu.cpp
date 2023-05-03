#include "stdafx.h"
#include "spawnerTypeMenu.h"
#include "../spawnVehicleMenu.h"
#include "spawnVehicleSettingsMenu.h"

using namespace SpawnerTypeMenuVars;

namespace SpawnerTypeMenuVars { }

void SpawnerTypeMenu::Init() {
	for (int i = 0; i < m_vehicleAmount; i++) {
		addOption(ButtonOption(HUD::_GetLabelText(VEHICLE::GetDisplayNameFromVehicleModel(Utils::GetHashKey(m_vehicles[i]))))
			.addCurrentOp([=] { GetWindowManager()->m_vehicleInfo.setName(HUD::_GetLabelText(VEHICLE::GetDisplayNameFromVehicleModel(Utils::GetHashKey(m_vehicles[i])))); GetWindowManager()->m_vehicleInfoComp.setModel(Utils::GetHashKey(m_vehicles[i])); })
			.addFunction([=] { GetFiberPool()->DoJob([=] {SpawnVehicleMenuVars::SpawnVehicle(m_vehicles[i]); }); })
			.addTooltip(m_vehicles[i])
			.addTooltip((string(va("Vehicle model name: ")) + m_vehicles[i]).c_str())
			/*.addHotkey()*/);
	}
}

void SpawnerTypeMenu::Update() {}

SpawnerTypeMenu* SpawnerTypeMenu::GetInstance() {
	return SpawnVehicleMenuVars::GetVehicleSub();
}