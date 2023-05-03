#include "stdafx.h"

bool compare(ProfileEntry& first, ProfileEntry& second) {
	return (first.getAverage() > second.getAverage());
}

void UIProfilerComponent::render() {
	static int TIMER;
	Utils::DoTimedFunction(&TIMER, 500, [&] {
		m_entries = GetProfiler()->GetEntries();
		sort(m_entries.begin(), m_entries.end(), compare);
	});


	double min = m_entries[0].getAverage();
	double max = m_entries[m_entries.size() - 1].getAverage();
	double length = max - min;

	float left = m_parent->m_position.x - m_parent->m_size.x / 2;
	float right = m_parent->m_position.x + m_parent->m_size.x / 2;
	float top = m_parent->m_position.y - m_parent->m_size.y / 2;
	float bottom = m_parent->m_position.y + m_parent->m_size.y / 2;

	float maxSize = m_textSize * m_linesToDisplay;
	float position = (float)(m_scroll) / (float)(m_entries.size() - m_linesToDisplay);
	float pos = m_entries.size() > m_linesToDisplay ? (position * (maxSize - m_textSize)) : maxSize - m_textSize;
	if (!GetMouse()->ButtonDown(VK_MOUSE_LEFT)) {
		m_dragging = false;
		GetWindowManager()->GetFrame()->m_isHandlingComponent = false;
	}

	if (!GetWindowManager()->GetFrame()->IsDragging() && GetMouse()->MouseWithinCentered(right + 0.01f, top + pos + GetRenderer()->m_dialogHeaderHeight + m_textSize / 2, 0.008f, 0.022f)) {
		GetMouse()->SetCursor(Mouse::HAND_OPEN);
		if (GetMouse()->ButtonDown(VK_MOUSE_LEFT)) {
			m_dragging = true;
			GetWindowManager()->GetFrame()->m_isHandlingComponent = true;
		}
	}
	if (m_dragging) {
		GetMouse()->SetCursor(Mouse::HAND_CLOSED);
		float posback = GetMouse()->GetMouseY() + 0.022f / 2 - (top + GetRenderer()->m_dialogHeaderHeight + m_textSize / 2);
		posback /= (maxSize - m_textSize);
		float positionback = posback * (float)(m_entries.size() - m_linesToDisplay);
		m_scroll = positionback;
		Utils::Clamp(&m_scroll, 0, m_entries.size() - m_linesToDisplay);
	}
	float offset = 0.005f;
	int scrollOffset = 0;

	GetRenderer()->DrawString("Name", left + offset, top + GetRenderer()->m_dialogHeaderHeight / 2, GetRenderer()->m_textFont, 0.3f, { GetRenderer()->m_cOption.m_r, GetRenderer()->m_cOption.m_g, GetRenderer()->m_cOption.m_b, GetRenderer()->m_cOption.m_a }, true, 1, offset + left, right);
	GetRenderer()->DrawString("MS", m_parent->m_position.x + offset, top + GetRenderer()->m_dialogHeaderHeight / 2, GetRenderer()->m_textFont, 0.3f, { GetRenderer()->m_cOption.m_r, GetRenderer()->m_cOption.m_g, GetRenderer()->m_cOption.m_b, GetRenderer()->m_cOption.m_a }, true, 1, 0.005f + m_parent->m_position.x, right);
	GetRenderer()->DrawString("CPU Cycles", m_parent->m_position.x + offset + 0.05f, top + GetRenderer()->m_dialogHeaderHeight / 2, GetRenderer()->m_textFont, 0.3f, { GetRenderer()->m_cOption.m_r, GetRenderer()->m_cOption.m_g, GetRenderer()->m_cOption.m_b, GetRenderer()->m_cOption.m_a }, true, 1, offset + m_parent->m_position.x + 0.05f, right);
	GetRenderer()->DrawString("Calls", m_parent->m_position.x + offset + 0.1f, top + GetRenderer()->m_dialogHeaderHeight / 2, GetRenderer()->m_textFont, 0.3f, { GetRenderer()->m_cOption.m_r, GetRenderer()->m_cOption.m_g, GetRenderer()->m_cOption.m_b, GetRenderer()->m_cOption.m_a }, true, 1, offset + m_parent->m_position.x + 0.1f, right);


	for (int i = m_scroll; i < m_scroll + m_linesToDisplay; i++) {
		if (i < m_entries.size() && i >= 0) {
			float percentage = m_entries.at(i).getAverage() / length * m_parent->m_size.x;
			percentage *= 0.9f;
			GetRenderer()->DrawRect(left - percentage / 2 + offset / 2, offset * 1.5f + top + (m_textSize * scrollOffset) + GetRenderer()->m_dialogHeaderHeight + (m_textSize * 0.8f) / 2, percentage, m_textSize *0.8f, { 255, 0, 0, 100 });
			GetRenderer()->DrawString(va("%s", m_entries.at(i).getFunctionName()), left + offset, offset / 2 + top + (m_textSize * scrollOffset) + GetRenderer()->m_dialogHeaderHeight, GetRenderer()->m_textFont, 0.3f, { 255, 255, 255, 255 }, false, 1, offset + left, right);
			GetRenderer()->DrawString(va("%fms", m_entries.at(i).getAverage()), m_parent->m_position.x + offset, offset / 2 + top + (m_textSize * scrollOffset) + GetRenderer()->m_dialogHeaderHeight, GetRenderer()->m_textFont, 0.3f, { 255, 255, 255, 255 }, false, 1, 0.005f + m_parent->m_position.x, right);
			GetRenderer()->DrawString(va("%lld", m_entries.at(i).getCycles()), m_parent->m_position.x + offset + 0.05f, offset / 2 + top + (m_textSize * scrollOffset) + GetRenderer()->m_dialogHeaderHeight, GetRenderer()->m_textFont, 0.3f, { 255, 255, 255, 255 }, false, 1, offset + m_parent->m_position.x + 0.05f, right);
			GetRenderer()->DrawString(va("%lld", m_entries.at(i).getCalls()), m_parent->m_position.x + offset + 0.1f, offset / 2 + top + (m_textSize * scrollOffset++) + GetRenderer()->m_dialogHeaderHeight, GetRenderer()->m_textFont, 0.3f, { 255, 255, 255, 255 }, false, 1, offset + m_parent->m_position.x + 0.1f, right);
		}
	}
	//GetRenderer()->DrawRect(right - 0.01f, m_parent->m_position.y - m_parent->m_size.y / 2 + GetRenderer()->m_dialogHeaderHeight + maxSize, 0.01f, 0.01f, { 25, 25, 25, 255 }); //Top
	//GetRenderer()->DrawSprite({ "commonmenu", "arrowright" }, right - 0.01f, m_parent->m_position.y - m_parent->m_size.y / 2 + GetRenderer()->m_dialogHeaderHeight + maxSize, 0.01f, 0.01f, 0, { 25, 25, 25, 255 }); //Top
	GetRenderer()->DrawRect(right + 0.01f, top + GetRenderer()->m_dialogHeaderHeight - 0.007f, 0.01f, 0.014f, { 0, 0, 0, 255 }); //Bottom
	GetRenderer()->DrawRect(right + 0.01f, bottom - GetRenderer()->m_dialogFooterHeight + 0.007f, 0.01f, 0.014f, { 0, 0, 0, 255 }); //Bottom
	GetRenderer()->DrawSpriteAspect({ "commonmenu", "arrowright" }, right + 0.01f, top + GetRenderer()->m_dialogHeaderHeight - 0.007f, 25, 25, -90, { 255, 255, 255, 255 }); //Bottom
	GetRenderer()->DrawSpriteAspect({ "commonmenu", "arrowright" }, right + 0.01f, bottom - GetRenderer()->m_dialogFooterHeight + 0.007f, 25, 25, 90, { 255, 255, 255, 255 }); //Bottom
	GetRenderer()->DrawRect(right + 0.01f, m_parent->m_position.y + GetRenderer()->m_dialogHeaderHeight / 2 - GetRenderer()->m_dialogFooterHeight / 2, 0.01f, maxSize, { GetRenderer()->m_cPrimary.m_r, GetRenderer()->m_cPrimary.m_g, GetRenderer()->m_cPrimary.m_b, 100 }); //Whole
	GetRenderer()->DrawRect(right + 0.01f, top + pos + GetRenderer()->m_dialogHeaderHeight + m_textSize / 2, 0.008f, 0.022f, GetRenderer()->m_cSelection); //Level
	GetRenderer()->DrawRect(right + 0.01f, top + pos + GetRenderer()->m_dialogHeaderHeight + m_textSize / 2 - 0.022f / 2 + GetRenderer()->m_lineWidth, 0.008f, GetRenderer()->m_lineWidth, GetRenderer()->m_cSelection.getOffset(75)); //Level
	GetRenderer()->DrawRect(right + 0.01f, top + pos + GetRenderer()->m_dialogHeaderHeight + m_textSize / 2 + 0.022f / 2 - GetRenderer()->m_lineWidth, 0.008f, GetRenderer()->m_lineWidth, GetRenderer()->m_cSelection.getOffset(-75)); //Level
																																																																					//GetRenderer()->DrawRect(right + 0.01f, m_parent->m_position.y - m_parent->m_size.y / 2 + pos + GetRenderer()->m_dialogHeaderHeight + m_textSize / 2, 0.007f, 0.021f, GetRenderer()->m_cOption); //Level
}