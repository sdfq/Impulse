#pragma once

//struct DownloadedPatterns {
//	string m_name;
//	bool m_important;
//	int m_offset;
//	string m_pattern;
//
//	static friend bool operator == (const DownloadedPatterns& left, string right) {
//		return !strcmp(left.m_name.c_str(), right.c_str());
//	}
//
//	DownloadedPatterns() : m_name(0), m_offset(0), m_important(false)
//	{}
//	
//	DownloadedPatterns(string name, bool important, int offset, string pattern) : m_name(name), m_important(important), m_offset(offset), m_pattern(pattern)
//	{}
//};

struct AuthResponse {
	string m_responseTime;
	string m_responseType;
	string m_response;

	void clear() {
		m_responseTime.clear();
		m_responseType.clear();
		m_response.clear();
	}
};

class Authorization {
private:
	int authProgress = 0;
	map<string, PStruct> g_downloadSignatures;
	char m_username[150];
	char m_password[150];
	bool m_authorized;
	string m_customAuthMessage;
	Role m_role;
	string m_hwid;
	bool m_rockstarIdSet = false;
	String m_currentVersion = "1.0.9";
	Network* m_network;

public:
	String GetCurrentMenuVersion() { return m_currentVersion; }
	bool CompareVersion(string version);
	void OnTick();
	void TagManager(string accessToken);
	float GetAuthProgress() { return Utils::Clamp(((float)authProgress / 30), 0.0f, 1.0f); }
	bool IsAuthorized() { return m_authorized; };
	void AuthInput(Status status, string username = "", string password = "");
	Status Authorize(String username, String password);
	void LogOut();
	string GetHWID();
	Role GetRole();
	PStruct* GetSignature(string name);
	string SRole() {
		if (IsStaff()) return "Staff";
		if (IsTester()) return "Tester";
		if (IsVIP()) return "VIP";
		else return "Standard";
	}
	inline bool IsDev() { return m_role == Dev; }
	inline bool IsStaff() { return m_role == Staff || IsDev(); }
	inline bool IsTester() { return m_role == Tester || IsStaff(); }
	inline bool IsVIP() { return m_role == Vip || IsTester() || IsStaff(); }
	String GetUsername() { return m_username; }
	String GetPassword() { return m_password; }

	~Authorization() { delete m_network; }
private:
	bool IsResponseGood(string resp);
	AuthResponse ParseResponse(string resp);
	void ParseSignatureResponse(string resp);
	Role ParseRole(string resp);
};

Authorization * GetAuth();