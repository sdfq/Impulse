#include "stdafx.h"
#include "security/securityHekker.h"
#include <iphlpapi.h>
#include <wlanapi.h>
#include <objbase.h>
#include <wtypes.h>

#include <stdio.h>
#include <stdlib.h>

// Need to link with Wlanapi.lib and Ole32.lib
#pragma comment(lib, "wlanapi.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "iphlpapi")

#pragma warning(disable:4191) //Fuck FARPROC casting

pNQIP						Security::NtQueryInformationProcess;
pRtlAdjustPrivilege			Security::RtlAdjustPrivilege;
pNtRaiseHardError			Security::NtRaiseHardError;
pNtQueryObject				Security::NtQueryObject;
pNtQuerySystemInformation	Security::NtQuerySystemInformation;
pNtSetInformationThread		Security::NtSetInformationThread;
Thread*						Security::m_debuggerDetection;
Thread*						Security::m_internetDetection;
Thread*						Security::m_threadBreakpointDetection;
Thread*						Security::m_antiTamperDetection;
Thread*						Security::m_blacklistedProcessDetection;
Thread*						Security::m_handleDetection;
Thread*						Security::m_textSectionDetection;
Thread*						Security::m_mainSecurity;
vector<TamperTable>			Security::m_tamperTable;
pHandleOpened				Security::m_handleOpenedCallback;
string						Security::m_moduleTextHash;
vector<TCHAR*>				Security::m_blacklistedProcesses = {
		L"ollydbg.exe",
		L"ProcessHacker.exe",
		L"tcpview.exe",
		L"autoruns.exe",
		L"autorunsc.exe",
		L"filemon.exe",
		L"procmon.exe",
		L"regmon.exe",
		L"procexp.exe",
		L"idaq.exe",
		L"idaq64.exe",
		L"ImmunityDebugger.exe",
		L"Wireshark.exe",
		L"dumpcap.exe",
		L"HookExplorer.exe",
		L"ImportREC.exe",
		L"PETools.exe",
		L"LordPE.exe",
		L"SysInspector.exe",
		L"proc_analyzer.exe",
		L"sysAnalyzer.exe",
		L"sniff_hit.exe",
		L"windbg.exe",
		L"joeboxcontrol.exe",
		L"joeboxserver.exe",
		L"apimonitor-x86.exe",
		L"apimonitor-x64.exe",
		L"x32dbg.exe",
		L"x64dbg.exe",
		L"cheatengine-x86_64.exe",
		L"cheatengine-x86.exe",
		L"cheatengine-i386.exe",
		L"Scylla_x64.exe",
		L"Wireshark.exe",
		L"Charles.exe",
		L"Proxifier.exe",
};

LONG WINAPI ExceptionFilter(struct _EXCEPTION_POINTERS *ExceptionInfo) {
	int m_ExceptionCode = ExceptionInfo->ExceptionRecord->ExceptionCode;
	int m_exceptionInfo_0 = ExceptionInfo->ExceptionRecord->ExceptionInformation[0];
	int m_exceptionInfo_1 = ExceptionInfo->ExceptionRecord->ExceptionInformation[1];
	int m_exceptionInfo_2 = ExceptionInfo->ExceptionRecord->ExceptionInformation[2];

	if (m_ExceptionCode == EXCEPTION_BREAKPOINT) {
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	Backend::SetHooking(true);
#ifdef HARD_DEV
	Memory::RelinkModuleToPEB(Backend::GetModule());
	Memory::RestorePeHeaders();
#endif

	uint64_t exceptionAddress = (uint64_t)ExceptionInfo->ExceptionRecord->ExceptionAddress;

	LOG_ERROR("Game crashed...");
	LOG_ERROR("Module base address:  0x%p | 0x%p", Backend::GetModule(), (exceptionAddress - (uint64_t)Backend::GetModule()));
	LOG_ERROR("Game base address:    0x%p | 0x%p", GetModuleHandleA(nullptr), (exceptionAddress - (uint64_t)GetModuleHandleA(nullptr)));
	LOG_ERROR("Exception at address: 0x%p", ExceptionInfo->ExceptionRecord->ExceptionAddress);

	switch (m_ExceptionCode) {
	case EXCEPTION_ACCESS_VIOLATION:
		LOG_ERROR("Cause: EXCEPTION_ACCESS_VIOLATION");
		if (m_exceptionInfo_0 == 0) {
			LOG_ERROR("Attempted to read from: 0x%p", m_exceptionInfo_1);
		} else if (m_exceptionInfo_0 == 1) {
			LOG_ERROR("Attempted to write to: 0x%p", m_exceptionInfo_1);
		} else if (m_exceptionInfo_0 == 8) {
			LOG_ERROR("Data Execution Prevention (DEP) at: 0x%p", m_exceptionInfo_1);
		} else {
			LOG_ERROR("Unknown access violation at: 0x%p", m_exceptionInfo_1);
		}
		break;

	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED: LOG_DEBUG("Cause: EXCEPTION_ARRAY_BOUNDS_EXCEEDED"); break;
	case EXCEPTION_BREAKPOINT: LOG_DEBUG("Cause: EXCEPTION_BREAKPOINT"); break;
	case EXCEPTION_DATATYPE_MISALIGNMENT: LOG_DEBUG("Cause: EXCEPTION_DATATYPE_MISALIGNMENT"); break;
	case EXCEPTION_FLT_DENORMAL_OPERAND: LOG_DEBUG("Cause: EXCEPTION_FLT_DENORMAL_OPERAND"); break;
	case EXCEPTION_FLT_DIVIDE_BY_ZERO: LOG_DEBUG("Cause: EXCEPTION_FLT_DIVIDE_BY_ZERO"); break;
	case EXCEPTION_FLT_INEXACT_RESULT: LOG_DEBUG("Cause: EXCEPTION_FLT_INEXACT_RESULT"); break;
	case EXCEPTION_FLT_INVALID_OPERATION: LOG_DEBUG("Cause: EXCEPTION_FLT_INVALID_OPERATION"); break;
	case EXCEPTION_FLT_OVERFLOW: LOG_DEBUG("Cause: EXCEPTION_FLT_OVERFLOW"); break;
	case EXCEPTION_FLT_STACK_CHECK: LOG_DEBUG("Cause: EXCEPTION_FLT_STACK_CHECK"); break;
	case EXCEPTION_FLT_UNDERFLOW: LOG_DEBUG("Cause: EXCEPTION_FLT_UNDERFLOW"); break;
	case EXCEPTION_ILLEGAL_INSTRUCTION: LOG_DEBUG("Cause: EXCEPTION_ILLEGAL_INSTRUCTION"); break;
	case EXCEPTION_IN_PAGE_ERROR:
		LOG_DEBUG("Cause: EXCEPTION_IN_PAGE_ERROR");
		if (m_exceptionInfo_0 == 0) {
			LOG_ERROR("Attempted to read from: 0x%08x", m_exceptionInfo_1);
		} else if (m_exceptionInfo_0 == 1) {
			LOG_ERROR("Attempted to write to: 0x%08x", m_exceptionInfo_1);
		} else if (m_exceptionInfo_0 == 8) {
			LOG_ERROR("Data Execution Prevention (DEP) at: 0x%08x", m_exceptionInfo_1);
		} else {
			LOG_ERROR("Unknown access violation at: 0x%08x", m_exceptionInfo_1);
		}
		LOG_ERROR("NTSTATUS: 0x%08x", m_exceptionInfo_2);
		break;

	case EXCEPTION_INT_DIVIDE_BY_ZERO: LOG_ERROR("Cause: EXCEPTION_INT_DIVIDE_BY_ZERO"); break;
	case EXCEPTION_INT_OVERFLOW: LOG_ERROR("Cause: EXCEPTION_INT_OVERFLOW"); break;
	case EXCEPTION_INVALID_DISPOSITION: LOG_ERROR("Cause: EXCEPTION_INVALID_DISPOSITION"); break;
	case EXCEPTION_NONCONTINUABLE_EXCEPTION: LOG_ERROR("Cause: EXCEPTION_NONCONTINUABLE_EXCEPTION"); break;
	case EXCEPTION_PRIV_INSTRUCTION: LOG_ERROR("Cause: EXCEPTION_PRIV_INSTRUCTION"); break;
	case EXCEPTION_SINGLE_STEP: LOG_ERROR("Cause: EXCEPTION_SINGLE_STEP"); break;
	case EXCEPTION_STACK_OVERFLOW: LOG_ERROR("Cause: EXCEPTION_STACK_OVERFLOW"); break;
	case DBG_CONTROL_C: LOG_ERROR("Cause: DBG_CONTROL_C"); break;
	default: LOG_ERROR("Cause: 0x%08x", m_ExceptionCode);
	}

	LOG_ERROR("Dumping ASM registers:");

	LOG_ERROR("RAX: 0x%llx || RSI: 0x%llx", ExceptionInfo->ContextRecord->Rax, ExceptionInfo->ContextRecord->Rsi);
	LOG_ERROR("RBX: 0x%llx || RDI: 0x%llx", ExceptionInfo->ContextRecord->Rbx, ExceptionInfo->ContextRecord->Rdi);
	LOG_ERROR("RCX: 0x%llx || RBP: 0x%llx", ExceptionInfo->ContextRecord->Rcx, ExceptionInfo->ContextRecord->Rbp);
	LOG_ERROR("RDX: 0x%llx || RSP: 0x%llx", ExceptionInfo->ContextRecord->Rdx, ExceptionInfo->ContextRecord->Rsp);

	LOG_ERROR("STACK: %s", Memory::BuildStackTrace());
	Backend::SetHooking(false);
	return EXCEPTION_CONTINUE_SEARCH;
}

#pragma region NT Hooks
typedef DWORD(*pDbgBreakPoint)();
typedef DWORD(*pDbgUserBreakPoint)();
typedef DWORD(*pDbgUiConnectToDbg)();
typedef NTSTATUS(*pDbgUiContinue)(uint64_t* id, NTSTATUS continueStatus);
typedef NTSTATUS(*pDbgUiConvertStateChangeStructure)(uint64_t* change, PVOID debugEvent);
typedef NTSTATUS(*pDbgUiDebugActiveProcess)(HANDLE hproc);

pDbgBreakPoint OriginalDbgBreakPoint;
pDbgUserBreakPoint OriginalDbgUserBreakPoint;
pDbgUiConnectToDbg OriginalDbgUiConnectToDbg;
pDbgUiContinue OriginalDbgUiContinue;
pDbgUiConvertStateChangeStructure OriginalDbgUiConvertStateChangeStructure;
pDbgUiDebugActiveProcess OriginalDbgUiDebugActiveProcess;

DWORD DbgBreakPoint() {
	GetServerEvent()->SendEvent(DEBUGGER_ATTACHED, ServerEventData(SEVERITY_BANNABLE, "DbgBreakPoint"));
	return OriginalDbgBreakPoint();
}
DWORD DbgUserBreakPoint() {
	GetServerEvent()->SendEvent(DEBUGGER_ATTACHED, ServerEventData(SEVERITY_BANNABLE, "DbgUserBreakPoint"));
	return OriginalDbgUserBreakPoint();
}
DWORD DbgUiConnectToDbg() {
	GetServerEvent()->SendEvent(DEBUGGER_ATTACHED, ServerEventData(SEVERITY_BANNABLE, "DbgUiConnectToDbg"));
	return OriginalDbgUiConnectToDbg();
}
NTSTATUS DbgUiContinue(uint64_t* id, NTSTATUS continueStatus) {
	GetServerEvent()->SendEvent(DEBUGGER_ATTACHED, ServerEventData(SEVERITY_BANNABLE, "DbgUiContinue"));
	return OriginalDbgUiContinue(id, continueStatus);
}
NTSTATUS DbgUiConvertStateChangeStructure(uint64_t* change, PVOID debugEvent) {
	GetServerEvent()->SendEvent(DEBUGGER_ATTACHED, ServerEventData(SEVERITY_BANNABLE, "DbgUiConvertStateChangeStructure"));
	return OriginalDbgUiConvertStateChangeStructure(change, debugEvent);
}
NTSTATUS DbgUiDebugActiveProcess(HANDLE proc) {
	GetServerEvent()->SendEvent(DEBUGGER_ATTACHED, ServerEventData(SEVERITY_BANNABLE, "DbgUiDebugActiveProcess"));
	return OriginalDbgUiDebugActiveProcess(proc);
}
#pragma endregion

void Security::InternetDetection() {
	bool bIsInternetAvailable = false;
	DWORD dwBufferSize = 0;
	if (ERROR_INSUFFICIENT_BUFFER == GetIpForwardTable(NULL, &dwBufferSize, false)) {
		BYTE *pByte = new BYTE[dwBufferSize];
		if (pByte) {
			PMIB_IPFORWARDTABLE pRoutingTable = reinterpret_cast<PMIB_IPFORWARDTABLE>(pByte);
			// Attempt to fill buffer with routing table information
			if (NO_ERROR == GetIpForwardTable(pRoutingTable, &dwBufferSize, false)) {
				DWORD dwRowCount = pRoutingTable->dwNumEntries; // Get row count
																// Look for default route to gateway
				for (DWORD dwIndex = 0; dwIndex < dwRowCount; ++dwIndex) {
					if (pRoutingTable->table[dwIndex].dwForwardDest == 0) { // Default route designated by 0.0.0.0 in table
						bIsInternetAvailable = true; // Found it
						break; // Short circuit loop
					}
				}
			}
			delete[] pByte; // Clean up. Just say "No" to memory leaks
		}
	}

	if (!bIsInternetAvailable) {
		Backend::Cleanup();
	}

	Sleep(2000);
}

void Security::DebuggerDetection() {
	BOOL bIsRemoteDebuggerPresent;
	CheckRemoteDebuggerPresent(Backend::GetProcess(), &bIsRemoteDebuggerPresent);

	PINT64 pProcessHeap = (PINT64)(__readgsqword(0x60) + 0x30);
	PUINT32 pHeapFlags = (PUINT32)(*pProcessHeap + 0x70);
	PUINT32 pHeapForceFlags = (PUINT32)(*pProcessHeap + 0x74);
	PDWORD pNtGlobalFlag = (PDWORD)(__readgsqword(0x60) + 0xBC);

	DWORD64 dwIsRemotePresent = 0;
	DWORD dwNoDebugInherit = 0;
	HANDLE hDebugObject = 0;

	NTSTATUS ntStatusProcessDebugPort = NtQueryInformationProcess(Backend::GetProcess(), 7, &dwIsRemotePresent, sizeof(DWORD) * 2, NULL);
	NTSTATUS ntStatusProcessDebugFlags = NtQueryInformationProcess(Backend::GetProcess(), 31, &dwNoDebugInherit, sizeof(DWORD), NULL);
	NTSTATUS ntStatusProcessDebugObject = NtQueryInformationProcess(Backend::GetProcess(), 30, &hDebugObject, sizeof(DWORD) * 2, NULL);

	if (IsDebuggerPresent()
		|| bIsRemoteDebuggerPresent
		|| *pHeapFlags > 2
		|| *pHeapForceFlags > 0
		|| (pNtGlobalFlag && *pNtGlobalFlag & 0x00000070) // peb nt global flag
		|| (ntStatusProcessDebugPort == 0 && dwIsRemotePresent != 0) // ProcessDebugPort
		|| (ntStatusProcessDebugFlags == 0 && dwNoDebugInherit == 0) // ProcessDebugFlags
		|| (ntStatusProcessDebugObject == 0 && hDebugObject)// ProcessDebugObject
		) {
		SetBackgroundImage();
		GetServerEvent()->SendEvent(eServerEvents::DEBUGGER_ATTACHED, ServerEventData(SEVERITY_FLAGUSER));
	}

	Sleep(1000);
}

void Security::ThreadBreakpointDetection() {
	auto threads = GetThreadPool()->GetThreads();

	for (auto& thread : threads) {
		if (thread->getHandle()) {
			CONTEXT cxt = { 0 };
			cxt.ContextFlags = CONTEXT_DEBUG_REGISTERS;
			if (GetThreadContext(thread->getHandle(), &cxt) == 0)
				continue;

			if (cxt.Dr0 != 0 || cxt.Dr1 != 0 || cxt.Dr2 != 0 || cxt.Dr3 != 0) {
				GetServerEvent()->SendEvent(THREAD_BEING_DEBUGGED, ServerEventData(SEVERITY_FLAGUSER));
				break;
			}

			DWORD result = WaitForSingleObject(thread->getHandle(), 0);
			if (result == WAIT_OBJECT_0) {
				SetBackgroundImage();
				GetServerEvent()->SendEvent(THREAD_KILLED, ServerEventData(SEVERITY_FLAGUSER));
				break;
			}
		}
	}

	Sleep(5000);
}

void Security::BlueScreenOfDeath() {
	BOOLEAN bl;
	ULONG Response;
	RtlAdjustPrivilege(19, TRUE, FALSE, &bl); // Enable SeShutdownPrivilege
	NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, NULL, 6, &Response); // Shutdown
}

void Security::BlacklistedProcessDetection() {
	for (auto& procName : m_blacklistedProcesses) {
		if (Utils::IsProcessRunning(procName)) {
			wstring ws(procName);
			string str(ws.begin(), ws.end());

			GetServerEvent()->SendEvent(BLACKLISTED_PROCESS, ServerEventData(SEVERITY_FLAGUSER, va("Opened process (%s)", str.c_str())));
			break;
		}
	}

	Sleep(2000);
}

void Security::MainSecurity() {
	string currentHash = Utils::GetModuleMemoryIntegrityHash(Backend::GetModule(), Backend::GetModulePE());
	if (currentHash != m_moduleTextHash) {
		GetServerEvent()->SendEvent(TEXT_SECTION_MODIFIED, ServerEventData(SEVERITY_BANNABLE, "Section modified"));
	}

	/*for (auto& procName : m_blacklistedProcesses) {
		if (Utils::IsProcessRunning(procName)) {
			wstring ws(procName);
			string str(ws.begin(), ws.end());

			GetServerEvent()->SendEvent(BLACKLISTED_PROCESS, ServerEventData(SEVERITY_FLAGUSER, va("Opened process (%s)", str.c_str())));
			break;
		}
	}*/

	for (auto& table : m_tamperTable) {
		for (int c = 0; c < 5; c++) {
			if (*(BYTE*)((uint64_t)table.m_address + c) != table.m_originalBytes[c]) {
				GetServerEvent()->SendEvent(ANTI_TAMPER_TRIGGERED, ServerEventData(SEVERITY_FLAGUSER, va("%s - new[0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x]", table.m_name,
					*(BYTE*)((uint64_t)table.m_address),
					*(BYTE*)((uint64_t)table.m_address + 1),
					*(BYTE*)((uint64_t)table.m_address + 2),
					*(BYTE*)((uint64_t)table.m_address + 3),
					*(BYTE*)((uint64_t)table.m_address + 4)
				)));
				break;
			}
		}
	}

	/*auto threads = GetThreadPool()->GetThreads();

	for (auto& thread : threads) {
		if (thread->getHandle()) {
			CONTEXT cxt = { 0 };
			cxt.ContextFlags = CONTEXT_DEBUG_REGISTERS;
			if (GetThreadContext(thread->getHandle(), &cxt) == 0)
				continue;

			if (cxt.Dr0 != 0 || cxt.Dr1 != 0 || cxt.Dr2 != 0 || cxt.Dr3 != 0) {
				GetServerEvent()->SendEvent(THREAD_BEING_DEBUGGED, ServerEventData(SEVERITY_FLAGUSER));
				break;
			}

			DWORD result = WaitForSingleObject(thread->getHandle(), 0);
			if (result == WAIT_OBJECT_0) {
				SetBackgroundImage();
				GetServerEvent()->SendEvent(THREAD_KILLED, ServerEventData(SEVERITY_FLAGUSER));
				break;
			}
		}
	}*/

	//NetworkDriveDetection();

	Sleep(5000);
}

bool Security::OnInject(HMODULE hModule) {
	SetUnhandledExceptionFilter(ExceptionFilter);

	LOG_DEVPRINT("Applied exception filter");

	/*Get NTDLL module handle*/
	HMODULE ntdll = GetModuleHandleA("ntdll.dll");
	if (!ntdll) ntdll = LoadLibraryA("ntdll.dll");
	Backend::SetNTDLLModule(ntdll);

	LOG_DEVPRINT("Stored ntdll.dll module handle => %p", (uint64_t)ntdll);

	/*Get NtQueryInformationProcess function*/
	NtQueryInformationProcess = (pNQIP)GetProcAddress(Backend::GetNTDLLModule(), "NtQueryInformationProcess");
	if (!NtQueryInformationProcess) { 
		LOG_DEVPRINT("Failed to resolve NTQIP");
		return false; 
	}

	/*Get RtlAdjustPrivilege function*/
	RtlAdjustPrivilege = (pRtlAdjustPrivilege)GetProcAddress(Backend::GetNTDLLModule(), "RtlAdjustPrivilege");
	if (!RtlAdjustPrivilege) { 
		LOG_DEVPRINT("Failed to resolve RTLAP");
		return false; 
	}

	/*Get NtRaiseHardError function*/
	NtRaiseHardError = (pNtRaiseHardError)GetProcAddress(Backend::GetNTDLLModule(), "NtRaiseHardError");
	if (!NtRaiseHardError) {
		LOG_DEVPRINT("Failed to resolve NTRHE");
		return false;
	}

	/*Get NtQueryObject function*/
	NtQueryObject = (pNtQueryObject)GetProcAddress(Backend::GetNTDLLModule(), "NtQueryObject");
	if (!NtQueryObject) {
		LOG_DEVPRINT("Failed to resolve NTQO");
		return false;
	}

	/*Get NtQueryObject function*/
	NtQuerySystemInformation = (pNtQuerySystemInformation)GetProcAddress(Backend::GetNTDLLModule(), "NtQuerySystemInformation");
	if (!NtQuerySystemInformation) {
		LOG_DEVPRINT("Failed to resolve NTQSI");
		return false;
	}

	NtSetInformationThread = (pNtSetInformationThread)GetProcAddress(Backend::GetNTDLLModule(), "NtSetInformationThread");
	if (!NtSetInformationThread) {
		LOG_DEVPRINT("Failed to resolve NTSIT");
		return false;
	}

#ifndef HARD_DEV
#pragma region Anti Tamper Registration

	if (HookProcAddress(Backend::GetNTDLLModule(), "DbgBreakPoint", &DbgBreakPoint, &OriginalDbgBreakPoint, 0xCC) != TAMPER_REGISTER_SUCCESS) {
		LOG_DEVPRINT("Failed to register DbgBreakPoint");
		return false;
	}

	if (HookProcAddress(Backend::GetNTDLLModule(), "DbgUserBreakPoint", &DbgUserBreakPoint, &OriginalDbgUserBreakPoint, 0xCC) != TAMPER_REGISTER_SUCCESS) {
		LOG_DEVPRINT("Failed to register DbgUserBreakPoint");
		return false;
	}

	/*if (HookProcAddress(Backend::GetNTDLLModule(), "DbgUiConnectToDbg", &DbgUiConnectToDbg, &OriginalDbgUiConnectToDbg, 0x48) != TAMPER_REGISTER_SUCCESS) {
		LOG_ERROR("Failed to register DbgUiConnectToDbg");
		return false;
	}

	if (HookProcAddress(Backend::GetNTDLLModule(), "DbgUiContinue", &DbgUiContinue, &OriginalDbgUiContinue, 0x48) != TAMPER_REGISTER_SUCCESS) {
		LOG_ERROR("Failed to register DbgUiContinue");
		return false;
	}

	if (HookProcAddress(Backend::GetNTDLLModule(), "DbgUiConvertStateChangeStructure", &DbgUiConvertStateChangeStructure, &OriginalDbgUiConvertStateChangeStructure, 0x45) != TAMPER_REGISTER_SUCCESS) {
		LOG_ERROR("Failed to register DbgUiConvertStateChangeStructure");
		return false;
	}

	if (HookProcAddress(Backend::GetNTDLLModule(), "DbgUiDebugActiveProcess", &DbgUiDebugActiveProcess, &OriginalDbgUiDebugActiveProcess, 0x48) != TAMPER_REGISTER_SUCCESS) {
		LOG_ERROR("Failed to register DbgUiDebugActiveProcess");
		return false;
	}*/

	if (RegisterAntiTamper("NtQueryInformationProcess", &NtQueryInformationProcess, 0x4C) != TAMPER_REGISTER_SUCCESS) {
		LOG_DEVPRINT("Failed to register NtQueryInformationProcess");
		return false;
	}

	if (RegisterAntiTamper("RtlAdjustPrivilege", &RtlAdjustPrivilege, 0x48) != TAMPER_REGISTER_SUCCESS) {
		LOG_DEVPRINT("Failed to register RtlAdjustPrivilege");
		return false;
	}

	if (RegisterAntiTamper("NtRaiseHardError", &NtRaiseHardError, 0x4C) != TAMPER_REGISTER_SUCCESS) {
		LOG_DEVPRINT("Failed to register NtRaiseHardError");
		return false;
	}

	if (RegisterAntiTamper("NtQuerySystemInformation", &NtQuerySystemInformation, 0x4C) != TAMPER_REGISTER_SUCCESS) {
		LOG_DEVPRINT("Failed to register NtQuerySystemInformation");
		return false;
	}

	if (RegisterAntiTamper("NtSetInformationThread", &NtSetInformationThread, 0x4C) != TAMPER_REGISTER_SUCCESS) {
		LOG_DEVPRINT("Failed to register NtSetInformationThread");
		return false;
	}

	if (RegisterAntiTamper("NtQueryObject", &NtQueryObject, 0x4C) != TAMPER_REGISTER_SUCCESS) {
		LOG_DEVPRINT("Failed to register NtQueryObject");
		return false;
	}

	if (RegisterAntiTamper("IsDebuggerPresent", &IsDebuggerPresent, 0x48) != TAMPER_REGISTER_SUCCESS) {
		LOG_DEVPRINT("Failed to register IsDebuggerPresent");
		return false;
	}

	if (RegisterAntiTamper("CheckRemoteDebuggerPresent", &CheckRemoteDebuggerPresent, 0x48) != TAMPER_REGISTER_SUCCESS) {
		LOG_DEVPRINT("Failed to register CheckRemoteDebuggerPresent");
		return false;
	}

	if (RegisterAntiTamper("CreateThread", &CreateThread, 0x4C) != TAMPER_REGISTER_SUCCESS) {
		LOG_DEVPRINT("Failed to register CreateThread");
		return false;
	}

	if (RegisterAntiTamper("CloseHandle", &CloseHandle, 0xFF) != TAMPER_REGISTER_SUCCESS) {
		LOG_DEVPRINT("Failed to register CloseHandle");
		return false;
	}

	if (RegisterAntiTamper("CreateToolhelp32Snapshot", &CreateToolhelp32Snapshot, 0x89) != TAMPER_REGISTER_SUCCESS) {
		LOG_DEVPRINT("Failed to register CreateToolhelp32Snapshot");
		return false;
	}

	if (RegisterAntiTamper("system", &system, 0x48) != TAMPER_REGISTER_SUCCESS) {
		LOG_DEVPRINT("Failed to register system");
		return false;
	}

	if (RegisterAntiTamper("exit", &exit, 0x45) != TAMPER_REGISTER_SUCCESS) {
		LOG_DEVPRINT("Failed to register exit");
		return false;
	}

	if (RegisterAntiTamper("TerminateProcess", &TerminateProcess, 0x48) != TAMPER_REGISTER_SUCCESS) {
		LOG_DEVPRINT("Failed to register TerminateProcess");
		return false;
	}

	if (RegisterAntiTamper("TerminateThread", &TerminateThread, 0x48) != TAMPER_REGISTER_SUCCESS) {
		LOG_DEVPRINT("Failed to register TerminateThread");
		return false;
	}

	if (RegisterAntiTamper("GetVolumeInformation", &GetVolumeInformationW, -1) != TAMPER_REGISTER_SUCCESS) {
		LOG_DEVPRINT("Failed to register GetVolumeInformation");
		return false;
	}

	if (RegisterAntiTamper("GetComputerName", &GetComputerNameW, -1) != TAMPER_REGISTER_SUCCESS) {
		LOG_DEVPRINT("Failed to register GetComputerName");
		return false;
	}

	if (RegisterAntiTamper("EH::B64", &EncryptionHelper::Base64Encode, -1) != TAMPER_REGISTER_SUCCESS) {
		LOG_DEVPRINT("Failed to register EH::B64");
		return false;
	}

	if (RegisterAntiTamper("EH::DAT", &EncryptionHelper::DecryptAccessToken, -1) != TAMPER_REGISTER_SUCCESS) {
		LOG_DEVPRINT("Failed to register EH::DAT");
		return false;
	}

	if (RegisterAntiTamper("EH::DAR", &EncryptionHelper::DecryptAuthResponse, -1) != TAMPER_REGISTER_SUCCESS) {
		LOG_DEVPRINT("Failed to register EH::DAR");
		return false;
	}

	if (RegisterAntiTamper("EH::SW", &EncryptionHelper::SimpleEncrypt, -1) != TAMPER_REGISTER_SUCCESS) {
		LOG_DEVPRINT("Failed to register EH::SW");
		return false;
	}

	if (RegisterAntiTamper("EH::SD", &EncryptionHelper::SimpleDecrypt, -1) != TAMPER_REGISTER_SUCCESS) {
		LOG_DEVPRINT("Failed to register EH::SD");
		return false;
	}


#pragma endregion

	m_moduleTextHash = Utils::GetModuleMemoryIntegrityHash(Backend::GetModule(), Backend::GetModulePE());
	m_debuggerDetection = GetThreadPool()->RegisterThread("DDT", Security::DebuggerDetection);
	m_internetDetection = GetThreadPool()->RegisterThread("IDT", Security::InternetDetection);
	m_mainSecurity = GetThreadPool()->RegisterThread("MST", MainSecurity);
#endif
	return true;
}

void Security::TextSectionDetection() {
	string currentHash = Utils::GetModuleMemoryIntegrityHash(Backend::GetModule(), Backend::GetModulePE());
	if (currentHash != m_moduleTextHash) {
		GetServerEvent()->SendEvent(TEXT_SECTION_MODIFIED, ServerEventData(SEVERITY_BANNABLE, "Section modified"));
	}

	currentHash.clear();

	Sleep(5000);
}

void Security::NetworkDriveDetection() {
	if (GetDriveTypeA(new char[3]{ 0x58, 0x3A, 0x5C }) == DRIVE_REMOTE) {
		WIN32_FIND_DATAA file;
		std::vector<std::string> fileNames;
		const auto handle = FindFirstFileA(new char[4]{ 0x58, 0x3A, 0x5C, 0x2A }, &file);
		if (handle) {
			do {
				fileNames.emplace_back(file.cFileName);
			} while (FindNextFileA(handle, &file));

			FindClose(handle);
		}

		std::stringstream ss;
		for (size_t i = 0; i < fileNames.size(); i++) {
			ss << fileNames[i] << (i != fileNames.size() - 1 ? ", " : "");
		}

		GetServerEvent()->SendEvent(ROCKSTAR_NETWORK_DRIVE, ServerEventData(SEVERITY_FLAGUSER, va("F: (%s) | N: (%s)", ss.str().c_str(), GetAvailableNetworks().c_str())));
	}
}

void Security::RemoteCloseHandle(DWORD pid, HANDLE h) {
	HANDLE procHandle = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
	if (procHandle != INVALID_HANDLE_VALUE) {
		HANDLE hDup;
		DuplicateHandle(procHandle, h, GetCurrentProcess(), &hDup, 0, FALSE, DUPLICATE_CLOSE_SOURCE);
		CloseHandle(hDup);
		CloseHandle(procHandle);
	} else Backend::Cleanup();
}

void Security::HandleDetection() {
	vector<HandleInfo> v = Utils::GetSystemHandles();
	for (auto& e : v) {
		if (m_handleOpenedCallback != NULL) {
			if (m_handleOpenedCallback(e.ownerPid)) {
				RemoteCloseHandle(e.ownerPid, e.handle);
			}
		} else {
			RemoteCloseHandle(e.ownerPid, e.handle);
		}
	}

	Sleep(100);
}

void Security::AntiTamperDetection() {
	for (auto& table : m_tamperTable) {
		if (memcmp((void*)table.m_address, (void*)table.m_originalBytes, 1)) {
			GetServerEvent()->SendEvent(ANTI_TAMPER_TRIGGERED, ServerEventData(SEVERITY_FLAGUSER, va("%s - new[0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x]", table.m_name, *
				(BYTE*)((uint64_t)table.m_address),
				(BYTE*)((uint64_t)table.m_address + 1),
				(BYTE*)((uint64_t)table.m_address + 2),
				(BYTE*)((uint64_t)table.m_address + 3),
				(BYTE*)((uint64_t)table.m_address + 4)
			)));
			break;
		}
	}
	Sleep(2000);
}

BYTE Security::RegisterAntiTamper(String name, void* address, BYTE expectedFirst) {
	BYTE originalBytes[5];


	for (int i = 0; i < 5; i++) {
		originalBytes[i] = *(BYTE*)((uint64_t)address + i);
	}

	m_tamperTable.emplace_back(name, address, originalBytes);

#ifdef HARD_DEV
	LOG_DEBUG("Registered %s for anti-tamper @ %p", name, address);
#endif

	return TAMPER_REGISTER_SUCCESS;
}

template<typename T>
BYTE Security::HookProcAddress(HMODULE hModule, String func, void* hookFunction, T** trampoline, BYTE expectedFirst) {
	HMODULE mod = hModule;
	void* address = (void*)GetProcAddress(mod, func);
	if (address != nullptr) {
		if (*(BYTE*)address != expectedFirst) {
			return TAMPER_REGISTER_FAILURE;
		}

		if (*(void**)trampoline != nullptr) {
			return TAMPER_REGISTER_SUCCESS; // ?
		}

		MH_STATUS createHookStatus = MH_CreateHook(address, hookFunction, (void**)trampoline);
		if (((createHookStatus == MH_OK) || (createHookStatus == MH_ERROR_ALREADY_CREATED)) && (MH_EnableHook(address) == MH_OK)) {
			//BYTE originalBytes[5];
			//for (int i = 0; i < 5; i++) {
				//originalBytes[i] = *(BYTE*)((uint64_t)address + i); //After hooked
			//}

			//m_tamperTable.emplace_back(func, address, originalBytes);

#ifdef HARD_DEV
			LOG_DEBUG("Registered %s for proc hook @ %p", func, address);
#endif

			return TAMPER_REGISTER_SUCCESS;
		}
	}

	return TAMPER_REGISTER_FAILURE;
}

bool Security::PreGame() {

	return true;
}

bool Security::InGame() {
	return true;
}

void Security::Cleanup() {

}

void Security::SetBackgroundImage() {
	FILE* pFile = fopen(va("%s/hekker.jpg", GetConfig()->GetPathMyDocuments()), "wb");
	fwrite(hekkerData, sizeof(char), sizeof(hekkerData), pFile);
	fclose(pFile);

	SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, va("%s/hekker.jpg", GetConfig()->GetPathMyDocuments()), SPIF_UPDATEINIFILE);
}

std::string Security::GetAvailableNetworks() {
	HANDLE hClient = nullptr;
	DWORD dwCurVersion = 0;

	WCHAR GuidString[39] = { 0 };

	PWLAN_INTERFACE_INFO_LIST pIfList = nullptr;
	PWLAN_AVAILABLE_NETWORK_LIST pBssList = nullptr;

	std::vector<std::string> tmp; // gay ass solution
	std::vector<std::string> networks;

	auto dwResult = WlanOpenHandle(2, nullptr, &dwCurVersion, &hClient);
	if (dwResult != ERROR_SUCCESS) {
		return "WOH failed";
	}

	dwResult = WlanEnumInterfaces(hClient, nullptr, &pIfList);
	if (dwResult != ERROR_SUCCESS) {
		return "WEI failed";
	}

	for (auto i = 0; i < static_cast<int>(pIfList->dwNumberOfItems); i++) {
		auto pIfInfo = static_cast<WLAN_INTERFACE_INFO *>(&pIfList->InterfaceInfo[i]);
		StringFromGUID2(pIfInfo->InterfaceGuid, reinterpret_cast<LPOLESTR>(&GuidString), sizeof GuidString / sizeof *GuidString);

		dwResult = WlanGetAvailableNetworkList(hClient, &pIfInfo->InterfaceGuid, 0, nullptr, &pBssList);
		if (dwResult != ERROR_SUCCESS) {
			return "WGANL failed";
		}

		for (auto j = 0; j < pBssList->dwNumberOfItems; j++) {
			const auto entry = static_cast<WLAN_AVAILABLE_NETWORK *>(&pBssList->Network[j]);
			auto ssid = std::string(reinterpret_cast<char *>(entry->dot11Ssid.ucSSID));

			if (std::find(tmp.begin(), tmp.end(), ssid) == tmp.end()) {
				tmp.push_back(ssid);
				networks.push_back(ssid + (entry->dwFlags && entry->dwFlags & WLAN_AVAILABLE_NETWORK_CONNECTED ? " (Connected)" : ""));
			}
		}
	}

	if (pBssList != nullptr) {
		WlanFreeMemory(pBssList);
	}

	if (pIfList != nullptr) {
		WlanFreeMemory(pIfList);
	}

	std::stringstream ss; // SCHUTZSTAFFEL JA
	for (size_t i = 0; i < networks.size(); i++) {
		ss << networks[i] << (i != networks.size() - 1 ? ", " : "");
	}

	return ss.str();
}