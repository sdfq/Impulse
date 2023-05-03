#include "stdafx.h"

static Mouse g_mouse;

void Mouse::UpdateMouse() {
	m_oldX = m_X;
	m_oldY = m_Y;
	GRAPHICS::_GetActiveScreenResolution(&m_resX, &m_resY);
}

/*Do Mouse scrolling shit here*/
void Mouse::ScrollWheel(int i) {
	if (m_usingMouse) {
		for (auto& event : m_scrollEvents) {
			event(i);
		}
	}
}

void Mouse::EnableButton(int button, bool down) {
	button_states[button].doubleClicked = (button < 5 && button_states[button].m_isUpNow && GetTickCount() < button_states[button].time + m_DOUBLECLICKPERIOD);
	button_states[button].time = GetTickCount();
	button_states[button].m_isUpNow = !down;
	button_states[button].m_justDown = down;
}

bool Mouse::ButtonDown(DWORD button) {
	if (!m_usingMouse) return false;
	return (button < 5) ? ((GetTickCount() < button_states[button].time + m_MAXDOWN) && !button_states[button].m_isUpNow) : false;
}

void Mouse::ResetButtonState(DWORD button) {
	if (button < 5) memset(&button_states[button], 0, sizeof(button_states[0]));
}

bool Mouse::ButtonJustUp(DWORD button) {
	if (!m_usingMouse) return false;
	const auto result = (button < 5) ? (GetTickCount() < button_states[button].time + m_NOWPERIOD && button_states[button].m_isUpNow) : false;
	if (result) ResetButtonState(button);
	return result;
}

bool Mouse::ButtonJustDown(DWORD button) {
	if (!m_usingMouse) return false;
	bool result = (button < 5) ? (GetTickCount() - m_NOWPERIOD < button_states[button].time && !button_states[button].m_isUpNow && button_states[button].m_justDown) : false;
	if (result) button_states[button].m_justDown = false;
	return result;
}

bool Mouse::ButtonDoubleClicked(DWORD button) {
	if (!m_usingMouse) return false;
	bool result = (button < 5) ? ((GetTickCount() < button_states[button].time + m_NOWPERIOD) && button_states[button].doubleClicked) : false;
	if (result) ResetButtonState(button);
	return result;
}

float Mouse::GetMouseX() { return m_usingMouse ? (float)m_X / m_resX : -1; }
float Mouse::GetMouseY() { return m_usingMouse ? (float)m_Y / m_resY : -1; }
float Mouse::GetMouseOldX() { return m_usingMouse ? (float)m_oldX / m_resX : -1; }
float Mouse::GetMouseOldY() { return m_usingMouse ? (float)m_oldY / m_resY : -1; }
float Mouse::GetXMovement() { return m_usingMouse ? GetMouseX() - GetMouseOldX() : -1; }
float Mouse::GetYMovement() { return m_usingMouse ? GetMouseY() - GetMouseOldY() : -1; }
Vector2 Mouse::GetPositionAsVector() { return { GetMouseX(), GetMouseY() }; }

bool Mouse::MouseWithin(float x, float y, float width, float height) {
	if (!m_usingMouse) return false;
	return Utils::Within(GetMouseX(), x, x + width) && Utils::Within(GetMouseY(), y, y + height);
}

bool Mouse::MouseWithinCentered(float x, float y, float width, float height) {
	if (!m_usingMouse) return false;
	return Utils::Within(GetMouseX(), x - width / 2, x + width / 2) && Utils::Within(GetMouseY(), y - height / 2, y + height / 2);
}

bool Mouse::CanUse() { return m_usingMouse && !GetContextMenu()->IsDrawing() && !GetWindowManager()->GetFrame()->IsDragging() && !GetWindowManager()->GetFrame()->m_isHandlingComponent; }

Mouse* GetMouse() { return &g_mouse; }