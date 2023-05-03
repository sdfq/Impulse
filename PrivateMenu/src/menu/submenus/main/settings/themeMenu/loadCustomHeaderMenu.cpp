#include "stdafx.h"
#include "loadCustomHeaderMenu.h"
#include "../themeMenu.h"

using namespace LoadCustomHeaderMenuVars;

namespace LoadCustomHeaderMenuVars {
	Vars vars;



	void LoadConfig() {
		vars.customYTDHeaderNames.clear();
		if (GetAuth()->IsVIP()) {
			if (!GetConfig()->DoesFileExist(GetConfig()->GetYTDConfigPath())) {
				ofstream i(GetConfig()->GetYTDConfigPath());
				json j;
				j["customheader.ytd"] = json::array({ "img_one" });

				i << setw(4) << j;
				i.close();

				vars.customYTDHeaderNames.push_back("img_one");
			} else {
				fstream i(GetConfig()->GetYTDConfigPath());
				json j;
				i >> j;

				json& imgData = j["customheader.ytd"];
				for (auto it = imgData.begin(); it != imgData.end(); ++it) {
					json val = *it;
					vars.customYTDHeaderNames.push_back(val.get<string>());
				}
			}

			if (GetConfig()->DoesFileExist(GetConfig()->GetYTDHeaderPath())) {
				int newIdx;
				Backend::RegisterFileFn(&newIdx, GetConfig()->GetYTDHeaderPath(), true, "customheader.ytd", false);
				GRAPHICS::RequestStreamedTextureDict("customheader", true);

				if (GetConfig()->ReadBool("Customization", "LoadCustom", false)) {
					String header = GetConfig()->ReadString("Customization", "Header", "null");
					if (!strcmp(header, "null") == 0) {
						for (auto& a : vars.customYTDHeaderNames) {
							if (strcmp(a.c_str(), header) == 0) {
								GetRenderer()->m_hHeader = { "customheader", a.c_str() };
							}
						}
					}
				}
			}
		}
	}
}

void LoadCustomHeaderMenu::Init() {
	setParentSubmenu<ThemeMenu>();
	setName("Custom headers", true, false);

	//LoadConfig();

	addOption(ToggleOption("Load selected custom header on startup")
		.addToggle(vars.loadOnStart)
		.addRequirement([] {return GetAuth()->IsVIP(); })
		.addFunction([&] { GetConfig()->WriteBool("Customization", "LoadCustom", vars.loadOnStart); })
		.addTooltip("Load the selected custom header on startup"));

	addOption(BreakOption());
}

/*Update once when submenu is opened*/
void LoadCustomHeaderMenu::UpdateOnce() {
	clearOptionsOffset(2);

	vars.loadOnStart = GetConfig()->ReadBool("Customization", "LoadCustom", false);

	ThemeMenuVars::SetHeader(0);
	LoadConfig();

	for (string str : vars.customYTDHeaderNames) {
		addOption(ButtonOption(str.c_str())
			.addRequirement([] {return GetAuth()->IsVIP(); })
			.addFunction([=] {
			GetRenderer()->m_hHeader = { "customheader", str.c_str() };
			GetConfig()->WriteString("Customization", "Header", str.c_str());

		}).addTooltip(str.c_str()));
	}
}

/*Update while submenu is active*/
void LoadCustomHeaderMenu::Update() {}

/*Background update*/
void LoadCustomHeaderMenu::FeatureUpdate() {}

/*Singleton*/
LoadCustomHeaderMenu* _instance;
LoadCustomHeaderMenu* LoadCustomHeaderMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new LoadCustomHeaderMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
LoadCustomHeaderMenu::~LoadCustomHeaderMenu() { delete _instance; }