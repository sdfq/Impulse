#pragma once

#pragma warning( disable : 4312 )

template<typename T>
inline T* SetAddressTypeForUse(DWORD64 address, int offset = 0) {
	return reinterpret_cast<T*>(reinterpret_cast<char*>(address) + offset);
}

template<typename T>
inline uint64_t GetAddressFromInstruction(T address, int offset = 0, int opSize = 3, int opLength = 7) {
	T _address = (address + offset);
	return (uint64_t)(*reinterpret_cast<int*>(_address + opSize) + _address + opLength);
}

template <typename T>
inline Status SimpleIsValidAddress(T* address, int offsetted = 0) {
	return ((address >= (PVOID)0x10000) && (address < ((PVOID)0x7fffffffffffffff)) && address != nullptr && !IsBadReadPtr(address, sizeof(address)) && address != (T*)offsetted);
}
template <typename T>
inline Status IsValidAddress(T* address, string name, bool isImportant, int offsetted = 0, bool isPattern = true) {
	if ((address >= (PVOID)0x10000) && (address < ((PVOID)0x7fffffffffffffff)) && address != nullptr && !IsBadReadPtr(address, sizeof(address)) && address != (T*)offsetted) {
		if (isPattern) {
			LOG_DEBUG("[Pattern] Found %s", name.c_str());
		}

		return STATUS_SUCCESS;
	}

	if (isImportant) {
		LOG_ERROR("[Pattern] Failed to find %s", name.c_str());
		return STATUS_FATAL;
	}

	LOG_WARN("[Pattern] Failed to find %s", name.c_str());
	return STATUS_WARNING;
}

class Memory {
public:
	typedef USHORT(WINAPI *CaptureStackBackTraceType)(__in ULONG, __in ULONG, __out PVOID*, __out_opt PULONG);
	static String BuildStackTrace();
	static void RelinkModuleToPEB(HMODULE hModule);
	static Status UnlinkModuleFromPEB(HMODULE hModule);
	static void FakePeHeader(HMODULE hModule);
	static void RestorePeHeaders();
	static bool IsScanInOurMemory(uint64_t baseScan, uint64_t endScan, uint64_t moduleBase, uint64_t moduleEnd);
	static void Cleanup() { for (UNLINKED_MODULE unlinkedModule : m_unlinkedModules) RelinkModuleToPEB(unlinkedModule.hModule); }

private:
	typedef struct _PEB_LDR_DATA {
		UINT8 _PADDING_[12];
		LIST_ENTRY InLoadOrderModuleList;
		LIST_ENTRY InMemoryOrderModuleList;
		LIST_ENTRY InInitializationOrderModuleList;
	} PEB_LDR_DATA, *PPEB_LDR_DATA;

	typedef struct _PEB {
		UINT8 _PADDING_[24];
		PEB_LDR_DATA* Ldr;
	} PEB, *PPEB;

	typedef struct _LDR_DATA_TABLE_ENTRY {
		LIST_ENTRY InLoadOrderLinks;
		LIST_ENTRY InMemoryOrderLinks;
		LIST_ENTRY InInitializationOrderLinks;
		VOID* DllBase;
	} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

	typedef struct _UNLINKED_MODULE {
		HMODULE hModule;
		PLIST_ENTRY RealInLoadOrderLinks;
		PLIST_ENTRY RealInMemoryOrderLinks;
		PLIST_ENTRY RealInInitializationOrderLinks;
		PLDR_DATA_TABLE_ENTRY Entry;
	} UNLINKED_MODULE;

#define UNLINK(x)                   \
    (x).Flink->Blink = (x).Blink;   \
    (x).Blink->Flink = (x).Flink;
#define RELINK(x, real)         \
    (x).Flink->Blink = (real);  \
    (x).Blink->Flink = (real);  \
    (real)->Blink = (x).Blink;  \
    (real)->Flink = (x).Flink;

	struct FindModuleHandle {
		HMODULE m_hModule;
		FindModuleHandle(HMODULE hModule) : m_hModule(hModule) {}
		bool operator() (UNLINKED_MODULE const &Module) const {
			return (Module.hModule == m_hModule);
		}
	};

	static vector<UNLINKED_MODULE> m_unlinkedModules;
};