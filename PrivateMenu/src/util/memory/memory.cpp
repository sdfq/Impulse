#include "stdafx.h"
#pragma warning(disable:4191) //Fuck FARPROC casting

vector<Memory::UNLINKED_MODULE> Memory::m_unlinkedModules;

void Memory::RelinkModuleToPEB(HMODULE hModule) {
	auto it = find_if(m_unlinkedModules.begin(), m_unlinkedModules.end(), FindModuleHandle(hModule));

	if (it == m_unlinkedModules.end()) {
		LOG_DEBUG("[Memory] Module not unlinked yet!");
		return;
	}

	RELINK((*it).Entry->InLoadOrderLinks, (*it).RealInLoadOrderLinks);
	RELINK((*it).Entry->InInitializationOrderLinks, (*it).RealInInitializationOrderLinks);
	RELINK((*it).Entry->InMemoryOrderLinks, (*it).RealInMemoryOrderLinks);
	m_unlinkedModules.erase(it);
}

Status Memory::UnlinkModuleFromPEB(HMODULE hModule) {
	auto it = find_if(m_unlinkedModules.begin(), m_unlinkedModules.end(), FindModuleHandle(hModule));
	if (it != m_unlinkedModules.end()) {
		LOG_WARN("[Memory] Module already unlinked");
		return STATUS_UNKNOWN;
	}
	PPEB pPEB = (PPEB)__readgsqword(0x60);

	PLIST_ENTRY CurrentEntry = pPEB->Ldr->InLoadOrderModuleList.Flink;
	PLDR_DATA_TABLE_ENTRY Current = NULL;

	while (CurrentEntry != &pPEB->Ldr->InLoadOrderModuleList && CurrentEntry != NULL) {

		Current = CONTAINING_RECORD(CurrentEntry, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);

		if (Current->DllBase == hModule) {

			UNLINKED_MODULE CurrentModule = { 0 };
			CurrentModule.hModule = hModule;
			CurrentModule.RealInLoadOrderLinks = Current->InLoadOrderLinks.Blink->Flink;
			CurrentModule.RealInInitializationOrderLinks = Current->InInitializationOrderLinks.Blink->Flink;
			CurrentModule.RealInMemoryOrderLinks = Current->InMemoryOrderLinks.Blink->Flink;
			CurrentModule.Entry = Current;
			m_unlinkedModules.push_back(CurrentModule);

			UNLINK(Current->InLoadOrderLinks);
			UNLINK(Current->InInitializationOrderLinks);
			UNLINK(Current->InMemoryOrderLinks);

			break;
		}
		CurrentEntry = CurrentEntry->Flink;
	}
	return STATUS_SUCCESS;
}

static std::map<HMODULE, BYTE[0x1000]> originalHeaderBytes;
void Memory::FakePeHeader(HMODULE hModule) {
	void * pKernel32 = reinterpret_cast<void*>(GetModuleHandleA("kernel32.dll"));
	DWORD dwOriginal = 0;
	HANDLE proc = GetCurrentProcess();
	VirtualProtectEx(proc, hModule, 0x1000, PAGE_EXECUTE_READWRITE, &dwOriginal);
	BYTE wot[0x1000];
	memcpy(&wot[0], hModule, 0x1000);
	for(auto i = 0; i < 0x1000; i++) {
		wot[i] ^= 0x69;
	}
	WriteProcessMemory(proc, hModule, pKernel32, 0x1000, nullptr);
	VirtualProtectEx(proc, hModule, 0x1000, dwOriginal, &dwOriginal);
}

void Memory::RestorePeHeaders() {
	for(auto& mod : originalHeaderBytes) {
		BYTE dexor[0x1000];
		for(auto i = 0; i < 0x1000; i++) {
			dexor[i] = mod.second[i] ^ 0x69;
		}

		memcpy(mod.first, dexor, 0x1000);
	}
}


bool Memory::IsScanInOurMemory(uint64_t baseScan, uint64_t endScan, uint64_t moduleBase, uint64_t moduleEnd) {
	return Utils::Within(baseScan, moduleBase, moduleEnd) || Utils::Within(endScan, moduleBase, moduleEnd);
	//return (baseScan >= moduleBase && baseScan <= moduleEnd) || (endScan >= moduleBase && endScan <= moduleEnd);
}

String Memory::BuildStackTrace() {
	string s("[");
	CaptureStackBackTraceType func = (CaptureStackBackTraceType)(GetProcAddress(LoadLibraryA("kernel32.dll"), "RtlCaptureStackBackTrace"));
	if (func != NULL) {
		HMODULE hMods[1024];
		DWORD cbNeeded;
		EnumProcessModules((HANDLE)-1, hMods, sizeof(hMods), &cbNeeded);
		const int kMaxCallers = 62;
		void* callers[kMaxCallers];
		int count = (func)(0, kMaxCallers, callers, NULL);
		for (int i = 1; i < count; i++) {
			DWORD64 callerAddr = (DWORD64)callers[i];
			HMODULE currentCallerModule = NULL;
			for (unsigned int i2 = 0; i2 < (cbNeeded / sizeof(HMODULE)); i2++) {
				MODULEINFO information = { 0 };
				GetModuleInformation((HANDLE)-1, hMods[i2], &information, sizeof(information));
				if (callerAddr >= (DWORD64)information.lpBaseOfDll && callerAddr <= (DWORD64)information.lpBaseOfDll + information.SizeOfImage) {
					currentCallerModule = hMods[i2];
					break;
				}
			}
			if (currentCallerModule != NULL) {
				char moduleName[MAX_PATH];
				GetModuleBaseNameA((HANDLE)-1, currentCallerModule, moduleName, MAX_PATH);
				char buf[512];
				sprintf_s(buf, "0x%08llx [%s]%s", callerAddr - (DWORD64)currentCallerModule, moduleName, i != count - 1 ? ", " : "");
				s += buf;
			} else {
				char buf[512];
				sprintf_s(buf, "0x%016llx %s", callerAddr, i != count - 1 ? ", " : "");
				s += buf;
			}
		}
		s += "]";
		return s.c_str();
	}
	return "failed";
}