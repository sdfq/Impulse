#include "stdafx.h"
#include "sessionTalking.h"
#include "../allPlayersMenu.h"

using namespace SessionTalkingMenuVars;

namespace SessionTalkingMenuVars {
	Vars vars;
}

void SessionTalkingMenu::Init() {
	setParentSubmenu<AllPlayersMenu>();
	setName("Talking", true, true);

	addOption(ToggleOption("Show list")
		.addToggle(vars.showList)
		.addTranslation().addHotkey()
		.addTooltip("Draw the talking players"));

	addOption(ToggleOption("Explode")
		.addToggle(vars.explode)
		.addTranslation().addHotkey()
		.addTooltip("Explode the talking players"));

	addOption(ToggleOption("Add wanted level")
		.addToggle(vars.addWantedLevel)
		.addTranslation().addHotkey()
		.addTooltip("Add wanted level to the talking players"));
}

/*Update once when submenu is opened*/
void SessionTalkingMenu::UpdateOnce() {}

/*Update while submenu is active*/
void SessionTalkingMenu::Update() {}

/*Background update*/
void SessionTalkingMenu::FeatureUpdate() {
	if (vars.showList) {
		float showTalkingIndex = 0.05f;
		OnlinePlayerCallback(true, [&](SPlayer player) {
			if (NETWORK::NetworkPlayerHasHeadset(player.m_id)) {
				if (NETWORK::NetworkIsPlayerTalking(player.m_id)) {
					GetRenderer()->DrawString(player.m_name, 0.80f, (showTalkingIndex += .02f), FontChaletLondon, 0.30f, Color(255, 255, 255));
				} else {
					GetRenderer()->DrawString(va("~m~%s", player.m_name), 0.80f, (showTalkingIndex += .02f), FontChaletLondon, 0.30f, Color(255, 255, 255));
				}
			}
		});
	}

	if (vars.explode) {
		OnlinePlayerCallback(false, [&](SPlayer player) {
			if (NETWORK::NetworkPlayerHasHeadset(player.m_id)) {
				if (NETWORK::NetworkIsPlayerTalking(player.m_id)) {
					FIRE::AddExplosion(player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 2, 10000, true, false, 0.0f, false);
				}
			}
		});
	}

	if (vars.addWantedLevel) {
		OnlinePlayerCallback(false, [&](SPlayer player) {
			if (NETWORK::NetworkPlayerHasHeadset(player.m_id)) {
				if (NETWORK::NetworkIsPlayerTalking(player.m_id)) {
					PLAYER::ReportCrime(player.m_id, 8, PLAYER::GetWantedLevelThreshold(5));
				}
			}
		});
	}
}

/*Singleton*/
SessionTalkingMenu* _instance;
SessionTalkingMenu* SessionTalkingMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new SessionTalkingMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
SessionTalkingMenu::~SessionTalkingMenu() { delete _instance; }