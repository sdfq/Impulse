#pragma once

class UISystemdataComponent : public UIComponent {
private:
	float m_half;
	float m_whole;
public:
	void setParent(UIWindow* parent) {
		m_parent = parent;
		m_parent->m_size.y = 0.25f;
		m_parent->m_size.x = 0.2f;
		m_half = m_parent->m_size.x / 2;
		m_whole = m_parent->m_size.x;
	}
	void update();
	void ASyncUpdate();
	void scrollEvent(int scroll) {}
	void render();

	void drawInfo(float x, float width, int yOffset, String name, String value, Texture text = { "", "" }, Color color = { 255, 255, 255, 255 });
	void drawMiddleLine(int yOffset);
	void drawMiddleLineTop(int yOffset);
	void drawMiddleLineBottom(int yOffset);
};