#include "stdafx.h"
#include "casinoMenu.h"
#include "..//recoveryMenu.h"

using namespace CasinoMenuVars;

namespace CasinoMenuVars {
	Vars vars;
}

void CasinoMenu::Init() {
	setParentSubmenu<RecoveryMenu>();
	setName("Casino", true, true);

	//addOption(ToggleOption("Disable chips buy timer")
	//	.addToggle(vars.DisableChipsBuyTimer)
	//	.addTooltip("Buy as many chips as many times as you want!")
	//	.addTranslation().canBeSaved());

	//addOption(ToggleOption("Unlimited chips buy limit")
	//	.addToggle(vars.BillionChips)
	//	.addTooltip("Buy as many chips as you want! All at once!")
	//	.addTranslation().canBeSaved()
	//	.addRequirement([] { return GetAuth()->IsVIP(); }));

	///*addOption(ToggleOption("Unlock all the t-shirts")
	//	.addToggle(vars.UnlockShirts)
	//	.addTooltip("Unlock all of the casino related t-shirts!")
	//	.addTranslation().canBeSaved());*/

	//addOption(ButtonOption("Unlock all the t-shirts")
	//	.addHotkey()
	//	.addFunction([] {

	//	for (int i = 0; i <= 18; i++) {
	//		Global(2573746).At(27287 + i).As<int>() = 0;
	//		Global(262145).At(27287 + i).As<int>() = 1;
	//	}

	//	for (int i = 0; i <= 6; i++) {
	//		Global(2573746).At(25998 + i).As<int>() = 0;
	//		Global(262145).At(25998 + i).As<int>() = 1;
	//	}

	//})
	//	.addTooltip("Unlock all of the casino related t-shirts!")
	//	.addTranslation());

	//addOption(ButtonOption("Reset lucky wheel timer")
	//	.addTranslation()
	//	.addHotkey()
	//	.addFunction([]
	//		{
	//			STATS::StatSetInt(Utils::GetHashKey("MPPLY_LUCKY_WHEEL_USAGE"), 0, 1);
	//		})
	//	.addTooltip("Test your luck again!")
	//	.addRequirement([] { return GetAuth()->IsVIP(); }));

	//addOption(ButtonOption("Unban yourself from the casino!")
	//	.addTranslation()
	//	.addHotkey()
	//	.addFunction([]
	//		{
	//			STATS::StatSetInt(-1274895349, 0, 1);
	//		})
	//	.addTooltip("If you're addicted, you're advised to seek medical assistance. This option may be removed at anytime with no warnings."));
}

/*Update once when submenu is opened*/
void CasinoMenu::UpdateOnce() {}

/*Update while submenu is active*/
void CasinoMenu::Update() 
{
	if (vars.BillionChips)
	{
		Global(262145).At(25953).As<int>() = INT_MAX;
	}

	if (vars.DisableChipsBuyTimer)
	{
		STATS::StatSetInt(Utils::GetHashKey("MPPLY_CASINO_CHIPS_PURTIM"), 0, 1);
		STATS::StatSetInt(Utils::GetHashKey("MPPLY_CASINO_CHIPS_PUR_GD"), 0, 1);
		STATS::StatSetInt(Utils::GetHashKey("MPPLY_CHIPS_COL_TIME"), 0, 1);
	}

	if (vars.UnlockShirts)
	{
		for (int i = 0; i <= 6; i++)
		{
			Global(2573746).At(25998 + i).As<int>() = 0;
		}
	}
}

/*Background update*/
void CasinoMenu::FeatureUpdate() {}

/*Singleton*/
CasinoMenu* _instance;
CasinoMenu* CasinoMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new CasinoMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
CasinoMenu::~CasinoMenu() { delete _instance; }