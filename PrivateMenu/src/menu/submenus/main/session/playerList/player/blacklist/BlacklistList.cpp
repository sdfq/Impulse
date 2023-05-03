#include "stdafx.h"
#include "BlacklistList.h"
#include "blacklistActionsMenu.h"
#include "menu/submenus/main/session/playerList/player/blacklistPlayer.h"
#include "menu/submenus/main/sessionMenu.h"
#include "menu/submenus/main/session/playerList/player/blacklist/rockstarDevActionsMenu.h"
#include <regex>

using namespace BlacklistListVars;

namespace BlacklistListVars {
	Var vars;

	void NonHostKick(int player) {
		Natives::TriggerScriptEvent({ SCRIPTEVENTS::NONHOSTKICK1, player, 48 }, 3, player);
		Natives::TriggerScriptEvent({ SCRIPTEVENTS::NONHOSTKICK2, player }, 2, player);
		Natives::TriggerScriptEvent({ SCRIPTEVENTS::NONHOSTKICK3, player }, 2, player);
		Natives::TriggerScriptEvent({ SCRIPTEVENTS::NONHOSTKICK4, player }, 2, player);
		Natives::TriggerScriptEvent({ SCRIPTEVENTS::NONHOSTKICK5, player }, 2, player);
	}

	void KickToSingleplayer(int player) {
		//CPed* ped = (CPed*)(PoolManager::GetEntityAddress(player.m_ped));
		//FingerOfGod::sendFingerCommand(ped->PlayerInfo->RockstarID, FINGER_NETWORK_KICK);
		Natives::TriggerScriptEvent({ SCRIPTEVENTS::KICKTOSP1, player, 1 }, 3, player);
		Natives::TriggerScriptEvent({ SCRIPTEVENTS::KICKTOSP2, player }, 2, player);
		Natives::TriggerScriptEvent({ SCRIPTEVENTS::KICKTOSP3, player, 0 }, 3, player);
		Natives::TriggerScriptEvent({ SCRIPTEVENTS::NONHOSTKICK3, player, 0 }, 3, player);
		Natives::TriggerScriptEvent({ SCRIPTEVENTS::NONHOSTKICK4, player, 0 }, 3, player);
		Natives::TriggerScriptEvent({ SCRIPTEVENTS::NONHOSTKICK6, player, 0 }, 3, player);
	}

	void BlamePlayer(SPlayer& players) {
		OnlinePlayerCallback(false, [=](SPlayer player) { if (player.m_id != GetLocalPlayer().m_id) Natives::AddOwnedExplosion(players.m_ped, player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 1, 10, 1, 0, 1); });
	}

	void Explode(SPlayer& player) {
		Vector3 coords = player.m_coordinates;
		FIRE::AddExplosion(coords.x, coords.y, coords.z, 18, 0.25f, true, false, 0.5f, false);
	}

	bool IsRidOnline(const char* rid) {
		int handle[13];
		NETWORK::NetworkHandleFromUserId(rid, handle, 13);
		return NETWORK::_NetworkIsFriendOnline2(handle);
	}

	bool IsStringNumber(string str) {
		return std::regex_match(str, std::regex("[(-|+)|][0-9]+"));
	}
}

void BlacklistList::Init() {
	setParentSubmenu<SessionMenu>();
	setName("Remove or add players", true, true);

	addOption(ToggleOption("Enable overseer")
		.addToggle(vars.enableBlacklist)
		.addTooltip("Enable the current overseer settings")
		.addHotkey().canBeSaved()
		.addTranslation());

	addOption(SubmenuOption("Rockstar staff")
		.addSubmenu<RockstarDevActionsMenu>().addHotkey().addTranslation()
		.addTooltip("Choose options to do if rockstar staff are detected in your session"));

	addOption(ButtonOption("Add player name")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addFunction([this] {
		GetMenuInput()->AddToQueue([] {
			string input;
			if (GetMenuInput()->Text("Name", input, 2, 50)) {
				vars.itemID = input.c_str();
			} else return;
			if (Utils::DoesItExistInBlacklist(0, vars.itemID)) return;
			json j;
			if (GetConfig()->DoesFileExist(GetConfig()->GetBlacklistPath())) {
				fstream file(GetConfig()->GetBlacklistPath());
				j = json::parse(file);
				file.open(GetConfig()->GetBlacklistPath(), ofstream::out | ofstream::trunc); /*Clear the file*/
				file.close();
			}
			j.push_back({ vars.itemID, 0, 0, 0, 0, 0, 0, "Empty note" }); 
			ofstream file2(GetConfig()->GetBlacklistPath());
			file2 << setw(4) << j;
			file2.close();
		});
	})
	.addHotkey()
	.addTooltip("Input the name of the player to add to the overseer").addTranslation());

	addOption(ButtonOption("Add player R* ID")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addFunction([this] {
		GetMenuInput()->AddToQueue([] {
			string input;
			if (GetMenuInput()->Text("R* ID", input, 2, 50)) {
				vars.itemID = input.c_str();
			}
			else return;

			if (Utils::DoesItExistInBlacklist(_atoi64(vars.itemID))) return;
			json j;
			if (GetConfig()->DoesFileExist(GetConfig()->GetBlacklistPath())) {
				fstream file(GetConfig()->GetBlacklistPath());
				j = json::parse(file);
				file.open(GetConfig()->GetBlacklistPath(), ofstream::out | ofstream::trunc); /*Clear the file*/
				file.close();
			}
			j.push_back({ vars.itemID, 0, 0, 1, 0, 0, 0, "Empty note" });
			ofstream file2(GetConfig()->GetBlacklistPath());
			file2 << setw(4) << j;
			file2.close();
		});
	})
		.addHotkey()
		.addTooltip("Input the name of the rid to add to the overseer").addTranslation());

	addOption(ToggleOption("Show if R* ID is online")
		.addToggle(vars.showridsonline)
		.addTooltip("This will show if a rockstar id is online or offline")
		.addHotkey().canBeSaved()
		.addTranslation());
	
	/*addOption(BreakOption());

	addOption(ButtonOption("~c~Empty")
		.addRequirement([] { return GetConfig()->DoesFileExist(GetConfig()->GetBlacklistPath()); })
		.addTooltip("Not in a vehicle").addTranslation());*/
}

/*Update once when submenu is opened*/
void BlacklistList::UpdateOnce() {
	
}

/*Update while submenu is active*/
void BlacklistList::Update() {
	static int TIMER, TIMER2;
	static bool update = true, updaterid = true;
	Utils::DoTimedFunction(&TIMER, 500, [] { update = true; });
	Utils::DoTimedFunction(&TIMER2, 5000, [] { updaterid = true; });

	if (update) {
		clearOptionsOffset(5);

		fstream i(GetConfig()->GetBlacklistPath());
		json j;
		if (i) {
			j = json::parse(i);

			for (int c = 0; c < j.size(); c++) {
				bool rockstar = false; uint32_t id = 0;

				if (j[c][3] == 1) {
					rockstar = true;
					id = (uint32_t)(_atoi64(j[c][0].get<string>().c_str()));

					if (vars.ridToCheck.size() == 0) {
						vars.ridToCheck.push_back(id);
					} else {
						bool exists = false;
						for (int i = 0; i < vars.ridToCheck.size(); i++) {
							if (vars.ridToCheck[i] == id) {
								exists = true;
								break;
							}
						}

						if (!exists) {
							vars.ridToCheck.push_back(id);
						}
					}
				}

				if (rockstar && vars.showridsonline) {
					addOption(SubmenuOption((string(va("%s", vars.elMap[id] ? "~w~[~g~Online~w~] " : "~w~[~r~Offline~w~] ")) + j[c][0].get<string>() + "  [" + j[c][7].get<string>() + "]").c_str())
						.addRequirement([] { return GetAuth()->IsVIP(); })
						.addTooltip("Look into the available actions for this rockstar id.")
						.addFunction([=] {
						vars.selectedBlacklistPlayer = c;
					})
						.addSubmenu<BlacklistActionsMenu>());
				} else {
					addOption(SubmenuOption((j[c][0].get<string>() + "  [" + j[c][7].get<string>() + "]").c_str())
						.addRequirement([] { return GetAuth()->IsVIP(); })
						.addTooltip("Look into the available actions for this player name.")
						.addFunction([=] {
						vars.selectedBlacklistPlayer = c;
					})
						.addSubmenu<BlacklistActionsMenu>());
				}
			}
		}
		update = false;
	}

	if (updaterid) {
		for (int i = 0; i < vars.ridToCheck.size(); i++) {
			Session::GetSessionInfoByRockstarId(vars.ridToCheck[i], [](uint32_t rid, bool isOnline, const char *gsInfo, int gsType) {
				vars.elMap[rid] = isOnline;
				//LOG_PRINT("R*id %i is %s", rid, isOnline ? "online!" : "offline :(");
			});

			vars.ridToCheck.erase(vars.ridToCheck.begin() + i);
		}
		updaterid = false;
	}
}

/*Background update*/
void BlacklistList::FeatureUpdate() {

	static int TIMER;
	static bool update = true;
	Utils::DoTimedFunction(&TIMER, 1000, [] { update = true; });

	if (update && vars.enableBlacklist) {

		fstream i(GetConfig()->GetBlacklistPath());
		json j;
		if (i) {
			j = json::parse(i);

			for (int c = 0; c < j.size(); c++) {
				string name = j[c][0]; // should have made a struc ik
				int kick = j[c][1];
				int warn = j[c][2];
				int rid = j[c][3];
				int freeze = j[c][4];
				int blame = j[c][5];
				int explode = j[c][6];
				if (rid) {
					int idx = Utils::PlayerIDFromRID(name);
					if (idx > -1) {
						if (kick) {
							NonHostKick(idx);
							KickToSingleplayer(idx);
						}

						if (warn) GetRenderer()->NotifyMap(("R* ID: " + name + "\nLocated: In your session" + "\nNotes: " + j[c][7].get<string>()).c_str(), false);

						if (freeze) BRAIN::ClearPedTasksImmediately(GetPlayer(idx).m_ped);

						if (explode) Explode(GetPlayer(idx));

						if (blame) BlamePlayer(GetPlayer(idx));
					}
				}
				else if (!rid) {
					int idx = Utils::PlayerIDFromName(const_cast<char*>(name.c_str()));
					if (idx > -1) {
						if (kick) {
							NonHostKick(idx);
							KickToSingleplayer(idx);
						}

						if (warn) GetRenderer()->NotifyMap(("SC Name: " + name + ": " + "\nLocated: In your session" + "\nNotes: " + j[c][7].get<string>()).c_str(), false);

						if (freeze) BRAIN::ClearPedTasksImmediately(GetPlayer(idx).m_ped);

						if (explode) Explode(GetPlayer(idx));

						if (blame) BlamePlayer(GetPlayer(idx));
					}
				}

			}
		}
		update = false;
	}
}

/*Singleton*/
BlacklistList* _instance;
BlacklistList* BlacklistList::GetInstance() {
	if (_instance == nullptr) {
		_instance = new BlacklistList();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
BlacklistList::~BlacklistList() { delete _instance; }