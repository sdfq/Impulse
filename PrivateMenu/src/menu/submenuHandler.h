#pragma once

class SubmenuHandler {
private:

	Submenu * m_mainSubmenu;
	Submenu* m_currentSubmenu;
	Submenu* m_previousSubmenu;
	Submenu* m_nextSubmenu;

	int m_nextCurrentOption;
	int m_nextScrollOffset;

	vector<Submenu*> m_submenus;
public:
	void Init();
	void Update(bool withInput);
	void ASyncUpdate();

	void addSubmenu(Submenu* submenu) { m_submenus.push_back(submenu); }
	int GetTotalOptions() { return m_totalOptions; }
	void SetSubmenu(Submenu* submenu);
	void SetSubmenuMain();
	void SetSubPrevious(bool resetPosition = false);
	Submenu* GetCurrentSubmenu() { return m_currentSubmenu; }
	Submenu* GetPreviousSubmenu() { return m_previousSubmenu; };
	vector<Submenu*> GetSubmenus() { return m_submenus; }

	template<typename T>
	bool IsCurrentSubmenuOfType() {
		return dynamic_cast<const T*>(GetCurrentSubmenu()) != nullptr;
	}

	int m_totalOptions;
	int m_currentOptionWithoutBreaks;
	int m_totalOptionsWithoutBreaks;
};

SubmenuHandler* GetSubmenuHandler();