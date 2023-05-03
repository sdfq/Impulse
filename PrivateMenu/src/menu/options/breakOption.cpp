#include "stdafx.h"

void BreakOption::Input(int position) {}

void BreakOption::Render(int position) {
	HUD::SetTextCentre(1);
	static char nameBuffer[100];
	GetRenderer()->DrawString(m_line ? vaBuff(nameBuffer, 100, "~b~__ ~s~%s ~b~__~s~", m_name.Get()) : vaBuff(nameBuffer, 100, "~b~[ ~s~%s ~b~]~s~", m_name.Get()), GetRenderer()->m_posX, GetRenderer()->GetOptionYText(position), m_line ? FontHouseScript : GetRenderer()->m_textFont, GetRenderer()->m_textSize * 1.2f, m_line ? GetRenderer()->m_cOption.getOffset(-75) : GetRenderer()->m_cOption.getOffset(-75), true);
}

void BreakOption::RenderSelected(int position) {
	switch (GetMenu()->m_breakScroll) {
		case 1: //Up
			if (GetMenu()->m_scrollOffset > 0 && GetMenu()->m_currentOption - GetMenu()->m_scrollOffset == 0)GetMenu()->m_scrollOffset--;
			if (GetMenu()->m_currentOption - 1 < 0)Bottom();
			else GetMenu()->m_currentOption--;
			break;
		case 2: //Down
			if (GetMenu()->m_scrollOffset < GetSubmenuHandler()->GetTotalOptions() - GetMenu()->m_maxOptions && GetMenu()->m_currentOption + 1 - GetMenu()->m_scrollOffset == GetMenu()->m_maxOptions) GetMenu()->m_scrollOffset++;
			if (GetMenu()->m_currentOption + 1 >= GetSubmenuHandler()->GetTotalOptions())Top();
			else GetMenu()->m_currentOption++;
			break;
		case 3: //Bottom
			if (GetMenu()->m_scrollOffset > 0 && GetMenu()->m_currentOption - GetMenu()->m_scrollOffset == 1)GetMenu()->m_scrollOffset--;
			GetMenu()->m_currentOption--; break;
		case 4: //Top
			if (GetMenu()->m_scrollOffset < GetSubmenuHandler()->GetTotalOptions() - GetMenu()->m_maxOptions && GetSubmenuHandler()->GetTotalOptions() >= GetMenu()->m_maxOptions && GetMenu()->m_currentOption - GetMenu()->m_scrollOffset == GetMenu()->m_maxOptions) GetMenu()->m_scrollOffset++;
			GetMenu()->m_currentOption++; break;
		default:
			break;
	}
}

void BreakOption::HandleHotkey(){
}
