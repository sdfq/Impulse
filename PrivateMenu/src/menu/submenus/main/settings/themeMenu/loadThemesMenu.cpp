#include "stdafx.h"
#include "loadThemesMenu.h"
#include "../themeMenu.h"

using namespace LoadThemesMenuVars;

namespace LoadThemesMenuVars {
	Vars vars;
	vector<string> m_themesFiles;

	shared_ptr<ButtonOption> m_addThemesButton;

	void LoadTheme(String fileName) {
		ifstream i(va("%s/%s.json", GetConfig()->GetThemesPath(), fileName));
		json jsonOb;
		i >> jsonOb;

		vector<int> temp = jsonGet<vector<int>>(jsonOb["Colors"], "Primary", GetRenderer()->m_cPrimary.getAsVector());
		GetRenderer()->m_cPrimary = { temp[0], temp[1], temp[2], temp[3] };

		temp = jsonGet<vector<int>>(jsonOb["Colors"], "Outline", GetRenderer()->m_cOutline.getAsVector());
		GetRenderer()->m_cOutline = { temp[0], temp[1], temp[2], temp[3] };

		temp = jsonGet<vector<int>>(jsonOb["Colors"], "Scroller", GetRenderer()->m_cSelection.getAsVector());
		GetRenderer()->m_cSelection = { temp[0], temp[1], temp[2], temp[3] };

		temp = jsonGet<vector<int>>(jsonOb["Colors"], "SubHeader", GetRenderer()->m_cSubHeader.getAsVector());
		GetRenderer()->m_cSubHeader = { temp[0], temp[1], temp[2], temp[3] };

		temp = jsonGet<vector<int>>(jsonOb["Colors"], "SubHeaderTitle", GetRenderer()->m_cTitle.getAsVector());
		GetRenderer()->m_cTitle = { temp[0], temp[1], temp[2], temp[3] };

		temp = jsonGet<vector<int>>(jsonOb["Colors"], "Text", GetRenderer()->m_cOption.getAsVector());
		GetRenderer()->m_cOption = { temp[0], temp[1], temp[2], temp[3] };

		GetRenderer()->m_textFont = jsonGet<int>(jsonOb["Text"], "Font", GetRenderer()->m_textFont);
		GetRenderer()->m_textSize = jsonGet<float>(jsonOb["Text"], "Size", GetRenderer()->m_textSize);

		GetRenderer()->m_colorlessToggles = jsonGet<bool>(jsonOb["Misc"], "ColorlessToggles", GetRenderer()->m_colorlessToggles);
		GetRenderer()->m_animatedArrows = jsonGet<bool>(jsonOb["Misc"], "AnimatedArrows", GetRenderer()->m_animatedArrows);
		GetRenderer()->m_arrows = jsonGet<int>(jsonOb["Misc"], "Arrows", GetRenderer()->m_arrows);

		GetRenderer()->m_width = jsonGet<float>(jsonOb["Menu"], "Width", GetRenderer()->m_width);
		GetRenderer()->m_optionHeight = jsonGet<float>(jsonOb["Menu"], "OptionHeight", GetRenderer()->m_optionHeight);
		GetMenu()->m_position.x = jsonGet<float>(jsonOb["Menu"], "XPosition", GetMenu()->m_position.x);
		GetMenu()->m_position.y = jsonGet<float>(jsonOb["Menu"], "YPosition", GetMenu()->m_position.y);

		GetWindowManager()->m_playerInfo.m_position.x = jsonGet<float>(jsonOb["Menu"], "WindowXPosition", GetWindowManager()->m_playerInfo.m_position.x);
		GetWindowManager()->m_playerInfo.m_position.y = jsonGet<float>(jsonOb["Menu"], "WindowYPosition", GetWindowManager()->m_playerInfo.m_position.y);

		GetWindowManager()->m_vehicleInfo.m_position.x = jsonGet<float>(jsonOb["Menu"], "VehicleImgXPosition", GetWindowManager()->m_vehicleInfo.m_position.x);
		GetWindowManager()->m_vehicleInfo.m_position.y = jsonGet<float>(jsonOb["Menu"], "VehicleImgYPosition", GetWindowManager()->m_vehicleInfo.m_position.y);

		ThemeMenuVars::SetHeader(jsonGet<int>(jsonOb, "Header", 0));

		i.close();
	}

	void LoadConfig() {
		if (GetConfig()->ReadBool("Customization", "LoadTheme", false)) {
			String theme = GetConfig()->ReadString("Customization", "Theme", "null");
			if (!strcmp(theme, "null") == 0) {
				LoadTheme(theme);
			}
		}
	}
}

void LoadThemesMenu::Init() {
	setParentSubmenu<ThemeMenu>();
	setName("Load themes", true, false);

	//LoadConfig();

	addOption(ToggleOption("Load selected theme on startup")
		.addToggle(vars.loadOnStart)
		.addRequirement([] {return GetAuth()->IsVIP(); })
		.addFunction([&] { GetConfig()->WriteBool("Customization", "LoadTheme", vars.loadOnStart); })
		.addTooltip("Load the selected theme on startup"));

	addOption(BreakOption());

	m_addThemesButton = addOption(ButtonOption("~c~Add themes to ./Documents/Impulse/Themes")
		.addTooltip("Add themes to ./Documents/Impulse/Themes").addTranslation());
}

/*Update once when submenu is opened*/
void LoadThemesMenu::UpdateOnce() {
	LoadConfig();
}

/*Update while submenu is active*/
void LoadThemesMenu::Update() {
	static int TIMER;
	static bool shouldUpdate = false;

	vars.loadOnStart = GetConfig()->ReadBool("Customization", "LoadTheme", false);

	Utils::DoTimedFunction(&TIMER, 2500, [] {shouldUpdate = true; });
	if (shouldUpdate) {
		clearOptionsOffset(2);
		GetConfig()->GetFilesFromDirectory(m_themesFiles, GetConfig()->GetThemesPath(), ".json");
		if (!m_themesFiles.empty()) {
			for (string& theme : m_themesFiles) {
				addOption(ButtonOption(theme.c_str())
					.addFunction([&] {
					GetConfig()->WriteString("Customization", "Theme", theme.c_str());
					LoadTheme(theme.c_str()); })
					.addTooltip(theme.c_str()));
			}
		} else {
			addOption(m_addThemesButton);
		}
		shouldUpdate = false;
	}
}

/*Background update*/
void LoadThemesMenu::FeatureUpdate() {}

/*Singleton*/
LoadThemesMenu* _instance;
LoadThemesMenu* LoadThemesMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new LoadThemesMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
LoadThemesMenu::~LoadThemesMenu() { delete _instance; }