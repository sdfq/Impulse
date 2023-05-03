#include "stdafx.h"
#include "menu/submenus/main/protectionMenu.h"
#include "menu/util/playerManager.h"
#include "menu/submenus/main/sessionMenu.h"
#include "menu/submenus/main/protection/eventreactionProtectionMenu.h"
#include "menu/submenus/main/session/playerList/player/remoteMenu.h"
#include "menu/submenus/main/session/playerList/player/griefingMenu.h"
#include "menu/submenus/main/session/playerList/player/playerTeleportMenu.h"
#include "menu/submenus/main/protection/eventreactionProtectionMenu.h"

NetEvent::Vars NetEvent::vars;
int NetEvent::SavedRemoteEventCount;
SavedRemoteEvent NetEvent::SavedRemoteEvents[10];
vector<int64_t> NetEvent::EventsWhitelist = {
3990864803781410816,
-4286753793816657919,
7017282668416298852,
1,
2,
1829532170,
2329576889,
140694592847243,
7881698880275375468,
7595720347004985714,
8243948387464014163,
4926763644075210305,
7957707105777313859,
3979330958639456866,
8022141755484161325,
8103474575570064711,
32778036992894308,
7235440056283916372,
7453016927478510157,
5579477688435830599,
25135171980511560,
24009345357075788,
8029200650131895411,
3558253245324222786,
7598524144786958916,
3905951728,
4252351910,
2523499477550,
7170,
1314698923,
4136296512,
2521346467329,
2508263810,
140698692480831,
3033046699,
4102629104,
457878498,
2513960345,
2994416968,
3853483753,
2523591646504,
129785531,
391525072,
3658665036,
1466368177,
140694538686722,
140694538684418,
140694538688258,
140694538689282,
3041043349,
1965153729070,
2330225949230,
2313046080046,
1947973859886,
3525876967,
3,
4,
14082,
423635655,
1602587606,
1136663604,
2632920828,
1851585574,
3690835919,
4268214959,
724207261,
2462190091688,
2135317668497,
3481834125,
1406900149544,
3448616800,
1250533401,
2353674798,
26872517006543455,
2238396883601,
2879249821,
2154132290094,
7957706001752088947,
2240031636014,
4134704086,
748432205,
2237878625793,
6,
2725362940462,
1963000718849,
1965245898024,
697234677,
693546501,
3530994962,
140694538800386,
3956351571,
8029716235336314698,
7,
8,
2291571243566,
2151979279873,
2154224459048,
140694538759938,
140694538759426,
140694538760194,
71426,
54786,
72194,
140694538756866,
4354,
0,
140694538760450,
58114,
55810,
71682,
65026,
72450,
140694538759682,
1794,
27395,
140694538756354,
140694538755586,
140694538755842,
140694538758146,
70914,
69122,
140694538760706,
140694538759170,
78338,
75010,
140694538756098,
32771,
33027,
33283,
50435,
50947,
34563,
36099,
66819,
15107,
13827,
2521145816579,
25603,
69634,
140694538757122,
71170,
71938,
58370,
73986,
2521145802752,
75778,
9,
10,
56067,
140694538757890,
6001151431224485203,
140694538757634,
140694538756610,
74242,
67586,
4575657221408423941,
13,
1111112300082757653,
1111112300082757656,
1111112300082757647,
1111112300082757636,
1111112300082757644,
4575657221408423943,
4575657221408423956,
4575657221408423939,
4575657221408423952,
4575657221408423938,
4575657221408423946,
11,
12,
2522949749030,
140695585735199,
140697156792238,
2525334477248,
2521145802765,
4294967295,
};

bool moddercheckevents = false;

void SaveRemoteEvent(int64_t* args, int count, int sender) {
	if (NetEvent::SavedRemoteEventCount == 10) NetEvent::SavedRemoteEventCount = 0;
	NetEvent::SavedRemoteEvents[NetEvent::SavedRemoteEventCount].m_count = count;
	for (int i = 0; i < count; i++) {
		NetEvent::SavedRemoteEvents[NetEvent::SavedRemoteEventCount].m_args[i] = args[i];
	}
	NetEvent::SavedRemoteEvents[NetEvent::SavedRemoteEventCount].m_args[1] = sender;
	NetEvent::SavedRemoteEvents[NetEvent::SavedRemoteEventCount].m_redirected = false;
	NetEvent::SavedRemoteEventCount++;
}

typedef bool(*pHandlers)(uint64_t NetEventStruct, CNetGamePlayer* sender, int64_t a3);
typedef void(*pSetupHandlers)(uint64_t NetEventStruct, int64_t a2, CNetGamePlayer* sender, int64_t a4);

typedef bool(__fastcall *pRemoteScriptLeave)(__int64 a1);
pRemoteScriptLeave OriginalRemoteScriptLeave;
bool RemoteScriptLeaveHook(__int64 a1) {
	return 0; // not actually used much in game, we can patch this off outright, fuck wardens.
}

pHandlers OriginalRequestControlEvent;
bool RequestControlEventHook(uint64_t NetEventStruct, CNetGamePlayer* sender, int64_t a3) {
	if (NetEvent::vars.control && NETWORK::NetworkIsSessionActive()) {
		return false;
	}

	//if (NetEvent::vars.smartProtex) return;

	return OriginalRequestControlEvent(NetEventStruct, sender, a3);
}

pSetupHandlers OriginalWeatherChangeEvent;
void WeatherChangeEventHook(uint64_t NetEventStruct, int64_t a2, CNetGamePlayer* sender, int64_t a4) {

	/*auto p1 = *(reinterpret_cast<int*>(NetEventStruct) + 56);
	auto p2 = *(reinterpret_cast<int*>(NetEventStruct) + 60);
	auto p3 = *(reinterpret_cast<int*>(NetEventStruct) + 64);

	LOG_DEBUG("Weather changed! %s %s %s", p1, p2, p3);*/

	//uint64_t WeatherID = *(uint64_t*)(NetEventStruct + 0x3C);
	//int WeatherID2 = *(int*)(NetEventStruct + 0x38);
	//int WeatherID3 = *(int*)(NetEventStruct + 0x3C);
	//int WeatherID4 = *(int*)(NetEventStruct + 0x40);

	////LOG_DEBUG("Weather changed1! %d", WeatherID);
	//LOG_DEBUG("Weather changed2! %i", WeatherID2);
	//LOG_DEBUG("Weather changed3! %i", WeatherID3);
	//LOG_DEBUG("Weather changed4! %i", WeatherID4);

	/*if (WeatherID >= 15 || WeatherID < 0) {
		LOG_PRINT("invalid weather id");
		return;
	}*/

	if (NetEvent::vars.bypassweatherchangequick == true){
		return OriginalWeatherChangeEvent(NetEventStruct, a2, sender, a4);
	}

	if (NetEvent::vars.weatherTime && NETWORK::NetworkIsSessionActive()) {
		return;
	}

	return OriginalWeatherChangeEvent(NetEventStruct, a2, sender, a4);
}

pHandlers OriginalTimeChangeEvent;
bool TimeChangeEventHook(uint64_t NetEventStruct, CNetGamePlayer* sender, int64_t a3) {
	if (NetEvent::vars.weatherTime && NETWORK::NetworkIsSessionActive()) {
		return false;
	}

	return OriginalTimeChangeEvent(NetEventStruct, sender, a3);
}

pSetupHandlers OriginalVoteKickEvent;
void VoteKickEventHook(uint64_t NetEventStruct, int64_t a2, CNetGamePlayer* sender, int64_t a4) {
	Player Sender = sender->m_playerID;

	EventReactionMenuVars::AddPlayer({ sender->PlayerInfo->Name, sender->m_playerID, EventReactionMenuVars::eResponses::NET_EVENT });

	if (NetEvent::vars.voteKick && NETWORK::NetworkIsSessionActive()) {
		if (NetEvent::vars.notifyNE)
			GetRenderer()->NotifyMapColor(va("Network Event: Warning\nFrom: %s\nType: %s", sender->PlayerInfo->Name, "Kick Votes"), 6);

		if (NetEvent::vars.redirectNetEvents) {

			GetRenderer()->NotifyMapColor(va("Vote Kick: Redirecting\nTo: %s", sender->PlayerInfo->Name), 6);

			int64_t arg1[3];
			arg1[0] = -120668417;
			arg1[1] = Sender;
			arg1[2] = 48;
			SaveRemoteEvent(arg1, 3, Sender);

			arg1[0] = 1222825035;
			arg1[2] = 0;
			SaveRemoteEvent(arg1, 2, Sender);

			arg1[0] = 769347061;
			arg1[2] = 0;
			SaveRemoteEvent(arg1, 2, Sender);

			arg1[0] = 999090520;
			arg1[2] = 0;
			SaveRemoteEvent(arg1, 2, Sender);

			arg1[0] = 1642479322;
			arg1[2] = 0;
			SaveRemoteEvent(arg1, 2, Sender);

			arg1[0] = 994306218;
			arg1[2] = 0;
			SaveRemoteEvent(arg1, 2, Sender);

			arg1[0] = -928998106;
			arg1[2] = 0;
			SaveRemoteEvent(arg1, 2, Sender);

			arg1[0] = 1153942884;
			arg1[2] = 0;
			SaveRemoteEvent(arg1, 2, Sender);

		}

		return;
	}

	return OriginalVoteKickEvent(NetEventStruct, a2, sender, a4);
}

pHandlers OriginalWantedLevelEvent;
bool WantedLevelEventHook(uint64_t NetEventStruct, CNetGamePlayer* sender, int64_t a3) {
	if (NetEvent::vars.wantedLevel && NETWORK::NetworkIsSessionActive()) {
		return false;
	}

	//if (NetEvent::vars.smartProtex) return;

	return OriginalWantedLevelEvent(NetEventStruct, sender, a3);
}

pHandlers OriginalClearPedTaskEvent;
bool ClearPedTaskEventHook(uint64_t NetEventStruct, CNetGamePlayer* sender, int64_t a3) {
	SPlayer Sender = GetPlayer(sender->m_playerID);
	CNetEventInfo* Struct = (CNetEventInfo*)NetEventStruct;

	EventReactionMenuVars::AddPlayer({ sender->PlayerInfo->Name, sender->m_playerID, EventReactionMenuVars::eResponses::NET_EVENT });

	if (NetEvent::vars.clearTasks && NETWORK::NetworkIsSessionActive()) {
		if (NetEvent::vars.notifyNE)
			GetRenderer()->NotifyMapColor(va("Network Event: Blocked\nFrom: %s\nType: %s", sender->PlayerInfo->Name, "Clear Tasks"), 6, false);

		if (NetEvent::vars.redirectNetEvents) {
			GetRenderer()->NotifyMapColor(va("Clear Tasks: Redirecting\nTo: %s", sender->PlayerInfo->Name), 6, false);
			BRAIN::ClearPedTasksImmediately(Sender.m_ped);
		}

		return false;
	}

	//if (NetEvent::vars.smartProtex) return;

	return OriginalClearPedTaskEvent(NetEventStruct, sender, a3);
}

pSetupHandlers OriginalRemoveAllWeaponsEvent;
void RemoveAllWeaponsEventHook(uint64_t NetEventStruct, int64_t a2, CNetGamePlayer* sender, int64_t a4) {

	EventReactionMenuVars::AddPlayer({ sender->PlayerInfo->Name, sender->m_playerID, EventReactionMenuVars::eResponses::NET_EVENT });

	if (NetEvent::vars.takeWeapons && NETWORK::NetworkIsSessionActive()) {
		if (NetEvent::vars.notifyNE)
			GetRenderer()->NotifyMapColor(va("Network Event: Blocked\nFrom: %s\nType: %s", sender->PlayerInfo->Name, "Remove All Weapons"), 6, false);
		return;
	}

	//if (NetEvent::vars.smartProtex) return;

	return OriginalRemoveAllWeaponsEvent(NetEventStruct, a2, sender, a4);
}

pSetupHandlers OriginalRemoveWeaponEvent;
void RemoveWeaponEventHook(uint64_t NetEventStruct, int64_t a2, CNetGamePlayer* sender, int64_t a4) {

	EventReactionMenuVars::AddPlayer({ sender->PlayerInfo->Name, sender->m_playerID, EventReactionMenuVars::eResponses::NET_EVENT });

	if (NetEvent::vars.takeWeapons && NETWORK::NetworkIsSessionActive()) {
		if (NetEvent::vars.notifyNE)
			GetRenderer()->NotifyMapColor(va("Network Event: Blocked\nFrom: %s\nType: %s", sender->PlayerInfo->Name, "Remove Weapon"), 6, false);
		return;
	}

	//if (NetEvent::vars.smartProtex) return;

	return OriginalRemoveWeaponEvent(NetEventStruct, a2, sender, a4);
}

pSetupHandlers OriginalGiveWeaponEvent;
void GiveWeaponEventHook(uint64_t NetEventStruct, int64_t a2, CNetGamePlayer* sender, int64_t a4) {
	SPlayer Sender = GetPlayer(sender->m_playerID);

	EventReactionMenuVars::AddPlayer({ sender->PlayerInfo->Name, sender->m_playerID, EventReactionMenuVars::eResponses::NET_EVENT });

	if (NetEvent::vars.giveWeapons && NETWORK::NetworkIsSessionActive()) {

		if (NetEvent::vars.notifyNE)
			GetRenderer()->NotifyMapColor(va("Network Event: Blocked\nFrom: %s\nType: %s", sender->PlayerInfo->Name, "Give Weapon"), 6, false);

		if (NetEvent::vars.redirectNetEvents) {
			GetRenderer()->NotifyMapColor(va("Give Weapon: Redirecting\nTo: %s", sender->PlayerInfo->Name), 6);
			WEAPON::GiveWeaponToPed(Sender.m_ped, *(Hash*)(NetEventStruct + 0x34), *(DWORD*)(NetEventStruct + 0x38), false, false);
		}

		return;
	}

	//if (NetEvent::vars.smartProtex) return;

	return OriginalGiveWeaponEvent(NetEventStruct, a2, sender, a4);
}

pHandlers OriginalExplosionEvent;
bool ExplosionEventHook(uint64_t NetEventStruct, CNetGamePlayer* sender, int64_t a3) {
	CNetEventInfo* Struct = (CNetEventInfo*)NetEventStruct;

	auto ExpType = *(int*)(NetEventStruct + 0xD8);

	if (NetEvent::vars.explosions && NETWORK::NetworkIsSessionActive()) {
		return false;
	}

	return OriginalExplosionEvent(NetEventStruct, sender, a3);
}

pHandlers OriginalFireEvent;
bool FireEventHook(uint64_t NetEventStruct, CNetGamePlayer* sender, int64_t a3) {
	if (NetEvent::vars.explosions && NETWORK::NetworkIsSessionActive()) {
		return false;
	}

	return OriginalFireEvent(NetEventStruct, sender, a3);
}

pHandlers OriginalPTFXEvent;
bool PTFXEventHook(uint64_t NetEventStruct, CNetGamePlayer* sender, int64_t a3) {
	if (NetEvent::vars.particleEffects && NETWORK::NetworkIsSessionActive()) {
		return false;
	}

	return OriginalPTFXEvent(NetEventStruct, sender, a3);
}

pHandlers OriginalPlaySoundEvent;
bool PlaySoundEventHook(uint64_t NetEventStruct, CNetGamePlayer* sender, int64_t a3) {
	if (NetEvent::vars.sound && NETWORK::NetworkIsSessionActive()) {
		return false;
	}

	return OriginalPlaySoundEvent(NetEventStruct, sender, a3);
}

pSetupHandlers OriginalScriptEvent;
void ScriptEventHook(uint64_t NetEventStruct, int64_t a2, CNetGamePlayer* sender, int64_t a4) {
	if (NetEvent::vars.ePqGPRWkeLpOicfiJfNO) {
		int64_t* ScriptEventArgs = (int64_t*)(NetEventStruct + 0x3E4); //1.46 0x334
		LOG_PRINT("%s: %lli, %lli, %lli, %lli, %lli", sender->PlayerInfo->Name, ScriptEventArgs[0], ScriptEventArgs[1], ScriptEventArgs[2], ScriptEventArgs[3], ScriptEventArgs[4]);
		return;
	}

	int64_t* arguments = (int64_t*)(NetEventStruct + 0x3E4); //1.46 0x334
	Player Sender = sender->m_playerID;
	const char* ReportReason = nullptr;
	int result = 1;
	const char* PlayerName = PLAYER::GetPlayerName(Sender);

	if (arguments[0] == SCRIPTEVENTS::START_TYPING)
	{
		GetPlayerManager()->AddTyping(Sender);
	}
	else if (arguments[0] == SCRIPTEVENTS::STOP_TYPING)
	{
		GetPlayerManager()->RemoveTyping(Sender);
	}

	if (arguments[0] == SCRIPTEVENTS::PAUSE_ENTER)
	{
		GetPlayerManager()->AddPaused(Sender);
	}
	else if (arguments[0] == SCRIPTEVENTS::PAUSE_LEAVE)
	{
		GetPlayerManager()->RemovePaused(Sender);
	}

	if (arguments[0] == SCRIPTEVENTS::JOINED_PLAYER)
	{
		if (SessionMenuVars::vars.warnonplayerjoin)
		{
			GetRenderer()->NotifyMap(va("%s is joining the game...", PLAYER::GetPlayerName(Sender)));
		}
	}

	if (GetPlayer(sender->m_playerID).m_isEvolveStaff) {
		return OriginalScriptEvent(NetEventStruct, a2, sender, a4);
	}

	if ((NetEvent::vars.scriptEvents || NetEvent::vars.smartProtex) && NETWORK::NetworkIsSessionActive())
	{
		// regular system
		if (Sender < 32 && Sender > -1)
		{
			switch (arguments[0])
			{
			case SCRIPTEVENTS::ECLIPSETELEPORT:
				if (arguments[2] == 0 && arguments[3] == 0 && arguments[4] == 0 && arguments[5] == 0)
				{
					ReportReason = "Infinite Loading Screen";
					moddercheckevents = true;
					result = 0;
				}
				else if (arguments[2] == 0 && arguments[3] == 0 && arguments[4] != 0)
				{
					ReportReason = "Remote Teleport";
					moddercheckevents = true;
					result = 0;
				}
				break;

			case SCRIPTEVENTS::CEOBAN:
					ReportReason = "Ban From Ceo";
					moddercheckevents = true;
					result = 0;
				break;

			case SCRIPTEVENTS::CEOKICK:
					ReportReason = "Kick From Ceo";
					moddercheckevents = true;
					result = 0;
				break;

			case SCRIPTEVENTS::FORCEINTOMISSION:
				ReportReason = "Force Into Event";
				moddercheckevents = true;
				result = 0;
				break;

			case SCRIPTEVENTS::GOTR:
				ReportReason = "Off The Radar";
				moddercheckevents = true;
				result = 0;
				break;

			case SCRIPTEVENTS::GCOPSTURNBLINDEYE:
				ReportReason = "Cops Turn Blind Eye";
				moddercheckevents = true;
				result = 0;
				break;

			case SCRIPTEVENTS::GNEVERWANTED:
				ReportReason = "Never Wanted";
				moddercheckevents = true;
				result = 0;
				break;

			case SCRIPTEVENTS::KICKFROMVEHICLE:
				ReportReason = "Gentle Kick From Vehicle";
				moddercheckevents = true;
				result = 0;
				break;

			case SCRIPTEVENTS::DISPLAYINSURANCEMESSAGE:
				ReportReason = "Insurance Fraud Spam";
				moddercheckevents = true;
				result = 0;
				break;

			case SCRIPTEVENTS::TRANSACTIONERRORSPAM:
				if (arguments[2] >= 10000) {
					ReportReason = "Transaction Spam";
					moddercheckevents = true;
					result = 0;
				}
				break;

			case SCRIPTEVENTS::FACECAMERAFORWARD:
				if (arguments[2] == SCRIPTEVENTS::FACECAMERAFORWARD2) {
					ReportReason = "Reset Cam";
					moddercheckevents = true;
					result = 0;
				}
				break;

			case 1513464838:
				result = 0;
				break;

			case -679747935:
				ReportReason = "Bounty";
				//moddercheckevents = true;
				result = 0;
				break;

			case 729971264:
				result = 0;
				break;

			case SCRIPTEVENTS::NONHOSTKICK1:
				//ReportReason = "Non Host Kick 1";
				//moddercheckevents = true;
				result = 0;
				break;

			case SCRIPTEVENTS::NONHOSTKICK2:
				//ReportReason = "Non Host Kick 2";
				//moddercheckevents = true;
				result = 0;
				break;

			case SCRIPTEVENTS::NONHOSTKICK3:
				ReportReason = "Non Host Kick 3";
				//moddercheckevents = true;
				result = 0;
				break;

			case SCRIPTEVENTS::NONHOSTKICK4:
				ReportReason = "Non Host Kick 4";
				//moddercheckevents = true;
				result = 0;
				break;

			case SCRIPTEVENTS::NONHOSTKICK5:
				ReportReason = "Non Host Kick 5";
				//moddercheckevents = true;
				result = 0;
				break;

			case SCRIPTEVENTS::NONHOSTKICK6:
				ReportReason = "Non Host Kick 6";
				//moddercheckevents = true;
				result = 0;
				break;

			case SCRIPTEVENTS::KICKTOSP1:
				ReportReason = "Kick to Singleplayer 1";
				//moddercheckevents = true;
				result = 0;
				break;

			case SCRIPTEVENTS::KICKTOSP2:
				//ReportReason = "Kick to Singleplayer 2";
				//moddercheckevents = true;
				result = 0;
				break;

			case SCRIPTEVENTS::KICKTOSP3:
				ReportReason = "Kick to Singleplayer 3";
				//moddercheckevents = true;
				result = 0;
				break;

			case 769347061: //Non Host Kick
			case 999090520: //Non Host Kick 
			case 1642479322://Non Host Kick
			case 994306218://Non Host Kick
			case 928998106://Non Host Kick
			case 2055958901://Non Host Kick
			case 256346004:
			case -1662909539:
			case -4156321:
			case 964496014:
			case 813647057:
			case -1996885757:
			case 1178932519:
			case -1184085326:
			case 2021867503:
			case 1586576930:
			case -12899832505:
			case -2136787743:
			case 27391769:
			case -1835749229: // new kicks from here 
			case 4174298879:
			case 2632057757:
			case 4290810975:
			case 2298081539:
			case 3110881970:
			case 4280036679:
			case 2158179553:
				//ReportReason = "Non Host Kick";
				result = 0;
				break;
			}
		}
	}

	if (ReportReason != nullptr && NetEvent::vars.notifySE)
	{
#ifdef HARD_DEV
		GetRenderer()->NotifyMapColor(va("Script Event: %d\nFrom: %s\nType: %s", arguments[0], PlayerName, ReportReason), 6);
#endif
#ifndef HARD_DEV
		GetRenderer()->NotifyMapColor(va("Script Event: Blocked\nFrom: %s\nType: %s", PlayerName, ReportReason), 6);
#endif
	}

	// if it has not be blocked yet
	bool ShouldRedirect = false;
	if (Sender < 32 && Sender > -1)
	{
		if (NetEvent::vars.smartProtex && result != 0)
		{
			// smart system
			bool found = false;
			for (int64_t e : NetEvent::EventsWhitelist)
			{
				if (e == arguments[0])
				{
					found = true;
				}
			}
			if (!found)
			{
#ifdef HARD_DEV
				/*if (NetEvent::vars.notify)
				{
					GetRenderer()->NotifyMapColor(va("[DEV] Script Event: %d\nFrom: %s\nType: %s", arguments[0], PlayerName, "Smart Filter"), 6);
				}*/
#endif
				ShouldRedirect = true;
				result = 0; // block unknown events ~Big dick guy
			}
		}
	}

	if (ReportReason == "Non Host Kick")
	{
		//GetRenderer()->NotifyMap(va("%s is modding. \nReason: %s", PlayerName, ReportReason), true);
		GetPlayerManager()->AddModding(Sender);
		EventReactionMenuVars::AddPlayer({ const_cast<char*>(PlayerName), Sender, EventReactionMenuVars::eResponses::KICK });
	}
	else if (ReportReason != nullptr)
	{
		//GetRenderer()->NotifyMap(va("%s is modding. \nReason: %s", PlayerName, ReportReason), true);
		GetPlayerManager()->AddModding(Sender);
		EventReactionMenuVars::AddPlayer({ const_cast<char*>(PlayerName), Sender, EventReactionMenuVars::eResponses::MALICIOUS });
	}

	if ((ReportReason != nullptr && NetEvent::vars.redirectScriptEvents) || ShouldRedirect)
	{
		SaveRemoteEvent(arguments, 10, sender->m_playerID);
	}

	if (NetEvent::vars.blockallncriptevents && NETWORK::NetworkIsSessionActive())
	{
		result = 0;
	}

	if (result)
	{
		return OriginalScriptEvent(NetEventStruct, a2, sender, a4);
	}
	else
	{
		return;
	}
}

//void GetEventDataHook(NativeContext* cxt) {
//
//#ifdef HARD_DEV
//	int64_t* arr = cxt->getArgument<int64_t*>(2);
//
//	printf("SE: %i, %i, %i, %i, %i, %i, %i, %i, %i, %i\n", arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7], arr[8], arr[9]);
//#endif
//
//	SCRIPT::GetEventData(cxt->getArgument<int>(0), cxt->getArgument<int>(1), cxt->getArgument<int64_t*>(2), cxt->getArgument<int>(3));
//}

unsigned int reportStatHashArray[] = {
	0x9C6A0C42,
	0x3CDB43E2,
	0x0E8FB6DD5,
	0x0F3DE4879,
	0x0CBFD04A4,
	0x9F79BA0B,
	0x62EB8C5A,
	0x0E7072CD,
	0x762F9994,
	0x0B722D6C0,
	0x0DAFB10F9,
	0x893E1390,
	0x6D7F0859
};
bool IsHashReportOrCommends(int a1) {
	for (int i = 0; i < 13; i++) {
		if (a1 == reportStatHashArray[i])
			return true;
	}

	return false;
}

typedef bool(*tNetworkIncrementStatEvent)(uint64_t, uint64_t);
tNetworkIncrementStatEvent OriginalNetworkIncrementStatEvent;
bool NetworkIncrementStatEventHook(uint64_t a1, uint64_t a2) {
	if (NetEvent::vars.stat && NETWORK::NetworkIsSessionActive()) {
		Hash stat = *(Hash*)(a1 + 0x30);
		bool block = false;
		switch (stat) {
		case 0x9C6A0C42:
			block = true;
			break;
		case 0xCBFD04A4:
			block = true;
			break;
		case 0x9F79BA0B:
			block = true;
			break;
		case 0xEC3CE96A:
			block = true;
			break;
		case 0x62EB8C5A:
			block = true;
			break;
		case 0x0E7072CD:
			block = true;
			break;
		case 0x762F9994:
			block = true;
			break;
		case 0xB722D6C0:
			block = true;
			break;
		}
		if (block) {
			return true;
		}
	}

	return OriginalNetworkIncrementStatEvent(a1, a2);
}

pHandlers OriginalHandleIncrementStatEvent;
bool HandleIncrementStatEventHook(uint64_t NetEventStruct, CNetGamePlayer* sender, int64_t a3) {
	Hash stat = *(Hash*)(NetEventStruct + 0x30);
	SPlayer* Sender = &GetPlayer(sender->m_playerID);

	EventReactionMenuVars::AddPlayer({ sender->PlayerInfo->Name, sender->m_playerID, EventReactionMenuVars::eResponses::REPORT });

	//LOG_PRINT("IncrementStat Detected Type: %i", *(int*)(NetEventStruct + 0x34));
	//LOG_PRINT("IncrementStat hash: 0x%X", stat);

	//if (!IsHashReportOrCommends(stat)) {
	//	if (stat == 0x6BE2DC59) { //0x6BE2DC59 = meghasasmallpeen
	//	switch (*(int*)(NetEventStruct + 0x34)) {
	//	case 1: Sender->m_isEvolveUserBlock = true; break;
	//	case 2: Sender->m_isEvolveUserBlock = false; break;
	//	case 3: Sender->m_isEvolveUser = true; break;
	//	case 4: Sender->m_isEvolveUser = false; break;
	//	case 5: Sender->m_isEvolveStaff = true; break;
	//	case 6: Sender->m_isEvolveStaff = false; break;
	//	case 7: Sender->m_isEvolveVIP = true; break;
	//	case 8: Sender->m_isEvolveVIP = false; break;
	//		}
	//	}
	//	return true;
	//}

	if (NetEvent::vars.stat && NETWORK::NetworkIsSessionActive()) {
		bool block = false;
		const char* statReason = NULL;

		switch (stat) {
		case 0x9C6A0C42:
			statReason = "Griefing";
			block = true;
			break;
		case 0xCBFD04A4:
			statReason = "Using Game Exploits";
			block = true;
			break;
		case 0x9F79BA0B:
			statReason = "Using Exploits";
			block = true;
			break;
		case 0xEC3CE96A:
			statReason = "Being a Cheater";
			block = true;
			break;
		case 0x62EB8C5A:
			statReason = "Being Annoying In VC";
			block = true;
			break;
		case 0x0E7072CD:
			statReason = "Being Hateful In VC";
			block = true;
			break;
		case 0x762F9994:
			statReason = "Being Annoying In Text Chat";
			block = true;
			break;
		case 0xB722D6C0:
			statReason = "Being Hateful In Text Chat";
			block = true;
			break;
		}

		if (block && statReason != NULL) {
			if (NetEvent::vars.notifyNE) {
				GetRenderer()->NotifyMapColor(va("Stat Event: Warning\nFrom: %s\nType: %s", sender->PlayerInfo->Name, statReason), 6);
			}
		}

		if (block) {
			return true;
		}


	}
	return OriginalHandleIncrementStatEvent(NetEventStruct, sender, a3);
}

typedef void(__fastcall *tGetModelInfo)(uint32_t hash, WORD* data);
tGetModelInfo GetModelInfo = (tGetModelInfo)((uint64_t)GetModuleHandle(0) + 0x15F09A0);

typedef __int64(*pNetObjEntityManageEntity)(int, BYTE, int, int);
pNetObjEntityManageEntity OriginalNetObjEntityManagePickup;
__int64 NetObjEntityManagePickupHook(int ecx, BYTE dl, int r8d, int r9d) {
	if (NetEvent::vars.pickups && NETWORK::NetworkIsSessionActive()) {
		/*if (NetEvent::vars.notify) {
			GetRenderer()->NotifyMapColor(va("Pickup: Blocked\nFrom: %s", GetPlayer(dl).m_name), 6);
		}*/
		return 0;
	}
	return OriginalNetObjEntityManagePickup(ecx, dl, r8d, r9d);
}

pNetObjEntityManageEntity OriginalNetObjEntityManagePed;
__int64 NetObjEntityManagePedHook(int ecx, BYTE dl, int r8d, int r9d) {

	if (NetEvent::vars.blockpednet && NETWORK::NetworkIsSessionActive()) {
		/*if (NetEvent::vars.notify) {
			GetRenderer()->NotifyMapColor(va("Ped: Blocked\nFrom: %s", GetPlayer(dl).m_name), 6);
		}*/
		return 0;
	}
	return OriginalNetObjEntityManagePed(ecx, dl, r8d, r9d);
}

pNetObjEntityManageEntity OriginalNetObjEntityManageObject;
__int64 NetObjEntityManageObjectHook(int ecx, BYTE dl, int r8d, int r9d) {
	if (NetEvent::vars.blockobjectnet && NETWORK::NetworkIsSessionActive()) {
		//if (NetEvent::vars.notify) {
		//	GetRenderer()->NotifyMapColor(va("Object: Blocked\nFrom: %s", GetPlayer(dl).m_name), 6);
		//}
		return 0;
	}
	return OriginalNetObjEntityManageObject(ecx, dl, r8d, r9d);
}

///////

pNetObjEntityManageEntity OriginalNetObjEntityManageHeliHook;
__int64 NetObjEntityManageHeliHook(int ecx, BYTE dl, int r8d, int r9d) {
	if (NetEvent::vars.blockhelinet && NETWORK::NetworkIsSessionActive()) {
		//if (NetEvent::vars.notify) {
		//	GetRenderer()->NotifyMapColor(va("Object: Blocked\nFrom: %s", GetPlayer(dl).m_name), 6);
		//}
		return 0;
	}
	return OriginalNetObjEntityManageHeliHook(ecx, dl, r8d, r9d);
}

pNetObjEntityManageEntity OriginalNetObjEntityManageBikeHook;
__int64 NetObjEntityManageBikeHook(int ecx, BYTE dl, int r8d, int r9d) {
	if (NetEvent::vars.blockbikenet && NETWORK::NetworkIsSessionActive()) {
		//if (NetEvent::vars.notify) {
		//	GetRenderer()->NotifyMapColor(va("Object: Blocked\nFrom: %s", GetPlayer(dl).m_name), 6);
		//}
		return 0;
	}
	return OriginalNetObjEntityManageBikeHook(ecx, dl, r8d, r9d);
}

pNetObjEntityManageEntity OriginalNetObjEntityManageAutomobileHook;
__int64 NetObjEntityManageAutomobileHook(int ecx, BYTE dl, int r8d, int r9d) {
	if (NetEvent::vars.blockautomobilenet && NETWORK::NetworkIsSessionActive()) {
		//if (NetEvent::vars.notify) {
		//	GetRenderer()->NotifyMapColor(va("Object: Blocked\nFrom: %s", GetPlayer(dl).m_name), 6);
		//}
		return 0;
	}
	return OriginalNetObjEntityManageAutomobileHook(ecx, dl, r8d, r9d);
}

pNetObjEntityManageEntity OriginalNetObjEntityManagePickupPlacementHook;
__int64 NetObjEntityManagePickupPlacementHook(int ecx, BYTE dl, int r8d, int r9d) {
	if (NetEvent::vars.pickups && NETWORK::NetworkIsSessionActive()) {
		//if (NetEvent::vars.notify) {
		//	GetRenderer()->NotifyMapColor(va("Object: Blocked\nFrom: %s", GetPlayer(dl).m_name), 6);
		//}
		return 0;
	}
	return OriginalNetObjEntityManagePickupPlacementHook(ecx, dl, r8d, r9d);
}

pNetObjEntityManageEntity OriginalNetObjEntityManagePlaneHook;
__int64 NetObjEntityManagePlaneHook(int ecx, BYTE dl, int r8d, int r9d) {
	if (NetEvent::vars.blockplanenet && NETWORK::NetworkIsSessionActive()) {
		//if (NetEvent::vars.notify) {
		//	GetRenderer()->NotifyMapColor(va("Object: Blocked\nFrom: %s", GetPlayer(dl).m_name), 6);
		//}
		return 0;
	}
	return OriginalNetObjEntityManagePlaneHook(ecx, dl, r8d, r9d);
}

#define NetObjCount 200

enum eNetObjType {
	NetObjObject = 0x42A00000,
	NetObjPed = 0x42F00000,
	NetObjVehicle = 0x43960000,
	NetObjFlyingVehicle = 0x43FA0000,
	NetObjDoor = 0x42960000,
	NetObjPickup = 0x42480000,
	NetObjPickupPlacement = 0x43160000,
	NetObjTrain = 0x44480000,
	NetObjPlayer = 0x447A0000
};

int SavedNetObjCount = 0;
struct SavedNetObj {
	int ID;
	Player Owner;
} SavedNetObjs[NetObjCount];

//static bool IsNetObjSaved(int NetID, Player* Owner);
bool IsNetObjSaved(int NetID, Player* Owner) {
	for (int i = 0; i < NetObjCount; i++) {
		if (SavedNetObjs[i].ID == NetID) {
			if (Owner != NULL) *Owner = SavedNetObjs[i].Owner;
			return true;
		}
	}
	return false;
}

int GetEntityNetID(Entity entity) {
	uint64_t EntityStruct = PoolManager::GetEntityAddress(entity);
	if (EntityStruct != 0) {
		uint64_t NetObjStruct = *(uint64_t*)(EntityStruct + 0xD0);
		if (NetObjStruct != 0) return *(int*)(NetObjStruct + 0xA);
	}
	return -1;
}

void SaveNetObj(int NetID, Player Owner) {
	if (SavedNetObjCount == NetObjCount) SavedNetObjCount = 0;
	SavedNetObjs[SavedNetObjCount].ID = NetID;
	SavedNetObjs[SavedNetObjCount].Owner = Owner;
	SavedNetObjCount++;
	//LOG_PRINT("Saved Net Obj From %s", GetPlayer(Owner).m_name);
}

typedef void(*pRecieveNetworkObject)(uint64_t rcx, int64_t NetObjectStruct);
pRecieveNetworkObject OriginalRecieveNetworkObject;
void RecieveNetworkObjectHook(uint64_t rcx, int64_t NetObjectStruct) {
	Player Sender = *(uint8_t*)(NetObjectStruct + 0x49);

	if (Sender != GetLocalPlayer().m_id) {
		int NetObjID = *(int*)(NetObjectStruct + 0xA);
		eNetObjType Type = (eNetObjType)*((int* (*)())(void*)*(uint64_t*)(*(uint64_t*)NetObjectStruct + 0xE0))();

		//LOG_PRINT("[RNO] Type: 0x%X, ID: %i, Sender: %s", Type, NetObjID, GetPlayer(Sender).m_name);

		if (Type == NetObjObject || Type == NetObjPed || Type == NetObjVehicle) {
			if (!IsNetObjSaved(NetObjID)) {
				SaveNetObj(NetObjID, Sender);
			}
		}
	}
	return OriginalRecieveNetworkObject(rcx, NetObjectStruct);
}



typedef bool(__fastcall *tAttemptToSpawnProp)(DWORD64 a1, DWORD64 data);
tAttemptToSpawnProp oAttemptToSpawnProp;
bool AttemptToSpawnOnlineProp(DWORD64 a1, DWORD64 data) {
	Hash prop = *(unsigned int*)(data + 0x140);
	switch (prop) {
	case 0xfbf7d21f:
	case 0x6d1bb815:
	case 0x9CF21E0F:
	case 0x34315488:
	case 0x6A27FEB1:
	case 0xCB2ACC8:
	case 0xC6899CDE:
	case 0xD14B5BA3:
	case 0xD9F4474C:
	case 0x32A9996C:
	case 0x69D4F974:
	case 0xCAFC1EC3:
	case 0x79B41171:
	case 0x1075651:
	case 0xC07792D4:
	case 0x781E451D:
	case 0x762657C6:
	case 0xC2E75A21:
	case 0xC3C00861:
	case 0x81FB3FF0:
	case 0x45EF7804:
	case 0xE65EC0E4:
	case 0xE764D794:
	case 0xE1AEB708:
	case 0xA5E3D471:
	case 0xD971BBAE:
	case 0xCF7A9A9D:
	case 0xC2CC99D8:
	case 0x8FB233A4:
	case 0x24E08E1F:
	case 0x337B2B54:
	case 0xB9402F87:
	case 0x4F2526DA:
		#ifdef HARD_DEV
		printf("Prevented a prop crash\n");
		#endif
		return false;
		break;
	default:
		return oAttemptToSpawnProp(a1, data);
	}
}

tAttemptToSpawnProp oAttemptToSpawnPed;
bool AttemptToSpawnOnlinePed(DWORD64 a1, DWORD64 data) {
	Hash ped = *(unsigned int*)(data + 0xC4);
	switch (ped) {
	case 0x3f039cba: // slod
	case 0x856CFB02: // slod
	case 0x2D7030F3: // slod
	case 0xB881AEE:
	case 0x8D8F1B10:
	case 0x613e626c:
		#ifdef HARD_DEV
		printf("Prevented a ped crash\n");
		#endif
		return false;
		break;
	default:
		return oAttemptToSpawnPed(a1, data);
	}
}

//UINT64 ScriptEventHandlerOP;
//void ScriptEventHandlerHook(UINT64 NetStruct, UINT64 p1, UINT64 SenderStruct) {
//	if (NetEvent::vars.allScriptEventstest2) { // && Backend::NetworkIsInSession()
//		return;
//	}
//
//	int SenderID = (int)*(char*)(SenderStruct + 0x2D);
//	uint64_t* ScriptEventArgs = (uint64_t*)(NetStruct + 0x334);
//
//	return ScriptEventHandlerOP(NetStruct, p1, SenderStruct);
//}


//UINT64 ScriptEventHandlerCallerAddress;
//UINT64* ScriptEventHandlerOP = NULL;
//void ScriptEventHandlerHook(UINT64 NetStruct, UINT64 p1, UINT64 SenderStruct) {
//	if (ProtectionMenuVars::vars.allScriptEvents2) {
//		return;
//	}
//		((void(*)(UINT64 NetStruct, UINT64 p1, UINT64 SenderStruct))ScriptEventHandlerCallerAddress)(NetStruct, p1, SenderStruct);
//}

typedef void(*tCallNetworkEventCallback)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
tCallNetworkEventCallback OriginalCallNetworkEventCallback;
void CallNetworkEventCallbackHook(uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5, uint64_t a6, uint64_t a7, uint64_t a8) {
	//auto id = *(byte*)(a2 + 8); /* event id */
	//auto senderID = *(byte*)(a4 + 0x2D); /* cnetgameplayer */
	//bool AllowEvent = true;


	//	switch (id) {
	//	case GAME_CLOCK_EVENT:
	//		AllowEvent = !ProtectionMenuVars::vars.gameclock;
	//		break;

	//	case KICK_VOTES_EVENT:
	//		AllowEvent = !NetEvent::vars.voteKick;
	//		break;

	//	case REQUEST_CONTROL_EVENT:
	//		AllowEvent = !NetEvent::vars.control;
	//		break;

	//	case ALTER_WANTED_LEVEL_EVENT:
	//		AllowEvent = !NetEvent::vars.wantedLevel;
	//		break;

	//	case NETWORK_CLEAR_PED_TASKS_EVENT:
	//		AllowEvent = !NetEvent::vars.clearTasks;
	//		break;

	//	case REMOVE_ALL_WEAPONS_EVENT:
	//	case REMOVE_WEAPON_EVENT:
	//		AllowEvent = !NetEvent::vars.takeWeapons;
	//		break;

	//	case GIVE_WEAPON_EVENT:
	//		AllowEvent = !NetEvent::vars.giveWeapons;
	//		break;

	//	case FIRE_EVENT:
	//	case EXPLOSION_EVENT:
	//		AllowEvent = !NetEvent::vars.explosions;
	//		break;

	//	case NETWORK_PTFX_EVENT:
	//		AllowEvent = !NetEvent::vars.particleEffects;
	//		break;

	//	case NETWORK_PLAY_SOUND_EVENT:
	//	case NETWORK_STOP_SOUND_EVENT:
	//		AllowEvent = !NetEvent::vars.sound;
	//		break;

	//	/*case SCRIPTED_GAME_EVENT:
	//		uint64_t * ScriptEventArgs = (uint64_t*)(a2 + 0x334);
	//		LOG_DEBUG("%s: %d, %d, %d, %d, %d", PLAYER::GetPlayerName(senderID), ScriptEventArgs[0], ScriptEventArgs[1], ScriptEventArgs[2], ScriptEventArgs[3], ScriptEventArgs[4]);
	//		break;*/
	//	}


	//if (!AllowEvent) {
	//	return;
	//}

	//if (NetEvent::vars.blockallncriptevents) {
	//	return;
	//}

	OriginalCallNetworkEventCallback(a1, a2, a3, a4, a5, a6, a7, a8);
}

typedef void(*pEventsHandler)(int64_t event_manager, CNetGamePlayer* pSender, CNetGamePlayer* pTarget, uint16_t event_id, int32_t event_index, int32_t event_handled_bitset, int64_t bitbuffer_size, int64_t bitbuffer);
pEventsHandler OriginalEventsHandler = nullptr;
void EventsHandlerHook(int64_t event_manager, CNetGamePlayer* pSender, CNetGamePlayer* pTarget, uint16_t event_id, int32_t event_index, int32_t event_handled_bitset, int64_t bitbuffer_size, int64_t bitbuffer)
{
	Player player = pSender->m_playerID;
	string playerName = PLAYER::GetPlayerName(player);

	OriginalEventsHandler(event_manager, pSender, pTarget, event_id, event_index, event_handled_bitset, bitbuffer_size, bitbuffer);
}

typedef int64_t(*pGetEventData)(int32_t eventGroup, int32_t eventIndex, int64_t* arguments, uint32_t argStructSize);
pGetEventData OriginalGetEventData;
int64_t GetEventDataHook(int32_t eventGroup, int32_t eventIndex, int64_t* arguments, uint32_t argStructSize)
{
	int64_t result = OriginalGetEventData(eventGroup, eventIndex, arguments, argStructSize);

	Player Sender = arguments[1];
	const char* PlayerName = PLAYER::GetPlayerName(Sender);
	const char* ReportReason = nullptr;

	if (Sender < 32 && Sender > -1)
	{
		// Log only player events
		/*if (NetEvent::vars.ePqGPRWkeLpOicfiJfNO)
		{
			printf_s("%s [EVENTLOG] %s: ", GetLog()->GetTimeAsString(), PlayerName);
			for (auto i = 0; i < argStructSize; i++)
			{
				printf_s("%d, ", arguments[i]);
			}
			result = 0;
		}*/
	}
	
	if (arguments[0] == SCRIPTEVENTS::START_TYPING)
	{
		GetPlayerManager()->AddTyping(Sender);
	}
	else if (arguments[0] == SCRIPTEVENTS::STOP_TYPING)
	{
		GetPlayerManager()->RemoveTyping(Sender);
	}

	if (arguments[0] == SCRIPTEVENTS::PAUSE_ENTER)
	{
		GetPlayerManager()->AddPaused(Sender);
	}
	else if (arguments[0] == SCRIPTEVENTS::PAUSE_LEAVE)
	{
		GetPlayerManager()->RemovePaused(Sender);
	}

	if (arguments[0] == SCRIPTEVENTS::JOINED_PLAYER)
	{
		if (SessionMenuVars::vars.warnonplayerjoin)
		{
			GetRenderer()->NotifyMap(va("%s is joining the game...", PlayerName));
		}
	}

	if ((NetEvent::vars.scriptEvents || NetEvent::vars.smartProtex) && NETWORK::NetworkIsSessionActive())
	{
		// regular system
		if (Sender < 32 && Sender > -1)
		{
			switch (arguments[0])
			{
			case 220529377:
				ReportReason = "Remote Teleport";

				result = 0;
				break;
			case -1574148096:
				if (arguments[2] == 0 && arguments[3] == 0 && arguments[4] == 0 && arguments[5] == 0)
				{
					ReportReason = "Infinite Loading Screen";

					result = 0;
				}
				else if (arguments[2] == 0 && arguments[3] == 0 && arguments[4] != 0)
				{
					ReportReason = "Remote Teleport";

					result = 0;
				}
				break;

			case 1857989824:
				if (arguments[5] == 148)
				{
					ReportReason = "Force To Single Player";

					result = 0;
				}
				break;

			case 13670104:
				if (arguments[2] == 1000)
				{
					ReportReason = "Ban From Ceo";

					result = 0;
				}
				break;

			case 1886569883:
				if (arguments[2] == 48)
				{
					ReportReason = "Non Host Kick";

					result = 0;
				}
				break;

			case -1672138036:
				if (arguments[2] == 0 && arguments[3] == 0)
				{
					ReportReason = "Non Host Kick";

					result = 0;
				}
				break;

			case 1618930485: //Alpha
				ReportReason = "Non Host Kick";

				result = 0;
				break;

			case -15432926: //force into event
				ReportReason = "Force Into Event";

				result = 0;
				break;

			case 1190833098: //kick from ceo
				ReportReason = "Kick From CEO";

				result = 0;
				break;

			case 360381720:
				ReportReason = "Ban From CEO";

				result = 0;
				break;

			case 997247450:
				if (arguments[2] == 3000 && arguments[4] == 10000 && arguments[6] == 4000)
				{
					ReportReason = "Non Host Kick";

					result = 0;
				}
				break;

			case 1119445978:
				if (arguments[4] == 1059127296 && arguments[7] == 1065353216)
				{
					ReportReason = "Non Host Kick";

					result = 0;
				}
				break;

			case 1344161996: //off the radar
				ReportReason = "Off The Radar";

				result = 0;
				break;

			case 1555129594: //Cops Turn Blind Eye
				ReportReason = "Cops Turn Blind Eye";

				result = 0;
				break;

			case 1475266103: //Never Wanted
				ReportReason = "Never Wanted";

				result = 0;
				break;

			case 325218053: //Gentle Kick From Vehicle
				ReportReason = "Gentle Kick From Vehicle";

				result = 0;
				break;

			case 537813547: //Insurance Fraud Spam
				ReportReason = "Insurance Fraud Spam";

				result = 0;
				break;

			case 221861863: //non host kick absolute
				if (arguments[2] == 48)
				{
					ReportReason = "Non Host Kick";

					result = 0;
				}
				break;

			case 801688181: //Trans Spam Loop
				ReportReason = "Transaction Spam";

				result = 0;
				break;

			case 1000837481: //Teleport / Infinate Inv
				ReportReason = "Teleport / Inf Invite";

				result = 0;
				break;

			case -1175363363: //Non Host Kick
				ReportReason = "Non Host Kick";

				result = 0;
				break;

			case -679747935: //Bounty Event
				ReportReason = "Bounty";

				result = 0;
				break;

			case 729971264: //Sound spam
				result = 0;
				break;

			case 566035618: //reset cam
				if (arguments[2] == 1432407380)
				{
					ReportReason = "Reset Cam";

					result = 0;
				}
				break;

			case 1513464838:
				result = 0;
				break;

			case 769347061: //Non Host Kick
			case 999090520: //Non Host Kick 
			case 1642479322://Non Host Kick
			case 994306218://Non Host Kick
			case 928998106://Non Host Kick
			case 2055958901://Non Host Kick
			case 256346004:
			case -1662909539:
			case -4156321:
			case 964496014:
			case 813647057:
			case -1996885757:
			case 1178932519:
			case -1184085326:
			case 2021867503:
			case 1586576930:
			case -12899832505:
			case -2136787743:
			case 27391769:
			case -1835749229: // new kicks from here 
			case 4174298879:
			case 2632057757:
			case 4290810975:
			case 2298081539:
			case 3110881970:
			case 4280036679:
			case 2158179553:
				ReportReason = "Non Host Kick";
				result = 0;
				break;
			}
		}
	}
	
	if (ReportReason != nullptr && NetEvent::vars.notifySE)
	{
#ifdef HARD_DEV
		GetRenderer()->NotifyMapColor(va("Script Event: %d\nFrom: %s\nType: %s", arguments[0], PlayerName, ReportReason), 6);
#endif
#ifndef HARD_DEV
		GetRenderer()->NotifyMapColor(va("Script Event: Blocked\nFrom: %s\nType: %s", PlayerName, ReportReason), 6);
#endif
	}

	// if it has not be blocked yet
	bool ShouldRedirect = false;
	if (Sender < 32 && Sender > -1)
	{
		if (NetEvent::vars.smartProtex && result != 0)
		{
			// smart system
			bool found = false;
			for (int64_t e : NetEvent::EventsWhitelist)
			{
				if (e == arguments[0]) 
				{
					found = true;
				} 
			}
			if (!found)
			{
#ifdef HARD_DEV
				////if (NetEvent::vars.notify)
				//{
				//	GetRenderer()->NotifyMapColor(va("[DEV] Script Event: %d\nFrom: %s\nType: %s", arguments[0], PlayerName, "Smart Filter"), 6);
				//}
#endif
				ShouldRedirect = true;
				result = 0; // block unknown events ~Big dick guy
			}
		}
	}

	if (ReportReason == "Non Host Kick")
	{
		EventReactionMenuVars::AddPlayer({ const_cast<char*>(PlayerName), Sender, EventReactionMenuVars::eResponses::KICK });
	}
	else if (ReportReason != nullptr)
	{
		EventReactionMenuVars::AddPlayer({ const_cast<char*>(PlayerName), Sender, EventReactionMenuVars::eResponses::MALICIOUS });
	}

	if ((ReportReason != nullptr && NetEvent::vars.redirectScriptEvents) || ShouldRedirect)
	{
		Natives::TriggerScriptEvent(arguments, argStructSize, (1 << Sender));
	}

	if (NetEvent::vars.blockallncriptevents)
	{
		result = 0;
	}

	return result;
}

void BuildNetEventMessage(std::string what, CNetGamePlayer* offender)
{
	GetRenderer()->NotifyMap(va("Event blocked from: %s\n Event type: %s", offender->PlayerInfo->Name, what.c_str()), true);
}

typedef void(*pSendAck)(int64_t g_eventMgr, CNetGamePlayer* sender, CNetGamePlayer* receiver, uint32_t bitBufferIndex, uint32_t eventHandledBitset);
pSendAck AcknowledgeEvent;
typedef void(*pMasterHandler)(int64_t event_manager, CNetGamePlayer* pSender, CNetGamePlayer* pTarget, uint16_t event_id, int32_t event_index, int32_t event_handled_bitset, int64_t bitbuffer_size, int64_t bitbuffer);
pMasterHandler OriginalMasterHandler;
void MasterHandlerHook(int64_t event_manager, CNetGamePlayer* sender, CNetGamePlayer* target, uint16_t event_id, int32_t event_index, int32_t event_handled_bitset, int64_t bitbuffer_size, int64_t bitbuffer) {

	bool ShouldBlock = false;

	if (GetPlayer(sender->m_playerID).m_isEvolveStaff)
	{
		return OriginalMasterHandler(event_manager, sender, target, event_id, event_index, event_handled_bitset, bitbuffer_size, bitbuffer);
	}

	if (sender && sender->m_playerID != -1)
	{
		if (NETWORK::NetworkIsSessionActive())
		{
			switch (event_id)
			{
			case REPORT_MYSELF_EVENT:
			case NETWORK_CHECK_CODE_CRCS_EVENT:
				/*if (NetEvent::vars.notify)
					GetRenderer()->NotifyMapColor(va("Network Event: Logged\nFrom: %s\nType: %s", sender->PlayerInfo->Name, "Report/Check/Cash"), 6, false);*/
				GetPlayerManager()->AddModding(sender->m_playerID);
				break;

			case GIVE_WEAPON_EVENT:
				EventReactionMenuVars::AddPlayer({ sender->PlayerInfo->Name, sender->m_playerID, EventReactionMenuVars::eResponses::NET_EVENT });
				if (NetEvent::vars.giveWeapons)
				{
					ShouldBlock = true;
					if (NetEvent::vars.notifyNE)
						GetRenderer()->NotifyMapColor(va("Network Event: Blocked\nFrom: %s\nType: %s", sender->PlayerInfo->Name, "Give Weapons"), 6, false);
				}
				GetPlayerManager()->AddModding(sender->m_playerID);
				break;

			case REMOVE_WEAPON_EVENT:
			case REMOVE_ALL_WEAPONS_EVENT:
				if (NetEvent::vars.takeWeapons)
				{
					ShouldBlock = true;
					if (NetEvent::vars.notifyNE)
						GetRenderer()->NotifyMapColor(va("Network Event: Blocked\nFrom: %s\nType: %s", sender->PlayerInfo->Name, "Remove Weapons"), 6, false);
				}
				GetPlayerManager()->AddModding(sender->m_playerID);
				break;

			case NETWORK_CLEAR_PED_TASKS_EVENT:
				EventReactionMenuVars::AddPlayer({ sender->PlayerInfo->Name, sender->m_playerID, EventReactionMenuVars::eResponses::NET_EVENT });
				if (NetEvent::vars.clearTasks)
				{
					ShouldBlock = true;
					if (NetEvent::vars.notifyNE)
						GetRenderer()->NotifyMapColor(va("Network Event: Blocked\nFrom: %s\nType: %s", sender->PlayerInfo->Name, "Clear Tasks"), 6, false);
					if (NetEvent::vars.redirectNetEvents)
					{
						GetRenderer()->NotifyMapColor(va("Clear Tasks: Redirecting\nTo: %s", sender->PlayerInfo->Name), 6, false);
						BRAIN::ClearPedTasksImmediately(GetPlayer(sender->m_playerID).m_ped);
					}
				}
				GetPlayerManager()->AddModding(sender->m_playerID);
				break;

			case FIRE_EVENT:
			case EXPLOSION_EVENT:
				if (NetEvent::vars.explosions)
				{
					ShouldBlock = true;
				}
				break;

			case NETWORK_PTFX_EVENT:
				if (NetEvent::vars.particleEffects)
				{
					ShouldBlock = true;
				}
				break;

			case REQUEST_CONTROL_EVENT:
				if (NetEvent::vars.control) {
					ShouldBlock = true;
				}
				break;

			case ALTER_WANTED_LEVEL_EVENT:
				if (NetEvent::vars.wantedLevel)
				{
					ShouldBlock = true;
				}
				break;

			case NETWORK_PLAY_SOUND_EVENT:
				if (NetEvent::vars.sound)
				{
					ShouldBlock = true;
				}
				break;

			case KICK_VOTES_EVENT:
				EventReactionMenuVars::AddPlayer({ sender->PlayerInfo->Name, sender->m_playerID, EventReactionMenuVars::eResponses::NET_EVENT });
				if (NetEvent::vars.voteKick)
				{
					ShouldBlock = true;
					if (NetEvent::vars.notifyNE)
						GetRenderer()->NotifyMapColor(va("Network Event: Warning\nFrom: %s\nType: %s", sender->PlayerInfo->Name, "Kick Votes"), 6);

					if (NetEvent::vars.redirectNetEvents)
					{

						GetRenderer()->NotifyMapColor(va("Vote Kick: Redirecting\nTo: %s", sender->PlayerInfo->Name), 6);

						int64_t arg1[3];
						arg1[0] = -120668417;
						arg1[1] = sender->m_playerID;
						arg1[2] = 48;
						SaveRemoteEvent(arg1, 3, sender->m_playerID);

						arg1[0] = 1222825035;
						arg1[2] = 0;
						SaveRemoteEvent(arg1, 2, sender->m_playerID);

						arg1[0] = 769347061;
						arg1[2] = 0;
						SaveRemoteEvent(arg1, 2, sender->m_playerID);

						arg1[0] = 999090520;
						arg1[2] = 0;
						SaveRemoteEvent(arg1, 2, sender->m_playerID);

						arg1[0] = 1642479322;
						arg1[2] = 0;
						SaveRemoteEvent(arg1, 2, sender->m_playerID);

						arg1[0] = 994306218;
						arg1[2] = 0;
						SaveRemoteEvent(arg1, 2, sender->m_playerID);

						arg1[0] = -928998106;
						arg1[2] = 0;
						SaveRemoteEvent(arg1, 2, sender->m_playerID);

						arg1[0] = 1153942884;
						arg1[2] = 0;
						SaveRemoteEvent(arg1, 2, sender->m_playerID);
					}
				}
				break;

			case GAME_WEATHER_EVENT:
				if (NetEvent::vars.bypassweatherchangequick == true) {
					return OriginalMasterHandler(event_manager, sender, target, event_id, event_index, event_handled_bitset, bitbuffer_size, bitbuffer);
				}
				if (NetEvent::vars.weatherTime && !NetEvent::vars.bypassweatherchangequick) {
					ShouldBlock = true;
				}
				break;

			case GAME_CLOCK_EVENT:
				if (ProtectionMenuVars::vars.gameclock) {
					ShouldBlock = true;
				}
				break;

			case GIVE_PICKUP_REWARDS_EVENT: // "i work for microsoft"
				ShouldBlock = true;
				break;

			case REMOTE_SCRIPT_LEAVE_EVENT: // "look i'm a wardens tester i'm cool"
				ShouldBlock = true;
				break;
			}
		}
	}

	if (NetEvent::vars.logallnetevents) {
		LOG_PRINT("Event ID: %i - From: %s", event_id, sender->PlayerInfo->Name);
	}

	if (NetEvent::vars.blockallnetevents && NETWORK::NetworkIsSessionActive())
	{
		ShouldBlock = true;
	}

	if (ShouldBlock)
	{
		AcknowledgeEvent(event_manager, sender, target, event_index, event_handled_bitset);
	}
	else
	{
		OriginalMasterHandler(event_manager, sender, target, event_id, event_index, event_handled_bitset, bitbuffer_size, bitbuffer);
	}
}

bool NetEvent::Initialize() {
	//DWORD64 patchAddress = 0;
	//auto patch = GetAuth()->GetSignature("HISEP");
	//if (patch != nullptr && (patchAddress = Pattern::Scan("HISEP", patch->m_pattern))) {
	//	Pattern::putVP(patchAddress, { 0xB0, 0x01, 0xC3 }); // mov al, 1; ret
	//}

	/*if (!Hooking::PatternCallback<void>({ "TEST1", true, 0, "48 89 5C 24 ? 57 48 83 EC 20 F6 42 1C 01 48 8B DA 48 8B F9 75 39 8B 4A 10" }, [](void* address) {
		ScriptEventHandlerCallerAddress = (uint64_t)address;
	})) return false;

	if (!Hooking::PatternCallback<void>({ "TEST2", true, 0x34, "40 53 48 83 EC 20 48 8B D9 E8 ? ? ? ? 48 8B 4B 30" }, [](void* address) {
		return Hooking::HookFunction(address, &ScriptEventHandlerHook, &ScriptEventHandlerOP, "TEST2");
	})) return false;*/

	if (!Hooking::ServerPatternCallback<void>("DFKD", [](Hooking::CallbackData<void> data) {
		AcknowledgeEvent = (pSendAck)data.m_address;
	})) return false;

	PatternBatch batch("NE");

	batch.Submit("NOEMPL", [](DWORD64 address) {
		return Hooking::HookFunctionQueued((void*)address, &NetObjEntityManagePlaneHook, &OriginalNetObjEntityManagePlaneHook, "NOEMPL");
	});

	batch.Submit("NOEMPP", [](DWORD64 address) {
		return Hooking::HookFunctionQueued((void*)address, &NetObjEntityManagePickupPlacementHook, &OriginalNetObjEntityManagePickupPlacementHook, "NOEMPP");
	});

	batch.Submit("NOEMA", [](DWORD64 address) {
		return Hooking::HookFunctionQueued((void*)address, &NetObjEntityManageAutomobileHook, &OriginalNetObjEntityManageAutomobileHook, "NOEMA");
	});

	batch.Submit("NOEMB", [](DWORD64 address) {
		return Hooking::HookFunctionQueued((void*)address, &NetObjEntityManageBikeHook, &OriginalNetObjEntityManageBikeHook, "NOEMB");
	});

	batch.Submit("NOEMH", [](DWORD64 address) {
		return Hooking::HookFunctionQueued((void*)address, &NetObjEntityManageHeliHook, &OriginalNetObjEntityManageHeliHook, "NOEMH");
	});

	batch.Submit("NOEMO", [](DWORD64 address) {
		return Hooking::HookFunctionQueued((void*)address, &NetObjEntityManageObjectHook, &OriginalNetObjEntityManageObject, "NOEMO");
	});

	batch.Submit("NOEMPED", [](DWORD64 address) {
		return Hooking::HookFunctionQueued((void*)address, &NetObjEntityManagePedHook, &OriginalNetObjEntityManagePed, "NOEMPED");
	});

	batch.Submit("NOEMP", [](DWORD64 address) {
		return Hooking::HookFunctionQueued((void*)address, &NetObjEntityManagePickupHook, &OriginalNetObjEntityManagePickup, "NOEMP");
	});

	batch.Submit("HISE", [](DWORD64 address) {
		return Hooking::HookFunctionQueued((void*)address, &HandleIncrementStatEventHook, &OriginalHandleIncrementStatEvent, "HISE");
	});

	batch.Submit("RNOH", [](DWORD64 address) {
		return Hooking::HookFunctionQueued((void*)address, &RecieveNetworkObjectHook, &OriginalRecieveNetworkObject, "RNOH");
	});

	/*batch.Submit("NEP_MAS", [](DWORD64 address) {
		return Hooking::HookFunctionQueued((void*)address, &CallNetworkEventCallbackHook, &OriginalCallNetworkEventCallback, "NEP_MAS");
	});*/

	batch.Submit("NEP_EHH", [](DWORD64 address) {
		//return Hooking::HookFunctionQueued((void*)address, &EventsHandlerHook, &OriginalEventsHandler, "NEP_EHH");
		return Hooking::HookFunctionQueued((void*)address, &MasterHandlerHook, &OriginalMasterHandler, "NEP_EHH");
	});

	//batch.Submit("NEP_RAW", [](DWORD64 address) {
	//	return Hooking::HookFunctionQueued((void*)address, &RemoveAllWeaponsEventHook, &OriginalRemoveAllWeaponsEvent, "NEP_RAW");
	//});

	//batch.Submit("NEP_RW", [](DWORD64 address) {
	//	return Hooking::HookFunctionQueued((void*)address, &RemoveWeaponEventHook, &OriginalRemoveWeaponEvent, "NEP_RW");
	//});

	//batch.Submit("NEP_GW", [](DWORD64 address) {
	//	return Hooking::HookFunctionQueued((void*)address, &GiveWeaponEventHook, &OriginalGiveWeaponEvent, "NEP_GW");
	//});

	//batch.Submit("NEP_WC", [](DWORD64 address) {
	//	return Hooking::HookFunctionQueued((void*)address, &WeatherChangeEventHook, &OriginalWeatherChangeEvent, "NEP_WC");
	//});

	/*batch.Submit("NEP_RC", [](DWORD64 address) {
		return Hooking::HookFunctionQueued((void*)address, &RequestControlEventHook, &OriginalRequestControlEvent, "NEP_RC");
	});*/

	//batch.Submit("NEP_WL", [](DWORD64 address) {
	//	return Hooking::HookFunctionQueued((void*)address, &WantedLevelEventHook, &OriginalWantedLevelEvent, "NEP_WL");
	//});

	//batch.Submit("NEP_CPT", [](DWORD64 address) {
	//	return Hooking::HookFunctionQueued((void*)address, &ClearPedTaskEventHook, &OriginalClearPedTaskEvent, "NEP_CPT");
	//});

	//batch.Submit("NEP_E", [](DWORD64 address) {
	//	return Hooking::HookFunctionQueued((void*)address, &ExplosionEventHook, &OriginalExplosionEvent, "NEP_E");
	//});

	//batch.Submit("NEP_F", [](DWORD64 address) {
	//	return Hooking::HookFunctionQueued((void*)address, &FireEventHook, &OriginalFireEvent, "NEP_F");
	//});

	//batch.Submit("NEP_PTFX", [](DWORD64 address) {
	//	return Hooking::HookFunctionQueued((void*)address, &PTFXEventHook, &OriginalPTFXEvent, "NEP_PTFX");
	//});

	//batch.Submit("NEP_PS", [](DWORD64 address) {
	//	return Hooking::HookFunctionQueued((void*)address, &PlaySoundEventHook, &OriginalPlaySoundEvent, "NEP_PS");
	//});

	///*batch.Submit("NEP_GEDE", [](DWORD64 address) {
	//	return Hooking::HookFunctionQueued((void*)address, &GetEventDataHook, &OriginalGetEventData, "NEP_GEDE");
	//});*/

	batch.Submit("NEP_S", [](DWORD64 address) {
		return Hooking::HookFunctionQueued((void*)address, &ScriptEventHook, &OriginalScriptEvent, "NEP_S");
	});

	//batch.Submit("NEP_VK", [](DWORD64 address) {
	//	return Hooking::HookFunctionQueued((void*)address, &VoteKickEventHook, &OriginalVoteKickEvent, "NEP_VK");
	//});

	//batch.Submit("NEP_RSL", [](DWORD64 address) {
	//	return Hooking::HookFunctionQueued((void*)address, &RemoteScriptLeaveHook, &OriginalRemoteScriptLeave, "NEP_SRL");
	//});

	batch.Flush();
	Hooking::ApplyQueue();

	return true;
}

String NetEvent::GetTeleportLocation(int id) {
	/*switch (id) {
		case 1: return "ECLIPSE_TOWERS"; break;
		case 5: return "ALTA_STREET"; break;
		case 7: return "DEL_PERRO_HEIGHTS"; break;
		case 8: return "1162_POWER_ST_APT_3"; break;
		case 9: return "0605_SPANISH_AVE_APT_1"; break;
		case 10: return "0604_LAS_LAGUNAS_BLVD_APT_4"; break;
		case 11: return "0184_MILTON_RD_APT_13"; break;
		case 12: return "THE_ROYALE_APT_19"; break;
		case 13: return "0504_S_MO_MILTON_DR"; break;
		case 14: return "0115_BAY_CITY_AVE_APT_45"; break;
		case 15: return "0325_SOUTH_ROCKFORD_DR"; break;
		case 16: return "DREAM_TOWER_APT_15"; break;
		case 17: return "2143_LAS_LAGUNAS_BLVD_APT_9"; break;
		case 18: return "1561_SAN_VITAS_ST_APT_2"; break;
		case 19: return "0112_S_ROCKFORD_DR_APT_13"; break;
		case 20: return "2057_VESPUCCI_BLVD_APT_1"; break;
		case 21: return "0069_COUGAR_AVE_APT_19"; break;
		case 22: return "PROSPERITY_ST_APT_21"; break;
		case 23: return "1115_BLVD_DEL_PERRO_APT_18"; break;
		case 24: return "0120_MURRIETA_HEIGHT_GARAGE"; break;
		case 25: return "UNIT_14_POPULAR_ST_GARAGE"; break;
		case 26: return "UNIT_2_POPULAR_ST_GARAGE"; break;
		case 27: return "331_SUPPLY_ST_GARAGE"; break;
		case 28: return "UNIT_1_OLYMPIC_FWY_GARAGE"; break;
		case 29: return "0754_ROY_LOWENSTEIN_BLVD_GARAGE"; break;
		case 30: return "12_LITTLE_BIGHORN_AVE_GARAGE"; break;
		case 31: return "UNIT_124_POPULAR_ST_GARAGE"; break;
		case 32: return "0552_ROY_LOWENSTEIN_BLCD_GARAGE"; break;
		case 33: return "0432_DAVIS_AVE_GARAGE"; break;
		case 35: return "WEAZEL_PLAZA"; break;
		case 38: return "4_INTEGRITY_WAY"; break;
		case 40: return "RICHARDS_MAJESTIC"; break;
		case 42: return "TINSEL_TOWERS"; break;
		case 44: return "142_PALETO_BLVD_GARAGE"; break;
		case 45: return "1_STRAWBERRY_AVE_GARAGE"; break;
		case 46: return "1932_GRAPESEED_AVE_GARAGE"; break;
		case 47: return "1920_SENORA_WAY_GARAGE"; break;
		case 48: return "2000_GREAT_OCEAN_HIGHWAY_GARAGE"; break;
		case 49: return "197_ROUTE_68_GARAGE"; break;
		case 50: return "870_ROUTE_68_APPROACH_GARAGE"; break;
		case 51: return "1200_ROUTE_68_GARAGE"; break;
		case 52: return "8754_ROUTE_68_GARAGE"; break;
		case 53: return "1905_DAVIS_AVE_GARAGE"; break;
		case 54: return "1623_SOUTH_SHAMBLES_ST_GARAGE"; break;
		case 55: return "4531_DRY_DOCK_ST_GARAGE"; break;
		case 56: return "1337_EXCEPTIONALISTS_WAY_GARAGE"; break;
		case 57: return "UNIT_76_GREENWICH_PARKWAY_GARAGE"; break;
		case 58: return "INNOCENCE_BLVD_GARAGE"; break;
		case 59: return "634_BLVD_DEL_PERRO_GARAGE"; break;
		case 60: return "0897_MIRROR_PARK_BLVD_GARAGE"; break;
		case 66: return "4_HANGMAN_AVE"; break;
		case 67: return "12_SUSTANCIA_RD"; break;
		case 68: return "4584_PROCOPIO_DR"; break;
		case 69: return "4401_PROCOPIO_DR"; break;
		case 70: return "0232_PALETO_BLVD"; break;
		case 71: return "140_ZANCUDO_AVE"; break;
		case 72: return "1893_GRAPESEED_AVE"; break;
		case 73: return "3655_WILD_OATS_DR"; break;
		case 74: return "2044_NORTH_CONKER_AVE"; break;
		case 75: return "2868_HILLCREST_AVE"; break;
		case 76: return "2862_HILLCREST_AVE"; break;
		case 77: return "3677_WHISPYMOUND_DR"; break;
		case 78: return "2117_MILTON_RD"; break;
		case 79: return "2866_HILLCREST_AVE"; break;
		case 80: return "2874_HILLCREST_AVE"; break;
		case 81: return "2113_MAD_WAYNE_THUNDER_DR"; break;
		case 82: return "2045_NORTH_CONKER_AVE"; break;
		case 86: return "ECLIPSE_WEIRD_FREEZE"; break;
		case 87: return "LOMBANK_WEST_OFFICE"; break;
		case 88: return "MAZE_BANK_WEST_OFFICE"; break;
		case 89: return "ARCADIUS_OFFICE"; break;
		case 90: return "MAZE_BANK_TOWER_OFFICE"; break;
		case 91: return "RANCHO_MC_CLUBHOUSE"; break;
		case 92: return "VESPUCCI_MC_CLUBHOUSE"; break;
		case 93: return "PILLBOX_HILL_MC_CLUBHOUSE"; break;
		case 94: return "GRAND_SENORA_DESERT_MC_CLUBHOUSE"; break;
		case 95: return "PALETO_BAY_MC_CLUBHOUSE"; break;
		case 96: return "SANDY_SHORES_MC_CLUBHOUSE"; break;
		case 97: return "LA_MESA_MC_CLUBHOUSE"; break;
		case 98: return "VINEWOOD_MC_CLUBHOUSE"; break;
		case 99: return "HAWICK_MC_CLUBHOUSE"; break;
		case 100: return "GRAPESEED_MC_CLUBHOUSE"; break;
		case 102: return "VESPUCCI_BEACH_MC_CLUBHOUSE"; break;
	};
	if (id >= 103 && id <= 114) return "OFFICE_GARAGES";
	return "Unknown";*/

	char* Return = "";
	switch (id) {
	case 0:
		Return = "MP_REP_PROP_1";
		break;
	case 1:
		Return = "MP_PROP_1";
		break;

	case 2:
		Return = "MP_PROP_2";
		break;

	case 3:
		Return = "MP_PROP_3";
		break;

	case 4:
		Return = "MP_PROP_4";
		break;

	case 5:
		Return = "MP_PROP_5";
		break;

	case 6:
		Return = "MP_PROP_6";
		break;

	case 7:
		Return = "MP_PROP_7";
		break;

	case 8:
		Return = "MP_PROP_8";
		break;

	case 9:
		Return = "MP_PROP_9";
		break;

	case 10:
		Return = "MP_PROP_10";
		break;

	case 11:
		Return = "MP_PROP_11";
		break;

	case 12:
		Return = "MP_PROP_12";
		break;

	case 13:
		Return = "MP_PROP_13";
		break;

	case 14:
		Return = "MP_PROP_14";
		break;

	case 15:
		Return = "MP_PROP_15";
		break;

	case 16:
		Return = "MP_PROP_16";
		break;

	case 17:
		Return = "MP_PROP_17";
		break;

	case 18:
		Return = "MP_PROP_18";
		break;

	case 19:
		Return = "MP_PROP_19";
		break;

	case 20:
		Return = "MP_PROP_20";
		break;

	case 21:
		Return = "MP_PROP_21";
		break;

	case 22:
		Return = "MP_PROP_22";
		break;

	case 23:
		Return = "MP_PROP_23";
		break;

	case 24:
		Return = "MP_PROP_24";
		break;

	case 25:
		Return = "MP_PROP_25";
		break;

	case 26:
		Return = "MP_PROP_26";
		break;

	case 27:
		Return = "MP_PROP_27";
		break;

	case 28:
		Return = "MP_PROP_28";
		break;

	case 29:
		Return = "MP_PROP_29";
		break;

	case 30:
		Return = "MP_PROP_30";
		break;

	case 31:
		Return = "MP_PROP_31";
		break;

	case 32:
		Return = "MP_PROP_32";
		break;

	case 33:
		Return = "MP_PROP_33";
		break;

	case 34:
		Return = "MP_PROP_34";
		break;

	case 35:
		Return = "MP_PROP_35";
		break;

	case 36:
		Return = "MP_PROP_36";
		break;

	case 37:
		Return = "MP_PROP_37";
		break;

	case 38:
		Return = "MP_PROP_38";
		break;

	case 39:
		Return = "MP_PROP_39";
		break;

	case 40:
		Return = "MP_PROP_40";
		break;

	case 41:
		Return = "MP_PROP_41";
		break;

	case 42:
		Return = "MP_PROP_42";
		break;

	case 43:
		Return = "MP_PROP_43";
		break;

	case 44:
		Return = "MP_PROP_44";
		break;

	case 45:
		Return = "MP_PROP_45";
		break;

	case 46:
		Return = "MP_PROP_46";
		break;

	case 47:
		Return = "MP_PROP_48";
		break;

	case 48:
		Return = "MP_PROP_49";
		break;

	case 49:
		Return = "MP_PROP_50";
		break;

	case 50:
		Return = "MP_PROP_51";
		break;

	case 51:
		Return = "MP_PROP_52";
		break;

	case 52:
		Return = "MP_PROP_57";
		break;

	case 53:
		Return = "MP_PROP_59";
		break;

	case 54:
		Return = "MP_PROP_60";
		break;

	case 55:
		Return = "MP_PROP_61";
		break;

	case 56:
		Return = "MP_PROP_62";
		break;

	case 57:
		Return = "MP_PROP_63";
		break;

	case 58:
		Return = "MP_PROP_64";
		break;

	case 59:
		Return = "MP_PROP_65";
		break;

	case 60:
		Return = "MP_PROP_66";
		break;

	case 61:
		Return = "MP_PROP_67";
		break;

	case 62:
		Return = "MP_PROP_68";
		break;

	case 63:
		Return = "MP_PROP_69";
		break;

	case 64:
		Return = "MP_PROP_70";
		break;

	case 65:
		Return = "MP_PROP_71";
		break;

	case 66:
		Return = "MP_PROP_72";
		break;

	case 67:
		Return = "MP_PROP_73";
		break;

	case 68:
		Return = "MP_PROP_74";
		break;

	case 69:
		Return = "MP_PROP_75";
		break;

	case 70:
		Return = "MP_PROP_76";
		break;

	case 71:
		Return = "MP_PROP_77";
		break;

	case 72:
		Return = "MP_PROP_78";
		break;

	case 83:
		Return = "MP_PROP_79";
		break;

	case 84:
		Return = "MP_PROP_80";
		break;

	case 85:
		Return = "MP_PROP_81";
		break;

	case 73:
		Return = "MP_PROP_83";
		break;

	case 74:
		Return = "MP_PROP_84";
		break;

	case 75:
		Return = "MP_PROP_85";
		break;

	case 76:
		Return = "MP_PROP_86";
		break;

	case 77:
		Return = "MP_PROP_87";
		break;

	case 78:
		Return = "MP_PROP_89";
		break;

	case 79:
		Return = "MP_PROP_90";
		break;

	case 80:
		Return = "MP_PROP_92";
		break;

	case 81:
		Return = "MP_PROP_94";
		break;

	case 82:
		Return = "MP_PROP_95";
		break;

	case 86:
		Return = "PM_SPAWN_Y";
		break;

	case 87:
		Return = "MP_PROP_OFF1";
		break;

	case 88:
		Return = "MP_PROP_OFF2";
		break;

	case 89:
		Return = "MP_PROP_OFF3";
		break;

	case 90:
		Return = "MP_PROP_OFF4";
		break;

	case 91:
		Return = "MP_PROP_CLUBH1";
		break;

	case 92:
		Return = "MP_PROP_CLUBH2";
		break;

	case 93:
		Return = "MP_PROP_CLUBH3";
		break;

	case 94:
		Return = "MP_PROP_CLUBH4";
		break;

	case 95:
		Return = "MP_PROP_CLUBH5";
		break;

	case 96:
		Return = "MP_PROP_CLUBH6";
		break;

	case 97:
		Return = "MP_PROP_CLUBH7";
		break;

	case 98:
		Return = "MP_PROP_CLUBH8";
		break;

	case 99:
		Return = "MP_PROP_CLUBH9";
		break;

	case 100:
		Return = "MP_PROP_CLUBH10";
		break;

	case 101:
		Return = "MP_PROP_CLUBH11";
		break;

	case 102:
		Return = "MP_PROP_CLUBH12";
		break;

	case 103:
	case 106:
	case 109:
	case 112:
		Return = "MP_PROP_OFFG1";
		break;

	case 104:
	case 107:
	case 110:
	case 113:
		Return = "MP_PROP_OFFG2";
		break;

	case 105:
	case 108:
	case 111:
	case 114:
		Return = "MP_PROP_OFFG3";
		break;

	case 115:
		Return = "IE_WARE_1";
		break;
	}
	return HUD::_GetLabelText(Return);
}