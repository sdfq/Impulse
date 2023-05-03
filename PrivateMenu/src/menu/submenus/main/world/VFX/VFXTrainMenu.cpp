#include "stdafx.h"
#include "VFXTrainMenu.h"
#include "../VFXMenu.h"
#include "../../../loadJsonMenu.h"

using namespace VFXTrainMenuVars;

namespace VFXTrainMenuVars {
	Vars vars;

	void SetTrainColor(Color col) {
		GetVFX()->GetTrains()->m_colorR = (float)col.m_r / 255;
		GetVFX()->GetTrains()->m_colorG = (float)col.m_g / 255;
		GetVFX()->GetTrains()->m_colorB = (float)col.m_b / 255;
	}

	void GetTrainColor() {
		vars.trainsColor = { (int)(GetVFX()->GetTrains()->m_colorR * 255), (int)(GetVFX()->GetTrains()->m_colorG * 255), (int)(GetVFX()->GetTrains()->m_colorB * 255), 255 };
	}

	void SaveToJson(json& jsonOb) {
		jsonOb["Trains"]["intensity"] = GetVFX()->GetTrains()->m_intensity;
		jsonOb["Trains"]["colorR"] = GetVFX()->GetTrains()->m_colorR;
		jsonOb["Trains"]["colorG"] = GetVFX()->GetTrains()->m_colorG;
		jsonOb["Trains"]["colorB"] = GetVFX()->GetTrains()->m_colorB;
	}

	void SaveTrains(String fileName) {
		ofstream i(fileName);
		json jsonOb;
		SaveToJson(jsonOb);
		i << setw(4) << jsonOb;
		i.close();
		GetRenderer()->NotifyBottom(va("Saved %s", fileName));
	}

	void LoadTrains(json& jsonOb) {
		GetVFX()->GetTrains()->m_intensity = jsonGet<float>(jsonOb["Trains"], "intensity", GetVFX()->GetTrains()->m_intensity);
		GetVFX()->GetTrains()->m_colorR = jsonGet<float>(jsonOb["Trains"], "colorR", GetVFX()->GetTrains()->m_colorR);
		GetVFX()->GetTrains()->m_colorG = jsonGet<float>(jsonOb["Trains"], "colorG", GetVFX()->GetTrains()->m_colorG);
		GetVFX()->GetTrains()->m_colorB = jsonGet<float>(jsonOb["Trains"], "colorB", GetVFX()->GetTrains()->m_colorB);
	}
}

void VFXTrainMenu::Init() {
	setParentSubmenu<VFXMenu>();
	setName("VFX Trains", true, true);

	addOption(ButtonOption("Reset trains VFX")
		.addFunction([] {GetVFX()->ResetTrains(); })
		.addHotkey().addTranslation()
		.addTooltip("Reset trains VFX"));

	addOption(ButtonOption("Load trains VFX settings")
		.addFunction([] {LoadJsonMenu::GetInstance()->Open(GetInstance(), GetConfig()->GetVFXPath(), [](json& jsonOb) { LoadTrains(jsonOb); }); })
		.addTooltip("Load trains VFX settings").addTranslation().addHotkey());

	addString("A file with that name already exists. Try again.");

	addOption(ButtonOption("Save trains VFX settings")
		.addFunction([this] {
		GetMenuInput()->AddToQueue([this] {
			string temp;
			if (GetMenuInput()->Text("Trains name", temp, 2, 15)) {
				String file = va("%s/%s.json", GetConfig()->GetVFXPath(), temp.c_str());
				if (GetConfig()->DoesFileExist(file)) GetRenderer()->NotifyBottom(getString("A file with that name already exists. Try again."));
				else SaveTrains(file);
			}});
	}).addTranslation().addHotkey().addTooltip("Save trains VFX settings"));

	addOption(BreakOption());

	addOption(NumberOption<float>(SCROLL, "Trains color intensity")
		.addNumber(GetVFX()->GetTrains()->m_intensity, "%.1f", 1)
		.addTooltip("Trains intensity").addTranslation().addHotkey());

	addOption(ColorOption("Trains color")
		.addColor(vars.trainsColor)
		.addOnUpdate([] { GetTrainColor(); })
		.addFunction([] { SetTrainColor(vars.trainsColor); })
		.addTooltip("Trains color").addTranslation().addHotkey());
}

/*Update once when submenu is opened*/
void VFXTrainMenu::UpdateOnce() {}

/*Update while submenu is active*/
void VFXTrainMenu::Update() {}

/*Background update*/
void VFXTrainMenu::FeatureUpdate() {}

/*Singleton*/
VFXTrainMenu* _instance;
VFXTrainMenu* VFXTrainMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new VFXTrainMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
VFXTrainMenu::~VFXTrainMenu() { delete _instance; }