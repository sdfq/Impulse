#include "stdafx.h"
#include "loadLanguageMenu.h"
#include "../languageMenu.h"

using namespace LoadLanguageMenuVars;

namespace LoadLanguageMenuVars {
	Vars vars;
	vector<string> m_languageFiles;

	shared_ptr<ButtonOption> m_addLanguagesButton;

	void LoadConfig() {
		if (GetConfig()->ReadBool("Customization", "LoadLanguage", false)) {
			String language = GetConfig()->ReadString("Customization", "Language", "null");
			if (!strcmp(language, "null") == 0) {
				LanguageMenuVars::LoadLanguage(language);
			}
		}
	}
}

void LoadLanguageMenu::Init() {
	setParentSubmenu<LanguageMenu>();
	setName("Load language", true, false);

	LoadConfig();

	addOption(ToggleOption("Load selected language on startup")
		.addToggle(vars.loadOnStart)
		.addRequirement([] {return GetAuth()->IsVIP(); })
		.addFunction([&] { GetConfig()->WriteBool("Customization", "LoadLanguage", vars.loadOnStart); })
		.addTooltip("Load the selected language on startup"));

	addOption(BreakOption());


	m_addLanguagesButton = addOption(ButtonOption("~c~Add languages to ./Documents/Impulse/Languages")
		.addTooltip("Add languages to ./Documents/Impulse/Languages").addTranslation());
}

/*Update once when submenu is opened*/
void LoadLanguageMenu::UpdateOnce() {}

/*Update while submenu is active*/
void LoadLanguageMenu::Update() {
	static int TIMER;
	static bool shouldUpdate = false;

	vars.loadOnStart = GetConfig()->ReadBool("Customization", "LoadLanguage", false);

	Utils::DoTimedFunction(&TIMER, 2500, [] {shouldUpdate = true; });
	if (shouldUpdate) {
		clearOptionsOffset(2);
		GetConfig()->GetFilesFromDirectory(m_languageFiles, GetConfig()->GetLanguagesPath(), ".json");
		if (!m_languageFiles.empty()) {
			for (string& language : m_languageFiles) {
				addOption(ButtonOption(language.c_str())
					.addFunction([&] {
					GetConfig()->WriteString("Customization", "Language", language.c_str());
					LanguageMenuVars::LoadLanguage(language.c_str()); })
					.addTooltip(language.c_str()));
			}
		} else {
			addOption(m_addLanguagesButton);
		}
		shouldUpdate = false;
	}
}

/*Background update*/
void LoadLanguageMenu::FeatureUpdate() {}

/*Singleton*/
LoadLanguageMenu* _instance;
LoadLanguageMenu* LoadLanguageMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new LoadLanguageMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
LoadLanguageMenu::~LoadLanguageMenu() { delete _instance; }