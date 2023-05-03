#include "stdafx.h"
#include "wardrobePresetsMenu.h"
#include "../wardrobeMenu.h"

using namespace WardrobePresetsMenuVars;

namespace WardrobePresetsMenuVars {
}

void WardrobePresetsMenu::Init() {
	setParentSubmenu<WardrobeMenu>();
	setName("Presets", true, true);
}

/*Update once when submenu is opened*/
void WardrobePresetsMenu::UpdateOnce() {}

/*Update while submenu is active*/
void WardrobePresetsMenu::Update() {}

/*Background update*/
void WardrobePresetsMenu::FeatureUpdate() {}

/*Singleton*/
WardrobePresetsMenu* _instance;
WardrobePresetsMenu* WardrobePresetsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new WardrobePresetsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
WardrobePresetsMenu::~WardrobePresetsMenu() { delete _instance; }