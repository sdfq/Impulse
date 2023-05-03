#include "stdafx.h"
#include "customSwappingMenu.h"
#include "swappingPresetsMenu.h"
#include "backend/backendModelSwap.h"
#include "menu/submenus/mainMenu.h"

using namespace ModelSwappingMenuVars;

namespace ModelSwappingMenuVars {
	Vars var;
}

void CustomSwappingMenu::Init() {
	setParentSubmenu<SwapPresetsMenu>();
	setName("Model Swapping", true, true);

	addOption(ButtonOption("Swap model:")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addFunction([this] {
		GetMenuInput()->AddToQueue([] {
			string input = "null";
			string input2 = "null";
			if (GetMenuInput()->Text("First model", input, 2, 50)) var.firstInput = input.c_str();
			if (GetMenuInput()->Text("Second model", input2, 2, 50)) var.secondInput = input2.c_str();
			// on input received
			if (STREAMING::IsModelValid(MISC::GetHashKey(input.c_str())) &&
				STREAMING::IsModelValid(MISC::GetHashKey(input2.c_str()))) {
				GetRenderer()->NotifyBottom("Valid models received!");
				ModelSwapping::ModelSwap(input.c_str(), input2.c_str());
			}
			else if(!STREAMING::IsModelValid(MISC::GetHashKey(var.firstInput))) {
				GetRenderer()->NotifyBottom("The first model provided is not valid! Check your spelling.");
			}
			else if (!STREAMING::IsModelValid(MISC::GetHashKey(var.secondInput))) {
				GetRenderer()->NotifyBottom("The second model provided is not valid! Check your spelling.");
			}
			else {
				GetRenderer()->NotifyBottom("None of the models provided are valid! Check your spelling.");
			}
		});
	})
		.addTooltip("Input the original and the new model, and the job is done!").addTranslation());
}

/*Update once when submenu is opened*/
void CustomSwappingMenu::UpdateOnce() {
}

/*Update while submenu is active*/
void CustomSwappingMenu::Update() {	
}

/*Background update*/
void CustomSwappingMenu::FeatureUpdate() {
	
}

/*Singleton*/
CustomSwappingMenu* _instance;
CustomSwappingMenu* CustomSwappingMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new CustomSwappingMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
CustomSwappingMenu::~CustomSwappingMenu() { delete _instance; }