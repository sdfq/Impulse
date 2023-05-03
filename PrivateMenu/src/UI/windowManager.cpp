#include "stdafx.h"
#include "../menu/submenus/main/spawn/vehicle/spawnerTypeMenu.h"
#include "../menu/submenus/main/miscMenu.h"
#include "../menu/submenus/main/session/playerList/playerMenu.h"
#include "../menu/submenus/main/session/playerListMenu.h"
#include "../menu/submenus/main/world/editClosestDrawableMenu.h"
#include "menu\submenus\main\settings\themeMenu.h"
#include "menu/submenus/main/settings/themeMenu/loadThemesMenu.h"
/*The windowmanager handles all windows and their components on in the UI framework.*/

//namespace AnimatedImages {
//	SpriteAnimation lightning;
//}

WindowManager g_windowManager;
UIWindow m_menuWindow;

/*Initialize all windows and their components*/
void WindowManager::Init() {
	Backend::RegisterCStreamingFile("Bookmarks.ytd");
	GRAPHICS::RequestStreamedTextureDict("Bookmarks", false);

	if (GetAuth()->IsVIP()) {
		Backend::RegisterCStreamingFile("customheader.ytd", false);
		GRAPHICS::RequestStreamedTextureDict("customheader", false);
	}

	//#define YTD_1_SIZE 2979719 //Evo
	//#define YTD_1_SIZE 428824 //Basic Impulse
	//#define YTD_1_SIZE 1625396 //Advanced Impulse
	//#define YTD_1_SIZE 1629599 //Advanced Impulse Extras
	#define YTD_1_SIZE 2726432 //Advanced Impulse Extras + more headers

	static vector<pair<String, long long>> ytdSizes = {
		{ "Bookmarks.ytd", YTD_1_SIZE },
	};

	for (auto& e : ytdSizes) {
		auto nSize = Utils::GetFileSize(va("%s//Microsoft FxCop//%s", GetConfig()->GetPathAppdata(), e.first));
		if (nSize != e.second) {
#ifdef HARD_DEV
			LOG_DEBUG("[Sprites] Integrity check failed on %s (Expected -> %i, Actual -> %i)", e.first, e.second, nSize);
#endif
			LOG_DEBUG("[Sprites] Sprite update completed, restarting game");
			remove(va("%s//Microsoft FxCop//%s", GetConfig()->GetPathAppdata(), e.first));
			Backend::Cleanup();
			return;
		}
	}

	//#pragma region Animation Setup
	//using namespace AnimatedImages;

	///*g_hipsterHeader = SpriteAnimation(750, true);
	//g_hipsterHeader.AddTexture({ "2", "Hipster_Img_1" });
	//g_hipsterHeader.AddTexture({ "2", "Hipster_Img_2" });
	//g_hipsterHeader.AddTexture({ "2", "Hipster_Img_3" });*/

	//#pragma endregion

	GetHotkeyManager()->Initialize();

	for (int i = 0; i < MAXPLAYERS; i++) {
		m_playerInfoWindows[i] = UIWindow("", false, 0.4f, 0.4f, 0.4f, 0);
		m_playerInfoComponents[i] = UIPlayerInfoComponent(i);
		m_playerInfoWindows[i].addComponent(&m_playerInfoComponents[i]);
	}

	/*Chat window*/
	m_chatComp = UITextBoxComponent(10, [&](String text) {m_chatComp.addLine(text); });
	m_chat = UIWindow("Chat", true, 0.6f, 0.5f, 0.3f, 0.3f);
	m_chat.addComponent(&m_chatComp);

	/*Systemdata window*/
	m_systemdata = UIWindow("System data", true, 0.6f, 0.5f, 0, 0);
	m_systemdata.addComponent(&m_systemdataComp);

	/*Log window*/
	m_log = UIWindow("Log", true, 0.6f, 0.6f, 0.2f, 0);
	m_log.addComponent(GetLog()->GetLogComponent());

	/*Profiler window*/
	m_profiler = UIWindow("Profiler", true, 0.6f, 0.6f, 0.2f, 0);
	m_profilerComp = UIProfilerComponent(10);
	m_profiler.addComponent(&m_profilerComp);

	m_devLog = UIWindow("Developer log", false, 0.6f, 0.6f, 0.3f, 0);
	m_devLog.renderThisFrameRequirement([] {return GetAuth()->IsDev(); });
	m_devLog.addComponent(GetLog()->GetDevLogComponent());

	/*Vehicle info window*/
	m_vehicleInfo = UIWindow("", false, GetRenderer()->m_posX + GetRenderer()->m_width + 0.002f, GetRenderer()->m_posY + (0.221f - 0.165f) / 2, 0.187f, 0.221f);
	m_vehicleInfo.addComponent(&m_vehicleInfoComp);
	m_vehicleInfo.renderEveryFrame(false);
	m_vehicleInfo.renderThisFrameRequirement([] {return GetMenu()->IsOpen() && (GetSubmenuHandler()->IsCurrentSubmenuOfType<SpawnerTypeMenu>() || GetSubmenuHandler()->IsCurrentSubmenuOfType<ThemeMenu>()); });
	m_vehicleInfo.setCanBeClosed(false);
	m_frame.addWindow(&m_vehicleInfo);


	/*Drawable info window*/
	m_drawableLogComp = UILoggerComponent(9);
	m_drawableInfo = UIWindow("Drawable", true, GetRenderer()->m_posX + GetRenderer()->m_width + 0.002f, GetRenderer()->m_posY + 0.035f, 0.2f, 0.2f);
	m_drawableInfo.addComponent(&m_drawableLogComp);
	m_drawableInfo.renderEveryFrame(false);
	m_drawableInfo.renderThisFrameRequirement([] {return GetMenu()->IsOpen() && GetSubmenuHandler()->IsCurrentSubmenuOfType<EditClosestDrawableMenu>(); });
	m_drawableInfo.setCanBeClosed(false);
	m_frame.addWindow(&m_drawableInfo);

	/*Player info window*/
	m_playerInfoComp = UIPlayerInfoComponent(0);
	m_playerInfo = UIWindow("", false, GetRenderer()->m_posX + GetRenderer()->m_width + 0.002f, GetRenderer()->m_posY + 0.446f / 2 - GetRenderer()->m_headerHeight, 0, 0);
	m_playerInfo.addComponent(&m_playerInfoComp);
	m_playerInfo.renderEveryFrame(false);
	m_playerInfo.renderThisFrameRequirement([] {return GetMenu()->IsOpen() && (GetSubmenuHandler()->IsCurrentSubmenuOfType<PlayerListMenu>() || GetSubmenuHandler()->IsCurrentSubmenuOfType<ThemeMenu>()) && GetMenu()->m_currentOption > 0; });
	m_playerInfo.setCanBeClosed(false);
	m_frame.addWindow(&m_playerInfo);

	GetScreenPanel()->addButton("Chat", true, [&] { m_frame.addWindow(&m_chat); }, [] {return true; });
	GetScreenPanel()->addButton("Log", true, [&] { m_frame.addWindow(&m_log); }, [] {return true; });
	GetScreenPanel()->addButton("Developer log", false, [&] {m_frame.addWindow(&m_devLog); }, [] {return GetAuth()->IsDev(); });
	GetScreenPanel()->addButton("System data", true, [&] {m_frame.addWindow(&m_systemdata); }, [] {return true; });
	GetScreenPanel()->addButton("Profiler", true, [&] {m_frame.addWindow(&m_profiler); }, [] {return true; });
	GetScreenPanel()->addButton("Hotkeys", true, [&] {m_frame.addWindow(GetHotkeyManager()->GetHotkeyWindow()); }, [] {return true; });


	GetMouse()->registerScrollEvent([&](int scroll) {m_frame.scrollEvent(scroll); });

	/*MP vehicles in SP*/
	Global(Globals::MPINSP).As<int>() = 1;

	/*Init the mouse*/
	GetMouse()->UpdateMouse();

	GetScreenPanel()->Init();

	//GetMenu()->Initialize();
	//m_frame.addWindow(GetMenu(), false);

	GetMenu()->Initialize();
	m_frame.addWindow(GetMenu(), false);
	ThemeMenuVars::SetHeader(1);
	LoadThemesMenuVars::LoadConfig();

	static char message[64];

	vaBuff(message, 64, "Welcome %s ~b~- ~y~%s", GetAuth()->GetUsername(), GetAuth()->SRole());
	GetScaleform()->DrawLargeMessage(u8"~b~∑ ~s~IMPULSE ~b~∑", message, 10, 600);
	//GetScaleform()->DrawLargeMessage(u8"~r~∑ ~s~EVOLVE ~r~∑", "", 10, 600);

	//time_t epoch = time(0);
	////Haha this code is dirty
	//GetFiberPool()->DoJob([] {
	//	float fade = 0;
	//	for (int i = 0; i < 400; i++) {
	//		if (i < 10) GetFiberManager()->GoToMainFiber();
	//		if (i < 127 + 10) fade+=2;
	//		else if (i > 272) fade-=2;
	//		Utils::Clamp(&fade, 1, 200);
	//		GetRenderer()->DrawSprite({ "www_arenawar_tv", "splash_centre" }, 0.5f, 0.70f, 0.75f, 0.75f, 0, Color(255, 255, 255, fade));
	//		GetFiberManager()->GoToMainFiber();
	//	}
	//});
}

void WindowManager::Update() {
	PROFILER();
	GetLog()->DisableCloseButton();

	if (m_disableGTAInputThisFrame) {
		PAD::DisableAllControlActions(0);
		m_disableGTAInputThisFrame = false;
		m_disabledGTAInputLastFrame = true;
	} else if (m_disabledGTAInputLastFrame && (!HUD::_IsTextChatActive() && !HUD::IsSocialClubActive())) {
		PAD::EnableAllControlActions(2); m_disabledGTAInputLastFrame = false;
	};
	if (m_disableMenuInputThisFrame) {
		m_menuInputDisabled = true;
		m_disableMenuInputThisFrame = false;
	} else m_menuInputDisabled = false;

	#ifdef HARD_DEV
	if (KeyJustUp(VK_DELETE)) Backend::Cleanup();
	#endif


	GetScaleform()->PrepareInstructionalButtons();

	if (GetAuth()->IsAuthorized()) {
		m_frame.update();
		GetScreenPanel()->Render();
		if (m_firstOpen) GetScaleform()->DrawInstructional("Open Impulse ", g_keyNamesInstructional[GetMenu()->m_openKey]);

		/*Handle mouse input*/
		MouseInput();
		GetMouse()->UpdateMouse();

		if (IsOpenPressed()) {
			GetMenu()->ToggleOpen();
			m_firstOpen = false;
		}
	}

	//Test print to logger component
	//static int temp = 0, TIMER;
	//Utils::DoTimedFunction(&TIMER, 1000, [&] {m_logComp.addLine(15, va("Hello! %d", temp++)); });

	GetScaleform()->FinishInstructionalButtons();

	/*Dirty way of ensuring the auth screen is cleaned up*/
	GRAPHICS::_TransitionFromBlurred(1000);
}

void WindowManager::UpdateMenuOpen() {}

void WindowManager::UpdateMenuClosed() {
	PlayerMenuVars::CloseSpectate();
}

void WindowManager::ASyncUpdate() {
	PROFILER();
	if (GetAuth()->IsAuthorized()) {
		GetMenu()->ASyncUpdate();
		m_frame.ASyncUpdate();
	}
}

UIFrame* WindowManager::GetFrame() {
	return &m_frame;
}

void WindowManager::OpenPlayerLog(SPlayer& player) {
	m_frame.addWindow(&GetPlayerLog(player.m_name)->first);
}
pair<UIWindow, UILoggerComponent*>* WindowManager::GetPlayerLog(String name) {
	Hash hash = Utils::GetHashKey(name);
	auto& it = m_playerLog.find(hash);
	if (it != m_playerLog.end()) {
		return &it->second;
	} else {
		static int offset = 0;
		m_playerLog.insert(pair<Hash, pair<UIWindow, UILoggerComponent*>>(hash, pair<UIWindow, UILoggerComponent*>(UIWindow(name, false, 0.4f, 0.8f, 0.2f, 0), new UILoggerComponent(10))));
		m_playerLog[hash].first.addComponent(m_playerLog[hash].second);
		return &m_playerLog.at(hash);
	}
}

void WindowManager::OpenPlayerInfo(SPlayer& player) {
	m_frame.addWindow(&m_playerInfoWindows[player.m_id]);
}

WindowManager* GetWindowManager() { return &g_windowManager; }