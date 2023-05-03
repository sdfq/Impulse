#pragma once

class UIPlayerInfoComponent : public UIComponent {
private:
	int m_player;
	float m_half;
	float m_whole;
public:
	UIPlayerInfoComponent(int player) : UIComponent(), m_player(player) {}
	UIPlayerInfoComponent() : UIComponent(), m_player(0) {}

	void setParent(UIWindow* parent) {
		m_parent = parent;
		m_parent->m_size.y = 0.448f;
		m_parent->m_size.x = 0.2f;
		m_half = m_parent->m_size.x / 2;
		m_whole = m_parent->m_size.x;
	}
	void setPlayer(int player) { m_player = player; }
	void update();
	void ASyncUpdate();
	void scrollEvent(int scroll) {}
	void render();
	void MapPanel();
	void drawInfo(float x, float width, int yOffset, String name, String value, Texture text = { "", "" }, Color color = { 255, 255, 255, 255 });
	void drawMiddleLine(int yOffset);
	void drawMiddleLineTop(int yOffset);
	void drawMiddleLineBottom(int yOffset);

	map<uint32_t, SocialclubData::RockstarAccount> AccountData;

};