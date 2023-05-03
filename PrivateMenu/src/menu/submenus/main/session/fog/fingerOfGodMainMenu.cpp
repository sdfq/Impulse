#include "stdafx.h"
#include "fingerOfGodMainMenu.h"
#include "fingerOfGodMenu.h"
#include "fingerOfGodFriendMenu.h"
#include "../../sessionMenu.h"

using namespace FingerOfGodMainMenuVars;

namespace FingerOfGodMainMenuVars {
	Vars vars;

	int networkHandle[100][13];
	__int64 presenceEventHandle[100][76];
}

void FingerOfGodMainMenu::Init() {
	setParentSubmenu<SessionMenu>();
	setName("Finger of god", true, false);

	addOption(SubmenuOption("Friend")
		.addRequirement([] { return GetAuth()->IsTester(); })
		.addSubmenu<FingerOfGodFriendMenu>()
		.addTooltip("Use FOG against your friends, even if they're in single player"));

	addOption(ButtonOption("Custom rockstar ID")
		.addRequirement([] { return GetAuth()->IsTester(); })
		.addFunction([] {
		GetMenuInput()->AddToQueue([] {
			string test;
			if (GetMenuInput()->Text("Input R* ID", test, 0, 100)) {
				FingerOfGodMenuVars::vars.currentID = _atoi64(test.c_str());
				GetSubmenuHandler()->SetSubmenu(FingerOfGodMenu::GetInstance());
			}
		});
	})
		.addTooltip("Custom rockstar ID"));

	addOption(ButtonOption("Advertise Impulse")
		.addRequirement([] { return GetAuth()->IsTester(); })
		.addFunction([] {
		static int _networkHandle[100][13]; // Reason is incase the usage in FingerOfGodMainMenu::Update fucks with it as that's called once every 250ms
		static __int64 _presenceEventHandle[100][76];
		OnlinePlayerCallback(false, [=](SPlayer player) {
			NETWORK::NetworkHandleFromPlayer(player.m_id, _networkHandle[player.m_id], 13);
			if (FingerOfGod::GetNetworkHandleID((__int64)_presenceEventHandle[player.m_id], _networkHandle[player.m_id], 13)) {
				FingerOfGod::sendCrewMessageCommand(*(__int64*)_presenceEventHandle[player.m_id], 0, CREW_ICON_ROCKSTAR, "LOOT", "Purchase the best mod at Impulse.black today!");
			}
		});
	})
		.addHotkey().addTranslation()
		.addTooltip("Send a crew message to the session advertising Impulse"));

	addOption(BreakOption("Players in session"));
}

/*Update once when submenu is opened*/
void FingerOfGodMainMenu::UpdateOnce() {}

/*Update while submenu is active*/
void FingerOfGodMainMenu::Update() {
	static int TIMER;
	static bool update = true;
	Utils::DoTimedFunction(&TIMER, 250, [] {update = true; });

	if (update) {
		clearOptionsOffset(4);
		vector<SPlayer> players;
		for (int i = 0; i < MAXPLAYERS; i++) {
			if (GetPlayer(i).m_exists) {
				players.push_back(GetPlayer(i));
			}
		}

		for (SPlayer& player : players) {
			NETWORK::NetworkHandleFromPlayer(player.m_id, networkHandle[player.m_id], 13);
			if (FingerOfGod::GetNetworkHandleID((__int64)presenceEventHandle[player.m_id], networkHandle[player.m_id], 13)) {
				addOption(SubmenuOption(player.m_name)
					.addRequirement([] { return GetAuth()->IsTester(); })
					.addFunction([=] { FingerOfGodMenuVars::vars.currentID = *(__int64*)presenceEventHandle[player.m_id]; })
					.addSubmenu<FingerOfGodMenu>());
			}
		}

		if (GetMenu()->m_currentOption > m_options.size()) GetMenu()->ResetCurrentOption();
		update = false;
	}
}

/*Background update*/
void FingerOfGodMainMenu::FeatureUpdate() {}

/*Singleton*/
FingerOfGodMainMenu* _instance;
FingerOfGodMainMenu* FingerOfGodMainMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new FingerOfGodMainMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
FingerOfGodMainMenu::~FingerOfGodMainMenu() { delete _instance; }