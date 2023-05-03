#include "stdafx.h"

void ButtonOption::Input(int position) {
	if (GetMouse()->CanUse() && GetMouse()->MouseWithinCentered(GetRenderer()->m_posX, GetRenderer()->GetOptionY(position) + GetRenderer()->m_optionHeight / 2, GetRenderer()->m_width, GetRenderer()->m_optionHeight)) {
		if (m_hoverTimer > 30) GetRenderer()->RenderMouseTooltip(m_tooltip.Get());
		else m_hoverTimer++;
		GetMenu()->m_currentOption = position + GetMenu()->m_scrollOffset;
		if (GetMouse()->ButtonJustDown(VK_MOUSE_LEFT))
			m_function();
	} else m_hoverTimer = 0;
}

void ButtonOption::Render(int position) {
	m_onUpdate(this);
	GetRenderer()->DrawString(m_name.Get(), GetRenderer()->m_posX - GetRenderer()->m_width / 2 + 0.006f, GetRenderer()->GetOptionYText(position), GetRenderer()->m_textFont, GetRenderer()->m_textSize, GetRenderer()->m_cOption);
}

void ButtonOption::RenderSelected(int position) {
	m_currentOp();
	if (IsOptionPressed() && m_requirement()) {
		m_function();
	}

	if (m_hasHotkey) {
		if (IsHotkeySavePressed()) {
			AUDIO::PlaySoundFrontend(-1, "ATM_WINDOW", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
			GetMenuInput()->AddToQueue([&] {GetMenuInput()->Hotkey(getName().Get(), this); });
		}
	}
}

void ButtonOption::HandleHotkey() {
	if (!m_requirement()) return;
	m_function();
	GetRenderer()->NotifyMap(va("~c~%s", m_name.Get()));
}
