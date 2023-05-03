#include "stdafx.h"
#include "playerListMenu.h"
#include "../sessionMenu.h"
#include "playerList/playerMenu.h"

using namespace PlayerListMenuVars;

namespace PlayerListMenuVars {
	Vars vars;

	ScrollStruct<int> sortTypes[] = {
		TranslationString("ID", true), 0,
		TranslationString("Distance", true), 1,
		TranslationString("Alphabetical", true), 2,
		TranslationString("Tag", true), 3,
		TranslationString("Money", true), 4
	};

	bool compareDistance(SPlayer& first, SPlayer& second) {
		return first.m_coordinates.Distance(GetLocalPlayer().m_coordinates) < second.m_coordinates.Distance(GetLocalPlayer().m_coordinates);
	}

	bool compareNoCase(SPlayer& first, SPlayer& second) {
		int i = 0;
		string name1 = first.m_name;
		string name2 = second.m_name;
		while ((i < name1.length()) && (i < name2.length())) {
			if (tolower(name1[i]) < tolower(name2[i])) return true;
			if (tolower(name1[i]) > tolower(name2[i])) return false;
			i++;
		}

		return name1.length() < name2.length();
	}
	bool compareMoney(SPlayer& first, SPlayer& second) {
		uint64_t money1 = Global(Globals::PLAYER_BASE).At(first.m_id, Globals::PLAYER_PADDING).At(Globals::PLAYER_OFFSET).At(Globals::PLAYER_OFFSET_TOTAL).As<uint64_t>();
		uint64_t money2 = Global(Globals::PLAYER_BASE).At(second.m_id, Globals::PLAYER_PADDING).At(Globals::PLAYER_OFFSET).At(Globals::PLAYER_OFFSET_TOTAL).As<uint64_t>();
		return (money1 > money2);
	}

	bool compareTag(SPlayer& first, SPlayer& second) {
		int points1 = 0, points2 = 0;
		if (first.m_isHost || first.m_isScriptHost) points1 += 5;
		if (first.m_isFriend) points1 += 4;
		if (first.m_isOTR) points1 += 2;
		if (first.m_isInInt) points1 += 1;
		if (first.m_isGod) points1 += 3;
		if (first.m_id == 33) points1 += 7;
		if (first.m_isLocalPlayer) points1 += 6;

		if (second.m_isHost || second.m_isScriptHost) points2 += 5;
		if (second.m_isFriend) points2 += 4;
		if (second.m_isOTR) points2 += 2;
		if (second.m_isInInt) points2 += 1;
		if (second.m_isGod) points1 += 3;
		if (second.m_id == 33) points2 += 7;
		if (second.m_isLocalPlayer) points2 += 6;

		return (points1 > points2);
	}

	String GenerateName(PlayerListMenu* instance, SPlayer& player) {
		static char name[150] = { 0 };
		strcpy(name, "");
		strcat(name, player.m_name);
		strcat(name, " ");

		if (GetAuth()->IsStaff() || GetAuth()->IsTester()) {
			if (player.m_isEvolveUserHidden && !player.m_isLocalPlayer) strcat(name, va("~c~%s~s~", instance->getString("[I]")));
		}
		if (player.m_isEvolveUser && !player.m_isEvolveVIP) strcat(name, va("~o~%s~s~", instance->getString("[IMP]")));
		if (player.m_isEvolveUserBlock) strcat(name, va("~o~%s~s~", instance->getString("[IMP-B]")));
		if (player.m_isEvolveStaff || player.m_isEvolveUser && player.m_isEvolveVIP && player.m_isEvolveStaff || player.m_isEvolveUser && player.m_isEvolveStaff || player.m_isEvolveVIP && player.m_isEvolveStaff) strcat(name, va("~o~%s~s~", instance->getString("[IMP-STAFF]")));
		if (player.m_isEvolveUser && player.m_isEvolveVIP || !player.m_isEvolveUser && player.m_isEvolveVIP) strcat(name, va("~o~%s~s~", instance->getString("[IMP-VIP]")));
		//
		if (vars.sorttype == 1) strcat(name, va("~b~[%.0f]~s~", player.m_coordinates.Distance(GetLocalPlayer().m_coordinates)));
		//
		if (player.m_isOTR && !player.m_isLocalPlayer) strcat(name, va("~b~%s~s~", instance->getString("[OTR]")));
		if (player.m_passive && !player.m_isLocalPlayer) strcat(name, va("~b~%s~s~", instance->getString("[PASSIVE]")));
		if (player.m_paused) strcat(name, va("~c~%s~s~", instance->getString("[PAUSED]")));
		if (player.m_typing) strcat(name, va("~c~%s~s~", instance->getString("[TYPING]")));
		if (player.m_cutscene && !player.m_isLocalPlayer) strcat(name, va("~c~%s~s~", instance->getString("[CUTSCENE]")));
		if (player.m_joining) strcat(name, va("~c~%s~s~", instance->getString("[JOINING..]")));
		//
		if (player.m_modding && !player.m_isLocalPlayer) strcat(name, va("~q~%s~s~", instance->getString("[MOD]")));
		if (player.m_isInInt && !player.m_isGod && !player.m_isLocalPlayer) strcat(name, va("~g~%s~s~", instance->getString("[INT]")));
		if (player.m_isGod && !player.m_isInInt && !player.m_modding && !player.m_isLocalPlayer) strcat(name, va("~r~%s~s~", instance->getString("[GOD]")));
		if (player.m_isGod && player.m_isInInt && !player.m_isLocalPlayer) strcat(name, va("~g~%s~s~", instance->getString("[INT]")));
		if (player.m_id == 30 || player.m_id == 31) strcat(name, va("~r~%s~s~", instance->getString("[SCTV]")));
		if (player.m_rstardev && !player.m_isLocalPlayer) strcat(name, va("~r~%s~s~", instance->getString("[ROCKSTAR]")));
		//
		if (player.m_isHost) strcat(name, va("~y~%s~s~", instance->getString("[Session Host]")));
		if (player.m_isScriptHost && !player.m_isHost) strcat(name, va("~y~%s~s~", instance->getString("[Script Host]")));
		if (player.m_isFriend) strcat(name, va("~y~%s~s~", instance->getString("[F]"))); //~q~ pinky purple
		if (player.m_isLocalPlayer) strcat(name, va("~y~%s~s~", instance->getString("[SELF]")));
		return name;
	}

	ScrollStruct<int> typesformarker[] = {
		TranslationString("Playerlist", true), 0,
		TranslationString("Playerlist & Playermenu", true), 1,
	};
}

void PlayerListMenu::Init() {
	setParentSubmenu<SessionMenu>();
	setName("Players", true, true);

	addString("[MOD]");
	addString("[Session Host]");
	addString("[Script Host]");
	addString("[F]");
	addString("[OTR]");
	addString("[INT]");
	addString("[GOD]");
	addString("[SCTV]");
	addString("[ROCKSTAR]");
	addString("[PASSIVE]");
	addString("[PAUSED]");
	addString("[TYPING]");
	addString("[CUTSCENE]");
	addString("[JOINING..]");
	addString("[SELF]");
	addString("[I]");
	addString("[IMP]");
	addString("[IMP-VIP]");
	addString("[IMP-B]");
	addString("[IMP-STAFF]");

	addOption(ScrollOption<int>(SCROLL, "Sort player list")
		.addScroll(vars.sorttype, 0, NUMOF(sortTypes) - 1, sortTypes)
		.canBeSaved().addTranslation()
		.addTooltip("Sort the player list"));

	addOption(ScrollOption<int>(TOGGLE, "Show marker on selected players")
		.addToggle(SessionMenuVars::vars.showmarkeronselectedbydefault)
		.addScroll(SessionMenuVars::vars.markertypeselector, 0, NUMOF(typesformarker) - 1, typesformarker)
		.addTooltip("This will show a marker above players on hover, will also show marker on last entered player")
		.canBeSaved()
		.addTranslation().addHotkey());

	addOption(BreakOption("Players").addTranslation());

	PlayerMenu::GetInstance();
}

/*Update once when submenu is opened*/
void PlayerListMenu::UpdateOnce() {}

/*Update while submenu is active*/
void PlayerListMenu::Update() {
	static int TIMER;
	static bool update = true;
	Utils::DoTimedFunction(&TIMER, 250, [] {update = true; });

	if (update) {
		clearOptionsOffset(3);
		vector<SPlayer> players;
		for (int i = 0; i < MAXPLAYERS; i++) {
			if (GetPlayer(i).m_exists) {
				players.push_back(GetPlayer(i));
			}
		}

		switch (vars.sorttype) {
		case 0: break;
		case 1: sort(players.begin(), players.end(), compareDistance); break;
		case 2: sort(players.begin(), players.end(), compareNoCase); break;
		case 3: sort(players.begin(), players.end(), compareTag); break;
		case 4: sort(players.begin(), players.end(), compareMoney); break;
		default: break;
		}

		for (SPlayer& player : players) {
			addOption(SubmenuOption(GenerateName(this, player))
				.addSubmenu<PlayerMenu>()
				.addOnDraw([=](int index) {
				if (NETWORK::NetworkIsSessionActive()) {
					String texture = PED::GetPedheadshotTxdString(player.m_headshotHandle);
					GetRenderer()->DrawSpriteUnsafe({ texture, texture }, GetRenderer()->m_posX - (GetRenderer()->m_width / 2) + 0.01f, GetRenderer()->GetOptionY(index) + GetRenderer()->m_optionHeight / 2, 0.01125f, 0.0225f, 0, Color(255, 255, 255, 210));
					return 0.01125f;
				}
			})
				.addCurrentOp([=] { GetWindowManager()->m_playerInfoComp.setPlayer(player.m_id); GetWindowManager()->m_playerInfo.setName(player.m_name); })
				.addFunction([=] {PlayerMenuVars::player = player.m_id; PlayerMenu::GetInstance()->getName().SetMapped(player.m_name);
			})
				.addTooltip("Go to player submenu"));
		}

		if (GetMenu()->m_currentOption > m_options.size()) GetMenu()->ResetCurrentOption();
		update = false;
	}
}

/*Background update*/
void PlayerListMenu::FeatureUpdate() {

}

/*Singleton*/
PlayerListMenu* _instance;
PlayerListMenu* PlayerListMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new PlayerListMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
PlayerListMenu::~PlayerListMenu() { delete _instance; }