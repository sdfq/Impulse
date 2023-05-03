#include "stdafx.h"
#include "tuneablesMenu.h"

using namespace TunablesMenuVars;

namespace TunablesMenuVars {

	
}

void TunablesMenu::Init() {
	setParentSubmenu<MiscMenu>();
	setName("Tuneables", true, true);

	addOption(ButtonOption("test")
		.addFunction([] {
		Global(262145 + 4721).As<bool>() = 1; //Snow
		Global(262145 + 0x1284).As<bool>() = 1; //RP Bonus
		Global(262145 + 4732).As<bool>() = 1; //Xmas Content
		Global(262145 + 5990).As<bool>() = 1; //Valentine Event
		Global(262145 + 0x2D2F).As<bool>() = 1; //Halloween Sounds
		Global(262145 + 12114).As<bool>() = 1; //Halloween Sounds
		Global(262145 + 18680).As<bool>() = 1; //Turf Wars
		Global(262145 + 12122).As<bool>() = 1; //Xmas Vehicle
		Global(262145 + 12796).As<bool>() = 1; //VALENTINE_2016_CLOTHING
		Global(262145 + 12797).As<bool>() = 1; //VALENTINE_2016_VEHICLE
		Global(262145 + 0x2A94).As<bool>() = 1; //VALENTINE_2016_CLOTHING
		Global(262145 + 0x2A91).As<bool>() = 1; //VALENTINE_2016_VEHICLE
		Global(262145 + 11442).As<bool>() = 1; //TURN_ON_VALENTINE_WEAPON
		Global(262145 + 11443).As<bool>() = 1; //VALENTINE_2016_VEHICLE
		Global(262145 + 11444).As<bool>() = 1; //TURN_ON_VALENTINE_MASKS
		Global(262145 + 11445).As<bool>() = 1; //TURN_ON_VALENTINE_HAIR
		Global(262145 + 0x2A91).As<bool>() = 1; //TURN_ON_VALENTINE_HAIR
		Global(262145 + 10123).As<bool>() = 1; //fuck knows
		Global(262145 + 11471).As<bool>() = 1; //TURN_ON_HALLOWEEN_ANIMS
		Global(262145 + 0x2AAD).As<bool>() = 1; //TURN_ON_HALLOWEEN_ANIMS
		Global(262145 + 8869).As<bool>() = 1; //TOGGLE_CHRISTMAS_EVE_GIFT
		Global(262145 + 8870).As<bool>() = 1; //TOGGLE_NEW_YEARS_EVE_GIFT
		Global(262145 + 8871).As<bool>() = 1; //TOGGLE_NEW_YEARS_DAY_GIFT
		Global(262145 + 18680).As<bool>() = 1; //DISABLE_SCTV_FRIENDS_SPECTATE
		Global(262145 + 8156).As<bool>() = 1; //DISABLE_SCTV_GTAO_TV
		Global(262145 + 8157).As<bool>() = 1; //DISABLE_SCTV_DEV_SPECTATE
		Global(262145 + 8158).As<bool>() = 1; //DISABLE_SCTV_FRIENDS_SPECTATE
		Global(262145 + 12848).As<bool>() = 1; //TURN_ON_BE_MY_VALENTINE
		Global(262145 + 11464).As<bool>() = 1; //TURN_ON_HALLOWEEN_WEAPONS
	})
		.addTooltip("")
		.addHotkey()
		.addTranslation());
}

/*Update once when submenu is opened*/
void TunablesMenu::UpdateOnce() {}

/*Update while submenu is active*/
void TunablesMenu::Update() {}

/*Background update*/
void TunablesMenu::FeatureUpdate() {}

/*Singleton*/
TunablesMenu* _instance;
TunablesMenu* TunablesMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new TunablesMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
TunablesMenu::~TunablesMenu() { delete _instance; }