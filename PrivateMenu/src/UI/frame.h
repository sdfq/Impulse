#pragma once

class UIFrame {
private:
	bool m_dragging;
	bool m_resizing;
	UIWindow * m_resizingWindow = nullptr;

	UIWindow * m_currentWindow;
	vector<UIWindow*> m_windows;
	Vector2 m_clickedPos;

	void rearrange(UIWindow* window) {
		m_windows.erase(remove(m_windows.begin(), m_windows.end(), window), m_windows.end());
		m_windows.insert(m_windows.begin(), window);
	}

	void dragUpdate();

public:
	bool m_isHandlingComponent = false;
	UIFrame() : m_dragging(false), m_currentWindow(nullptr) {}

	void addWindow(UIWindow* window, bool fadeIn = true);
	void removeWindow(UIWindow* window);

	void update();
	void ASyncUpdate();
	void scrollEvent(int scroll);
	bool IsDragging() { return m_dragging;  }
	UIWindow* getCurrentWindow() { return m_currentWindow; }
	vector<UIWindow*> getWindows() { return m_windows; }
};