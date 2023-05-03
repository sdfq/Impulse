#pragma once

class BreakOption : public Option {
private:
	bool m_line;
	void(*m_function)();

public:
	BreakOption() : Option("________________________", true), m_line(true) { }
	BreakOption(String name) : Option(name, true), m_line(false) {}

	BreakOption& addRequirement(bool(*func)()) {
		m_requirement = func;
		return *this;
	}

	BreakOption& addTranslation() {
		m_name.SetHasTranslation(true);
		return *this;
	}

	void Input(int position);
	void Render(int position);
	void RenderSelected(int position);
	void HandleHotkey();

	void setName(String name) {
		m_name.Set(name);
		m_line = false;
	}
	void setLine() { m_line = true;  setName("________________________"); }
};
