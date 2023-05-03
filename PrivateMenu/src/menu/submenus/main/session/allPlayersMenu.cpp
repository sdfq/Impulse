#include "stdafx.h"
#include "allPlayersMenu.h"
#include "../sessionMenu.h"
#include "playerList/player/griefingMenu.h"
#include "allPlayers/excludesMenu.h"
#include "allPlayers/sessionModifications.h"
#include "allPlayers/sessionTeleportMenu.h"
#include "allPlayers/sessionPeacefulMenu.h"
#include "allPlayers/sessionTalking.h"
#include "allPlayers/sessionESP.h"
#include "allPlayers/sessionRemote.h"
#include "allPlayers/sessionVehicle.h"
#include "allPlayers/spawn/sessionSpawnVehicleMenu.h"
#include "allPlayers/sessionGriefing.h"
#include "allPlayers/sessionDisablesMenu.h"

using namespace AllPlayersMenuVars;

namespace AllPlayersMenuVars {
	Vars vars;
}

void AllPlayersMenu::Init() {
	setParentSubmenu<SessionMenu>();
	setName("All players", true, true);

	addOption(SubmenuOption("Excludes")
		.addSubmenu<ExcludesMenu>()
		.addTranslation().addHotkey()
		.addTooltip("Exclude certain players from session options"));

	addOption(SubmenuOption("Modifications")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addSubmenu<SessionModificationsMenu>()
		.addTranslation().addHotkey()
		.addTooltip("Session modification options"));

	addOption(SubmenuOption("Teleport")
		.addSubmenu<SessionTeleportMenu>()
		.addTooltip("Teleport options")
		.addTranslation().addHotkey());

	addOption(SubmenuOption("Peaceful")
		.addSubmenu<SessionPeacefulMenu>()
		.addTooltip("Peaceful options")
		.addTranslation().addHotkey());

	addOption(SubmenuOption("Griefing")
		.addSubmenu<SessionGriefingMenu>()
		.addTooltip("Griefing options")
		.addTranslation().addHotkey());

	addOption(SubmenuOption("Talking")
		.addSubmenu<SessionTalkingMenu>()
		.addTooltip("Talking options")
		.addTranslation().addHotkey());

	addOption(SubmenuOption("Remote")
		.addSubmenu<SessionRemoteMenu>()
		.addTooltip("Remote options")
		.addTranslation().addHotkey());

	addOption(SubmenuOption("Vehicle")
		.addSubmenu<SessionVehicleMenu>()
		.addTooltip("Vehicle options")
		.addTranslation().addHotkey());

	addOption(SubmenuOption("Spawn vehicle")
		.addSubmenu<SessionSpawnVehicleMenu>()
		.addTooltip("Spawn vehicle options")
		.addTranslation().addHotkey());

	addOption(SubmenuOption("Extra sensory perception")
		.addSubmenu<SessionESPMenu>()
		.addTooltip("ESP options")
		.addTranslation().addHotkey());

	addOption(ToggleOption("Chat commands")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.chat)
		.addTooltip("Enable chat commands for session")
		.addTranslation().addHotkey());

	addOption(ButtonOption("Add lobby to session overseer")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { 
		json j;
		if (GetConfig()->DoesFileExist(GetConfig()->GetBlacklistPath())) {
			fstream file(GetConfig()->GetBlacklistPath());
			j = json::parse(file);
			file.open(GetConfig()->GetBlacklistPath(), ofstream::out | ofstream::trunc); /*Clear the file*/
			file.close();
		}
		CPed* ped = (CPed*)(PoolManager::GetEntityAddress(player.m_ped));
		if (ped != 0) {
			string rid = to_string(ped->PlayerInfo->RockstarID);
			if (Utils::DoesItExistInBlacklist(_atoi64(rid.c_str()), "", true)) return;
			string pname = player.m_name;
			j.push_back({ rid, 0, 0, 1, 0, 0, 0, pname }); // last 1, we are adding a rid
		}
		ofstream file2(GetConfig()->GetBlacklistPath());
		file2 << setw(4) << j;
		file2.close();
	}); })
		.addTooltip("This will add all players in your session to the session overseer (RID + Name)")
		.addTranslation().addHotkey());

	addOption(BreakOption());

	addOption(ButtonOption("Crash session with entities")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { GriefingMenuVars::CrashPlayer(player); }); })
		.addTooltip("Crashes the session using entities (please stay far away from any players when using)")
		.addTranslation().addHotkey());

	addOption(ButtonOption("Crash session without entities")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addFunction([] {
		Natives::fSetLobbyWeather(-1, -1, -1, 0);
	})
		.addTranslation().addHotkey()
		.addTooltip("Crashes the session without using entities"));

}

/*Update once when submenu is opened*/
void AllPlayersMenu::UpdateOnce() {}

/*Update while submenu is active*/
void AllPlayersMenu::Update() {}

/*Background update*/
void AllPlayersMenu::FeatureUpdate() {
	
}

/*Singleton*/
AllPlayersMenu* _instance;
AllPlayersMenu* AllPlayersMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new AllPlayersMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
AllPlayersMenu::~AllPlayersMenu() { delete _instance; }