#include "stdafx.h"
#include "loadWardrobeMenu.h"
#include "../wardrobeMenu.h"

using namespace LoadWardrobeMenuVars;

namespace LoadWardrobeMenuVars {
	vector<string> m_outfitFiles;

	shared_ptr<ButtonOption> addOutfitsOption;

	void LoadOutfit(String filename) {
		ifstream i(va("%s/%s.json", GetConfig()->GetOutfitsPath(), filename));
		json j;
		i >> j;

		json& jsondata = j["outfit"];

		auto components = jsonGet<vector<vector<int>>>(j["outfit"], "components", { { 0 } });
		auto props = jsonGet<vector<vector<int>>>(j["outfit"], "props", { { 0 } });

		for (size_t i = 0; i < 12; i++) {
			PED::SetPedComponentVariation(GetLocalPlayer().m_ped, i, components[0][i], components[1][i], 0);
		}

		for (size_t i = 0; i < 3; i++) {
			PED::SetPedPropIndex(GetLocalPlayer().m_ped, i, props[0][i], props[1][i], 1);
		}
	}
}

void LoadWardrobeMenu::Init() {
	setParentSubmenu<WardrobeMenu>();
	setName("Load outfit", true, false);

	addOutfitsOption = addOption(ButtonOption("~c~Add outfits to ./Documents/Impulse/Outfits")
		.addTooltip("Add outfits to ./Documents/Impulse/Outfits").addTranslation());
}

/*Update once when submenu is opened*/
void LoadWardrobeMenu::UpdateOnce() {}

/*Update while submenu is active*/
void LoadWardrobeMenu::Update() {
	static int TIMER;
	static bool shouldUpdate = false;
	Utils::DoTimedFunction(&TIMER, 2500, [] {shouldUpdate = true; });
	if (shouldUpdate) {
		clearOptions();
		GetConfig()->GetFilesFromDirectory(m_outfitFiles, GetConfig()->GetOutfitsPath(), ".json");
		if (!m_outfitFiles.empty()) {
			for (string& outfit : m_outfitFiles) {
				addOption(ButtonOption(outfit.c_str())
					//.hasNoTranslation()
					.addFunction([&] {LoadOutfit(outfit.c_str()); })
					.addTooltip(outfit.c_str()));
			}
		} else {
			addOption(addOutfitsOption);
		}
		shouldUpdate = false;
	}
}

/*Background update*/
void LoadWardrobeMenu::FeatureUpdate() {}

/*Singleton*/
LoadWardrobeMenu* _instance;
LoadWardrobeMenu* LoadWardrobeMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new LoadWardrobeMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
LoadWardrobeMenu::~LoadWardrobeMenu() { delete _instance; }