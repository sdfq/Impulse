#include "stdafx.h"
#include "sessionVehicle.h"
#include "../allPlayersMenu.h"
#include "../playerList/player/playerVehicleMenu.h"

using namespace SessionVehicleMenuVars;

namespace SessionVehicleMenuVars {
	Vars vars;
}

void SessionVehicleMenu::Init() {
	setParentSubmenu<AllPlayersMenu>();
	setName("Vehicle", true, true);

	addOption(ButtonOption("Godmode vehicle")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { PlayerVehicleMenuVars::GodmodeVehicle(player); }); })
		.addTooltip("Godmode vehicle").addTranslation());

	addOption(ButtonOption("Kick from vehicle")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { PlayerVehicleMenuVars::KickFromVehicle(player, false); }); })
		.addTooltip("Kick player from vehicle").addTranslation());

	addOption(BreakOption("Movement Modifications").addTranslation());

	addOption(ToggleOption("Horn boost")
		.addToggle(vars.hornBoost)
		.addTooltip("Horn boost").addTranslation());

	addOption(ButtonOption("Launch vehicle")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { PlayerVehicleMenuVars::LaunchVehicle(player); }); })
		.addTooltip("Launch vehicle").addTranslation());

	addOption(ButtonOption("Launch vehicle")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { PlayerVehicleMenuVars::SlingShotVehicle(player); }); })
		.addTooltip("Launch vehicle").addTranslation());

	addOption(ButtonOption("Boost vehicle")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { PlayerVehicleMenuVars::BoostVehicle(player); }); })
		.addTooltip("Boost vehicle").addTranslation());

	addOption(ButtonOption("Stop vehicle")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { PlayerVehicleMenuVars::StopVehicle(player); }); })
		.addTooltip("Stop vehicle").addTranslation());

	addOption(ToggleOption("Freeze vehicle")
		.addToggle(vars.freeze)
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { PlayerVehicleMenuVars::FreezeVehicle(player, vars.freeze); }); })
		.addTooltip("Freeze vehicle").addTranslation());

	addOption(ButtonOption("Rotate vehicle")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { PlayerVehicleMenuVars::RotateVehicle(player); }); })
		.addTooltip("Rotate vehicle").addTranslation());

	addOption(BreakOption("Trolling").addTranslation());

	addOption(ButtonOption("Kill engine")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { PlayerVehicleMenuVars::SetVehicleEngineHealth(player, -3700); }); })
		.addTooltip("Kill engine").addTranslation());

	addOption(ButtonOption("Revive engine")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { PlayerVehicleMenuVars::SetVehicleEngineHealth(player, 1000); }); })
		.addTooltip("Revive engine").addTranslation());

	addOption(ToggleOption("Kick from vehicle loop")
		.addToggle(vars.kickLoop)
		.addTooltip("Kick from vehicle loop").addTranslation());

	addOption(ButtonOption("Delete vehicle")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { PlayerVehicleMenuVars::DeleteVehicle(player); }); })
		.addTooltip("Delete vehicle").addTranslation());

	addOption(ButtonOption("Burst tires")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { PlayerVehicleMenuVars::BurstTires(player); }); })
		.addTooltip("Burst tires").addTranslation());

	addOption(ButtonOption("Lock doors")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { PlayerVehicleMenuVars::LockDoors(player, true); }); })
		.addTooltip("Lock doors").addTranslation());

	addOption(ButtonOption("Unlock doors")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { PlayerVehicleMenuVars::LockDoors(player, false); }); })
		.addTooltip("Unlock  doors").addTranslation());

	addOption(BreakOption("Vehicle Modifications").addTranslation());

	addOption(ButtonOption("Repair vehicle")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { PlayerVehicleMenuVars::FixVehicle(player); }); })
		.addTooltip("Repair vehicle").addTranslation());

	addOption(ButtonOption("Fully tune vehicle")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { PlayerVehicleMenuVars::TuneVehicle(player); }); })
		.addTooltip("Fully tune vehicle").addTranslation());
}

/*Update once when submenu is opened*/
void SessionVehicleMenu::UpdateOnce() {}

/*Update while submenu is active*/
void SessionVehicleMenu::Update() {}

/*Background update*/
void SessionVehicleMenu::FeatureUpdate() {
	OnlinePlayerCallback(true, [](SPlayer player) { if (vars.hornBoost) PlayerVehicleMenuVars::HornBoost(player); });
	OnlinePlayerCallback(true, [](SPlayer player) { if (vars.kickLoop) PlayerVehicleMenuVars::KickFromVehicle(player, true); });
	OnlinePlayerCallback(true, [](SPlayer player) { if (vars.freeze) PlayerVehicleMenuVars::FreezeVehicle(player, true); });
}

/*Singleton*/
SessionVehicleMenu* _instance;
SessionVehicleMenu* SessionVehicleMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new SessionVehicleMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
SessionVehicleMenu::~SessionVehicleMenu() { delete _instance; }