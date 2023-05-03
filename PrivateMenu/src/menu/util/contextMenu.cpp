#include "stdafx.h"

ContextMenu g_contextMenu;

//Test
void ContextMenu::DrawMenu(int position, initializer_list<ContextMenuOption> options) {

	m_isDrawing = true;
	m_options = options;
	m_position = position;
	m_width = 0;
	for (auto& option : options) {
		float size = GetRenderer()->GetStringWidth(option.m_name, 0, 0.4f);
		m_width = size > m_width ? size : m_width;
	}
	m_width = m_width > 0.1f ? m_width : 0.1f;
	m_optionHeight = GetRenderer()->GetStringHeight(0, 0.4f);
	m_height = options.size() * m_optionHeight;
}

void ContextMenu::Update() {
	if (!m_isDrawing) return;
	GetWindowManager()->DisableMenuInputThisFrame();
	//if (GetMouse()->ButtonJustUp(VK_MOUSE_LEFT) && !Utils::Within(GetMouse()->GetMouseX(), m_position.x, m_position.x + m_width) && !Utils::Within(GetMouse()->GetMouseY(), m_position.y, m_position.y + m_height)) {
	//	m_isDrawing = false;
	//	GetWindowManager()->m_menuInputDisabled = false;
	//}

	GetRenderer()->DrawBox(GetRenderer()->m_posX + GetRenderer()->m_width/2 + m_width / 2, GetRenderer()->GetOptionY(m_position), m_width, m_height);
	int temp = 0;
	for (auto& option : m_options) {
		GetRenderer()->DrawString(option.m_name, GetRenderer()->m_posX + GetRenderer()->m_width / 2 + m_width / 2, GetRenderer()->GetOptionY(m_position) + m_optionHeight * temp++, 0, 0.4f, { 255, 255, 255, 255 });
	}
}

ContextMenu* GetContextMenu() { return &g_contextMenu; }