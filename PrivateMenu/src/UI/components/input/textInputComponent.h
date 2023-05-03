#pragma once

class UITextInputComponent : public UIComponent {
private:
	bool m_textSelected;
	bool m_blink;
	string m_input;
	function<void(String)> m_callback;
public:
	UITextInputComponent(int player) : UIComponent(), m_textSelected(true), m_blink(false), m_input(nullptr) {}
	UITextInputComponent() : UIComponent() {}

	void setParent(UIWindow* parent) {
		m_parent = parent;
		m_parent->setCanBeClosed(true);
		m_parent->setCanBeMinimized(true);
		m_textSelected = true;
	}

	void set(String name, function<void(String)> callback) {
		m_callback = callback;
		m_parent->setName(name);
	}
	void update();
	void ASyncUpdate();
	void scrollEvent(int scroll) {}
	void render();
};