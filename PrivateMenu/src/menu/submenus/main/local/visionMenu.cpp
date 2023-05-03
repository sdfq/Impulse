#include "stdafx.h"
#include "visionMenu.h"
#include "../localMenu.h"

using namespace VisionMenuVars;

namespace VisionMenuVars {
	vector<pair<String, String>> visions = {
		{ "Default", "" },
		{ "Damage", "damage" },
		{ "Vagos", "VagosSPLASH" },
		{ "Cops", "CopsSPLASH" },
		{ "White screen", "BarryFadeOut" },
		{ "Water lab", "WATER_lab" },
		{ "MP spectator cam", "Multipayer_spectatorCam" },
		{ "Cops", "cops" },
		{ "Spectator 1", "spectator1" },
		{ "Sunglasses", "sunglasses" },
		{ "Dying", "dying" },
		{ "Orange", "REDMIST" },
		{ "Vagos", "vagos" },
		{ "Blurry", "CHOP" },
		{ "Stoned", "stoned" },
		{ "Prologue shootout", "prologue_shootout" },
		{ "Secret camera", "secret_camera" },
		{ "UFO", "ufo" },
		{ "UFO deathray", "ufo_deathray" },
		{ "Wobbly", "drug_wobbly" },
		{ "Killstreak", "MP_Killstreak" },
		{ "Hint cam", "Hint_cam" },
		{ "Black and white", "blackNwhite" },
		{ "Sniper", "sniper" },
		{ "Crane cam", "crane_cam" },
		{ "Bikers", "BikersSPLASH" }
	};
}

void VisionMenu::Init() {
	setParentSubmenu<LocalMenu>();
	setName("Vision", true, true);

	for (auto& element : visions) {
		addOption(ButtonOption(element.first).addTranslation().addHotkey()
			.addFunction([=] { if (!strcmp(element.first, "Default")) GRAPHICS::ClearTimecycleModifier(); else GRAPHICS::SetTimecycleModifier(element.second); })
			.addTooltip("Set this vision"));
	}
}

/*Update once when submenu is opened*/
void VisionMenu::UpdateOnce() {}

/*Update while submenu is active*/
void VisionMenu::Update() {}

/*Background update*/
void VisionMenu::FeatureUpdate() {}

/*Singleton*/
VisionMenu* _instance;
VisionMenu* VisionMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new VisionMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
VisionMenu::~VisionMenu() { delete _instance; }