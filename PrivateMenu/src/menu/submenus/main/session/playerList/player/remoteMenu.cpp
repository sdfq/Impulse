#include "stdafx.h"
#include "remoteMenu.h"
#include "../playerMenu.h"

using namespace RemoteMenuVars;

namespace RemoteMenuVars {
	Vars vars;

	ScrollStruct<int> invites[] = {
		TranslationString("Yacht", true), 1,
		TranslationString("Office", true), 2,
		TranslationString("Clubhouse", true), 3,
		TranslationString("Office garage", true), 6,
		TranslationString("Auto shop", true), 7,
		TranslationString("Apartment", true), 0
	};

	ScrollStruct<int> missions[] = {
		TranslationString("Weather Mission", true), 0,
		TranslationString("Exit Strat Mission", true), 2,
		TranslationString("Cover Blown Mission", true), 4,
		TranslationString("Mole Hunt Mission", true), 5,
		TranslationString("Data Breach Mission", true), 6,
		TranslationString("Work Dispute Mission", true), 7
	};

	ScrollStruct<int> msgs[] = {
		TranslationString("Armorerd truck", true), 1584445674, // 1.46 = -130461309
		TranslationString("Easy way out", true), -248473985, // 1.46 = 554851531
		TranslationString("Smuggler Plane", true), 867265021, // 1.46 = -53425260
		TranslationString("You have entered the .", true), -1105658240, // 1.46 = 1369534593
		TranslationString("You develiered a bag of cash", true), 1582222113, // 1.46 = -957727376
		TranslationString("Mugger $1", true), 771350006, // 1.46 = -210487359
		TranslationString("Added to your wanted level", true), -53170297, // 1.46 = 1723217930
		TranslationString("Off the radar", true), 1380034405, // 1.46 = -1476055326
		TranslationString("The king", true), 1219422932, // 1.46 = -89603292
		TranslationString("Revealed all players", true), 1532262544 // 1.46 = 650772739

	};

	ScrollStruct<int> moneyamount[] = {
		TranslationString("$1", true), 1,
		TranslationString("$10000", true), 10000,
		TranslationString("$1000000", true), 1000000,
		TranslationString("$100000000", true), 100000000,
		TranslationString("$999999999", true), 999999999,
		TranslationString("$2147483647", true), 2147483647,
		TranslationString("$1337", true), 1337,
		TranslationString("$69", true), 69
	};

	ScrollStruct<int> moneymsgs[] = {
		TranslationString("Banked money", true), -1695772783, // 1.46 = -1550586884
		TranslationString("Stolen money", true), 1014468925, // 1.46 = -1432462772
		TranslationString("Removed money", true), 1207028646 // 1.46 = 2110027654
	};

	void NonHostKick(SPlayer& player) {
		NETWORK::NetworkSessionKickPlayer(player.m_id);
		Natives::ObfuscatedTriggerScriptEvent({ SCRIPTEVENTS::NONHOSTKICK1, player.m_id, 48 }, 3, player.m_id);
		Natives::ObfuscatedTriggerScriptEvent({ SCRIPTEVENTS::NONHOSTKICK2, player.m_id }, 2, player.m_id);
		Natives::ObfuscatedTriggerScriptEvent({ SCRIPTEVENTS::NONHOSTKICK3, player.m_id }, 2, player.m_id);
		Natives::ObfuscatedTriggerScriptEvent({ SCRIPTEVENTS::NONHOSTKICK4, player.m_id }, 2, player.m_id);
		Natives::ObfuscatedTriggerScriptEvent({ SCRIPTEVENTS::NONHOSTKICK5, player.m_id }, 2, player.m_id);
		Natives::ObfuscatedTriggerScriptEvent({ 1953937033, player.m_id, 0 }, 3, player.m_id);
		Natives::ObfuscatedTriggerScriptEvent({ 3353227751, player.m_id, 0 }, 3, player.m_id);
	}

	void KickToSingleplayer(SPlayer& player) {
		NETWORK::NetworkSessionKickPlayer(player.m_id);
		Natives::ObfuscatedTriggerScriptEvent({ SCRIPTEVENTS::KICKTOSP1, player.m_id, 1 }, 3, player.m_id);
		Natives::ObfuscatedTriggerScriptEvent({ SCRIPTEVENTS::KICKTOSP2, player.m_id }, 2, player.m_id);
		Natives::ObfuscatedTriggerScriptEvent({ SCRIPTEVENTS::KICKTOSP3, player.m_id, 0 }, 3, player.m_id);
		Natives::ObfuscatedTriggerScriptEvent({ SCRIPTEVENTS::NONHOSTKICK3, player.m_id, 0 }, 3, player.m_id);
		Natives::ObfuscatedTriggerScriptEvent({ SCRIPTEVENTS::NONHOSTKICK4, player.m_id, 0 }, 3, player.m_id);
		Natives::ObfuscatedTriggerScriptEvent({ SCRIPTEVENTS::NONHOSTKICK6, player.m_id, 0 }, 3, player.m_id);
		Natives::ObfuscatedTriggerScriptEvent({ 1953937033, player.m_id, 0 }, 3, player.m_id);
		Natives::ObfuscatedTriggerScriptEvent({ 2870072008, player.m_id, 0 }, 3, player.m_id);
	}

	void CEOKick(SPlayer& player) {
		Natives::TriggerScriptEvent({ SCRIPTEVENTS::CEOKICK, player.m_id, 1, 5 }, 4, player.m_id); // 585981075
	}

	void CEOBan(SPlayer& player) {
		Natives::TriggerScriptEvent({ SCRIPTEVENTS::CEOBAN, player.m_id, 2, 1 }, 4, player.m_id); // 1318668309
	}

	void InfiniteLoadingScreen(SPlayer& player) {
		Natives::TriggerScriptEvent({ SCRIPTEVENTS::ECLIPSETELEPORT, player.m_id, 0, 0 }, 4, player.m_id); // -328868154
	}

	void Invite(SPlayer& player, int index) {
		Natives::TriggerScriptEvent({ SCRIPTEVENTS::INVITE, player.m_id, invites[index].m_result }, 3, player.m_id); // 729971264
	}

	void GOTR(SPlayer& player) {
		static int TIMER[32];
		Utils::DoTimedFunction(&TIMER[player.m_id], 300, [&] {
			Natives::TriggerScriptEvent({ SCRIPTEVENTS::GOTR, player.m_id, NETWORK::GetNetworkTime(), NETWORK::GetNetworkTime(), 1, 1, Global(Globals::REMOTE_BASE).At(player.m_id, Globals::REMOTE_SIZE).At(Globals::REMOTE_OFFSET).As<int>() }, 7, player.m_id);
		});
	}

	void GNeverWanted(SPlayer& player) {
		static int TIMER[32];
		Utils::DoTimedFunction(&TIMER[player.m_id], 300, [&] {
			Natives::TriggerScriptEvent({ SCRIPTEVENTS::GNEVERWANTED, player.m_id, Global(Globals::REMOTE_BASE).At(player.m_id, Globals::REMOTE_SIZE).At(Globals::REMOTE_OFFSET).As<int>() }, 3, player.m_id);
			//int handle = globalHandle(1625435).At(player, 560).At(491).As<int>();
		});
	}

	void GCopsTurnBlindEye(SPlayer& player) {
		static int TIMER[32];
		Utils::DoTimedFunction(&TIMER[player.m_id], 300, [&] {
			Natives::TriggerScriptEvent({ SCRIPTEVENTS::GCOPSTURNBLINDEYE, player.m_id, NETWORK::GetNetworkTime(), NETWORK::GetNetworkTime(), 1, 1, Global(Globals::REMOTE_BASE).At(player.m_id, Globals::REMOTE_SIZE).At(Globals::REMOTE_OFFSET).As<int>() }, 7, player.m_id);
			//int handle = globalHandle(1625435).At(target, 560).At(491).As<int>();
			//int handle1 = globalHandle(2524719).At(4545).As<int>();
		});
	}

	void Friendly(SPlayer& player) {
		Backend::IncrementPlayerStat(player.m_id, Utils::GetHashKey("MPPLY_FRIENDLY"), 9999);
	}

	void Helpful(SPlayer& player) {
		Backend::IncrementPlayerStat(player.m_id, Utils::GetHashKey("MPPLY_HELPFUL"), 9999);
	}

	void RBadSport(SPlayer& player) {
		static int TIMER[32];
		Utils::DoTimedFunction(&TIMER[player.m_id], 200, [&] {
			Backend::IncrementPlayerStat(player.m_id, Utils::GetHashKey("MPPLY_HELPFUL"), 99999);
			Backend::IncrementPlayerStat(player.m_id, Utils::GetHashKey("MPPLY_FRIENDLY"), 99999);
		});
	}

	void BadRep(SPlayer& player) {
		Backend::IncrementPlayerStat(player.m_id, Utils::GetHashKey("MPPLY_BECAME_CHEATER_NUM"), 10);
		Backend::IncrementPlayerStat(player.m_id, Utils::GetHashKey("MPPLY_GRIEFING"), 10);
		Backend::IncrementPlayerStat(player.m_id, Utils::GetHashKey("MPPLY_OFFENSIVE_LANGUAGE"), 10);
		Backend::IncrementPlayerStat(player.m_id, Utils::GetHashKey("MPPLY_OFFENSIVE_UGC"), 10);
	}

	void BadSport(SPlayer& player) {
		static int TIMER[32];
		Utils::DoTimedFunction(&TIMER[player.m_id], 300, [&] {
			Backend::IncrementPlayerStat(player.m_id, Utils::GetHashKey("MPPLY_BECAME_CHEATER_NUM"), 99999);
			Backend::IncrementPlayerStat(player.m_id, Utils::GetHashKey("MPPLY_GRIEFING"), 99999);
			Backend::IncrementPlayerStat(player.m_id, Utils::GetHashKey("MPPLY_OFFENSIVE_LANGUAGE"), 99999);
			Backend::IncrementPlayerStat(player.m_id, Utils::GetHashKey("MPPLY_OFFENSIVE_UGC"), 99999);
		});
	}

	void SoundSpam(SPlayer& player) {
		Natives::TriggerScriptEvent({ SCRIPTEVENTS::INVITE, player.m_id, 0 }, 3, player.m_id);
	}

	void DisplaySpectatingMessage(SPlayer& player) {
		Natives::TriggerScriptEvent({ SCRIPTEVENTS::SPECTATINGMESSAGE, player.m_id }, 2, player.m_id);
	}

	void FaceCameraForward(SPlayer& player) {
		static int TIMER2[32];
		Utils::DoTimedFunction(&TIMER2[player.m_id], 200, [&] {
			Natives::TriggerScriptEvent({ SCRIPTEVENTS::FACECAMERAFORWARD, player.m_id, SCRIPTEVENTS::FACECAMERAFORWARD2 }, 3, player.m_id);
		});
	}

	void test(SPlayer& player) {
		Natives::TriggerScriptEvent({ 2023259876 }, 1, player.m_id);
		Natives::TriggerScriptEvent({ -2100194653 }, 1, player.m_id);
	}

	void WantedLevelRP(SPlayer& player) {
		PLAYER::ReportCrime(player.m_id, 8, PLAYER::GetWantedLevelThreshold(5));

		static int TIMER2[32];
		Utils::DoTimedFunction(&TIMER2[player.m_id], 2000, [&] {
			Natives::TriggerScriptEvent({ SCRIPTEVENTS::GNEVERWANTED, player.m_id, Global(Globals::REMOTE_BASE).At(player.m_id, Globals::REMOTE_SIZE).At(Globals::REMOTE_OFFSET).As<int>() }, 3, player.m_id);
		});
	}
}

void RemoteMenu::Init() {
	setParentSubmenu<PlayerMenu>();
	setName("Remote", true, false);

	/*addOption(ButtonOption("Non host kick")
		.addFunction([] { test(GetSelectedPlayer()); })
		.addTooltip("Non host kick").addTranslation());*/

	addOption(ButtonOption("Non host kick")
		.addFunction([] { NonHostKick(GetSelectedPlayer()); })
		.addTooltip("Non host kick").addTranslation());

	addOption(ButtonOption("Kick to single player")
		.addFunction([] {KickToSingleplayer(GetSelectedPlayer()); })
		.addTooltip("Kick to single player").addTranslation());

	addOption(ButtonOption("CEO kick")
		.addFunction([] {CEOKick(GetSelectedPlayer()); })
		.addTooltip("CEO kick").addTranslation());

	addOption(ButtonOption("CEO ban")
		.addFunction([] {CEOBan(GetSelectedPlayer()); })
		.addTooltip("CEO ban").addTranslation());

	addOption(BreakOption("Troll").addTranslation());

	addOption(ButtonOption("Infinite loading screen")
		.addFunction([] {InfiniteLoadingScreen(GetSelectedPlayer()); })
		.addTooltip("Infinite loading screen").addTranslation());

	addOption(ToggleOption("Sound spam")
		.addToggle(GetSelectedPlayer().m_soundSpam)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_soundSpam); })
		.addTranslation()
		.addTooltip("Sound spam"));

#ifdef HARD_DEV

#endif

	addOption(ButtonOption("Transaction error")
		.addFunction([] { 
		auto var0 = Global(1626536 + 1 + GetSelectedPlayer().m_id * 603 + 529).As<int>();
		auto var1 = Global(1645834 + 9).As<int>();
		Natives::TriggerScriptEvent({ SCRIPTEVENTS::TRANSACTIONERRORSPAM, GetSelectedPlayer().m_id, 10000, 0, 0, var0, var1, var1 }, 8, GetSelectedPlayer().m_id);
	})
		.addTooltip("This will give the player a transaction error black screen").addTranslation());

	addOption(ButtonOption("Face players camera forward")
		.addFunction([] { Natives::TriggerScriptEvent({ SCRIPTEVENTS::FACECAMERAFORWARD, GetSelectedPlayer().m_id, SCRIPTEVENTS::FACECAMERAFORWARD2 }, 3, GetSelectedPlayer().m_id); })
		.addTooltip("Face the players camera forward").addTranslation());

	addOption(ToggleOption("Force players camera forward")
		.addToggle(GetSelectedPlayer().m_facecamera)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_facecamera); })
		.addTooltip("Force the players camera forward on loop").addTranslation());

	addOption(ButtonOption("Gentle kick from vehicle")
		.addFunction([] { Natives::TriggerScriptEvent({ SCRIPTEVENTS::KICKFROMVEHICLE, GetSelectedPlayer().m_id }, 2, GetSelectedPlayer().m_id); })
		.addTooltip("Gently kick the player from his vehicle").addTranslation());

	addOption(ScrollOption<int>(SCROLLSELECT, "Force into mission")
		.addScroll(vars.m_mission, 0, NUMOF(missions) - 1, missions)
		.addFunction([] { Natives::TriggerScriptEvent({ SCRIPTEVENTS::FORCEINTOMISSION, GetSelectedPlayer().m_id, missions[vars.m_mission].m_result }, 3, GetSelectedPlayer().m_id); })
		.addTooltip("Force the player into a mission").addTranslation());

	addOption(BreakOption("Notifications").addTranslation());

	addOption(ToggleOption("Display spectating message")
		.addToggle(GetSelectedPlayer().m_displaySpectatingMessage)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_displaySpectatingMessage); })
		.addTooltip("Display spectating message").addTranslation());

	addOption(ButtonOption("Display insurance message")
		.addFunction([] { Natives::TriggerScriptEvent({ SCRIPTEVENTS::DISPLAYINSURANCEMESSAGE, GetSelectedPlayer().m_id, 9999999999 }, 3, GetSelectedPlayer().m_id); })
		.addTooltip("This will display an insurance message to the player").addTranslation());

	addOption(ScrollOption<int>(SCROLLSELECT, "Invite notifs")
		.addScroll(vars.m_invite, 0, NUMOF(invites) - 1, invites)
		.addFunction([] { Invite(GetSelectedPlayer(), vars.m_invite); })
		.addTooltip("Invite to selection").addTranslation());

	addOption(ScrollOption<int>(SCROLLSELECT, "Send message notifs")
		.addScroll(vars.m_msgs, 0, NUMOF(msgs) - 1, msgs)
		.addFunction([] { Natives::TriggerScriptEvent({ SCRIPTEVENTS::NOTIFICATION, GetSelectedPlayer().m_id, msgs[vars.m_msgs].m_result }, 3, GetSelectedPlayer().m_id); })
		.addTooltip("Send message notifs to a player").addTranslation());

	addOption(ButtonOption("Send notif banner")
		.addFunction([] { Natives::TriggerScriptEvent({ SCRIPTEVENTS::NOTIFICATION, GetSelectedPlayer().m_id, SCRIPTEVENTS::NOTIFICATION2 }, 3, GetSelectedPlayer().m_id); })
		.addTooltip("Displays a onscreen banner on players screen").addTranslation());

	addOption(ScrollOption<int>(SCROLL, "Send money notif amount")
		.addScroll(vars.m_moneyamount, 0, NUMOF(moneyamount) - 1, moneyamount)
		.addTooltip("Change the money amount for the notif function below").addTranslation());

	addOption(ScrollOption<int>(SCROLLSELECT, "Send money notifs")
		.addScroll(vars.m_moneymsgs, 0, NUMOF(moneymsgs) - 1, moneymsgs)
		.addFunction([] { Natives::TriggerScriptEvent({ SCRIPTEVENTS::NOTIFICATION, GetSelectedPlayer().m_id, moneymsgs[vars.m_moneymsgs].m_result, moneyamount[vars.m_moneyamount].m_result }, 4, GetSelectedPlayer().m_id); })
		.addTooltip("Send a money specific notif to a player").addTranslation());

	addOption(BreakOption("Give Globals").addTranslation());

	addOption(ToggleOption("Give never wanted")
		.addToggle(GetSelectedPlayer().m_neverWanted)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_neverWanted); })
		.addTooltip("Never wanted [This doesnt show up on their screen]").addTranslation());

	addOption(ToggleOption("Give off the radar")
		.addToggle(GetSelectedPlayer().m_otr)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_otr); })
		.addTooltip("Off the radar").addTranslation());

	addOption(ToggleOption("Give cops turn blind eye")
		.addToggle(GetSelectedPlayer().m_blindEye)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_blindEye); })
		.addTooltip("Cops turn blind eye").addTranslation());

	/*addOption(ToggleOption("dddddddddd")
		.addToggle(GetSelectedPlayer().m_wantedlevelloop)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_wantedlevelloop); })
		.addTooltip("dddddddddd").addTranslation());*/

		/*addOption(BreakOption("Reputation").addTranslation());

		addOption(ButtonOption("Commend for being friendly")
			.addFunction([] {Friendly(GetSelectedPlayer()); })
			.addTooltip("Commend for being friendly").addTranslation()
			.addRequirement([] { return GetAuth()->IsVIP(); }));

		addOption(ButtonOption("Commend for being helpful")
			.addFunction([] {Helpful(GetSelectedPlayer()); })
			.addTooltip("Commend for being helpful").addTranslation()
			.addRequirement([] { return GetAuth()->IsVIP(); }));

		addOption(ButtonOption("Give bad reputation")
			.addFunction([] {BadRep(GetSelectedPlayer()); })
			.addTooltip("Give bad reputation").addTranslation()
			.addRequirement([] { return GetAuth()->IsVIP(); }));*/

			/*addOption(ToggleOption("~g~[Tester]~s~ Give badsport")
				.addToggle(GetSelectedPlayer().m_badsport)
				.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_badsport); })
				.addTooltip("Give badsport (this doesnt work on everyone)").addTranslation()
				.addRequirement([] { return GetAuth()->IsTester(); }));

			addOption(ToggleOption("~g~[Tester]~s~ Remove badsport")
				.addToggle(GetSelectedPlayer().m_removebadsport)
				.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_removebadsport); })
				.addTooltip("Remove badsport (this doesnt work on everyone)").addTranslation()
				.addRequirement([] { return GetAuth()->IsTester(); }));*/
}

/*Update once when submenu is opened*/
void RemoteMenu::UpdateOnce() {}

/*Update while submenu is active*/
void RemoteMenu::Update() {}

/*Background update*/
void RemoteMenu::FeatureUpdate() {
	OnlinePlayerCallback(false, [](SPlayer player) { if (player.m_otr) GOTR(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (player.m_facecamera) FaceCameraForward(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (player.m_neverWanted) GNeverWanted(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (player.m_blindEye) GCopsTurnBlindEye(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (player.m_soundSpam) SoundSpam(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (player.m_displaySpectatingMessage) DisplaySpectatingMessage(player); });
	//OnlinePlayerCallback(false, [](SPlayer player) { if (player.m_transactionSpam) TransactionSpam(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (player.m_badsport) BadSport(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (player.m_removebadsport) RBadSport(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (player.m_wantedlevelloop) WantedLevelRP(player); });

}

/*Singleton*/
RemoteMenu* _instance;
RemoteMenu* RemoteMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new RemoteMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
RemoteMenu::~RemoteMenu() { delete _instance; }