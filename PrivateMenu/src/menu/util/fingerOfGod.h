#pragma once

enum PresenceEvent {
	// gs_award
	PRESENCE_GAME_SERVER = 0x76849AA6 /*(0x76849AA6)*/,
	// used for when rockstar gives you anything (e.g. money). If you block it users won't see rewards from R* but it can be abused as screen spam aswell. (Maybe make a map notif instead)
	// UGCStatUpdate
	PRESENCE_UGC_STAT_UPDATE = 0x2190F9E1 /*(0x2190F9E1)*/,
	// handler ret 0 -> disabled
	// bounty
	PRESENCE_BOUNTY = 0xECB54731 /*(0xECB54731)*/,
	// handler ret 0
	// StatUpdate
	PRESENCE_STAT_UPDATE = 0xEDF54CE2 /*(0xEDF54CE2)*/,
	// FriendCrewJoined
	PRESENCE_FRIEND_CREW_JOINED = 0x12859620 /*(0x12859620)*/,
	// FriendCrewCreated
	PRESENCE_FRIEND_CREW_CREATED = 0x3F1009B2 /*(0x3F1009B2)*/,
	// mission_verified
	PRESENCE_MISSION_VERIFIED = 0x8C571656 /*(0x8C571656)*/,
	// rockstar_message
	PRESENCE_ROCKSTAR_MESSAGE = 0x70E4D0E1 /*(0x70E4D0E1)*/,
	// the thing @gopro_2027 used
	// crew_message
	PRESENCE_ROCKSTAR_CREW_MESSAGE = 0xCBB12972 /*(0xCBB12972)*/,
	// game_award
	PRESENCE_GAME_AWARD = 0xD36120CE /*(0xD36120CE)*/,
	// handler ret 1 (disabled aswell)
	// vinv
	PRESENCE_VOICE_SESSION_INVITE = 0xB7AECB0C /*(0xB7AECB0C)*/,
	// vres
	PRESENCE_VOICE_SESSION_RESPONSE = 0x7EC656F7 /*(0x7EC656F7)*/,
	// ginv
	PRESENCE_GAME_INVITE = 0x04ED840B /*(0x04ED840B)*/,
	// used for the phone notification. (using ros.publish). The SC notification is done via ros.mp.invite
	// ginvc
	PRESENCE_GAME_INVITED_CANCEL = 0xFCEFA1A2 /*(0xFCEFA1A2)*/,
	// grep
	PRESENCE_GAME_INVITE_REPLY = 0x227E6048 /*(0x227E6048)*/,
	// prolly tells the inviter if we're available
	// tinv
	PRESENCE_TOURNAMENT_INVITE = 0xCFDF8DF4 /*(0xCFDF8DF4)*/,
	// finv
	PRESENCE_FOLLOW_INVITE = 0x13F209B2 /*(0x13F209B2)*/,
	// ainv
	PRESENCE_ADMIN_INVITE = 0x255FF988 /*(0x255FF988)*/,
	// idk if this forces other people to join - would be funny
	// jreq
	PRESENCE_JOIN_QUEUE_REQUEST = 0x0FD33101 /*(0x0FD33101)*/,
	// jqup
	PRESENCE_JOIN_QUEUE_UPDATE = 0x33A53ACB /*(0x33A53ACB)*/,
	// finger
	PRESENCE_FINGER_OF_GOD = 0xB07F4711 /*(0xB07F4711)*/,
	// oh pls
	// news
	PRESENCE_NEWS_ITEM = 0x6EAF6B7D /*(0x6EAF6B7D)*/,
	// ForceSessionUpdate
	PRESENCE_FORCE_SESSION_UPDATE = 0xECAA6FA0 /*(0xECAA6FA0)*/,
	// gtri
	PRESENCE_GAME_TRIGGER_EVENT = 0x28C617D9 /*(0x28C617D9)*/,
	// TextMessage
	PRESENCE_TEXT_MESSAGE = 0x1A8A9221 /*(0x1A8A9221)*/,
};

enum FingerCommand {
	FINGER_KILL = 0xC2F12A5B /*(0xC2F12A5B)*/,
	FINGER_ADMIN_KICK = 0x84643284 /*(0x84643284)*/,
	FINGER_RELAX = 0x4349E22B /*(0x4349E22B)*/,
	FINGER_VEHICLE = 0xDD245B9C /*(0xDD245B9CC)*/,
	FINGER_NETWORK_KICK = 0x1D106C54 /*(0x1D106C54)*/,
	// there re prolly other handlers aswell, not sure tho. hashes above appear in the handler
};

class FingerOfGod {
public:
	static void Init(bool(*callback)(const PresenceEvent presenceEvent, const FingerCommand command, String name));

	static bool sendFingerCommandCustom(const QWORD handle, const String command);
	static bool sendCrewMessageCommand(const QWORD handle, const long long senderID, const int crewId, const String subject, const String message);
	static bool sendFingerCommand(const QWORD handle, const FingerCommand command, const char* vehicle = "");
	static bool sendCashCorrection(const QWORD handle, const int amount);
	static bool sendTextMessage(const QWORD handle, const char *message, const QWORD as);
	static bool sendFriendCreatedCrew(const QWORD handle, const char* friendName);
	static bool sendFriendJoinedCrew(const QWORD handle, const int clanId, const char* tag, const char* crewName, const bool open, const char* friendName);

	typedef bool(*getNetworkHandleId)(__int64, int*, int);
	static getNetworkHandleId GetNetworkHandleID;

private:
	// callback and hook
	static bool(*m_callback)(const PresenceEvent presenceEvent, const FingerCommand command, String name);
	static bool _readGamePresence(__int64 a1, __int64 a2, __int64 a3, __int64 a4);

	typedef bool(__fastcall *sendPresenceEventType)(int, __int64, __int64, __int64, int);
	static sendPresenceEventType m_sendEvent;
	static bool sendPresenceEvent(const QWORD handle, const char* payload);
};
