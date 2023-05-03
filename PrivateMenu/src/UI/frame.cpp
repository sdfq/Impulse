#include "stdafx.h"

void UIFrame::addWindow(UIWindow* window, bool fadeIn) {
	auto& it = find(m_windows.begin(), m_windows.end(), window);
	if (it != m_windows.end()) {
		rearrange(*it);
		return;
	}
	m_windows.push_back(window);
	window->setParent(this);
	if (fadeIn)window->fadeIn([] {});
	rearrange(window);
}

void UIFrame::removeWindow(UIWindow* window) {
	window->fadeOut([this, window] {
		m_windows.erase(remove(m_windows.begin(), m_windows.end(), window), m_windows.end()); });
}

void UIFrame::update() {
	GetMouse()->SetCursor(Mouse::NORMAL);
	int i = Utils::Clamp(m_windows.size(), -8, 6);
	for (auto& window : m_windows) {
		if (!window->shouldRenderThisFrame()) continue;
		static int temp;
		GetRenderer()->Set2DLayer(i--);
		PROFILER_START(Window);
		window->render();
		PROFILER_END(Window);
	}
	if (!GetMouse()->ButtonDown(VK_MOUSE_LEFT))m_dragging = false;
	if (!m_dragging && !m_isHandlingComponent) {
		static float xSize = 0.02f * 1.2f;
		static float ySize = 0.03f * 1.2f;
		static float xOffset = 0.01f;
		static float xOffset2 = 0.0225f;
		static float yOffset = 0.015f;

		for (auto& window : m_windows) {
			if (!window->shouldRenderThisFrame()) continue;
			if (window->canBeClosed() || window->canBeMinimized()) {
				if (Utils::Within(GetMouse()->GetMouseY(), window->m_position.y - window->m_size.y / 2 + yOffset - ySize / 4, window->m_position.y - window->m_size.y / 2 + yOffset + ySize / 4)) {
					bool withinRight = Utils::Within(GetMouse()->GetMouseX(), window->m_position.x + window->m_size.x / 2 - xOffset - xSize / 4, window->m_position.x + window->m_size.x / 2 - xOffset + xSize / 4);
					bool withinLeft = Utils::Within(GetMouse()->GetMouseX(), window->m_position.x + window->m_size.x / 2 - xOffset2 - xSize / 4, window->m_position.x + window->m_size.x / 2 - xOffset2 + xSize / 4);
					if (withinRight) {
						if (GetMouse()->ButtonJustDown(VK_MOUSE_LEFT)) {
							if (window->canBeClosed()) removeWindow(window);
							else window->minimize();
						} else GetMouse()->SetCursor(window->canBeClosed() ? Mouse::HAND_MIDDLEFINGER : window->isMinimized() ? Mouse::ARROW_PLUS : Mouse::ARROW_MINUS);
						break;
					}
					if (withinLeft && window->canBeClosed()) {
						if (GetMouse()->ButtonJustDown(VK_MOUSE_LEFT)) {
							window->minimize();
						} else GetMouse()->SetCursor(window->isMinimized() ? Mouse::ARROW_PLUS : Mouse::ARROW_MINUS);
						break;
					}
				}
			}
			/*Resizing*/
			/*if (GetMouse()->MouseWithinCentered(window->m_position.x + window->m_size.x / 2 + 0.01f, window->m_position.y, 0.02f, window->m_size.y)) {
				if (!m_resizing && !m_dragging) GetMouse()->SetCursor(Mouse::ARROW_LEFT_RIGHT);
				if (IsMouseDown() && !m_resizing && !m_dragging) {
					m_resizing = true;
					m_resizingWindow = window;
					GetMouse()->SetCursor(Mouse::HAND_CLOSED);
				};
			} else if (!IsMouseDown()) {
				m_resizing = false;
				m_resizingWindow = nullptr;
				if (!m_dragging)m_clickedPos = { GetMouse()->GetMouseX() - m_currentWindow->m_size.x, GetMouse()->GetMouseY() - m_currentWindow->m_size.y };
				m_dragging = true;
			}*/
			if (window->within(GetMouse()->GetMouseX(), GetMouse()->GetMouseY()) && !m_resizing) {
				m_currentWindow = window;
				if (GetMouse()->ButtonDown(VK_MOUSE_LEFT)) {
					rearrange(m_currentWindow);

				}
				window->update();
				if (window->withinHeaderY(GetMouse()->GetMouseY())) {
					GetMouse()->SetCursor(Mouse::HAND_OPEN);
					//if (GetMouse()->ButtonDoubleClicked(VK_MOUSE_LEFT)) window->minimize();
					/*else*/ if (GetMouse()->ButtonDown(VK_MOUSE_LEFT)) {
						if (!m_dragging)m_clickedPos = { GetMouse()->GetMouseX() - m_currentWindow->m_position.x, GetMouse()->GetMouseY() - m_currentWindow->m_position.y };
						m_dragging = true;
					}
				}
				break;
			}
		}
		/*Resizing*/
		/*if (m_resizing && m_resizingWindow != nullptr) {
			m_resizingWindow->m_size.x += GetMouse()->GetXMovement();
			if (!Utils::Clamp(&m_resizingWindow->m_size.x, 0.05f, 0.3f)) {
				m_resizingWindow->m_position.x += GetMouse()->GetXMovement() / 2;
			} else {
				PAD::_SetCursorLocation(m_resizingWindow->m_position.x + m_resizingWindow->m_size.x / 2, GetMouse()->GetMouseY());
			}
		}*/
	} else dragUpdate();
}

void UIFrame::dragUpdate() {
	if (m_currentWindow == nullptr)return;
	if (m_dragging && m_currentWindow->shouldRenderThisFrame()) {
		GetMouse()->SetCursor(Mouse::HAND_CLOSED);
		m_currentWindow->m_position.x = GetMouse()->GetMouseX() - m_clickedPos.x;
		m_currentWindow->m_position.y = GetMouse()->GetMouseY() - m_clickedPos.y;
		if (Utils::Clamp(&m_currentWindow->m_position.x, m_currentWindow->m_size.x / 2, 1 - m_currentWindow->m_size.x / 2) |
			Utils::Clamp(&m_currentWindow->m_position.y, m_currentWindow->m_size.y / 2, 1 - m_currentWindow->m_size.y / 2))
			PAD::_SetCursorLocation(m_currentWindow->m_position.x + m_clickedPos.x, m_currentWindow->m_position.y + m_clickedPos.y);
	}
}

void UIFrame::ASyncUpdate() {
	for (auto& window : m_windows) {
		window->ASyncUpdate();
	}
}

void UIFrame::scrollEvent(int scroll) {
	for (auto& window : m_windows) {
		if (!window->shouldRenderThisFrame()) continue;
		if (window->within(GetMouse()->GetMouseX(), GetMouse()->GetMouseY())) {
			window->scrollEvent(scroll);
			break;
		}
	}
}