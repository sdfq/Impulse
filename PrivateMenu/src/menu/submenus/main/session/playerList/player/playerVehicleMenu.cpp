#include "stdafx.h"
#include "playerVehicleMenu.h"
#include "../playerMenu.h"
#include "../../../vehicle/LSCMenu.h"
#include "../../../vehicleMenu.h"

using namespace PlayerVehicleMenuVars;

namespace PlayerVehicleMenuVars {

	void HornBoost(SPlayer& player) {
		if (!player.m_isInVehicle) return;
		if (PLAYER::IsPlayerPressingHorn(player.m_id)) {
			GetEntityControl()->SimpleRequestControl(player.m_vehicle);
			VEHICLE::SetVehicleForwardSpeed(player.m_vehicle, 500);
		}
	}

	void SetVehicleEngineHealth(SPlayer& player, int health) {
		if (!player.m_isInVehicle) return;
		GetEntityControl()->RequestControl("[VEH]", player.m_vehicle, [health](Entity vehicle) {VEHICLE::SetVehicleEngineHealth(vehicle, health); });
	}

	void KickFromVehicle(SPlayer& player, bool loop) {
		if (!player.m_isInVehicle) return;
		if (loop) {
			static int TIMER;
			Utils::DoTimedFunction(&TIMER, 500, [&] { BRAIN::ClearPedTasksImmediately(player.m_ped); });
		} else BRAIN::ClearPedTasksImmediately(player.m_ped);
	}

	void RotateVehicle(SPlayer& player) {
		if (!player.m_isInVehicle) return;
		GetEntityControl()->RequestControl("[ROTV]", player.m_vehicle, [](Entity vehicle) {
			Vector3 rot = ENTITY::GetEntityRotation(vehicle, 0);
			ENTITY::SetEntityRotation(vehicle, rot.x + 180, rot.y, rot.z, 2, true);
		});
	}

	void DeleteVehicle(SPlayer& player) {
		if (!player.m_isInVehicle) return;
		GetEntityControl()->DeleteVehicle(player.m_vehicle);
	}

	void FixVehicle(SPlayer& player) {
		if (!player.m_isInVehicle) return;
		GetEntityControl()->RequestControl("[FV]", player.m_vehicle, [](Entity vehicle) {VEHICLE::SetVehicleFixed(vehicle); });
	}

	void TuneVehicle(SPlayer& player) {
		if (!player.m_isInVehicle) return;
		GetEntityControl()->RequestControl("[TV]", player.m_vehicle, [](Entity vehicle) {LSCMenuVars::MaxVehicle(vehicle); });
	}

	void LaunchVehicle(SPlayer& player) {
		if (!player.m_isInVehicle) return;
		GetEntityControl()->RequestControl("[LV]", player.m_vehicle, [](Entity vehicle) {Utils::ApplyForceToEntity(vehicle, 0, 0, 20); });
	}

	void SlingShotVehicle(SPlayer& player) {
		if (!player.m_isInVehicle) return;
		GetEntityControl()->RequestControl("[LV]", player.m_vehicle, [](Entity vehicle) {
			ENTITY::ApplyForceToEntity(vehicle, 1, 0, 0, 150, 4, 2, 0, true, true, true, true, false, true);
			//ENTITY::ApplyForceToEntityCenterOfMass(vehicle, 1, 0.f, 100.f, 100.f, TRUE, TRUE, TRUE, TRUE);
		});
	}

	void BurstTires(SPlayer& player) {
		if (!player.m_isInVehicle) return;
		GetEntityControl()->RequestControl("[BT]", player.m_vehicle, [](Entity vehicle) {
			VEHICLE::SetVehicleTyresCanBurst(vehicle, true);
			for (int tireID = 0; tireID < 8; tireID++) {
				VEHICLE::SetVehicleTyreBurst(vehicle, tireID, true, 1000.0);
			}
		});
	}

	void BoostVehicle(SPlayer& player) {
		if (!player.m_isInVehicle) return;
		GetEntityControl()->RequestControl("[BV]", player.m_vehicle, [](Entity vehicle) {VEHICLE::SetVehicleForwardSpeed(vehicle, 100); });
	}

	void StopVehicle(SPlayer& player) {
		if (!player.m_isInVehicle) return;
		GetEntityControl()->RequestControl("[SV]", player.m_vehicle, [](Entity vehicle) {VEHICLE::SetVehicleForwardSpeed(vehicle, 0); });
	}

	void GodmodeVehicle(SPlayer& player) {
		if (!player.m_isInVehicle) return;
		GetEntityControl()->RequestControl("[GV]", player.m_vehicle, [](Entity vehicle) {
			VehicleMenuVars::VehicleGodmode(vehicle, true);
		});
	}

	void FreezeVehicle(SPlayer& player, bool toggle) {
		if (!player.m_isInVehicle) return;
		GetEntityControl()->RequestControl("[FV]", player.m_vehicle, [&](Entity vehicle) {
			ENTITY::FreezeEntityPosition(vehicle, toggle);
		});
	}

	void LockDoors(SPlayer& player, bool lock) {
		if (!player.m_isInVehicle) return;
		GetEntityControl()->RequestControl("[LD]", player.m_vehicle, [=](Entity vehicle) {VEHICLE::SetVehicleDoorsLocked(player.m_vehicle, lock ? 4 : 1); });
	}
}

void PlayerVehicleMenu::Init() {
	setParentSubmenu<PlayerMenu>();
	setName("Player vehicle", true, false);

	addOption(ButtonOption("Godmode vehicle")
		.addFunction([] {GodmodeVehicle(GetSelectedPlayer()); })
		.addTooltip("Godmode vehicle").addTranslation());

	addOption(ButtonOption("Kick from vehicle")
		.addFunction([] {KickFromVehicle(GetSelectedPlayer(), false); })
		.addTooltip("Kick player from vehicle").addTranslation());

	addOption(BreakOption("Movement Modifications").addTranslation());

	addOption(ToggleOption("Horn boost")
		.addToggle(GetSelectedPlayer().m_hornBoost)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_hornBoost); })
		.addTooltip("Horn boost").addTranslation());

	addOption(ButtonOption("Launch vehicle")
		.addFunction([] {LaunchVehicle(GetSelectedPlayer()); })
		.addTooltip("Launch vehicle").addTranslation());

	addOption(ButtonOption("Slingshot vehicle")
		.addFunction([] {SlingShotVehicle(GetSelectedPlayer()); })
		.addTooltip("Slingshot vehicle").addTranslation());

	addOption(ButtonOption("Boost vehicle")
		.addFunction([] {BoostVehicle(GetSelectedPlayer()); })
		.addTooltip("Boost vehicle").addTranslation());

	addOption(ButtonOption("Stop vehicle")
		.addFunction([] {StopVehicle(GetSelectedPlayer()); })
		.addTooltip("Stop vehicle").addTranslation());

	addOption(ToggleOption("Freeze vehicle")
		.addToggle(GetSelectedPlayer().m_freezeVehicle)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_freezeVehicle); })
		.addFunction([] {FreezeVehicle(GetSelectedPlayer(), GetSelectedPlayer().m_freezeVehicle); })
		.addTooltip("Freeze vehicle").addTranslation());

	addOption(ButtonOption("Rotate vehicle")
		.addFunction([] {RotateVehicle(GetSelectedPlayer()); })
		.addTooltip("Rotate vehicle").addTranslation());

	addOption(BreakOption("Trolling").addTranslation());

	addOption(ButtonOption("Kill engine")
		.addFunction([] { SetVehicleEngineHealth(GetSelectedPlayer(), -3700); })
		.addTooltip("Kill engine").addTranslation());

	addOption(ButtonOption("Revive engine")
		.addFunction([] { SetVehicleEngineHealth(GetSelectedPlayer(), 1000); })
		.addTooltip("Revive engine").addTranslation());

	addOption(ToggleOption("Kick from vehicle loop")
		.addToggle(GetSelectedPlayer().m_kickLoop)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_kickLoop); })
		.addTooltip("Kick from vehicle loop").addTranslation());

	addOption(ButtonOption("Delete vehicle")
		.addFunction([] {DeleteVehicle(GetSelectedPlayer()); })
		.addTooltip("Delete vehicle").addTranslation());

	addOption(ButtonOption("Burst tires")
		.addFunction([] {BurstTires(GetSelectedPlayer()); })
		.addTooltip("Burst tires").addTranslation());

	addOption(ButtonOption("Lock doors")
		.addFunction([] {LockDoors(GetSelectedPlayer(), true); })
		.addTooltip("Lock doors").addTranslation());

	addOption(ButtonOption("Unlock doors")
		.addFunction([] {LockDoors(GetSelectedPlayer(), false); })
		.addTooltip("Unlock  doors").addTranslation());

	addOption(BreakOption("Vehicle Modifications").addTranslation());

	addOption(ButtonOption("Repair vehicle")
		.addFunction([] {FixVehicle(GetSelectedPlayer()); })
		.addTooltip("Repair vehicle").addTranslation());

	addOption(ButtonOption("Fully tune vehicle")
		.addFunction([] {TuneVehicle(GetSelectedPlayer()); })
		.addTooltip("Fully tune vehicle").addTranslation());

	addOption(BreakOption("Vehicle Acrobatics").addTranslation());

	addOption(ButtonOption("Front flip").addTranslation()
		.addFunction([] {if (GetSelectedPlayer().m_isInVehicle)
			GetEntityControl()->SimpleRequestControl(GetSelectedPlayer().m_vehicle);
			ENTITY::ApplyForceToEntity(GetSelectedPlayer().m_vehicle, true, 0.0f, 0.0f, 20.0f, 0.0f, -2.0f, 0.0f, true, true, true, true, false, true); })
		.addHotkey().addTooltip("Do a front flip"));

	addOption(ButtonOption("Back flip").addTranslation()
		.addFunction([] {if (GetSelectedPlayer().m_isInVehicle)
			GetEntityControl()->SimpleRequestControl(GetSelectedPlayer().m_vehicle);
			ENTITY::ApplyForceToEntity(GetSelectedPlayer().m_vehicle, true, 0.0f, 0.0f, 20.0f, 0.0f, 6.0f, 0.0f, true, true, true, true, false, true); })
		.addHotkey().addTooltip("Do a back flip"));

	addOption(ButtonOption("Kick flip").addTranslation()
		.addFunction([] {if (GetSelectedPlayer().m_isInVehicle)
			GetEntityControl()->SimpleRequestControl(GetSelectedPlayer().m_vehicle);
			ENTITY::ApplyForceToEntity(GetSelectedPlayer().m_vehicle, 1, 0.0, 0.0, 10.71, 5.0, 0.0, 0.0, 1, false, true, true, true, true); })
		.addHotkey().addTooltip("Do a kick flip"));

	addOption(ButtonOption("Heel flip").addTranslation()
		.addFunction([] {if (GetSelectedPlayer().m_isInVehicle)
			GetEntityControl()->SimpleRequestControl(GetSelectedPlayer().m_vehicle);
			ENTITY::ApplyForceToEntity(GetSelectedPlayer().m_vehicle, true, 0.0f, 0.0f, 20.0f, -2.0f, 0.0f, 0.0f, true, true, true, true, false, true); })
		.addHotkey().addTooltip("Do a heel flip"));

	addOption(ButtonOption("Bunny hop").addTranslation()
		.addFunction([] {if (GetSelectedPlayer().m_isInVehicle)
			GetEntityControl()->SimpleRequestControl(GetSelectedPlayer().m_vehicle);
			ENTITY::ApplyForceToEntity(GetSelectedPlayer().m_vehicle, true, 0.0f, 0.0f, 6.0f, 0.0f, 0.0f, 0.0f, true, false, true, true, true, true); })
		.addHotkey().addTooltip("Do a bunny hop"));

	addOption(ButtonOption("Slingshot").addTranslation()
		.addFunction([] {if (GetSelectedPlayer().m_isInVehicle)
			GetEntityControl()->SimpleRequestControl(GetSelectedPlayer().m_vehicle);
			ENTITY::ApplyForceToEntity(GetSelectedPlayer().m_vehicle, 1, 0, 0, 150, 4, 2, 0, true, true, true, true, false, true); })
		.addHotkey().addTooltip("Fling your vehicle"));
}

/*Update once when submenu is opened*/
void PlayerVehicleMenu::UpdateOnce() {}

/*Update while submenu is active*/
void PlayerVehicleMenu::Update() {}

/*Background update*/
void PlayerVehicleMenu::FeatureUpdate() {
	OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_hornBoost) HornBoost(player); });
	OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_kickLoop) KickFromVehicle(player, true); });
	OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_freezeVehicle) FreezeVehicle(player, true); });
}

/*Singleton*/
PlayerVehicleMenu* _instance;
PlayerVehicleMenu* PlayerVehicleMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new PlayerVehicleMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
PlayerVehicleMenu::~PlayerVehicleMenu() { delete _instance; }