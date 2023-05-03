#include "stdafx.h"
#include "sessionSpawnVehicleMenu.h"
#include "sessionSpawnerTypeMenu.h"
#include "../../allPlayersMenu.h"

using namespace SessionSpawnVehicleMenuVars;

SessionSpawnerTypeMenu* SessionSpawnVehicleMenu::spawnerTypeMenus[23];

namespace SessionSpawnVehicleMenuVars {
	Vars vars;

	int spawn = 0;
	int vehicleSub;

	SessionSpawnerTypeMenu* GetVehicleSub() {
		return SessionSpawnVehicleMenu::spawnerTypeMenus[vehicleSub];
	}
}

void SessionSpawnVehicleMenu::addSpawner(int num, String name, String* vehicles, int size) {
	spawnerTypeMenus[num] = new SessionSpawnerTypeMenu(name, vehicles, size);
	spawnerTypeMenus[num]->getName().SetMapped(name);
	GetSubmenuHandler()->addSubmenu(spawnerTypeMenus[num]);
	vehicleSub = num;
	addOption(SubmenuOption(name).addTranslation()
		.addSubmenu(spawnerTypeMenus[num])
		.addTooltip(name).addHotkey());
}

void SessionSpawnVehicleMenu::Init() {
	setParentSubmenu<AllPlayersMenu>();
	setName("Spawn vehicle", true, false);

	addSpawner(spawn++, "Super", super, NUMOF(super));
	addSpawner(spawn++, "Sport", sports, NUMOF(sports));
	addSpawner(spawn++, "Sports classic", sportsclassic, NUMOF(sportsclassic));
	addSpawner(spawn++, "Off road", offroad, NUMOF(offroad));
	addSpawner(spawn++, "Sedan", sedans, NUMOF(sedans));
	addSpawner(spawn++, "SUV", suv, NUMOF(suv));
	addSpawner(spawn++, "Coupe", coupes, NUMOF(coupes));
	addSpawner(spawn++, "Muscle", muscle, NUMOF(muscle));
	addSpawner(spawn++, "Compact", compacts, NUMOF(compacts));
	addSpawner(spawn++, "Van", van, NUMOF(van));
	addSpawner(spawn++, "Commercial", commercial, NUMOF(commercial));
	addSpawner(spawn++, "Industrial", industrial, NUMOF(industrial));
	addSpawner(spawn++, "Military", military, NUMOF(military));
	addSpawner(spawn++, "Service", service, NUMOF(service));
	addSpawner(spawn++, "Emergency", emergency, NUMOF(emergency));
	addOption(BreakOption("Bikes").addTranslation());
	addSpawner(spawn++, "Motorcycle", motorcycles, NUMOF(motorcycles));
	addSpawner(spawn++, "Cycle", cycles, NUMOF(cycles));
	addOption(BreakOption("Flying").addTranslation());
	addSpawner(spawn++, "Planes", planes, NUMOF(planes));
	addSpawner(spawn++, "Helicopters", helicopters, NUMOF(helicopters));
	addOption(BreakOption("Boats").addTranslation());
	addSpawner(spawn++, "Boats", boats, NUMOF(boats));
	addOption(BreakOption("Misc").addTranslation());
	addSpawner(spawn++, "Trains", trains, NUMOF(trains));
	addSpawner(spawn++, "Trailer", trailer, NUMOF(trailer));
	addSpawner(spawn, "Utility", utility, NUMOF(utility));
}

/*Update once when submenu is opened*/
void SessionSpawnVehicleMenu::UpdateOnce() {}

/*Update while submenu is active*/
void SessionSpawnVehicleMenu::Update() {}

/*Background update*/
void SessionSpawnVehicleMenu::FeatureUpdate() {}

/*Singleton*/
SessionSpawnVehicleMenu* _instance;
SessionSpawnVehicleMenu* SessionSpawnVehicleMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new SessionSpawnVehicleMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
SessionSpawnVehicleMenu::~SessionSpawnVehicleMenu() { delete _instance; }