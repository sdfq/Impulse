#pragma once
#include <shlobj.h>
#include <shlwapi.h>
#include <direct.h>

class Config {
private:
	static char m_appdata[260];
	static char m_documents[260];
	static char m_log[260];
	static char m_VFX[260];
	static char m_ytd[260];
	static char m_data[260];
	static char m_login[260];
	static char m_config[260];
	static char m_themes[260];
	static char m_plugins[260];
	static char m_ytdConfig[260];
	static char m_ytdHeader[260];
	static char m_outfits[260];
	static char m_handling[260];
	static char m_vehicles[260];
	static char m_languages[260];
	static char m_recoveries[260];
	static char m_teleports[260];
	static char m_blacklist[260];
	static char m_profiles[260];
	static char m_namesave[260];
	static char m_playerlogs[260];
	static char m_chatdumps[260];
	static char m_ridspoof[260];
	static char m_messaging[260];
	static char m_mapmods[260];

public:
	String GetPathAppdata() { return m_appdata; }
	String GetLogPath() { return m_log; }
	String GetVFXPath() { return m_VFX; }
	String GetYTDPath() { return m_ytd; }
	String GetDataPath() { return m_data; }
	String GetLoginPath() { return m_login; }
	String GetConfigPath() { return m_config; }
	String GetThemesPath() { return m_themes; }
	String GetPluginsPath() { return m_plugins; }
	String GetOutfitsPath() { return m_outfits; }
	String GetHandlingPath() { return m_handling; }
	String GetYTDConfigPath() { return m_ytdConfig; }
	String GetYTDHeaderPath() { return m_ytdHeader; }
	String GetVehiclesPath() { return m_vehicles; }
	String GetLanguagesPath() { return m_languages; }
	String GetPathMyDocuments() { return m_documents; }
	String GetRecoveriesPath() { return m_recoveries; }
	String GetTeleportsPath() { return m_teleports; }
	String GetBlacklistPath() { return m_blacklist; }
	String GetProfilesPath() { return m_profiles; }
	String GetNameSavePath() { return m_namesave;  }
	String GetChatDumpsPath() { return m_chatdumps;  }
	String GetRIDSpoofPath() { return m_ridspoof; }
	String GetMessagingPath() { return m_messaging; }
	String GetPlayerLogsPath(String name) { return va("%s\\%s.ini", m_playerlogs, name); }
	String GetMapModsPath() { return m_mapmods; }

	void Initialize() {
		SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, SHGFP_TYPE_CURRENT, m_appdata);
		SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, m_documents);

		vaBuff(m_config, 260, "%s\\Impulse\\Config.ini", m_documents);
		vaBuff(m_log, 260, "%s\\Impulse\\Impulse.log", m_documents);
		vaBuff(m_data, 260, "%s\\Impulse\\Data.dat", m_documents);
		vaBuff(m_ytd, 260, "%s\\Impulse\\YTD", m_documents);
		vaBuff(m_VFX, 260, "%s\\Impulse\\VFX", m_documents);
		vaBuff(m_ytdConfig, 260, "%s\\Impulse\\YTD\\config.json", m_documents);
		vaBuff(m_ytdHeader, 260, "%s\\Impulse\\YTD\\customheader.ytd", m_documents);
		vaBuff(m_login, 260, "%s\\Impulse\\Impulse.login", m_documents);
		vaBuff(m_themes, 260, "%s\\Impulse\\Themes", m_documents);
		vaBuff(m_outfits, 260, "%s\\Impulse\\Outfits", m_documents);
		vaBuff(m_vehicles, 260, "%s\\Impulse\\Vehicles", m_documents);
		vaBuff(m_handling, 260, "%s\\Impulse\\Handling", m_documents);
		vaBuff(m_languages, 260, "%s\\Impulse\\Languages", m_documents);
		vaBuff(m_plugins, 260, "%s\\Impulse\\Plugins", m_documents);
		vaBuff(m_recoveries, 260, "%s\\Impulse\\Recoveries", m_documents);
		vaBuff(m_teleports, 260, "%s\\Impulse\\Teleports", m_documents);
		vaBuff(m_blacklist, 260, "%s\\Impulse\\Overseer\\overseerconfig.json", m_documents);
		vaBuff(m_profiles, 260, "%s\\Impulse\\Profiles\\", m_documents);
		vaBuff(m_namesave, 260, "%s\\Impulse\\Name\\name loader.ini", m_documents);
		vaBuff(m_playerlogs, 260, "%s\\Impulse\\Player Logs", m_documents);
		vaBuff(m_chatdumps, 260, "%s\\Impulse\\Chat Dumps\\", m_documents);
		vaBuff(m_ridspoof, 260, "%s\\Impulse\\RID Spoof Profiles\\", m_documents);
		vaBuff(m_messaging, 260, "%s\\Impulse\\Messaging\\", m_documents);
		vaBuff(m_mapmods, 260, "%s\\Impulse\\Map mods\\", m_documents);

		CreateAppdataFolder("//Microsoft FxCop");

		CreateDocumentsFolder("//Impulse");
		CreateDocumentsFolder("//Impulse//YTD");
		CreateDocumentsFolder("//Impulse//VFX");
		CreateDocumentsFolder("//Impulse//Themes");
		CreateDocumentsFolder("//Impulse//Outfits");
		CreateDocumentsFolder("//Impulse//Vehicles");
		CreateDocumentsFolder("//Impulse//Handling");
		CreateDocumentsFolder("//Impulse//Languages");
		CreateDocumentsFolder("//Impulse//Plugins");
		CreateDocumentsFolder("//Impulse//Recoveries");
		CreateDocumentsFolder("//Impulse//Teleports");
		CreateDocumentsFolder("//Impulse//Overseer");
		CreateDocumentsFolder("//Impulse//Profiles");
		CreateDocumentsFolder("//Impulse//Name");
		CreateDocumentsFolder("//Impulse//Player Logs");
		CreateDocumentsFolder("//Impulse//Chat Dumps");
		CreateDocumentsFolder("//Impulse//RID Spoof Profiles");
		CreateDocumentsFolder("//Impulse//Messaging");
		CreateDocumentsFolder("//Impulse//Map mods");
	}

	void CreateAppdataFolder(String path) {
		_mkdir(va("%s%s", m_appdata, path));
	}

	void CreateDocumentsFolder(String path) {
		_mkdir(va("%s%s", m_documents, path));
	}

	void GetFilesFromDirectory(vector<string>& buffer, string folder, string extention) {
		buffer.clear();
		string loc = folder + "\\*" + extention;
		WIN32_FIND_DATAA fd;
		HANDLE hFind = ::FindFirstFileA(loc.c_str(), &fd);
		if (hFind != INVALID_HANDLE_VALUE) {
			do {
				if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
					string orig = fd.cFileName;
					string newstring = orig.substr(0, orig.size() - extention.size());
					buffer.push_back(newstring.c_str());
				}
			} while (::FindNextFileA(hFind, &fd));
			::FindClose(hFind);
		}
	}

	bool DoesFileExist(String file) {
		ifstream i(file);
		return i.good();
	}

	//.ini
	void RemoveString(String section, String key) {
		WritePrivateProfileStringA(section, key, nullptr, GetConfigPath());
	}

	String ReadString(String section, String key, String defaultReturn, String path = m_config) {
		static char currentOptionBuffer[255];
		GetPrivateProfileStringA(section, key, defaultReturn, currentOptionBuffer, 255, path);
		return currentOptionBuffer;
	}

	String ReadStringCustomDefault(String section, String key, String defaultReturn, String path = m_config) {
		char currentOptionBuffer[255];
		GetPrivateProfileStringA(section, key, defaultReturn, currentOptionBuffer, 255, path);
		return currentOptionBuffer;
	}

	void WriteString(String section, String key, String value, String path = m_config) {
		WritePrivateProfileStringA(section, key, value, path);
	}

	template<typename Type>
	Type ReadNumber(String section, String key, String format, Type defaultVal, Type(*func)(String text), String path = m_config) {
		char resultBuffer[255];
		char defaultBuffer[255];
		sprintf_s(defaultBuffer, format, defaultVal);
		GetPrivateProfileStringA(section, key, defaultBuffer, resultBuffer, 255, path);
		return func(resultBuffer);
	}

	int ReadInt(String section, String key, int defaultReturn, String path = m_config) {
		return ReadNumber<int>(section, key, "%d", defaultReturn, [](String text) {return atoi(text); }, path);
	}

	float ReadFloat(String section, String key, float defaultReturn, String path = m_config) {
		return ReadNumber<float>(section, key, "%f", defaultReturn, [](String text) {return (float)atof(text); }, path);
	}

	int64_t ReadInt64(String section, String key, int64_t defaultReturn, String path = m_config) {
		return ReadNumber<int64_t>(section, key, "%lld", defaultReturn, [](String text) {return _atoi64(text); }, path);
	}

	template<typename Type>
	void WriteNumber(String section, String key, String format, Type value, String path = m_config) {
		char buffer[255];
		sprintf_s(buffer, format, value);
		WritePrivateProfileStringA(section, key, buffer, path);
	}

	void WriteInt(String section, String key, int value) {
		WriteNumber<int>(section, key, "%d", value);
	}

	void WriteFloat(String section, String key, float value) {
		WriteNumber<float>(section, key, "%f", value);
	}

	void WriteInt64(String section, String key, int64_t value, String path = m_config) {
		WriteNumber<int64_t>(section, key, "%lld", value, path);
	}

	void WriteBool(String section, String key, bool value) {
		WritePrivateProfileStringA(section, key, value ? "true" : "false", GetConfigPath());
	}

	void WriteBool(String section, String key, bool value, String path) {
		WritePrivateProfileStringA(section, key, value ? "true" : "false", path);
	}

	bool ReadBool(String section, String key, bool defaultReturn, String path = m_config) {
		char currentOptionBuffer[255];
		GetPrivateProfileStringA(section, key, defaultReturn ? "true" : "false", currentOptionBuffer, 255, path);
		return strcmp(currentOptionBuffer, "true") == 0;
	}

	void WriteColor(String section, String key, Color color) {
		WritePrivateProfileStringA(section, key, va("%d;%d;%d;%d;", color.m_r, color.m_g, color.m_b, color.m_a), GetConfigPath());
	}

	void ReadColor(String section, String key, Color* color) {
		string temp = ReadString(section, key, "null");
		if (temp != "null") {
			vector<string> SC = split(temp, ";");
			if (SC.size() == 4) *color = { stoi(SC.at(0)), stoi(SC.at(1)), stoi(SC.at(2)), stoi(SC.at(3)) };
		}
	}
};

Config* GetConfig();