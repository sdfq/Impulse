#include "stdafx.h"
#include "miscDisable.h"
#include "../miscMenu.h"

using namespace MiscDisableMenuVars;

namespace MiscDisableMenuVars {
	Vars vars;

	void DisablePhone() {
		using namespace Globals;
		int Unk_1 = 15745;

		if (*Global(PHONE_BASE).At(1).Get<bool>() != 1) {
			if (SCRIPT::_GetNumberOfInstancesOfScriptWithNameHash(Utils::GetHashKey("cellphone_flashhand")) > 0 ||
				*Global(PHONE_BASE).At(1).Get<int>() > 3) {
				if (*Global(PHONE_BOOL1).Get<bool>()) {
					Global(PHONE_BOOL1).As<int>() = 0;
					Global(PHONE_POSSET).As<int>() = *Global(PHONE_POSGET).Get<int>();
					Global(PHONE_POSSET).At(1).As<int>() = *Global(PHONE_POSGET).At(1).Get<int>();
					Global(PHONE_POSSET).At(2).As<int>() = *Global(PHONE_POSGET).At(2).Get<int>();
					MOBILE::SetMobilePhonePosition(
						*Global(PHONE_POSSET).Get<float>(),
						*Global(PHONE_POSSET).At(1).Get<float>(),
						*Global(PHONE_POSSET).At(2).Get<float>()
					);
				}

				if (*Global(PHONE_BASE).At(1).Get<int>() == 10 && *Global(PHONE_BASE).At(1).Get<int>() == 9) {
					MISC::SetBit(Global(PHONE_BITSET1).Get<int>(), 16);
				}

				if (AUDIO::IsMobilePhoneCallOngoing()) {
					AUDIO::StopScriptedConversation(false);
				}

				Global(Unk_1).As<int>() = 5;
				MISC::ClearBit((int*)Global(PHONE_BITSET2).Get<int64_t>(), 30);

				if (*Global(PHONE_BASE).At(1).Get<int>() != 1 && *Global(PHONE_BASE).At(1).Get<int>() != 0) {
					Global(PHONE_BASE).At(1).As<int>() = 3;
				}
			}
			MISC::SetBit((int*)Global(PHONE_BITSET1).Get<int>(), 2);
		}
	}
}

void MiscDisableMenu::Init() {
	setParentSubmenu<MiscMenu>();
	setName("Disables", true, true);

	addOption(ToggleOption("Disable idle kick")
		.addToggle(MiscMenuVars::vars.disableIdleKick)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Don't get kicked for idling"));

	addOption(ToggleOption("Disable cinematic button")
		.addToggle(MiscMenuVars::vars.disableCinematicButton)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Disable cinematic button"));

	addOption(ToggleOption("Disable stunt jump cutscenes")
		.addToggle(MiscMenuVars::vars.disableStuntJumpCutscenes)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Disable stunt jump cutscenes"));

	//addOption(ToggleOption("Disable phone calls")
	//	.addToggle(MiscMenuVars::vars.disablePhoneCalls)
	//	.addFunction([] {
	//		if (MiscMenuVars::vars.disablePhoneCalls) {
	//			SCRIPT::SetScriptAsNoLongerNeeded("cellphone_controller"); // maybe that works lol
	//			MISC::TerminateAllScriptsWithThisName("cellphone_controller");
	//		} else {
	//			SCRIPT::RequestScript("cellphone_controller");
	//			SYSTEM::StartNewScript("cellphone_controller", 1424);
	//			SCRIPT::SetScriptAsNoLongerNeeded("cellphone_controller");
	//		}
	//	})
	//	.addTranslation().addHotkey().canBeSaved()
	//	.addTooltip("Disable all phone calls"));

	addOption(ToggleOption("Disable phone")
		.addToggle(vars.disablePhoneCalls).addTranslation()
		.addHotkey().canBeSaved()
		.addTooltip("Disable the phone"));

	/*addOption(ToggleOption("Disable cinematic camera")
		.addToggle(vars.cinematicdisable).addTranslation()
		.addHotkey().canBeSaved()
		.addTooltip("Disable the phone"));*/

	addOption(ToggleOption("Disable notifications")
		.addToggle(MiscMenuVars::vars.disableNotifications)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Disable notifications"));

	addOption(ToggleOption("Disable game recordings")
		.addToggle(MiscMenuVars::vars.disableGameRecordings)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Disable game recordings"));

	addOption(ToggleOption("Disable HUD")
		.addToggle(MiscMenuVars::vars.disableHUD)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Disable HUD"));
}

/*Update once when submenu is opened*/
void MiscDisableMenu::UpdateOnce() {}

/*Update while submenu is active*/
void MiscDisableMenu::Update() {}

/*Background update*/
void MiscDisableMenu::FeatureUpdate() {
	if (vars.disablePhoneCalls)DisablePhone();

	if (vars.cinematicdisable) {
		CAM::SetCinematicButtonActive(0);
		CAM::SetCinematicModeActive(0);
	}
}

/*Singleton*/
MiscDisableMenu* _instance;
MiscDisableMenu* MiscDisableMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new MiscDisableMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
MiscDisableMenu::~MiscDisableMenu() { delete _instance; }