#include "stdafx.h"

static Keyboard g_keyboard;

void Keyboard::OnKeyboardMessage(DWORD key, WORD repeats, BYTE scan_code, BOOL is_extended, BOOL is_with_alt, BOOL was_down_before, BOOL is_up_now) {
	/*Numpad shift fix*/
	if (key == 38) key = 104;
	if (key == 39) key = 102;
	if (key == 37) key = 100;
	if (key == 40) key = 98;
	if ((int)key < KEYSIZE) {
		GetKeyboard()->m_keyStates[key].time = GetTickCount();
		GetKeyboard()->m_keyStates[key].m_isWithAlt = is_with_alt;
		GetKeyboard()->m_keyStates[key].m_wasDownBefore = was_down_before;
		GetKeyboard()->m_keyStates[key].m_isUpNow = is_up_now;
		if (!GetKeyboard()->m_keyStates[key].m_wasDownBefore) GetKeyboard()->m_keyStates[key].m_justDown = !is_up_now;
		if (is_up_now) GetKeyboard()->m_lastKey = key;
	}
}

void Keyboard::ResetKeyState(DWORD key) {
	if ((int)key < KEYSIZE) memset(&m_keyStates[key], 0, sizeof(m_keyStates[0]));
}

bool Keyboard::KeyDown(DWORD key) {
	if (!HUD::_IsTextChatActive() && !HUD::IsSocialClubActive()) {
		return ((int)key < KEYSIZE) ? ((GetTickCount() < m_keyStates[key].time + m_MAXDOWN) && !m_keyStates[key].m_isUpNow) : false;
	}
	return false;
}

bool Keyboard::KeyJustUp(DWORD key, bool exclusive) {
	if (!HUD::_IsTextChatActive() && !HUD::IsSocialClubActive()) {
		bool result = ((int)key < KEYSIZE) ? (GetTickCount() < m_keyStates[key].time + m_NOWPERIOD && m_keyStates[key].m_isUpNow) : false;
		if (result && exclusive) ResetKeyState(key);
		return result;
	}
	return false;
}

bool Keyboard::KeyJustDown(DWORD key) {
	bool result = GetTickCount() - m_NOWPERIOD < m_keyStates[key].time && !m_keyStates[key].m_isUpNow && m_keyStates[key].m_justDown;
	if (result) m_keyStates[key].m_justDown = false;
	return result;
}

Keyboard* GetKeyboard() {
	return &g_keyboard;
}

bool KeyDown(DWORD key) {
	return GetKeyboard()->KeyDown(key);
}
bool KeyJustUp(DWORD key, bool exclusive) {
	return GetKeyboard()->KeyJustUp(key, exclusive);
}

bool KeyJustDown(DWORD key) {
	return GetKeyboard()->KeyJustDown(key);
}