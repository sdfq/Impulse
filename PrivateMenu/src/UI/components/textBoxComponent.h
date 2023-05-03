#pragma once
#include "menu/submenus/main/session/data management/dataMenu.h"

class UITextBoxComponent : public UIComponent {
private:
	int m_linesToDisplay;
	int m_scroll;
	bool m_autoScroll;
	float m_textSize;
	bool m_dragging;
	bool m_textSelected;
	string m_inputText;
	bool m_blink;
	function<void(String)> m_callback;

public:
	UITextBoxComponent() : UIComponent(), m_linesToDisplay(0), m_callback([](String text) {}){}
	UITextBoxComponent(int linesToDisplay, function<void(String)> callback) : UIComponent(), m_linesToDisplay(linesToDisplay), m_textSize(0.022f), m_scroll(0), m_autoScroll(true), m_callback(callback) {}

	void setParent(UIWindow* parent) {
		m_parent = parent;
		m_parent->m_size.y = m_linesToDisplay * m_textSize + GetRenderer()->m_dialogHeaderHeight + GetRenderer()->m_dialogFooterHeight;
	}

	vector<string> m_lines;

	vector<string> getLines() const
	{
		return m_lines;
	}

	void addLine(string line) {
		replace(line.begin(), line.end(), '\n', ' ');
		m_lines.push_back(line);
		DataMenuVars::LogLine(line.c_str());
		if (m_autoScroll && m_scroll == m_lines.size() - m_linesToDisplay - 1) m_scroll = m_lines.size() - m_linesToDisplay;
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

	void update();
	void ASyncUpdate() {

	}
	void scrollEvent(int scroll) {
		m_scroll -= (int)scroll;
		Utils::Clamp(&m_scroll, 0, m_lines.size() - m_linesToDisplay);
	}

	void render();
};