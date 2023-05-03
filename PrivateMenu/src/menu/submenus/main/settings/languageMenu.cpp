#include "stdafx.h"
#include "languageMenu.h"
#include "../settingsMenu.h"
#include "languageMenu/loadLanguageMenu.h"

using namespace LanguageMenuVars;

namespace LanguageMenuVars {
	vector<TranslationString*> g_translationTable;

	void GenerateDefault() {
		String file = va("%s/%s.json", GetConfig()->GetLanguagesPath(), "Generated");
		ofstream i(file);

		json jsonOb =
		{
			{ "font", -1 }
		};

		for (auto& submenu : GetSubmenuHandler()->GetSubmenus()) {
			if (submenu) {
				String subName = submenu->getName().GetOriginal();
				for (auto& option : submenu->getOptions()) {
					if (option->getName().HasTranslation() && strcmp(option->getName().GetOriginal(), "") != 0)
						jsonOb["strings"][subName][option->getName().GetOriginal()] = option->getName().GetOriginal();
					if (option->getTooltip().HasTranslation() && strcmp(option->getTooltip().GetOriginal(), "") != 0)
						jsonOb["strings"][subName][option->getTooltip().GetOriginal()] = option->getTooltip().GetOriginal();
					option->WriteTranslation(jsonOb["strings"][subName], true);
				}
				if (submenu->getName().HasTranslation()) {
					jsonOb["strings"]["submenu names"][submenu->getName().GetOriginal()] = submenu->getName().GetOriginal();
				}
				for (auto& str : submenu->getStrings()) jsonOb["strings"][subName][str.Get()] = str.Get();
			}
		}
		for (auto& str : g_translationTable) jsonOb["strings"]["misc"][str->Get()] = str->Get();

		for (auto& button : GetScreenPanel()->GetButtons()) {
			if (button.m_name.HasTranslation()) jsonOb["strings"]["panel"][button.m_name.Get()] = button.m_name.Get();
		}
		for (auto& window : GetWindowManager()->GetFrame()->getWindows()) {
			if (window->getName().HasTranslation()) jsonOb["strings"]["windows"][window->getName().Get()] = window->getName().Get();
		}
		i << setw(4) << jsonOb;
		i.close();

	}

	void Reset() {
		for (auto& submenu : GetSubmenuHandler()->GetSubmenus()) {
			String subName = submenu->getName().GetOriginal();
			for (auto& option : submenu->getOptions()) {
				option->getName().Reset();
				option->getTooltip().Reset();
				option->ResetTranslation();
			}
			if (submenu->getName().HasTranslation()) {
				submenu->getName().Reset();
			}
			for (auto& str : submenu->getStrings()) str.Reset();
		}
		for (auto& str : g_translationTable) str->Reset();

		for (auto& button : GetScreenPanel()->GetButtons()) {
			if (button.m_name.HasTranslation()) button.m_name.Reset();
		}

		for (auto& window : GetWindowManager()->GetFrame()->getWindows()) {
			if (window->getName().HasTranslation()) window->getName().Reset();
		}
	}

	void GenerateTest() {
		String file = va("%s/%s.json", GetConfig()->GetLanguagesPath(), "Test");
		ofstream i(file);

		json jsonOb =
		{
			{ "font", -1 }
		};

		for (auto& submenu : GetSubmenuHandler()->GetSubmenus()) {
			String subName = submenu->getName().GetOriginal();
			for (auto& option : submenu->getOptions()) {
				if (option->getName().HasTranslation() && strcmp(option->getName().GetOriginal(), "") != 0)
					jsonOb["strings"][subName][option->getName().GetOriginal()] = "Test";
				if (option->getTooltip().HasTranslation() && strcmp(option->getTooltip().GetOriginal(), "") != 0)
					jsonOb["strings"][subName][option->getTooltip().GetOriginal()] = "Test";
				option->WriteTranslation(jsonOb["strings"][subName], false);
			}
			if (submenu->getName().HasTranslation()) {
				jsonOb["strings"]["submenu names"][submenu->getName().GetOriginal()] = "Test";
			}
			for (auto& str : submenu->getStrings()) jsonOb["strings"][subName][str.Get()] = "Test";
		}
		for (auto& str : g_translationTable) jsonOb["strings"]["misc"][str->Get()] = "Test";

		for (auto& button : GetScreenPanel()->GetButtons()) {
			if (button.m_name.HasTranslation()) jsonOb["strings"]["panel"][button.m_name.Get()] = "Test";
		}

		for (auto& window : GetWindowManager()->GetFrame()->getWindows()) {
			if (window->getName().HasTranslation()) jsonOb["strings"]["windows"][window->getName().Get()] = "Test";
		}
		i << setw(4) << jsonOb;
		i.close();
	}

	void LoadLanguage(String fileName) {
		try {
			ifstream i(va("%s/%s.json", GetConfig()->GetLanguagesPath(), fileName));
			if (i.fail()) throw "Failed";
			json jsonOb = json::parse(i);
			const auto font = jsonGet<int>(jsonOb, "font", -1);
			if (font != -1) GetRenderer()->m_textFont = font;
			for (auto& submenu : GetSubmenuHandler()->GetSubmenus()) {
				String subName = submenu->getName().GetOriginal();
				for (auto& option : submenu->getOptions()) {
					option->getName().SetMapped(jsonGet<string>(jsonOb["strings"][subName], option->getName().GetOriginal(), option->getName().GetOriginal()).c_str());
					option->getTooltip().SetMapped(jsonGet<string>(jsonOb["strings"][subName], option->getTooltip().GetOriginal(), option->getTooltip().GetOriginal()).c_str());
					option->ReadTranslation(jsonOb["strings"][subName]);
				}
				if (submenu->getName().HasTranslation()) {
					submenu->getName().Reset();
				}
				for (auto& str : submenu->getStrings()) str.SetMapped(jsonGet<string>(jsonOb["strings"][subName], str.Get(), str.Get()).c_str());
			}
			for (auto& str : g_translationTable) str->SetMapped(jsonGet<string>(jsonOb["strings"]["misc"], str->Get(), str->Get()).c_str());

			for (auto& button : GetScreenPanel()->GetButtons()) {
				if (button.m_name.HasTranslation()) button.m_name.SetMapped(jsonGet<string>(jsonOb["strings"]["panel"], button.m_name.Get(), button.m_name.Get()).c_str());
			}

			for (auto& window : GetWindowManager()->GetFrame()->getWindows()) {
				if (window->getName().HasTranslation()) window->getName().SetMapped(jsonGet<string>(jsonOb["strings"]["windows"], window->getName().Get(), window->getName().Get()).c_str());
			}
		} catch (json::parse_error& e) {
			if (e.id == 101) {
				GetRenderer()->NotifyBottom("Failed to load translation file. Make sure it's in UTF-8 format");
				LOG_PRINT("Failed to load translation file. Make sure it's encoded in UTF-8");
			} else GetRenderer()->NotifyBottom(va("Failed to load translation file: %d", e.id));
		} catch (...) { GetRenderer()->NotifyBottom("Failed to load translation file"); }
	}
}

void LanguageMenu::Init() {
	setParentSubmenu<SettingsMenu>();
	setName("Languages", true, true);

	addOption(ButtonOption("Generate empty language file")
		.addFunction([] {GetThreadPool()->DoJob([] {GenerateDefault(); GetFiberPool()->DoJob([] {GetRenderer()->NotifyMap("Generated language file"); }); }); })
		.addTooltip("Generate an empty language file in ./Documents/Impulse/Languages").addTranslation().addHotkey());

	//addOption(ButtonOption("Generate test")
	//	.addFunction([] {GetThreadPool()->DoJob([] {GenerateTest(); }); })
	//	.addTooltip("Generate a language file filled with \"test\"").addTranslation());

	addOption(ButtonOption("Reset language")
		.addFunction([] {GetThreadPool()->DoJob([] {Reset(); GetRenderer()->NotifyMap("Reset language"); }); })
		.addTooltip("Reset language to English").addTranslation().addHotkey());

	addOption(SubmenuOption("Load languages")
		.addSubmenu<LoadLanguageMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Load saved languages").addHotkey());
}

/*Update once when submenu is opened*/
void LanguageMenu::UpdateOnce() {}

/*Update while submenu is active*/
void LanguageMenu::Update() {}

/*Background update*/
void LanguageMenu::FeatureUpdate() {}

/*Singleton*/
LanguageMenu* _instance;
LanguageMenu* LanguageMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new LanguageMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
LanguageMenu::~LanguageMenu() {
	for (auto& t : g_translationTable) delete t;
	delete _instance;
}