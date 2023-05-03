#include "stdafx.h"

namespace Pattern {
	map<string, uint64_t> m_storedAddresses;

	uint64_t StringToUint64(string str) {
		istringstream iss(str);
		uint64_t ret;
		if (iss >> hex >> ret) {
			return (uint64_t)ret;
		}
		return 0;
	}

	void Initialize() {
		ifstream i(GetConfig()->GetDataPath());
		if (!i.fail()) {
			try {
				string read((istreambuf_iterator<char>(i)), istreambuf_iterator<char>());
				if (read.empty()) { i.close(); return; };
				string dec = EncryptionHelper::ABitLessSimpleDecrypt(read);
				json jsonOb = json::parse(dec);
				for (auto& x : json::iterator_wrapper(jsonOb)) {
					m_storedAddresses.insert({ x.key().c_str(), (uint64_t)x.value() });
				}
			} catch (...) { LOG_DEBUG("[Service] Preloading data failed"); }
		}
		i.close();
	}

	std::string jsonto_string(const json &j) {
		if (j.type() == json::value_t::string) {
			return j.get<std::string>();
		}

		return j.dump();
	}

	void Finalize() {
		ofstream i(GetConfig()->GetDataPath());
		json jsonOb;

		for (auto& s : m_storedAddresses) {
			jsonOb[s.first] = s.second;
		}

		string str = jsonto_string(jsonOb);
		//string str = jsonOb.get<string>();
		string toWrite = EncryptionHelper::ABitLessSimpleEncrypt(str);

		i << toWrite;
		i.close();
	}

	vector<DWORD64> getStringAddress(string str) {
		string currentMask;
		String to_scan = str.c_str();
		for (uint8_t i = 0; i < strlen(to_scan); i++) currentMask += "x";
		const char *mask = currentMask.c_str();
		vector<DWORD64> foundAddrs;
		for (uint32_t i = 0; i < Backend::GetGameSize(); ++i) {
			auto address = Backend::GetGameBase() + i;
			if (compare((BYTE *)(address), (BYTE *)to_scan, mask)) {
				foundAddrs.push_back((address));
			}
		}
		return foundAddrs;
	}
}