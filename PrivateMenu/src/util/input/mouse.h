#pragma once

#define VK_MOUSE_LEFT	0
#define VK_MOUSE_MIDDLE	2
#define VK_MOUSE_RIGHT	1

class Mouse {
private:
	bool m_usingMouse;
	vector<function<void(int)>> m_scrollEvents;
	struct {
		DWORD time;
		DWORD doubleClickTime;
		DWORD doubleClicked;
		BOOL m_isUpNow;
		bool m_justDown;
	} button_states[5];

	const int m_NOWPERIOD = 100, m_MAXDOWN = 600000, m_DOUBLECLICKPERIOD = 200;

	void ResetButtonState(DWORD button);
public:
	enum {
		NORMAL,
		INVIS = 2,
		HAND_OPEN,
		HAND_CLOSED,
		HAND_MIDDLEFINGER,
		ARROW_LEFT,
		ARROW_RIGHT,
		ARROW_UP,
		ARROW_DOWN,
		ARROW_LEFT_RIGHT,
		ARROW_PLUS,
		ARROW_MINUS
	};

	float m_scrollWheel;
	int m_X, m_Y, m_oldX, m_oldY;
	int m_resX, m_resY;

	void UpdateMouse();
	void ScrollWheel(int i);
	void EnableButton(int key, bool is_up_now);
	bool ButtonDown(DWORD button);
	bool ButtonJustUp(DWORD button);
	bool ButtonJustDown(DWORD button);
	bool ButtonDoubleClicked(DWORD button);
	float GetMouseX();
	float GetMouseY();
	float GetMouseOldX();
	float GetMouseOldY();
	float GetXMovement();
	float GetYMovement();
	Vector2 GetPositionAsVector();

	bool MouseWithin(float x, float y, float width, float height);
	bool MouseWithinCentered(float x, float y, float width, float height);

	void SetCursor(int cursor) { HUD::_SetCursorSprite(cursor); }
	void ResetCursor() { HUD::_SetCursorSprite(0); }

	void registerScrollEvent(function<void(int)> m_callback) {
		m_scrollEvents.push_back(m_callback);
	}

	void ToggleMouse() { m_usingMouse ^= true; }
	bool CanUse();
	bool IsEnabled() { return m_usingMouse; }

};

Mouse* GetMouse();