#pragma once

class ColorOption : public Option {
private:
	function<void(ColorOption*)> m_onUpdate;
	function<void()> m_currentOp;
	function<void()> m_function;
	Color* m_color;
public:

	ColorOption(String name) : Option(name), m_function([] {}), m_onUpdate([](ColorOption* option) {}), m_color(nullptr), m_currentOp([] {}) {}


	ColorOption& addColor(Color& color) {
		m_color = &color;
		return *this;
	}

	ColorOption& addFunction(function<void()> func) {
		m_function = func;
		return *this;
	}

	ColorOption& addRequirement(bool(*func)()) {
		m_requirement = func;
		return *this;
	}

	ColorOption& addOnUpdate(function<void(ColorOption*)> func) {
		m_onUpdate = func;
		return *this;
	}

	ColorOption& addOnUpdate(function<void()> update) {
		m_onUpdate = [=](ColorOption* option) {update(); };
		return *this;
	}

	ColorOption& addCurrentOp(function<void()> func) {
		m_currentOp = func;
		return *this;
	}

	ColorOption& addHotkey() {
		m_hasHotkey = true;
		return *this;
	}

	ColorOption& addTranslation() {
		m_name.SetHasTranslation(true);
		m_tooltip.SetHasTranslation(true);
		return *this;
	}

	ColorOption& canBeSaved() {
		m_canBeSaved = true;
		if (SimpleIsValidAddress(m_color) && m_requirement()) GetConfig()->ReadColor("Colors", m_name.GetOriginal(), m_color);
		return *this;
	}

	ColorOption& addTooltip(String tooltip) {
		m_tooltip.Set(tooltip);
		return *this;
	}

	void GetInput();
	void Input(int position);
	void Render(int position);
	void RenderSelected(int position);
	void HandleHotkey();
};
