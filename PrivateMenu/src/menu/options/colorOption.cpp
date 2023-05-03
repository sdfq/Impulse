#include "stdafx.h"

void ColorOption::GetInput() {
	GetMenuInput()->AddToQueue([this] {if (GetMenuInput()->Col(getName().Get(), *m_color)) {
		m_function();
	}
	});
}

void ColorOption::Input(int position) {
	if (GetMouse()->CanUse() && GetMouse()->MouseWithinCentered(GetRenderer()->m_posX, GetRenderer()->GetOptionY(position) + GetRenderer()->m_optionHeight / 2, GetRenderer()->m_width, GetRenderer()->m_optionHeight)) {
		if (m_hoverTimer > 30) GetRenderer()->RenderMouseTooltip(m_tooltip.Get());
		else m_hoverTimer++;
		GetMenu()->m_currentOption = position + GetMenu()->m_scrollOffset;
		if (GetMouse()->ButtonJustDown(VK_MOUSE_LEFT))
			GetInput();
	} else m_hoverTimer = 0;
}

void ColorOption::Render(int position) {
	m_onUpdate(this);
	GetRenderer()->DrawString(m_name.Get(), GetRenderer()->m_posX - GetRenderer()->m_width / 2 + 0.006f, GetRenderer()->GetOptionYText(position), GetRenderer()->m_textFont, GetRenderer()->m_textSize, GetRenderer()->m_cOption);
	Color darkened = m_color->getOffset(-50);
	Color lightened = m_color->getOffset(50);
	//GetRenderer()->DrawRect(GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.015f, GetRenderer()->GetOptionY(position) + (GetRenderer()->m_optionHeight / 2) - 0.0025f + 0.035f / 2, 0.02f, 0.02f, { 0, 0, 0, 255 });
	GetRenderer()->DrawRect(GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.015f, GetRenderer()->GetOptionY(position) + (GetRenderer()->m_optionHeight / 2) - 0.015f - 0.0025f + 0.035f / 2, 0.015f, 0.02f, { m_color->m_r, m_color->m_g, m_color->m_b, 255 });
	GetRenderer()->DrawRect(GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.015f, GetRenderer()->GetOptionY(position) + (GetRenderer()->m_optionHeight / 2) - 0.015f - 0.0025f + 0.035f / 2 - 0.01f + GetRenderer()->m_lineWidth, 0.015f, GetRenderer()->m_lineWidth * 2, { lightened.m_r, lightened.m_g, lightened.m_b, 255 });
	GetRenderer()->DrawRect(GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.015f, GetRenderer()->GetOptionY(position) + (GetRenderer()->m_optionHeight / 2) - 0.015f - 0.0025f + 0.035f / 2 + 0.01f - GetRenderer()->m_lineWidth, 0.015f, GetRenderer()->m_lineWidth * 2, { darkened.m_r, darkened.m_g, darkened.m_b, 255 });
}

void ColorOption::RenderSelected(int position) {
	m_currentOp();
	if (IsOptionPressed() && m_requirement()) {
		GetInput();
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
			GetConfig()->WriteColor("Colors", m_name.GetOriginal(), *m_color);
		}
	}
}

void ColorOption::HandleHotkey() {
	if (!m_requirement()) return;
	GetInput();
	GetRenderer()->NotifyMap(va("~c~%s", m_name.Get()));
}
