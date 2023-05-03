#include "stdafx.h"
#include "menu/submenus/main/session/playerList/playerMenu.h"
#include "blacklistPlayer.h"
#include "blacklist/BlacklistList.h"

using namespace BlacklistVars;

namespace BlacklistVars {
}


void BlacklistMenu::Init() {
	setParentSubmenu<PlayerMenu>();
	setName("Overseer", true , true);
	
	addOption(ButtonOption("Add player to overseer")
		.addFunction([] {
		if (Utils::DoesItExistInBlacklist(0, GetSelectedPlayer().m_name)) return;
		json j;
		if (GetConfig()->DoesFileExist(GetConfig()->GetBlacklistPath())) {
			fstream file(GetConfig()->GetBlacklistPath());
			j = json::parse(file);
			file.open(GetConfig()->GetBlacklistPath(), ofstream::out | ofstream::trunc); /*Clear the file*/
			file.close();
		}
		j.push_back({ GetSelectedPlayer().m_name, 0, 0, 0, 0, 0, 0, "Empty note" }); // last 0, we are adding a player not a rid
		ofstream file2(GetConfig()->GetBlacklistPath());
		file2 << setw(4) << j;
		file2.close();
	}).addTranslation()
	.addTooltip("This will add the player name to your overseer, goto session to edit").addTranslation());

	addOption(ButtonOption("Add R* ID to overseer")
		.addFunction([] {

		json j;
		if (GetConfig()->DoesFileExist(GetConfig()->GetBlacklistPath())) {
			fstream file(GetConfig()->GetBlacklistPath());
			j = json::parse(file);
			file.open(GetConfig()->GetBlacklistPath(), ofstream::out | ofstream::trunc); /*Clear the file*/
			file.close();
		}
		CPed* ped = (CPed*)(PoolManager::GetEntityAddress(GetSelectedPlayer().m_ped));
		if (ped != 0) {
			string rid = to_string(ped->PlayerInfo->RockstarID);
			if (Utils::DoesItExistInBlacklist(_atoi64(rid.c_str()))) return;
			string pname = GetSelectedPlayer().m_name;
			j.push_back({ rid, 0, 0, 1, 0, 0, 0, pname }); // last 1, we are adding a rid
		}
		ofstream file2(GetConfig()->GetBlacklistPath());
		file2 << setw(4) << j;
		file2.close();
	}).addTranslation()
	.addTooltip("This will add the players r* id to your overseer, goto session to edit").addTranslation());

}

/*Update once when submenu is opened*/
void BlacklistMenu::UpdateOnce() {}

/*Update while submenu is active*/
void BlacklistMenu::Update() {}

/*Background update*/
void BlacklistMenu::FeatureUpdate() {
}


/*Singleton*/
BlacklistMenu* _instance;
BlacklistMenu* BlacklistMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new BlacklistMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
BlacklistMenu::~BlacklistMenu() { delete _instance; }