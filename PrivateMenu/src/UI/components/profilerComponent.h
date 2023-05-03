#pragma once

class UIProfilerComponent : public UIComponent {
private:
	vector<ProfileEntry> m_entries;
	int m_linesToDisplay;
	int m_scroll;
	float m_textSize;
	bool m_dragging;

public:
	UIProfilerComponent() : UIComponent(), m_linesToDisplay(0) {}
	UIProfilerComponent(int linesToDisplay) : UIComponent(), m_linesToDisplay(linesToDisplay), m_textSize(0.022f), m_scroll(0) {}

	void setParent(UIWindow* parent) {
		m_parent = parent;
		m_parent->m_size.x = 0.35f;
		m_parent->m_size.y = m_linesToDisplay * m_textSize + GetRenderer()->m_dialogHeaderHeight + GetRenderer()->m_dialogFooterHeight;
		m_parent->m_renderName = false;
	}

	void update() {}
	void ASyncUpdate() {}

	void scrollEvent(int scroll) {
		m_scroll -= (int)scroll;
		Utils::Clamp(&m_scroll, 0, m_entries.size() - m_linesToDisplay);
	}

	void render();
};