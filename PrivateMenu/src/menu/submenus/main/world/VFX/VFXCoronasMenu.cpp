#include "stdafx.h"
#include "VFXCoronasMenu.h"
#include "../VFXMenu.h"
#include "../../../loadJsonMenu.h"

using namespace VFXCoronasMenuVars;

namespace VFXCoronasMenuVars {
	Vars vars;

	void SetCoronas(Color& col) {
		GetVFX()->GetCoronas()->m_colorR = (float)col.m_r / 255;
		GetVFX()->GetCoronas()->m_colorG = (float)col.m_g / 255;
		GetVFX()->GetCoronas()->m_colorB = (float)col.m_b / 255;
	}

	void GetCoronas() {
		vars.coronas = { (int)(GetVFX()->GetCoronas()->m_colorR * 255), (int)(GetVFX()->GetCoronas()->m_colorG * 255), (int)(GetVFX()->GetCoronas()->m_colorB * 255), 255 };
	}

	void SaveToJson(json& jsonOb) {
		jsonOb["Coronas"]["colorR"] = GetVFX()->GetCoronas()->m_colorR;
		jsonOb["Coronas"]["colorG"] = GetVFX()->GetCoronas()->m_colorG;
		jsonOb["Coronas"]["colorB"] = GetVFX()->GetCoronas()->m_colorB;
		jsonOb["Coronas"]["globalIntensity"] = GetVFX()->GetCoronas()->m_globalIntensity;
		jsonOb["Coronas"]["globalScreenspaceExpansion"] = GetVFX()->GetCoronas()->m_globalScreenspaceExpansion;
		jsonOb["Coronas"]["globalSize"] = GetVFX()->GetCoronas()->m_globalSize;
		jsonOb["Coronas"]["rotationSpeed"] = GetVFX()->GetCoronas()->m_rotationSpeed;
		jsonOb["Coronas"]["sizeScaleParaboloid"] = GetVFX()->GetCoronas()->m_sizeScaleParaboloid;
		jsonOb["Coronas"]["waterIntensity"] = GetVFX()->GetCoronas()->m_waterIntensity;
		jsonOb["Coronas"]["waterScreenspaceExpansion"] = GetVFX()->GetCoronas()->m_waterScreenspaceExpansion;
		jsonOb["Coronas"]["waterSize"] = GetVFX()->GetCoronas()->m_waterSize;
		jsonOb["Coronas"]["zBiasMultiplier"] = GetVFX()->GetCoronas()->m_zBiasMultiplier;
	}

	void SaveCoronas(String fileName) {
		ofstream i(fileName);
		json jsonOb;
		SaveToJson(jsonOb);
		i << setw(4) << jsonOb;
		i.close();
		GetRenderer()->NotifyBottom(va("Saved %s", fileName));
	}

	void LoadCoronas(json& jsonOb) {
		GetVFX()->GetCoronas()->m_colorR = jsonGet<float>(jsonOb["Coronas"], "colorR", GetVFX()->GetCoronas()->m_colorR);
		GetVFX()->GetCoronas()->m_colorG = jsonGet<float>(jsonOb["Coronas"], "colorG", GetVFX()->GetCoronas()->m_colorG);
		GetVFX()->GetCoronas()->m_colorB = jsonGet<float>(jsonOb["Coronas"], "colorB", GetVFX()->GetCoronas()->m_colorB);
		GetVFX()->GetCoronas()->m_globalIntensity = jsonGet<float>(jsonOb["Coronas"], "globalIntensity", GetVFX()->GetCoronas()->m_globalIntensity);
		GetVFX()->GetCoronas()->m_globalScreenspaceExpansion = jsonGet<float>(jsonOb["Coronas"], "globalScreenspaceExpansion", GetVFX()->GetCoronas()->m_globalScreenspaceExpansion);
		GetVFX()->GetCoronas()->m_globalSize = jsonGet<float>(jsonOb["Coronas"], "globalSize", GetVFX()->GetCoronas()->m_globalSize);
		GetVFX()->GetCoronas()->m_rotationSpeed = jsonGet<float>(jsonOb["Coronas"], "rotationSpeed", GetVFX()->GetCoronas()->m_rotationSpeed);
		GetVFX()->GetCoronas()->m_sizeScaleParaboloid = jsonGet<float>(jsonOb["Coronas"], "sizeScaleParaboloid", GetVFX()->GetCoronas()->m_sizeScaleParaboloid);
		GetVFX()->GetCoronas()->m_waterIntensity = jsonGet<float>(jsonOb["Coronas"], "waterIntensity", GetVFX()->GetCoronas()->m_waterIntensity);
		GetVFX()->GetCoronas()->m_waterScreenspaceExpansion = jsonGet<float>(jsonOb["Coronas"], "waterScreenspaceExpansion", GetVFX()->GetCoronas()->m_waterScreenspaceExpansion);
		GetVFX()->GetCoronas()->m_waterSize = jsonGet<float>(jsonOb["Coronas"], "waterSize", GetVFX()->GetCoronas()->m_waterSize);
		GetVFX()->GetCoronas()->m_zBiasMultiplier = jsonGet<float>(jsonOb["Coronas"], "zBiasMultiplier", GetVFX()->GetCoronas()->m_zBiasMultiplier);
	}
}

void VFXCoronasMenu::Init() {
	setParentSubmenu<VFXMenu>();
	setName("VFX Coronas", true, true);

	addOption(ButtonOption("Reset coronas VFX")
		.addFunction([] {GetVFX()->ResetCoronas(); })
		.addHotkey().addTranslation()
		.addTooltip("Reset coronas VFX"));

	addOption(ButtonOption("Load coronas VFX settings")
		.addFunction([] {LoadJsonMenu::GetInstance()->Open(GetInstance(), GetConfig()->GetVFXPath(), [](json& jsonOb) { LoadCoronas(jsonOb); }); })
		.addTooltip("Load coronas VFX settings").addTranslation().addHotkey());

	addString("A file with that name already exists. Try again.");

	addOption(ButtonOption("Save coronas VFX settings")
		.addFunction([this] {
		GetMenuInput()->AddToQueue([this] {
			string temp;
			if (GetMenuInput()->Text("Coronas name", temp, 2, 15)) {
				String file = va("%s/%s.json", GetConfig()->GetVFXPath(), temp.c_str());
				if (GetConfig()->DoesFileExist(file)) GetRenderer()->NotifyBottom(getString("A file with that name already exists. Try again."));
				else SaveCoronas(file);
			}});
	}).addTranslation().addHotkey().addTooltip("Save coronas VFX settings"));

	addOption(BreakOption());

	addOption(NumberOption<float>(SCROLL, "Coronas global intensity")
		.addNumber(GetVFX()->GetCoronas()->m_globalIntensity, "%.2f", 0.1f)
		.addTooltip("Coronas global intensity").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Coronas water intensity")
		.addNumber(GetVFX()->GetCoronas()->m_waterIntensity, "%.2f", 0.1f)
		.addTooltip("Coronas global intensity").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Coronas global size")
		.addNumber(GetVFX()->GetCoronas()->m_globalSize, "%.2f", 0.1f)
		.addTooltip("Coronas global size").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Coronas global size")
		.addNumber(GetVFX()->GetCoronas()->m_waterSize, "%.2f", 0.1f)
		.addTooltip("Coronas global size").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Coronas global screen space expansion")
		.addNumber(GetVFX()->GetCoronas()->m_globalScreenspaceExpansion, "%.2f", 0.1f)
		.addTooltip("Coronas global screen space expansion").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Coronas water screen space expansion")
		.addNumber(GetVFX()->GetCoronas()->m_waterScreenspaceExpansion, "%.2f", 0.1f)
		.addTooltip("Coronas water screen space expansion").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Coronas rotation speed")
		.addNumber(GetVFX()->GetCoronas()->m_rotationSpeed, "%.2f", 0.1f)
		.addTooltip("Coronas rotation speed").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Coronas size scale paraboloid")
		.addNumber(GetVFX()->GetCoronas()->m_sizeScaleParaboloid, "%.2f", 0.1f)
		.addTooltip("Coronas size scale paraboloid").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Coronas Z bias multiplier")
		.addNumber(GetVFX()->GetCoronas()->m_zBiasMultiplier, "%.2f", 0.1f)
		.addTooltip("Coronas Z bias multiplier").addTranslation().addHotkey());

	addOption(ColorOption("Coronas color")
		.addColor(vars.coronas)
		.addOnUpdate([] { GetCoronas(); })
		.addFunction([] { SetCoronas(vars.coronas); })
		.addTooltip("Coronas color").addTranslation().addHotkey());
}

/*Update once when submenu is opened*/
void VFXCoronasMenu::UpdateOnce() {}

/*Update while submenu is active*/
void VFXCoronasMenu::Update() {}

/*Background update*/
void VFXCoronasMenu::FeatureUpdate() {}

/*Singleton*/
VFXCoronasMenu* _instance;
VFXCoronasMenu* VFXCoronasMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new VFXCoronasMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
VFXCoronasMenu::~VFXCoronasMenu() { delete _instance; }