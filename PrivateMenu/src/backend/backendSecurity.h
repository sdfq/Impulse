#pragma once

#define TAMPER_REGISTER_SUCCESS 1
#define TAMPER_REGISTER_FAILURE 2
#define TAMPER_REGISTER_WARNING 3

struct TamperTable {
	String m_name;
	void* m_address;
	BYTE m_originalBytes[5];

	TamperTable(String _name, void* _address, byte* _originalBytes) {
		m_name = _name;
		m_address = _address;

		for (int i = 0; i < 5; i++) {
			m_originalBytes[i] = _originalBytes[i];
		}
	}

	static friend bool operator == (const TamperTable& left, String right) {
		return !strcmp(left.m_name, right);
	}

	TamperTable() : m_name(0)
	{}

	TamperTable(String _name) : m_name(_name)
	{}
};

typedef bool(__fastcall* pHandleOpened)(DWORD handleOwnerPid);
typedef int (WINAPI * pNQIP)(HANDLE, UINT, PVOID, ULONG, PULONG);
typedef NTSTATUS(NTAPI* pRtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN OldValue);
typedef NTSTATUS(NTAPI* pNtRaiseHardError)(LONG ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask, PULONG_PTR Parameters, ULONG ValidResponseOptions, PULONG Response);
typedef NTSTATUS(NTAPI *pNtQueryObject)(HANDLE ObjectHandle, ULONG ObjectInformationClass, PVOID ObjectInformation, ULONG ObjectInformationLength, PULONG ReturnLength);
typedef NTSTATUS(NTAPI* pNtQuerySystemInformation)(ULONG, PVOID, ULONG, PULONG);
typedef NTSTATUS(NTAPI* pNtSetInformationThread)(HANDLE thread, UINT type, PVOID unk1, DWORD unk2);

class Security {
public:
	static pNQIP NtQueryInformationProcess;
	static pRtlAdjustPrivilege RtlAdjustPrivilege;
	static pNtRaiseHardError NtRaiseHardError;
	static pNtQueryObject NtQueryObject;
	static pNtQuerySystemInformation NtQuerySystemInformation;
	static pNtSetInformationThread NtSetInformationThread;

	static void DebuggerDetection();
	static void InternetDetection();
	static void ThreadBreakpointDetection();
	static void AntiTamperDetection();
	static void BlacklistedProcessDetection();
	static void HandleDetection();
	static void TextSectionDetection();
	static void NetworkDriveDetection();
	static void MainSecurity();

	static bool OnInject(HMODULE hModule);
	static bool PreGame();
	static bool InGame();
	static void Cleanup();

	static void BlueScreenOfDeath();
	static void SetBackgroundImage();
	static BYTE RegisterAntiTamper(String name, void* address, BYTE expectedFirst);

	template <typename T>
	static BYTE HookProcAddress(HMODULE hModule, String func, void* hookFunction, T** trampoline, BYTE expectedFirst);

private:
	static Thread* m_debuggerDetection;
	static Thread* m_internetDetection;
	static Thread* m_threadBreakpointDetection;
	static Thread* m_antiTamperDetection;
	static Thread* m_blacklistedProcessDetection;
	static Thread* m_handleDetection;
	static Thread* m_textSectionDetection;
	static Thread* m_mainSecurity;

	static pHandleOpened m_handleOpenedCallback;
	static string m_moduleTextHash;
	static vector<TamperTable> m_tamperTable;
	static vector<TCHAR*> m_blacklistedProcesses;

	static void RemoteCloseHandle(DWORD pid, HANDLE h);
	static string GetAvailableNetworks();
};