#include "stdafx.h"

void UITextInputComponent::update()
{
	if (GetMouse()->MouseWithin(m_parent->m_position.x - m_parent->m_size.x / 2 + 0.01f, m_parent->m_position.y + m_parent->m_headerHeight, m_parent->m_size.x - 0.02f, GetRenderer()->m_dialogFooterHeight * 2)) {
		GetMouse()->SetCursor(Mouse::HAND_MIDDLEFINGER);
		if (GetMouse()->ButtonJustUp(VK_MOUSE_LEFT)) {
			GetMouse()->SetCursor(Mouse::HAND_CLOSED);
			m_textSelected = true;
		}
	}
}
void UITextInputComponent::ASyncUpdate(){}
void UITextInputComponent::render()
{
	if (m_textSelected)
		GetRenderer()->DrawRect(m_parent->m_position.x, m_parent->m_position.y + m_parent->m_headerHeight, m_parent->m_size.x - 0.02f, GetRenderer()->m_dialogFooterHeight, { 255, 255, 255, 255 });
	else
		GetRenderer()->DrawRect(m_parent->m_position.x, m_parent->m_position.y + m_parent->m_headerHeight / 2, m_parent->m_size.x - 0.02f, GetRenderer()->m_dialogFooterHeight, { 155, 155, 155, 255 });

	if (!GetMouse()->MouseWithin(m_parent->m_position.x - m_parent->m_size.x / 2, m_parent->m_position.y + m_parent->m_headerHeight, m_parent->m_size.x, GetRenderer()->m_dialogFooterHeight * 2)) {
		if (GetMouse()->ButtonDown(VK_MOUSE_LEFT)) {
			m_textSelected = false;
		}
	}

	static int TIMER;
	Utils::DoTimedFunction(&TIMER, 350, [this] {m_blink = !m_blink; });
	GetRenderer()->DrawString((m_input + (m_blink && m_textSelected ? "~m~|~s~" : "")).c_str(), m_parent->m_position.x - m_parent->m_size.x / 2 + 0.002f + 0.01f, m_parent->m_position.y + m_parent->m_headerHeight - 0.004f, 0, 0.3f, { 0, 0, 0, 255 }, false, 1, m_parent->m_position.x - m_parent->m_size.x / 2 + 0.002f + 0.01f, m_parent->m_position.x + m_parent->m_size.x / 2 - 0.002f - 0.01f);

	if (m_textSelected) {
		GetMenuInput()->GetInput(m_input, normalCombinations, NUMOF(normalCombinations), 50);
		GetWindowManager()->DisableMenuInputThisFrame();
	}

	if (m_textSelected && GetKeyboard()->KeyJustUp(VK_RETURN)) {
		m_callback(m_input.c_str());
		m_input.clear();
		m_textSelected = false;
	}
}