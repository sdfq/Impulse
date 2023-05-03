#include "stdafx.h"
#include "blacklistActionsMenu.h"
#include "BlacklistList.h"
#include "menu/submenus/main/session/playerList/player/blacklistPlayer.h"
#include "menu/submenus/main/sessionMenu.h"


using namespace BlacklistActionsVars;

namespace BlacklistActionsVars {
	Var vars;

	ScrollStruct<CrewIconId> Icons[] = {
		TranslationString("Rockstar icon", true), CREW_ICON_ROCKSTAR,
		TranslationString("Kappa icon", true), CREW_ICON_KAPPA,
		TranslationString("Doge icon", true), CREW_ICON_DOGE,
		TranslationString("Trollface icon", true), CREW_ICON_TROLLFACE,
		TranslationString("Anonymous icon", true), CREW_ICON_ANONYMOUS,
		TranslationString("Spoderman icon", true), CREW_ICON_SPODERMAN,
		TranslationString("Skull icon", true), CREW_ICON_SKULL,
		TranslationString("U MAD? icon", true), CREW_ICON_UMAD,
		TranslationString("Anime Tiddies icon", true), CREW_ICON_ANIME_TIDDIES,
		TranslationString("Redtube icon", true), CREW_ICON_REDTUBE
	};
}

void BlacklistActionsMenu::Init() {
	setParentSubmenu<BlacklistList>();
	setName("Select what to do", true, true);
	addOption(ToggleOption("Kick")
		.addToggle(vars.toggleKick)
		.addFunction([=] {
		bool blacklistEnabled = BlacklistListVars::vars.enableBlacklist;
		if (blacklistEnabled) BlacklistListVars::vars.enableBlacklist = false;
		fstream file(GetConfig()->GetBlacklistPath());
		json j = json::parse(file);
		file.open(GetConfig()->GetBlacklistPath(), ofstream::out | ofstream::trunc); /*Clear the file*/
		file.close();
		if (vars.toggleKick) j[BlacklistListVars::vars.selectedBlacklistPlayer][1] = 1;
		else j[BlacklistListVars::vars.selectedBlacklistPlayer][1] = 0;
		ofstream file2(GetConfig()->GetBlacklistPath());
		file2 << setw(4) << j;
		file2.close();
		if (blacklistEnabled) BlacklistListVars::vars.enableBlacklist = true;
	})
		.addTooltip("Enable kicking on join")
		.addTranslation());

	addOption(ToggleOption("Warn me")
		.addToggle(vars.toggleWarn)
		.addFunction([=] {
		bool blacklistEnabled = BlacklistListVars::vars.enableBlacklist;
		if (blacklistEnabled) BlacklistListVars::vars.enableBlacklist = false;
		fstream file(GetConfig()->GetBlacklistPath());
		json j = json::parse(file);
		file.open(GetConfig()->GetBlacklistPath(), ofstream::out | ofstream::trunc); /*Clear the file*/
		file.close();
		if (vars.toggleWarn) j[BlacklistListVars::vars.selectedBlacklistPlayer][2] = 1;
		else j[BlacklistListVars::vars.selectedBlacklistPlayer][2] = 0;
		ofstream file2(GetConfig()->GetBlacklistPath());
		file2 << setw(4) << j;
		file2.close();
		if (blacklistEnabled) BlacklistListVars::vars.enableBlacklist = true;
	})
		.addTooltip("Enable warning on join")
		.addTranslation());

	addOption(ToggleOption("Freeze")
		.addToggle(vars.toggleFreeze)
		.addFunction([=] {
		bool blacklistEnabled = BlacklistListVars::vars.enableBlacklist;
		if (blacklistEnabled) BlacklistListVars::vars.enableBlacklist = false;
		fstream file(GetConfig()->GetBlacklistPath());
		json j = json::parse(file);
		file.open(GetConfig()->GetBlacklistPath(), ofstream::out | ofstream::trunc); /*Clear the file*/
		file.close();
		if (vars.toggleFreeze) j[BlacklistListVars::vars.selectedBlacklistPlayer][4] = 1;
		else j[BlacklistListVars::vars.selectedBlacklistPlayer][4] = 0;
		ofstream file2(GetConfig()->GetBlacklistPath());
		file2 << setw(4) << j;
		file2.close();
		if (blacklistEnabled) BlacklistListVars::vars.enableBlacklist = true;
	})
		.addTooltip("Enable freezing on join")
		.addTranslation());

	addOption(ToggleOption("Blame")
		.addToggle(vars.toggleBlame)
		.addFunction([=] {
		bool blacklistEnabled = BlacklistListVars::vars.enableBlacklist;
		if (blacklistEnabled) BlacklistListVars::vars.enableBlacklist = false;
		fstream file(GetConfig()->GetBlacklistPath());
		json j = json::parse(file);
		file.open(GetConfig()->GetBlacklistPath(), ofstream::out | ofstream::trunc); /*Clear the file*/
		file.close();
		if (vars.toggleBlame) j[BlacklistListVars::vars.selectedBlacklistPlayer][5] = 1;
		else j[BlacklistListVars::vars.selectedBlacklistPlayer][5] = 0;
		ofstream file2(GetConfig()->GetBlacklistPath());
		file2 << setw(4) << j;
		file2.close();
		if (blacklistEnabled) BlacklistListVars::vars.enableBlacklist = true;
	})
		.addTooltip("Enable blaming on join")
		.addTranslation());

	addOption(ToggleOption("Explode")
		.addToggle(vars.toggleExplode)
		.addFunction([=] {
		bool blacklistEnabled = BlacklistListVars::vars.enableBlacklist;
		if (blacklistEnabled) BlacklistListVars::vars.enableBlacklist = false;
		fstream file(GetConfig()->GetBlacklistPath());
		json j = json::parse(file);
		file.open(GetConfig()->GetBlacklistPath(), ofstream::out | ofstream::trunc); /*Clear the file*/
		file.close();
		if (vars.toggleExplode) j[BlacklistListVars::vars.selectedBlacklistPlayer][6] = 1;
		else j[BlacklistListVars::vars.selectedBlacklistPlayer][6] = 0;
		ofstream file2(GetConfig()->GetBlacklistPath());
		file2 << setw(4) << j;
		file2.close();
		if (blacklistEnabled) BlacklistListVars::vars.enableBlacklist = true;
	})
		.addTooltip("Enable exploding on join")
		.addTranslation());

	addOption(ToggleOption("Is this a R*ID?")
		.addToggle(vars.toggleRID)
		.addFunction([=] {
		bool blacklistEnabled = BlacklistListVars::vars.enableBlacklist;
		if (blacklistEnabled) BlacklistListVars::vars.enableBlacklist = false;
		fstream file(GetConfig()->GetBlacklistPath());
		json j = json::parse(file);
		file.open(GetConfig()->GetBlacklistPath(), ofstream::out | ofstream::trunc); /*Clear the file*/
		file.close();
		if (vars.toggleRID) j[BlacklistListVars::vars.selectedBlacklistPlayer][3] = 1;
		else j[BlacklistListVars::vars.selectedBlacklistPlayer][3] = 0;
		ofstream file2(GetConfig()->GetBlacklistPath());
		file2 << setw(4) << j;
		file2.close();
		if (blacklistEnabled) BlacklistListVars::vars.enableBlacklist = true;
	})
		.addTooltip("Decide on whether this item should be a R* ID or not.")
		.addTranslation());

		addOption(ButtonOption("Join player via R* ID")
			.addRequirement([] { return vars.toggleRID && GetAuth()->IsVIP(); })
			.addFunction([=] {
			bool blacklistEnabled = BlacklistListVars::vars.enableBlacklist;
			if (blacklistEnabled) BlacklistListVars::vars.enableBlacklist = false;
			fstream file(GetConfig()->GetBlacklistPath());
			json j = json::parse(file);
			string rid = j[BlacklistListVars::vars.selectedBlacklistPlayer][0].get<string>();
			Session::JoinByRockstarId(atoi(rid.c_str()));
			//GetSubmenuHandler()->SetSubPrevious(true);
			if (blacklistEnabled) BlacklistListVars::vars.enableBlacklist = true;
			GetMenu()->Close();
		})
			.addTooltip("Join this rockstar ID"));

		addOption(ScrollOption<CrewIconId>(SCROLLSELECT, "Send message to R* ID")
			.addRequirement([] { return vars.toggleRID && GetAuth()->IsVIP(); })
			.addScroll(vars.iconIndex, 0, NUMOF(Icons) - 1, Icons)
			.addFunction([] {
			GetMenuInput()->AddToQueue([] {
				string senderID;
				string recieverID;
				string subject;
				if (GetMenuInput()->Text("Enter clan tag", subject, 0, 4)) {
					string message;
					if (GetMenuInput()->Text("Enter message", message, 0, 100)) {
						fstream file(GetConfig()->GetBlacklistPath());
						json j = json::parse(file);
						string rid = j[BlacklistListVars::vars.selectedBlacklistPlayer][0].get<string>();
						long long reciever = _atoi64(rid.c_str());


						FingerOfGod::sendCrewMessageCommand(reciever, 0, Icons[vars.iconIndex].m_result, subject.c_str(), message.c_str());
						GetRenderer()->NotifyMap("Message Sent");
					}
				}
			});
		})
			.addTooltip("Send a message to this r* id"));

		addOption(ButtonOption("Input player note")
			.addFunction([]
		{
			GetFiberPool()->DoJob([]
			{
				bool blacklistEnabled = BlacklistListVars::vars.enableBlacklist;
				if (blacklistEnabled) BlacklistListVars::vars.enableBlacklist = false;
				fstream file(GetConfig()->GetBlacklistPath());
				json j = json::parse(file);
				file.open(GetConfig()->GetBlacklistPath(), ofstream::out | ofstream::trunc); /*Clear the file*/
				file.close();
				string input;
				if (GetMenuInput()->Text("Note", input, 2, 50)) {
					j[BlacklistListVars::vars.selectedBlacklistPlayer][7] = input; // 7 = input i should fucking make an enum
					ofstream file2(GetConfig()->GetBlacklistPath());
					file2 << setw(4) << j;
					file2.close();
				}
				GetSubmenuHandler()->SetSubPrevious(true);
				if (blacklistEnabled) BlacklistListVars::vars.enableBlacklist = true;
			});
		})
			.addTooltip("Allows you to edit this player's note")
			.addTranslation());

	addOption(ButtonOption("Remove player from overseer")
		.addTooltip("Removes the player from the overseer and brings you back to the overseer menu.")
		.addFunction([=] {
		bool blacklistEnabled = BlacklistListVars::vars.enableBlacklist;
		if (blacklistEnabled) BlacklistListVars::vars.enableBlacklist = false;
		fstream file(GetConfig()->GetBlacklistPath());
		json j = json::parse(file);
		file.open(GetConfig()->GetBlacklistPath(), ofstream::out | ofstream::trunc); /*Clear the file*/
		file.close();
		j.erase(BlacklistListVars::vars.selectedBlacklistPlayer);
		ofstream file2(GetConfig()->GetBlacklistPath());
		file2 << setw(4) << j;
		file2.close();
		GetSubmenuHandler()->SetSubPrevious(true);
		if (blacklistEnabled) BlacklistListVars::vars.enableBlacklist = true;
	})
		.addTranslation());
}

/*Update once when submenu is opened*/
void BlacklistActionsMenu::UpdateOnce() {
	fstream i(GetConfig()->GetBlacklistPath());
	json j;
	j = json::parse(i);
	j[BlacklistListVars::vars.selectedBlacklistPlayer][1] == 1 ? vars.toggleKick = true : vars.toggleKick = false;
	j[BlacklistListVars::vars.selectedBlacklistPlayer][2] == 1 ? vars.toggleWarn = true : vars.toggleWarn = false;
	j[BlacklistListVars::vars.selectedBlacklistPlayer][3] == 1 ? vars.toggleRID = true : vars.toggleRID = false;
	j[BlacklistListVars::vars.selectedBlacklistPlayer][4] == 1 ? vars.toggleFreeze = true : vars.toggleFreeze = false;
	j[BlacklistListVars::vars.selectedBlacklistPlayer][5] == 1 ? vars.toggleBlame = true : vars.toggleBlame = false;
	j[BlacklistListVars::vars.selectedBlacklistPlayer][6] == 1 ? vars.toggleExplode = true : vars.toggleExplode = false;
}

/*Update while submenu is active*/
void BlacklistActionsMenu::Update() {
	
}

/*Background update*/
void BlacklistActionsMenu::FeatureUpdate() {
}

/*Singleton*/
BlacklistActionsMenu* _instance;
BlacklistActionsMenu* BlacklistActionsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new BlacklistActionsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
BlacklistActionsMenu::~BlacklistActionsMenu() { delete _instance; }