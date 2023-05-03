#include "stdafx.h"
#include "VFXTrafficLightMenu.h"
#include "../VFXMenu.h"
#include "../../../loadJsonMenu.h"

using namespace VFXTrafficLightMenuVars;

namespace VFXTrafficLightMenuVars {
	Vars vars;

	void SetRed(Color& col) {
		GetVFX()->GetTrafficLights()->m_redR = (float)col.m_r / 255;
		GetVFX()->GetTrafficLights()->m_redG = (float)col.m_g / 255;
		GetVFX()->GetTrafficLights()->m_redB = (float)col.m_b / 255;
	}

	void SetOrange(Color& col) {
		GetVFX()->GetTrafficLights()->m_orangeR = (float)col.m_r / 255;
		GetVFX()->GetTrafficLights()->m_orangeG = (float)col.m_g / 255;
		GetVFX()->GetTrafficLights()->m_orangeB = (float)col.m_b / 255;
	}

	void SetGreen(Color& col) {
		GetVFX()->GetTrafficLights()->m_greenR = (float)col.m_r / 255;
		GetVFX()->GetTrafficLights()->m_greenG = (float)col.m_g / 255;
		GetVFX()->GetTrafficLights()->m_greenB = (float)col.m_b / 255;
	}

	void SetWalk(Color& col) {
		GetVFX()->GetTrafficLights()->m_walkR = (float)col.m_r / 255;
		GetVFX()->GetTrafficLights()->m_walkG = (float)col.m_g / 255;
		GetVFX()->GetTrafficLights()->m_walkB = (float)col.m_b / 255;
	}

	void SetDontWalk(Color& col) {
		GetVFX()->GetTrafficLights()->m_dontWalkR = (float)col.m_r / 255;
		GetVFX()->GetTrafficLights()->m_dontWalkG = (float)col.m_g / 255;
		GetVFX()->GetTrafficLights()->m_dontWalkB = (float)col.m_b / 255;
	}


	void GetRed() {
		vars.red = { (int)(GetVFX()->GetTrafficLights()->m_redR * 255), (int)(GetVFX()->GetTrafficLights()->m_redG * 255), (int)(GetVFX()->GetTrafficLights()->m_redB * 255), 255 };
	}

	void GetOrange() {
		vars.orange = { (int)(GetVFX()->GetTrafficLights()->m_orangeR * 255), (int)(GetVFX()->GetTrafficLights()->m_orangeG * 255), (int)(GetVFX()->GetTrafficLights()->m_orangeB * 255), 255 };
	}

	void GetGreen() {
		vars.green = { (int)(GetVFX()->GetTrafficLights()->m_greenR * 255), (int)(GetVFX()->GetTrafficLights()->m_greenG * 255), (int)(GetVFX()->GetTrafficLights()->m_greenB * 255), 255 };
	}

	void GetWalk() {
		vars.walk = { (int)(GetVFX()->GetTrafficLights()->m_walkR * 255), (int)(GetVFX()->GetTrafficLights()->m_walkG * 255), (int)(GetVFX()->GetTrafficLights()->m_walkB * 255), 255 };
	}

	void GetDontWalk() {
		vars.dontwalk = { (int)(GetVFX()->GetTrafficLights()->m_dontWalkR * 255), (int)(GetVFX()->GetTrafficLights()->m_dontWalkG * 255), (int)(GetVFX()->GetTrafficLights()->m_dontWalkB * 255), 255 };
	}

	void SaveToJson(json& jsonOb) {
		jsonOb["TrafficLights"]["dontWalkR"] = GetVFX()->GetTrafficLights()->m_dontWalkR;
		jsonOb["TrafficLights"]["dontWalkG"] = GetVFX()->GetTrafficLights()->m_dontWalkG;
		jsonOb["TrafficLights"]["dontWalkB"] = GetVFX()->GetTrafficLights()->m_dontWalkB;
		jsonOb["TrafficLights"]["walkR"] = GetVFX()->GetTrafficLights()->m_walkR;
		jsonOb["TrafficLights"]["walkG"] = GetVFX()->GetTrafficLights()->m_walkG;
		jsonOb["TrafficLights"]["walkB"] = GetVFX()->GetTrafficLights()->m_walkB;
		jsonOb["TrafficLights"]["redR"] = GetVFX()->GetTrafficLights()->m_redR;
		jsonOb["TrafficLights"]["redG"] = GetVFX()->GetTrafficLights()->m_redG;
		jsonOb["TrafficLights"]["redB"] = GetVFX()->GetTrafficLights()->m_redB;
		jsonOb["TrafficLights"]["orangeR"] = GetVFX()->GetTrafficLights()->m_orangeR;
		jsonOb["TrafficLights"]["orangeG"] = GetVFX()->GetTrafficLights()->m_orangeG;
		jsonOb["TrafficLights"]["orangeB"] = GetVFX()->GetTrafficLights()->m_orangeB;
		jsonOb["TrafficLights"]["greenR"] = GetVFX()->GetTrafficLights()->m_greenR;
		jsonOb["TrafficLights"]["greenG"] = GetVFX()->GetTrafficLights()->m_greenG;
		jsonOb["TrafficLights"]["greenB"] = GetVFX()->GetTrafficLights()->m_greenB;
	}

	void SaveTrafficLights(String fileName) {
		ofstream i(fileName);
		json jsonOb;
		SaveToJson(jsonOb);
		i << setw(4) << jsonOb;
		i.close();
		GetRenderer()->NotifyBottom(va("Saved %s", fileName));
	}

	void LoadTrafficLights(json& jsonOb) {
		GetVFX()->GetTrafficLights()->m_dontWalkR = jsonGet<float>(jsonOb["TrafficLights"], "dontWalkR", GetVFX()->GetTrafficLights()->m_dontWalkR);
		GetVFX()->GetTrafficLights()->m_dontWalkG = jsonGet<float>(jsonOb["TrafficLights"], "dontWalkG", GetVFX()->GetTrafficLights()->m_dontWalkG);
		GetVFX()->GetTrafficLights()->m_dontWalkB = jsonGet<float>(jsonOb["TrafficLights"], "dontWalkB", GetVFX()->GetTrafficLights()->m_dontWalkB);
		GetVFX()->GetTrafficLights()->m_walkR = jsonGet<float>(jsonOb["TrafficLights"], "walkR", GetVFX()->GetTrafficLights()->m_walkR);
		GetVFX()->GetTrafficLights()->m_walkG = jsonGet<float>(jsonOb["TrafficLights"], "walkG", GetVFX()->GetTrafficLights()->m_walkG);
		GetVFX()->GetTrafficLights()->m_walkB = jsonGet<float>(jsonOb["TrafficLights"], "walkB", GetVFX()->GetTrafficLights()->m_walkB);
		GetVFX()->GetTrafficLights()->m_redR = jsonGet<float>(jsonOb["TrafficLights"], "redR", GetVFX()->GetTrafficLights()->m_redR);
		GetVFX()->GetTrafficLights()->m_redG = jsonGet<float>(jsonOb["TrafficLights"], "redG", GetVFX()->GetTrafficLights()->m_redG);
		GetVFX()->GetTrafficLights()->m_redB = jsonGet<float>(jsonOb["TrafficLights"], "redB", GetVFX()->GetTrafficLights()->m_redB);
		GetVFX()->GetTrafficLights()->m_orangeR = jsonGet<float>(jsonOb["TrafficLights"], "orangeR", GetVFX()->GetTrafficLights()->m_orangeR);
		GetVFX()->GetTrafficLights()->m_orangeG = jsonGet<float>(jsonOb["TrafficLights"], "orangeG", GetVFX()->GetTrafficLights()->m_orangeG);
		GetVFX()->GetTrafficLights()->m_orangeB = jsonGet<float>(jsonOb["TrafficLights"], "orangeB", GetVFX()->GetTrafficLights()->m_orangeB);
		GetVFX()->GetTrafficLights()->m_greenR = jsonGet<float>(jsonOb["TrafficLights"], "greenR", GetVFX()->GetTrafficLights()->m_greenR);
		GetVFX()->GetTrafficLights()->m_greenG = jsonGet<float>(jsonOb["TrafficLights"], "greenG", GetVFX()->GetTrafficLights()->m_greenG);
		GetVFX()->GetTrafficLights()->m_greenB = jsonGet<float>(jsonOb["TrafficLights"], "greenB", GetVFX()->GetTrafficLights()->m_greenB);
	}
}

void VFXTrafficLightMenu::Init() {
	setParentSubmenu<VFXMenu>();
	setName("VFX Traffic lights", true, true);

	addOption(ButtonOption("Reset traffic lights VFX")
		.addFunction([] {GetVFX()->ResetTrafficLights(); })
		.addHotkey().addTranslation()
		.addTooltip("Reset traffic lights VFX"));

	addOption(ButtonOption("Load traffic lights VFX settings")
		.addFunction([] {LoadJsonMenu::GetInstance()->Open(GetInstance(), GetConfig()->GetVFXPath(), [](json& jsonOb) { LoadTrafficLights(jsonOb); }); })
		.addTooltip("Load traffic lights VFX settings").addTranslation().addHotkey());

	addString("A file with that name already exists. Try again.");

	addOption(ButtonOption("Save traffic lights VFX settings")
		.addFunction([this] {
		GetMenuInput()->AddToQueue([this] {
			string temp;
			if (GetMenuInput()->Text("Traffic lights name", temp, 2, 15)) {
				String file = va("%s/%s.json", GetConfig()->GetVFXPath(), temp.c_str());
				if (GetConfig()->DoesFileExist(file)) GetRenderer()->NotifyBottom(getString("A file with that name already exists. Try again."));
				else SaveTrafficLights(file);
			}});
	}).addTranslation().addHotkey().addTooltip("Save traffic lights VFX settings"));

	addOption(BreakOption());

	addOption(ColorOption("Traffic light red")
		.addColor(vars.red)
		.addOnUpdate([] { GetRed(); })
		.addFunction([] { SetRed(vars.red); })
		.addTooltip("Traffic light red").addTranslation().addHotkey());

	addOption(ColorOption("Traffic light orange")
		.addColor(vars.orange)
		.addOnUpdate([] { GetOrange(); })
		.addFunction([] { SetOrange(vars.orange); })
		.addTooltip("Traffic light red").addTranslation().addHotkey());

	addOption(ColorOption("Traffic light red")
		.addColor(vars.green)
		.addOnUpdate([] { GetGreen(); })
		.addFunction([] { SetGreen(vars.green); })
		.addTooltip("Traffic light red").addTranslation().addHotkey());

	addOption(ColorOption("Traffic pedestrian red")
		.addColor(vars.dontwalk)
		.addOnUpdate([] { GetDontWalk(); })
		.addFunction([] { SetDontWalk(vars.dontwalk); })
		.addTooltip("Traffic pedestrian red").addTranslation().addHotkey());

	addOption(ColorOption("Traffic pedestrian green")
		.addColor(vars.walk)
		.addOnUpdate([] { GetWalk(); })
		.addFunction([] { SetWalk(vars.walk); })
		.addTooltip("Traffic pedestrian green").addTranslation().addHotkey());
}

/*Update once when submenu is opened*/
void VFXTrafficLightMenu::UpdateOnce() {}

/*Update while submenu is active*/
void VFXTrafficLightMenu::Update() {}

/*Background update*/
void VFXTrafficLightMenu::FeatureUpdate() {}

/*Singleton*/
VFXTrafficLightMenu* _instance;
VFXTrafficLightMenu* VFXTrafficLightMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new VFXTrafficLightMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
VFXTrafficLightMenu::~VFXTrafficLightMenu() { delete _instance; }