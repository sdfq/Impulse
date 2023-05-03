#pragma once

class ToggleOption : public Option {
private:
	function<void(ToggleOption*)> m_onUpdate;
	function<void()> m_currentOp;
	function<void()> m_function;
	bool* m_bool;

public:

	ToggleOption(String name) : Option(name), m_function([] {}), m_onUpdate([](ToggleOption* option) {}), m_bool(nullptr), m_currentOp([] {}) {}

	ToggleOption& addToggle(void(*func)()) {
		m_function = func;
		return *this;
	}

	ToggleOption &addToggle(bool& toggle) {
		m_bool = &toggle;
		return *this;
	}

	ToggleOption& addHotkey() {
		m_hasHotkey = true;
		return *this;
	}

	ToggleOption& canBeSaved() {
		m_canBeSaved = true;
		if (SimpleIsValidAddress(m_bool) && m_requirement()) *m_bool = GetConfig()->ReadBool("Toggles", m_name.GetOriginal(), *m_bool);
		return *this;
	}

	ToggleOption& addTranslation() {
		m_name.SetHasTranslation(true);
		m_tooltip.SetHasTranslation(true);
		return *this;
	}

	ToggleOption& addFunction(function<void()> func) {
		m_function = func;
		return *this;
	}

	ToggleOption& addRequirement(function<bool()> func) {
		m_requirement = func;
		return *this;
	}

	ToggleOption& addOnUpdate(function<void(ToggleOption*)> update) {
		m_onUpdate = update;
		return *this;
	}

	ToggleOption& addOnUpdate(function<void()> update) {
		m_onUpdate = [=](ToggleOption* option) {update(); };
		return *this;
	}

	ToggleOption& addCurrentOp(function<void()> func) {
		m_currentOp = func;
		return *this;
	}

	ToggleOption& addTooltip(String tooltip) {
		m_tooltip.Set(tooltip);
		return *this;
	}

	void Input(int position);
	void Render(int position);
	void RenderSelected(int position);
	void HandleHotkey();
};
