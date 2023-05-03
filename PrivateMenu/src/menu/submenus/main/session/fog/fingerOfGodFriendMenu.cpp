#include "stdafx.h"
#include "fingerOfGodFriendMenu.h"
#include "fingerOfGodMenu.h"
#include "fingerOfGodMainMenu.h"

using namespace FingerOfGodFriendMenuVars;

namespace FingerOfGodFriendMenuVars {
	Vars vars;

	int networkHandle[100][13];
	__int64 presenceEventHandle[100][76];
}

void FingerOfGodFriendMenu::Init() {
	setParentSubmenu<FingerOfGodMainMenu>();
	setName("Friend", true, true);
}

/*Update once when submenu is opened*/
void FingerOfGodFriendMenu::UpdateOnce() {
	clearOptionsOffset(0);

	int friendCount = NETWORK::NetworkGetFriendCount();

	for (int i = 0; i < friendCount; i++) {
		NETWORK::NetworkHandleFromFriend(i, networkHandle[i], 13);
		if (FingerOfGod::GetNetworkHandleID((__int64)presenceEventHandle[i], networkHandle[i], 13)) {
			addOption(SubmenuOption(NETWORK::NetworkGetFriendName(i))
				.addRequirement([] { return GetAuth()->IsTester(); })
				.addFunction([=] { FingerOfGodMenuVars::vars.currentID = *(__int64*)presenceEventHandle[i]; })
				.addSubmenu<FingerOfGodMenu>());
		}
	}
}

/*Update while submenu is active*/
void FingerOfGodFriendMenu::Update() {}

/*Background update*/
void FingerOfGodFriendMenu::FeatureUpdate() {}

/*Singleton*/
FingerOfGodFriendMenu* _instance;
FingerOfGodFriendMenu* FingerOfGodFriendMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new FingerOfGodFriendMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
FingerOfGodFriendMenu::~FingerOfGodFriendMenu() { delete _instance; }