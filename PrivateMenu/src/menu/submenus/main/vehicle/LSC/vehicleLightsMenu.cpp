#include "stdafx.h"
#include "vehicleLightsMenu.h"
#include "../LSCMenu.h"

using namespace VehicleLightsMenuVars;

namespace VehicleLightsMenuVars {
	Vars vars;

	ScrollStruct<int> Lightcolor[] = {
		TranslationString("Default", true), NULL,
		//TranslationString("White", true), 1,
		TranslationString("Blue", true), 2,
		TranslationString("Electric Blue", true), 3,
		TranslationString("Mint Green", true), 4,
		TranslationString("Lime Green", true), 5,
		TranslationString("Yellow", true), 6,
		TranslationString("Golden Shower", true), 7,
		TranslationString("Orange", true), 8,
		TranslationString("Red", true), 9,
		TranslationString("Pink", true), 10,
		TranslationString("Hot Pink", true), 11,
		TranslationString("Purple", true), 12,
		TranslationString("Backlight", true), 13
	};

	void Rainbowxenos() {
		static int TIMER;
		Utils::DoTimedFunction(&TIMER, 200, [] {
				VEHICLE::_SetVehicleHeadlightColor(GetLocalPlayer().m_vehicle, MISC::GetRandomIntInRange(2, 13));
		});
	}

	void Rainbowneons() {
		if (!GetLocalPlayer().m_isInVehicle) return;
		VEHICLE::_GetVehicleNeonLightsColour(GetLocalPlayer().m_vehicle, &vars.neon.m_r, &vars.neon.m_g, &vars.neon.m_b);
			Vehicle vehicle = GetLocalPlayer().m_vehicle;
			if (vars.neon.m_r > 0 && vars.neon.m_b == 0) {
				vars.neon.m_r--;
				vars.neon.m_g++;
			}
			if (vars.neon.m_g > 0 && vars.neon.m_r == 0) {
				vars.neon.m_g--;
				vars.neon.m_b++;
			}
			if (vars.neon.m_b > 0 && vars.neon.m_g == 0) {
				vars.neon.m_r++;
				vars.neon.m_b--;
			}
			GetEntityControl()->SimpleRequestControl(GetLocalPlayer().m_vehicle);
			VEHICLE::_SetVehicleNeonLightsColour(GetLocalPlayer().m_vehicle, vars.neon.m_r, vars.neon.m_g, vars.neon.m_b);

	}

}

void VehicleLightsMenu::Init() {
	setParentSubmenu<LSCMenu>();
	setName("Lights", true, true);

	addOption(ToggleOption("Xenon lights")
		.addToggle(vars.xenonlights)
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addOnUpdate([] {vars.xenonlights = VEHICLE::IsToggleModOn(GetLocalPlayer().m_vehicle, MOD_XENONLIGHTS); })
		.addFunction([] { VEHICLE::ToggleVehicleMod(GetLocalPlayer().m_vehicle, MOD_XENONLIGHTS, vars.xenonlights); })
		.addTooltip("Xenon lights").addTranslation());

	addOption(ScrollOption<int>(SCROLL, "Xenon lights Color")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addScroll(vars.xenonlightcolor, 0, NUMOF(Lightcolor) - 1, Lightcolor).canLoop()
		.addFunction([] { VEHICLE::_SetVehicleHeadlightColor(GetLocalPlayer().m_vehicle, vars.xenonlightcolor); })
		.addTooltip("Xenon Lights Color").addTranslation());

	addOption(ToggleOption("Rainbow xenon lights")
		.addTranslation().canBeSaved()
		.addToggle(vars.rainbowxenon)
		.addTooltip("This will loop through the color ids for xenon lights").addHotkey());

	addOption(BreakOption("Neon").addTranslation());

	addOption(ColorOption("Neon")
		.addColor(vars.neon)
		.addFunction([] {VEHICLE::_SetVehicleNeonLightsColour(GetLocalPlayer().m_vehicle, vars.neon.m_r, vars.neon.m_g, vars.neon.m_b); })
		.addTooltip("Neon lights color").addTranslation());

	addOption(ToggleOption("Rainbow neon lights")
		.addTranslation().canBeSaved()
		.addFunction([] {VEHICLE::_SetVehicleNeonLightsColour(GetLocalPlayer().m_vehicle, 255, 0, 0); })
		.addToggle(vars.rainbowneons)
		.addTooltip("This will rainbow your neon lights").addHotkey());

	addOption(ToggleOption("Left")
		.addToggle(vars.neonleft)
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addOnUpdate([] {vars.neonleft = VEHICLE::_IsVehicleNeonLightEnabled(GetLocalPlayer().m_vehicle, 0); })
		.addFunction([] { VEHICLE::_SetVehicleNeonLightEnabled(GetLocalPlayer().m_vehicle, 0, vars.neonleft); })
		.addTooltip("Neon left").addTranslation());

	addOption(ToggleOption("Right")
		.addToggle(vars.neonright)
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addOnUpdate([] {vars.neonleft = VEHICLE::_IsVehicleNeonLightEnabled(GetLocalPlayer().m_vehicle, 1); })
		.addFunction([] { VEHICLE::_SetVehicleNeonLightEnabled(GetLocalPlayer().m_vehicle, 1, vars.neonright); })
		.addTooltip("Neon right").addTranslation());

	addOption(ToggleOption("Front")
		.addToggle(vars.neonfront)
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addOnUpdate([] {vars.neonleft = VEHICLE::_IsVehicleNeonLightEnabled(GetLocalPlayer().m_vehicle, 2); })
		.addFunction([] { VEHICLE::_SetVehicleNeonLightEnabled(GetLocalPlayer().m_vehicle, 2, vars.neonfront); })
		.addTooltip("Neon front").addTranslation());

	addOption(ToggleOption("Back")
		.addToggle(vars.neonback)
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addOnUpdate([] {vars.neonleft = VEHICLE::_IsVehicleNeonLightEnabled(GetLocalPlayer().m_vehicle, 3); })
		.addFunction([] { VEHICLE::_SetVehicleNeonLightEnabled(GetLocalPlayer().m_vehicle, 3, vars.neonback); })
		.addTooltip("Neon back").addTranslation());
}

/*Update once when submenu is opened*/
void VehicleLightsMenu::UpdateOnce() {}

/*Update while submenu is active*/
void VehicleLightsMenu::Update() {
	if (!GetLocalPlayer().m_isInVehicle) GetSubmenuHandler()->SetSubPrevious();

	VEHICLE::SetVehicleModKit(GetLocalPlayer().m_vehicle, 0);

	/*static int TIMER;
	Utils::DoTimedFunction(&TIMER, 250, [] { vars.xenonlightcolor = VEHICLE::_GetVehicleHeadlightColor(GetLocalPlayer().m_vehicle); });*/
}

/*Background update*/
void VehicleLightsMenu::FeatureUpdate() {
	if (vars.rainbowxenon) Rainbowxenos();
	if (vars.rainbowneons) Rainbowneons();
}

/*Singleton*/
VehicleLightsMenu* _instance;
VehicleLightsMenu* VehicleLightsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new VehicleLightsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
VehicleLightsMenu::~VehicleLightsMenu() { delete _instance; }