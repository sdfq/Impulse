#pragma once
#include "menu\submenus\main\settingsMenu.h"
#include "menu\submenus\main\miscMenu.h"

static bool IsOpenPressed() {
	if (GetWindowManager()->IsMenuInputDisabled()) return false;
	// Open menu - RB + LB / open key + for some reason Q and E?
	//return ((PAD::IsDisabledControlPressed(2, INPUT_FRONTEND_RB) && PAD::IsDisabledControlPressed(2, INPUT_FRONTEND_LEFT)) || KeyJustUp(GetMenu()->m_openKey));
	return ((PAD::IsDisabledControlPressed(2, SettingsMenuVars::vars.openkeynew) && PAD::IsDisabledControlPressed(2, SettingsMenuVars::vars.openkeynew2)) || KeyJustUp(GetMenu()->m_openKey));
}
static bool IsAJPressed(bool overrideInput = false) {
	if (!overrideInput && GetWindowManager()->IsMenuInputDisabled()) return false;

	if (SettingsMenuVars::vars.disablecontrollerinput) {
		return KeyJustDown(VK_NUMPAD5);
	} else
	return PAD::IsDisabledControlJustReleased(2, INPUT_FRONTEND_ACCEPT) || KeyJustDown(VK_NUMPAD5);
}
static bool IsBJPressed(bool overrideInput = false) {
	if (!overrideInput && GetWindowManager()->IsMenuInputDisabled()) return false;

	if (SettingsMenuVars::vars.disablecontrollerinput) {
		return KeyJustDown(VK_NUMPAD0) || (GetMouse()->CanUse() && GetMouse()->ButtonJustUp(VK_MOUSE_RIGHT));
	} else
	return PAD::IsDisabledControlJustReleased(2, INPUT_FRONTEND_CANCEL) || KeyJustDown(VK_NUMPAD0) || (GetMouse()->CanUse() && GetMouse()->ButtonJustUp(VK_MOUSE_RIGHT));
}
static bool IsRPressed(bool overrideInput = false) {
	if (!overrideInput && GetWindowManager()->IsMenuInputDisabled()) return false;

	if (SettingsMenuVars::vars.disablecontrollerinput) {
		if (KeyDown(VK_NUMPAD6)) return true; else return false;
	} else
	if (PAD::IsDisabledControlPressed(2, INPUT_FRONTEND_RIGHT) || KeyDown(VK_NUMPAD6)) return true; else return false;
}
static bool IsRJPressed(bool overrideInput = false) {
	if (!overrideInput && GetWindowManager()->IsMenuInputDisabled()) return false;

	if (SettingsMenuVars::vars.disablecontrollerinput) {
		if (KeyJustUp(VK_NUMPAD6)) return true; else return false;
	} else
	if (PAD::IsDisabledControlJustReleased(2, INPUT_FRONTEND_RIGHT) || KeyJustUp(VK_NUMPAD6)) return true; else return false;
}
static bool IsLPressed(bool overrideInput = false) {
	if (!overrideInput && GetWindowManager()->IsMenuInputDisabled()) return false;

	if (SettingsMenuVars::vars.disablecontrollerinput) {
		if (KeyDown(VK_NUMPAD4)) return true; else return false;
	} else
	if (PAD::IsDisabledControlPressed(2, INPUT_FRONTEND_LEFT) || KeyDown(VK_NUMPAD4)) return true; else return false;
}
static bool IsLJPressed(bool overrideInput = false) {
	if (!overrideInput && GetWindowManager()->IsMenuInputDisabled()) return false;

	if (SettingsMenuVars::vars.disablecontrollerinput) {
		if (KeyJustUp(VK_NUMPAD4)) return true; else return false;
	} else
	if (PAD::IsDisabledControlJustReleased(2, INPUT_FRONTEND_LEFT) || KeyJustUp(VK_NUMPAD4)) return true; else return false;
}
static bool IsUPressed(bool overrideInput = false) {
	if (!overrideInput && GetWindowManager()->IsMenuInputDisabled()) return false;

	if (SettingsMenuVars::vars.disablecontrollerinput) {
		if (KeyDown(VK_NUMPAD8)) return true; else return false;
	} else
	if (PAD::IsDisabledControlPressed(2, INPUT_FRONTEND_UP) || KeyDown(VK_NUMPAD8)) return true; else return false;
}
static bool IsUJPressed(bool overrideInput = false) {
	if (!overrideInput && GetWindowManager()->IsMenuInputDisabled()) return false;

	if (SettingsMenuVars::vars.disablecontrollerinput) {
		if (KeyJustUp(VK_NUMPAD8)) return true; else return false;
	} else
	if (PAD::IsDisabledControlJustReleased(2, INPUT_FRONTEND_UP) || KeyJustUp(VK_NUMPAD8)) return true; else return false;
}
static bool IsDPressed(bool overrideInput = false) {
	if (!overrideInput && GetWindowManager()->IsMenuInputDisabled()) return false;

	if (SettingsMenuVars::vars.disablecontrollerinput) {
		if (KeyDown(VK_NUMPAD2)) return true; else return false;
	} else
	if (PAD::IsDisabledControlPressed(2, INPUT_FRONTEND_DOWN) || KeyDown(VK_NUMPAD2)) return true; else return false;
}
static bool IsDJPressed(bool overrideInput = false) {
	if (!overrideInput && GetWindowManager()->IsMenuInputDisabled()) return false;

	if (SettingsMenuVars::vars.disablecontrollerinput) {
		if (KeyJustUp(VK_NUMPAD2)) return true; else return false;
	} else
	if (PAD::IsDisabledControlJustReleased(2, INPUT_FRONTEND_DOWN) || KeyJustUp(VK_NUMPAD2)) return true; else return false;
}
static bool IsOptionPressed() {
	if (GetWindowManager()->IsMenuInputDisabled()) return false;
	if (IsAJPressed()) {
		AUDIO::PlaySoundFrontend(-1, "SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
		return true;
	}
	return false;
}

static void Up() {
	if (GetSubmenuHandler()->GetTotalOptions() == 0) return;
	GetMenu()->m_currentOption--;
	if (GetMenu()->m_scrollOffset > 0 && GetMenu()->m_currentOption - GetMenu()->m_scrollOffset == -1)GetMenu()->m_scrollOffset--;
	AUDIO::PlaySoundFrontend(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
	GetMenu()->m_breakScroll = 1;
}
static void Down() {
	if (GetSubmenuHandler()->GetTotalOptions() == 0) return;
	GetMenu()->m_currentOption++;
	if (GetMenu()->m_scrollOffset < GetSubmenuHandler()->GetTotalOptions() - GetMenu()->m_maxOptions && GetMenu()->m_currentOption - GetMenu()->m_scrollOffset == GetMenu()->m_maxOptions) GetMenu()->m_scrollOffset++;
	if (GetSubmenuHandler()->GetTotalOptions() >= GetMenu()->m_maxOptions && GetMenu()->m_scrollOffset > GetSubmenuHandler()->GetTotalOptions() - GetMenu()->m_maxOptions) GetMenu()->m_scrollOffset = GetSubmenuHandler()->GetTotalOptions() - GetMenu()->m_maxOptions;
	AUDIO::PlaySoundFrontend(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
	GetMenu()->m_breakScroll = 2;
}
static void Bottom() {
	if (GetSubmenuHandler()->GetTotalOptions() == 0) return;
	GetMenu()->m_currentOption = GetSubmenuHandler()->GetTotalOptions() - 1;
	if (GetSubmenuHandler()->GetTotalOptions() >= GetMenu()->m_maxOptions) GetMenu()->m_scrollOffset = GetSubmenuHandler()->GetTotalOptions() - GetMenu()->m_maxOptions;
	AUDIO::PlaySoundFrontend(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
	GetMenu()->m_breakScroll = 3;
}
static void Top() {
	if (GetSubmenuHandler()->GetTotalOptions() == 0) return;
	GetMenu()->m_currentOption = 0;
	GetMenu()->m_scrollOffset = 0;
	AUDIO::PlaySoundFrontend(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
	GetMenu()->m_breakScroll = 4;
}

static void MenuControls() {
	if (GetWindowManager()->IsMenuInputDisabled()) return;
	static bool upDisabled = false;
	static bool downDisabled = false;
	static int upTimer = 0;
	static int downTimer = 0;
	static int TIMER;
	//Scroll up
	if (IsUJPressed()) {
		if (!upDisabled) {
			if (GetMenu()->m_currentOption == 0) Bottom(); else Up();
		}
		upDisabled = false;
		upTimer = 0;
	}
	// Scroll down
	if (IsDJPressed()) {
		if (!downDisabled) {
			if (GetMenu()->m_currentOption == GetSubmenuHandler()->GetTotalOptions() - 1) Top(); else Down();
		}
		downDisabled = false;
		downTimer = 0;
	}
	// Hold up
	if (IsUPressed()) {
		if (++upTimer > 30) {
			upDisabled = true;
			Utils::DoTimedFunction(&TIMER, 100, [] { if (GetMenu()->m_currentOption == 0) Bottom(); else Up(); });
		}
	}
	// Hold down
	if (IsDPressed()) {
		if (++downTimer > 30) {
			downDisabled = true;
			Utils::DoTimedFunction(&TIMER, 100, [] { if (GetMenu()->m_currentOption == GetSubmenuHandler()->GetTotalOptions() - 1) Top(); else Down(); });
		}
	}

	// B press
	if (IsBJPressed()) {
		AUDIO::PlaySoundFrontend(-1, "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);

		GetSubmenuHandler()->SetSubPrevious();
	}

	//Binds press
	//if (currentsub != SUB::MAINMENU && isBinds())
}

static bool IsHotkeySavePressed() {
	return KeyJustUp(VK_F12);
}

static bool IsSavePressed() {
	return KeyJustUp(VK_F11);
}

static bool IsMousePressed() {
	//if (GetMouse()->m_draggingHeader)return false;
	return (GetMouse()->CanUse() ? GetMouse()->ButtonJustUp(VK_MOUSE_LEFT) : false);
}
static bool IsMouseDown() {
	return (GetMouse()->CanUse() ? GetMouse()->ButtonDown(VK_MOUSE_LEFT) : false);
}

static TranslationString strEnableCursor("Toggle cursor on", true, true);
static TranslationString strDisableCursor("Toggle cursor off", true, true);
static void MouseInput() {
	if (GetMouse()->IsEnabled()) {
		if (!MiscMenuVars::vars.Allowmousemovements) {
			GetWindowManager()->DisableGTAInputThisFrame();
		}
		HUD::_ShowCursorThisFrame();
	}
	if (GetWindowManager()->IsMenuInputDisabled()) return;
	if (!SettingsMenuVars::vars.hideuicursortooltip) GetScaleform()->DrawInstructional(GetMouse()->IsEnabled() ? strDisableCursor.Get() : strEnableCursor.Get(), g_keyNamesInstructional[GetMenu()->m_mouseKey]);
	if (KeyJustUp(GetMenu()->m_mouseKey)) GetMouse()->ToggleMouse();
}

static void PrepareMenu() {

	//if (HUD::IsPauseMenuActive()) GetWindowManager()->close();
	MOBILE::SetMobilePhonePosition(0, 0, 0);
	HUD::HideHudComponentThisFrame(5);
	HUD::DisplayAmmoThisFrame(0);
	HUD::SetRadarZoom(0);
	HUD::DisplayCash(1);
	//Remove notifications
	//HUD::CLEAR_PRINTS();
	HUD::ClearBrief();
	HUD::ClearAllHelpMessages();
}

static void DisableControls() {
	using namespace HUDComponents;

	HUD::HideHelpTextThisFrame();
	CAM::SetCinematicButtonActive(1);

	HUD::HideHudComponentThisFrame(HUD_HELP_TEXT);
	HUD::HideHudComponentThisFrame(HUD_VEHICLE_NAME);
	HUD::HideHudComponentThisFrame(HUD_AREA_NAME);
	HUD::HideHudComponentThisFrame(HUD_STREET_NAME);
	HUD::HideHudComponentThisFrame(HUD_VEHICLE_CLASS);

	PAD::SetInputExclusive(2, INPUT_FRONTEND_ACCEPT);
	PAD::SetInputExclusive(2, INPUT_FRONTEND_CANCEL);
	PAD::SetInputExclusive(2, INPUT_FRONTEND_DOWN);
	PAD::SetInputExclusive(2, INPUT_FRONTEND_UP);
	PAD::SetInputExclusive(2, INPUT_FRONTEND_LEFT);
	PAD::SetInputExclusive(2, INPUT_FRONTEND_RIGHT);
	PAD::DisableControlAction(0, INPUT_NEXT_CAMERA, true);
	PAD::DisableControlAction(0, INPUT_VEH_SELECT_NEXT_WEAPON, true);
	PAD::DisableControlAction(0, INPUT_FRONTEND_RIGHT, true);
	PAD::DisableControlAction(0, INPUT_FRONTEND_DOWN, true);
	PAD::DisableControlAction(0, INPUT_FRONTEND_LEFT, true);
	PAD::DisableControlAction(0, INPUT_FRONTEND_UP, true);
	PAD::DisableControlAction(0, INPUT_ARREST, true);
	PAD::DisableControlAction(0, INPUT_CONTEXT, true);
	PAD::DisableControlAction(0, INPUT_MELEE_BLOCK, true);
	PAD::DisableControlAction(2, INPUT_FRONTEND_UP, true);
	PAD::DisableControlAction(0, INPUT_HUD_SPECIAL, true);
	PAD::DisableControlAction(0, INPUT_VEH_CIN_CAM, true);
	PAD::DisableControlAction(2, INPUT_VEH_CIN_CAM, true);
	PAD::DisableControlAction(0, INPUT_VEH_HEADLIGHT, true);
	PAD::DisableControlAction(2, INPUT_FRONTEND_LEFT, true);
	PAD::DisableControlAction(2, INPUT_FRONTEND_DOWN, true);
	PAD::DisableControlAction(2, INPUT_FRONTEND_RDOWN, true);
	PAD::DisableControlAction(2, INPUT_FRONTEND_RIGHT, true);
	PAD::DisableControlAction(0, INPUT_CHARACTER_WHEEL, true);
	PAD::DisableControlAction(0, INPUT_VEH_RADIO_WHEEL, true);
	PAD::DisableControlAction(2, INPUT_FRONTEND_CANCEL, true);
	PAD::DisableControlAction(0, INPUT_MELEE_ATTACK_LIGHT, true);
	PAD::DisableControlAction(0, INPUT_MELEE_ATTACK_HEAVY, true);
	PAD::DisableControlAction(0, INPUT_SELECT_CHARACTER_TREVOR, true);
	PAD::DisableControlAction(0, INPUT_SELECT_CHARACTER_MICHAEL, true);
	PAD::DisableControlAction(0, INPUT_SELECT_CHARACTER_FRANKLIN, true);
	PAD::DisableControlAction(0, INPUT_SELECT_CHARACTER_MULTIPLAYER, true);
}