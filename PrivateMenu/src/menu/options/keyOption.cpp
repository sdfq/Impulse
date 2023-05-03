#include "stdafx.h"

void KeyOption::Input(int position) {
	if (GetMouse()->CanUse() && GetMouse()->MouseWithinCentered(GetRenderer()->m_posX, GetRenderer()->GetOptionY(position) + GetRenderer()->m_optionHeight / 2, GetRenderer()->m_width, GetRenderer()->m_optionHeight)) {
		if (m_hoverTimer > 30) GetRenderer()->RenderMouseTooltip(m_tooltip.Get());
		else m_hoverTimer++;
		GetMenu()->m_currentOption = position + GetMenu()->m_scrollOffset;
		if (GetMouse()->ButtonJustDown(VK_MOUSE_LEFT))
			GetMenuInput()->AddToQueue([this] {if (GetMenuInput()->Key(getName().Get(), m_key, m_isController, m_controllerSupport)) {
			m_function();
			GetConfig()->WriteInt("Keys", m_name.GetOriginal(), *m_key);
			if (m_isController)GetConfig()->WriteBool("KeysController", m_name.GetOriginal(), *m_isController);
		} });
	} else m_hoverTimer = 0;
}
void KeyOption::Render(int position) {
	m_onUpdate(this);
	GetRenderer()->DrawString(m_name.Get(), GetRenderer()->m_posX - GetRenderer()->m_width / 2 + 0.006f, GetRenderer()->GetOptionYText(position), GetRenderer()->m_textFont, GetRenderer()->m_textSize, GetRenderer()->m_cOption);
	GetRenderer()->DrawString(g_keyNames[*m_key], GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.01f, GetRenderer()->GetOptionYText(position), GetRenderer()->m_textFont, GetRenderer()->m_textSize, GetRenderer()->m_cOption.getOffset(-20), true, 2, 0, GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.01f);
}

void KeyOption::RenderSelected(int position) {
	m_currentOp();
	if (IsOptionPressed() && m_requirement()) {
		GetMenuInput()->AddToQueue([this] {if (GetMenuInput()->Key(getName().Get(), m_key, m_isController, m_controllerSupport)) {
			m_function();
			GetConfig()->WriteInt("Keys", m_name.GetOriginal(), *m_key);
			if (m_isController)GetConfig()->WriteBool("KeysController", m_name.GetOriginal(), *m_isController);
		} });
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
			GetRenderer()->NotifyMap(va("%s saved", m_name));
			GetConfig()->WriteInt("Keys", m_name.GetOriginal(), *m_key);
			if(m_isController)GetConfig()->WriteBool("KeysController", m_name.GetOriginal(), *m_isController);
		}
	}
}

void KeyOption::HandleHotkey() {
	if (!m_requirement()) return;
	GetMenuInput()->AddToQueue([this] {if (GetMenuInput()->Key(getName().Get(), m_key, m_isController, m_controllerSupport)) {
		m_function();
		GetConfig()->WriteInt("Keys", m_name.GetOriginal(), *m_key);
		if (m_isController)GetConfig()->WriteBool("KeysController", m_name.GetOriginal(), *m_isController);
	} });
	GetRenderer()->NotifyMap(va("~c~%s", m_name.Get()));
}
