#include "stdafx.h"
#include "menu/submenus/mainMenu.h"

SubmenuHandler g_submenuHandler;

void SubmenuHandler::Init() {
	m_mainSubmenu = m_currentSubmenu = MainMenu::GetInstance();
}
void SubmenuHandler::Update(bool withInput) {
	m_currentSubmenu->MenuUpdate(withInput);
	if (m_nextSubmenu != nullptr) {
		GetMenu()->m_currentOption = m_nextCurrentOption;
		GetMenu()->m_scrollOffset = m_nextScrollOffset;
		m_currentSubmenu = m_nextSubmenu;
		m_nextSubmenu = nullptr;
		m_currentSubmenu->UpdateOnce();
	}
}

void SubmenuHandler::ASyncUpdate() {
	PROFILER();
	if (GetAuth()->IsAuthorized())
		for (auto& sub : m_submenus) sub->FeatureUpdate();
}

void SubmenuHandler::SetSubmenu(Submenu* submenu) {
	m_previousSubmenu = m_currentSubmenu;
	m_currentSubmenu->m_oldCurrentOption = GetMenu()->m_currentOption;
	m_currentSubmenu->m_oldScrollOffset = GetMenu()->m_scrollOffset;
	m_nextCurrentOption = 0;
	m_nextScrollOffset = 0;
	m_nextSubmenu = submenu;
}

void SubmenuHandler::SetSubPrevious(bool resetPosition) {
	m_previousSubmenu = m_currentSubmenu;
	if (m_currentSubmenu->getParentSubmenu() == nullptr) {
		GetSubmenuHandler()->SetSubmenuMain();
		GetMenu()->Close();
	} else {
		m_nextSubmenu = m_currentSubmenu->getParentSubmenu();
		m_nextCurrentOption = resetPosition ? 0 : m_nextSubmenu->m_oldCurrentOption;
		m_nextScrollOffset = resetPosition ? 0 : m_nextSubmenu->m_oldScrollOffset;
	}
}
void SubmenuHandler::SetSubmenuMain() {
	m_nextSubmenu = m_mainSubmenu;
	m_nextCurrentOption = 0;
	m_nextScrollOffset = 0;
}

SubmenuHandler* GetSubmenuHandler() {
	return &g_submenuHandler;
}

