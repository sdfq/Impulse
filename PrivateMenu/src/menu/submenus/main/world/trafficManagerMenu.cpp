#include "stdafx.h"
#include "trafficManagerMenu.h"
#include "../worldMenu.h"
#include "../vehicle/LSCMenu.h"

using namespace TrafficManagerMenuVars;

namespace TrafficManagerMenuVars {
	Vars vars;
	vector<Vehicle> nearbyVehicles;

	void UpdateNearbyVehicles() {
		static set<Vehicle> lastSeenVehicles;
		nearbyVehicles.clear();
		const int numElements = 20;
		const int arrSize = numElements * 2 + 2;

		Vehicle *vehicles = new Ped[arrSize];
		vehicles[0] = numElements;
		int found = PED::GetPedNearbyVehicles(GetLocalPlayer().m_ped, vehicles);

		for (int i = 0; i < found; i++) {
			int offsettedID = i * 2 + 2;

			if (!ENTITY::DoesEntityExist(vehicles[offsettedID])) continue;

			Vehicle xveh = vehicles[offsettedID];

			bool inSet = lastSeenVehicles.find(xveh) != lastSeenVehicles.end();
			if (!inSet) {
				lastSeenVehicles.insert(xveh);
			}
		}

		for (std::set<Ped>::iterator it = lastSeenVehicles.begin(); it != lastSeenVehicles.end();) {
			if (!ENTITY::DoesEntityExist(*it)) {
				lastSeenVehicles.erase(it++);
			} else {
				nearbyVehicles.push_back(*it);
				++it;
			}
		}

		delete vehicles;

	}

	void RunTrafficManagerWorker(PoolActions task, int player) {
		vector<Vehicle> poolVehicles;
		if (vars.usepools) {
			VehiclePool::Update();
			poolVehicles = VehiclePool::GetVehicles();
		} else UpdateNearbyVehicles();

		for (Vehicle& veh : vars.usepools ? poolVehicles : nearbyVehicles) {
			if (veh == GetLocalPlayer().m_vehicle || !ENTITY::DoesEntityExist(veh)) continue;
			GetEntityControl()->SimpleRequestControl(veh);
			Vector3 VehicleCoords = ENTITY::GetEntityCoords(veh, 0);
			switch (task) {
				case VEHICLE_ESP: GetRenderer()->DrawLine(GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, GetLocalPlayer().m_coordinates.z, VehicleCoords.x, VehicleCoords.y, VehicleCoords.z, { 255, 0, 0, 255 }); break;
				case VEHICLE_CHAOS: AUDIO::_SoundVehicleHornThisFrame(veh); if (AUDIO::IsHornActive(veh)) VEHICLE::SetVehicleForwardSpeed(veh, 100.f); break;
				case VEHICLE_EXPLODE: NETWORK::NetworkExplodeVehicle(veh, 1, 0, 0); break;
				case VEHICLE_KILLDRIVER: VEHICLE::SetVehicleOutOfControl(veh, 1, 0); break;
				case VEHICLE_LAUNCH: Utils::ApplyForceToEntity(veh, 0, 0, 20); break;
				case VEHICLE_BOOST: VEHICLE::SetVehicleForwardSpeed(veh, 100); break;
				case VEHICLE_KICKFLIP: ENTITY::ApplyForceToEntity(veh, true, 0.0f, 0.0f, 10.71f, 5.0f, 0.0f, 0.0f, true, false, true, true, true, true); break;
				case VEHICLE_DELETE: GetEntityControl()->SimpleDeleteVehicle(veh); break;
				case VEHICLE_PUSH: ENTITY::ApplyForceToEntity(veh, 3, VehicleCoords.x - GetLocalPlayer().m_coordinates.x, VehicleCoords.y - GetLocalPlayer().m_coordinates.y, VehicleCoords.z - GetLocalPlayer().m_coordinates.z, 0, 0, 0, false, false, true, true, false, true); break;
				case VEHICLE_FULLYTUNE: LSCMenuVars::MaxVehicle(veh); break;
				case VEHICLE_RANDOMPAINTJOB: if (NETWORK::NetworkHasControlOfEntity(veh))LSCMenuVars::RandomizeVehicle(veh); break;
				case VEHICLE_FIX: 	VEHICLE::SetVehicleFixed(veh); break;
				case VEHICLE_SCORCH: ENTITY::SetEntityRenderScorched(veh, true); break;
				case VEHICLE_COMETOME: 	if (ENTITY::DoesEntityExist(VEHICLE::GetPedInVehicleSeat(veh, -1, 1))) BRAIN::TaskVehicleDriveToCoord(VEHICLE::GetPedInVehicleSeat(veh, -1, 1), veh, GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, GetLocalPlayer().m_coordinates.z, 100, 1, ENTITY::GetEntityModel(veh), 16777216, 4, -1); break; //Hello
				case VEHICLE_NEGATIVEGRAVITY: VEHICLE::SetVehicleGravity(veh, false); break;
				case VEHICLE_NORMALGRAVITY: VEHICLE::SetVehicleGravity(veh, true); break;
				case VEHICLE_HOSTILETRAFFIC: {
					Ped ped = VEHICLE::GetPedInVehicleSeat(veh, -1, 1);
					if (ENTITY::DoesEntityExist(ped)) {
						SPlayer& pl = GetPlayer(player);
						BRAIN::TaskVehicleDriveToCoord(ped, veh, pl.m_coordinates.x, pl.m_coordinates.y, pl.m_coordinates.z, 100, 1, ENTITY::GetEntityModel(veh), 16777216, 4, -1);
					}
					break;
				}
			}
		}
	}
}

void TrafficManagerMenu::Init() {
	setParentSubmenu<WorldMenu>();
	setName("Traffic manager", true, true);

	addOption(ToggleOption("Use vehicle pools (bigger range)")
		.addToggle(vars.usepools)
		.addHotkey().addTranslation()
		.addTooltip("Use entity pools to extend the range of these options"));

	addOption(ToggleOption("Vehicle ESP")
		.addToggle(vars.esp)
		.addHotkey().addTranslation()
		.addTooltip("Extra sensory perception"));

	addOption(ToggleOption("Vehicle chaos")
		.addToggle(vars.chaos)
		.addHotkey().addTranslation()
		.addTooltip("Chaos"));

	addOption(ButtonOption("Explode vehicles")
		.addFunction([] {RunTrafficManagerWorker(VEHICLE_EXPLODE); })
		.addHotkey().addTranslation()
		.addTooltip("Explode vehicles"));

	addOption(ButtonOption("Kill driver")
		.addFunction([] {RunTrafficManagerWorker(VEHICLE_KILLDRIVER); })
		.addHotkey().addTranslation()
		.addTooltip("Kill driver"));

	addOption(ButtonOption("Launch vehicles")
		.addFunction([] {RunTrafficManagerWorker(VEHICLE_LAUNCH); })
		.addHotkey().addTranslation()
		.addTooltip("Launch vehicles"));

	addOption(ButtonOption("Boost vehicles")
		.addFunction([] {RunTrafficManagerWorker(VEHICLE_BOOST); })
		.addHotkey().addTranslation()
		.addTooltip("Boost vehicles"));

	addOption(ButtonOption("Kickflip vehicles")
		.addFunction([] {RunTrafficManagerWorker(VEHICLE_KICKFLIP); })
		.addHotkey().addTranslation()
		.addTooltip("Kickflip vehicles"));

	addOption(ButtonOption("Delete vehicles")
		.addFunction([] {RunTrafficManagerWorker(VEHICLE_DELETE); })
		.addHotkey().addTranslation()
		.addTooltip("Delete vehicles"));


	//Causes crash when there are too many vehicles

	//addOption(ButtonOption("Fully tune vehicles")
	//	.addFunction([] {RunTrafficManagerWorker(VEHICLE_FULLYTUNE); })
	//	.addHotkey()
	//	.addTooltip("Fully tune vehicles"));


	//Causes crash when there are too many vehicles

	//addOption(ButtonOption("Randomize vehicles")
	//	.addFunction([] {RunTrafficManagerWorker(VEHICLE_RANDOMPAINTJOB); })
	//	.addHotkey()
	//	.addTooltip("Randomize vehicles"));

	addOption(ButtonOption("Fix vehicles")
		.addFunction([] {RunTrafficManagerWorker(VEHICLE_FIX); })
		.addHotkey().addTranslation()
		.addTooltip("Fix vehicles"));

	addOption(ButtonOption("Scorch vehicles")
		.addFunction([] {RunTrafficManagerWorker(VEHICLE_SCORCH); })
		.addHotkey().addTranslation()
		.addTooltip("Scorch vehicles"));

	addOption(ButtonOption("Drive vehicles to me")
		.addFunction([] {RunTrafficManagerWorker(VEHICLE_COMETOME); })
		.addHotkey().addTranslation()
		.addTooltip("Drive vehicles to me"));

	addOption(ButtonOption("No gravity")
		.addFunction([] {RunTrafficManagerWorker(VEHICLE_NEGATIVEGRAVITY); })
		.addHotkey().addTranslation()
		.addTooltip("No gravity"));

	addOption(ButtonOption("Normal gravity")
		.addFunction([] {RunTrafficManagerWorker(VEHICLE_NORMALGRAVITY); })
		.addHotkey().addTranslation()
		.addTooltip("Normal gravity"));
}

/*Update once when submenu is opened*/
void TrafficManagerMenu::UpdateOnce() {}

/*Update while submenu is active*/
void TrafficManagerMenu::Update() {}

/*Background update*/
void TrafficManagerMenu::FeatureUpdate() {
	if (vars.esp) RunTrafficManagerWorker(VEHICLE_ESP);
	if (vars.chaos) RunTrafficManagerWorker(VEHICLE_CHAOS);
}

/*Singleton*/
TrafficManagerMenu* _instance;
TrafficManagerMenu* TrafficManagerMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new TrafficManagerMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
TrafficManagerMenu::~TrafficManagerMenu() { delete _instance; }