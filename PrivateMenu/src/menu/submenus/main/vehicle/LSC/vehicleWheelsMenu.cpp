#include "stdafx.h"
#include "vehicleWheelsMenu.h"
#include "../LSCMenu.h"

using namespace VehicleWheelsMenuVars;

namespace VehicleWheelsMenuVars {
	Vars vars;

	vector <shared_ptr<VehicleOption>> m_vehOptions;

	ScrollStruct<int> wheelTypes[] = {
		TranslationString("Sport", true), 0,
		TranslationString("Muscle", true), 1,
		TranslationString("Lowrider", true), 2,
		TranslationString("SUV", true), 3,
		TranslationString("Offroad", true), 4,
		TranslationString("Tuner", true), 5,
		TranslationString("Bike Wheels", true), 6,
		TranslationString("High end", true), 7,
		TranslationString("Benny Wheels", true), 8,
		TranslationString("Benny Wheels 2", true), 9
	};

	void Bullsetproof(Vehicle veh) {
		GetEntityControl()->RequestControl("[BPT]", veh, [](Entity veh) {
			VEHICLE::SetVehicleTyresCanBurst(veh, 0);
			VEHICLE::SetVehicleWheelsCanBreak(veh, 0);
		});
	}
}

void VehicleWheelsMenu::Init() {
	setParentSubmenu<LSCMenu>();
	setName("Wheels", true, true);

	addOption(ToggleOption("Tire smoke")
		.addToggle(vars.tiresmoke)
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addOnUpdate([] {vars.tiresmoke = VEHICLE::IsToggleModOn(GetLocalPlayer().m_vehicle, MOD_TIRESMOKE); })
		.addFunction([] {VEHICLE::ToggleVehicleMod(GetLocalPlayer().m_vehicle, MOD_TIRESMOKE, vars.tiresmoke); })
		.addTooltip("Tire smoke").addTranslation());

	addOption(ColorOption("Tire smoke color")
		.addColor(vars.tiresmokecol)
		.addFunction([] {VEHICLE::SetVehicleTyreSmokeColor(GetLocalPlayer().m_vehicle, vars.tiresmokecol.m_r, vars.tiresmokecol.m_g, vars.tiresmokecol.m_b); })
		.addTooltip("Vehicle tire smoke color").addTranslation());

	addOption(ToggleOption("Bulletproof wheels")
		.addToggle(vars.bulletproofwheels)
		.addFunction([] { 
		if (!vars.bulletproofwheels) {
			VEHICLE::SetVehicleTyresCanBurst(GetLocalPlayer().m_vehicle, 1);
			VEHICLE::SetVehicleWheelsCanBreak(GetLocalPlayer().m_vehicle, 1);
		}
		})
		.addTooltip("Set your vehicles wheels to bulletproof").addTranslation());

	/*addOption(ColorOption("Wheel color")
		.addColor(vars.tiresmokecol)
		.addFunction([] {
		VEHICLE::SetVehicleTyreSmokeColor(GetLocalPlayer().m_vehicle, vars.tiresmokecol.m_r, vars.tiresmokecol.m_g, vars.tiresmokecol.m_b); 
	})
		.addTooltip("Vehicle wheel color").addTranslation());*/

	addOption(BreakOption());

	addOption(ScrollOption<int>(SCROLL, "Wheel type")
		.addRequirement([] { return GetLocalPlayer().m_isInVehicle; })
		.addScroll(vars.wheeltype, 0, NUMOF(wheelTypes) - 1, wheelTypes)
		.addFunction([] { VEHICLE::SetVehicleWheelType(GetLocalPlayer().m_vehicle, vars.wheeltype); })
		.addTooltip("Wheel type").addTranslation());

	m_vehOptions.push_back(addOption(VehicleOption("Wheels")
		.addMod(MOD_FRONTWHEELS)
		.addTooltip("Wheels").addTranslation()));

	m_vehOptions.push_back(addOption(VehicleOption("Rear wheels")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && VEHICLE::IsThisModelABike(ENTITY::GetEntityModel(GetLocalPlayer().m_vehicle)); })
		.addMod(MOD_BACKWHEELS)
		.addTooltip("Rear wheels").addTranslation()));

}

/*Update once when submenu is opened*/
void VehicleWheelsMenu::UpdateOnce() {}

/*Update while submenu is active*/
void VehicleWheelsMenu::Update() {
	if (!GetLocalPlayer().m_isInVehicle) GetSubmenuHandler()->SetSubPrevious(true);

	if (vars.bulletproofwheels) Bullsetproof;

	VEHICLE::SetVehicleModKit(GetLocalPlayer().m_vehicle, 0);
	for (auto& a : m_vehOptions) {
		a->checkVisibility();
	}
}

/*Background update*/
void VehicleWheelsMenu::FeatureUpdate() {}

/*Singleton*/
VehicleWheelsMenu* _instance;
VehicleWheelsMenu* VehicleWheelsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new VehicleWheelsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
VehicleWheelsMenu::~VehicleWheelsMenu() { delete _instance; }