#include "stdafx.h"

HotkeyManager g_hotkeyManager;

static UIWindow m_hotkeys;
static UILoggerComponent m_hotkeysComp;

void HotkeyManager::Initialize() {
	m_hotkeys = UIWindow("Hotkeys", true, 0.4f, 0.2f, 0.2f, 0.2f);
	m_hotkeysComp = UILoggerComponent(10);
	m_hotkeysComp.clear();
	m_hotkeysComp.setUpdateCallback([&] {
		static int TIMER;
		Utils::DoTimedFunction(&TIMER, 100, [&] {
			m_hotkeysComp.clear();
			for (auto& hk : m_registeredHotkeys) {
				m_hotkeysComp.addLine(va("%s - ~c~[~s~%s~c~]", g_keyNames[hk.m_key], hk.m_option->getName().GetOriginal()));
			}
		});
	});
	m_hotkeys.addComponent(&m_hotkeysComp);
}

UIWindow* HotkeyManager::GetHotkeyWindow() {
	return &m_hotkeys;
}

void HotkeyManager::InitHotkey(Option* option) {
	String result = GetConfig()->ReadString("Hotkeys", option->getName().GetOriginal(), "null");
	if (strcmp(result, "null") != 0) {
		int key = stoi(result);
		option->m_hotkey = key;
		m_registeredHotkeys.push_back({ key, option });
	}
}

void HotkeyManager::RegisterHotkey(int key, Option* option) {
	m_registeredHotkeys.push_back({ key, option });
	SaveToConfig(option->getName().GetOriginal(), key);
}

void HotkeyManager::UnregisterHotkey(int key) {
	for (auto& hotkey : m_registeredHotkeys) {
		if (hotkey.m_key == key) {
			hotkey.m_option->m_hotkey = -1;
			m_registeredHotkeys.erase(remove(m_registeredHotkeys.begin(), m_registeredHotkeys.end(), hotkey), m_registeredHotkeys.end());
			GetConfig()->RemoveString("Hotkeys", hotkey.m_option->getName().GetOriginal());
		}
	}
}
Option* HotkeyManager::IsHotkeyInUse(int key) {
	for (auto& hotkey : m_registeredHotkeys) {
		if (hotkey.m_key == key) return hotkey.m_option;
	}
	return nullptr;
}
void HotkeyManager::Update() {
	PROFILER();
	if (GetWindowManager()->IsMenuInputDisabled() || HUD::_IsTextChatActive() || HUD::IsSocialClubActive())return;
	int lastKey = GetKeyboard()->GetLastKey();
	if (KeyJustUp(lastKey)) {
		for (auto& hotkey : m_registeredHotkeys) {
			if (hotkey.m_key == lastKey) {
				hotkey.m_option->HandleHotkey();
			}
		}
	}
}

void HotkeyManager::SaveToConfig(String name, int key) {
	GetConfig()->WriteInt("Hotkeys", name, key);
}

HotkeyManager* GetHotkeyManager() { return &g_hotkeyManager; }