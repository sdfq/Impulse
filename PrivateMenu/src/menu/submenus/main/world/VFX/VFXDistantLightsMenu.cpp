#include "stdafx.h"
#include "VFXDistantLightsMenu.h"
#include "../VFXMenu.h"
#include "../../../loadJsonMenu.h"

using namespace VFXDistantLightsMenuVars;

namespace VFXDistantLightsMenuVars {
	Vars vars;

	void SetVehicle1(Color& col) {
		GetVFX()->GetDistantLights()->m_vehicleColorR = (float)col.m_r / 255;
		GetVFX()->GetDistantLights()->m_vehicleColorG = (float)col.m_g / 255;
		GetVFX()->GetDistantLights()->m_vehicleColorB = (float)col.m_b / 255;
	}

	void SetVehicle2(Color& col) {
		GetVFX()->GetDistantLights()->m_vehicleColor2R = (float)col.m_r / 255;
		GetVFX()->GetDistantLights()->m_vehicleColor2G = (float)col.m_g / 255;
		GetVFX()->GetDistantLights()->m_vehicleColor2B = (float)col.m_b / 255;
	}
	void GetVehicle1() {
		vars.vehicle1 = { (int)(GetVFX()->GetDistantLights()->m_vehicleColorR * 255), (int)(GetVFX()->GetDistantLights()->m_vehicleColorG * 255), (int)(GetVFX()->GetDistantLights()->m_vehicleColorB * 255), 255 };
	}

	void GetVehicle2() {
		vars.vehicle2 = { (int)(GetVFX()->GetDistantLights()->m_vehicleColor2R * 255), (int)(GetVFX()->GetDistantLights()->m_vehicleColor2G * 255), (int)(GetVFX()->GetDistantLights()->m_vehicleColor2B * 255), 255 };
	}

	void SaveToJson(json& jsonOb) {
		jsonOb["DistantLights"]["flicker"] = GetVFX()->GetDistantLights()->m_flicker;
		jsonOb["DistantLights"]["hourEnd"] = GetVFX()->GetDistantLights()->m_hourEnd;
		jsonOb["DistantLights"]["hourStart"] = GetVFX()->GetDistantLights()->m_hourStart;
		jsonOb["DistantLights"]["reflectionsSize"] = GetVFX()->GetDistantLights()->m_reflectionsSize;
		jsonOb["DistantLights"]["size"] = GetVFX()->GetDistantLights()->m_size;
		jsonOb["DistantLights"]["sizeMin"] = GetVFX()->GetDistantLights()->m_sizeMin;
		jsonOb["DistantLights"]["sizeUpscale"] = GetVFX()->GetDistantLights()->m_sizeUpscale;
		jsonOb["DistantLights"]["sizeUpscaleReflections"] = GetVFX()->GetDistantLights()->m_sizeUpscaleReflections;
		jsonOb["DistantLights"]["speedX"] = GetVFX()->GetDistantLights()->m_speed.x;
		jsonOb["DistantLights"]["speedY"] = GetVFX()->GetDistantLights()->m_speed.y;
		jsonOb["DistantLights"]["speedZ"] = GetVFX()->GetDistantLights()->m_speed.z;
		//jsonOb["DistantLights"]["streetlightColorR"] = GetVFX()->GetDistantLights()->m_streetlightColorR;
		//jsonOb["DistantLights"]["streetlightColorG"] = GetVFX()->GetDistantLights()->m_streetlightColorG;
		//jsonOb["DistantLights"]["streetlightColorB"] = GetVFX()->GetDistantLights()->m_streetlightColorB;
		jsonOb["DistantLights"]["streetlightHDRIntensity"] = GetVFX()->GetDistantLights()->m_streetlightHDRIntensity;
		jsonOb["DistantLights"]["streetlightHourEnd"] = GetVFX()->GetDistantLights()->m_streetlightHourEnd;
		jsonOb["DistantLights"]["streetlightHourStart"] = GetVFX()->GetDistantLights()->m_streetlightHourStart;
		jsonOb["DistantLights"]["twinkleAmount"] = GetVFX()->GetDistantLights()->m_twinkleAmount;
		jsonOb["DistantLights"]["twinkleSpeed"] = GetVFX()->GetDistantLights()->m_twinkleSpeed;
		jsonOb["DistantLights"]["vehicleColorR"] = GetVFX()->GetDistantLights()->m_vehicleColorR;
		jsonOb["DistantLights"]["vehicleColorG"] = GetVFX()->GetDistantLights()->m_vehicleColorG;
		jsonOb["DistantLights"]["vehicleColorB"] = GetVFX()->GetDistantLights()->m_vehicleColorB;
		jsonOb["DistantLights"]["vehicleColor2R"] = GetVFX()->GetDistantLights()->m_vehicleColor2R;
		jsonOb["DistantLights"]["vehicleColor2G"] = GetVFX()->GetDistantLights()->m_vehicleColor2G;
		jsonOb["DistantLights"]["vehicleColor2B"] = GetVFX()->GetDistantLights()->m_vehicleColor2B;
		jsonOb["DistantLights"]["vehicleHDRIntensity"] = GetVFX()->GetDistantLights()->m_vehicleHDRIntensity;
		jsonOb["DistantLights"]["vehicleZOffset"] = GetVFX()->GetDistantLights()->m_vehicleZOffset;
	}
	void SaveDistantLights(String fileName) {
		ofstream i(fileName);
		json jsonOb;
		SaveToJson(jsonOb);
		i << setw(4) << jsonOb;
		i.close();
		GetRenderer()->NotifyBottom(va("Saved %s", fileName));
	}

	void LoadDistantLights(json& jsonOb) {
		GetVFX()->GetDistantLights()->m_flicker = jsonGet<float>(jsonOb["DistantLights"], "flicker", GetVFX()->GetDistantLights()->m_flicker);
		GetVFX()->GetDistantLights()->m_hourEnd = jsonGet<float>(jsonOb["DistantLights"], "hourEnd", GetVFX()->GetDistantLights()->m_hourEnd);
		GetVFX()->GetDistantLights()->m_hourStart = jsonGet<float>(jsonOb["DistantLights"], "hourStart", GetVFX()->GetDistantLights()->m_hourStart);
		GetVFX()->GetDistantLights()->m_reflectionsSize = jsonGet<float>(jsonOb["DistantLights"], "reflectionsSize", GetVFX()->GetDistantLights()->m_reflectionsSize);
		GetVFX()->GetDistantLights()->m_size = jsonGet<float>(jsonOb["DistantLights"], "size", GetVFX()->GetDistantLights()->m_size);
		GetVFX()->GetDistantLights()->m_sizeMin = jsonGet<float>(jsonOb["DistantLights"], "sizeMin", GetVFX()->GetDistantLights()->m_sizeMin);
		GetVFX()->GetDistantLights()->m_sizeUpscale = jsonGet<float>(jsonOb["DistantLights"], "sizeUpscale", GetVFX()->GetDistantLights()->m_sizeUpscale);
		GetVFX()->GetDistantLights()->m_sizeUpscaleReflections = jsonGet<float>(jsonOb["DistantLights"], "sizeUpscaleReflections", GetVFX()->GetDistantLights()->m_sizeUpscaleReflections);
		GetVFX()->GetDistantLights()->m_speed.x = jsonGet<float>(jsonOb["DistantLights"], "speedX", GetVFX()->GetDistantLights()->m_speed.x);
		GetVFX()->GetDistantLights()->m_speed.y = jsonGet<float>(jsonOb["DistantLights"], "speedY", GetVFX()->GetDistantLights()->m_speed.y);
		GetVFX()->GetDistantLights()->m_speed.z = jsonGet<float>(jsonOb["DistantLights"], "speedZ", GetVFX()->GetDistantLights()->m_speed.z);
		//GetVFX()->GetDistantLights()->m_streetlightColorR = jsonGet<float>(jsonOb["DistantLights"], "streetlightColorR", GetVFX()->GetDistantLights()->m_streetlightColorR);
		//GetVFX()->GetDistantLights()->m_streetlightColorG = jsonGet<float>(jsonOb["DistantLights"], "streetlightColorG", GetVFX()->GetDistantLights()->m_streetlightColorG);
		//GetVFX()->GetDistantLights()->m_streetlightColorB = jsonGet<float>(jsonOb["DistantLights"], "streetlightColorB", GetVFX()->GetDistantLights()->m_streetlightColorB);
		GetVFX()->GetDistantLights()->m_streetlightHDRIntensity = jsonGet<float>(jsonOb["DistantLights"], "streetlightHDRIntensity", GetVFX()->GetDistantLights()->m_streetlightHDRIntensity);
		GetVFX()->GetDistantLights()->m_streetlightHourEnd = jsonGet<float>(jsonOb["DistantLights"], "streetlightHourEnd", GetVFX()->GetDistantLights()->m_streetlightHourEnd);
		GetVFX()->GetDistantLights()->m_streetlightHourStart = jsonGet<float>(jsonOb["DistantLights"], "streetlightHourStart", GetVFX()->GetDistantLights()->m_streetlightHourStart);
		GetVFX()->GetDistantLights()->m_twinkleAmount = jsonGet<float>(jsonOb["DistantLights"], "twinkleAmount", GetVFX()->GetDistantLights()->m_twinkleAmount);
		GetVFX()->GetDistantLights()->m_twinkleSpeed = jsonGet<float>(jsonOb["DistantLights"], "twinkleSpeed", GetVFX()->GetDistantLights()->m_twinkleSpeed);
		GetVFX()->GetDistantLights()->m_vehicleColorR = jsonGet<float>(jsonOb["DistantLights"], "vehicleColorR", GetVFX()->GetDistantLights()->m_vehicleColorR);
		GetVFX()->GetDistantLights()->m_vehicleColorG = jsonGet<float>(jsonOb["DistantLights"], "vehicleColorG", GetVFX()->GetDistantLights()->m_vehicleColorG);
		GetVFX()->GetDistantLights()->m_vehicleColorB = jsonGet<float>(jsonOb["DistantLights"], "vehicleColorB", GetVFX()->GetDistantLights()->m_vehicleColorB);
		GetVFX()->GetDistantLights()->m_vehicleColor2R = jsonGet<float>(jsonOb["DistantLights"], "vehicleColor2R", GetVFX()->GetDistantLights()->m_vehicleColor2R);
		GetVFX()->GetDistantLights()->m_vehicleColor2G = jsonGet<float>(jsonOb["DistantLights"], "vehicleColor2G", GetVFX()->GetDistantLights()->m_vehicleColor2G);
		GetVFX()->GetDistantLights()->m_vehicleColor2B = jsonGet<float>(jsonOb["DistantLights"], "vehicleColor2B", GetVFX()->GetDistantLights()->m_vehicleColor2B);
		GetVFX()->GetDistantLights()->m_vehicleHDRIntensity = jsonGet<float>(jsonOb["DistantLights"], "vehicleHDRIntensity", GetVFX()->GetDistantLights()->m_vehicleHDRIntensity);
		GetVFX()->GetDistantLights()->m_vehicleZOffset = jsonGet<float>(jsonOb["DistantLights"], "vehicleZOffset", GetVFX()->GetDistantLights()->m_vehicleZOffset);
	}
}

void VFXDistantLightsMenu::Init() {
	setParentSubmenu<VFXMenu>();
	setName("VFX Distant Lights", true, true);

	addOption(ButtonOption("Reset distant lights VFX")
		.addFunction([] {GetVFX()->ResetDistantLights(); })
		.addHotkey().addTranslation()
		.addTooltip("Reset distant lights VFX"));

	addOption(ButtonOption("Load distant lights VFX settings")
		.addFunction([] {LoadJsonMenu::GetInstance()->Open(GetInstance(), GetConfig()->GetVFXPath(), [](json& jsonOb) { LoadDistantLights(jsonOb); }); })
		.addTooltip("Load distant lights VFX settings").addTranslation().addHotkey());

	addString("A file with that name already exists. Try again.");

	addOption(ButtonOption("Save distant lights VFX settings")
		.addFunction([this] {
		GetMenuInput()->AddToQueue([this] {
			string temp;
			if (GetMenuInput()->Text("Distant lights name", temp, 2, 15)) {
				String file = va("%s/%s.json", GetConfig()->GetVFXPath(), temp.c_str());
				if (GetConfig()->DoesFileExist(file)) GetRenderer()->NotifyBottom(getString("A file with that name already exists. Try again."));
				else SaveDistantLights(file);
			}});
	}).addTranslation().addHotkey().addTooltip("Save distant lights VFX settings"));

	addOption(BreakOption());

	addOption(NumberOption<float>(SCROLL, "Distant lights start hour")
		.addNumber(GetVFX()->GetDistantLights()->m_hourStart, "%.1f", 1)
		.addTooltip("Distant start hour").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Distant lights end hour")
		.addNumber(GetVFX()->GetDistantLights()->m_hourEnd, "%.1f", 1)
		.addTooltip("Distant end hour").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Distant lights street light start hour")
		.addNumber(GetVFX()->GetDistantLights()->m_streetlightHourStart, "%.1f", 1)
		.addTooltip("Distant start hour").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Distant lights street light end hour")
		.addNumber(GetVFX()->GetDistantLights()->m_streetlightHourEnd, "%.1f", 1)
		.addTooltip("Distant end hour").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Distant lights flicker")
		.addNumber(GetVFX()->GetDistantLights()->m_flicker, "%.2f", 0.1f)
		.addTooltip("Distant lights flicker").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Distant lights twinkle speed")
		.addNumber(GetVFX()->GetDistantLights()->m_twinkleSpeed, "%.2f", 0.1f)
		.addTooltip("Distant vehicle twinkle speed").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Distant lights twinkle amount")
		.addNumber(GetVFX()->GetDistantLights()->m_twinkleAmount, "%.2f", 0.1f)
		.addTooltip("Distant vehicle twinkle amount").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Distant lights size")
		.addNumber(GetVFX()->GetDistantLights()->m_size, "%.2f", 0.1f)
		.addTooltip("Distant lights size").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Distant lights min size")
		.addNumber(GetVFX()->GetDistantLights()->m_sizeMin, "%.2f", 0.1f)
		.addTooltip("Distant lights min size").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Distant lights reflection size")
		.addNumber(GetVFX()->GetDistantLights()->m_reflectionsSize, "%.2f", 0.1f)
		.addTooltip("Distant lights reflection size").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Distant lights size upscale")
		.addNumber(GetVFX()->GetDistantLights()->m_sizeUpscale, "%.2f", 0.1f)
		.addTooltip("Distant lights size upscale").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Distant lights size upscale reflections")
		.addNumber(GetVFX()->GetDistantLights()->m_sizeUpscaleReflections, "%.2f", 0.1f)
		.addTooltip("Distant lights size upscale reflections").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Distant lights speed 1")
		.addNumber(GetVFX()->GetDistantLights()->m_speed.x, "%.2f", 0.1f)
		.addTooltip("Distant lights speed 1").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Distant lights speed 2")
		.addNumber(GetVFX()->GetDistantLights()->m_speed.y, "%.2f", 0.1f)
		.addTooltip("Distant lights speed 2").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Distant lights speed 3")
		.addNumber(GetVFX()->GetDistantLights()->m_speed.z, "%.2f", 0.1f)
		.addTooltip("Distant lights speed 3").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Distant lights vehicle light z offset")
		.addNumber(GetVFX()->GetDistantLights()->m_vehicleZOffset, "%.2f", 0.1f)
		.addTooltip("Distant vehicle light z offset").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Distant lights street light intensity")
		.addNumber(GetVFX()->GetDistantLights()->m_streetlightHDRIntensity, "%.2f", 0.1f)
		.addTooltip("Distant street light intensity").addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Distant lights vehicle light intensity")
		.addNumber(GetVFX()->GetDistantLights()->m_vehicleHDRIntensity, "%.2f", 0.1f)
		.addTooltip("Distant vehicle light intensity").addTranslation().addHotkey());

	addOption(ColorOption("Vehicle color 1")
		.addColor(vars.vehicle1)
		.addOnUpdate([] { GetVehicle1(); })
		.addFunction([] { SetVehicle1(vars.vehicle1); })
		.addTooltip("Vehicle color 1").addTranslation().addHotkey());

	addOption(ColorOption("Vehicle color 2")
		.addColor(vars.vehicle2)
		.addOnUpdate([] { GetVehicle2(); })
		.addFunction([] { SetVehicle2(vars.vehicle2); })
		.addTooltip("Vehicle color 2").addTranslation().addHotkey());
}

/*Update once when submenu is opened*/
void VFXDistantLightsMenu::UpdateOnce() {}

/*Update while submenu is active*/
void VFXDistantLightsMenu::Update() {}

/*Background update*/
void VFXDistantLightsMenu::FeatureUpdate() {}

/*Singleton*/
VFXDistantLightsMenu* _instance;
VFXDistantLightsMenu* VFXDistantLightsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new VFXDistantLightsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
VFXDistantLightsMenu::~VFXDistantLightsMenu() { delete _instance; }