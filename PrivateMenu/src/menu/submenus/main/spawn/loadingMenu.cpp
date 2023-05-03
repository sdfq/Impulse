#include "stdafx.h"
#include "loadingMenu.h"
#include "loading/JsonVehicleMenu.h"
#include "loading/XMLVehicleMenu.h"
#include "loading/INIVehicleMenu.h"
#include "../spawnMenu.h"
#include "../../loadJsonMenu.h"

using namespace LoadingMenuVars;

namespace LoadingMenuVars {
	void LoadINIVehicle(char* path) {
	}
}

void LoadingMenu::Init() {
	setParentSubmenu<SpawnMenu>();
	setName("Loading", true, true);

	addOption(SubmenuOption("Load XML vehicles")
		.addSubmenu<XMLVehicleMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Load saved XML vehicles"));

	addOption(SubmenuOption("Load json vehicles")
		.addSubmenu<JsonVehicleMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Load saved json vehicles"));

	addOption(SubmenuOption("Load INI vehicles")
		.addSubmenu<INIVehicleMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Load saved INI vehicles").addTranslation().addHotkey());
}

/*Update once when submenu is opened*/
void LoadingMenu::UpdateOnce() {}

/*Update while submenu is active*/
void LoadingMenu::Update() {}

/*Background update*/
void LoadingMenu::FeatureUpdate() {}

/*Singleton*/
LoadingMenu* _instance;
LoadingMenu* LoadingMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new LoadingMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
LoadingMenu::~LoadingMenu() { delete _instance; }