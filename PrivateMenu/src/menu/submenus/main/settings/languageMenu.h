#pragma once
#include "menu/submenu.h"

class LanguageMenu : public Submenu {
public:
	static LanguageMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	LanguageMenu() : Submenu() {}
	~LanguageMenu();
};

namespace LanguageMenuVars
{
	extern vector<TranslationString*> g_translationTable;
	void LoadLanguage(String path);
}