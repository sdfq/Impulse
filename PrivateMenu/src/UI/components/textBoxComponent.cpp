#include "stdafx.h"

void UITextBoxComponent::update() {
	if (GetMouse()->MouseWithin(m_parent->m_position.x - m_parent->m_size.x / 2, m_parent->m_position.y + m_parent->m_size.y / 2 - GetRenderer()->m_dialogFooterHeight, m_parent->m_size.x, GetRenderer()->m_dialogFooterHeight * 2)) {
		GetMouse()->SetCursor(Mouse::HAND_MIDDLEFINGER);
		if (GetMouse()->ButtonJustUp(VK_MOUSE_LEFT)) {
			GetMouse()->SetCursor(Mouse::HAND_CLOSED);
			m_textSelected = true;
		}
	}
}

void UITextBoxComponent::render() {
	float left = m_parent->m_position.x - m_parent->m_size.x / 2;
	float right = m_parent->m_position.x + m_parent->m_size.x / 2;
	float maxSize = m_textSize * m_linesToDisplay;
	float position = (float)(m_scroll) / (float)(m_lines.size() - m_linesToDisplay);
	float pos = m_lines.size() > m_linesToDisplay ? (position * (maxSize - m_textSize)) : maxSize - m_textSize;
	if (!GetMouse()->ButtonDown(VK_MOUSE_LEFT)) m_dragging = false;
	if (!GetWindowManager()->GetFrame()->IsDragging() && GetMouse()->MouseWithinCentered(right + 0.01f, m_parent->m_position.y - m_parent->m_size.y / 2 + pos + GetRenderer()->m_dialogHeaderHeight + m_textSize / 2, 0.008f, 0.022f)) {
		GetMouse()->SetCursor(Mouse::HAND_OPEN);
		if (GetMouse()->ButtonDown(VK_MOUSE_LEFT)) m_dragging = true;
	}
	if (m_dragging) {
		GetMouse()->SetCursor(Mouse::HAND_CLOSED);
		float posback = GetMouse()->GetMouseY() + 0.022f / 2 - (m_parent->m_position.y - m_parent->m_size.y / 2 + GetRenderer()->m_dialogHeaderHeight + m_textSize / 2);
		posback /= (maxSize - m_textSize);
		float positionback = posback * (float)(m_lines.size() - m_linesToDisplay);
		m_scroll = positionback;
		Utils::Clamp(&m_scroll, 0, m_lines.size() - m_linesToDisplay);
	}
	float offset = 0.005f;
	int scrollOffset = 0;
	for (int i = m_scroll; i < m_scroll + m_linesToDisplay; i++) {
		if (i < m_lines.size() && i >= 0) {
			string temp = m_lines.at(i);
			int size = temp.size();
			if (size > 110) temp = temp.substr(0, 107) + "...";

			GetRenderer()->DrawString(temp.c_str(), left + offset, offset / 2 + m_parent->m_position.y - m_parent->m_size.y / 2 - GetRenderer()->m_dialogHeaderHeight / 4 + (m_textSize * scrollOffset++) + GetRenderer()->m_dialogHeaderHeight, 4, GetRenderer()->m_textSize, { 255, 255, 255, 255 }, true, 1, 0.005f + m_parent->m_position.x - m_parent->m_size.x / 2, m_parent->m_position.x + m_parent->m_size.x / 2);
		}
	}
	//GetRenderer()->DrawRect(right - 0.01f, m_parent->m_position.y - m_parent->m_size.y / 2 + GetRenderer()->m_dialogHeaderHeight + maxSize, 0.01f, 0.01f, { 25, 25, 25, 255 }); //Top
	//GetRenderer()->DrawSprite({ "commonmenu", "arrowright" }, right - 0.01f, m_parent->m_position.y - m_parent->m_size.y / 2 + GetRenderer()->m_dialogHeaderHeight + maxSize, 0.01f, 0.01f, 0, { 25, 25, 25, 255 }); //Top
	GetRenderer()->DrawRect(right + 0.01f, m_parent->m_position.y - m_parent->m_size.y / 2 + GetRenderer()->m_dialogHeaderHeight - 0.007f, 0.01f, 0.014f, { 0, 0, 0, 255 }); //Bottom
	GetRenderer()->DrawRect(right + 0.01f, m_parent->m_position.y + m_parent->m_size.y / 2 - GetRenderer()->m_dialogFooterHeight + 0.007f, 0.01f, 0.014f, { 0, 0, 0, 255 }); //Bottom
	GetRenderer()->DrawSpriteAspect({ "commonmenu", "arrowright" }, right + 0.01f, m_parent->m_position.y - m_parent->m_size.y / 2 + GetRenderer()->m_dialogHeaderHeight - 0.007f, 25, 25, -90, { 255, 255, 255, 255 }); //Bottom
	GetRenderer()->DrawSpriteAspect({ "commonmenu", "arrowright" }, right + 0.01f, m_parent->m_position.y + m_parent->m_size.y / 2 - GetRenderer()->m_dialogFooterHeight + 0.007f, 25, 25, 90, { 255, 255, 255, 255 }); //Bottom
	GetRenderer()->DrawRect(right + 0.01f, m_parent->m_position.y + GetRenderer()->m_dialogHeaderHeight / 2 - GetRenderer()->m_dialogFooterHeight / 2, 0.01f, maxSize, { GetRenderer()->m_cPrimary.m_r, GetRenderer()->m_cPrimary.m_g, GetRenderer()->m_cPrimary.m_b, 100 }); //Whole
	GetRenderer()->DrawRect(right + 0.01f, m_parent->m_position.y - m_parent->m_size.y / 2 + pos + GetRenderer()->m_dialogHeaderHeight + m_textSize / 2, 0.008f, 0.022f, GetRenderer()->m_cSelection); //Level
	GetRenderer()->DrawRect(right + 0.01f, m_parent->m_position.y - m_parent->m_size.y / 2 + pos + GetRenderer()->m_dialogHeaderHeight + m_textSize / 2 - 0.022f / 2 + GetRenderer()->m_lineWidth, 0.008f, GetRenderer()->m_lineWidth, GetRenderer()->m_cSelection.getOffset(75)); //Level
	GetRenderer()->DrawRect(right + 0.01f, m_parent->m_position.y - m_parent->m_size.y / 2 + pos + GetRenderer()->m_dialogHeaderHeight + m_textSize / 2 + 0.022f / 2 - GetRenderer()->m_lineWidth, 0.008f, GetRenderer()->m_lineWidth, GetRenderer()->m_cSelection.getOffset(-75)); //Level

	if (m_textSelected)
		GetRenderer()->DrawRect(m_parent->m_position.x, m_parent->m_position.y + m_parent->m_size.y / 2 - GetRenderer()->m_dialogFooterHeight / 2 - GetRenderer()->m_lineWidth, m_parent->m_size.x - GetRenderer()->m_lineWidth * 2, GetRenderer()->m_dialogFooterHeight, { 255, 255, 255, 255 });
	else
		GetRenderer()->DrawRect(m_parent->m_position.x, m_parent->m_position.y + m_parent->m_size.y / 2 - GetRenderer()->m_dialogFooterHeight / 2 - GetRenderer()->m_lineWidth, m_parent->m_size.x - GetRenderer()->m_lineWidth * 2, GetRenderer()->m_dialogFooterHeight, { 155, 155, 155, 255 });

	if (!GetMouse()->MouseWithin(m_parent->m_position.x - m_parent->m_size.x / 2, m_parent->m_position.y + m_parent->m_size.y / 2 - GetRenderer()->m_dialogFooterHeight, m_parent->m_size.x, GetRenderer()->m_dialogFooterHeight * 2)) {
		if (GetMouse()->ButtonDown(VK_MOUSE_LEFT)) {
			m_textSelected = false;
		}
	}

	static int TIMER;
	Utils::DoTimedFunction(&TIMER, 350, [this] {m_blink = !m_blink; });
	GetRenderer()->DrawString((m_inputText + (m_blink && m_textSelected ? "~m~|~s~" : "")).c_str(), m_parent->m_position.x - m_parent->m_size.x / 2 + 0.002f, m_parent->m_position.y + m_parent->m_size.y / 2 - GetRenderer()->m_dialogFooterHeight - 0.004f, 0, 0.3f, { 0, 0, 0, 255 }, false, 1, m_parent->m_position.x - m_parent->m_size.x / 2 + 0.002f, m_parent->m_position.x + m_parent->m_size.x / 2 - 0.002f);

	if (m_textSelected) {
		GetMenuInput()->GetInput(m_inputText, normalCombinations, NUMOF(normalCombinations), 50);
		GetWindowManager()->DisableMenuInputThisFrame();
	}

	if (m_textSelected && GetKeyboard()->KeyJustUp(VK_RETURN)) {
		m_callback(m_inputText.c_str());
		m_inputText.clear();
	}
}
