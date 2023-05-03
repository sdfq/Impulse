#include "stdafx.h"
#include "miscTrainOptions.h"
#include "../miscMenu.h"

using namespace MiscTrainOptionsMenuVars;

static Vehicle trainHandle;

namespace MiscTrainOptionsMenuVars {
	Vars vars;

	void TrainKeyboard() {

		if (KeyDown(0x57)) {
			float TrainSpeed = ENTITY::GetEntitySpeed(trainHandle);
			TrainSpeed += 20.0f;
			VEHICLE::SetTrainCruiseSpeed(trainHandle, TrainSpeed);
			VEHICLE::SetTrainSpeed(trainHandle, TrainSpeed);
		}

		if (KeyDown(0x53)) {
			float TrainSpeed = ENTITY::GetEntitySpeed(trainHandle);
			TrainSpeed -= 20.0f;
			VEHICLE::SetTrainCruiseSpeed(trainHandle, TrainSpeed);
			VEHICLE::SetTrainSpeed(trainHandle, TrainSpeed);
		}

		if (KeyDown(0x20)) {
			VEHICLE::SetTrainCruiseSpeed(trainHandle, 0);
			VEHICLE::SetTrainSpeed(trainHandle, 0);
		}

	}


}

void MiscTrainOptions::Init() {
	setParentSubmenu<MiscMenu>();
	setName("Train Options", true, true);

	addOption(ButtonOption("Drive Nearest Train")
		.addFunction([] {
		const int ElementAmount = 10;
		const int ArrSize = ElementAmount * 2 + 2;

		Vehicle *vehs = new Vehicle[ArrSize];
		vehs[0] = ElementAmount;
		int VehFound = PED::GetPedNearbyVehicles(GetLocalPlayer().m_ped, vehs);

		for (int i = 0; i < VehFound; i++) {
			int offsettedID = i * 2 + 2;
			if (vehs[offsettedID] != NULL && ENTITY::DoesEntityExist(vehs[offsettedID])) {
				if (VEHICLE::IsThisModelATrain(ENTITY::GetEntityModel(vehs[offsettedID]))) {
					trainHandle = vehs[offsettedID];
					PED::SetPedIntoVehicle(GetLocalPlayer().m_ped, trainHandle, -1);
					//Notify(cprintf("Found Train", trainHandle)).Send(NotifySuccess);
					if (PED::GetVehiclePedIsIn(GetLocalPlayer().m_ped, 0) == trainHandle)
					break;
				}
			}
		}
	})
		.addTooltip("Drive the nearest train to your ped (be near a train)")
		.addTranslation().addHotkey());

	addOption(ButtonOption("Spawn Train")
		.addFunction([] {
		STREAMING::RequestModel(0x3D6AAA9B);
		STREAMING::RequestModel(0x0AFD22A6);
		STREAMING::RequestModel(0x264D9262);
		STREAMING::RequestModel(0x36DCFF98);
		STREAMING::RequestModel(0x0E512E79);
		STREAMING::RequestModel(0xD1ABB666);
		if (STREAMING::HasModelLoaded(0x3D6AAA9B) &&
			STREAMING::HasModelLoaded(0x0AFD22A6) &&
			STREAMING::HasModelLoaded(0x264D9262) &&
			STREAMING::HasModelLoaded(0x36DCFF98) &&
			STREAMING::HasModelLoaded(0x0E512E79) &&
			STREAMING::HasModelLoaded(0xD1ABB666)) {
			trainHandle = VEHICLE::CreateMissionTrain(15, GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, GetLocalPlayer().m_coordinates.z, true);
			PED::SetPedIntoVehicle(GetLocalPlayer().m_ped, trainHandle, -1);
		}
	}).addTranslation().addHotkey()
		.addTooltip("Be near a train track when spawning this (Sometimes needs to be pressed twice)"));

	addOption(ButtonOption("Quit Train Ride")
		.addFunction([] {
		BRAIN::ClearPedTasksImmediately(GetLocalPlayer().m_ped);
		trainHandle = 0;
	}).addTranslation().addHotkey()
		.addTooltip("Exit the train without getting rid of it"));

	addOption(ButtonOption("Delete Spawned Train")
		.addFunction([] {
		VEHICLE::DeleteMissionTrain(&trainHandle);
	}).addTranslation().addHotkey()
		.addTooltip("Delete the spawned train"));


	//if (ENTITY::DoesEntityExist(trainHandle)) {

		addOption(ToggleOption("Keyboard Controls")
			.addToggle(vars.trainkeyboard).addTranslation().addHotkey()
			.addFunction([] { GetRenderer()->NotifyMap("Keyboard Controls:\nW = Increase Speed\nS = Lower Speed\nSpace = Insta Stop"); })
			.addTooltip("This allows keyboard controls to move the train back and fourth"));

		addOption(ButtonOption("Chrome Train")
			.addFunction([] { 
			VEHICLE::SetVehicleColours(trainHandle, 120, 120);
			for (int i = 0; i < 25; i++) {
				Vehicle carriage = VEHICLE::GetTrainCarriage(trainHandle, i);
				if (ENTITY::DoesEntityExist(carriage)) {
					VEHICLE::SetVehicleColours(carriage, 120, 120);
				}
			}
			}).addTranslation().addHotkey()
			.addTooltip("Chrome the current train carriage"));

		addOption(ButtonOption("Derail Train")
			.addFunction([] { 
			VEHICLE::SetVehicleUndriveable(trainHandle, true);
			VEHICLE::SetVehicleEngineHealth(trainHandle, 0);
			VEHICLE::SetVehiclePetrolTankHealth(trainHandle, 0);
			Vector3 TrainLocation = ENTITY::GetEntityCoords(trainHandle, false);
			FIRE::AddExplosion(TrainLocation.x, TrainLocation.y, TrainLocation.z, 29, 9999, true, false, false, 1);
			VEHICLE::SetRenderTrainAsDerailed(trainHandle, true);
			ENTITY::SetEntityRenderScorched(trainHandle, true);
			VEHICLE::SetTrainCruiseSpeed(trainHandle, 0);
			VEHICLE::SetTrainSpeed(trainHandle, 0);
			VEHICLE::SetMissionTrainCoords(trainHandle, TrainLocation.x, TrainLocation.y, TrainLocation.z + 1);
			}).addTranslation().addHotkey()
			.addTooltip("Detail your current train from the tracks (still moveable)"));

		addOption(ButtonOption("Speed Up Train")
			.addFunction([] { 
			float TrainSpeed = ENTITY::GetEntitySpeed(trainHandle);
			TrainSpeed += 20.0f;
			VEHICLE::SetTrainCruiseSpeed(trainHandle, TrainSpeed);
			VEHICLE::SetTrainSpeed(trainHandle, TrainSpeed);
			}).addTranslation().addHotkey()
			.addTooltip("Manually speed up the train"));

		addOption(ButtonOption("Slow Down Train")
			.addFunction([] { 
			float TrainSpeed = ENTITY::GetEntitySpeed(trainHandle);
			TrainSpeed -= 20.0f;
			VEHICLE::SetTrainCruiseSpeed(trainHandle, TrainSpeed);
			VEHICLE::SetTrainSpeed(trainHandle, TrainSpeed);
			}).addTranslation().addHotkey()
			.addTooltip("Manually slow down the train"));
	//}
}

/*Update once when submenu is opened*/
void MiscTrainOptions::UpdateOnce() {}

/*Update while submenu is active*/
void MiscTrainOptions::Update() {}

/*Background update*/
void MiscTrainOptions::FeatureUpdate() {
	if (vars.trainkeyboard) TrainKeyboard();


}

/*Singleton*/
MiscTrainOptions* _instance;
MiscTrainOptions* MiscTrainOptions::GetInstance() {
	if (_instance == nullptr) {
		_instance = new MiscTrainOptions();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
MiscTrainOptions::~MiscTrainOptions() { delete _instance; }