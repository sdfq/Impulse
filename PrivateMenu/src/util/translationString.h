#pragma once

class TranslationString {
private:
	char m_original[128];
	char m_mapped[128];
	bool m_hasTranslation;

public:
	TranslationString::TranslationString(String original, bool hasTranslation = false, bool reg = false) {
		Set(original);
		m_hasTranslation = hasTranslation;
		if (reg)Register();
	}

	TranslationString(const TranslationString& src) {
		*this = src;
	}

	String GetOriginal() { return m_original; }
	String Get() {
		return m_hasTranslation ? m_mapped : m_original;
	}
	void Register();
	void SetHasTranslation(bool has) { m_hasTranslation = has; }
	bool HasTranslation() { return m_hasTranslation; }

	void SetMapped(String s) {
		strcpy(m_mapped, s);
	}
	void Reset() { SetMapped(m_original); }
	void Set(String original) {
		strcpy(m_original, original);
		SetMapped(m_original);
	}
};