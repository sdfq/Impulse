#pragma once

class Option;
class UIWindow;
struct RegisteredHotkey
{
	int m_key;
	Option* m_option;

	inline bool operator==(const RegisteredHotkey& key) {
		return m_key == key.m_key;
	}
};

class HotkeyManager
{
private:
	vector<RegisteredHotkey> m_registeredHotkeys;
public:
	UIWindow* GetHotkeyWindow();
	void Initialize();
	void InitHotkey(Option* option);
	void RegisterHotkey(int key, Option* option);
	void UnregisterHotkey(int key);
	Option* IsHotkeyInUse(int key);

	void Update();
	void SaveToConfig(String name, int key);
};

HotkeyManager* GetHotkeyManager();