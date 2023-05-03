#include "stdafx.h"
#include "recoveryMenu.h"
#include "recovery/KDMenu.h"
#include "recovery/moneyMenu.h"
#include "recovery/statsMenu.h"
#include "recovery/unlocksMenu.h"
#include "recovery/casinoMenu.h"
#include "../mainMenu.h"

using namespace RecoveryMenuVars;

namespace RecoveryMenuVars {

	Vars vars;

	int GetXpFromLevel(int level) {
		return Global(Globals::LEVEL).At(level).At(1).As<int>();
	}

	void SetLevel(String stat, int rank) {
		if (rank < 0 && rank > 8000) rank = 8000;
		Stats::SetStatI(stat, GetXpFromLevel(rank), 0);
	}

	void RpIncreaser() {
		static int TIMER;
		Utils::DoTimedFunction(&TIMER, 100, [] {
			if (PLAYER::GetPlayerWantedLevel(GetLocalPlayer().m_id) == 0) {
				PLAYER::ReportCrime(GetLocalPlayer().m_id, 28, PLAYER::GetWantedLevelThreshold(5));
				PLAYER::SetPlayerWantedCentrePosition(GetLocalPlayer().m_id, -99999, -99999, 99999);
			}
			else {
				PLAYER::ClearPlayerWantedLevel(GetLocalPlayer().m_id);
			}
		});
	}

	void RpIncreaserevent() {
		static int TIMER;
		Utils::DoTimedFunction(&TIMER, 500, [] {
			Natives::TriggerScriptEvent({ SCRIPTEVENTS::INCREASERP, GetLocalPlayer().m_id }, 2, GetLocalPlayer().m_id);
		});
	}

	int GetLevelRP(int lvl)
	{
		//return globalHandle(283571).At(lvl, 1).As<int>();
		if (lvl >= 1 && lvl <= 8000)
		{
			int idk1 = 28550;
			int idk2 = 1584350;
			int idk3 = 1;
			int idk4 = 0;
			while (idk4 == 0)
			{
				if (idk3 <= lvl)
				{
					if (lvl < 100)
					{
						idk4 = SYSTEM::Pow((lvl * 25.5f), 1.82f) + 50;
						break;
					}
					else if (idk3 >= 100)
					{
						if (lvl == idk3)
						{
							idk4 = idk2;
							break;
						}
						else
						{
							idk1 += 50;
							idk2 += idk1;
						}
					}
					else
						idk3 = 99;
					idk3++;
				}
				else break;

			}
			return idk4;
		}
		else {
			return 0;
		}
	}
}

void RecoveryMenu::Init() {
	setParentSubmenu<MainMenu>();
	setName("Recovery", true, true);

	addOption(SubmenuOption("Money")
		//.addRequirement([] { return GetAuth()->IsTester(); })
		.addSubmenu<MoneyMenu>().addTranslation()
		.addTooltip("Money options"));

	/*addOption(ButtonOption("~c~Money~s~")
		.addRequirement([] { return !GetAuth()->IsTester(); })
		.addTooltip("Disabled for fixes")
	);*/

	//addOption(ButtonOption("~c~Other options will be back shortly...~s~"));

	addOption(SubmenuOption("Unlocks")
		.addSubmenu<UnlocksMenu>().addTranslation()
		.addTooltip("Unlocks"));

	/*addOption(SubmenuOption("Casino")
		.addSubmenu<CasinoMenu>().addTranslation()
		.addTooltip("Casino stat editor"));*/

	addOption(SubmenuOption("Stat editor")
		.addSubmenu<StatsMenu>().addTranslation()
		.addTooltip("Stat editor"));

	addOption(SubmenuOption("KD editor")
		.addSubmenu<KDMenu>().addTranslation()
		.addTooltip("KD editor"));

	addOption(BreakOption("Level").addTranslation());

	/*addOption(ButtonOption("Set custom level")
		.addFunction([] { static int rank; GetMenuInput()->AddToQueue([&] {if (GetMenuInput()->Number<int>("Set custom level", &rank, 0, true, 8000, true, "%d")) SetLevel("CHAR_XP_FM", rank); }); })
		.addHotkey().addTranslation()
		.addTooltip("Sets the level to the users input"));*/

	addOption(ButtonOption("Set custom level")
		.addFunction([] { static int rank; GetMenuInput()->AddToQueue([&] {if (GetMenuInput()->Number<int>("Set custom level", &rank, 0, true, 8000, true, "%d")) SetLevel("CHAR_SET_RP_GIFT_ADMIN", rank); }); })
		.addHotkey().addTranslation()
		.addTooltip("Sets the level to the users input. You'll receive a notification when changing session"));

	addOption(ButtonOption("Set custom crew level")
		.addFunction([] { static int rank; GetMenuInput()->AddToQueue([&] {
		if (GetMenuInput()->Number<int>("Set custom crew level", &rank, 0, true, 8000, true, "%d"))
			STATS::StatSetInt(Utils::GetHashKey("MPPLY_CREW_LOCAL_XP_0"), GetLevelRP(rank), 1);
		STATS::StatSetInt(Utils::GetHashKey("MPPLY_CREW_LOCAL_XP_1"), GetLevelRP(rank), 1);
		STATS::StatSetInt(Utils::GetHashKey("MPPLY_CREW_LOCAL_XP_2"), GetLevelRP(rank), 1);
		STATS::StatSetInt(Utils::GetHashKey("MPPLY_CREW_LOCAL_XP_3"), GetLevelRP(rank), 1);
		STATS::StatSetInt(Utils::GetHashKey("MPPLY_CREW_LOCAL_XP_4"), GetLevelRP(rank), 1);
		/*STATS::StatSetInt(Utils::GetHashKey("MPPLY_CREW_GLOBAL_XP_0"), GetLevelRP(rank), 1);
		STATS::StatSetInt(Utils::GetHashKey("MPPLY_CREW_GLOBAL_XP_1"), GetLevelRP(rank), 1);
		STATS::StatSetInt(Utils::GetHashKey("MPPLY_CREW_GLOBAL_XP_2"), GetLevelRP(rank), 1);
		STATS::StatSetInt(Utils::GetHashKey("MPPLY_CREW_GLOBAL_XP_3"), GetLevelRP(rank), 1);
		STATS::StatSetInt(Utils::GetHashKey("MPPLY_CREW_GLOBAL_XP_4"), GetLevelRP(rank), 1);*/
	}); })
		.addHotkey().addTranslation()
		.addTooltip("Sets the users crew levels to what is inputted."));

	addOption(ToggleOption("RP increaser (wanted level)")
		.addToggle(vars.rpIncreaser).addTranslation().addHotkey()
		.addTooltip("Increase RP without recovery, turn off no cops"));

	/*addOption(ToggleOption("RP increaser (script event)")
		.addToggle(vars.rpIncreaserevent).addTranslation().addHotkey()
		.addTooltip("Increase RP without recovery, turn off script event blocks"));*/

	addOption(BreakOption("Misc").addTranslation());

	//addOption(ButtonOption("Fill CEO office with cash")
	//	.addFunction([] {
	//	//Stats::SetStatI("LIFETIME_BUY_COMPLETE", 4000, 1);
	//	//Stats::SetStatI("LIFETIME_BUY_UNDERTAKEN", 4000, 1);
	//	//Stats::SetStatI("LIFETIME_SELL_COMPLETE", 4000, 1);
	//	//Stats::SetStatI("LIFETIME_SELL_UNDERTAKEN", 4000, 1);
	//	//Stats::SetStatI("LIFETIME_CONTRA_EARNINGS", 30000000, 1);
	//	STATS::StatSetInt(Utils::GetHashKey("LIFETIME_BUY_COMPLETE"), 4000, 1);
	//	STATS::StatSetInt(Utils::GetHashKey("LIFETIME_BUY_UNDERTAKEN"), 4000, 1);
	//	STATS::StatSetInt(Utils::GetHashKey("LIFETIME_SELL_COMPLETE"), 4000, 1);
	//	STATS::StatSetInt(Utils::GetHashKey("LIFETIME_SELL_UNDERTAKEN"), 4000, 1);
	//	STATS::StatSetInt(Utils::GetHashKey("LIFETIME_CONTRA_EARNINGS"), 30000000, 1);
	//	STATS::StatSetInt(Utils::GetHashKey("MP0_LIFETIME_BUY_COMPLETE"), 4000, 1);
	//	STATS::StatSetInt(Utils::GetHashKey("MP0_LIFETIME_BUY_UNDERTAKEN"), 4000, 1);
	//	STATS::StatSetInt(Utils::GetHashKey("MP0_LIFETIME_SELL_COMPLETE"), 4000, 1);
	//	STATS::StatSetInt(Utils::GetHashKey("MP0_LIFETIME_SELL_UNDERTAKEN"), 4000, 1);
	//	STATS::StatSetInt(Utils::GetHashKey("MP0_LIFETIME_CONTRA_EARNINGS"), 30000000, 1);
	//	STATS::StatSetInt(Utils::GetHashKey("MP1_LIFETIME_BUY_COMPLETE"), 4000, 1);
	//	STATS::StatSetInt(Utils::GetHashKey("MP1_LIFETIME_BUY_UNDERTAKEN"), 4000, 1);
	//	STATS::StatSetInt(Utils::GetHashKey("MP1_LIFETIME_SELL_COMPLETE"), 4000, 1);
	//	STATS::StatSetInt(Utils::GetHashKey("MP1_LIFETIME_SELL_UNDERTAKEN"), 4000, 1);
	//	STATS::StatSetInt(Utils::GetHashKey("MP1_LIFETIME_CONTRA_EARNINGS"), 30000000, 1);
	//})
	//	.addTooltip("This will fill your CEO office with cash").addTranslation());

	addOption(ButtonOption("Bypass tutorial")
		.addFunction([] {Stats::SetStatB("NO_MORE_TUTORIALS", true, 1); })
		.addTooltip("Bypass tutorial").addTranslation());

	addOption(ButtonOption("Redesign character")
		.addFunction([] {
		STATS::StatSetBool(Utils::GetHashKey("MP0_FM_CHANGECHAR_ASKED"), 0, 1);
		STATS::StatSetBool(Utils::GetHashKey("MP1_FM_CHANGECHAR_ASKED"), 0, 1);
		})
		.addTooltip("Redesign character, activate in sp and then go online").addTranslation());

	addOption(ButtonOption("Change character gender")
		.addFunction([] {
		STATS::StatSetBool(Utils::GetHashKey("MP0_ALLOW_GENDER_CHANGE"), 0, 1);
		STATS::StatSetBool(Utils::GetHashKey("MP1_ALLOW_GENDER_CHANGE"), 0, 1);
	})
		.addTooltip("Press M - style - change appearence").addTranslation());

	addOption(ButtonOption("Clear mental state")
		.addFunction([] {
		STATS::StatSetBool(Utils::GetHashKey("MP0_PLAYER_MENTAL_STATE"), 0, 1);
		STATS::StatSetBool(Utils::GetHashKey("MP1_PLAYER_MENTAL_STATE"), 0, 1);
	})
		.addTooltip("Clears your current mental state").addTranslation());

	addOption(ButtonOption("Modded rolls + more ammo (shooting ability)")
		.addFunction([] {Stats::SetStatI("SHOOTING_ABILITY", 900, 1); })
		.addTooltip("Modded rolls + more ammo (shooting ability)").addTranslation());
}

/*Update once when submenu is opened*/
void RecoveryMenu::UpdateOnce() {}

/*Update while submenu is active*/
void RecoveryMenu::Update() {}

/*Background update*/
void RecoveryMenu::FeatureUpdate() {
	if (vars.rpIncreaser) RpIncreaser();
	if (vars.rpIncreaserevent) RpIncreaserevent();
}

/*Singleton*/
RecoveryMenu* _instance;
RecoveryMenu* RecoveryMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new RecoveryMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
RecoveryMenu::~RecoveryMenu() { delete _instance; }