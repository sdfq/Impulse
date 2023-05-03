#pragma once
#include "menu/submenus/main/settingsMenu.h"

class Menu : public UIWindow {
private:
	bool m_closing = false;
	bool m_draggingSlider = false;
	bool m_inputThisFrame;
public:
	bool m_open = false;


	//Menu() : {}

	int m_maxOptions = 14; //14 is Default
	int m_currentOption = 0;
	int m_scrollOffset;
	int m_breakScroll;

	int m_openKey = VK_F4;
	int m_mouseKey = 'X';

	void update() override;
	bool within(float x, float y) override;
	bool withinHeaderY(float y) override;

	void render() override;
	void ASyncUpdate();
	void scrollEvent(int scroll) override;

	void Open() {
	if (m_isFading) return;
		m_open = true;

		if (!SettingsMenuVars::vars.keeplastpos) {
			GetSubmenuHandler()->SetSubmenuMain();
		}

		AUDIO::PlaySoundFrontend(-1, "FocusIn", "HintCamSounds", 0);
		fadeIn([&] {m_closing = false; });
	}
	void Close() {
		if (!m_isFading) { m_closing = true; fadeOut([&] {m_open = false; }); }
	}
	void ToggleOpen() { if (!m_isFading) { if (m_open) Close(); else Open(); } }
	bool IsOpen() { return m_open && !m_closing; }

	void Initialize();
	void ResetCurrentOption() { m_currentOption = 0; m_scrollOffset = 0; }
};

Menu* GetMenu();