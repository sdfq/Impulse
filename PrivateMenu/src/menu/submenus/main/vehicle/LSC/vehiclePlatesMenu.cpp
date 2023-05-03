#include "stdafx.h"
#include "vehiclePlatesMenu.h"
#include "../LSCMenu.h"

using namespace VehiclePlatesMenuVars;

namespace VehiclePlatesMenuVars {
	Vars vars;

	void SetNumberPlate(Vehicle vehicle, String text) {
		VEHICLE::SetVehicleNumberPlateText(vehicle, text);
	}

	ScrollStruct<int> LicensePlates[] = {
		TranslationString("Blue on white", true), 0,
		TranslationString("Yellow on black", true), 1,
		TranslationString("Yellow on white", true), 2,
		TranslationString("Blue on white 2", true), 3,
		TranslationString("Blue on white 3", true), 4,
		TranslationString("Yankton", true), 5
	};
}

void VehiclePlatesMenu::Init() {
	setParentSubmenu<LSCMenu>();
	setName("Plates", true, true);

	addOption(ScrollOption<int>(SCROLL, "License plate")
		.addScroll(vars.licenseplate, 0, NUMOF(LicensePlates) - 1, LicensePlates).canLoop()
		.addFunction([] { VEHICLE::SetVehicleNumberPlateTextIndex(GetLocalPlayer().m_vehicle, vars.licenseplate); })
		.addTooltip("License plate").addTranslation());

	addOption(ButtonOption("Set license plate text")
		.addFunction([] {
		GetMenuInput()->AddToQueue([] {
			string temp;
			if (GetMenuInput()->Text("License plate text", temp, 1, 8)) {
				SetNumberPlate(GetLocalPlayer().m_vehicle, temp.c_str());
			}});
	})
		.addHotkey().addTranslation()
		.addTooltip("Set the license plate text"));
}

/*Update once when submenu is opened*/
void VehiclePlatesMenu::UpdateOnce() {}

/*Update while submenu is active*/
void VehiclePlatesMenu::Update() {
	if (!GetLocalPlayer().m_isInVehicle) GetSubmenuHandler()->SetSubPrevious();

	VEHICLE::SetVehicleModKit(GetLocalPlayer().m_vehicle, 0);

	static int TIMER;
	Utils::DoTimedFunction(&TIMER, 250, [] { vars.licenseplate = VEHICLE::GetVehicleNumberPlateTextIndex(GetLocalPlayer().m_vehicle); });
}

/*Background update*/
void VehiclePlatesMenu::FeatureUpdate() {}

/*Singleton*/
VehiclePlatesMenu* _instance;
VehiclePlatesMenu* VehiclePlatesMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new VehiclePlatesMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
VehiclePlatesMenu::~VehiclePlatesMenu() { delete _instance; }