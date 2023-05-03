#include "stdafx.h"
#include "VFXMenu.h"
#include "../worldMenu.h"
#include "../../loadJsonMenu.h"
#include "VFX/VFXTrafficLightMenu.h"
#include "VFX/VFXVehicleMenu.h"
#include "VFX/VFXTrainMenu.h"
#include "VFX/VFXTonemappingMenu.h"
#include "VFX/VFXCoronasMenu.h"
#include "VFX/VFXDistantLightsMenu.h"
#include "VFX/VFXPuddlesMenu.h"
#include "VFX/VFXSkyMenuVars.h"

using namespace VFXMenuVars;

namespace VFXMenuVars {

	void SaveVFX(String fileName) {
		ofstream i(fileName);
		json jsonOb;
		VFXTrafficLightMenuVars::SaveToJson(jsonOb);
		VFXVehicleMenuVars::SaveToJson(jsonOb);
		VFXTrainMenuVars::SaveToJson(jsonOb);
		VFXTonemappingMenuVars::SaveToJson(jsonOb);
		VFXCoronasMenuVars::SaveToJson(jsonOb);
		VFXDistantLightsMenuVars::SaveToJson(jsonOb);
		VFXPuddlesMenuVars::SaveToJson(jsonOb);
		VFXSkyMenuVars::SaveToJson(jsonOb);
		i << setw(4) << jsonOb;
		i.close();
		GetRenderer()->NotifyBottom(va("Saved %s", fileName));
	}

	void LoadVFX(json& jsonOb) {
		VFXTrafficLightMenuVars::LoadTrafficLights(jsonOb);
		VFXVehicleMenuVars::LoadVehicle(jsonOb);
		VFXTrainMenuVars::LoadTrains(jsonOb);
		VFXTonemappingMenuVars::LoadTonemapping(jsonOb);
		VFXCoronasMenuVars::LoadCoronas(jsonOb);
		VFXDistantLightsMenuVars::LoadDistantLights(jsonOb);
		VFXPuddlesMenuVars::LoadRainPuddles(jsonOb);
		VFXSkyMenuVars::LoadSky(jsonOb);
	}
}

void VFXMenu::Init() {
	setParentSubmenu<WorldMenu>();
	setName("VFX Engine", true, true);

	addOption(ButtonOption("Reset VFX settings")
		.addFunction([] {GetVFX()->ResetAll(); })
		.addHotkey().addTranslation()
		.addTooltip("Reset all VFX settings"));

	addOption(ButtonOption("Load VFX settings")
		.addFunction([] {LoadJsonMenu::GetInstance()->Open(GetInstance(), GetConfig()->GetVFXPath(), [](json& jsonOb) { LoadVFX(jsonOb); }); })
		.addTooltip("Load VFX settings").addTranslation().addHotkey());

	addString("A file with that name already exists. Try again.");

	addOption(ButtonOption("Save VFX settings")
		.addFunction([this] {
		GetMenuInput()->AddToQueue([this] {
			string temp;
			if (GetMenuInput()->Text("VFX name", temp, 2, 15)) {
				String file = va("%s/%s.json", GetConfig()->GetVFXPath(), temp.c_str());
				if (GetConfig()->DoesFileExist(file)) GetRenderer()->NotifyBottom(getString("A file with that name already exists. Try again."));
				else SaveVFX(file);
			}});
	}).addTranslation().addHotkey().addTooltip("Save VFX settings"));

	addOption(BreakOption());

	addOption(SubmenuOption("Traffic light VFX")
		.addSubmenu<VFXTrafficLightMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Traffic light VFX"));

	addOption(SubmenuOption("Vehicle VFX")
		.addSubmenu<VFXVehicleMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Vehicle VFX"));

	addOption(SubmenuOption("Train VFX")
		.addSubmenu<VFXTrainMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Train VFX"));

	addOption(SubmenuOption("Tone mapping VFX")
		.addSubmenu<VFXTonemappingMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Tone mapping VFX"));

	addOption(SubmenuOption("Corona VFX")
		.addSubmenu<VFXCoronasMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Corona VFX"));

	addOption(SubmenuOption("Distant lights VFX")
		.addSubmenu<VFXDistantLightsMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Distant lights VFX"));

	addOption(SubmenuOption("Rain puddles VFX")
		.addSubmenu<VFXPuddlesMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Rain puddles VFX"));

	addOption(SubmenuOption("Sky VFX")
		.addSubmenu<VFXSkyMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Sky VFX"));
}

/*Update once when submenu is opened*/
void VFXMenu::UpdateOnce() {}

/*Update while submenu is active*/
void VFXMenu::Update() {}

/*Background update*/
void VFXMenu::FeatureUpdate() {}

/*Singleton*/
VFXMenu* _instance;
VFXMenu* VFXMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new VFXMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
VFXMenu::~VFXMenu() { delete _instance; }