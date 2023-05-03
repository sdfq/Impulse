#pragma once

//namespace AnimatedImages {
//	extern SpriteAnimation g_hipsterHeader;
//}

class WindowManager {
private:
	bool m_menuInputDisabled;
	bool m_disableGTAInputThisFrame;
	bool m_disabledGTAInputLastFrame;
	bool m_disableMenuInputThisFrame;
	void UpdateMenuOpen();
	void UpdateMenuClosed();
	map<Hash, pair<UIWindow, UILoggerComponent*>> m_playerLog;
	vector<UILoggerComponent> m_playerLogComponents;

	UIWindow m_playerInfoWindows[MAXPLAYERS];
	UIPlayerInfoComponent m_playerInfoComponents[MAXPLAYERS];

public:
	void DisableAllInputThisFrame() { m_disableGTAInputThisFrame = true; m_disableMenuInputThisFrame = true; }
	void DisableGTAInputThisFrame() { m_disableGTAInputThisFrame = true; }
	void DisableMenuInputThisFrame() { m_disableMenuInputThisFrame = true; }
	bool IsMenuInputDisabled() { return m_menuInputDisabled; }
	bool m_firstOpen;

	String m_version;

	UIFrame m_frame;

	UIWindow m_vehicleInfo;
	UIVehicleComponent m_vehicleInfoComp;

	UIWindow m_drawableInfo;
	UILoggerComponent m_drawableLogComp;

	UIWindow m_playerInfo;
	UIPlayerInfoComponent m_playerInfoComp;

	UIWindow m_systemdata;
	UISystemdataComponent m_systemdataComp;

	UIWindow m_log;
	UIWindow m_devLog;

	UIWindow m_profiler;
	UIProfilerComponent m_profilerComp;

	UIWindow m_chat;
	UITextBoxComponent m_chatComp;

	void Init();
	void Update();
	void ASyncUpdate();
	UIFrame* GetFrame();

	void OpenPlayerLog(SPlayer& player);
	pair<UIWindow, UILoggerComponent*>* GetPlayerLog(String name);
	void OpenPlayerInfo(SPlayer& player);

	//bool isOpen() { return m_open; }
	//void close() { m_open = false; }

	void CloseAllWindows() {
		for (auto& window : GetFrame()->getWindows()) {
			if (window->canBeClosed())GetFrame()->removeWindow(window);
		}
	}

	WindowManager() : /*m_open(false),*/ m_firstOpen(true), m_menuInputDisabled(false), m_version("2.5") {}
	~WindowManager() {
		for (auto& p : m_playerLog) {
			delete p.second.second;
		}
	}
};

WindowManager* GetWindowManager();