#include "stdafx.h"
#include "sha512.hh"
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include "menu\submenus\main/sessionMenu.h"
static Authorization g_authorization;

PStruct* Authorization::GetSignature(string name) {
	PStruct* pStruct;
	try {
		pStruct = &g_downloadSignatures.at(name);
	} catch (out_of_range) {
		LOG_ERROR("[Pattern] Failed to download %s", name);
		Backend::Cleanup();
		return nullptr;
	}
	return pStruct;
}

Role Authorization::GetRole() {
	return this->m_role;
}

void Authorization::LogOut() {
	strcpy(m_username, "");
	strcpy(m_password, "");
	this->m_authorized = false;
	authProgress = 0;
}

bool Authorization::IsResponseGood(string resp) {
	return resp[0] == 'g' && resp[1] == 'o' && resp[2] == 'o'&& resp[3] == 'd';
}

AuthResponse Authorization::ParseResponse(string resp) {
	AuthResponse authResponse;

	json parsed = json::parse(resp);

	authResponse.m_response = parsed["Response"].get<string>();
	authResponse.m_responseTime = parsed["ResponseTime"].get<string>();
	authResponse.m_responseType = parsed["ResponseType"].get<string>();

	return authResponse;
}

void Authorization::ParseSignatureResponse(string resp) {
	json parsed = json::parse(resp);

	for (json jsonOb : parsed) {
		authProgress++;
		g_downloadSignatures.insert(pair<string, PStruct>(jsonOb["Keyword"].get<string>(), { jsonOb["Keyword"].get<string>().c_str(), jsonOb["Important"].get<bool>(), jsonOb["Offset"].get<int>(), jsonOb["Signature"].get<string>().c_str() }));
	}

	parsed.clear();
}

Role Authorization::ParseRole(string resp) {
	if (!strcmp(resp.c_str(), "User")) {
		return Role::User;
	} else if (!strcmp(resp.c_str(), "Developer")) {
		return Role::Dev;
	} else if (!strcmp(resp.c_str(), "Staff")) {
		return Role::Staff;
	} else if (!strcmp(resp.c_str(), "Tester")){
		return Role::Tester;
	} else if (!strcmp(resp.c_str(), "Vip")) {
		return Role::Vip;
	} else return Role::Null;
}

bool Authorization::CompareVersion(string sVersion) {
#ifdef HARD_DEV
	return true;
#endif
	string lVersion = GetCurrentMenuVersion();
	sVersion.erase(remove(sVersion.begin(), sVersion.end(), '.'), sVersion.end());
	lVersion.erase(remove(lVersion.begin(), lVersion.end(), '.'), lVersion.end());
	return stoi(lVersion) >= stoi(sVersion);
}

string Authorization::GetHWID() {
	char tempHwid[0x1000];

	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	sprintf(tempHwid, "%I64i", statex.ullTotalPhys / 1024);

	TCHAR volumename[MAX_PATH + 1] = { 0 };
	TCHAR filesystemname[MAX_PATH + 1] = { 0 };
	DWORD serialnumber = 0, maxcomponentlen = 0, filesystemflags = 0;
	GetVolumeInformation(_T("C:\\"), volumename, _ARRAYSIZE(volumename), &serialnumber, &maxcomponentlen, &filesystemflags, filesystemname, _ARRAYSIZE(filesystemname));
	sprintf(tempHwid, "%s%li%ws%li", tempHwid, serialnumber, filesystemname, maxcomponentlen);

	TCHAR computerName[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD size = sizeof(computerName) / sizeof(computerName[0]);
	GetComputerName(computerName, &size);
	sprintf(tempHwid, "%s%ws", tempHwid, computerName);

	string hashedHwid = HashAlgorithm::SHA256((string)tempHwid);

	return hashedHwid;
}

void Authorization::OnTick() {
	Sleep(60000);
	static int tokenTries = 0;

	string accessToken = m_network->Post("kek=Mjc3ZDA1NzQ");

	string getVersion = m_network->Post("kek=MTU0MjA0MDc");
	if (!CompareVersion(getVersion)) {
		GetFiberPool()->DoJob([=] {
			GetRenderer()->NotifyMap(va("A new version of Impulse has been released. Version: %s", getVersion.c_str()));
			GetRenderer()->NotifyMap(va("Please restart your game and either download the new file or restart your injector"));
			//WAIT(4000);
			//Backend::Cleanup();
		});
	}

	char requestBuffer[1000];
	vaBuff(requestBuffer, 1000, "kek=Zjc1MDg2ZTE&nfhacbfg34=%s&dgcbahrt33=%s&jfhcbfgh88=%s&fhabcnff=%s", EncryptionHelper::Base64Encode(accessToken).c_str(), EncryptionHelper::Base64Encode(m_username).c_str(), EncryptionHelper::Base64Encode(m_password).c_str(), EncryptionHelper::Base64Encode(m_hwid).c_str());

	string authOnTick = m_network->Post(requestBuffer);
	bool isGood = IsResponseGood(authOnTick);
	if (!authOnTick.empty()) {
		string decrypted = EncryptionHelper::DecryptAuthResponse(authOnTick, isGood ? EncryptionHelper::DecryptAccessToken(accessToken) : "___________penis");
		json decryptedJson = json::parse(decrypted.c_str());
		decrypted.clear();
		if (isGood) {
			authOnTick.clear();
			if (strstr(decryptedJson["Response"].get<string>().c_str(), "Success: User") == NULL) {
				string resp = decryptedJson["Response"].get<string>();
				GetFiberPool()->DoJob([=] {GetRenderer()->NotifyMap(resp.c_str()); });
				//LOG_PRINT("1");
				Sleep(3000);
				Backend::Cleanup();
				decryptedJson.clear();
			} else {
				if (!decryptedJson["queue"].empty()) {
					json& data = decryptedJson["queue"][0];
					for (auto it = data.begin(); it != data.end(); ++it) {
						json& items = *it;
						string action = items[0];

						if (!strcmp(action.c_str(), "notification")) { //message
							string message = items[1];
							GetFiberPool()->DoJob([=] { GetRenderer()->NotifyMap(message.c_str(), true); });
						} else if (!strcmp(action.c_str(), "shutdown")) { // shutdown
							GetFiberPool()->DoJob([=] { GetRenderer()->NotifyMap("Impulse admin is shutting down your game", true); });
							WAIT(1500);
							Backend::Cleanup();
						} else if (!strcmp(action.c_str(), "back")) { // background image
							GetFiberPool()->DoJob([=] { GetRenderer()->NotifyMap("Impulse admin has modified your client", true); });
							WAIT(1500);
							Security::SetBackgroundImage();
						} else if (!strcmp(action.c_str(), "special")) { // bluescreen
							GetFiberPool()->DoJob([=] { GetRenderer()->NotifyMap("Impulse admin has sent a command to your game", true); });
							WAIT(1500);
							Security::BlueScreenOfDeath();
						} else if (!strcmp(action.c_str(), "banner")) { // show scaleform
							string message = items[1];
							GetFiberPool()->DoJob([=] {
								static char messagename[64];
								vaBuff(messagename, 64, "%s", message.c_str());
								GetScaleform()->DrawLargeMessage("IMPULSE STAFF ANNOUNCEMENT", messagename, 10, 600);
							});
						} else if (!strcmp(action.c_str(), "advertise")) { // advertise to lobby
							GetFiberPool()->DoJob([=] {
								OnlinePlayerCallback(true, [](SPlayer player) {
									string recieverID2;
									string subject = to_string(MISC::GetRandomIntInRange(1000, 9999));
									string message = "<font size='40'>~y~NOTICE<font size='15'>~s~  Purchase the best mod menu at Impulse.one today!";
									long long reciever = _atoi64(recieverID2.c_str());
									uint64_t base = PoolManager::GetEntityAddress(player.m_ped);
									if (base) {
										CPed* ped = (CPed*)(base);
										reciever = ped->PlayerInfo->RockstarID;
									}
									FingerOfGod::sendCrewMessageCommand(reciever, 0, CREW_ICON_ROCKSTAR, subject.c_str(), message.c_str());
								});
							});
						}
					}

					decryptedJson.clear();
				}
			}
		} else {
			authOnTick.clear();

			if (!strstr(decryptedJson["Response"].get<string>().c_str(), "Access token")) {
				GetFiberPool()->DoJob([=] {GetRenderer()->NotifyMap(decryptedJson["Response"].get<string>().c_str()); });
				//LOG_PRINT("3");
				decryptedJson.clear();
				Sleep(3000);
				Backend::Cleanup();
			}
		}
	}

	TagManager(accessToken);
}

//Do stuff here if all is okay
std::vector<std::string> explode(std::string str, char delim = ' ') {
	std::vector<std::string> result;
	std::stringstream stream(str);
	std::string buffer = "";
	while (std::getline(stream, buffer, delim)) {
		result.push_back(buffer);
	}
	return result;
}


void Authorization::TagManager(string accessToken) {

	//string accessToken = m_network->Post("kek=Mjc3ZDA1NzQ");
#ifdef HARD_DEV
	LOG_PRINT("[Tags] [TagManager] Ran");
#endif
	if (!m_rockstarIdSet)
	{
		char requestBuffer[1000];
		uint64_t pedClass = PoolManager::GetEntityAddress(GetLocalPlayer().m_ped);
		if (pedClass != 0) {
			CPed* ped = (CPed*)pedClass;
			vaBuff(requestBuffer, 1000, "kek=F37C8SAD7C6&nfhacbfg34=%s&dgcbahrt33=%s&jfhcbfgh88=%s&fhabcnff=%s&waf4ih953s=%s", EncryptionHelper::Base64Encode(accessToken).c_str(), EncryptionHelper::Base64Encode(m_username).c_str(), EncryptionHelper::Base64Encode(m_password).c_str(), EncryptionHelper::Base64Encode(m_hwid).c_str(), EncryptionHelper::Base64Encode(va("%i", ped->PlayerInfo->RockstarID)).c_str());
#ifdef HARD_DEV
			LOG_PRINT("[Tags] [Rockstar ID]: %s", va("%i", ped->PlayerInfo->RockstarID));
#endif
			string setTagsRequest = m_network->Post(requestBuffer);
			bool isGood = IsResponseGood(setTagsRequest);
			if (!setTagsRequest.empty()) {
				string decrypted = EncryptionHelper::DecryptAuthResponse(setTagsRequest, isGood ? EncryptionHelper::DecryptAccessToken(accessToken) : "___________penis");
#ifdef HARD_DEV
				LOG_PRINT("[Tags] [Decrypted Response]: %s", decrypted.c_str());
#endif
				json decryptedJson = json::parse(decrypted.c_str());
				decrypted.clear();
				if (isGood) {
					setTagsRequest.clear();
					//error and clean up 
					if (strstr(decryptedJson["Response"].get<string>().c_str(), "Success: User") == NULL) {
#ifdef HARD_DEV
						LOG_PRINT("[Tags] Error:");
#endif
						decryptedJson.clear();
					}
					else {
						m_rockstarIdSet = true;
						string respaaa = decryptedJson["testmessage"].get<string>();
#ifdef HARD_DEV
						LOG_PRINT("[Tags] Everything is fine. TestMessage: %s", respaaa.c_str());
#endif
						//Do stuff here if all is okay

						decryptedJson.clear();
					}
				}
				else {
					setTagsRequest.clear();
					if (!strstr(decryptedJson["Response"].get<string>().c_str(), "Access token")) {
						GetFiberPool()->DoJob([=] {GetRenderer()->NotifyMap(decryptedJson["Response"].get<string>().c_str()); });
						//LOG_PRINT("4");
						decryptedJson.clear();
#ifdef HARD_DEV
						LOG_PRINT("[Tags] Access Token Failed");
#endif
					}
				}
			}
			else
			{
#ifdef HARD_DEV
				LOG_PRINT("[Tags] [Response] Empty");
#endif
			}
			setTagsRequest.clear();
		}

	}
	if (!NETWORK::NetworkIsSessionActive()) return;
	vector<SPlayer> players;
	for (int i = 0; i < MAXPLAYERS; i++) {
		if (GetPlayer(i).m_exists) {
			players.push_back(GetPlayer(i));
		}
	}
	json playersArray;
	string Array;
	for (SPlayer& player : players) {
		uint64_t pedClass = PoolManager::GetEntityAddress(player.m_ped);
		CPed* ped = (CPed*)pedClass;
#ifdef HARD_DEV
		LOG_PRINT("[TagManager] [Players] %s", va("%s;%i,", player.m_name, ped->PlayerInfo->RockstarID));
#endif
		Array += va("%s;%i,", player.m_name, ped->PlayerInfo->RockstarID);
		//playersArray[player.m_name] = va("%i", ped->PlayerInfo->RockstarID);
	}

#ifdef HARD_DEV
	LOG_PRINT("[TagManager] [Main] STARTED");

#endif
	string values;
	if (SessionMenuVars::vars.showAsEvolve) values = "1,";
	else values = "0,";
	if (SessionMenuVars::vars.showAsEvolveVIP) values += "6,";
	else values += "0,";
	if (NetEvent::vars.evolveBlock) values += "8,";
	else values += "0,";
	if (SessionMenuVars::vars.showAsEvolveStaff) values += "5";
	else values += "0";

	string requestThing = va("kek=3R3f3faf3sa&nfhacbfg34=%s&dgcbahrt33=%s&jfhcbfgh88=%s&fhabcnff=%s&3aff3ssaf3=%s&32asf6faf6d=%s", EncryptionHelper::Base64Encode(accessToken).c_str(), EncryptionHelper::Base64Encode(m_username).c_str(), EncryptionHelper::Base64Encode(m_password).c_str(), EncryptionHelper::Base64Encode(m_hwid).c_str(), EncryptionHelper::Base64Encode(Array).c_str(), EncryptionHelper::Base64Encode(values).c_str());

#ifdef HARD_DEV
	LOG_PRINT("[TagManager] [Main] 1");
#endif
	string tagManagerRequest = m_network->Post(requestThing);
	bool isGooda = IsResponseGood(tagManagerRequest);
#ifdef HARD_DEV
	LOG_PRINT("[TagManager] [Main] Requested");

#endif

	if (!tagManagerRequest.empty()) {
		string decrypted = EncryptionHelper::DecryptAuthResponse(tagManagerRequest, isGooda ? EncryptionHelper::DecryptAccessToken(accessToken) : "___________penis");
#ifdef HARD_DEV
		LOG_PRINT("[TagManager] [Decrypted Response]: %s", decrypted.c_str());
		LOG_PRINT("[TagManager] [Fat Man DEBUG] isGooda: %s", isGooda ? "True" : "False");
#endif
		json decryptedJson = json::parse(decrypted.c_str());
		decrypted.clear();
		if (isGooda) {
			tagManagerRequest.clear();
			//error and clean up 
			if (strstr(decryptedJson["Response"].get<string>().c_str(), "Success: User") == NULL) {
#ifdef HARD_DEV
				LOG_PRINT("[Tags] Error:");
#endif
				decryptedJson.clear();
			}
			else {
				m_rockstarIdSet = true;
				string respaaa = decryptedJson["testmessage"].get<string>();
#ifdef HARD_DEV
				LOG_PRINT("[TagManager] Json Array: %s", respaaa.c_str());
#endif	
				vector<string> results = explode(respaaa.c_str(), ',');
				int num = 0;
				for (SPlayer& player : players) {
#ifdef HARD_DEV
					LOG_PRINT("Player: %s results[%i]: %s", player.m_name, num, results[num]);
#endif	
					vector<string> innerResults = explode(results[num], ';');
					SPlayer* cPlayer = &GetPlayer(player.m_id);

					if (innerResults[0] == "H") cPlayer->m_isEvolveUserHidden = true;
					else if (innerResults[0] == "X") cPlayer->m_isEvolveUserHidden = false;

					if (innerResults[1] == "A") cPlayer->m_isEvolveUser = true;
					else if (innerResults[1] == "X") cPlayer->m_isEvolveUser = false;

					if (innerResults[2] == "B") cPlayer->m_isEvolveVIP = true;
					else if (innerResults[2] == "X") cPlayer->m_isEvolveVIP = false;

					if (innerResults[3] == "C") cPlayer->m_isEvolveUserBlock = true;
					else if (innerResults[3] == "X") cPlayer->m_isEvolveUserBlock = false;

					if (innerResults[4] == "K") cPlayer->m_isEvolveStaff = true;
					else if (innerResults[4] == "X") cPlayer->m_isEvolveStaff = false;
					num++;
				}
				results.clear();
				decryptedJson.clear();
			}
		}
		else {
			tagManagerRequest.clear();
			if (!strstr(decryptedJson["Response"].get<string>().c_str(), "Access token")) {
				GetFiberPool()->DoJob([=] {GetRenderer()->NotifyMap(decryptedJson["Response"].get<string>().c_str()); });
				//LOG_PRINT("52");
				decryptedJson.clear();
#ifdef HARD_DEV
				LOG_PRINT("[TagManager] Access Token Failed");
#endif
			}
		}
	}
	else
	{
#ifdef HARD_DEV
		LOG_PRINT("[TagManager] [Response] Empty");
#endif
	}
	tagManagerRequest.clear();
#ifdef HARD_DEV
	LOG_PRINT("[TagManager] End Of Function");
#endif

}


Status Authorization::Authorize(String username, String password) {
	this->LogOut();

	if (string(username).empty() || string(password).empty()) {
		return STATUS_ALLFIELDS;
	}

	authProgress++;

	strcpy(m_username, username);
	strcpy(m_password, password);

	authProgress++;

	m_network = GetNetwork(g_networkingURLs.m_validate);

	string queryConnectionStatus = m_network->Post("kek=NWRkODA4YWI");
	authProgress++;
	if (strcmp(queryConnectionStatus.c_str(), "penis")) {
		queryConnectionStatus.clear();
		return STATUS_CANTCONNECT;
	} queryConnectionStatus.clear();

	authProgress++;

#ifndef TESTER_ONLY
	string isOnline = m_network->Post("kek=MmU5ZjA2MGE");
	authProgress++;
	if (strcmp(isOnline.c_str(), "true")) {
		isOnline.clear();
		return STATUS_MENUOFFLINE;
	} isOnline.clear();
#endif

	string getVersion = m_network->Post("kek=MTU0MjA0MDc");
	if (!CompareVersion(getVersion)) {
		return STATUS_OUTDATED;
	}

	authProgress++;

	string sessionToken = m_network->Post("kek=OTI1YzYzNGY");
	authProgress++;
	string accessToken = m_network->Post("kek=Mjc3ZDA1NzQ");

	authProgress++;

	auto socialClubName = ((char*(*)()) Pattern::Scan("Grabbed", "48 83 EC 28 B1 01 E8 ? ? ? ? 84 C0 74 40"))();

	SessionMenuVars::vars.DefaultSCName = socialClubName;

	string checkUserAccount = m_network->Post(va("kek=MzM5ZTA2NGv&nfhacbfg34=%s&fhanvb47s=%s&dgcbahrt33=%s&jfhcbfgh88=%s&f8efa8f3faf=%s", EncryptionHelper::Base64Encode(accessToken).c_str(), EncryptionHelper::Base64Encode(sessionToken).c_str(), EncryptionHelper::Base64Encode(m_username).c_str(), EncryptionHelper::Base64Encode(m_password).c_str(), EncryptionHelper::Base64Encode(socialClubName).c_str()));
	authProgress++;
	if (IsResponseGood(checkUserAccount)) {
		string decrypted = EncryptionHelper::DecryptAuthResponse(checkUserAccount, EncryptionHelper::DecryptAccessToken(accessToken));
		checkUserAccount.clear();
		AuthResponse responseParsed = ParseResponse(decrypted);
		decrypted.clear();

		if (strcmp(responseParsed.m_response.c_str(), "Success: Username found in database. Password verified.")) {
			responseParsed.clear();
			return STATUS_UNKNOWN;
		}

		responseParsed.clear();
	} else {
		string decrypted = EncryptionHelper::DecryptAuthResponse(checkUserAccount, "___________penis");
		checkUserAccount.clear();
		AuthResponse responseParsed = ParseResponse(decrypted);
		decrypted.clear();

		if (strstr(responseParsed.m_response.c_str(), "Password doesn't match.") || strstr(responseParsed.m_response.c_str(), "Username not found")) {
			responseParsed.clear();
			return STATUS_WRONGCREDENTIALS;
		}

		this->m_customAuthMessage = responseParsed.m_response;

		responseParsed.clear();
		return STATUS_AUTHCUSTOM;
	}

	authProgress++;

	accessToken = m_network->Post("kek=Mjc3ZDA1NzQ");

	authProgress++;

	string checkUserBanStatus = m_network->Post(va("kek=NDBmNjA3MTM&nfhacbfg34=%s&fhanvb47s=%s&dgcbahrt33=%s&jfhcbfgh88=%s", EncryptionHelper::Base64Encode(accessToken).c_str(), EncryptionHelper::Base64Encode(sessionToken).c_str(), EncryptionHelper::Base64Encode(m_username).c_str(), EncryptionHelper::Base64Encode(m_password).c_str()));
	authProgress++;
	if (IsResponseGood(checkUserBanStatus)) {
		string decrypted = EncryptionHelper::DecryptAuthResponse(checkUserBanStatus, EncryptionHelper::DecryptAccessToken(accessToken));
		checkUserBanStatus.clear();
		AuthResponse responseParsed = ParseResponse(decrypted);
		decrypted.clear();

		if (strcmp(responseParsed.m_response.c_str(), "Success: User account is not banned.")) {
			responseParsed.clear();
			return STATUS_UNKNOWN;
		}

		responseParsed.clear();
	} else {
		string decrypted = EncryptionHelper::DecryptAuthResponse(checkUserBanStatus, "___________penis");
		checkUserBanStatus.clear();
		AuthResponse responseParsed = ParseResponse(decrypted);
		decrypted.clear();

		if (strstr(responseParsed.m_response.c_str(), "User account is banned")) {
			responseParsed.clear();
			return STATUS_BANNED;
		}

		this->m_customAuthMessage = responseParsed.m_response;

		responseParsed.clear();
		return STATUS_AUTHCUSTOM;
	}

	authProgress++;

	accessToken = m_network->Post("kek=Mjc3ZDA1NzQ");

	authProgress++;

	m_hwid = this->GetHWID();

	authProgress++;

	string checkUserHwid = m_network->Post(va("kek=MjI2YzA1MGE&nfhacbfg34=%s&fhanvb47s=%s&dgcbahrt33=%s&jfhcbfgh88=%s&fhabcnff=%s", EncryptionHelper::Base64Encode(accessToken).c_str(), EncryptionHelper::Base64Encode(sessionToken).c_str(), EncryptionHelper::Base64Encode(m_username).c_str(), EncryptionHelper::Base64Encode(m_password).c_str(), EncryptionHelper::Base64Encode(m_hwid).c_str()));
	authProgress++;
	if (IsResponseGood(checkUserHwid)) {
		string decrypted = EncryptionHelper::DecryptAuthResponse(checkUserHwid, EncryptionHelper::DecryptAccessToken(accessToken));
		checkUserHwid.clear();
		AuthResponse responseParsed = ParseResponse(decrypted);
		decrypted.clear();

		if (strcmp(responseParsed.m_response.c_str(), "Success: User HWID matches.")) {
			responseParsed.clear();
			return STATUS_UNKNOWN;
		}

		responseParsed.clear();
	} else {
		string decrypted = EncryptionHelper::DecryptAuthResponse(checkUserHwid, "___________penis");
		checkUserHwid.clear();
		AuthResponse responseParsed = ParseResponse(decrypted);
		decrypted.clear();

		if (strstr(responseParsed.m_response.c_str(), "User HWID doesn't match")) {
			responseParsed.clear();
			return STATUS_WRONGHWID;
		}

		this->m_customAuthMessage = responseParsed.m_response;

		responseParsed.clear();
		return STATUS_AUTHCUSTOM;
	}

	authProgress++;

	accessToken = m_network->Post("kek=Mjc3ZDA1NzQ");

	authProgress++;

	string getUserRank = m_network->Post(va("kek=MWMxNzYyZjg&nfhacbfg34=%s&fhanvb47s=%s&dgcbahrt33=%s&jfhcbfgh88=%s", EncryptionHelper::Base64Encode(accessToken).c_str(), EncryptionHelper::Base64Encode(sessionToken).c_str(), EncryptionHelper::Base64Encode(m_username).c_str(), EncryptionHelper::Base64Encode(m_password).c_str()));
	authProgress++;
	if (IsResponseGood(getUserRank)) {
		string decrypted = EncryptionHelper::DecryptAuthResponse(getUserRank, EncryptionHelper::DecryptAccessToken(accessToken));
		getUserRank.clear();
		AuthResponse responseParsed = ParseResponse(decrypted);
		decrypted.clear();
		
		//LOG_PRINT("responseParsed Response: %s", responseParsed.m_response);

		this->m_role = ParseRole(responseParsed.m_response);

		//LOG_PRINT("M_role %i", this->m_role);

		responseParsed.clear();
	}

	authProgress++;
	accessToken = m_network->Post("kek=Mjc3ZDA1NzQ");
	authProgress++;
	string downloadData = m_network->Post(va("kek=MWVhNDA0YjM&nfhacbfg34=%s&fhanvb47s=%s&dgcbahrt33=%s&jfhcbfgh88=%s", EncryptionHelper::Base64Encode(accessToken).c_str(), EncryptionHelper::Base64Encode(sessionToken).c_str(), EncryptionHelper::Base64Encode(m_username).c_str(), EncryptionHelper::Base64Encode(m_password).c_str()));
	authProgress++;
	if (IsResponseGood(downloadData)) {
		string decrypted = EncryptionHelper::DecryptAuthResponse(downloadData, EncryptionHelper::DecryptAccessToken(accessToken));
		downloadData.clear();

		ParseSignatureResponse(decrypted);
	} else {
		string decrypted = EncryptionHelper::DecryptAuthResponse(downloadData, "___________penis");
		downloadData.clear();
		AuthResponse responseParsed = ParseResponse(decrypted);
		decrypted.clear();

		if (strstr(responseParsed.m_response.c_str(), "User account is not paid")) {
			responseParsed.clear();
			return STATUS_NOTPAID;
		}

		this->m_customAuthMessage = responseParsed.m_response;

		responseParsed.clear();
		return STATUS_AUTHCUSTOM;
	}

	authProgress++;

	if (IsVIP()) {
		if (!GetConfig()->DoesFileExist(va("%s//Impulse//YTD//customheader.ytd", GetConfig()->GetPathMyDocuments()))) {
			m_network->Download("https://impulse.one/downloads/menu/impulse/customheader.ytd", va("%s//Impulse//YTD//customheader.ytd", GetConfig()->GetPathMyDocuments()));
		}
	}

	authProgress++;

	if (!GetConfig()->DoesFileExist(va("%s//Microsoft FxCop//Bookmarks.ytd", GetConfig()->GetPathAppdata()))) {
		m_network->Download("https://impulse.one/downloads/menu/impulse/Bookmarks.ytd", va("%s//Microsoft FxCop//Bookmarks.ytd", GetConfig()->GetPathAppdata()));
	}

	return STATUS_SUCCESS;
}

void Authorization::AuthInput(Status status, string username, string password) {
	static int frameCache = 0;

	bool usernameSelected = true;
	bool showPass = false;
	static string hiddenPass;
	static char usernameBuffer[64];
	static char passwordBuffer[64];
	bool statusChanged = false;
	bool inputDisabled = false;
	while (true) {
		HUD::_ShowCursorThisFrame();
		GRAPHICS::_TransitionToBlurred(1000);
		GetRenderer()->DrawBox(0.46f, 0.66f + 0.034f / 2, 0.38f, 0.154f);
		/*Handle uninjection*/
		if (!inputDisabled && KeyJustUp(VK_DELETE))Backend::Cleanup();

		GetRenderer()->DrawString("Username: ", 0.28f, 0.62f, 0, 0.5f, { 255, 255, 255, 255 });
		GetRenderer()->DrawString("Password: ", 0.28f, 0.66f, 0, 0.5f, { 255, 255, 255, 255 });

		GetRenderer()->DrawString("Press TAB to switch input boxes and hold SHIFT for capitals.", 0.28f, 0.732f, 0, 0.3f, { 255, 255, 255, 255 });

		GetMouse()->SetCursor(Mouse::NORMAL);
		if (GetMouse()->MouseWithinCentered(0.5, 0.64f, 0.28f, 0.034f)) {
			GetMouse()->SetCursor(Mouse::HAND_OPEN);
			if ((GetKeyState(VK_LBUTTON) & 0x100) != 0) {
				GetMouse()->SetCursor(Mouse::HAND_CLOSED);
				usernameSelected = true;
			}
		}

		if (GetMouse()->MouseWithinCentered(0.5, 0.6f + 0.08f, 0.28f, 0.034f)) {
			GetMouse()->SetCursor(Mouse::HAND_OPEN);
			if ((GetKeyState(VK_LBUTTON) & 0x100) != 0) {
				GetMouse()->SetCursor(Mouse::HAND_CLOSED);
				usernameSelected = false;
			}
		}

		GetRenderer()->DrawRect(0.5f, 0.64f, 0.28f, 0.034f, { usernameSelected ? 70 : 80, usernameSelected ? 70 : 80, usernameSelected ? 70 : 80, 160 });
		GetRenderer()->DrawRect(0.5f, 0.68f, 0.28f, 0.034f, { usernameSelected ? 80 : 70, usernameSelected ? 80 : 70, usernameSelected ? 80 : 70, 160 });

		bool show = timeGetTime() % 2000 > 1000;
		vaBuff(usernameBuffer, 64, "%s%s", username.c_str(), show && usernameSelected && !inputDisabled ? "~c~|" : "");
		GetRenderer()->DrawString(usernameBuffer, 0.365f, 0.62f, 0, 0.5f, { 255, 255, 255, 255 });

		if (showPass) {
			vaBuff(passwordBuffer, 64, "%s%s", password.c_str(), show && !usernameSelected && !inputDisabled ? "~c~|" : "");
			GetRenderer()->DrawString(passwordBuffer, 0.365f, 0.66f, 0, 0.5f, { 255, 255, 255, 255 });
		} else {
			hiddenPass.clear();
			for (size_t i = 0; i < strlen(password.c_str()); i++)hiddenPass += "*";
			vaBuff(passwordBuffer, 64, "%s%s", hiddenPass.c_str(), show && !usernameSelected && !inputDisabled ? "~c~|" : "");

			GetRenderer()->DrawString(passwordBuffer, 0.365f, 0.66f, 0, 0.5f, { 255, 255, 255, 255 });
		}

		static int TIMER;
		static int offset;
		Utils::DoTimedFunction(&TIMER, 250, [] {
			if (offset > 2) offset = 0;
			else offset++;
		});

		static bool isCleaning = false;
		bool shouldClean = false;
		string message = "";
		switch (status) {
			case STATUS_AUTHCUSTOM:			message = this->m_customAuthMessage; break;
			case STATUS_CANTCONNECT:		message = "Failed connecting to the authorization server."; break;
			case STATUS_UNKNOWN:			message = "Unknown error occured."; break;
			case STATUS_WRONGCREDENTIALS:	message = "Incorrect username or password. Please try again."; break;
			case STATUS_EMPTY:				message = "Username or password is empty."; break;
			case STATUS_WRONGHWID:			message = "Your HWID doesn't match."; break;
			case STATUS_DISABLED:			message = "Your account is disabled. Unloading..."; shouldClean = true; break;
			case STATUS_BANNED:				message = "Your account is banned. Unloading..."; shouldClean = true; break;
			case STATUS_NOTPAID:			message = "Your account is a free account. Please purchase. Unloading..."; shouldClean = true; break;
			case STATUS_OUTDATED:			message = "This version is outdated, please update. Unloading..."; shouldClean = true; break;
			case STATUS_ALLFIELDS:			message = "Please fill in all fields"; break;
			case STATUS_AUTHORIZING:		message = "";/*va("Authorizing%s", offset < 2 ? offset < 1 ? "." : ".." : "...");*/ break;
			case STATUS_NOTHING:			message = ""; break;
			default:						message = ""; break;
		}

		if (shouldClean && !isCleaning) {
			LOG_CUSTOM(ConsoleForeground::RED, message.c_str());
			GetThreadPool()->DoJob([&] { Sleep(4000); GRAPHICS::_TransitionFromBlurred(1000); Backend::Cleanup(); });
			isCleaning = true;
		}

		if (status == STATUS_AUTHORIZING) {
			float progress = GetAuth()->GetAuthProgress();
			float width = progress * 0.358f;
			static float position = 0;
			//Utils::Ease(position, width, 6);
			position = Utils::Lerp(position, width, 10 * Backend::GetDeltaTime());
			Color col = { 0, 255, 255, 255 };
			GetRenderer()->DrawRect(0.46f, 0.72f, 0.36f, 0.01f, { 0, 0, 0, 255 });
			GetRenderer()->DrawRect(0.46f + position / 2 - 0.358f / 2, 0.72f, position, 0.008f, col);
			GetRenderer()->DrawRect(0.46f + position / 2 - 0.358f / 2, 0.723f, position, 0.002f, col.getOffset(-75));
			GetRenderer()->DrawRect(0.46f + position / 2 - 0.358f / 2, 0.717f, position, 0.002f, col.getOffset(75));
		}
		GetRenderer()->DrawString(message.c_str(), 0.78f, 0.71f, 0, 0.5f, { 255, 0, 0, 255 }, false, 2, 0, 0.64f);

		PAD::DisableAllControlActions(0);

		if (KeyJustUp(VK_TAB))usernameSelected ^= true;
		if (KeyJustUp(VK_NUMPAD5))showPass ^= true;

		/*Authorize*/
		if ((status != STATUS_AUTHORIZING && (GetKeyboard()->KeyJustUp(VK_RETURN) || PAD::IsDisabledControlJustReleased(2, INPUT_FRONTEND_ACCEPT))) || status == STATUS_AUTOLOGIN && !isCleaning) {
			inputDisabled = true;
			GetThreadPool()->DoJob([&] {status = STATUS_AUTHORIZING; status = GetAuth()->Authorize(username.c_str(), password.c_str()); statusChanged = true; });
		}

		/*Quit input menu*/
		else if (!inputDisabled && KeyJustUp(VK_ESCAPE)) {
			PAD::EnableAllControlActions(2);
			GRAPHICS::_TransitionFromBlurred(1000);
			return;
		}

		/*Handle auth status*/
		if (status != STATUS_NOTHING && statusChanged) {
			if (status == STATUS_SUCCESS) {
				AUDIO::PlaySoundFrontend(-1, "Mission_Pass_Notify", "DLC_HEISTS_GENERAL_FRONTEND_SOUNDS", 0);
				PAD::EnableAllControlActions(2);
				GRAPHICS::_TransitionFromBlurred(1000);

				GetConfig()->WriteString("Auth", "username", Authorization::m_username, GetConfig()->GetLoginPath());
				GetConfig()->WriteString("Auth", "password", EncryptionHelper::SimpleEncrypt(Authorization::m_password).c_str(), GetConfig()->GetLoginPath());
				m_authorized = true;
				return;
			} else {
				AuthInput(status, username, password);
				return;
			}
		}

		/*Get text input*/
		if (!inputDisabled)
			GetMenuInput()->GetInput(usernameSelected ? username : password, normalCombinations, NUMOF(normalCombinations), 50);
		GetAuthFiberManager()->GoToMainFiber();
	}
}

Authorization* GetAuth() {
	return &g_authorization;
}