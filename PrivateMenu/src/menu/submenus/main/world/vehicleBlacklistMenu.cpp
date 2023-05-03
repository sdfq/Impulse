#include "stdafx.h"
#include "vehicleBlacklistMenu.h"
#include "..//worldMenu.h"
#include "backend/pools/entityPool.h"
#include "backend/pools/poolManager.h"
#include "backend/pools/vehiclePool.h"

using namespace VehicleBlacklistMenuVars;

namespace VehicleBlacklistMenuVars 
{
	Vars vars;

	void RemoveVehicleFromList(std::string name)
	{
		std::vector<std::string> buffer;
		for (std::string& s : vars.BlacklistedVehicles)
		{
			if (s != name)
			{
				buffer.push_back(s);
			}
		}
		vars.BlacklistedVehicles = buffer;
	}

	ScrollStruct<int> Action[] = {
		TranslationString("Delete Vehicle", true), 0,
		TranslationString("Teleport To Sea", true), 1,
		TranslationString("Kick From Vehicle", true), 2,
	};
}

void VehicleBlacklistMenu::Init() {
	setParentSubmenu<WorldMenu>();
	setName("Vehicles blacklist", true, true);

	addOption(ToggleOption("Enable blacklist")
		.addToggle(vars.BlacklistEnabled)
		.addTooltip("Enable the vehicles blacklist")
		.addTranslation().addHotkey().canBeSaved());

	addOption(ScrollOption<int>(SCROLLSELECT, "Action")
		.addScroll(vars.Actiontochoose, 0, NUMOF(Action) - 1, Action)
		.addFunction([] {  })
		.addTooltip("Choose what happens to blacklisted vehicle").addTranslation());

	addOption(ButtonOption("Add vehicle")
		.addFunction([]
			{
		GetMenuInput()->AddToQueue([] {
				string temp;
				if (GetMenuInput()->Text("Vehicle codename", temp, 2, 15))
				{
					vars.BlacklistedVehicles.push_back(temp);
				}
	});
			})
		.addTooltip("Add a vehicle to the blacklist [For vehicle model names look in tooltip box with veh spawner]")
		.addHotkey()
		.addTranslation());
}

/*Update once when submenu is opened*/
void VehicleBlacklistMenu::UpdateOnce() {}

/*Update while submenu is active*/
void VehicleBlacklistMenu::Update() {

	if (!vars.BlacklistEnabled) {
		VehiclePool::Update();
	}

	static int TIMER;
	static bool update = true;
	Utils::DoTimedFunction(&TIMER, 250, [] { update = true; });
	
	if (update)
	{
		clearOptionsOffset(3);
		for (std::string& str : vars.BlacklistedVehicles)
		{
			addOption(ButtonOption(str.c_str())
				.addFunction([=]
					{
						RemoveVehicleFromList(str);
						GetMenu()->ResetCurrentOption();
					})
				.addTooltip("Click to remove the vehicle from the blacklist")
				.addTranslation());
		}
		update = false;
	}
}

/*Background update*/
void VehicleBlacklistMenu::FeatureUpdate() 
{
	if (vars.BlacklistEnabled) {
		VehiclePool::Update();

		for (Vehicle& veh : VehiclePool::GetVehicles()) {
			Hash hash = ENTITY::GetEntityModel(veh);
			for (std::string& vehStr : vars.BlacklistedVehicles) {
				if (MISC::GetHashKey(vehStr.c_str()) == hash) {
					if (vars.Actiontochoose == 0) {

						WorldMenuVars::vars.RequestControlOfEnt(veh);
						GetEntityControl()->SimpleDeleteVehicle(veh);

					} else if (vars.Actiontochoose == 1) {

						WorldMenuVars::vars.RequestControlOfEnt(veh);
						ENTITY::SetEntityCoords(veh, 6400.f, 6400.f, 0.f, false, false, false, false);

					} else if (vars.Actiontochoose == 2) {

						WorldMenuVars::vars.RequestControlOfEnt(veh);
						Ped ped = VEHICLE::GetPedInVehicleSeat(veh, -1, 1);
						if (ENTITY::DoesEntityExist(ped) && PED::IsPedInVehicle(ped, veh, true)) {
							BRAIN::ClearPedTasksImmediately(ped);
						}
					}
					break;
				}
			}
		}
	}
}

/*Singleton*/
VehicleBlacklistMenu* _instance;
VehicleBlacklistMenu* VehicleBlacklistMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new VehicleBlacklistMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
VehicleBlacklistMenu::~VehicleBlacklistMenu() { delete _instance; }