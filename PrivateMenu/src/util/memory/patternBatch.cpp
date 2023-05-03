#include "stdafx.h"

void PatternBatch::Submit(PStruct pattern, bool(*callback)(DWORD64 address)) {
	vector<PatternByte> p;
	istringstream iss(pattern.m_pattern);
	string w;
	while (iss >> w) {
		if (w.data()[0] == '?') {
			p.push_back(PatternByte());
		} else if (w.length() == 2 && isxdigit(w.data()[0]) && isxdigit(w.data()[1])) { // Hex
			p.push_back(PatternByte(w));
		} else return;
	}
	m_buffer.push_back({ pattern, p, callback, false, 0x0 });
}

void PatternBatch::Submit(string serverPattern, bool(*callback)(DWORD64 address)) {
	PStruct* pStruct = GetAuth()->GetSignature(serverPattern);
	if (pStruct == nullptr) return;
	Submit(*pStruct, callback);
}


void PatternBatch::Flush() {
	MODULEINFO module = {};
	GetModuleInformation(GetCurrentProcess(), GetModuleHandle(nullptr), &module, sizeof(MODULEINFO));
	for (DWORD64 i = 0; i < (DWORD64)module.SizeOfImage; i++) {
		UINT8* lpCurrentByte = (UINT8*)((DWORD64)module.lpBaseOfDll + i);

		for (auto& bp : m_buffer) {
			if (bp.m_found) continue;
			bool found = true;
			for (size_t ps = 0; ps < bp.m_bytes.size(); ps++) {
				if (bp.m_bytes[ps].ignore == false && lpCurrentByte[ps] != bp.m_bytes[ps].data) {
					found = false;
					break;
				}
			}
			if (found) {
				bp.m_found = true;
				bp.m_addr = (DWORD64)lpCurrentByte;
			}
		}
	}
	for (auto& bp : m_buffer) {
		if (bp.m_found) {
			char* address = SetAddressTypeForUse<char>(bp.m_addr, bp.m_pattern.m_offset);
			switch (IsValidAddress<char>(address, bp.m_pattern.m_name, bp.m_pattern.m_important, bp.m_pattern.m_offset)) {
			case STATUS_SUCCESS: bp.m_callback((DWORD64)address);  break;
			case STATUS_WARNING: if (!bp.m_pattern.m_important) { break; }
			case STATUS_FATAL: LOG_ERROR("[Pattern] %s pattern callback failed", bp.m_pattern.m_name); Backend::Cleanup(); break;
			}
		}
	}
	LOG_DEBUG("[Pattern] %s batch flushed", GetName());
}
