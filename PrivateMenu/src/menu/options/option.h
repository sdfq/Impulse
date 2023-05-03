#pragma once

class Option {
protected:
	function<bool()> m_requirement;

	TranslationString m_name;
	TranslationString m_tooltip;
	bool m_isBreak;
	bool m_visible;
	uint8_t m_hoverTimer;

public:
	bool m_canBeSaved;
	bool m_hasHotkey;
	int m_hotkey;

	Option() : m_name(TranslationString("")), m_tooltip(TranslationString("")), m_hotkey(-1), m_hasHotkey(false), m_requirement([] {return true; }), m_canBeSaved(false), m_isBreak(false), m_visible(true), m_hoverTimer(0) {}
	Option(String name) : m_name(TranslationString(name)), m_tooltip(TranslationString("")), m_hotkey(-1), m_hasHotkey(false), m_requirement([] {return true; }), m_canBeSaved(false), m_isBreak(false), m_visible(true), m_hoverTimer(0) {}
	Option(String name, bool isBreak) : m_name(TranslationString(name)), m_tooltip(TranslationString("")), m_hotkey(-1), m_hasHotkey(false), m_requirement([] {return true; }), m_canBeSaved(false), m_isBreak(isBreak), m_visible(true), m_hoverTimer(0) {}

	Option(const Option& src) : m_name(src.m_name), m_tooltip(src.m_tooltip) {
		*this = src;
	}

	virtual void Input(int position);
	virtual void Render(int position);
	virtual void RenderSelected(int position);
	virtual void HandleHotkey();
	virtual void WriteTranslation(json& jsonOb, bool def);
	virtual void ReadTranslation(json& jsonOb);
	virtual void ResetTranslation();

	virtual void setName(String name) {
		m_name.Set(name);
	}

	template<typename T>
	bool IsOfType() {
		return dynamic_cast<const T*>(this) != nullptr;
	}

	void setVisible(bool visible) { m_visible = visible; }

	TranslationString& getName() { return m_name; }
	TranslationString& getTooltip() { return m_tooltip; }

	bool isBreak() { return m_isBreak; }
	bool isVisible() { return m_visible && m_requirement(); }
};

