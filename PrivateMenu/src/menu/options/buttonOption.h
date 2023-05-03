#pragma once

class ButtonOption : public Option {
private:
	function<void(ButtonOption*)> m_onUpdate;
	function<void()> m_function;
	function<void()> m_currentOp;
public:

	ButtonOption(String name) : Option(name), m_function([] {}), m_onUpdate([](ButtonOption* option) {}), m_currentOp([] {}) {}


	ButtonOption& addFunction(function<void()> func) {
		m_function = func;
		return *this;
	}

	ButtonOption& addRequirement(bool(*func)()) {
		m_requirement = func;
		return *this;
	}

	ButtonOption& addOnUpdate(function<void(ButtonOption*)> func) {
		m_onUpdate = func;
		return *this;
	}

	ButtonOption& addCurrentOp(function<void()> func) {
		m_currentOp = func;
		return *this;
	}

	ButtonOption& addHotkey() {
		m_hasHotkey = true;
		return *this;
	}

	ButtonOption& addTranslation() {
		m_name.SetHasTranslation(true);
		m_tooltip.SetHasTranslation(true);
		return *this;
	}

	ButtonOption& addTooltip(String tooltip) {
		m_tooltip.Set(tooltip);
		return *this;
	}

	void Input(int position);
	void Render(int position);
	void RenderSelected(int position);
	void HandleHotkey();
};
