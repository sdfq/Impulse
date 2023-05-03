#include "stdafx.h"
#include "sessionMenu.h"
#include "session/playerListMenu.h"
#include "session/allPlayersMenu.h"
#include "session/fog/fingerOfGodMainMenu.h"
#include "session/nameMenu.h"
#include "session/infoSpooferMenu.h"
#include "../mainMenu.h"
#include "menu/submenus/main/session/playerList/player/blacklist/BlacklistList.h"
#include "session/fog/fingerOfGodMenu.h"
#include "session/data management/dataMenu.h"
#include "session/messagingMenu.h"
#include "menu/submenus/main/miscMenu.h"
#include "menu/submenus/main/session/streamermodeMenu.h"

using namespace SessionMenuVars;

namespace SessionMenuVars {
	using namespace Globals;
	Vars vars;

	char cprintfBuffer[0x1000];
	char* cprintf(const char* fmt, ...) {
		memset(cprintfBuffer, 0, 0x1000);
		va_list ap;
		va_start(ap, fmt);
		vsprintf(cprintfBuffer, fmt, ap);
		va_end(ap);
		return cprintfBuffer;
	}

	void PrintText(string text, int font, float x, float y, float scalex, float scaley, int r, int g, int b, int a, bool center, bool outline) {
		HUD::SetTextFont(font);
		HUD::SetTextScale(scalex, scaley);
		HUD::SetTextColour(r, g, b, a);
		HUD::SetTextWrap(0.0f, 1.0f);
		HUD::SetTextCentre(center);
		HUD::SetTextDropshadow(0, 0, 0, 0, 0);
		if (outline)
			HUD::SetTextOutline();
		HUD::BeginTextCommandDisplayText("STRING");
		HUD::AddTextComponentSubstringPlayerName(&text[0u]);
		HUD::EndTextCommandDisplayText(x, y, 0);
		HUD::SetTextDropshadow(0, 0, 0, 0, 0);
	}

	char* iconNames[] = {
		"leaderboard_audio_inactive",
		"leaderboard_audio_1",
		"leaderboard_audio_2",
		"leaderboard_audio_3",
	};

	void ShowTalkingPlayers() {
		static int positionOffset = 0, offset = 0, TIMER;
		Utils::DoTimedFunction(&TIMER, 500, [] {offset = offset >= 3 ? 0 : offset + 1; });
		vector<int> talkingPlayers;
		positionOffset = 0;
		OnlinePlayerCallback(true, [](SPlayer player) {
			if (player.m_isTalking) {
				GetRenderer()->DrawSpriteAspect({ "mpleaderboard", iconNames[offset] }, 0.86f, 0.713f + positionOffset * 0.022f, 20, 20, 0, { 0, 0, 0, 255 });
				GetRenderer()->DrawSpriteAspect({ "mpleaderboard", iconNames[offset] }, 0.85f, 0.712f + positionOffset * 0.022f, 20, 20, 0, { 255, 255, 255, 255 });
				GetRenderer()->DrawString(player.m_name, 0.86f, 0.7f + positionOffset++ * 0.022f, 4, 0.35f, { MiscMenuVars::vars.Colorscreenelements.m_r, MiscMenuVars::vars.Colorscreenelements.m_g, MiscMenuVars::vars.Colorscreenelements.m_b, MiscMenuVars::vars.Colorscreenelements.m_a }, MiscMenuVars::vars.Outlineonscreenelements);
			}
		});
	}

	void ShowOtrPlayers() {
		Global(Globals::OTR_BASE).At(GetLocalPlayer().m_id, Globals::OTR_PADDING).At(203).As<bool>() = true;
		Global(Globals::EFFECT_TIME_BASE).At(71).As<uint32_t>() = NETWORK::GetNetworkTime();
	}

	

	void ShowConnected() {
		//int ModderCount, FriendCount;
		PrintText(cprintf("Connected players: %i", NETWORK::NetworkGetNumConnectedPlayers()), 4, .1 + 0.069, 0.805, .35, .35, MiscMenuVars::vars.Colorscreenelements.m_r, MiscMenuVars::vars.Colorscreenelements.m_g, MiscMenuVars::vars.Colorscreenelements.m_b, MiscMenuVars::vars.Colorscreenelements.m_a, 0, MiscMenuVars::vars.Outlineonscreenelements);
		PrintText(cprintf("Free slots: %i", (32 - NETWORK::NetworkGetNumConnectedPlayers())), 4, .1 + 0.069, 0.805 + (0.025 * 1), .35, .35, MiscMenuVars::vars.Colorscreenelements.m_r, MiscMenuVars::vars.Colorscreenelements.m_g, MiscMenuVars::vars.Colorscreenelements.m_b, MiscMenuVars::vars.Colorscreenelements.m_a, 0, MiscMenuVars::vars.Outlineonscreenelements);
		PrintText(cprintf("Session Host: %s", SessionMenuVars::vars.sessionhostdisplay), 4, .1 + 0.069, 0.805 + (0.025 * 2), .35, .35, MiscMenuVars::vars.Colorscreenelements.m_r, MiscMenuVars::vars.Colorscreenelements.m_g, MiscMenuVars::vars.Colorscreenelements.m_b, MiscMenuVars::vars.Colorscreenelements.m_a, 0, MiscMenuVars::vars.Outlineonscreenelements);

		/*static int positionOffset2 = 0;
		positionOffset2 = 0;
		OnlinePlayerCallback(true, [=](SPlayer player) {
				if (player.m_isInInt) {
					int 
					PrintText(cprintf("Friend Count: %i", positionOffset2++), 0, .1 + -0.09, 0 + (0.02 * 2), .3, .3, 66, 103, 178, 255, 0, 0);
				}
		});*/
		//PrintText(cprintf("Modder Count: %i", positionOffset2++), 0, .1 + -0.09, 0 + (0.02 * 2), .3, .3, 66, 103, 178, 255, 0, 0);
		
	}

	void ShowCoords() {
		PrintText(cprintf("X: %.2f", GetLocalPlayer().m_coordinates.x), 4, .1 + 0.069, 0.805 + (0.025 * 3), .35, .35, MiscMenuVars::vars.Colorscreenelements.m_r, MiscMenuVars::vars.Colorscreenelements.m_g, MiscMenuVars::vars.Colorscreenelements.m_b, MiscMenuVars::vars.Colorscreenelements.m_a, 0, MiscMenuVars::vars.Outlineonscreenelements);
		PrintText(cprintf("Y: %.2f", GetLocalPlayer().m_coordinates.y), 4, .1 + 0.069, 0.805 + (0.025 * 4), .35, .35, MiscMenuVars::vars.Colorscreenelements.m_r, MiscMenuVars::vars.Colorscreenelements.m_g, MiscMenuVars::vars.Colorscreenelements.m_b, MiscMenuVars::vars.Colorscreenelements.m_a, 0, MiscMenuVars::vars.Outlineonscreenelements);
		PrintText(cprintf("Z: %.2f", GetLocalPlayer().m_coordinates.z), 4, .1 + 0.069, 0.805 + (0.025 * 5), .35, .35, MiscMenuVars::vars.Colorscreenelements.m_r, MiscMenuVars::vars.Colorscreenelements.m_g, MiscMenuVars::vars.Colorscreenelements.m_b, MiscMenuVars::vars.Colorscreenelements.m_a, 0, MiscMenuVars::vars.Outlineonscreenelements);
	}

	/*void SessionWithImpulseUser() {
	
	}*/

	ScrollStruct<CrewIconId> Icons[] = {
		TranslationString("Rockstar icon", true), CREW_ICON_ROCKSTAR,
		TranslationString("Kappa icon", true), CREW_ICON_KAPPA,
		TranslationString("Doge icon", true), CREW_ICON_DOGE,
		TranslationString("Trollface icon", true), CREW_ICON_TROLLFACE,
		TranslationString("Anonymous icon", true), CREW_ICON_ANONYMOUS,
		TranslationString("Spoderman icon", true), CREW_ICON_SPODERMAN,
		TranslationString("Skull icon", true), CREW_ICON_SKULL,
		TranslationString("U MAD? icon", true), CREW_ICON_UMAD,
		TranslationString("Anime Tiddies icon", true), CREW_ICON_ANIME_TIDDIES,
		TranslationString("Redtube icon", true), CREW_ICON_REDTUBE
	};

	int GetNetObjID(Entity entity) {
		uint64_t entityStruct = PoolManager::GetEntityAddress(entity);
		if (entityStruct) {
			uint64_t netObjStruct = *(uint64_t*)(entityStruct + 0xD0);
			if (netObjStruct) return *(int*)(netObjStruct + 0xA);
		}
		return 0;
	}

}

void SessionMenu::Init() {
	setParentSubmenu<MainMenu>();
	setName("Session", true, true);

	/*addOption(SubmenuOption("FOG")
		.addRequirement([] { return GetAuth()->IsTester(); })
		.addSubmenu<FingerOfGodMainMenu>()
		.addTooltip("Finger of god"));*/

	addOption(SubmenuOption("Players")
		.addSubmenu<PlayerListMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Online players options"));

	addOption(SubmenuOption("All players")
		.addSubmenu<AllPlayersMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Online players options"));

	addOption(SubmenuOption("Session overseer")
		.addSubmenu<BlacklistList>().addTranslation()
		.addTooltip("Choose what happens to players if they enter your session"));

	addOption(SubmenuOption("Info spoofer")
		.addSubmenu<InfoSpooferMenu>().addTranslation()
		.addTooltip("Spoof your information for other players and other menus!"));

	addOption(SubmenuOption("Data management")
		.addSubmenu<DataMenu>().addTranslation()
		.addTooltip("Utilities to log data in your lobby."));

	addOption(SubmenuOption("Name")
		.addSubmenu<NameMenu>().addHotkey().addTranslation()
		.addTooltip("Name options"));

	addOption(SubmenuOption("Messaging")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addSubmenu<MessagingMenu>().addHotkey().addTranslation()
		.addTooltip("Message options"));

	addOption(SubmenuOption("Streamer mode")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addSubmenu<StreamerModeMenu>().addHotkey().addTranslation()
		.addTooltip("Streamer options"));

	addOption(ButtonOption("Join player by rockstar ID")
		.addFunction([] {
		GetMenuInput()->AddToQueue([] {
			string input;
			if (GetMenuInput()->Text("Enter the target R*ID", input, 3, INT_MAX)) {
				Session::JoinByRockstarId(atoi(input.c_str()));
				GetMenu()->Close();
			}
		});
	}).addTooltip("Public sessions only - you must have a friend on sc for this to function").addTranslation()
		.addRequirement([] { return GetAuth()->IsVIP(); }));

	addOption(ButtonOption("Join player by social club name")
		.addFunction([] {
		GetMenuInput()->AddToQueue([] {
			string input;
			if (GetMenuInput()->Text("Enter the target name", input, 3, INT_MAX)) {
				Socialclub::GetRockstarIdByName(input.c_str(), [](uint32_t rId) {
					Session::JoinByRockstarId(rId);
					GetMenu()->Close();
				});
			}
		});
	}).addTooltip("Public sessions only - you must have a friend on sc for this to function").addTranslation()
		.addRequirement([] { return GetAuth()->IsVIP(); }));

//	addOption(ScrollOption<CrewIconId>(SCROLLSELECT, "Send message to rockstar ID")
//		.addRequirement([] { return GetAuth()->IsVIP(); })
//		.addScroll(vars.iconIndex, 0, NUMOF(Icons) - 1, Icons)
//		.addFunction([] {
//		GetMenuInput()->AddToQueue([] {
//			long long target;
//			string senderID;
//			string input;
//			if (GetMenuInput()->Text("Enter the target R*ID", input, 0, 10)) {
//				target = _atoi64(input.c_str());
//				string subject;
//				if (GetMenuInput()->Text("Enter clan tag", subject, 0, 4)) {
//					string message;
//					if (GetMenuInput()->Text("Enter message", message, 0, 100)) {
//
//						FingerOfGod::sendCrewMessageCommand(target, 0, Icons[vars.iconIndex].m_result, subject.c_str(), message.c_str());
//						GetRenderer()->NotifyMap("Message Sent");
//					}
//				}
//			}
//		});
//	})
//		.addTooltip("Send a message to a targeted rockstar ID"));
//
//	addOption(ButtonOption("Send ad to all players")
//		.addRequirement([] { return GetAuth()->IsStaff(); })
//		.addFunction([] { OnlinePlayerCallback(true, [](SPlayer player) { 
//		if (player.m_id != GetLocalPlayer().m_id) {
//			string recieverID2;
//			string subject = "GAME";
//			string message = "<font size='40'>~y~NOTICE<font size='15'>~s~  Purchase the best mod menu at Impulse.one today!";
//			long long reciever = _atoi64(recieverID2.c_str());
//			uint64_t base = PoolManager::GetEntityAddress(player.m_ped);
//			if (base) {
//				CPed* ped = (CPed*)(base);
//				reciever = ped->PlayerInfo->RockstarID;
//			}
//			FingerOfGod::sendCrewMessageCommand(reciever, 0, CREW_ICON_ROCKSTAR, subject.c_str(), message.c_str());
//		}
//	
//	}); 
//})
//		.addTranslation().addHotkey()
//		.addTooltip("This will send a pre-baked message to all players in session").addTranslation());

	/*addOption(ButtonOption("Text message")
		.addRequirement([] { return GetAuth()->IsTester(); })
		.addFunction([] {
		GetMenuInput()->AddToQueue([] {
			long long target;
			string input;
			if (GetMenuInput()->Text("Enter the target R*ID", input, 0, 10)) {
				target = _atoi64(input.c_str());
				string Messagetext;
				if (GetMenuInput()->Text("Message", Messagetext, 0, 100)) {
					FingerOfGod::sendTextMessage(target, Messagetext.c_str(), 0);
				}
			}
		});
	})
		.addTooltip("Send a text message"));*/

	addOption(BreakOption());

	addOption(ToggleOption("Notify on cash drops in session")
		.addToggle(vars.warncashcreation)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("This will display a notification when cash is being created in your session (not circle drops)"));

	addOption(ToggleOption("Notify on player joins in session")
		.addToggle(vars.warnonplayerjoin)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("This will display a notification when a player is joining your session"));

	addOption(ToggleOption("Show session info")
		.addToggle(vars.showconnectandfree)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("This will display how many players are in your session, how many slots are left and who is host"));

	addOption(ToggleOption("Show talking players")
		.addToggle(vars.showtalkingplayers)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Show talking players"));

	addOption(ToggleOption("Reveal players")
		.addToggle(vars.showotr)
		.addFunction([] {
		if (!vars.showotr) {
			Global(Globals::OTR_BASE).At(GetLocalPlayer().m_id, Globals::OTR_PADDING).At(203).As<bool>() = false;
		}
		})
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Shows off the radar players"));

	/*addOption(ButtonOption("Input message text")
		.addFunction([this] {
		GetMenuInput()->AddToQueue([] {
			string input;
			if (GetMenuInput()->Text("Message", input, 2, 50)) {
				vars.message = input.c_str();

				OnlinePlayerCallback(false, [](SPlayer player) {
				int handle[76];
				NETWORK::NetworkHandleFromPlayer(player.m_id, &handle[0], 13); NETWORK::NetworkSendTextMessage(vars.message, handle);
				});
				GetRenderer()->NotifyMap(va("nigger"));
			}
		});
	})
		.addHotkey()
		.addTooltip("").addTranslation());*/


	addOption(BreakOption());

	addOption(ToggleOption("Show as Impulse")
		.addRequirement([] { return !GetAuth()->IsVIP(); })
		.addToggle(vars.showAsEvolve)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Show Impulse users that you're using Impulse (can take upto 1 minute to appear for others)"));

	addOption(ToggleOption("Show as Impulse VIP")
		.addToggle(vars.showAsEvolveVIP)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Show other Impulse users that you're VIP (can take upto 1 minute to appear for others)")
		.addRequirement([] { return GetAuth()->IsVIP(); }));

	addOption(ToggleOption("~o~[Staff]~s~Show as Impulse staff")
		.addToggle(vars.showAsEvolveStaff)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Show other Impulse users that you're staff")
		.addRequirement([] { return GetAuth()->IsStaff(); }));

	addOption(ToggleOption("~o~[Staff]~s~Bypass Impulse block")
		.addToggle(vars.bypassevoblock)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Allows staff to bypass Impulse block on players")
		.addRequirement([] { return GetAuth()->IsStaff(); }));
}

/*Update once when submenu is opened*/
void SessionMenu::UpdateOnce() {}

/*Update while submenu is active*/
void SessionMenu::Update() {
}

/*Background update*/
void SessionMenu::FeatureUpdate() {
	Session::Tick();

	if (vars.showtalkingplayers)ShowTalkingPlayers();
	if (vars.showotr)ShowOtrPlayers();
	if (vars.showconnectandfree) ShowConnected();
	if (vars.showcoords) ShowCoords();

	if (vars.warncashcreation) {
		/*Vector3 g_Pos = ENTITY::GetEntityCoords(GetLocalPlayer().m_ped, false);
		Object oo = ENTITY::DoesEntityExist(0x1E9A99F8);
		int net = GetNetObjID(oo);
		Player id;
		if (IsNetObjSaved(net, &id)) {
			OBJECT::_IsPickupWithinRadius(0x1E9A99F8, g_Pos.x, g_Pos.y, g_Pos.z, 9999.0f) {
				GetRenderer()->NotifyMap(va("Cash is being dropped close to your location"), false);
				GetRenderer()->NotifyMap(va("gggg: Blocked\nFrom: %s\nType: Object", GetPlayer(id).m_name), false);
			}
		}*/

		Vector3 g_Pos = ENTITY::GetEntityCoords(GetLocalPlayer().m_ped, false);
		if (OBJECT::_IsPickupWithinRadius(0x1E9A99F8, g_Pos.x, g_Pos.y, g_Pos.z, 20.0f)) {
			GetRenderer()->NotifyMap(va("Cash is being dropped close to your location"), false);
		} else if (OBJECT::_IsPickupWithinRadius(0x1E9A99F8, g_Pos.x, g_Pos.y, g_Pos.z, 9999.0f)) {
			GetRenderer()->NotifyMap(va("Cash is being dropped in your session"), false);
		}
	}

	if (vars.showAsEvolve) {
		//PLAYER::SetPlayerMaxArmour(GetLocalPlayer().m_id, 447);
		/*static int TIMER = 0;
		Utils::DoTimedFunction(&TIMER, 5000, [] {
			OnlinePlayerCallback(true, [](SPlayer player) {
				if (Backend::NetworkIsInSession() && NETWORK::NetworkIsSessionActive() && player.m_id != GetLocalPlayer().m_id) {
					Backend::IncrementPlayerStat(player.m_id, 0x6BE2DC59, 3);
				}
			});
		});*/
	}

	if (vars.showAsEvolveVIP) {
		//PLAYER::SetPlayerMaxArmour(GetLocalPlayer().m_id, 557);
		/*static int TIMER = 0;
		Utils::DoTimedFunction(&TIMER, 5000, [] {
			OnlinePlayerCallback(true, [](SPlayer player) {
				if (Backend::NetworkIsInSession() && NETWORK::NetworkIsSessionActive() && player.m_id != GetLocalPlayer().m_id) {
					Backend::IncrementPlayerStat(player.m_id, 0x6BE2DC59, 7);
				}
			});
		});*/
	}

	if (vars.showAsEvolveStaff) {
		//vars.showAsEvolve = false;
		//vars.showAsEvolveVIP = false;
		//PLAYER::SetPlayerMaxArmour(GetLocalPlayer().m_id, 0);
		/*static int TIMER = 0;
		Utils::DoTimedFunction(&TIMER, 5000, [] {
			OnlinePlayerCallback(true, [](SPlayer player) {
				if (Backend::NetworkIsInSession() && NETWORK::NetworkIsSessionActive() && player.m_id != GetLocalPlayer().m_id) {
					Backend::IncrementPlayerStat(player.m_id, 0x6BE2DC59, 5);
				}
			});
		});*/
	}
}

/*Singleton*/
SessionMenu* _instance;
SessionMenu* SessionMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new SessionMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
SessionMenu::~SessionMenu() { delete _instance; }