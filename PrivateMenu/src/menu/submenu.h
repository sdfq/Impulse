#pragma once

class Submenu {
protected:
	vector<TranslationString> m_strings;
	vector<shared_ptr<Option>> m_options;
	TranslationString m_name;
	Submenu* m_parentSubmenu;

public:
	bool m_canBeSearched;

	virtual ~Submenu();
	Submenu() : m_name(TranslationString("")), m_parentSubmenu(nullptr), m_canBeSearched(false), m_oldCurrentOption(0), m_oldScrollOffset(0) {}

	int m_oldCurrentOption;
	int m_oldScrollOffset;

	vector<shared_ptr<Option>> getOptions() { return m_options; }

	void MenuUpdate(bool withInput);

	virtual void Init();
	virtual void UpdateOnce();
	virtual void Update();
	virtual void FeatureUpdate();

	/*This calls the copy constructor, kinda dirty but very developer friendly*/
	template<typename T, typename = enable_if<is_base_of<Option, T>::value>>
	shared_ptr<T> addOption(T& option) {
		shared_ptr<T> ptr = make_shared<T>(option);
		m_options.push_back(ptr);
		if (option.m_hasHotkey) {
			GetHotkeyManager()->InitHotkey(ptr.get());
		}
		return ptr;
	}

	template<typename T, typename = enable_if<is_base_of<Option, T>::value>>
	shared_ptr<T>& addOption(shared_ptr<T>& option) {
		m_options.push_back(option);
		if (option->m_hasHotkey) {
			GetHotkeyManager()->InitHotkey(option.get());
		}
		return option;
	}

	template<typename T, typename = enable_if<is_base_of<Submenu, T>::value>>
	void setParentSubmenu() {
		m_parentSubmenu = T::GetInstance();
	}

	void setParentSubmenu(Submenu*& sub) {
		m_parentSubmenu = sub;
	}

	Submenu* getParentSubmenu() { return m_parentSubmenu; }

	void addString(String str) { m_strings.push_back(TranslationString(str)); }

	String getString(String str) {
		for (auto& s : m_strings) if (strcmp(str, s.Get()) == 0) return s.Get();
		return va("~r~[~s~%s~r~]", str);
	}

	vector<TranslationString> getStrings() { return m_strings; }


	void setName(String name, bool hasTranslation, bool canBeSearched) {
		m_name.Set(name);
		m_name.SetHasTranslation(hasTranslation);
		m_canBeSearched = canBeSearched;
	}

	TranslationString& getName() { return m_name; }

	/*Clear options from the submenu*/
	void clearOptions() {
		for (auto& option : m_options) {
			if (option->m_hasHotkey)
				GetHotkeyManager()->UnregisterHotkey(option->m_hotkey);
		}
		m_options.clear();
	}

	/*Clear options from a starting offset*/
	void clearOptionsOffset(int offset) {
		if (offset > m_options.size()) return;
		for (int i = offset; i < m_options.size(); i++) {
			if (m_options[i]->m_hasHotkey)
				GetHotkeyManager()->UnregisterHotkey(m_options[i]->m_hotkey);
		}
		m_options.resize(offset);
	}
};