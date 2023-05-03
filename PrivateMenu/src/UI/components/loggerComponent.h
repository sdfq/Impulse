#pragma once

class UILoggerComponent : public UIComponent {
private:
	int m_linesToDisplay;
	int m_scroll;
	bool m_autoScroll;
	float m_textSize;
	bool m_dragging;
	function<void()> m_updateCallback;

public:
	UILoggerComponent() : UIComponent(), m_linesToDisplay(0) {}
	UILoggerComponent(int linesToDisplay) : UIComponent(), m_linesToDisplay(linesToDisplay), m_textSize(0.022f), m_scroll(0), m_autoScroll(true), m_updateCallback([] {}) {}

	void setParent(UIWindow* parent) {
		m_parent = parent;
		m_parent->m_size.y = m_linesToDisplay * m_textSize + GetRenderer()->m_dialogHeaderHeight + GetRenderer()->m_dialogFooterHeight;
	}

	vector<string> m_lines;

	void addLine(string line) {
		replace(line.begin(), line.end(), '\n', ' ');
		m_lines.push_back(line);
		if (m_autoScroll && m_scroll == m_lines.size() - m_linesToDisplay - 1) m_scroll = m_lines.size() - m_linesToDisplay;
	}

	void clear() {
		m_lines.clear();
	}

	void addLine(int color, String line) {
		using namespace ConsoleForeground;
		string str = line;
		switch (color) {
			case BLACK: str.insert(0, "~u~"); break;
			case DARKGRAY: str.insert(0, "~m~"); break;
			case GRAY: str.insert(0, "~c~"); break;
			case WHITE: str.insert(0, "~w~"); break;
			case DARKGREEN: case GREEN: str.insert(0, "~g~"); break;
			case DARKYELLOW: case YELLOW: str.insert(0, "~y~"); break;
			case DARKBLUE: case DARKCYAN: case BLUE: case CYAN: str.insert(0, "~b~"); break;
			case DARKRED: case RED: case DARKMAGENTA: case MAGENTA: str.insert(0, "~r~"); break;
			default: break;
		}
		addLine(str);
	}

	void setUpdateCallback(function<void()> callback) {
		m_updateCallback = callback;
	}

	void update() {}
	void ASyncUpdate() {
		m_updateCallback();
	}

	void scrollEvent(int scroll) {
		m_scroll -= (int)scroll;
		Utils::Clamp(&m_scroll, 0, m_lines.size() - m_linesToDisplay);
	}

	void render();
};