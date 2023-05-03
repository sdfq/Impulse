#pragma once

class Anticheat
{
public:
	typedef enum _MEMORY_INFORMATION_CLASS {
		MemoryBasicInformation
	} MEMORY_INFORMATION_CLASS;

private:
	typedef bool(WINAPI * pMetricCheatHook)(uint64_t*, int, int);
	typedef void(*pCreateNetworkEventHook)(void*, CNetEventInfo*);
	typedef bool(*pProcessMetricHook)(uint64_t*, bool);
	typedef uint64_t(*pAddEventToListHook)(uint64_t);

	typedef SIZE_T(WINAPI *pVirtualQueryEx)(HANDLE, LPCVOID, PMEMORY_BASIC_INFORMATION, SIZE_T);
	typedef SIZE_T(WINAPI *pVirtualQuery)(LPCVOID, PMEMORY_BASIC_INFORMATION, SIZE_T);
	typedef NTSTATUS(*pNtQueryVirtualMemoryHook)(HANDLE, PVOID, MEMORY_INFORMATION_CLASS, PVOID, SIZE_T, PSIZE_T);
	
	static pMetricCheatHook OriginalMetricCheat;
	static pCreateNetworkEventHook OriginalCreateNetworkEvent;
	static pAddEventToListHook OriginalAddEventToList;
	static pProcessMetricHook OriginalProcessMetric;

	static pVirtualQueryEx OriginalVirtualQueryEx;
	static pVirtualQuery OriginalVirtualQuery;
	static pNtQueryVirtualMemoryHook OriginalNtQueryVirtualMemory;

public:
	static bool PreGame();
	static bool PreAuth();
	static bool InGame();
	static void Cleanup();

	static bool MetricCheatHook(uint64_t* rcx, int edx, int r8);
	static void CreateNetworkEventHook(void* eventTable, CNetEventInfo* event);
	static bool ProcessMetricHook(uint64_t* metric, bool unk);
	static uint64_t AddEventToListHook(uint64_t eventPool);

	static SIZE_T WINAPI VirtualQueryExHook(HANDLE hProcess, LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength);
	static SIZE_T WINAPI VirtualQueryHook(LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength);
	static NTSTATUS NtQueryVirtualMemoryHook(HANDLE processHandle, PVOID baseAddr, Anticheat::MEMORY_INFORMATION_CLASS memInfoClass, PVOID memInfo, SIZE_T memInfoLength, PSIZE_T retLength);

	typedef bool(*pSigScanSystem)();
	static pSigScanSystem OriginalSigScanSystem;
	static pSigScanSystem SigScanSystem;

	typedef void(__cdecl * pGrabPointersToNTDLLFunctions)();
	static pGrabPointersToNTDLLFunctions GrabPointersToNTDLLFunctions;

	typedef __int64(__fastcall *pMessageBoxCrash)(__int64 a1, unsigned __int64 a2);
	static pMessageBoxCrash OriginalMessageBoxCrash;
	
	static pMessageBoxCrash MessageBoxCrash;
	static __int64  __fastcall MessageBoxCrashHook(__int64 a1, unsigned __int64 a2);

	static uint64_t m_addEventToListPointer;
	static uint64_t m_tunables;
	static LPCRITICAL_SECTION m_crcCriticalSectionPointer;
};