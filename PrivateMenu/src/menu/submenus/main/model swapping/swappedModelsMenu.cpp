#include "stdafx.h"
#include "swappedModelsMenu.h"
#include "swappingPresetsMenu.h"
#include "backend/backendModelSwap.h"

using namespace SwappedMenuVars;

namespace SwappedMenuVars {
}

void SwappedModelsMenu::Init() {
	setParentSubmenu<SwapPresetsMenu>();
	setName("Swapped models", true, true);
}

/*Update once when submenu is opened*/
void SwappedModelsMenu::UpdateOnce() {}

/*Update while submenu is active*/
void SwappedModelsMenu::Update() {
	static int TIMER;
	static bool update = true;
	Utils::DoTimedFunction(&TIMER, 100, [] { update = true; });
	if (update) {
		clearOptions();

		if (ModelSwapping::modelSwaps.size() > 0) {

			addOption(BreakOption("Swaps"));

			if (ModelSwapping::modelSwaps.size() > 0) {

				for (modelSwap_t m : ModelSwapping::modelSwaps) {

					string text = m.originalModel + " swapped with " + m.newModel;

					addOption(ButtonOption(text.c_str())
						.addFunction([=] {
						ModelSwapping::RemoveSwap(m.originalModel.c_str());
					})
						.addTooltip("Remove this swap")
						.addTranslation());
				}
			}
		}
		else {
			addOption(ButtonOption("~c~No swaps yet~s~"));
		}
		update = false;
	}
	
}

/*Background update*/
void SwappedModelsMenu::FeatureUpdate() {}

/*Singleton*/
SwappedModelsMenu* _instance;
SwappedModelsMenu* SwappedModelsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new SwappedModelsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
SwappedModelsMenu::~SwappedModelsMenu() { delete _instance; }