#include "stdafx.h"
#include "VFXVehicleMenu.h"
#include "../VFXMenu.h"
#include "../../../loadJsonMenu.h"

using namespace VFXVehicleMenuVars;

namespace VFXVehicleMenuVars {

	void SaveToJson(json& jsonOb) {
		jsonOb["Vehicle"]["fadeDistance"] = GetVFX()->GetVehicleFade()->m_fadeDistance;
		jsonOb["Vehicle"]["headLightAngle"] = GetVFX()->GetVehicle()->m_headLightAngle;
		jsonOb["Vehicle"]["headLightSplit"] = GetVFX()->GetVehicle()->m_headLightSplit;
		jsonOb["Vehicle"]["headlightIntensity"] = GetVFX()->GetVehicleHeadlights()->m_headlightIntensity;
		jsonOb["Vehicle"]["headlightPlayerIntensity"] = GetVFX()->GetVehicleHeadlights()->m_headlightPlayerIntensity;
		jsonOb["Vehicle"]["headlightPlayerDistance"] = GetVFX()->GetVehicleHeadlights()->m_headlightPlayerDistance;
		jsonOb["Vehicle"]["headlightPlayerExponent"] = GetVFX()->GetVehicleHeadlights()->m_headlightPlayerExponent;
		jsonOb["Vehicle"]["clippingPaneHeight"] = GetVFX()->GetVehicleNeon()->m_clippingPaneHeight;
		jsonOb["Vehicle"]["extendSides"] = GetVFX()->GetVehicleNeon()->m_extendSides;
		jsonOb["Vehicle"]["extentFront"] = GetVFX()->GetVehicleNeon()->m_extentFront;
		jsonOb["Vehicle"]["falloffExponent"] = GetVFX()->GetVehicleNeon()->m_falloffExponent;
		jsonOb["Vehicle"]["intensity"] = GetVFX()->GetVehicleNeon()->m_intensity;
		jsonOb["Vehicle"]["radius"] = GetVFX()->GetVehicleNeon()->m_radius;
	}

	void SaveVehicle(String fileName) {
		ofstream i(fileName);
		json jsonOb;
		SaveToJson(jsonOb);
		i << setw(4) << jsonOb;
		i.close();
		GetRenderer()->NotifyBottom(va("Saved %s", fileName));
	}

	void LoadVehicle(json& jsonOb) {
		GetVFX()->GetVehicleFade()->m_fadeDistance = jsonGet<float>(jsonOb["Vehicle"], "fadeDistance", GetVFX()->GetVehicleFade()->m_fadeDistance);
		GetVFX()->GetVehicle()->m_headLightAngle = jsonGet<float>(jsonOb["Vehicle"], "headLightAngle", GetVFX()->GetVehicle()->m_headLightAngle);
		GetVFX()->GetVehicle()->m_headLightSplit = jsonGet<float>(jsonOb["Vehicle"], "headLightSplit", GetVFX()->GetVehicle()->m_headLightSplit);
		GetVFX()->GetVehicleHeadlights()->m_headlightIntensity = jsonGet<float>(jsonOb["Vehicle"], "headlightIntensity", GetVFX()->GetVehicleHeadlights()->m_headlightIntensity);
		GetVFX()->GetVehicleHeadlights()->m_headlightDistance = jsonGet<float>(jsonOb["Vehicle"], "headlightDistance", GetVFX()->GetVehicleHeadlights()->m_headlightDistance);
		GetVFX()->GetVehicleHeadlights()->m_headlightPlayerIntensity = jsonGet<float>(jsonOb["Vehicle"], "headlightPlayerIntensity", GetVFX()->GetVehicleHeadlights()->m_headlightPlayerIntensity);
		GetVFX()->GetVehicleHeadlights()->m_headlightPlayerDistance = jsonGet<float>(jsonOb["Vehicle"], "headlightPlayerDistance", GetVFX()->GetVehicleHeadlights()->m_headlightPlayerDistance);
		GetVFX()->GetVehicleHeadlights()->m_headlightPlayerExponent = jsonGet<float>(jsonOb["Vehicle"], "headlightPlayerExponent", GetVFX()->GetVehicleHeadlights()->m_headlightPlayerExponent);
		GetVFX()->GetVehicleNeon()->m_clippingPaneHeight = jsonGet<float>(jsonOb["Vehicle"], "clippingPaneHeight", GetVFX()->GetVehicleNeon()->m_clippingPaneHeight);
		GetVFX()->GetVehicleNeon()->m_extendSides = jsonGet<float>(jsonOb["Vehicle"], "extendSides", GetVFX()->GetVehicleNeon()->m_extendSides);
		GetVFX()->GetVehicleNeon()->m_extentFront = jsonGet<float>(jsonOb["Vehicle"], "extentFront", GetVFX()->GetVehicleNeon()->m_extentFront);
		GetVFX()->GetVehicleNeon()->m_falloffExponent = jsonGet<float>(jsonOb["Vehicle"], "falloffExponent", GetVFX()->GetVehicleNeon()->m_falloffExponent);
		GetVFX()->GetVehicleNeon()->m_intensity = jsonGet<float>(jsonOb["Vehicle"], "intensity", GetVFX()->GetVehicleNeon()->m_intensity);
		GetVFX()->GetVehicleNeon()->m_radius = jsonGet<float>(jsonOb["Vehicle"], "radius", GetVFX()->GetVehicleNeon()->m_radius);
	}
}

void VFXVehicleMenu::Init() {
	setParentSubmenu<VFXMenu>();
	setName("VFX Vehicle", true, true);

	addOption(ButtonOption("Reset vehicle VFX")
		.addFunction([] {GetVFX()->ResetVehicle(); GetVFX()->ResetVehicleFade(); GetVFX()->ResetVehicleHeadlights(); GetVFX()->ResetTrafficLights(); })
		.addHotkey().addTranslation()
		.addTooltip("Reset vehicle VFX"));

	addOption(ButtonOption("Load vehicle VFX settings")
		.addFunction([] {LoadJsonMenu::GetInstance()->Open(GetInstance(), GetConfig()->GetVFXPath(), [](json& jsonOb) { LoadVehicle(jsonOb); }); })
		.addTooltip("Load vehicle VFX settings").addTranslation().addHotkey());

	addString("A file with that name already exists. Try again.");

	addOption(ButtonOption("Save vehicle VFX settings")
		.addFunction([this] {
		GetMenuInput()->AddToQueue([this] {
			string temp;
			if (GetMenuInput()->Text("Vehicle name", temp, 2, 15)) {
				String file = va("%s/%s.json", GetConfig()->GetVFXPath(), temp.c_str());
				if (GetConfig()->DoesFileExist(file)) GetRenderer()->NotifyBottom(getString("A file with that name already exists. Try again."));
				else SaveVehicle(file);
			}});
	}).addTranslation().addHotkey().addTooltip("Save vehicle VFX settings"));

	addOption(BreakOption());

	addOption(NumberOption<float>(SCROLL, "Fade distance")
		.addNumber(GetVFX()->GetVehicleFade()->m_fadeDistance, "%.2f", 1)
		.addTooltip("Fade distance").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Headlight angle")
		.addNumber(GetVFX()->GetVehicle()->m_headLightAngle, "%.2f", 0.1f)
		.addTooltip("Headlight angle").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Headlight split")
		.addNumber(GetVFX()->GetVehicle()->m_headLightSplit, "%.2f", 0.1f)
		.addTooltip("Headlight split").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Headlight distance")
		.addNumber(GetVFX()->GetVehicleHeadlights()->m_headlightDistance, "%.2f", 0.1f)
		.addTooltip("Headlight distance").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Headlight intensity")
		.addNumber(GetVFX()->GetVehicleHeadlights()->m_headlightIntensity, "%.2f", 0.1f)
		.addTooltip("Headlight intensity").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Player headlight distance")
		.addNumber(GetVFX()->GetVehicleHeadlights()->m_headlightPlayerDistance, "%.2f", 0.1f)
		.addTooltip("Player headlight distance").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Player headlight exponent")
		.addNumber(GetVFX()->GetVehicleHeadlights()->m_headlightPlayerExponent, "%.2f", 0.1f)
		.addTooltip("Player headlight exponent").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Player headlight intensity")
		.addNumber(GetVFX()->GetVehicleHeadlights()->m_headlightPlayerIntensity, "%.2f", 0.1f)
		.addTooltip("Player headlight intensity").addTranslation().addHotkey());

	addOption(BreakOption("Neon").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Neon intensity")
		.addNumber(GetVFX()->GetVehicleNeon()->m_intensity, "%.2f", 0.1f)
		.addTooltip("Neon intensity").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Neon radius")
		.addNumber(GetVFX()->GetVehicleNeon()->m_radius, "%.2f", 0.1f)
		.addTooltip("Neon radius").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Neon extended sides")
		.addNumber(GetVFX()->GetVehicleNeon()->m_extendSides, "%.2f", 0.1f)
		.addTooltip("Neon side width").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Neon extended front")
		.addNumber(GetVFX()->GetVehicleNeon()->m_extentFront, "%.2f", 0.1f)
		.addTooltip("Neon front width").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Neon falloff exponent")
		.addNumber(GetVFX()->GetVehicleNeon()->m_falloffExponent, "%.2f", 0.1f)
		.addTooltip("Neon falloff exponent").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Neon clipping pane height")
		.addNumber(GetVFX()->GetVehicleNeon()->m_clippingPaneHeight, "%.2f", 0.1f)
		.addTooltip("Neon clipping pane height").addTranslation().addHotkey());
}

/*Update once when submenu is opened*/
void VFXVehicleMenu::UpdateOnce() {}

/*Update while submenu is active*/
void VFXVehicleMenu::Update() {}

/*Background update*/
void VFXVehicleMenu::FeatureUpdate() {}

/*Singleton*/
VFXVehicleMenu* _instance;
VFXVehicleMenu* VFXVehicleMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new VFXVehicleMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
VFXVehicleMenu::~VFXVehicleMenu() { delete _instance; }