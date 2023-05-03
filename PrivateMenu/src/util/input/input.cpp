#include "stdafx.h"

WNDPROC Input::m_windowProc;
set<Input::KeyboardFunction> Input::g_keyboardFunctions;

bool Input::Initialize() {
	m_windowProc = (WNDPROC)SetWindowLongPtrA(Backend::GetWindow(), GWLP_WNDPROC, (__int3264)(LONG_PTR)WindowProcess);

	if (m_windowProc == nullptr) return false;
	LOG_DEBUG("[Hooking] IH initialized");
	return true;
}

LRESULT APIENTRY Input::WindowProcess(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) {
		case WM_SIZE: return DefWindowProc(hwnd, uMsg, wParam, lParam);
		case WM_LBUTTONDOWN:	GetMouse()->EnableButton(0, true); break;
		case WM_LBUTTONUP:		GetMouse()->EnableButton(0, false); break;
		case WM_RBUTTONDOWN:	GetMouse()->EnableButton(1, true); break;
		case WM_RBUTTONUP:		GetMouse()->EnableButton(1, false); break;
		case WM_MBUTTONDOWN:	GetMouse()->EnableButton(2, true); break;
		case WM_MBUTTONUP:		GetMouse()->EnableButton(2, false); break;
		case WM_MOUSEWHEEL:		GetMouse()->ScrollWheel(GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? 1 : -1); break;
		case WM_MOUSEMOVE:		GetMouse()->m_X = GET_X_LPARAM(lParam); GetMouse()->m_Y = GET_Y_LPARAM(lParam); break;
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP: {
			GetKeyboard()->OnKeyboardMessage((DWORD)wParam, lParam & 0xFFFF, (lParam >> 16) & 0xFF, (lParam >> 24) & 1, (uMsg == WM_SYSKEYDOWN || uMsg == WM_SYSKEYUP), (lParam >> 30) & 1, (uMsg == WM_SYSKEYUP || uMsg == WM_KEYUP));
			auto functions = g_keyboardFunctions; for (auto & function : functions) function((DWORD)wParam, lParam & 0xFFFF, (lParam >> 16) & 0xFF, (lParam >> 24) & 1, (uMsg == WM_SYSKEYDOWN || uMsg == WM_SYSKEYUP), (lParam >> 30) & 1, (uMsg == WM_SYSKEYUP || uMsg == WM_KEYUP));
			break;
		}
	}
	return CallWindowProc(m_windowProc, hwnd, uMsg, wParam, lParam);
}

void Input::Cleanup() {
	SetWindowLongPtrA(Backend::GetWindow(), GWLP_WNDPROC, (LONG_PTR)m_windowProc);
	LOG_DEBUG("[Hooking] Disabled IH");
}
