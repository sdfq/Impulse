#include "stdafx.h"
#include "session.h"

Session::readSessionInfoType Session::__readSessionInfo;
Session::joinSelectedPlayerType Session::joinSelectedPlayer;
Session::playerMenuListConstructorType Session::__playerMenuListConstructor;

Session::readSessionInfoResponseType Session::__readSessionInfoResponse;
Session::sendSessionInfoByGamerHandleTaskType Session::sendSessionInfoByGamerHandleTask;
std::vector<SessionInfoTask> Session::sessionInfoTasks;

#pragma optimize("", off)
void Session::GetSessionInfoByRockstarId(uint32_t handle, std::function<void(uint32_t, bool, const char *, int)> callback) {
	//LOG_PRINT("Queued r*id %i for online status...", handle);
	auto containsCallback = false;
	//LOG_PRINT("%i", handle);
	for (auto& x : sessionInfoTasks) {
		if (x.m_rockstarId == handle) {
			containsCallback = true;
		}
	}

	if (!containsCallback) {
		sessionInfoTasks.push_back({ handle, callback });
	}

	static int i = 0;

	static InfoTaskData data{};
	data.rockstarId = handle;
	data.unk1 = 3;
	data.unk2 = 2;

	sendSessionInfoByGamerHandleTask(0, &data, 1, 1, 1, 1, &i);
}
#pragma optimize("", on)

bool __fastcall Session::_readSessionInfoResponse(__int64 a1) {
	if (*reinterpret_cast<DWORD *>(a1 + 0x50) == 1 && *reinterpret_cast<DWORD *>(a1 + 0x54) == 3 && reinterpret_cast<char *>(a1 + 0x14C8) != nullptr) {
		try {
			const auto responseData = *reinterpret_cast<char **>(a1 + 0x14C8);
			if (!nlohmann::json::accept(responseData)) {
				//LOG_PRINT("dddd");
				return false;
			}

			auto response = nlohmann::json::parse(responseData);

			if (response.find("gsinfo") == response.end()) {
				//LOG_PRINT("aaaaaaaa");
				return false;
			}

			const auto rId = static_cast<uint32_t>(std::stoul(response["_id"].get<std::string>().substr(3)));

			for (auto it = sessionInfoTasks.begin(); it < sessionInfoTasks.end(); ++it) {
				if (it->m_rockstarId == rId) {
					auto gsInfo = response["gsinfo"].get<std::string>();

					if (gsInfo.empty()) {
						it->m_callback(it->m_rockstarId, false, nullptr, -1);
						sessionInfoTasks.erase(it);
						return false;
					}

					const auto gsType = response["gstype"].get<int>();

					it->m_callback(it->m_rockstarId, true, gsInfo.c_str(), gsType);
					sessionInfoTasks.erase(it);

					return false;
				}
			}

			if (response["gsinfo"].get<std::string>().empty()) {
				//LOG_PRINT("oooooooooo");
				return false;
			}

		} catch (nlohmann::json::exception e) {
			//LOG_PRINT("assssssssssssssssss");
			return false;
		}
	}

	return __readSessionInfoResponse(a1);
}

int Session::handleToFake = -1;
__int64 Session::menuPointer = 0;
CHostStruct* Session::hostStruct = NULL;

void Session::Initialize() {
	Hooking::ServerPatternCallback<char>("SSIHT", [](Hooking::CallbackData<char> data) {
		sendSessionInfoByGamerHandleTask = reinterpret_cast<sendSessionInfoByGamerHandleTaskType>(data.m_address);
	});

	Hooking::ServerPatternCallback<char>("RSIR", [](Hooking::CallbackData<char> data) {
		Hooking::HookFunction(data.m_address, &_readSessionInfoResponse, &__readSessionInfoResponse, "RSIR");
	});

	Hooking::ServerPatternCallback<char>("SESRS", [](Hooking::CallbackData<char> data) {
		Hooking::HookFunction(data.m_address, &_readSessionInfo, &__readSessionInfo, "SESRSH");
	});

	Hooking::ServerPatternCallback<char>("SESJS", [](Hooking::CallbackData<char> data) {
		joinSelectedPlayer = reinterpret_cast<joinSelectedPlayerType>(data.m_address);
	});

	Hooking::ServerPatternCallback<char>("SESPL", [](Hooking::CallbackData<char> data) {
		Hooking::HookFunction(data.m_address, &_playerMenuListConstructor, &__playerMenuListConstructor, "SESPLH");
	});

	Hooking::ServerPatternCallback<char>("HRID", [](Hooking::CallbackData<char> data) {
		Session::hostStruct = *reinterpret_cast<CHostStruct **>(data.m_address + *reinterpret_cast<int *>(data.m_address + 3) + 7);
	});
}

bool Session::_readSessionInfo(__int64 a1, int a2, DWORD *handlePtr, unsigned int a4) {
	if (handleToFake != -1) {
		*handlePtr = handleToFake;
		handleToFake = -1;
	}

	const auto ret = __readSessionInfo(a1, a2, handlePtr, a4); // (Step: 4) - last step. Call the original function with the manipulated handle
	return ret;
}

QWORD *Session::_playerMenuListConstructor(__int64 a1, __int64 a2, __int64 a3) {
	const auto ret = __playerMenuListConstructor(a1, a2, a3);

	if (handleToFake != -1) {
		menuPointer = reinterpret_cast<__int64>(ret); // (Step: 2) - next expected step: Session::Tick() waits for CScriptedCoronaPlayerCardDataManager to load
	}

	return ret;
}

// stackoverflow - VERY SLOW DON'T USE IN TICK FUNCTIONS
bool isBadPtr(void* ptr)
{
	MEMORY_BASIC_INFORMATION mbi;
	if (VirtualQuery(ptr, &mbi, sizeof mbi)) {
		const DWORD mask = (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY);
		auto b = !(mbi.Protect & mask);
		// check the page is not a guard page
		if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS)) {
			b = true;
		}

		return b;
	}
	return true;
}

void Session::Tick() {
	static __int64 managerAddress = 0;

	if (!managerAddress) {
		Hooking::PatternCallback<char>({"SSCPC", false, 0x0, "48 8B 0D ? ? ? ? 44 8A FA 8B"}, [](char *address){
			managerAddress = (__int64)address;
		});
	}

	if (handleToFake != -1) {
		const auto manager = *reinterpret_cast<__int64 *>(managerAddress + *reinterpret_cast<int *>(managerAddress + 3) + 7);

		if (manager && !isBadPtr(reinterpret_cast<void *>(manager))) {
			if (!isBadPtr(reinterpret_cast<uint32_t *>(manager + 0x32))) {
				joinSelectedPlayer(menuPointer, false);
			}
		}
	}

	if (!Backend::m_originalRID) {
		auto mngr = ReClass::GetNetworkPlayerManager();
		if (mngr) {
			auto local = mngr->m_localPlayer;
			if (local) {
				auto info = local->PlayerInfo;
				if (info) {
					Backend::m_spoofingRID = info->RockstarID;
					Backend::m_originalRID = info->RockstarID;
				}
			}
		}
	}
}

void Session::JoinByRockstarId(const int handle) {
	// Step 0: Set up the fake join (menuPointer, handleToFake)
	// Step 1: Call Native::ActivateFrontendMenu with component ID 2 (ty IDA) to open the friends tab
	// Step 2: __playerListMenuConstructor will be called because of step 1. We set the menuPointer here...
	// Step 3: Session::Tick will wait for CScriptedCoronaPlayerCardDataManager to load (required to join) and then call joinSelectedPlayer(menuPointer, false)
	// Step 4: __readSessionInfo will be called from joinSelectedPlayer. Here we will manipulate the handle and reset it afterwards so we don't accidentally join that handle again when joining a friend
	menuPointer = 0;
	handleToFake = handle;

	HUD::ActivateFrontendMenu(0xD528C7E2, false, 2); // (Step: 1) - next expected step: __playerMenuListConstructor hook (set menuPointer)
}