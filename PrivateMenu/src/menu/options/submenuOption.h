#pragma once

class Submenu;

class SubmenuOption : public Option {
public:
	function<void(SubmenuOption*)> m_onUpdate;
	function<float(int)> m_onDraw;
	function<void()> m_currentOp;
	function<void()> m_function;
	Submenu * m_submenu;

	SubmenuOption(String name) : Option(name), m_function([] {}), m_onDraw([](int index) {return 0.0f; }), m_onUpdate([](SubmenuOption* option) {}), m_submenu(nullptr), m_currentOp([] {}) {}

	template<typename T, typename = enable_if<is_base_of<Submenu, T>::value>>
	SubmenuOption& addSubmenu() {
		m_submenu = T::GetInstance();
		//LOG_PRINT("Option: %s | To Submenu: %s | Null = %s", m_name, m_submenu->getName(), m_submenu == NULL ? "yes" : "no");
		return *this;
	}

	SubmenuOption& addSubmenu(Submenu* submenu) {
		m_submenu = submenu;
		return *this;
	}

	SubmenuOption& addFunction(function<void()> func) {
		m_function = func;
		return *this;
	}

	SubmenuOption& addOnDraw(function<float(int)> func) {
		m_onDraw = func;
		return *this;
	}

	SubmenuOption& addRequirement(function<bool()> func) {
		m_requirement = func;
		return *this;
	}

	SubmenuOption& addOnUpdate(function<void(SubmenuOption*)> func) {
		m_onUpdate = func;
		return *this;
	}

	SubmenuOption& addCurrentOp(function<void()> func) {
		m_currentOp = func;
		return *this;
	}

	SubmenuOption& setVisible(bool visible) {
		m_visible = visible;
		return *this;
	}

	SubmenuOption& addHotkey() {
		m_hasHotkey = true;
		return *this;
	}

	SubmenuOption& addTranslation() {
		m_name.SetHasTranslation(true);
		m_tooltip.SetHasTranslation(true);
		return *this;
	}

	SubmenuOption& addName(String name) {
		m_name.Set(name);
		return *this;
	}

	SubmenuOption& addTooltip(String tooltip) {
		m_tooltip.Set(tooltip);
		return *this;
	}

	void Input(int position);
	void Render(int position);
	void RenderSelected(int position);
	void HandleHotkey();
};
