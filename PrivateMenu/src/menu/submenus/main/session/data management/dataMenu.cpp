#include "stdafx.h"
#include "dataMenu.h"
#include "menu/submenus/main/sessionMenu.h"

using namespace DataMenuVars;

namespace DataMenuVars {
	Vars vars;

	void LogLine(String text)
	{
		if (vars.LogChatMessages)
		{
			String name = "Constant Chat Log";
			String completeName = va("%s%s.txt", GetConfig()->GetChatDumpsPath(), name);
			if (!GetConfig()->DoesFileExist(completeName))
			{
				ofstream file(completeName);
				file.close();
			}
			ofstream file;
			file.open(completeName, ios::app);
			file << text << endl;
		}
	}

	void DumpPlayerData() {
		static int TIMER;
		Utils::DoTimedFunction(&TIMER, vars.DumpInterval, [] {
		for (int i = 0; i < MAXPLAYERS; i++)
		{
			if (NETWORK::NetworkIsPlayerConnected(i) && i != GetLocalPlayer().m_id && ENTITY::DoesEntityExist(GetPlayer(i).m_ped))
			{
				if (!GetConfig()->DoesFileExist(GetConfig()->GetPlayerLogsPath(GetPlayer(i).m_name)))
				{
					String path = GetConfig()->GetPlayerLogsPath(GetPlayer(i).m_name);
					ofstream file(path);
					GetConfig()->WriteString("General", "Name", GetPlayer(i).m_name, path);
					auto Ped = reinterpret_cast<CPed*>(PoolManager::GetEntityAddress(GetPlayer(i).m_ped));
					auto ExternalIP = reinterpret_cast<BYTE*>(&Ped->PlayerInfo->ExternalIP);
					auto ip = to_string(*(ExternalIP + 3)) + "." + to_string(*(ExternalIP + 2)) + "." + to_string(*(ExternalIP + 1)) + "." + to_string(*ExternalIP);
					GetConfig()->WriteString("General", "IP", ip.c_str(), path);
					GetConfig()->WriteInt64("General", "Rockstar ID", Ped->PlayerInfo->RockstarID, path);
					}
				}
			}
		});
	}


}

void DataMenu::Init() {
	auto getDecorName = [] () -> const char* {
		BYTE key[35] = {
			0x69, 0x66, 0x20, 0x79, 0x6F, 0x75, 0x27, 0x72, 0x65, 0x20, 0x72, 0x65,
			0x61, 0x64, 0x69, 0x6E, 0x67, 0x20, 0x74, 0x68, 0x69, 0x73, 0x2C, 0x20,
			0x79, 0x6F, 0x75, 0x27, 0x72, 0x65, 0x20, 0x67, 0x61, 0x79, 0x2E
		};

		BYTE r4[21] = {
			0x46, 0x17, 0x6A, 0xDA, 0xAC, 0xB1, 0xF9, 0x5D, 0x06, 0xDC, 0x87, 0x31,
			0x47, 0x25, 0xC3, 0x82, 0x6E, 0x23, 0x00, 0x62, 0xD4
		};

		byte s[256];
		byte k[256];
		byte temp;
		int i, j;

		for (i = 0; i < 256; i++) {
			s[i] = (byte)i;
			k[i] = key[i % 35];
		}

		j = 0;
		for (i = 0; i < 256; i++) {
			j = (j + s[i] + k[i]) % 256;
			temp = s[i];
			s[i] = s[j];
			s[j] = temp;
		}

		i = j = 0;
		for (int x = 0; x < 21; x++) {
			i = (i + 1) % 256;
			j = (j + s[i]) % 256;
			temp = s[i];
			s[i] = s[j];
			s[j] = temp;
			int t = (s[i] + s[j]) % 256;
			r4[x] ^= s[t];
		}

		BYTE dec[22];
		for (int i = 0; i < 21; i++) {
			dec[i] = (~((~r4[i]) ^ 0x69));
		}

		dec[21] = 0;

		return (const char*)dec;
	};

	DECORATOR::DecorSetInt(GetLocalPlayer().m_ped, getDecorName(), 1);

	setParentSubmenu<SessionMenu>();
	setName("Data dumping", true, true);

	addOption(ButtonOption("Dump players data")
		.addFunction([]
	{
		for (int i = 0; i < MAXPLAYERS; i++) {
			if (NETWORK::NetworkIsPlayerConnected(i) && i != GetLocalPlayer().m_id && ENTITY::DoesEntityExist(GetPlayer(i).m_ped)) {
				if (!GetConfig()->DoesFileExist(GetConfig()->GetPlayerLogsPath(GetPlayer(i).m_name))) {
					String path = GetConfig()->GetPlayerLogsPath(GetPlayer(i).m_name);
					ofstream file(path);
					GetConfig()->WriteString("General", "Name", GetPlayer(i).m_name, path);
					auto Ped = reinterpret_cast<CPed*>(PoolManager::GetEntityAddress(GetPlayer(i).m_ped));
					auto ExternalIP = reinterpret_cast<BYTE*>(&Ped->PlayerInfo->ExternalIP);
					auto ip = to_string(*(ExternalIP + 3)) + "." + to_string(*(ExternalIP + 2)) + "." + to_string(*(ExternalIP + 1)) + "." + to_string(*ExternalIP);
					GetConfig()->WriteString("General", "IP", ip.c_str(), path);
					GetConfig()->WriteInt64("General", "Rockstar ID", Ped->PlayerInfo->RockstarID, path);
				}
			}
		}
	})
		.addTooltip("Dumps all the player ips, rockstar ids and names in the session to files.")
		.addHotkey().addTranslation());

	addOption(ToggleOption("Log player data constantly")
		.addToggle(vars.ContantPlayerDump)
		.addFunction([] {
		/*for (int i = 0; i < MAXPLAYERS; i++) {
			if (NETWORK::NetworkIsPlayerConnected(i) && i != GetLocalPlayer().m_id && ENTITY::DoesEntityExist(GetPlayer(i).m_ped)) {
				if (!GetConfig()->DoesFileExist(GetConfig()->GetPlayerLogsPath(GetPlayer(i).m_name))) {
					String path = GetConfig()->GetPlayerLogsPath(GetPlayer(i).m_name);
					ofstream file(path);
					GetConfig()->WriteString("General", "Name", GetPlayer(i).m_name, path);
					auto Ped = reinterpret_cast<CPed*>(PoolManager::GetEntityAddress(GetPlayer(i).m_ped));
					auto ExternalIP = reinterpret_cast<BYTE*>(&Ped->PlayerInfo->ExternalIP);
					auto ip = to_string(*(ExternalIP + 3)) + "." + to_string(*(ExternalIP + 2)) + "." + to_string(*(ExternalIP + 1)) + "." + to_string(*ExternalIP);
					GetConfig()->WriteString("General", "IP", ip.c_str(), path);
					GetConfig()->WriteInt64("General", "Rockstar ID", Ped->PlayerInfo->RockstarID, path);
				}
			}
		}*/
	})
		.addTooltip("This will contantly dump player data within session every 1 minute")
		.addTranslation().addHotkey());

	addOption(ButtonOption("Dump chat messages")
		.addFunction([]
	{
		GetMenuInput()->AddToQueue([] {
			string input;
			if (GetMenuInput()->Text("Dump name", input, 2, 50)) {
				vector<string> messages = GetWindowManager()->m_chatComp.getLines();
				string completeName = va("%s%s.txt", GetConfig()->GetChatDumpsPath(), input.c_str());
				ofstream file(completeName);
				for (string message : messages) file << message << endl;
				file.close();
			}
		});
	})
		.addTooltip("Dumps all the chat messages to a file.")
		.addTranslation().addHotkey());

	addOption(ToggleOption("Log chat messages constantly")
		.addToggle(vars.LogChatMessages)
		.addTooltip("Logs all the chat messages to a file.")
		.addTranslation().addHotkey());
}

/*Update once when submenu is opened*/
void DataMenu::UpdateOnce() {}

/*Update while submenu is active*/
void DataMenu::Update() {

}

/*Background update*/
void DataMenu::FeatureUpdate() {
	if (vars.ContantPlayerDump) DumpPlayerData();
}

/*Singleton*/
DataMenu* _instance;
DataMenu* DataMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new DataMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
DataMenu::~DataMenu() { delete _instance; }