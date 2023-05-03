#include "stdafx.h"

namespace PRIVATE {
	typedef BOOL(__stdcall *tVirtualProtectEx)(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect);
	typedef HANDLE(__stdcall *tOpenProcess)(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId);
	typedef BOOL(__stdcall *tCloseHandle)(HANDLE handle);

	struct VirtualProtectBypassParams {
		tVirtualProtectEx VirtualProtectFnc;
		tOpenProcess OpenProcessFnc;
		tCloseHandle CloseHandleFnc;

		DWORD TargetProcessId;


		LPVOID lpAddress;
		SIZE_T dwSize;
		DWORD flNewProtect;
		DWORD lpflOldProtect;

		BOOL Result;


		VirtualProtectBypassParams(DWORD targetProcessId, LPVOID _lpAddress, SIZE_T _dwSize, DWORD _flNewProtect) {
			VirtualProtectFnc = VirtualProtectEx;
			OpenProcessFnc = OpenProcess;
			CloseHandleFnc = CloseHandle;

			TargetProcessId = targetProcessId;

			lpAddress = _lpAddress;
			dwSize = _dwSize;
			flNewProtect = _flNewProtect;
		}
	};
	LPVOID VPThreadPtr = 0, VPParamsPtr = 0;
	DWORD WINAPI ThreadVirtualProtect(LPVOID params) {
		VirtualProtectBypassParams *T = (VirtualProtectBypassParams*)(params);
		HANDLE h = T->OpenProcessFnc(PROCESS_ALL_ACCESS, false, T->TargetProcessId);
		T->Result = T->VirtualProtectFnc(h, T->lpAddress, T->dwSize, T->flNewProtect, &T->lpflOldProtect);
		T->CloseHandleFnc(h);
		return TRUE;
	}
}

DWORD FindProcessId(const WCHAR* _processName) {
	const std::wstring& processName = std::wstring(_processName);
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE)
		return 0;

	Process32First(processesSnapshot, &processInfo);
	if (!processName.compare(processInfo.szExeFile)) {
		CloseHandle(processesSnapshot);
		return processInfo.th32ProcessID;
	}

	while (Process32Next(processesSnapshot, &processInfo)) {
		if (!processName.compare(processInfo.szExeFile)) {
			CloseHandle(processesSnapshot);
			return processInfo.th32ProcessID;
		}
	}

	CloseHandle(processesSnapshot);
	return 0;
}

BOOL Ext_VirtualProtect(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect) {
	using namespace PRIVATE;
	VirtualProtectBypassParams params(GetCurrentProcessId(), lpAddress, dwSize, flNewProtect);
	HANDLE eHandle = OpenProcess(PROCESS_ALL_ACCESS, false, FindProcessId(L"explorer.exe"));
	if (!VPThreadPtr || !VPParamsPtr) {
		VPThreadPtr = VirtualAllocEx(eHandle, NULL, 512, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		VPParamsPtr = VirtualAllocEx(eHandle, NULL, sizeof(VirtualProtectBypassParams), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	}
	if (WriteProcessMemory(eHandle, VPThreadPtr, ThreadVirtualProtect, 512, NULL) &&
		WriteProcessMemory(eHandle, VPParamsPtr, &params, sizeof(VirtualProtectBypassParams), NULL)
		) {
		HANDLE thread = CreateRemoteThread(eHandle, NULL, NULL, static_cast<LPTHREAD_START_ROUTINE>(VPThreadPtr), VPParamsPtr, NULL, NULL);
		if (thread) {
			WaitForSingleObject(thread, INFINITE);
			if (ReadProcessMemory(eHandle, VPParamsPtr, &params, sizeof(VirtualProtectBypassParams), NULL)) {
				*lpflOldProtect = params.lpflOldProtect;
				return params.Result;
			} else {
				LOG_DEVPRINT("Failed to verify if the function succeed");
			}
		} else {
			LOG_DEVPRINT("CreateRemoteThread failed");
		}
	}
	return false;
}

BOOL ClearCodeInjectionAllocatedMemory() {
	using namespace PRIVATE;
	BOOL result = VirtualFree(VPThreadPtr, NULL, NULL) && VirtualFree(VPParamsPtr, NULL, NULL);
	return result;
}