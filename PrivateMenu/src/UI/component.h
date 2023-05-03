#pragma once

class UIWindow;
class UIComponent {
protected:
	UIWindow * m_parent;
public:
	UIComponent() : m_parent(nullptr) {}
	void setParent(UIWindow* parent) { m_parent = parent; }
	virtual void update() = 0;
	virtual void ASyncUpdate() = 0;
	virtual void render() = 0;
	virtual void scrollEvent(int scroll) = 0;
};