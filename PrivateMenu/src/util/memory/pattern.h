#pragma once

struct PatternByte {
	PatternByte() : ignore(true) {
		//
	}

	PatternByte(string byteString, bool ignoreThis = false) {
		data = StringToUint8(byteString);
		ignore = ignoreThis;
	}

	bool ignore;
	UINT8 data;

private:
	UINT8 StringToUint8(string str) {
		istringstream iss(str);

		UINT32 ret;

		if (iss >> hex >> ret) {
			return (UINT8)ret;
		}

		return 0;
	}
};

namespace Pattern {
	extern map<string, uint64_t> m_storedAddresses;
	void Initialize();
	void Finalize();
	static DWORD64 Scanner(string name, DWORD64 dwStart, DWORD64 dwLength, string s) {
		vector<PatternByte> p;
		istringstream iss(s);
		string w;

		while (iss >> w) {
			if (w.data()[0] == '?') {
				p.push_back(PatternByte());
			} else if (w.length() == 2 && isxdigit(w.data()[0]) && isxdigit(w.data()[1])) { // Hex
				p.push_back(PatternByte(w));
			} else {
				return NULL;
			}
		}

		auto it = m_storedAddresses.find(name);
		if (it != m_storedAddresses.end()) {
			UINT8* lpCurrentByte = (UINT8*)(dwStart + it->second);
			bool found = true;

			for (size_t ps = 0; ps < p.size(); ps++) {
				if (p[ps].ignore == false && lpCurrentByte[ps] != p[ps].data) {
					found = false;
				}
			}
			if (found) {
				return (DWORD64)lpCurrentByte;
			}
		}

		for (DWORD64 i = 0; i < dwLength; i++) {
			UINT8* lpCurrentByte = (UINT8*)(dwStart + i);

			bool found = true;

			for (size_t ps = 0; ps < p.size(); ps++) {
				if (p[ps].ignore == false && lpCurrentByte[ps] != p[ps].data) {
					found = false;
					break;
				}
			}
			if (found) {
				MODULEINFO module = {};
				GetModuleInformation(GetCurrentProcess(), GetModuleHandle(nullptr), &module, sizeof(MODULEINFO));
				m_storedAddresses.insert({ name , (uint64_t)lpCurrentByte - (uint64_t)module.lpBaseOfDll });
				return (DWORD64)lpCurrentByte;
			}
		}
		return NULL;
	}

	static DWORD64 Scan(String name, string s) {
		MODULEINFO module = {};
		GetModuleInformation(GetCurrentProcess(), GetModuleHandle(nullptr), &module, sizeof(MODULEINFO));
		return Scanner(name, (DWORD64)module.lpBaseOfDll, (DWORD64)module.SizeOfImage, s);
	}

	static DWORD64 ScanModule(string name, string s, MODULEINFO moduleInfo = {}) {
		return Scanner(name, (DWORD64)moduleInfo.lpBaseOfDll, (DWORD64)moduleInfo.SizeOfImage, s);
	}

	template<typename ValueType, typename AddressType>
	static void putVP(AddressType address, ValueType value) {
		DWORD oldProtect;
		VirtualProtect((void*)address, sizeof(value), PAGE_EXECUTE_READWRITE, &oldProtect);

		memcpy((void*)address, &value, sizeof(value));

		VirtualProtect((void*)address, sizeof(value), oldProtect, &oldProtect);
	}

	template<typename AddressType>
	static void putVP(AddressType address, vector<DWORD> offsets) {
		for (int i = 0; i < offsets.size(); i++) {
			DWORD oldProtect;
			DWORD value = offsets[i];
			VirtualProtect((void*)(address + i), sizeof(value), PAGE_EXECUTE_READWRITE, &oldProtect);

			memcpy((void*)(address + i), &value, sizeof(value));

			VirtualProtect((void*)(address + i), sizeof(value), oldProtect, &oldProtect);
		}
	}

	template<typename ValueType, typename AddressType>
	static void put(AddressType address, ValueType value) {
		memcpy((void*)address, &value, sizeof(value));
	}

	template<typename AddressType>
	static void nop(AddressType address, size_t length) {
		memset((void*)address, 0x90, length);
	}

	template<typename ValueType, typename AddressType>
	static void WriteVirtualProtect(AddressType address, ValueType value, int size = -1) {
		SIZE_T thesize = 0;

		thesize = size == -1 ? sizeof(value) : size;

		DWORD oldProtect;
		VirtualProtect((void*)address, thesize, PAGE_EXECUTE_READWRITE, &oldProtect);

		memcpy((void*)address, &value, thesize);

		VirtualProtect((void*)address, thesize, oldProtect, &oldProtect);
	}

	template<typename AddressType>
	static void returnFunction(AddressType address, uint16_t stackSize = 0) {
		if (stackSize == 0) {
			put<uint8_t>(address, 0xC3);
		} else {
			put<uint8_t>(address, 0xC2);
			put<uint16_t>((uintptr_t)address + 1, stackSize);
		}
	}

	static uintptr_t getMultilayerPointer(uintptr_t base_address, vector<DWORD> offsets) {
		uintptr_t ptr = *(uintptr_t*)(base_address);
		if (!ptr) {
			return NULL;
		}
		auto level = offsets.size();

		for (auto i = 0; i < level; i++) {
			if (i == level - 1) {
				ptr += offsets[i];
				if (!ptr) return NULL;
				return ptr;
			} else {
				ptr = *(uint64_t*)(ptr + offsets[i]);
				if (!ptr) return NULL;
			}
		}
		return ptr;
	}

	static bool compare(const uint8_t* pData, const uint8_t* bMask, String sMask) {
		for (; *sMask; ++sMask, ++pData, ++bMask)
			if (*sMask == 'x' && *pData != *bMask)
				return false;
		return *sMask == NULL;
	}

	vector<DWORD64> getStringAddress(string str);
	static void* ReplaceInstructionAddress(void* wherePtr, void* toPtr, const int opSize = 3, const int opLength = 7) {
		const auto delta = static_cast<DWORD>(reinterpret_cast<DWORD64>(toPtr) - reinterpret_cast<DWORD64>(wherePtr) - opLength);
		const auto original = reinterpret_cast<void *>(reinterpret_cast<DWORD64>(wherePtr) + *reinterpret_cast<int *>(reinterpret_cast<DWORD64>(wherePtr) + opSize) + opLength);

		DWORD op;
		VirtualProtect(wherePtr, 7, PAGE_READWRITE, &op);
		*reinterpret_cast<DWORD *>(reinterpret_cast<DWORD64>(wherePtr) + opSize) = delta;
		VirtualProtect(wherePtr, 7, op, &op);

		return original;
	}
};