#include "stdafx.h"
#include "sessionSpawnerTypeMenu.h"
#include "sessionSpawnVehicleMenu.h"
#include "../../../spawn/spawnVehicleMenu.h"

using namespace SessionSpawnerTypeMenuVars;
using namespace SessionSpawnVehicleMenuVars;

namespace SessionSpawnerTypeMenuVars {}

void SessionSpawnerTypeMenu::Init() {
	setParentSubmenu<SessionSpawnVehicleMenu>();

	for (int i = 0; i < m_vehicleAmount; i++) {
		//addOption(ButtonOption(HUD::_GetLabelText(VEHICLE::GetDisplayNameFromVehicleModel(Utils::GetHashKey(m_vehicles[i]))))
			addOption(ButtonOption((string(va("Session: ")) + HUD::_GetLabelText(VEHICLE::GetDisplayNameFromVehicleModel(Utils::GetHashKey(m_vehicles[i])))).c_str())
			.addCurrentOp([=] { GetWindowManager()->m_vehicleInfo.setName(HUD::_GetLabelText(VEHICLE::GetDisplayNameFromVehicleModel(Utils::GetHashKey(m_vehicles[i])))); GetWindowManager()->m_vehicleInfoComp.setModel(Utils::GetHashKey(m_vehicles[i])); })
			.addFunction([=] { GetFiberPool()->DoJob([=] { OnlinePlayerCallback(false, [=](SPlayer player) { SpawnVehicleMenuVars::SpawnVehiclePlayer(Utils::GetHashKey(m_vehicles[i]), player.m_id, 0); }); }); })
			.addTooltip((string(va("Vehicle model name: ")) + m_vehicles[i]).c_str())//.addTooltip(m_vehicles[i])
			/*.addHotkey()*/);
	}
}

void SessionSpawnerTypeMenu::Update() {}

SessionSpawnerTypeMenu* SessionSpawnerTypeMenu::GetInstance() {
	return SessionSpawnVehicleMenuVars::GetVehicleSub();
}