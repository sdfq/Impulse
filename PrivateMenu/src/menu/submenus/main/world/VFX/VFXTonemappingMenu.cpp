#include "stdafx.h"
#include "VFXTonemappingMenu.h"
#include "../VFXMenu.h"
#include "../../../loadJsonMenu.h"

using namespace VFXTonemappingMenuVars;

namespace VFXTonemappingMenuVars {
	Vars vars;
	void SaveToJson(json& jsonOb) {
		jsonOb["Tonemapping"]["sunExposure"] = GetVFX()->GetTonemapping()->m_sunExposure;
		jsonOb["Tonemapping"]["brightFilmicA"] = GetVFX()->GetTonemapping()->m_brightFilmicA;
		jsonOb["Tonemapping"]["brightFilmicB"] = GetVFX()->GetTonemapping()->m_brightFilmicB;
		jsonOb["Tonemapping"]["brightFilmicC"] = GetVFX()->GetTonemapping()->m_brightFilmicC;
		jsonOb["Tonemapping"]["brightFilmicD"] = GetVFX()->GetTonemapping()->m_brightFilmicD;
		jsonOb["Tonemapping"]["brightFilmicE"] = GetVFX()->GetTonemapping()->m_brightFilmicE;
		jsonOb["Tonemapping"]["brightFilmicF"] = GetVFX()->GetTonemapping()->m_brightFilmicF;
		jsonOb["Tonemapping"]["brightFilmicW"] = GetVFX()->GetTonemapping()->m_brightFilmicW;
		jsonOb["Tonemapping"]["brightFilmicExposure"] = GetVFX()->GetTonemapping()->m_brightFilmicExposure;
		jsonOb["Tonemapping"]["darkFilmicA"] = GetVFX()->GetTonemapping()->m_darkFilmicA;
		jsonOb["Tonemapping"]["darkFilmicB"] = GetVFX()->GetTonemapping()->m_darkFilmicB;
		jsonOb["Tonemapping"]["darkFilmicC"] = GetVFX()->GetTonemapping()->m_darkFilmicC;
		jsonOb["Tonemapping"]["darkFilmicD"] = GetVFX()->GetTonemapping()->m_darkFilmicD;
		jsonOb["Tonemapping"]["darkFilmicE"] = GetVFX()->GetTonemapping()->m_darkFilmicE;
		jsonOb["Tonemapping"]["darkFilmicF"] = GetVFX()->GetTonemapping()->m_darkFilmicF;
		jsonOb["Tonemapping"]["darkFilmicW"] = GetVFX()->GetTonemapping()->m_darkFilmicW;
		jsonOb["Tonemapping"]["darkFilmicExposure"] = GetVFX()->GetTonemapping()->m_darkFilmicExposure;
	}

	void SaveTonemapping(String fileName) {
		ofstream i(fileName);
		json jsonOb;
		SaveToJson(jsonOb);
		i << setw(4) << jsonOb;
		i.close();
		GetRenderer()->NotifyBottom(va("Saved %s", fileName));
	}

	void LoadTonemapping(json& jsonOb) {
		GetVFX()->GetTonemapping()->m_sunExposure = jsonGet<float>(jsonOb["Tonemapping"], "sunExposure", GetVFX()->GetTonemapping()->m_sunExposure);
		GetVFX()->GetTonemapping()->m_brightFilmicA = jsonGet<float>(jsonOb["Tonemapping"], "brightFilmicA", GetVFX()->GetTonemapping()->m_brightFilmicA);
		GetVFX()->GetTonemapping()->m_brightFilmicB = jsonGet<float>(jsonOb["Tonemapping"], "brightFilmicB", GetVFX()->GetTonemapping()->m_brightFilmicB);
		GetVFX()->GetTonemapping()->m_brightFilmicC = jsonGet<float>(jsonOb["Tonemapping"], "brightFilmicC", GetVFX()->GetTonemapping()->m_brightFilmicC);
		GetVFX()->GetTonemapping()->m_brightFilmicD = jsonGet<float>(jsonOb["Tonemapping"], "brightFilmicD", GetVFX()->GetTonemapping()->m_brightFilmicD);
		GetVFX()->GetTonemapping()->m_brightFilmicE = jsonGet<float>(jsonOb["Tonemapping"], "brightFilmicE", GetVFX()->GetTonemapping()->m_brightFilmicE);
		GetVFX()->GetTonemapping()->m_brightFilmicF = jsonGet<float>(jsonOb["Tonemapping"], "brightFilmicF", GetVFX()->GetTonemapping()->m_brightFilmicF);
		GetVFX()->GetTonemapping()->m_brightFilmicW = jsonGet<float>(jsonOb["Tonemapping"], "brightFilmicW", GetVFX()->GetTonemapping()->m_brightFilmicW);
		GetVFX()->GetTonemapping()->m_brightFilmicExposure = jsonGet<float>(jsonOb["Tonemapping"], "brightFilmicExposure", GetVFX()->GetTonemapping()->m_brightFilmicExposure);

		GetVFX()->GetTonemapping()->m_darkFilmicA = jsonGet<float>(jsonOb["Tonemapping"], "darkFilmicA", GetVFX()->GetTonemapping()->m_darkFilmicA);
		GetVFX()->GetTonemapping()->m_darkFilmicB = jsonGet<float>(jsonOb["Tonemapping"], "darkFilmicB", GetVFX()->GetTonemapping()->m_darkFilmicB);
		GetVFX()->GetTonemapping()->m_darkFilmicC = jsonGet<float>(jsonOb["Tonemapping"], "darkFilmicC", GetVFX()->GetTonemapping()->m_darkFilmicC);
		GetVFX()->GetTonemapping()->m_darkFilmicD = jsonGet<float>(jsonOb["Tonemapping"], "darkFilmicD", GetVFX()->GetTonemapping()->m_darkFilmicD);
		GetVFX()->GetTonemapping()->m_darkFilmicE = jsonGet<float>(jsonOb["Tonemapping"], "darkFilmicE", GetVFX()->GetTonemapping()->m_darkFilmicE);
		GetVFX()->GetTonemapping()->m_darkFilmicF = jsonGet<float>(jsonOb["Tonemapping"], "darkFilmicF", GetVFX()->GetTonemapping()->m_darkFilmicF);
		GetVFX()->GetTonemapping()->m_darkFilmicW = jsonGet<float>(jsonOb["Tonemapping"], "darkFilmicW", GetVFX()->GetTonemapping()->m_darkFilmicW);
		GetVFX()->GetTonemapping()->m_darkFilmicExposure = jsonGet<float>(jsonOb["Tonemapping"], "darkFilmicExposure", GetVFX()->GetTonemapping()->m_darkFilmicExposure);
	}

	float CalculateDay() {
		float A = GetVFX()->GetTonemapping()->m_brightFilmicA;
		float B = GetVFX()->GetTonemapping()->m_brightFilmicB;
		float C = GetVFX()->GetTonemapping()->m_brightFilmicC;
		float D = GetVFX()->GetTonemapping()->m_brightFilmicD;
		float E = GetVFX()->GetTonemapping()->m_brightFilmicE;
		float F = GetVFX()->GetTonemapping()->m_brightFilmicF;
		float W = GetVFX()->GetTonemapping()->m_brightFilmicW;
		float AW = A * W;
		float BC = B * C;
		float DE = D * E;
		float DF = D * F;
		return (W*(AW + BC) + DE) / (W*(AW + B) + DF) - (E / F);
	}

	float CalculateNight() {
		float A = GetVFX()->GetTonemapping()->m_darkFilmicA;
		float B = GetVFX()->GetTonemapping()->m_darkFilmicB;
		float C = GetVFX()->GetTonemapping()->m_darkFilmicC;
		float D = GetVFX()->GetTonemapping()->m_darkFilmicD;
		float E = GetVFX()->GetTonemapping()->m_darkFilmicE;
		float F = GetVFX()->GetTonemapping()->m_darkFilmicF;
		float W = GetVFX()->GetTonemapping()->m_darkFilmicW;
		float AW = A * W;
		float BC = B * C;
		float DE = D * E;
		float DF = D * F;
		return (W*(AW + BC) + DE) / (W*(AW + B) + DF) - (E / F);
	}
}

void VFXTonemappingMenu::Init() {
	setParentSubmenu<VFXMenu>();
	setName("VFX Tone mapping", true, true);

	addOption(ButtonOption("Reset tone mapping VFX")
		.addFunction([] {GetVFX()->ResetTonemapping(); })
		.addHotkey().addTranslation()
		.addTooltip("Reset tone mapping VFX"));

	addOption(ButtonOption("Load tone mapping VFX settings")
		.addFunction([] {LoadJsonMenu::GetInstance()->Open(GetInstance(), GetConfig()->GetVFXPath(), [](json& jsonOb) { LoadTonemapping(jsonOb); }); })
		.addTooltip("Load tone mapping VFX settings").addTranslation().addHotkey());

	addString("A file with that name already exists. Try again.");

	addOption(ButtonOption("Save tone mapping VFX settings")
		.addFunction([this] {
		GetMenuInput()->AddToQueue([this] {
			string temp;
			if (GetMenuInput()->Text("Tone mapping name", temp, 2, 15)) {
				String file = va("%s/%s.json", GetConfig()->GetVFXPath(), temp.c_str());
				if (GetConfig()->DoesFileExist(file)) GetRenderer()->NotifyBottom(getString("A file with that name already exists. Try again."));
				else SaveTonemapping(file);
			}});
	}).addTranslation().addHotkey().addTooltip("Save tone mapping VFX settings"));


	addOption(BreakOption("Equation").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Day:   ~c~(W(AW+BC)+DE) / (W(AW+B)+DF) - (E/F)")
		.addNumber(vars.equationDay, "%.4f", 0)
		.addTooltip("The result of the day tone mapping equation").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Night: ~c~(W(AW+BC)+DE) / (W(AW+B)+DF) - (E/F)")
		.addNumber(vars.equationDay, "%.4f", 0)
		.addTooltip("The result of the night tone mapping equation").addTranslation());

	addOption(BreakOption());

	addOption(NumberOption<float>(SCROLL, "Sun exposure")
		.addNumber(GetVFX()->GetTonemapping()->m_sunExposure, "%.3f", 0.1f)
		.addTooltip("Sun exposure").addTranslation().addHotkey());

	addOption(BreakOption("Day").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Day filmic A")
		.addNumber(GetVFX()->GetTonemapping()->m_brightFilmicA, "%.3f", 0.01f)
		.addTooltip("Day filmic A").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Day filmic B")
		.addNumber(GetVFX()->GetTonemapping()->m_brightFilmicB, "%.3f", 0.01f)
		.addTooltip("Day filmic B").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Day filmic C")
		.addNumber(GetVFX()->GetTonemapping()->m_brightFilmicC, "%.3f", 0.01f)
		.addTooltip("Day filmic C").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Day filmic D")
		.addNumber(GetVFX()->GetTonemapping()->m_brightFilmicD, "%.3f", 0.01f)
		.addTooltip("Day filmic D").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Day filmic E")
		.addNumber(GetVFX()->GetTonemapping()->m_brightFilmicE, "%.3f", 0.01f)
		.addTooltip("Day filmic E").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Day filmic F")
		.addNumber(GetVFX()->GetTonemapping()->m_brightFilmicF, "%.3f", 0.01f)
		.addTooltip("Day filmic F").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Day filmic W")
		.addNumber(GetVFX()->GetTonemapping()->m_brightFilmicW, "%.3f", 0.01f)
		.addTooltip("Day filmic W").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Day exposure")
		.addNumber(GetVFX()->GetTonemapping()->m_brightFilmicExposure, "%.3f", 0.1f)
		.addTooltip("Day exposure").addTranslation().addHotkey());

	addOption(BreakOption("Night").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Night filmic A")
		.addNumber(GetVFX()->GetTonemapping()->m_darkFilmicA, "%.3f", 0.01f)
		.addTooltip("Night filmic A").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Night filmic B")
		.addNumber(GetVFX()->GetTonemapping()->m_darkFilmicB, "%.3f", 0.01f)
		.addTooltip("Night filmic B").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Night filmic C")
		.addNumber(GetVFX()->GetTonemapping()->m_darkFilmicC, "%.3f", 0.01f)
		.addTooltip("Night filmic C").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Night filmic D")
		.addNumber(GetVFX()->GetTonemapping()->m_darkFilmicD, "%.3f", 0.01f)
		.addTooltip("Night filmic D").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Night filmic E")
		.addNumber(GetVFX()->GetTonemapping()->m_darkFilmicE, "%.3f", 0.01f)
		.addTooltip("Night filmic E").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Night filmic F")
		.addNumber(GetVFX()->GetTonemapping()->m_darkFilmicF, "%.3f", 0.01f)
		.addTooltip("Night filmic F").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Night filmic W")
		.addNumber(GetVFX()->GetTonemapping()->m_darkFilmicW, "%.3f", 0.01f)
		.addTooltip("Night filmic W").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Night exposure")
		.addNumber(GetVFX()->GetTonemapping()->m_darkFilmicExposure, "%.3f", 0.1f)
		.addTooltip("Night exposure").addTranslation().addHotkey());
}

/*Update once when submenu is opened*/
void VFXTonemappingMenu::UpdateOnce() {}

/*Update while submenu is active*/
void VFXTonemappingMenu::Update() {
	vars.equationDay = CalculateDay();
	vars.equationNight = CalculateNight();
}

/*Background update*/
void VFXTonemappingMenu::FeatureUpdate() {}

/*Singleton*/
VFXTonemappingMenu* _instance;
VFXTonemappingMenu* VFXTonemappingMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new VFXTonemappingMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
VFXTonemappingMenu::~VFXTonemappingMenu() { delete _instance; }