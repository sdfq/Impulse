#include "stdafx.h"
#include "sessionRemote.h"
#include "../allPlayersMenu.h"
#include "../playerList/player/remoteMenu.h"

using namespace SessionRemoteMenuVars;

namespace SessionRemoteMenuVars {
	Vars vars;
}

void SessionRemoteMenu::Init() {
	setParentSubmenu<AllPlayersMenu>();
	setName("Remote", true, true);

	addOption(ButtonOption("Non host kick")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { RemoteMenuVars::NonHostKick(player); }); })
		.addTooltip("Non host kick").addTranslation().addHotkey());

	addOption(ButtonOption("Kick to single player")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { RemoteMenuVars::KickToSingleplayer(player); }); })
		.addTooltip("Kick to single player").addTranslation().addHotkey());

	addOption(ButtonOption("CEO kick")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { RemoteMenuVars::CEOKick(player); }); })
		.addTooltip("CEO kick").addTranslation().addHotkey());

	addOption(ButtonOption("CEO ban")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { RemoteMenuVars::CEOBan(player); }); })
		.addTooltip("CEO ban").addTranslation().addHotkey());

	addOption(BreakOption("Troll").addTranslation());

	addOption(ButtonOption("Infinite loading screen")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { RemoteMenuVars::InfiniteLoadingScreen(player); }); })
		.addTooltip("Infinite loading screen").addTranslation().addHotkey());

	addOption(ToggleOption("Sound spam")
		.addTranslation().addHotkey()
		.addToggle(vars.soundSpam)
		.addTooltip("Sound spam"));

	addOption(ToggleOption("Lock lobbies view to face forward")
		.addTranslation().addHotkey()
		.addToggle(vars.lockview)
		.addTooltip("Lock lobbies view to face forward"));

	addOption(ButtonOption("Gentle kick from vehicle").addTranslation().addHotkey()
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) {  Natives::TriggerScriptEvent({ SCRIPTEVENTS::KICKFROMVEHICLE, player.m_id }, 2, player.m_id); }); })
		.addTooltip("Gently kick the player from his vehicle"));

	addOption(ScrollOption<int>(SCROLLSELECT, "Force into mission").addTranslation()
		.addScroll(vars.m_mission, 0, NUMOF(RemoteMenuVars::missions) - 1, RemoteMenuVars::missions)
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { Natives::TriggerScriptEvent({ SCRIPTEVENTS::FORCEINTOMISSION, player.m_id, RemoteMenuVars::missions[vars.m_mission].m_result }, 3, player.m_id); }); })
		.addTooltip("Force the player into a mission"));

	addOption(BreakOption("Notifications").addTranslation());

	addOption(ToggleOption("Display spectating message")
		.addTranslation().addHotkey()
		.addToggle(vars.spectating)
		.addTooltip("Display spectating message"));

	addOption(ButtonOption("Display insurance message")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { Natives::TriggerScriptEvent({ 380155193, player.m_id, 9999999999 }, 3, player.m_id); }); })
		.addTooltip("This will display an insurance message to the player").addTranslation());

	addOption(ScrollOption<int>(SCROLLSELECT, "Invite notif")
		.addScroll(vars.m_invite, 0, NUMOF(RemoteMenuVars::invites) - 1, RemoteMenuVars::invites)
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { RemoteMenuVars::Invite(player, vars.m_invite); }); })
		.addTooltip("Invite to selection").addTranslation().addHotkey());

	addOption(ScrollOption<int>(SCROLLSELECT, "Send message notifs")
		.addScroll(vars.m_sendmsg, 0, NUMOF(RemoteMenuVars::msgs) - 1, RemoteMenuVars::msgs)
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { Natives::TriggerScriptEvent({ SCRIPTEVENTS::NOTIFICATION, player.m_id, RemoteMenuVars::msgs[vars.m_sendmsg].m_result }, 3, player.m_id); }); })
		.addTooltip("Send messages that are notifications").addTranslation().addHotkey());

	addOption(ButtonOption("Send notif banner").addTranslation().addHotkey()
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) {  Natives::TriggerScriptEvent({ SCRIPTEVENTS::NOTIFICATION, player.m_id, SCRIPTEVENTS::NOTIFICATION2 }, 3, player.m_id); }); })
		.addTooltip("Displays a onscreen banner on players screen"));

	addOption(ScrollOption<int>(SCROLLSELECT, "Send money notif amount")
		.addScroll(vars.m_moneyamount, 0, NUMOF(RemoteMenuVars::moneyamount) - 1, RemoteMenuVars::moneyamount)
		.addTooltip("Change the money amount for the notif function below").addTranslation().addHotkey());

	addOption(ScrollOption<int>(SCROLLSELECT, "Send money notifs")
		.addScroll(vars.m_sendmmsg, 0, NUMOF(RemoteMenuVars::moneymsgs) - 1, RemoteMenuVars::moneymsgs)
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { Natives::TriggerScriptEvent({ SCRIPTEVENTS::NOTIFICATION, player.m_id, RemoteMenuVars::moneymsgs[vars.m_sendmmsg].m_result, RemoteMenuVars::moneyamount[vars.m_moneyamount].m_result }, 4, player.m_id); }); })
		.addTooltip("Send a money specific notif to a player").addTranslation().addHotkey());

	addOption(BreakOption("Give Globals").addTranslation());

	addOption(ToggleOption("Give never wanted")
		.addToggle(vars.gneverWanted)
		.addTranslation().addHotkey()
		.addTooltip("Give Never wanted"));

	addOption(ToggleOption("Give cops turn blind eye")
		.addToggle(vars.gblindEye)
		.addTranslation().addHotkey()
		.addTooltip("Give Cops turn blind eye"));

	addOption(ToggleOption("Give off the radar")
		.addToggle(vars.gotr)
		.addTooltip("Give Off the radar").addTranslation().addHotkey());

	/*addOption(BreakOption("Reputation").addTranslation());

	addOption(ButtonOption("Commend for being friendly")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { RemoteMenuVars::Friendly(player); }); })
		.addTooltip("Commend for being friendly").addTranslation().addHotkey()
		.addRequirement([] { return GetAuth()->IsVIP(); }));

	addOption(ButtonOption("Commend for being helpful")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { RemoteMenuVars::Helpful(player); }); })
		.addTooltip("Commend for being helpful").addTranslation().addHotkey()
		.addRequirement([] { return GetAuth()->IsVIP(); }));

	addOption(ButtonOption("Give bad reputation")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { RemoteMenuVars::BadRep(player); }); })
		.addTooltip("Give bad reputation").addTranslation().addHotkey()
		.addRequirement([] { return GetAuth()->IsVIP(); }));

	addOption(ToggleOption("~g~[Tester]~s~ Give badsport to lobby")
		.addRequirement([] { return GetAuth()->IsTester(); })
		.addTranslation().addHotkey()
		.addToggle(vars.badsportlobby)
		.addTooltip("Give badsport (this doesnt work on everyone)"));

	addOption(ToggleOption("~g~[Tester]~s~ Remove badsport from lobby")
		.addRequirement([] { return GetAuth()->IsTester(); })
		.addTranslation().addHotkey()
		.addToggle(vars.rbadsportlobby)
		.addTooltip("Remove badsport (this doesnt work on everyone)"));*/
}

/*Update once when submenu is opened*/
void SessionRemoteMenu::UpdateOnce() {}

/*Update while submenu is active*/
void SessionRemoteMenu::Update() {}

/*Background update*/
void SessionRemoteMenu::FeatureUpdate() {
	if (vars.soundSpam) {
		OnlinePlayerCallback(false, [](SPlayer player) { RemoteMenuVars::SoundSpam(player); });
	}

	//if (vars.transactionSpam) {
	//	OnlinePlayerCallback(false, [](SPlayer player) { RemoteMenuVars::TransactionSpam(player); });
	//}

	if (vars.spectating) {
		OnlinePlayerCallback(false, [](SPlayer player) { RemoteMenuVars::DisplaySpectatingMessage(player); });
	}

	if (vars.gotr) {
		OnlinePlayerCallback(false, [](SPlayer player) { RemoteMenuVars::GOTR(player); });
	}

	if (vars.gneverWanted) {
		OnlinePlayerCallback(false, [](SPlayer player) { RemoteMenuVars::GNeverWanted(player); });
	}

	if (vars.gblindEye) {
		OnlinePlayerCallback(false, [](SPlayer player) { RemoteMenuVars::GCopsTurnBlindEye(player); });
	}

	if (vars.lockview) {
		OnlinePlayerCallback(false, [](SPlayer player) { RemoteMenuVars::FaceCameraForward(player); });
	}

	if (vars.badsportlobby) {
		OnlinePlayerCallback(false, [](SPlayer player) { RemoteMenuVars::BadSport(player); });
	}

	if (vars.rbadsportlobby) {
		OnlinePlayerCallback(false, [](SPlayer player) { RemoteMenuVars::RBadSport(player); });
	}
}

/*Singleton*/
SessionRemoteMenu* _instance;
SessionRemoteMenu* SessionRemoteMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new SessionRemoteMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
SessionRemoteMenu::~SessionRemoteMenu() { delete _instance; }