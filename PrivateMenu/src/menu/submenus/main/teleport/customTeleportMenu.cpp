#include "stdafx.h"
#include "customTeleportMenu.h"
#include "../teleportMenu.h"

using namespace CustomMenuVars;

namespace CustomMenuVars {

	vector<string> m_teleportFiles;

	shared_ptr<ButtonOption> addTeleportsOption;

	void LoadTeleports(String filename) {
		ifstream i(va("%s/%s.json", GetConfig()->GetTeleportsPath(), filename));
		json j;
		i >> j;
		json& jsondata = j["teleport"];

		auto location = jsonGet<vector<vector<float>>>(j["teleport"], "location", { { 0 } });

		TeleportMenuVars::TeleportToCoords(Vector3(location[0][0], location[0][1], location[0][2]));

	}
}

void CustomTeleportMenu::Init() {
	setParentSubmenu<TeleportMenu>();
	setName("Custom Teleports", true, true);

	addTeleportsOption = addOption(ButtonOption("~c~Add teleports to ./Documents/Impulse/Teleports")
		.addTooltip("Add teleports to ./Documents/Impulse/Teleports").addTranslation());

}

/*Update once when submenu is opened*/
void CustomTeleportMenu::UpdateOnce() {}

/*Update while submenu is active*/
void CustomTeleportMenu::Update() {
	static int TIMER;
	static bool shouldUpdate = false;
	Utils::DoTimedFunction(&TIMER, 2500, [] {shouldUpdate = true; });
	if (shouldUpdate) {
		clearOptions();
		GetConfig()->GetFilesFromDirectory(m_teleportFiles, GetConfig()->GetTeleportsPath(), ".json");
		if (!m_teleportFiles.empty()) {
			for (auto& teleport : m_teleportFiles) {
				addOption(ButtonOption(teleport.c_str())
					//.hasNoTranslation()
					.addFunction([&] {LoadTeleports(teleport.c_str()); })
					.addTooltip(teleport.c_str()));
			}
		}
		else {
			addOption(addTeleportsOption);
		}
		shouldUpdate = false;
	}
}

/*Background update*/
void CustomTeleportMenu::FeatureUpdate() {}

/*Singleton*/
CustomTeleportMenu* _instance;
CustomTeleportMenu* CustomTeleportMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new CustomTeleportMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
CustomTeleportMenu::~CustomTeleportMenu() { delete _instance; }