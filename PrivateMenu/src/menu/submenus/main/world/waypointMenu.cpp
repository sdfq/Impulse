#include "stdafx.h"
#include "waypointMenu.h"
#include "../teleportMenu.h"
#include "../worldMenu.h"

using namespace WaypointMenuVars;

namespace WaypointMenuVars {
	Vars vars;

	void Explode() {
		static int TIMER;
		if (HUD::IsWaypointActive()) {
			Utils::DoTimedFunction(&TIMER, 250, [] {
				Vector3 coords = TeleportMenuVars::GetTeleportCoordsFixedHeight();
				if (coords.z != 1000.0f)
					FIRE::AddExplosion(coords.x, coords.y, coords.z, 0, 5, 1, 0, 0, 0);
			});
		}
	}

	void MoneyDrop() {
		static int TIMER;
		if (HUD::IsWaypointActive()) {
			Utils::DoTimedFunction(&TIMER, 500, [] {
				GetEntityControl()->SimpleRequestModel(-1666779307);
				Vector3 SpawnLocation = TeleportMenuVars::GetTeleportCoordsFixedHeight();
				if (SpawnLocation.z != 1000.0f) {
					SpawnLocation.x += MISC::GetRandomFloatInRange(0, 10.0f);
					SpawnLocation.y += MISC::GetRandomFloatInRange(0, 10.0f);
					SpawnLocation.z += MISC::GetRandomFloatInRange(5.0f, 10.0f);
					OBJECT::CreateMoneyPickups(SpawnLocation.x, SpawnLocation.y, SpawnLocation.z, 0x1E9A99F8, 2500, -1666779307);
				}
			});
		}
	}

	void SendPoliceToWaypoint() {
		if (HUD::IsWaypointActive()) {
			Hash vehicleHash = Utils::GetHashKey("POLICE3");
			GetEntityControl()->SimpleRequestModel(vehicleHash);
			Vector3 pos = ENTITY::GetOffsetFromEntityInWorldCoords(GetLocalPlayer().m_ped, 0.0, 5.0, 0);
			Vehicle	veh = VEHICLE::CreateVehicle(vehicleHash, pos.x, pos.y, pos.z, ENTITY::GetEntityHeading(GetLocalPlayer().m_ped), true, false, true);
			if (veh) {
				Hash driverHash = Utils::GetHashKey("s_m_y_marine_01");
				GetEntityControl()->SimpleRequestModel(driverHash);
				Ped driver = PED::CreateRandomPedAsDriver(veh, false);
				DECORATOR::DecorSetInt(veh, "MPBitset", 0);
				VEHICLE::SetVehicleIsStolen(veh, false);
				VEHICLE::SetVehicleSiren(veh, 1);
				PED::SetPedIntoVehicle(driver, veh, -1);

				Vector3 waypoint = TeleportMenuVars::GetWaypointCoords();
				BRAIN::TaskVehicleDriveToCoord(driver, veh, waypoint.x, waypoint.y, waypoint.z, 40, 1, vehicleHash, 7, 6, -1);
			}
		}
	}

	void DriveToWaypoint() {
		if (HUD::IsWaypointActive()) {
			vars.drivingtowaypoint = true;
			Vector3 waypoint = TeleportMenuVars::GetWaypointCoords();
			if (GetLocalPlayer().m_isInVehicle) {
				BRAIN::TaskVehicleDriveToCoord(GetLocalPlayer().m_ped, GetLocalPlayer().m_vehicle, waypoint.x, waypoint.y, waypoint.z, 40, 1, ENTITY::GetEntityModel(GetLocalPlayer().m_vehicle), 7, 6, -1);
			}
			else GetRenderer()->NotifyBottom("You need to be in a vehicle");
		}
		else GetRenderer()->NotifyBottom("You need to have a waypoint");
	}

	void StopAutoDrive() {
		vars.drivingtowaypoint = false;
		if (GetLocalPlayer().m_isInVehicle) {
			Vehicle veh = GetLocalPlayer().m_vehicle;
			BRAIN::ClearPedTasksImmediately(GetLocalPlayer().m_ped);
			PED::SetPedIntoVehicle(GetLocalPlayer().m_ped, veh, -1);
		}
	}

	void CheckAutoDrive() {
		const int MINDIST = 50;
		if (HUD::IsWaypointActive()) {
			Vector3 waypoint = TeleportMenuVars::GetWaypointCoords();
			if (waypoint.Distance(GetLocalPlayer().m_coordinates) < MINDIST) {
				StopAutoDrive();
			}
		}
		else {
			StopAutoDrive();
		}
	}
}

void WaypointMenu::Init() {
	setParentSubmenu<WorldMenu>();
	setName("Waypoint", true, true);

	addOption(ToggleOption("Explode")
		.addToggle(vars.explode)
		.addHotkey().addTranslation()
		.addTooltip("Explode at waypoint"));

	addOption(ToggleOption("Money drop")
		.addToggle(vars.moneydrop)
		.addHotkey().addTranslation()
		.addTooltip("Money drop at waypoint"));

	addOption(ButtonOption("Send police")
		.addFunction([] {SendPoliceToWaypoint(); })
		.addHotkey().addTranslation()
		.addTooltip("Send police to waypoint"));

	addOption(ButtonOption("Auto drive to waypoint")
		.addFunction([] {DriveToWaypoint(); })
		.addHotkey().addTranslation()
		.addTooltip("Automatically drive to waypoint"));

	addOption(ButtonOption("Stop auto drive")
		.addFunction([] {StopAutoDrive(); })
		.addHotkey().addTranslation()
		.addTooltip("Stop autodrive"));
}

/*Update once when submenu is opened*/
void WaypointMenu::UpdateOnce() {}

/*Update while submenu is active*/
void WaypointMenu::Update() {}

/*Background update*/
void WaypointMenu::FeatureUpdate() {
	if (vars.explode)Explode();
	if (vars.moneydrop)MoneyDrop();
	if (vars.drivingtowaypoint) CheckAutoDrive();
}

/*Singleton*/
WaypointMenu* _instance;
WaypointMenu* WaypointMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new WaypointMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
WaypointMenu::~WaypointMenu() { delete _instance; }