#include "stdafx.h"
#include "menu\submenus\main\sessionMenu.h"
#include "menu/submenus/main/weapon/weaponWeapons.h"
#include <regex>

Anticheat::pMetricCheatHook					Anticheat::OriginalMetricCheat;
Anticheat::pVirtualQueryEx					Anticheat::OriginalVirtualQueryEx;
Anticheat::pVirtualQuery					Anticheat::OriginalVirtualQuery;
Anticheat::pNtQueryVirtualMemoryHook		Anticheat::OriginalNtQueryVirtualMemory;
Anticheat::pCreateNetworkEventHook			Anticheat::OriginalCreateNetworkEvent;
Anticheat::pAddEventToListHook				Anticheat::OriginalAddEventToList;
Anticheat::pProcessMetricHook				Anticheat::OriginalProcessMetric;
Anticheat::pSigScanSystem					Anticheat::OriginalSigScanSystem;
Anticheat::pSigScanSystem					Anticheat::SigScanSystem;
Anticheat::pGrabPointersToNTDLLFunctions	Anticheat::GrabPointersToNTDLLFunctions;
Anticheat::pMessageBoxCrash					Anticheat::OriginalMessageBoxCrash;
Anticheat::pMessageBoxCrash					Anticheat::MessageBoxCrash;
uint64_t									Anticheat::m_addEventToListPointer;
uint64_t									Anticheat::m_tunables;
LPCRITICAL_SECTION							Anticheat::m_crcCriticalSectionPointer;

namespace MemePatch {
	map<uint64_t, vector<BYTE>> g_orig;
	void CopyBytes(uint64_t address, int size) {
		vector<BYTE> orig(size);
		memcpy(&orig[0], (void*)address, size);

		g_orig[address] = orig;
	}

	void PatchWithRetValue(const uint64_t address, const int value) {
		char buf[0x21];
		sprintf_s(buf, "\\x48\\xC7\\xC0\\x%02X\\x%02X\\x%02X\\x%02X\\xC3", value & 0xFF, value >> 8 & 0xFF,
			value >> 16 & 0xFF, value >> 24 & 0xFF);

		DWORD op;
		const auto addr = reinterpret_cast<LPVOID>(address);

		VirtualProtect(addr, 8, PAGE_EXECUTE_READWRITE, &op);
		CopyBytes(address, 8);
		memcpy(addr, buf, 8);
		VirtualProtect(addr, 8, op, &op);
	}

	void PatchReturnFalse(const uint64_t address) {
		DWORD d;
		VirtualProtect(reinterpret_cast<LPVOID>(address), 4, PAGE_EXECUTE_READWRITE, &d);
		CopyBytes(address, 4);
		memcpy(reinterpret_cast<LPVOID>(address), "\x48\x31\xC0\xC3", 4); // xor rax, rax; ret
		VirtualProtect(reinterpret_cast<LPVOID>(address), 4, d, &d);
	}

}

bool Anticheat::MetricCheatHook(uint64_t* rcx, int edx, int r8) {
	bool origReturn = OriginalMetricCheat(rcx, edx, r8);
	CNetGamePlayer* player = (CNetGamePlayer*)rcx;
	char* name = player->PlayerInfo->Name;
	int playerID = Utils::PlayerIDFromName(name);
	if (edx != 3 && r8 != -1778492849 && playerID != -1) {
		if (Backend::IsLoaded())LOG_DEVDEBUG("[CMetric] %s, %s, %d, %d", name, origReturn ? "true" : "false", edx, r8);
		//if (Backend::IsLoaded()) GetPlayerManager()->AddModding(playerID);
	}

	if (playerID == PLAYER::PlayerId()) {
		if (Backend::IsLoaded())LOG_DEVCUSTOM(ConsoleForeground::DARKRED, "[CMetric] Metric cheat");
		return true;
	}

	return playerID == PLAYER::PlayerId() ? true : origReturn;
}

void Anticheat::CreateNetworkEventHook(void* eventTable, CNetEventInfo* event) {
	if (event->ID == REPORT_MYSELF_EVENT) {
		LOG_DEVCUSTOM(ConsoleForeground::DARKCYAN, "[ACEvent] Reported myself (blocked) | ID: %d, Hash: %d", *(int*)(event + 48), *(int*)(event + 52));
	}
	if (event->ID == NETWORK_CHECK_CODE_CRCS_EVENT || event->ID == REPORT_MYSELF_EVENT || event->ID == REPORT_CASH_SPAWN_EVENT) return;
	OriginalCreateNetworkEvent(eventTable, event);
}

//uint64_t Anticheat::AddEventToListHook(uint64_t eventPool) {
//
//	static uint64_t reportMyself = 0;
//
//	if (!reportMyself) {
//		Hooking::PatternCallback<char>({ "RMSE", true, 0, "48 8B C4 44 88 48 20 44 88 40 18 48 89 50 10" }, [](char *address) {
//			reportMyself = (uint64_t)address;
//		});
//	}
//
//	/*if (reportMyself == 0x4A8) {
//		LOG_PRINT("AETL Failed");
//		Backend::Cleanup();
//		return 0;
//	}*/
//	const static uint64_t crc = reportMyself - 0x1B54;
//	const static uint64_t cashSpawn = reportMyself - 0x97F;
//
//	//const static uint64_t scriptarray = reportMyself - 0x401;
//	//const static uint64_t array = reportMyself + 0x4DB739;
//
//	uint64_t caller = (uint64_t)_ReturnAddress();
//
//	if (caller == reportMyself) {
//		LOG_DEVCUSTOM(ConsoleForeground::DARKRED, "Prevented REPORT_MYSELF_EVENT event creation");
//		return 0;
//	}
//
//	if (caller == crc) {
//		LOG_DEVCUSTOM(ConsoleForeground::DARKRED, "Prevented NETWORK_CHECK_CODE_CRCS_EVENT event creation");
//		return 0;
//	}
//
//	if (caller == cashSpawn) {
//		LOG_DEVCUSTOM(ConsoleForeground::DARKRED, "Prevented REPORT_CASH_SPAWN_EVENT event creation");
//		return 0;
//	}
//
//	/*if (caller == scriptarray) {
//		LOG_DEVCUSTOM(ConsoleForeground::DARKRED, "Prevented SCRIPT_ARRAY_DATA_VERIFY_EVENT event creation");
//		return 0;
//	}
//
//	if (caller == array) {
//		LOG_DEVCUSTOM(ConsoleForeground::DARKRED, "Prevented ARRAY_DATA_VERIFY_EVENT event creation");
//		return 0;
//	}*/
//
//	//Pattern::putVP((uint64_t)GetModuleHandleA(0) + 0x11420A4, 0xC3);
//	//Pattern::putVP((uint64_t)GetModuleHandleA(0) + 0x161DBE4, 0xC3);
//	
//	/*const static uint64_t reportMyself = m_addEventToListPointer + 0x4A8;
//	const static uint64_t crc = m_addEventToListPointer - 0x1B54;
//	const static uint64_t cashSpawn = m_addEventToListPointer - 0x97F;
//
//	uint64_t caller = (uint64_t)_ReturnAddress();
//
//	if (caller == reportMyself || caller == crc || caller == cashSpawn) {
//		LOG_DEVCUSTOM(ConsoleForeground::DARKRED, "[ACEvent] Report Myself | CRC | Cash Spawn");
//		return 0;
//	}*/
//
//	return OriginalAddEventToList(eventPool);
//}

//uint64_t Anticheat::AddEventToListHook(uint64_t eventPool) {
//	uint64_t caller = (uint64_t)_ReturnAddress();
//	static uint64_t baseStart = 0;
//
//	if (!baseStart) {
//		Hooking::PatternCallback<char>({ "AETL_S", true, 0, "48 8B C4 44 88 48 20 44 88 40 18 48 89 50 10" }, [](char *address) {
//			baseStart = (uint64_t)address;
//		});
//	}
//
//	if (caller == baseStart + 0x4A8) {
//		LOG_DEVCUSTOM(ConsoleForeground::DARKRED, "Prevented REPORT_MYSELF_EVENT event creation");
//		return 0;
//	}
//
//	if (caller == baseStart + 0x1B54) {
//		LOG_DEVCUSTOM(ConsoleForeground::DARKRED, "Prevented NETWORK_CHECK_CODE_CRCS_EVENT event creation");
//		return 0;
//	}
//
//	if (caller == baseStart + 0x97F) {
//		LOG_DEVCUSTOM(ConsoleForeground::DARKRED, "Prevented REPORT_CASH_SPAWN_EVENT event creation");
//		return 0;
//	}
//
//	return OriginalAddEventToList(eventPool);
//}

uint64_t Anticheat::AddEventToListHook(uint64_t eventPool) {
	uint64_t caller = (uint64_t)_ReturnAddress();

	static once_flag init;
	static uint64_t reportMyself, checkCRC, cashSpawn;

	call_once(init, [] {
		Hooking::PatternCallback<char>({ "AETL_RMS_B", true, 0x5E, "40 53 48 83 EC 40 83 B9 ? ? ? ? ? 48 8B D9 75 67 48 83 64 24 ? ? 48 83 64 24 ? ? 48 8D 54 24 ? 48 81 C1 ? ? ? ?" }, [](char *address) {
			auto b = GetAddressFromInstruction(address, 0, 1, 5);
			if (b) {
				reportMyself = b + 0x22;
			}
		});

		Hooking::PatternCallback<char>({ "AETL_NCCCRCE", true, 0x0, "48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 83 EC 30 44 8B F1 48 8B 0D ? ? ? ? 41 8B F8 8B EA E8 ? ? ? ? 33 DB 48 85 C0 74 5C 40 8A" }, [](char *address) {
			checkCRC = (uint64_t)address + 0x64;
		});

		Hooking::PatternCallback<char>({ "AETL_RCSE", true, -0x3F, "48 89 5C 24 ? 57 48 83 EC 20 33 FF 48 8B D9 48 85 C9 74 08 48 8B 01 FF 50 68 EB 07 48 8D 05" }, [](char *address) {
			cashSpawn = (uint64_t)address;
		});
	});

	if (caller == reportMyself) {
		LOG_DEVCUSTOM(ConsoleForeground::DARKRED, "Prevented REPORT_MYSELF_EVENT event creation");
		return 0;
	}

	if (caller == checkCRC) {
		LOG_DEVCUSTOM(ConsoleForeground::DARKRED, "Prevented NETWORK_CHECK_CODE_CRCS_EVENT event creation");
		return 0;
	}

	if (caller == cashSpawn) {
		LOG_DEVCUSTOM(ConsoleForeground::DARKRED, "Prevented REPORT_CASH_SPAWN_EVENT event creation");
		return 0;
	}

	return OriginalAddEventToList(eventPool);
}

void SetThisScriptCanBePausedHook(NativeContext* cxt) {
	if (strstr(SCRIPT::GetThisScriptName(), "valentinerpreward2")) {
		SCRIPT::TerminateThisThread();
	}

	MISC::SetThisScriptCanBePaused(cxt->getArgument<bool>(0));
}

//void Anticheat::ProcessMetricHook(uint64_t* metric, bool unk) {
//	uint64_t classDefinition = *metric;
//	char* metricName = ((char* (*)())(void*)*(uint64_t*)(classDefinition + 0x18))();
//	//if (strstr(metricName, "EARN")) {
//	//	LOG_PRINT("AMT %I64d", *(__int64 *)(classDefinition + 128));
//	//	LOG_PRINT("SP %d", *(__int64 *)(classDefinition + 148));
//	//
//	//}
//	if (strstr(metricName, "CASH_CREATED")) {
//		if (SessionMenuVars::vars.warncashcreation) {
//			GetRenderer()->NotifyMap(va("Cash is being dropped in your session"), false);
//		}
//		//LOG_PRINT("ID %I64d", *(__int64 *)(classDefinition + 24));
//		//LOG_PRINT("ID %x", *(__int64 *)(classDefinition + 32));
//		//LOG_PRINT("ID %d", *(__int64 *)(classDefinition + 64));
//		//LOG_PRINT("ID %d", *(__int64 *)(classDefinition + 68));
//	}
//	if (strstr(metricName, "SES_JOIN")) {
//		GetWindowManager()->m_chatComp.addLine("~r~________________Joined New session________________");
//		//GetFiberPool()->DoJob([] {
//		//	while (!SCRIPT::DoesScriptExist("valentinerpreward2")) GetFiberManager()->GoToMainFiber(); // don't think this needs to wait
//		//
//		//	Hooking::ScriptTableCallback("valentinerpreward2", "V", [](Script::ScriptTableItem* script) {
//		//		if (!Hooking::HookScriptNative(script, 0xAA391C728106F7AF, SetThisScriptCanBePausedHook, "V")) {
//		//		}
//		//	});
//		//});
//	}
//
//	if (strstr(metricName, "SPAWN")) {
//		if (WeaponWeaponsMenuVars::vars.giveallweaponsloop) {
//			GetFiberPool()->DoJob([] {
//				WAIT(2000);
//				WeaponWeaponsMenuVars::giveallweaponeverysesh();
//			});
//		}
//	}
//
//	if (Backend::IsLoaded())LOG_DEVCUSTOM(ConsoleForeground::DARKRED, "[CMetric] Name: %s, Offset: GTA5.exe+0x%llx", metricName, classDefinition - (uint64_t)GetModuleHandle(nullptr));
//}

bool Anticheat::ProcessMetricHook(uint64_t* metric, bool unk) {
	if (metric) {
		uint64_t classDefinition = *metric;
		if (classDefinition) {
			char* metricName = ((char* (*)())(void*)*(uint64_t*)(classDefinition + 0x18))();

			LOG_PRINT("Processing metric %s", metricName);

			if (strstr(metricName, "CASH_CREATED")) {
				if (SessionMenuVars::vars.warncashcreation) {
					GetRenderer()->NotifyMap(va("Cash is being dropped in your session"), false);
				}
			}

			if (strstr(metricName, "SES_JOIN")) {
				GetWindowManager()->m_chatComp.addLine("~r~________________Joined New session________________");
			}

			if (strstr(metricName, "SPAWN")) {
				if (WeaponWeaponsMenuVars::vars.giveallweaponsloop) {
					GetFiberPool()->DoJob([] {
						WAIT(2000);
						WeaponWeaponsMenuVars::giveallweaponeverysesh();
					});
				}
			}

			if (Backend::IsLoaded())LOG_DEVCUSTOM(ConsoleForeground::DARKRED, "[CMetric] Name: %s, Offset: GTA5.exe+0x%llx", metricName, classDefinition - (uint64_t)GetModuleHandle(nullptr));
		}
	}

	return OriginalProcessMetric(metric, unk);
}

SIZE_T WINAPI Anticheat::VirtualQueryExHook(HANDLE hProcess, LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength) {
	if (lpBuffer != nullptr) {
		if (Memory::IsScanInOurMemory((uint64_t)lpAddress, (uint64_t)lpAddress + dwLength, Backend::GetModuleBase(), (Backend::GetModuleBase() + Backend::GetModuleSize()))) {
			lpBuffer->AllocationBase = 0;
			lpBuffer->AllocationProtect = 0;
			lpBuffer->State = MEM_FREE;
			lpBuffer->Protect = PAGE_NOACCESS;
			lpBuffer->Type = 0;
			if (Backend::IsLoaded())LOG_DEVCUSTOM(ConsoleForeground::DARKRED, "[MemScan] memory scan 0x3 detected");
		}

		if (ScriptHookV::LoadedModuleMemory.size()) {
			for (auto& item : ScriptHookV::LoadedModuleMemory) {
				if (!Utils::Within((uint64_t)_ReturnAddress(), item.m_base, (item.m_base + item.m_size))) {
					if (Memory::IsScanInOurMemory((uint64_t)lpAddress, (uint64_t)lpAddress + dwLength, item.m_base, (item.m_base + item.m_size))) {
						lpBuffer->AllocationBase = 0;
						lpBuffer->AllocationProtect = 0;
						lpBuffer->State = MEM_FREE;
						lpBuffer->Protect = PAGE_NOACCESS;
						lpBuffer->Type = 0;
						if (Backend::IsLoaded()) LOG_DEVCUSTOM(ConsoleForeground::DARKRED, "[MemScan] memory scan detected in shv");
					}
				}
			}
		}
	}

	return OriginalVirtualQueryEx(hProcess, lpAddress, lpBuffer, dwLength);
}

SIZE_T WINAPI Anticheat::VirtualQueryHook(LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength) {
	if (lpBuffer != nullptr) {
		if (Memory::IsScanInOurMemory((uint64_t)lpAddress, (uint64_t)lpAddress + dwLength, Backend::GetModuleBase(), (Backend::GetModuleBase() + Backend::GetModuleSize()))) {
			lpBuffer->AllocationBase = 0;
			lpBuffer->AllocationProtect = 0;
			lpBuffer->State = MEM_FREE;
			lpBuffer->Protect = PAGE_NOACCESS;
			lpBuffer->Type = 0;
			if (Backend::IsLoaded())LOG_DEVCUSTOM(ConsoleForeground::DARKRED, "[MemScan] memory scan 0x2 detected");
		}

		if (ScriptHookV::LoadedModuleMemory.size()) {
			for (auto& item : ScriptHookV::LoadedModuleMemory) {
				if (!Utils::Within((uint64_t)_ReturnAddress(), item.m_base, (item.m_base + item.m_size))) {
					if (Memory::IsScanInOurMemory((uint64_t)lpAddress, (uint64_t)lpAddress + dwLength, item.m_base, (item.m_base + item.m_size))) {
						lpBuffer->AllocationBase = 0;
						lpBuffer->AllocationProtect = 0;
						lpBuffer->State = MEM_FREE;
						lpBuffer->Protect = PAGE_NOACCESS;
						lpBuffer->Type = 0;
						if (Backend::IsLoaded()) LOG_DEVCUSTOM(ConsoleForeground::DARKRED, "[MemScan] memory scan detected in shv");
					}
				}
			}
		}
	}

	return OriginalVirtualQuery(lpAddress, lpBuffer, dwLength);
}

NTSTATUS Anticheat::NtQueryVirtualMemoryHook(HANDLE processHandle, PVOID baseAddr, MEMORY_INFORMATION_CLASS memInfoClass, PVOID memInfo, SIZE_T memInfoLength, PSIZE_T retLength) {
	if (!Backend::IsHooking()) {
		if (!Utils::Within((uint64_t)_ReturnAddress(), (uint64_t)Backend::GetModuleBase(), (Backend::GetModuleBase() + Backend::GetModuleSize()))) {
			if (Memory::IsScanInOurMemory((uint64_t)baseAddr, (uint64_t)baseAddr + memInfoLength, Backend::GetModuleBase(), (Backend::GetModuleBase() + Backend::GetModuleSize()))) {
				LOG_DEVCUSTOM(ConsoleForeground::DARKRED, "[MemScan] memory scan 0x1 detected 0x%llx 0x%llx 0x%llx 0x%llx", (uint64_t)baseAddr, (uint64_t)baseAddr + memInfoLength, Backend::GetModuleBase(), (Backend::GetModuleBase() + Backend::GetModuleSize()));
				LOG_DEVCUSTOM(ConsoleForeground::DARKRED, "[MemScan] call in our module. Return: 0x%llx (GTA5.exe + 0x%llx)", _ReturnAddress(), (uint64_t)_ReturnAddress() - (uint64_t)GetModuleHandleA(nullptr));
				return 0xC0000022; //0xC0000004
			}
		}
	}

	if (ScriptHookV::LoadedModuleMemory.size() > 0) {
		for (auto item : ScriptHookV::LoadedModuleMemory) {
			if (!Utils::Within((uint64_t)_ReturnAddress(), item.m_base, (item.m_base + item.m_size))) {
				if (Memory::IsScanInOurMemory((uint64_t)baseAddr, (uint64_t)baseAddr + memInfoLength, item.m_base, (item.m_base + item.m_size))) {
					//LOG_PRINT("Detected a signature scan inside a loaded SHV module (sneak -100). 0x%llx : 0x%llx", item.m_base, item.m_size);
					LOG_DEVCUSTOM(ConsoleForeground::DARKRED, "[MemScan] memory scan detected in shv module 0x%llx 0x%llx 0x%llx 0x%llx", (uint64_t)baseAddr, (uint64_t)baseAddr + memInfoLength, item.m_base, (item.m_base + item.m_size));
					return 0xC0000022; //0xC0000004
				}
			}
		}
	}

	return OriginalNtQueryVirtualMemory(processHandle, baseAddr, memInfoClass, memInfo, memInfoLength, retLength);
}

typedef int (WINAPI *pMessageBoxW)(HWND, LPCWSTR, LPCWSTR, UINT);
pMessageBoxW OriginalpMessageBoxW = NULL;
int WINAPI MessageBoxWHook(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType) {
	LOG_DEVPRINT("MessageBox!");
	LOG_DEVPRINT("%s", Memory::BuildStackTrace());
	return OriginalpMessageBoxW(hWnd, L"Hooked!", lpCaption, uType);
}

typedef BOOL(WINAPI *pTerminateProcess)(HANDLE, UINT);
pTerminateProcess OriginalTerminateProcess = NULL;
BOOL TerminateProcessHook(HANDLE hProcess, UINT uExitCode) {
	LOG_DEVPRINT("Terminate call");
	return true;
}

__int64 Anticheat::MessageBoxCrashHook(__int64 a1, unsigned __int64 a2) {
	LOG_DEVPRINT("Crash!");
	return 0;
}

typedef BOOL(*pBitBlt)(HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, DWORD rop);
pBitBlt OriginalBitBlt;
BOOL BitBltHook(HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, DWORD rop) {
	LOG_DEVCUSTOM(ConsoleForeground::DARKCYAN, "[BitBlt] Prevented screenshot - %s", Memory::BuildStackTrace());
	return FALSE;
}

typedef bool(__fastcall *appendTransactionToQueueType)(NetshopQueue*, CNetShopTransaction*);
static appendTransactionToQueueType appendTransactionToQueue;
static bool __fastcall appendTransactionToQueueHook(NetshopQueue* shopQueue, CNetShopTransaction* transaction) {
#ifdef HARD_DEV
	if (Backend::IsLoaded())LOG_DEVDEBUG("Append transaction to q called");
#endif
	auto allow = transaction->ServiceHash == -1;

	if (!allow) {
		switch (transaction->CategoryHash) {
		case CATEGORY_SERVICE_UNLOCKED:
		case CATEGORY_SERVICE_WITH_LIMIT:
		case CATEGORY_SERVICE_WITH_THRESHOLD:
			allow = true; break;
		default: break;
		}
	}

	if (!allow) {
#ifdef HARD_DEV
		if (Backend::IsLoaded())LOG_DEVCUSTOM(ConsoleForeground::RED, "[AppTrTQ] Category: 0x%08X | Service: 0x%08X", transaction->CategoryHash, transaction->ServiceHash);
#endif
		return false;
	}


	if (!allow && NetEvent::vars.blockalltransactions) {
		return false;
	}

#ifdef HARD_DEV
	LOG_DEVDEBUG("Allowing...");
#endif
	return appendTransactionToQueue(shopQueue, transaction);
}

typedef BOOL(*pTryEnterCriticalSection)(LPCRITICAL_SECTION lpCriticalSection);
pTryEnterCriticalSection OriginalTryEnterCriticalSection;
BOOL TryEnterCriticalSectionHook(LPCRITICAL_SECTION lpCriticalSection) {
	if (lpCriticalSection == Anticheat::m_crcCriticalSectionPointer) {
		return FALSE;
	}

	return OriginalTryEnterCriticalSection(lpCriticalSection);
}

typedef DWORD(*pGetModuleFileNameA)(HMODULE hModule, LPSTR lpFilename, DWORD nSize);
pGetModuleFileNameA OriginalGetModuleFileNameA;
DWORD GetModuleFileNameAHook(HMODULE hModule, LPSTR lpFilename, DWORD nSize) {
	if (strstr(lpFilename, "ScriptHookV")) {
		return 0;
	}
	if (strstr(lpFilename, "ScriptHook")) {
		return 0;
	}
	if (strstr(lpFilename, "dinput8")) {
		return 0;
	}
	if (strstr(lpFilename, "Menyoo")) {
		return 0;
	}
	return OriginalGetModuleFileNameA(hModule, lpFilename, nSize);
}

static BOOL(WINAPI * OriginalReadProcessMemory)(HANDLE hProcess, LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T * lpNumberOfBytesRead) = ReadProcessMemory;
BOOL ReadProcessMemoryHook(HANDLE hProcess, LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T * lpNumberOfBytesRead) {
	if (!Backend::IsHooking()) {
		if (!Utils::Within((uint64_t)_ReturnAddress(), (uint64_t)Backend::GetModuleBase(), (Backend::GetModuleBase() + Backend::GetModuleSize()))) {
			if (Memory::IsScanInOurMemory((uint64_t)lpBaseAddress, (uint64_t)lpBaseAddress + nSize, Backend::GetModuleBase(), (Backend::GetModuleBase() + Backend::GetModuleSize()))) {
				LOG_DEVCUSTOM(ConsoleForeground::DARKRED, "[MemScan] memory scan RPM detected 0x%llx 0x%llx 0x%llx 0x%llx", (uint64_t)lpBaseAddress, (uint64_t)lpBaseAddress + nSize, Backend::GetModuleBase(), (Backend::GetModuleBase() + Backend::GetModuleSize()));
				return 0;
			}
		}
	}

	return OriginalReadProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesRead);
}

bool SigScanSystemHook() {
	return 1; // inject in sp possibly
}

typedef bool(*pMetricHookOne)(void* Src);
typedef bool(*pMetricHookTwo)(unsigned int a1, __int64 a2, char a3);
typedef bool(*pMetricHookThree)(unsigned int a1, __int64 a2);

pMetricHookOne OrigMetricOne = nullptr;
pMetricHookTwo OrigMetricTwo = nullptr;
pMetricHookThree OrigMetricThree = nullptr;

bool MetricHandlerOneHook(uint64_t* src) {
	uint64_t classDefinition = *src;
	char* metricName = ((char* (*)())(void*) * (uint64_t*)(classDefinition + 0x18))();
#ifdef HARD_DEV
	if (Backend::IsLoaded())LOG_DEVCUSTOM(ConsoleForeground::DARKRED, "[CMetric 1] Name: %s, Offset: GTA5.exe+0x%llx", metricName, classDefinition - (uint64_t)GetModuleHandle(nullptr));
#endif
	return true;
}

bool MetricHandlerTwoHook(unsigned int a1, uint64_t* src, char a3) {
	uint64_t classDefinition = *src;
	char* metricName = ((char* (*)())(void*) * (uint64_t*)(classDefinition + 0x18))();

	if (strstr(metricName, "SES_JOIN")) {
		GetWindowManager()->m_chatComp.addLine("~r~________________Joined New session________________");
	}

#ifdef HARD_DEV
	if (Backend::IsLoaded())LOG_DEVCUSTOM(ConsoleForeground::DARKRED, "[CMetric 2] Name: %s, Offset: GTA5.exe+0x%llx", metricName, classDefinition - (uint64_t)GetModuleHandle(nullptr));
#endif
	return true;
}

bool MetricHandlerThreeHook(unsigned int a1, uint64_t* src) {
	uint64_t classDefinition = *src;
	char* metricName = ((char* (*)())(void*) * (uint64_t*)(classDefinition + 0x18))();

	if (strstr(metricName, "SPAWN")) {
		if (WeaponWeaponsMenuVars::vars.giveallweaponsloop) {
			GetFiberPool()->DoJob([] {
				WAIT(2000);
				WeaponWeaponsMenuVars::giveallweaponeverysesh();
			});
		}
	}

	if (strstr(metricName, "CASH_CREATED")) {
		if (SessionMenuVars::vars.warncashcreation) {
			GetRenderer()->NotifyMap(va("Cash is being dropped in your session"), false);
		}
	}

#ifdef HARD_DEV
	if (Backend::IsLoaded())LOG_DEVCUSTOM(ConsoleForeground::DARKRED, "[CMetric 3] Name: %s, Offset: GTA5.exe+0x%llx", metricName, classDefinition - (uint64_t)GetModuleHandle(nullptr));
#endif
	return true;
}

class NetData {
public:
	char* Data; //0x0000
}; //Size: 0x0008

class NetRequest {
public:
	char pad_0000[16]; //0x0000
	class NetData* RequestData; //0x0010
	char pad_0018[64]; //0x0018
	char* ResponseHeaders; //0x0058
	char pad_0060[40]; //0x0060
	char* RequestHeaders; //0x0088
	char pad_0090[1112]; //0x0090
	class NetData* ResponseData; //0x04E8
	char pad_04F0[4]; //0x04F0
	uint16_t ContentLength; //0x04F4
	char pad_04F6[18]; //0x04F6
	char* Scheme; //0x0508
	char* Host; //0x0510
	char* Path; //0x0518
	char pad_0520[72]; //0x0520
	char* UserAgent; //0x0568
	char pad_0570[3032]; //0x0570
	char* URLRequest; //0x1148
	char pad_1150[1432]; //0x1150
}; //Size: 0x16E8

typedef bool(__fastcall* updateRequest)(NetRequest* request);
static updateRequest __updateRequest;
static bool __fastcall _updateRequest(NetRequest* request) {
	if (request->RequestData && request->RequestData->Data) {
		//LOG_PRINT("Request to %s://%s%s:\n%s\n%s", request->Scheme, request->Host, request->Path, request->RequestHeaders ? request->RequestHeaders : "No headers available.", request->RequestData && request->RequestData->Data && strcmp(request->Scheme, "https") == 0 ? request->RequestData->Data : "null");

		const auto path = std::string(request->Path);

		for (auto blockedApi : { "SubmitCompressed", "SubmitRealTime", "Bonus" }) {
			if (path.find(blockedApi) != std::string::npos) {
				request->Host = "google.com";
				//request->Path = (char*)std::regex_replace(path, std::regex(blockedApi), "yikes").c_str();
				//LOG_PRINT("MODIFIED request to %s://%s%s:\n%s\n%s", request->Scheme, request->Host, request->Path, request->RequestHeaders ? request->RequestHeaders : "No headers available.", request->RequestData && request->RequestData->Data && strcmp(request->Scheme, "https") == 0 ? request->RequestData->Data : "null");
				//LOG_PRINT("Modified");
				return __updateRequest(request);
			}
		}
	}
	return __updateRequest(request);
}

bool Anticheat::PreAuth() {
	//Api block for /bonus
	if (!Hooking::PatternCallback<char>({ "BSRH", true, 0x0, "40 55 57 41 54 41 55" }, [](char* address) {
		Hooking::HookFunction(address, &_updateRequest, &__updateRequest, "BSRH");
	})) return false;

	if (!Hooking::PatternCallback<void>({ "SDWF", true, 0x0, "48 8B C4 48 89 58 18 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 48 8D 8D ? ? ? ? 0F 29 70 B8 E8 ? ? ? ? 48 8D 8D ? ? ? ? E8 ? ? ? ? 4C 8D 05 ? ? ? ?" }, [](void* data) {
		*(BYTE*)data = 0xC3;
	})) return false;

	if (!Hooking::PatternCallback<void>({ "GREW", true, 0x0, "48 89 5C 24 ? 55 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B D9 48 8D 0D ? ? ? ?" }, [](void* data) {
		*(BYTE*)data = 0xC3;
	})) return false;

	// if an invalid resource is called, it's prolly this!
	if (!Hooking::PatternCallback<void>({ "CKFP", true, 0x0, "80 3D ? ? ? ? ? 0F 85 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 08" }, [](void* address) {
		Pattern::putVP(address, 0xC3);
	})) return false;

	/*Critical section shit*/
	if (!Hooking::PatternCallback<char>({ "CSS", true, 0x0, "48 8D 0D ? ? ? ? 4C 8B F0 48" }, [](char* address) {
		m_crcCriticalSectionPointer = (LPCRITICAL_SECTION)GetAddressFromInstruction(address);
	})) return false;

	/*Grab Pointers To NTDLL Functions*/
	if (!Hooking::PatternCallback<void>({ "GPTNF", true, 0x0, "40 53 48 83 EC 20 48 8D 0D ? ? ? ? FF 15 ? ? ? ? 48 8D 15 ? ? ? ? 48 8B C8 48 8B D8 FF 15 ? ? ? ? 48 8D 15 ? ? ? ? 48 8B CB 48 89 05 ? ? ? ?" }, [](void* address) {
		GrabPointersToNTDLLFunctions = (pGrabPointersToNTDLLFunctions)address;
	})) return false;

	/*Sig Scan System*/
	/*if (!Hooking::PatternCallback<void>({ "SYS", false, 0x0, "48 8D 0D ? ? ? ? 48 89 55 0F E9 ? ? ? ?" }, [](void* address) {
		uint64_t FuncAddy = GetAddressFromInstruction((uint64_t)address);
		Pattern::putVP(FuncAddy, { 0xB0, 0x01, 0xC3 });
	})) return false;*/

	/*Virtual Query hooks*/
	Hooking::HookFunction(&VirtualQueryEx, &VirtualQueryExHook, &OriginalVirtualQueryEx, "VQE", false);
	Hooking::HookFunction(&VirtualQuery, &VirtualQueryHook, &OriginalVirtualQuery, "VQ", false);
	Hooking::HookFunction(GetProcAddress(Backend::GetNTDLLModule(), "NtQueryVirtualMemory"), &NtQueryVirtualMemoryHook, &OriginalNtQueryVirtualMemory, "NQVM", false);

	GrabPointersToNTDLLFunctions();

	return true;
	Hooking::PatternCallback<char>({ "ATTQ", true, 0xB, "48 85 DB 74 2A 48 8B D3" }, [](char* address) {
		Hooking::HookFunction(reinterpret_cast<void *>(GetAddressFromInstruction(address, 0, 1, 5)), &appendTransactionToQueueHook, &appendTransactionToQueue, "ATTQH");
	})
		&& Hooking::HookFunction(&GetModuleFileNameA, &GetModuleFileNameAHook, &OriginalGetModuleFileNameA, "GMFNA", false)
		&& Hooking::HookFunction(&TryEnterCriticalSection, &TryEnterCriticalSectionHook, &OriginalTryEnterCriticalSection, "TECS", false);
}

bool Anticheat::PreGame() {

	//Hooking::HookFunction(&BitBlt, &BitBltHook, &OriginalBitBlt, "BBLT", false);

	/*Send Script Event To Network*/
	/*if (!Hooking::ServerPatternCallback<char>("SSETN", [](Hooking::CallbackData<char> data) {
		data.m_address += 0x26;
		Pattern::WriteVirtualProtect<short>(data.m_address, 0x33EB);
		data.m_address += 0x82;
		Pattern::WriteVirtualProtect<short>(data.m_address, 0x66EB);
	})) return false;*/

	/*Send Network Info Change Event*/
	//if (!Hooking::PatternCallback<char>({ "SNICE", false, 0x0, "48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 83 EC 30 44 8B F1" }, [](char* address) {
	//	//Pattern::returnFunction(address);
	//	Pattern::put(address, 0xC3);
	//})) return false;

	/*Metric Cheat*/
	if (!Hooking::ServerPatternCallbackBool<void>("MCF", [](Hooking::CallbackData<void> data) -> bool {
		return Hooking::HookFunction(data, &MetricCheatHook, &OriginalMetricCheat);
	})) return false;

	/*Create Network Event*/
	//if (!Hooking::ServerPatternCallbackBool<void>("CNE", [](Hooking::CallbackData<void> data) -> bool {
	//	return Hooking::HookFunction(data, &CreateNetworkEventHook, &OriginalCreateNetworkEvent);
	//})) return false;

	/*Add Event To List*/
	if (!Hooking::ServerPatternCallbackBool<void>("AETL", [](Hooking::CallbackData<void> data) {
		return Hooking::HookFunction(data, &AddEventToListHook, &OriginalAddEventToList);
	})) return false;

	/*Add Event To List Pointer*/
	/*if (!Hooking::ServerPatternCallback<char>("AETLP", [](Hooking::CallbackData<char> data) {
		m_addEventToListPointer = (uint64_t)data.m_address;
	})) return false;*/

	/*Anti Cheat Metric Function*/
	if (!Hooking::ServerPatternCallback<void>("ACMF", [](Hooking::CallbackData<void> data) {
		Pattern::putVP(data.m_address, 0xC3);
	})) return false;

	/*if (!Hooking::ServerPatternCallback<void>("ACDC", [](Hooking::CallbackData<void> data) {
		Pattern::nop(data.m_address, 0xD);
	})) return false;

	if (!Hooking::ServerPatternCallback<void>("ACWD", [](Hooking::CallbackData<void> data) {
		MemePatch::PatchWithRetValue((uint64_t)data.m_address, 1);
	})) return false;*/

	if (!Hooking::ServerPatternCallback<void>("AS3", [](Hooking::CallbackData<void> data) {
		return Hooking::HookFunction(data.m_address, &MetricHandlerOneHook, &OrigMetricOne, "AS3");
	})) return false;

	if (!Hooking::ServerPatternCallback<void>("FD2", [](Hooking::CallbackData<void> data) {
		return Hooking::HookFunction(data.m_address, &MetricHandlerTwoHook, &OrigMetricTwo, "FD2");
	})) return false;

	if (!Hooking::ServerPatternCallback<void>("SSA", [](Hooking::CallbackData<void> data) {
		return Hooking::HookFunction(data.m_address, &MetricHandlerThreeHook, &OrigMetricThree, "SSA");
	})) return false;

	/*Process metric hook*/
	/*if (!Hooking::ServerPatternCallback<void>("PM", [](Hooking::CallbackData<void> data) {
		return Hooking::HookFunction(data, &ProcessMetricHook, &OriginalProcessMetric);
	})) return false;*/

	/*Some integrity check*/
	if (!Hooking::ServerPatternCallback<char>("WD", [](Hooking::CallbackData<char> data) {
		Pattern::putVP(data.m_address, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0xC3 });
	})) return false;

	///*Another integrity check*/
	if (!Hooking::ServerPatternCallback<void>("IC", [](Hooking::CallbackData<void> data) {
		Pattern::nop(data.m_address, 13);
	})) return false;

	///*Another integrity check*/
	if (!Hooking::ServerPatternCallback<char>("MBXC", [](Hooking::CallbackData<char> data) {
		Pattern::putVP(data.m_address, 0xC3);
	})) return false;

	if (!Hooking::PatternCallback<char>({ "ITCK", false, 0x0, "48 83 EC 48 48 83 64 24 ? ? 83 4C 24 ? ?" }, [](char* address) {
		Pattern::putVP(address, 0xC3);
	})) return false;

	/*Tunables*/
	//if (!Hooking::PatternCallback<char>({ "TMF", false, 0x0, "48 8B 1D ? ? ? ? BA ? ? ? ? B9 ? ? ? ? E8 ? ? ? ?" }, [](char* address) {
	//	//Tunables = reinterpret_cast<decltype(Tunables)>(address + *(int32_t*)(address + 3) + 7);
	//	m_tunables = (uint64_t)(address + 3 + *(int*)(address + 7));
	//})) return false;

	/*Telemetry Block*/
	/*if (!Hooking::ServerPatternCallback<char>("TEL", [](Hooking::CallbackData<char> data) {
		Pattern::returnFunction(data.m_address);
	})) return false;*/

	/*IntegrityCheck Block*/
	/*if (!Hooking::ServerPatternCallback<char>("IB", [](Hooking::CallbackData<char> data) {
		Pattern::returnFunction(data.m_address);
	})) return false;*/

	/*Scan System*/
	/*if (!Hooking::ServerPatternCallback<void>("SS", [](Hooking::CallbackData<void> data) {
	Pattern::nop(data.m_address, 7);
	})) return false;*/

	//Report Myself Call
	/*if (!Hooking::ServerPatternCallback<void>("RMC", [](Hooking::CallbackData<void>& data) {
	Pattern::returnFunction(data.m_address);
	})) return false;*/

	/*Anticheat Virtual Call Something*/
	/*if (!Hooking::PatternCallback<void>({ "AVCS", true, 0x0, "FF 52 08 48 83 3B 00" }, [](void* address) {
		Pattern::nop(address, 3);
	})) return false;*/

	/*Message Box Crash 1*/
	//if (!Hooking::PatternCallback<void>({ "AVCS", true, 0x0, "E8 ? ? ? ? 48 03 03" }, [](void* address) {
	//	//Pattern::nop(address, 5);
	//	Hooking::HookFunction(address, &MessageBoxCrashHook, &OriginalMessageBoxCrash, "AVCS");
	//})) return false;

	/*Message Box Crash 2*/
	//if (!Hooking::PatternCallback<void>({ "AVCS", true, 0x0, "E8 ? ? ? ? CC 33 D2" }, [](void* address) {
	//	//Pattern::nop(address, 5);
	//	MessageBoxCrash = (pMessageBoxCrash)address;
	//})) return false;

	/*Spare AC Nop*/
	/*if (!Hooking::ServerPatternCallback<void>("W2", [](Hooking::CallbackData<void>& data) {
		//Pattern::nop(address, 11);
	})) return false;*/

	return true;
}

bool Anticheat::InGame() {
	return true;
}

void Anticheat::Cleanup() {

}