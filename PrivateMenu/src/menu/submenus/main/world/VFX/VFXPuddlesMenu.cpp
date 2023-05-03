#include "stdafx.h"
#include "VFXPuddlesMenu.h"
#include "../VFXMenu.h"
#include "../../../loadJsonMenu.h"

using namespace VFXPuddlesMenuVars;

namespace VFXPuddlesMenuVars {

	void SaveToJson(json& jsonOb) {
		jsonOb["RainPuddles"]["depth"] = GetVFX()->GetPuddles()->m_depth;
		jsonOb["RainPuddles"]["range"] = GetVFX()->GetPuddles()->m_range;
		jsonOb["RainPuddles"]["dropFactor"] = GetVFX()->GetPuddles()->m_ripples->m_dropFactor;
		jsonOb["RainPuddles"]["maxDuration"] = GetVFX()->GetPuddles()->m_ripples->m_maxDuration;
		jsonOb["RainPuddles"]["maxSize"] = GetVFX()->GetPuddles()->m_ripples->m_maxSize;
		jsonOb["RainPuddles"]["minDuration"] = GetVFX()->GetPuddles()->m_ripples->m_minDuration;
		jsonOb["RainPuddles"]["minSize"] = GetVFX()->GetPuddles()->m_ripples->m_minSize;
		jsonOb["RainPuddles"]["rippleStrength"] = GetVFX()->GetPuddles()->m_ripples->m_dropFactor;
		jsonOb["RainPuddles"]["speed"] = GetVFX()->GetPuddles()->m_ripples->m_speed;
	}

	void SaveRainPuddles(String fileName) {
		ofstream i(fileName);
		json jsonOb;
		SaveToJson(jsonOb);
		i << setw(4) << jsonOb;
		i.close();
		GetRenderer()->NotifyBottom(va("Saved %s", fileName));
	}

	void LoadRainPuddles(json& jsonOb) {
		GetVFX()->GetPuddles()->m_depth = jsonGet<float>(jsonOb["RainPuddles"], "depth", GetVFX()->GetPuddles()->m_depth);
		GetVFX()->GetPuddles()->m_range = jsonGet<float>(jsonOb["RainPuddles"], "range", GetVFX()->GetPuddles()->m_range);
		GetVFX()->GetPuddles()->m_scale = jsonGet<float>(jsonOb["RainPuddles"], "scale", GetVFX()->GetPuddles()->m_scale);
		GetVFX()->GetPuddles()->m_ripples->m_dropFactor = jsonGet<float>(jsonOb["RainPuddles"], "dropFactor", GetVFX()->GetPuddles()->m_ripples->m_dropFactor);
		GetVFX()->GetPuddles()->m_ripples->m_maxDuration = jsonGet<float>(jsonOb["RainPuddles"], "maxDuration", GetVFX()->GetPuddles()->m_ripples->m_maxDuration);
		GetVFX()->GetPuddles()->m_ripples->m_maxSize = jsonGet<float>(jsonOb["RainPuddles"], "maxSize", GetVFX()->GetPuddles()->m_ripples->m_maxSize);
		GetVFX()->GetPuddles()->m_ripples->m_minDuration = jsonGet<float>(jsonOb["RainPuddles"], "minDuration", GetVFX()->GetPuddles()->m_ripples->m_minDuration);
		GetVFX()->GetPuddles()->m_ripples->m_minSize = jsonGet<float>(jsonOb["RainPuddles"], "minSize", GetVFX()->GetPuddles()->m_ripples->m_minSize);
		GetVFX()->GetPuddles()->m_ripples->m_dropFactor = jsonGet<float>(jsonOb["RainPuddles"], "rippleStrength", GetVFX()->GetPuddles()->m_ripples->m_dropFactor);
		GetVFX()->GetPuddles()->m_ripples->m_speed = jsonGet<float>(jsonOb["RainPuddles"], "speed", GetVFX()->GetPuddles()->m_ripples->m_speed);
	}
}

void VFXPuddlesMenu::Init() {
	setParentSubmenu<VFXMenu>();
	setName("VFX Rain Puddles", true, true);

	addOption(ButtonOption("Reset rain puddles VFX")
		.addFunction([] {GetVFX()->ResetPuddles(); })
		.addHotkey().addTranslation()
		.addTooltip("Reset rain puddles VFX"));

	addOption(ButtonOption("Load rain puddles VFX settings")
		.addFunction([] {LoadJsonMenu::GetInstance()->Open(GetInstance(), GetConfig()->GetVFXPath(), [](json& jsonOb) { LoadRainPuddles(jsonOb); }); })
		.addTooltip("Load rain puddles VFX settings").addTranslation().addHotkey());

	addString("A file with that name already exists. Try again.");

	addOption(ButtonOption("Save rain puddles VFX settings")
		.addFunction([this] {
		GetMenuInput()->AddToQueue([this] {
			string temp;
			if (GetMenuInput()->Text("Rain puddles name", temp, 2, 15)) {
				String file = va("%s/%s.json", GetConfig()->GetVFXPath(), temp.c_str());
				if (GetConfig()->DoesFileExist(file)) GetRenderer()->NotifyBottom(getString("A file with that name already exists. Try again."));
				else SaveRainPuddles(file);
			}});
	}).addTranslation().addHotkey().addTooltip("Save rain puddles VFX settings"));

	addOption(BreakOption());

	addOption(NumberOption<float>(SCROLL, "Puddles depth")
		.addNumber(GetVFX()->GetPuddles()->m_depth, "%.2f", 0.1f)
		.addTooltip("Puddles depth").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Puddles range")
		.addNumber(GetVFX()->GetPuddles()->m_range, "%.2f", 0.1f)
		.addTooltip("Puddles range").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Puddles scale")
		.addNumber(GetVFX()->GetPuddles()->m_scale, "%.2f", 0.1f)
		.addTooltip("Puddles scale").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Puddles drop factor")
		.addNumber(GetVFX()->GetPuddles()->m_ripples->m_dropFactor, "%.2f", 0.1f)
		.addTooltip("Puddles drop factor").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Puddles min duration")
		.addNumber(GetVFX()->GetPuddles()->m_ripples->m_minDuration, "%.2f", 0.1f)
		.addTooltip("Puddles min duration").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Puddles max duration")
		.addNumber(GetVFX()->GetPuddles()->m_ripples->m_maxDuration, "%.2f", 0.1f)
		.addTooltip("Puddles max duration").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Puddles min size")
		.addNumber(GetVFX()->GetPuddles()->m_ripples->m_minSize, "%.2f", 0.1f)
		.addTooltip("Puddles min size").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Puddles max size")
		.addNumber(GetVFX()->GetPuddles()->m_ripples->m_maxSize, "%.2f", 0.1f)
		.addTooltip("Puddles max size").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Puddles ripple strength")
		.addNumber(GetVFX()->GetPuddles()->m_ripples->m_rippleStrength, "%.2f", 0.1f)
		.addTooltip("Puddles ripple strength").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Puddles ripple speed")
		.addNumber(GetVFX()->GetPuddles()->m_ripples->m_speed, "%.2f", 0.1f)
		.addTooltip("Puddles ripple speed").addTranslation().addHotkey());
}

/*Update once when submenu is opened*/
void VFXPuddlesMenu::UpdateOnce() {}

/*Update while submenu is active*/
void VFXPuddlesMenu::Update() {}

/*Background update*/
void VFXPuddlesMenu::FeatureUpdate() {}

/*Singleton*/
VFXPuddlesMenu* _instance;
VFXPuddlesMenu* VFXPuddlesMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new VFXPuddlesMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
VFXPuddlesMenu::~VFXPuddlesMenu() { delete _instance; }