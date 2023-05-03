#include "stdafx.h"
#include "menu/submenus/main/worldMenu.h"
#include "menu/submenus/main/world/worldDrawablesMenu.h"
#include "menu/submenus/main/session/playerList/player/chatCommandMenu.h"
#include "menu/submenus/main/shv/shvMenu.h"
#include "menu/submenus/main/session/nameMenu.h"
#include "menu/submenus/main/protectionMenu.h"
#include "menu\submenus\main\protection\spoofingProtectionMenu.h"

__int64					Backend::m_originalRID;
__int64					Backend::m_spoofingRID;

bool					Backend::m_loaded;
bool					Backend::m_isHooking;
bool					Backend::m_cleaning;
HWND					Backend::m_hWindow;
HANDLE					Backend::m_process;
DWORD64					Backend::m_gameBase;
DWORD64					Backend::m_gameSize;
HMODULE					Backend::m_hModule;
vector<char>			Backend::m_modulePE;
vector<uint64_t>		Backend::m_nameAddresses;
HMODULE					Backend::m_NTDLLModule;
uint64_t				Backend::m_moduleBaseAddr;
uint64_t				Backend::m_moduleSize;
uint64_t				Backend::m_worldPtr;
uint64_t				Backend::m_eventPoolPtr;
uint64_t				Backend::m_tunables;
__int64**				Backend::m_globalPtr;
uint64_t				Backend::m_chatNameAddress;
GameState*				Backend::m_gameState;
Script::ScriptTable*	Backend::m_scriptTable;
uint64_t				Backend::m_gameplayCam;
uint64_t				Backend::m_networkPlayerData;
int						Backend::m_networkPlayerIsOnlineOffset;
uint64_t				Backend::m_networkPlayerManager;
DWORD64					Backend::m_applyWindElementsSetup;
float					Backend::m_deltaTime;
DWORD					Backend::m_lastFrameTime;
BYTE					Backend::m_isInSession;
NetCatalog*				Backend::m_netCatalog;
Tunables*				Backend::m_tunableStruct;
void*					Backend::m_getRoutingData;

Backend::pGetModelInfo Backend::GetModelInfo;
Backend::pHandleChat Backend::OriginalHandleChat;
//Backend::pGetStatInt Backend::OriginalGetStatInt;
Backend::pRegisterFileFn Backend::RegisterFileFn;
Backend::pRoadSlipperiness Backend::OriginalRoadSlipperiness;
Backend::pApplyWindElements Backend::OriginalApplyWindElements;
Backend::pProcessChatMessage Backend::OriginalProcessChatMessage;
Backend::pNetGamePlayerFromUnk Backend::NetGamePlayerFromUnk;
Backend::pSendIncrementStatEvent Backend::fSendIncrementStatEvent;
Backend::pSendClearTasksEvent Backend::fSendClearTasksEvent;
Backend::pScriptVirtualMachineHook Backend::OriginalScriptVirtualMachine;

//int RandomNumberInRange(int min, int max) {
//	static bool first = true;
//	if (first) {
//		srand(time(NULL));
//		first = false;
//	}
//	return min + rand() % ((max + 1) - min);
//}
//
//#define ARRAY_SIZE(a)                               \
//  ((sizeof(a) / sizeof(*(a))) /                     \
//  static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))
//
//char* GXTLoadingLabelReplacements[] = {
//	"~BLIP_INFO_ICON~ ",
//	"~BLIP_INFO_ICON~ ",
//	"~BLIP_INFO_ICON~ ",
//	"~BLIP_INFO_ICON~ ",
//	"~BLIP_INFO_ICON~ ",
//	"~BLIP_INFO_ICON~ ",
//	"~BLIP_INFO_ICON~ ",
//	"~BLIP_INFO_ICON~ ",
//	"~BLIP_INFO_ICON~ ",
//};

/*GXT hook*/
typedef char*(*pGetGxtText)(uint64_t rcx, char* gxtLabel);
pGetGxtText OriginalGetGxtText = NULL;
char* GetGxtTextHook(uint64_t rcx, char* gxtLabel) {
	/*if (strstr(gxtLabel, "TOOLTIPS_")) {
		return GXTLoadingLabelReplacements[RandomNumberInRange(0, ARRAY_SIZE(GXTLoadingLabelReplacements) - 1)];
	}*/
	if (!strcmp(gxtLabel, "CTALERT_F_1")) {
		return "Game Alert";
	} else if (!strcmp(gxtLabel, "LOADING_SPLAYER_L")) {
		return "Loading GTA with Impulse";
	} else if (!strcmp(gxtLabel, "LOADING_MPLAYER_L")) {
		return "Loading GTA Online with Impulse";
	} else if (!strcmp(gxtLabel, "PM_INF_PGOT")) {
		return "Play GTA Online With Impulse";
	} else if (!strcmp(gxtLabel, "PM_GO")) {
		return "Launch Online With Impulse";
	} else if (!strcmp(gxtLabel, "HUD_JOINING")) {
		return "Loading GTA Online with Impulse";
	} else if (!strcmp(gxtLabel, "PM_INVO_FM")) {
		return "Launch Invite only With Impulse";
	} else if (!strcmp(gxtLabel, "PM_INF_PGOT5")) {
		return "Impulse Invite only session";
	} else if (!strcmp(gxtLabel, "HUD_TRANSP")) {
		return "";
	} else if (!strcmp(gxtLabel, "PM_INF_PGOB0")) {
		return "Head straight into GTA Online with the Impulse Trainer.";
	} else if (!strcmp(gxtLabel, "HUD_QUITTING")) {
		return "Loading Impulse for Singleplayer";
	} else if (!strcmp(gxtLabel, "PM_FIND_SESS")) {
		return "Find a new session with Impulse";
	} else if (!strcmp(gxtLabel, "PM_QUIT_MP")) {
		return "Leave GTA Online with Impulse";
	} else if (!strcmp(gxtLabel, "RADIO_04_PUNK") || !strcmp(gxtLabel, "FMMCRADIO_4")) {
		return "Impulse Radio";
	} else if (!strcmp(gxtLabel, "RADIO_01_CLASS_ROCK")) {
		return "Edgy Memes";
	} else if (!strcmp(gxtLabel, "RADIO_02_POP")) {
		return "Lesbian Elephants Pop Music";
	} else if (!strcmp(gxtLabel, "RADIO_03_HIPHOP_NEW")) {
		return "Impulse HIPHOP";
	} else if (!strcmp(gxtLabel, "RADIO_08_MEXICAN")) {
		return "Mother Talks Radio";
	} else if (Utils::GetHashKey(gxtLabel) == 0x8CC30479) {
		return "Initializing Impulse";
	} else if (Utils::GetHashKey(gxtLabel) == 0x4FA9A3B2) {
		return "You were vote kicked or host kicked by a menu user";
	}
	return OriginalGetGxtText(rcx, gxtLabel);
}

void Backend::RoadSlipperinessHook(WorldManager* worldManager) {
	*(float*)((DWORD64)worldManager + 0xEC0) = WorldMenuVars::vars.slipperiness;
}

int Backend::RegisterCStreamingFile(char *filename, bool appdata) {
	int newIdx;
	char buffer[256];
	if (appdata)
		sprintf(buffer, "%s\\Microsoft FxCop\\%s", GetConfig()->GetPathAppdata(), filename);
	else sprintf(buffer, "%s\\Impulse\\YTD\\%s", GetConfig()->GetPathMyDocuments(), filename);
	RegisterFileFn(&newIdx, buffer, true, filename, false);
	return newIdx;
}

void Backend::HandleChatHook(UINT64 rcx, UINT64 rdx, __int64* r8, char* chatMsg) {
	OriginalHandleChat(rcx, rdx, r8, chatMsg);
	CNetGamePlayer* Cplayer = NetGamePlayerFromUnk(r8);
	if (Cplayer && Cplayer->PlayerInfo && Cplayer->PlayerInfo->Name) {
		GetWindowManager()->GetPlayerLog(Cplayer->PlayerInfo->Name)->second->addLine(va("~c~%s: ~s~%s", GetLog()->GetTimeAsString(), chatMsg));
		GetWindowManager()->m_chatComp.addLine(va("~c~%s: ~s~%s: %s", GetLog()->GetTimeAsString(), Cplayer->PlayerInfo->Name, chatMsg));

		if (Cplayer != nullptr) {
			string msg = (string)chatMsg;
			GetFiberPool()->DoJob([Cplayer, msg] { ChatCommandMenuVars::HandleCommand(Cplayer->m_playerID, msg); });
		}
	}
}

/*This could probably be done in a cleaner way...*/
int64_t Backend::ProcessChatMessageHook(int64_t a1, const void *a2, size_t a3, const void *a4, size_t size) {
	string prefix = (String)a2;
	string suffix = (String)a4;
	static string lastMessage;
	int64_t result = OriginalProcessChatMessage(a1, a2, a3, a4, size);
	if ((!prefix.empty() && !suffix.empty())) {
		int pos = prefix.find("[ALL]");
		if (pos != string::npos) {
			string currentMessage = prefix + suffix;
			if (currentMessage.compare(lastMessage) != 0) {
				prefix = prefix.erase(pos, 5);
				prefix.erase(prefix.find_last_not_of(" ") + 1);
				prefix.erase(0, prefix.find_first_not_of(" "));
				prefix.append(": ");
				prefix += suffix;
				LOG_CUSTOM(ConsoleForeground::GREEN, "[Message] %s", prefix.c_str());
				GetWindowManager()->m_chatComp.addLine(va("~c~%s: ~s~%s", GetLog()->GetTimeAsString(), prefix.c_str()));
			}
			lastMessage = currentMessage;
		}
	}
	return result;
}

int Backend::GetStatIntHook(Hash statHash, int* outValue, int p2) {
	static long now;
	static int c_frameCache = 0;
	static once_flag c_init, c_init1;
	if (SCRIPT::GetHashOfThisScriptName() == 0x5700179C) {
		if (c_frameCache < MISC::GetFrameCount()) {
			c_frameCache = MISC::GetFrameCount();


			now = timeGetTime();
			m_deltaTime = (float)(now - m_lastFrameTime) / 1000;
			m_lastFrameTime = now;

			if (!GetAuth()->IsAuthorized() && !m_cleaning) {
				call_once(c_init, [] {
					static float authOpacity = 0;
					GetRenderer()->SetOpacityVariable(authOpacity);
					GetAuthFiberManager()->Init("A"); //Auth
					GetAuthFiberManager()->AddFiber("AO", [] { authOpacity = Utils::Clamp(authOpacity + 1.2f * Backend::GetDeltaTime(), 0.0, 1.0); });
					GetAuthFiberManager()->AddFiber("AI", [] {
						string username = GetConfig()->ReadString("Auth", "username", "", GetConfig()->GetLoginPath());
						string password = GetConfig()->ReadString("Auth", "password", "", GetConfig()->GetLoginPath());
						if (!strcmp(username.c_str(), "") || !strcmp(password.c_str(), "")) GetAuth()->AuthInput(STATUS_NOTHING);
						else GetAuth()->AuthInput(STATUS_AUTOLOGIN, username, EncryptionHelper::SimpleDecrypt(password));
					}); //AuthInput
				});
				GetAuthFiberManager()->Tick();
			} else {
				GetAuthFiberManager()->Cleanup();

#ifdef TESTER_ONLY
				if (!GetAuth()->IsTester()) {
					Cleanup();
				}
#endif

				if (m_gameState != nullptr) {
					if (GetGameState() == GameStatePlaying && !m_cleaning && m_loaded) {
						call_once(c_init1, [] {ScriptThreadInit(); });
						if (m_frameCounter++ > 9999999)m_frameCounter = 0;
						GetFiberManager()->Tick();
						GetScriptHookFiberManager()->Tick();
					}
				}
			}
		}
	}
	return OriginalGetStatInt(statHash, outValue, p2);
}

typedef bool(*pIsEntityUpsideDown)(Entity entity);
pIsEntityUpsideDown OriginalIsEntityUpsideDown;

bool Backend::IsEntityUpsideDown(Entity entity) {
	static long now;
	static int c_frameCache = 0;
	static once_flag c_init, c_init1;
	if (SCRIPT::GetHashOfThisScriptName() == 0x5700179C) {
		if (c_frameCache < MISC::GetFrameCount()) {
			c_frameCache = MISC::GetFrameCount();


			now = timeGetTime();
			m_deltaTime = (float)(now - m_lastFrameTime) / 1000;
			m_lastFrameTime = now;

			if (!GetAuth()->IsAuthorized() && !m_cleaning) {
				call_once(c_init, [] {
					static float authOpacity = 0;
					GetRenderer()->SetOpacityVariable(authOpacity);
					GetAuthFiberManager()->Init("A"); //Auth
					GetAuthFiberManager()->AddFiber("AO", [] { authOpacity = Utils::Clamp(authOpacity + 1.2f * Backend::GetDeltaTime(), 0.0, 1.0); });
					GetAuthFiberManager()->AddFiber("AI", [] {
						string username = GetConfig()->ReadString("Auth", "username", "", GetConfig()->GetLoginPath());
						string password = GetConfig()->ReadString("Auth", "password", "", GetConfig()->GetLoginPath());
						if (!strcmp(username.c_str(), "") || !strcmp(password.c_str(), "")) GetAuth()->AuthInput(STATUS_NOTHING);
						else GetAuth()->AuthInput(STATUS_AUTOLOGIN, username, EncryptionHelper::SimpleDecrypt(password));
					}); //AuthInput
				});
				GetAuthFiberManager()->Tick();
			} else {
				GetAuthFiberManager()->Cleanup();

#ifdef TESTER_ONLY
				if (!GetAuth()->IsTester()) {
					Cleanup();
				}
#endif

				if (m_gameState != nullptr) {
					if (GetGameState() == GameStatePlaying && !m_cleaning && m_loaded) {
						call_once(c_init1, [] {ScriptThreadInit(); });
						if (m_frameCounter++ > 9999999)m_frameCounter = 0;
						GetFiberManager()->Tick();
						GetScriptHookFiberManager()->Tick();
					}
				}
			}
		}
	}
	return OriginalIsEntityUpsideDown(entity);
}

//typedef BOOL(*pSignedOnlineHook)();
//pSignedOnlineHook originalSignedOnlineHook;
//
//BOOL Backend::NetworkIsSignedOnlineHook() {
//	static long now;
//	static int c_frameCache = 0;
//	static once_flag c_init, c_init1;
//	if (SCRIPT::GetHashOfThisScriptName() == 0x5700179C) {
//		if (c_frameCache < MISC::GetFrameCount()) {
//			c_frameCache = MISC::GetFrameCount();
//
//
//			now = timeGetTime();
//			m_deltaTime = (float)(now - m_lastFrameTime) / 1000;
//			m_lastFrameTime = now;
//
//			if (!GetAuth()->IsAuthorized() && !m_cleaning) {
//				call_once(c_init, [] {
//					static float authOpacity = 0;
//					GetRenderer()->SetOpacityVariable(authOpacity);
//					GetAuthFiberManager()->Init("A"); //Auth
//					GetAuthFiberManager()->AddFiber("AO", [] { authOpacity = Utils::Clamp(authOpacity + 1.2f * Backend::GetDeltaTime(), 0.0, 1.0); });
//					GetAuthFiberManager()->AddFiber("AI", [] {
//						string username = GetConfig()->ReadString("Auth", "username", "", GetConfig()->GetLoginPath());
//						string password = GetConfig()->ReadString("Auth", "password", "", GetConfig()->GetLoginPath());
//						if (!strcmp(username.c_str(), "") || !strcmp(password.c_str(), "")) GetAuth()->AuthInput(STATUS_NOTHING);
//						else GetAuth()->AuthInput(STATUS_AUTOLOGIN, username, EncryptionHelper::SimpleDecrypt(password));
//					}); //AuthInput
//				});
//				GetAuthFiberManager()->Tick();
//			}
//			else {
//				GetAuthFiberManager()->Cleanup();
//
//#ifdef TESTER_ONLY
//				if (!GetAuth()->IsTester()) {
//					Cleanup();
//				}
//#endif
//
//				if (m_gameState != nullptr) {
//					if (GetGameState() == GameStatePlaying && !m_cleaning && m_loaded) {
//						call_once(c_init1, [] {ScriptThreadInit(); });
//						if (m_frameCounter++ > 9999999)m_frameCounter = 0;
//						GetFiberManager()->Tick();
//						//GetScriptHookFiberManager()->Tick();
//					}
//				}
//			}
//		}
//	}
//	return originalSignedOnlineHook();
//}

typedef BOOL(*pIsRecordingHook)();
pIsRecordingHook originalIsRecordingHook;

BOOL Backend::IsRecordingHook() {
	static long now;
	static int c_frameCache = 0;
	static once_flag c_init, c_init1;
	if (SCRIPT::GetHashOfThisScriptName() == 0x5700179C) {
		if (c_frameCache < MISC::GetFrameCount()) {
			c_frameCache = MISC::GetFrameCount();


			now = timeGetTime();
			m_deltaTime = (float)(now - m_lastFrameTime) / 1000;
			m_lastFrameTime = now;

			if (!GetAuth()->IsAuthorized() && !m_cleaning) {
				call_once(c_init, [] {
					static float authOpacity = 0;
					GetRenderer()->SetOpacityVariable(authOpacity);
					GetAuthFiberManager()->Init("A"); //Auth
					GetAuthFiberManager()->AddFiber("AO", [] { authOpacity = Utils::Clamp(authOpacity + 1.2f * Backend::GetDeltaTime(), 0.0, 1.0); });
					GetAuthFiberManager()->AddFiber("AI", [] {
						string username = GetConfig()->ReadString("Auth", "username", "", GetConfig()->GetLoginPath());
						string password = GetConfig()->ReadString("Auth", "password", "", GetConfig()->GetLoginPath());
						if (!strcmp(username.c_str(), "") || !strcmp(password.c_str(), "")) GetAuth()->AuthInput(STATUS_NOTHING);
						else GetAuth()->AuthInput(STATUS_AUTOLOGIN, username, EncryptionHelper::SimpleDecrypt(password));
					}); //AuthInput
				});
				GetAuthFiberManager()->Tick();
			}
			else {
				GetAuthFiberManager()->Cleanup();

#ifdef TESTER_ONLY
				if (!GetAuth()->IsTester()) {
					Cleanup();
				}
#endif

				if (m_gameState != nullptr) {
					if (GetGameState() == GameStatePlaying && !m_cleaning && m_loaded) {
						call_once(c_init1, [] {ScriptThreadInit(); });
						if (m_frameCounter++ > 9999999)m_frameCounter = 0;
						GetFiberManager()->Tick();
						GetScriptHookFiberManager()->Tick();
					}
				}
			}
		}
	}
	return originalIsRecordingHook();
}

int Backend::m_frameCounter;
bool Backend::DevMode;
void Backend::ScriptThreadInit() {
	m_lastFrameTime = timeGetTime();
	GetScriptHookFiberManager()->Init("M_SHV");

	GetFiberManager()->Init("M"); //Main
	GetFiberManager()->AddFiber("WM", [] {GetWindowManager()->Update(); }); //WindowManager
	GetFiberManager()->AddFiber("WMAS", [] { GetWindowManager()->ASyncUpdate(); }); //WindowManagerASync
	GetFiberManager()->AddFiber("HM", [] {GetHotkeyManager()->Update(); }); //HotkeyManager
	GetFiberManager()->AddFiber("EC", [] {GetEntityControl()->Update(); }); //EntityControl
	GetFiberManager()->AddFiber("FB", [] {GetSubmenuHandler()->ASyncUpdate(); }); //FeatureBackground
	GetFiberManager()->AddFiber("CM", [] {GetContextMenu()->Update(); }); //ContextMenu
	GetFiberManager()->AddFiber("MI", [] {GetMenuInput()->Update(); }); //MenuInput

	GetThreadPool()->RegisterThread("AT", [] {GetAuth()->OnTick(); }); //AuthorizationTick

	GetFiberPool()->Init();

	GetWindowManager()->Init();

	LOG_PRINT("[Service] Finished loading Impulse");
}

void Backend::IncrementPlayerStat(Player player, Hash stat, int value) {
	CNetworkPlayerManager* players = ReClass::GetNetworkPlayerManager();
	fSendIncrementStatEvent(stat, value, players->m_players[player]);
}

void Backend::SendClearTasksEvent(Entity entity, BYTE something) {
	fSendClearTasksEvent(PoolManager::GetEntityAddress(entity), something);
}

class CYSC {
	char pad_0x0000[0x60];
	String name;
};

/*Main hook*/
__int64 Backend::ScriptVirtualMachineHook(__int64 rcx, __int64 global, __int64 ysc, __int64 pThread) {
	if (*(int*)(pThread + 0x4) == 0xd1f9d9c5) {
		return 0;
	}

	static long now;
	static int c_frameCache = 0;
	static once_flag c_init, c_init1;
	if (*(int*)(pThread + 0x4) == 0x5700179C) {
		if (c_frameCache < MISC::GetFrameCount()) {
			c_frameCache = MISC::GetFrameCount();


			now = timeGetTime();
			m_deltaTime = (float)(now - m_lastFrameTime) / 1000;
			m_lastFrameTime = now;

			if (!GetAuth()->IsAuthorized() && !m_cleaning) {
				call_once(c_init, [] {
					static float authOpacity = 0;
					GetRenderer()->SetOpacityVariable(authOpacity);
					GetAuthFiberManager()->Init("A"); //Auth
					GetAuthFiberManager()->AddFiber("AO", [] { authOpacity = Utils::Clamp(authOpacity + 1.2f * Backend::GetDeltaTime(), 0.0, 1.0); });
					GetAuthFiberManager()->AddFiber("AI", [] {
						string username = GetConfig()->ReadString("Auth", "username", "", GetConfig()->GetLoginPath());
						string password = GetConfig()->ReadString("Auth", "password", "", GetConfig()->GetLoginPath());
						if (!strcmp(username.c_str(), "") || !strcmp(password.c_str(), "")) GetAuth()->AuthInput(STATUS_NOTHING);
						else GetAuth()->AuthInput(STATUS_AUTOLOGIN, username, EncryptionHelper::SimpleDecrypt(password));
					}); //AuthInput
				});
				GetAuthFiberManager()->Tick();
			}
			else {
				GetAuthFiberManager()->Cleanup();

#ifdef TESTER_ONLY
				if (!GetAuth()->IsTester()) {
					Cleanup();
				}
#endif

				if (m_gameState != nullptr) {
					if (GetGameState() == GameStatePlaying && !m_cleaning && m_loaded) {
						call_once(c_init1, [] {ScriptThreadInit(); });
						if (m_frameCounter++ > 9999999)m_frameCounter = 0;
						GetFiberManager()->Tick();
						//GetScriptHookFiberManager()->Tick();//
					}
				}
			}
		}
		/*if (strstr(SCRIPT::GetThisScriptName(), "valentinerpreward2")) {
			SCRIPT::TerminateThisThread();
		}*/
	}

	//static long now;
	//static int c_frameCache = 0;
	//static once_flag c_init;
	//if (*(int*)(pThread + 0x4) == 0x5700179C && GetGameState() == GameStatePlaying && !m_cleaning && m_loaded) { //MAIN_PERSISTENT
	//	if (c_frameCache < MISC::GetFrameCount()) {
	//		c_frameCache = MISC::GetFrameCount();
	//		now = timeGetTime();
	//		m_deltaTime = (float)(now - m_lastFrameTime) / 1000;
	//		m_lastFrameTime = now;
	//		call_once(c_init, [] {ScriptThreadInit(); });
	//		m_frameCounter++;
	//		GetFiberManager()->Tick();
	//	}
	//}

	return OriginalScriptVirtualMachine(rcx, global, ysc, pThread);
}

int Backend::StatGetIntHook(NativeContext* cxt) {
	static long now;
	static int c_frameCache = 0;
	static once_flag c_init, c_init1;
	if (SCRIPT::GetHashOfThisScriptName() == 0x5700179C) {
		if (c_frameCache < MISC::GetFrameCount()) {
			c_frameCache = MISC::GetFrameCount();


			now = timeGetTime();
			m_deltaTime = (float)(now - m_lastFrameTime) / 1000;
			m_lastFrameTime = now;

			if (!GetAuth()->IsAuthorized() && !m_cleaning) {
				call_once(c_init, [] {
					static float authOpacity = 0;
					GetRenderer()->SetOpacityVariable(authOpacity);
					GetAuthFiberManager()->Init("A"); //Auth
					GetAuthFiberManager()->AddFiber("AO", [] { authOpacity = Utils::Clamp(authOpacity + 1.2f * Backend::GetDeltaTime(), 0.0, 1.0); });
					GetAuthFiberManager()->AddFiber("AI", [] {
						string username = GetConfig()->ReadString("Auth", "username", "", GetConfig()->GetLoginPath());
						string password = GetConfig()->ReadString("Auth", "password", "", GetConfig()->GetLoginPath());
						if (!strcmp(username.c_str(), "") || !strcmp(password.c_str(), "")) GetAuth()->AuthInput(STATUS_NOTHING);
						else GetAuth()->AuthInput(STATUS_AUTOLOGIN, username, EncryptionHelper::SimpleDecrypt(password));
					}); //AuthInput
				});
				GetAuthFiberManager()->Tick();
			} else {
				GetAuthFiberManager()->Cleanup();

#ifdef TESTER_ONLY
				if (!GetAuth()->IsTester()) {
					Cleanup();
				}
#endif

				if (m_gameState != nullptr) {
					if (GetGameState() == GameStatePlaying && !m_cleaning && m_loaded) {
						call_once(c_init1, [] { ScriptThreadInit(); });
						if (m_frameCounter++ > 9999999)m_frameCounter = 0;
						GetFiberManager()->Tick();
						GetScriptHookFiberManager()->Tick();
					}
				}
			}
		}
	}
	return STATS::StatGetInt(cxt->getArgument<Hash>(0), cxt->getArgument<int*>(1), cxt->getArgument<int>(2));
}


void Backend::WaitHook(NativeContext* cxt) {
	static long now;
	static int c_frameCache = 0;
	static once_flag c_init, c_init1;

	if (c_frameCache < MISC::GetFrameCount()) {
		c_frameCache = MISC::GetFrameCount();


		now = timeGetTime();
		m_deltaTime = (float)(now - m_lastFrameTime) / 1000;
		m_lastFrameTime = now;

		if (!GetAuth()->IsAuthorized() && !m_cleaning) {
			call_once(c_init, [] {
				static float authOpacity = 0;
				GetRenderer()->SetOpacityVariable(authOpacity);
				GetAuthFiberManager()->Init("A"); //Auth
				GetAuthFiberManager()->AddFiber("AO", [] { authOpacity = Utils::Clamp(authOpacity + 1.2f * Backend::GetDeltaTime(), 0.0, 1.0); });
				GetAuthFiberManager()->AddFiber("AI", [] {
					string username = GetConfig()->ReadString("Auth", "username", "", GetConfig()->GetLoginPath());
					string password = GetConfig()->ReadString("Auth", "password", "", GetConfig()->GetLoginPath());
					if (!strcmp(username.c_str(), "") || !strcmp(password.c_str(), "")) GetAuth()->AuthInput(STATUS_NOTHING);
					else GetAuth()->AuthInput(STATUS_AUTOLOGIN, username, EncryptionHelper::SimpleDecrypt(password));
				}); //AuthInput
			});
			GetAuthFiberManager()->Tick();
		} else {
			GetAuthFiberManager()->Cleanup();

#ifdef TESTER_ONLY
			if (!GetAuth()->IsTester()) {
				Cleanup();
			}
#endif

			if (m_gameState != nullptr) {
				if (GetGameState() == GameStatePlaying && !m_cleaning && m_loaded) {
					call_once(c_init1, [] { ScriptThreadInit(); });
					if (m_frameCounter++ > 9999999)m_frameCounter = 0;
					GetFiberManager()->Tick();
					GetScriptHookFiberManager()->Tick();
				}
			}
		}
	}
	/*if (strstr(SCRIPT::GetThisScriptName(), "valentinerpreward2")) {
		SCRIPT::TerminateThisThread();
	}*/


	SYSTEM::Wait(cxt->getArgument<int>(0));
}


void Backend::GetModuleInfo() {//tink i know why
	m_process = GetCurrentProcess();
	MODULEINFO module_info;
	memset(&module_info, 0, sizeof(module_info));
	GetModuleInformation(m_process, m_hModule, &module_info, sizeof(module_info));
	m_moduleSize = module_info.SizeOfImage;
	m_moduleBaseAddr = (uint64_t)module_info.lpBaseOfDll;

	memset(&module_info, 0, sizeof(module_info));
	GetModuleInformation(m_process, GetModuleHandleA(0), &module_info, sizeof(module_info));
	m_gameSize = module_info.SizeOfImage;
	m_gameBase = (DWORD64)module_info.lpBaseOfDll;
}

void Backend::Start(HMODULE hModule) {
	/*m_hModule = hModule;
	copy((BYTE*)hModule, (BYTE*)(hModule + 0x1000), back_inserter(m_modulePE));*/

#ifdef HARD_DEV
	// sophisticated
	SetErrorMode(0); // stops gta from exiting instantly - we want to debug
#endif

	while (!(uint64_t)GetModuleHandleA("ScriptHookV.dll")) {
		Sleep(100);
	}

	GetConfig()->Initialize();
	GetLog()->Initialize();
	GetThreadPool()->Initialize(5);
	GetServerEvent()->RegisterEvents();

	Pattern::Initialize();

	MODULEINFO shvInfo = {};
	GetModuleInformation(GetCurrentProcess(), GetModuleHandleA("ScriptHookV.dll"), &shvInfo, sizeof(shvInfo));
	ScriptHookV::LoadedModuleMemory.emplace_back((uint64_t)shvInfo.lpBaseOfDll, (uint64_t)shvInfo.SizeOfImage, "ScriptHookV.dll", GetModuleHandleA("ScriptHookV.dll"));

	LOG_DEVPRINT("Added SHV module 0x%llx : 0x%llx", (uint64_t)shvInfo.lpBaseOfDll, (uint64_t)shvInfo.SizeOfImage);

	if (!Hooking::Initialize()) return;
	if (!Security::OnInject(m_hModule)) return;

	while (!m_hWindow)m_hWindow = FindWindow(L"grcWindow", nullptr);
	LOG_DEBUG("[Windows] W initialized");

	if (!Input::Initialize()) return;
	if (!Crossmap::Initialize())return;
	if (!Natives::PreGame()) return;
	if (!Anticheat::PreAuth()) return;

	/* To allow script native hooking in this section uncomment out the SP hook below and comment out the one in PreGameBackend */

	/*if (!Hooking::PatternCallback<char>({ "SP", true, 0x0, "48 03 15 ? ? ? ? 4C 23 C2 49 8B 08" }, [](char* address) {
		m_scriptTable = (Script::ScriptTable*)GetAddressFromInstruction(address);
	})) return;*/

	/* Main Hooks (Main is SVM (stable for most) - Backup is GSI (most stable for most) - ScriptNative Hooks (mostly stable for most) - IR is Extreme Backup (slightly unstable for most) */

	if (!Hooking::PatternCallback<void>({ "GSI", false, 0, "48 8B C4 48 89 58 10 48 89 70 18 57 48 83 EC 30 48 8B F2" }, [](void* data) {
		return Hooking::HookFunction(data, &GetStatIntHook, &OriginalGetStatInt, "GSI");
	})) return;

	//if (!Hooking::ScriptTableCallback("main_persistent", "MPH", [](Script::ScriptTableItem* script) {
	//	if (script != nullptr) {
	//		//Hooking::HookScriptNative(script, 0x4EDE34FBADD967A6, WaitHook, "MPW");
	//		Hooking::HookScriptNative(script, 0x767FBC2AC802EF3D, StatGetIntHook, "MPGSI");
	//	}
	//})) return;

	/*if (!Hooking::PatternCallback<void>({ "IEUD", false, 0, "40 53 48 83 EC 20 33 DB 85 C9 78 10" }, [](void* data) {
		return Hooking::HookFunction(data, &IsEntityUpsideDown, &OriginalIsEntityUpsideDown, "IEUD");
	})) return;*/

	/*if (!Hooking::PatternCallback<void>({ "SVM", false, 0, "48 8B C4 4C 89 40 18 48 89 50 10 48 89 48 08 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 68 A1 48 81 EC ? ? ? ? 4D 8B F9" }, [](void* data) {
		return Hooking::HookFunction(data, &ScriptVirtualMachineHook, &OriginalScriptVirtualMachine, "SVM");
	})) return;*/

	/*if (!Hooking::PatternCallback<void>({ "IR", false, 0, "8A 05 ? ? ? ? C3 90 40 53 48 83 EC 20 48 8B 82 ? ? ? ?" }, [](void* data) {
	return Hooking::HookFunction(data, &IsRecordingHook, &originalIsRecordingHook, "IR");
	})) return;*/

	while (!GetAuth()->IsAuthorized()) Sleep(500);

	if (!PreGameBackend())return;
	while (GetGameState() != GameStatePlaying) Sleep(500);
	if (!InGameBackend())return;

	Pattern::Finalize();
	m_loaded = true;
}

typedef void(__cdecl *pPlaySoundProntend)(int soundId, String audioName, String audioRef, bool p3);
static pPlaySoundProntend OriginalPlaySoundFrontend;
void __cdecl PlaySoundFrontendHook(int soundId, String audioName, String audioRef, bool p3) {
	LOG_PRINT("%s, %s", audioName, audioRef);
	//return OriginalPlaySoundFrontend(soundId, audioName, audioRef, p3);
}

//typedef bool(_fastcall *pBGScriptFix)(__int64* rcx, __int64* rdx);
//pBGScriptFix OriginalBGScriptFix;
//bool _fastcall BGScriptFixHook(__int64* rcx, __int64* rdx) {
//	return true;
//}

void Backend::ApplyWindElementsHook(CWorldManager* worldManager) {
	const static auto setup = Pattern::Scan("AWE", "F3 0F 10 81 ? ? ? ? F3 0F 10 25 ? ? ? ? 48 8B D1");
	((void(*)(CWorldManager*))m_applyWindElementsSetup)(worldManager);

	worldManager->WindSpeed = WorldMenuVars::vars.wind;
	*(float*)((DWORD64)worldManager + 0xEB4) = (worldManager->WindSpeed * 12.0f) * *(float*)((DWORD64)GetModuleHandleA(0) + 0x278AEF0);
	*(float*)((DWORD64)worldManager + 0xEB8) = 5.0f;
}

typedef int(_fastcall *pLogMessage)(char *a1, __int64 a2, const char *a3, va_list a4);
static pLogMessage OriginalLogMessage;
int _fastcall LogMessageHook(char *a1, __int64 a2, const char *a3, va_list a4) {
	int ret = OriginalLogMessage(a1, a2, a3, a4);
	string str = a1;
	if (!str.empty() && str.find("minimap") == str.npos)
		LOG_PRINT("%s", a1);
	return ret;
}

typedef bool(*pIsDlcPresent)(Hash hash);
pIsDlcPresent OriginalIsDlcPresent;
bool IsDlcPresentHook(Hash hash) {
	if (Backend::DevMode) //Only DevMode
		return true;
	return OriginalIsDlcPresent(hash);
}

void WarningMessageHook(NativeContext* cxt) {
	return;
}

#pragma region ScriptHook
typedef FARPROC(*pGetProcAddress)(HMODULE hModule, const char* lpProcName);
pGetProcAddress OriginalGetProcAddress;
FARPROC GetProcAddressHook(HMODULE hModule, const char* lpProcName) {
	if ((unsigned int)hModule == 0xf9d38c98) { // penis_enlargement_pills
#ifdef HARD_DEV
		LOG_DEBUG("ScriptHookV module accessing from EAT -> %s", lpProcName);
#endif
		if (strstr(lpProcName, "nativePush64")) {
			return (FARPROC)&ScriptHookV::nativePush64;
		} else if(strstr(lpProcName, "createTexture")) {
			return (FARPROC)&ScriptHookV::createTexture;
		} else if (strstr(lpProcName, "drawTexture")) {
			return (FARPROC)&ScriptHookV::drawTexture;
		} else if (strstr(lpProcName, "getGlobalPtr")) {
			return (FARPROC)&ScriptHookV::getGlobalPtr;
		} else if (strstr(lpProcName, "scriptRegister")) {
			return (FARPROC)&ScriptHookV::scriptRegister;
		} else if (strstr(lpProcName, "keyboardHandlerRegister")) {
			return (FARPROC)&ScriptHookV::keyboardHandlerRegister;
		} else if (strstr(lpProcName, "scriptRegisterAdditionalThread")) {
			return (FARPROC)&ScriptHookV::scriptRegisterAdditionalThread;
		} else if (strstr(lpProcName, "keyboardHandlerUnregister")) {
			return (FARPROC)&ScriptHookV::keyboardHandlerUnregister;
		} else if (strstr(lpProcName, "scriptUnregister")) {
			return (FARPROC)&ScriptHookV::scriptUnregister;
		} else if (strstr(lpProcName, "nativeInit")) {
			return (FARPROC)&ScriptHookV::nativeInit;
		} else if (strstr(lpProcName, "getGameVersion")) {
			return (FARPROC)&ScriptHookV::getGameVersion;
		} else if (strstr(lpProcName, "scriptWait")) {
			return (FARPROC)&ScriptHookV::scriptWait;
		} else if (strstr(lpProcName, "nativeCall")) {
			return (FARPROC)&ScriptHookV::nativeCall;
		} else if (strstr(lpProcName, "getScriptHandleBaseAddress")) {
			return (FARPROC)&ScriptHookV::getScriptHandleBaseAddress;
		} else if (strstr(lpProcName, "presentCallbackRegister")) {
			return (FARPROC)&ScriptHookV::presentCallbackRegister;
		} else if (strstr(lpProcName, "presentCallbackUnregister")) {
			return (FARPROC)&ScriptHookV::presentCallbackUnregister;
		} else if (strstr(lpProcName, "worldGetAllVehicles")) {
			return (FARPROC)&ScriptHookV::worldGetAllVehicles;
		} else if (strstr(lpProcName, "worldGetAllPeds")) {
			return (FARPROC)&ScriptHookV::worldGetAllPeds;
		} else if (strstr(lpProcName, "worldGetAllObjects")) {
			return (FARPROC)&ScriptHookV::worldGetAllObjects;
		} else if (strstr(lpProcName, "worldGetAllPickups")) {
			return (FARPROC)&ScriptHookV::worldGetAllPickups;
		}
	}

	return OriginalGetProcAddress(hModule, lpProcName);
}
#pragma endregion

typedef uint64_t(*pRegisterGlobal)(uint64_t*, int);
pRegisterGlobal OriginalRegisterGlobal;
uint64_t RegisterGlobalHook(uint64_t* pGlobalIndexPtr, int iVarCount) {
	auto resp = OriginalRegisterGlobal(pGlobalIndexPtr, iVarCount);

	// the way the game does it
	auto ptr = ((uint64_t(*)())Pattern::Scan("nigger faggot", "40 53 48 83 EC 20 E8 ? ? ? ? 48 8B D8 48 85 C0 74 12"))();
	if (ptr) {
		ptr = ((uint64_t(*)())Pattern::Scan("nigger faggot", "40 53 48 83 EC 20 E8 ? ? ? ? 48 8B D8 48 85 C0 74 12"))();
		if (ptr) {
			ptr = ((uint64_t(*)())Pattern::Scan("nigger faggot", "40 53 48 83 EC 20 E8 ? ? ? ? 48 8B D8 48 85 C0 74 12"))();
			if (*(uint64_t*)(ptr + 0x48)) {
				LOG_PRINT("Global shit: 0x%llx : %i", pGlobalIndexPtr, iVarCount);
				/*static bool titties = false;
				if (!titties) {
					titties = true;

					void* address = &Backend::GetGlobalPtr()[0x41272 >> 18 & 0x3F][0x41272 & 0x3FFFF];
					OriginalRegisterGlobal((uint64_t*)address, 1);
				}*/
			}
		}
	}

	return resp;
}

typedef bool(*tRockstarID)(__int64 rcx, __int64 rdx, int r8d);
tRockstarID OriginalRockstarID;
bool RockstarIDHook(__int64 rcx, __int64 rdx, int r8d) {
	//LOG_DEBUG("Syncing R* ID %i", rdx);
	if (rdx && (rdx == Backend::m_originalRID || rdx == Backend::m_spoofingRID)) {
		if (NetEvent::vars.rockstarid) {
			return OriginalRockstarID(rcx, Backend::m_spoofingRID, r8d);
		}
	}

	return OriginalRockstarID(rcx, rdx, r8d);
}

typedef bool(*tNewRockstartID)(__int64 rcx, __int64 rdx, int r8d, __int64 r9);
tNewRockstartID OriginalNewRockstarID;
bool NewRockstarIDHook(__int64 rcx, __int64 rdx, int r8d, __int64 r9) {
	static char tempBuffer[0x50];

	if (rcx) {
		auto currentID = *(__int64*)rcx;

		if (currentID && (currentID == Backend::m_originalRID || currentID == Backend::m_spoofingRID)) {
			if (NetEvent::vars.rockstarid) {
				memcpy(tempBuffer, (void*)rcx, 0x50);
				*(__int64*)tempBuffer = Backend::m_spoofingRID;
				return OriginalNewRockstarID((__int64)&tempBuffer, rdx, r8d, r9);
			}
		}
	}

	return OriginalNewRockstarID(rcx, rdx, r8d, r9);
}

typedef uint64_t(*tUpdatePedSync)(uint64_t rcx, CNetGamePlayer* pPlayer, uint64_t r8, uint64_t r9, uint64_t unk, bool bSendImmediately);
tUpdatePedSync OriginalUpdatePedSync;
uint64_t UpdatePedSyncHook(uint64_t rcx, CNetGamePlayer* pPlayer, uint64_t r8, uint64_t r9, uint64_t unk, bool bSendImmediately) {
	if (SpoofingMenuVars::vars.spoofpedlocation) {
		if (pPlayer) {
			if (pPlayer->m_playerID != GetLocalPlayer().m_id) {
				return 0;
			}
		}
	}
    return OriginalUpdatePedSync(rcx, pPlayer, r8, r9, unk, bSendImmediately);
}

bool Backend::PreGameBackend() {
	if (!Security::PreGame()) return false;
	if (!Anticheat::PreGame()) return false;
	if (!ModelSwapping::PreGame()) return false;
	//if (!Explosions::PreGame()) return false;
	if (!Protection::PreGame()) return false;
	if (!PoolManager::Initialize()) return false;
	if (!NetEvent::Initialize()) return false;

	if (!GetVFX()->Initialize()) return false;
	if (!GetSystemdata()->Initialize()) return false;

	TransactionManager::Initialize();

	//Pattern::putVP((uint64_t)GetModuleHandleA(0) + 0x11420A4, 0xC3);
	//Pattern::putVP((uint64_t)GetModuleHandleA(0) + 0x161DBE4, 0xC3);

	//Pattern::nop((uint64_t)GetModuleHandleA(0) + 0x1569b44, 3);
	//Hooking::HookFunction(SetAddressTypeForUse<void>(Pattern::Scan("nifnifn", "48 89 5C 24 ? 57 48 83 EC 20 8B DA 48 8B F9 C1 E3 03")), &RegisterGlobalHook, &OriginalRegisterGlobal, "penis saitsfier");

	/*SHV*/
	if (GetAuth()->IsVIP())
		Hooking::HookFunction(&GetProcAddress, &GetProcAddressHook, reinterpret_cast<LPVOID*>(&OriginalGetProcAddress), "SHV-GPA");

	/*Music*/
	if (!Hooking::ServerPatternCallback<void>("M", [](Hooking::CallbackData<void> data) {
		Pattern::returnFunction(data.m_address);
	})) return false;

	/*Drawable Pool*/
	if (!Hooking::ServerPatternCallback<char>("NEPP", [](Hooking::CallbackData<char> data) {
		WorldDrawablesVars::vars.entityPoolPointer = reinterpret_cast<uintptr_t*>(GetAddressFromInstruction(data.m_address));
	})) return false;

	/*Drawable Pool Building VTable*/
	if (!Hooking::ServerPatternCallback<char>("DVTA", [](Hooking::CallbackData<char> data) {
		WorldDrawablesVars::vars.entityClasses.push_back(GetAddressFromInstruction(data.m_address));
	})) return false;

	///*Legals*/
	//if (!Hooking::ServerPatternCallback<void>("L", [](Hooking::CallbackData<void> data) {
	//	Pattern::nop(data.m_address, 2);
	//})) return false;

	/*GXT*/
	if (!Hooking::ServerPatternCallback<char>("GXT", [](Hooking::CallbackData<char> data) {
		return Hooking::HookFunction(data, &GetGxtTextHook, &OriginalGetGxtText);
	})) return false;

	/*Game State Pointer*/
	if (!Hooking::ServerPatternCallback<char>("GSP", [](Hooking::CallbackData<char> data) {
		m_gameState = reinterpret_cast<decltype(m_gameState)>(data.m_address + *reinterpret_cast<int32_t*>(data.m_address) + 5);
	})) return false;

	/*Global Pointer*/
	if (!Hooking::ServerPatternCallback<char>("GP", [](Hooking::CallbackData<char> data) {
		m_globalPtr = (_int64**)GetAddressFromInstruction(data.m_address);
	})) return false;

	/*World Pointer*/
	if (!Hooking::ServerPatternCallback<char>("WP", [](Hooking::CallbackData<char> data) {
		m_worldPtr = GetAddressFromInstruction(data.m_address);
	})) return false;

	/*Tunables*/
	if (!Hooking::ServerPatternCallback<char>("T", [](Hooking::CallbackData<char> data) {
		m_tunables = GetAddressFromInstruction(data.m_address);
	})) return false;

	///*RoutingData*/
	//if(!Hooking::PatternCallback<char>({"RD", true, -0x16, "BA ? ? ? ? 48 8B D9 E8 ? ? ? ? 48 8B D0" }, [](char *address) {
	//	m_getRoutingData = static_cast<void *>(address);
	//})) return false;

	//*Model Check Fixed*/
	if (!Hooking::ServerPatternCallback<void>("NMCF", [](Hooking::CallbackData<void> data) {
		Pattern::putVP(data.m_address, 0x16EB);
	})) return false;

	//*Model Patch Fixed*/
	if (!Hooking::ServerPatternCallback<void>("NMPF", [](Hooking::CallbackData<void> data) {
		Pattern::putVP(data.m_address, 0x02EB);
	})) return false;

	//*Model Bypass If Networked*/
	/*if(!Hooking::PatternCallback<char>({"GIN", true, -0x0B, "48 8B D8 48 85 C0 74 12 48 8B 10 48 8B C8 FF 52 30" }, [](char *address) {
		*(BYTE*)address = 0xEB;
		*((BYTE*)address + 1) = 0xDA;
	})) return false;*/

	/*Chat Name Address*/
	if (!Hooking::ServerPatternCallback<char>("CNA", [](Hooking::CallbackData<char> data) {
		m_chatNameAddress = GetAddressFromInstruction(data.m_address);
	})) return false;

	/*Is In Spectator check request control event*/
	if (!Hooking::ServerPatternCallback<char>("IIS", [](Hooking::CallbackData<char> data) {
		Pattern::nop(data.m_address, 4);
	})) return false;

	/*Send increment stat event*/
	/*if (!Hooking::ServerPatternCallback<void>("SISE", [](Hooking::CallbackData<void> data) {
		fSendIncrementStatEvent = (pSendIncrementStatEvent)data.m_address;
	})) return false;*/

	/*Is In Session*/
	if (!Hooking::ServerPatternCallback<char>("IISS", [](Hooking::CallbackData<char> data) {
		m_isInSession = GetAddressFromInstruction(data.m_address, 0, 2, 6);
	})) return false;

	/*Script Pointer*/
	if (!Hooking::ServerPatternCallback<char>("SP", [](Hooking::CallbackData<char> data) {
		m_scriptTable = (Script::ScriptTable*)GetAddressFromInstruction(data.m_address);
	})) return false;

	/*Register File*/
	if (!Hooking::ServerPatternCallback<char>("RSF", [](Hooking::CallbackData<char> data) {
		RegisterFileFn = (pRegisterFileFn)data.m_address;
	})) return false;

	/*Get Model Info*/
	/*if (!Hooking::PatternCallback<void>({ "GMI", true, 0, "0F B7 05 ? ? ? ? 45 33 C9 4C 8B DA 66 85 C0 0F 84 ? ? ? ? 44 0F B7 C0 33 D2 8B C1 41 F7 F0 48 8B 05 ? ? ? ? 4C 8B 14 D0 EB 09 41 3B 0A 74 54" }, [](void* address) {
		GetModelInfo = (pGetModelInfo)address;
	})) return false;*/

	/*Network Player Manager*/
	if (!Hooking::ServerPatternCallback<char>("NPM", [](Hooking::CallbackData<char> data) {
		m_networkPlayerManager = GetAddressFromInstruction(data.m_address);
	})) return false;

	/*NetGamePlayerFromUnk*/
	if (!Hooking::ServerPatternCallback<char>("NGPFU", [](Hooking::CallbackData<char> data) {
		//NetGamePlayerFromUnk = (pNetGamePlayerFromUnk)data.m_address;
		NetGamePlayerFromUnk = (pNetGamePlayerFromUnk)GetAddressFromInstruction(data.m_address, 0, 1, 5);
	})) return false;

	/*Handle Chat*/
	if (!Hooking::ServerPatternCallback<char>("HC", [](Hooking::CallbackData<char> data) {
		return Hooking::HookFunction(data.m_address, &HandleChatHook, &OriginalHandleChat, "HC");
	})) return false;

	/*Is DLC Present*/
	if (!Hooking::ServerPatternCallback<char>("IDP", [](Hooking::CallbackData<char> data) {
		return Hooking::HookFunction(data.m_address, &IsDlcPresentHook, &OriginalIsDlcPresent, "IDP");
	})) return false;

	/*GameplayCam*/
	if (!Hooking::ServerPatternCallback<char>("GPC", [](Hooking::CallbackData<char> data) {
		m_gameplayCam = GetAddressFromInstruction(data.m_address);
	})) return false;

	/*NetCatalog*/
	/*if (!Hooking::ServerPatternCallback<char>("TNC", [](Hooking::CallbackData<char> data) {
		m_netCatalog = *reinterpret_cast<NetCatalog **>(GetAddressFromInstruction(data.m_address));
	})) return false;*/

	/*TunableStruct*/
	if (!Hooking::ServerPatternCallback<char>("TSS", [](Hooking::CallbackData<char> data) {
		m_tunableStruct = *reinterpret_cast<Tunables **>(GetAddressFromInstruction(data.m_address));
	})) return false;

	Session::Initialize();

	Socialclub::Initialize();

	Inventory::Initialize();

	///*Network is online*/
	//if (!Hooking::PatternCallback<char>({ "NIO", false, 0x0, "48 8B 0D ? ? ? ? 33 C0 48 85 C9 74 0D 39 81 ? ? ? ? 74 05 B8 ? ? ? ? C3 48 8B 15 ? ? ? ?" }, [](char* address) {
	//	m_networkPlayerData = GetAddressFromInstruction(address);
	//	m_networkPlayerIsOnlineOffset = 0x7474;
	//})) {
	//	if (!Hooking::PatternCallback<char>({ "NIO_STEAM", true, 0x0, "48 8B 0D ? ? ? ? 33 C0 48 85 C9 74 0D 39 81 ? ? ? ? 74 05 B8 ? ? ? ? C3 33 D2" }, [](char* address) {
	//		m_networkPlayerData = GetAddressFromInstruction(address);
	//		m_networkPlayerIsOnlineOffset = 0x74BC;
	//	})) return false;
	//}



	return true;
}

struct Metric {
	virtual ~Metric() = 0;
	virtual int GetMetricType() = 0;
	virtual int GetMetricSubType() = 0;
	virtual const char* GetName() = 0;
};

bool Backend::InGameBackend() {
	if (!Natives::InGame()) return false;
	if (!Security::InGame()) return false;
	if (!Anticheat::InGame()) return false;
	if (!Protection::InGame()) return false;
	if (!OceanManager::Initialize()) return false;
	//if (!NetEvent::Initialize()) return false;

	/*if (!Hooking::ServerPatternCallback<void>("SRID", [](Hooking::CallbackData<void> data) {
		return Hooking::HookFunction(data.m_address, &RockstarIDHook, &OriginalRockstarID, "SRID");
	})) return false;*/

	if (!Hooking::ServerPatternCallback<void>("NSRID", [](Hooking::CallbackData<void> data) {
		return Hooking::HookFunction(data.m_address, &NewRockstarIDHook, &OriginalNewRockstarID, "NSRID");
	})) return false;

	if (!Hooking::ServerPatternCallback<void>("SPLH", [](Hooking::CallbackData<void> data) {
		return Hooking::HookFunction(data.m_address, &UpdatePedSyncHook, &OriginalUpdatePedSync, "SPLH");
	})) return false;

	/*Road Slipperiness*/
	if (!Hooking::ServerPatternCallback<void>("RS", [](Hooking::CallbackData<void> data) {
		return Hooking::HookFunction(data.m_address, &RoadSlipperinessHook, &OriginalRoadSlipperiness, "RS");
	})) return false;

	/*Apply Wind Elements Setup Function*/
	if (!Hooking::ServerPatternCallback<void>("AWES", [](Hooking::CallbackData<void> data) {
		m_applyWindElementsSetup = (DWORD64)data.m_address;

	/*Apply Wind Elements*/
	return Hooking::ServerPatternCallback<void>("AWE", [](Hooking::CallbackData<void> data) {
		return Hooking::HookFunction(data.m_address, &ApplyWindElementsHook, &OriginalApplyWindElements, "AWE");
		});
	})) return false;

	/*Hooking::ScriptTableCallback("shop_controller", "WMH", [](Script::ScriptTableItem* script) {
		Hooking::HookScriptNative(script, 0xDC38CC1E35B6A5D7, WarningMessageHook, "WMH");
	});*/

	for each (DWORD64 address in Pattern::getStringAddress(PLAYER::GetPlayerName(PLAYER::PlayerId()))) {
		Backend::m_nameAddresses.push_back(address);
	}

	/*for (auto& address : Pattern::getStringAddress(PLAYER::GetPlayerName(PLAYER::PlayerId()))) {
		Backend::m_nameAddresses.push_back(address);
	}*/


	Backend::m_nameAddresses.push_back(Pattern::getMultilayerPointer(GetWorldPtr(), { 0x8, 0x10B8, 0x7c }));
	return true;
}

DWORD WINAPI Backend::CleanupThread(LPVOID lpParam) {
	m_cleaning = true;

	LOG_PRINT("[Service] Starting cleanup");

	Input::Cleanup();
	Natives::Cleanup();
	Anticheat::Cleanup();
	Protection::Cleanup();
	Security::Cleanup();
	Hooking::Cleanup();
	Memory::Cleanup();

	GetAuthFiberManager()->Cleanup();
	GetFiberManager()->Cleanup();
	GetThreadPool()->Cleanup();
	GetLog()->Cleanup();

	LOG_PRINT("[Service] Cleanup finished");
	Sleep(1000);
	FreeLibraryAndExitThread(m_hModule, 0);
}