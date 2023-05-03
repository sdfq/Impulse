#include "stdafx.h"
#include "VFXSkyMenuVars.h"
#include "../VFXMenu.h"
#include "../../../loadJsonMenu.h"

using namespace VFXSkyMenuVars;

namespace VFXSkyMenuVars {
	void SaveToJson(json& jsonOb) {
		jsonOb["Sky"]["cloudSpeedLarge"] = GetVFX()->GetSky()->m_cloudSpeedLarge;
		jsonOb["Sky"]["cloudSpeedOverall"] = GetVFX()->GetSky()->m_cloudSpeedOverall;
		jsonOb["Sky"]["cloudSpeedSmall"] = GetVFX()->GetSky()->m_cloudSpeedSmall;
		jsonOb["Sky"]["edgeDetailScale"] = GetVFX()->GetSky()->m_edgeDetailScale;
		jsonOb["Sky"]["overlayDetailScale"] = GetVFX()->GetSky()->m_overlayDetailScale;
		jsonOb["Sky"]["speedEdge"] = GetVFX()->GetSky()->m_speedEdge;
		jsonOb["Sky"]["speedHats"] = GetVFX()->GetSky()->m_speedHats;
		jsonOb["Sky"]["speedHats"] = GetVFX()->GetSky()->m_speedHats;
		//jsonOb["Sky"]["sunDiscColorR"] = GetVFX()->GetSky()->m_sunDiscColorR;
		//jsonOb["Sky"]["sunDiscColorG"] = GetVFX()->GetSky()->m_sunDiscColorG;
		//jsonOb["Sky"]["sunDiscColorB"] = GetVFX()->GetSky()->m_sunDiscColorB;
	}

	void SaveSky(String fileName) {
		ofstream i(fileName);
		json jsonOb;
		SaveToJson(jsonOb);
		i << setw(4) << jsonOb;
		i.close();
		GetRenderer()->NotifyBottom(va("Saved %s", fileName));
	}

	void LoadSky(json& jsonOb) {
		GetVFX()->GetSky()->m_cloudSpeedLarge = jsonGet<float>(jsonOb["Sky"], "cloudSpeedLarge", GetVFX()->GetSky()->m_cloudSpeedLarge);
		GetVFX()->GetSky()->m_cloudSpeedOverall = jsonGet<float>(jsonOb["Sky"], "cloudSpeedOverall", GetVFX()->GetSky()->m_cloudSpeedOverall);
		GetVFX()->GetSky()->m_cloudSpeedSmall = jsonGet<float>(jsonOb["Sky"], "cloudSpeedSmall", GetVFX()->GetSky()->m_cloudSpeedSmall);
		GetVFX()->GetSky()->m_edgeDetailScale = jsonGet<float>(jsonOb["Sky"], "edgeDetailScale", GetVFX()->GetSky()->m_edgeDetailScale);
		GetVFX()->GetSky()->m_overlayDetailScale = jsonGet<float>(jsonOb["Sky"], "overlayDetailScale", GetVFX()->GetSky()->m_overlayDetailScale);
		GetVFX()->GetSky()->m_speedEdge = jsonGet<float>(jsonOb["Sky"], "speedEdge", GetVFX()->GetSky()->m_speedEdge);
		GetVFX()->GetSky()->m_speedHats = jsonGet<float>(jsonOb["Sky"], "speedHats", GetVFX()->GetSky()->m_speedHats);
		//GetVFX()->GetSky()->m_sunDiscColorR = jsonGet<float>(jsonOb["Sky"], "sunDiscColorR", GetVFX()->GetSky()->m_sunDiscColorR);
		//GetVFX()->GetSky()->m_sunDiscColorG = jsonGet<float>(jsonOb["Sky"], "sunDiscColorG", GetVFX()->GetSky()->m_sunDiscColorG);
		//GetVFX()->GetSky()->m_sunDiscColorB = jsonGet<float>(jsonOb["Sky"], "sunDiscColorB", GetVFX()->GetSky()->m_sunDiscColorB);
	}
}

void VFXSkyMenu::Init() {
	setParentSubmenu<VFXMenu>();
	setName("VFX Sky", true, true);

	addOption(ButtonOption("Reset sky VFX")
		.addFunction([] {GetVFX()->ResetSky(); })
		.addHotkey().addTranslation()
		.addTooltip("Reset sky VFX"));

	addOption(ButtonOption("Load sky VFX settings")
		.addFunction([] {LoadJsonMenu::GetInstance()->Open(GetInstance(), GetConfig()->GetVFXPath(), [](json& jsonOb) { LoadSky(jsonOb); }); })
		.addTooltip("Load sky VFX settings").addTranslation().addHotkey());

	addString("A file with that name already exists. Try again.");

	addOption(ButtonOption("Save sky VFX settings")
		.addFunction([this] {
		GetMenuInput()->AddToQueue([this] {
			string temp;
			if (GetMenuInput()->Text("Sky name", temp, 2, 15)) {
				String file = va("%s/%s.json", GetConfig()->GetVFXPath(), temp.c_str());
				if (GetConfig()->DoesFileExist(file)) GetRenderer()->NotifyBottom(getString("A file with that name already exists. Try again."));
				else SaveSky(file);
			}});
	}).addTranslation().addHotkey().addTooltip("Save sky VFX settings"));

	addOption(BreakOption());

	addOption(NumberOption<float>(SCROLL, "Small cloud speed")
		.addNumber(GetVFX()->GetSky()->m_cloudSpeedSmall, "%.2f", 0.1f)
		.addTooltip("Small cloud speed").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Large cloud speed")
		.addNumber(GetVFX()->GetSky()->m_cloudSpeedLarge, "%.2f", 0.1f)
		.addTooltip("Small cloud speed").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Overall cloud speed")
		.addNumber(GetVFX()->GetSky()->m_cloudSpeedOverall, "%.2f", 0.1f)
		.addTooltip("Overall cloud speed").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Cloud edge detail scale")
		.addNumber(GetVFX()->GetSky()->m_edgeDetailScale, "%.2f", 0.1f)
		.addTooltip("Cloud edge detail scale").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Cloud overlay detail scale")
		.addNumber(GetVFX()->GetSky()->m_overlayDetailScale, "%.2f", 0.1f)
		.addTooltip("Cloud overlay detail scale").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Cloud hat speed")
		.addNumber(GetVFX()->GetSky()->m_speedEdge, "%.2f", 0.1f)
		.addTooltip("Cloud hat speed").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Cloud edge speed")
		.addNumber(GetVFX()->GetSky()->m_speedEdge, "%.2f", 0.1f)
		.addTooltip("Cloud edge speed").addTranslation().addHotkey());
}

/*Update once when submenu is opened*/
void VFXSkyMenu::UpdateOnce() {}

/*Update while submenu is active*/
void VFXSkyMenu::Update() {}

/*Background update*/
void VFXSkyMenu::FeatureUpdate() {

}

/*Singleton*/
VFXSkyMenu* _instance;
VFXSkyMenu* VFXSkyMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new VFXSkyMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
VFXSkyMenu::~VFXSkyMenu() { delete _instance; }