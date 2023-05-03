#include "stdafx.h"

void ToggleOption::Input(int position) {
	if (GetMouse()->CanUse() && GetMouse()->MouseWithinCentered(GetRenderer()->m_posX, GetRenderer()->GetOptionY(position) + GetRenderer()->m_optionHeight / 2, GetRenderer()->m_width, GetRenderer()->m_optionHeight)) {
		if (m_hoverTimer > 30) GetRenderer()->RenderMouseTooltip(m_tooltip.Get());
		else m_hoverTimer++;
		GetMenu()->m_currentOption = position + GetMenu()->m_scrollOffset;
		if (GetMouse()->ButtonJustDown(VK_MOUSE_LEFT)) {
			*m_bool ^= true;
			m_function();
		}
	} else m_hoverTimer = 0;
}

void ToggleOption::Render(int position) {
	m_onUpdate(this);
	GetRenderer()->DrawString(m_name.Get(), GetRenderer()->m_posX - GetRenderer()->m_width / 2 + 0.006f, GetRenderer()->GetOptionYText(position), GetRenderer()->m_textFont, GetRenderer()->m_textSize, GetRenderer()->m_cOption);

	//Draw arrow
	GetRenderer()->DrawSprite(GetRenderer()->GetToggleTexture(*m_bool), GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.013f, GetRenderer()->GetOptionY(position) + (GetRenderer()->m_optionHeight / 2), 0.02f, 0.015f, 0, { 255, 255, 255, 255 });
}

void ToggleOption::RenderSelected(int position) {
	m_currentOp();
	if (IsOptionPressed() && m_requirement()) {
		*m_bool ^= true;
		m_function();
	}

	if (m_hasHotkey) {
		if (IsHotkeySavePressed()) {
			AUDIO::PlaySoundFrontend(-1, "ATM_WINDOW", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
			GetMenuInput()->AddToQueue([&] {GetMenuInput()->Hotkey(getName().Get(), this); });
		}
	}

	if (m_canBeSaved) {
		if (IsSavePressed()) {
			AUDIO::PlaySoundFrontend(-1, "ATM_WINDOW", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
			GetRenderer()->NotifyMap(va("%s saved", m_name.Get()));
			GetConfig()->WriteBool("Toggles", m_name.GetOriginal(), *m_bool);
		}
	}
};

TranslationString strEnabled("enabled", true, true);
TranslationString strDisabled("disabled", true, true);
void ToggleOption::HandleHotkey() {
	if (!m_requirement()) return;
	*m_bool ^= true;
	m_function();
	GetRenderer()->NotifyMap(va("~c~%s %s", m_name.Get(), *m_bool ? strEnabled.Get() : strDisabled.Get()));
}