#include "stdafx.h"
#include "playerSpawnVehicleMenu.h"
#include "../../playerMenu.h"
#include "playerSpawnerTypeMenu.h"

using namespace PlayerSpawnVehicleMenuVars;
PlayerSpawnerTypeMenu* PlayerSpawnVehicleMenu::spawnerTypeMenus[55];
namespace PlayerSpawnVehicleMenuVars {
	Vars vars;
	int spawn = 0;
	int vehicleSub;

	PlayerSpawnerTypeMenu* GetVehicleSub() {
		return PlayerSpawnVehicleMenu::spawnerTypeMenus[vehicleSub];
	}
}

void PlayerSpawnVehicleMenu::addSpawner(int num, String name, String* vehicles, int size) {
	spawnerTypeMenus[num] = new PlayerSpawnerTypeMenu(name, vehicles, size);
	GetSubmenuHandler()->addSubmenu(spawnerTypeMenus[num]);
	vehicleSub = num;
	addOption(SubmenuOption(name).addTranslation()
		.addSubmenu(spawnerTypeMenus[num])
		.addTooltip(name).addHotkey());
}

void PlayerSpawnVehicleMenu::Init() {
	setParentSubmenu<PlayerMenu>();
	setName("Spawn vehicle", true, false);

	addOption(ToggleOption("Spawn invincible")
		.addToggle(vars.spawnInvincible)
		.addTooltip("Turn the spawned vehicle invincible")
		.addTranslation());

	addSpawner(spawn++, "Casino", dlccasino, NUMOF(dlccasino));
	addSpawner(spawn++, "Arena War", dlcaw, NUMOF(dlcaw));
	addSpawner(spawn++, "After Hours", dlcaa, NUMOF(dlcaa));
	addSpawner(spawn++, "Super Sport Series", dlcsss, NUMOF(dlcsss));
	addSpawner(spawn++, "Doomsday Heist", dlcddh, NUMOF(dlcddh));
	addSpawner(spawn++, "Smuggler's Run", dlcsr, NUMOF(dlcsr));
	addSpawner(spawn++, "Gunrunning", dlcgr, NUMOF(dlcgr));
	addSpawner(spawn++, "Cunning Stunts", dlcsvc, NUMOF(dlcsvc));
	addSpawner(spawn++, "Import/Export", dlcie, NUMOF(dlcie));
	addSpawner(spawn++, "Bikers", dlcbu, NUMOF(dlcbu));
	addSpawner(spawn++, "Cunning Stunts", dlccs, NUMOF(dlccs));
	addSpawner(spawn++, "Finance and Felony", dlcfaf, NUMOF(dlcfaf));
	addSpawner(spawn++, "Lowriders: Custom Classics", dlclrof, NUMOF(dlclrof));
	addSpawner(spawn++, "Be My Valentine", dlcbmv, NUMOF(dlcbmv));
	addSpawner(spawn++, "January 2016", dlcj16, NUMOF(dlcj16));
	addSpawner(spawn++, "Festive Surprise 2015", dlcfs15, NUMOF(dlcfs15));
	addSpawner(spawn++, "Executives and Other Criminals", dlceaoc, NUMOF(dlceaoc));
	addSpawner(spawn++, "Halloween Surprise", dlchs, NUMOF(dlchs));
	addSpawner(spawn++, "Lowriders", dlclcc, NUMOF(dlclcc));
	addSpawner(spawn++, "Freemode Events", dlcfme, NUMOF(dlcfme));
	addSpawner(spawn++, "Ill-Gotten Gains Part 2", dlciggp2, NUMOF(dlciggp2));
	addSpawner(spawn++, "Ill-Gotten Gains Part 1", dlciggp1, NUMOF(dlciggp1));
	addSpawner(spawn++, "Heists", dlch, NUMOF(dlch));
	addSpawner(spawn++, "Festive Surprise 2014", dlcfs14, NUMOF(dlcfs14));
	addSpawner(spawn++, "Last Team Standing", dlclts, NUMOF(dlclts));
	addSpawner(spawn++, "San Andreas Flight School", dlcfs, NUMOF(dlcfs));
	addSpawner(spawn++, "Independence Day Special", dlcids, NUMOF(dlcids));
	addSpawner(spawn++, "I'm Not a Hipster", dlcnah, NUMOF(dlcnah));
	addSpawner(spawn++, "High Life", dlchl, NUMOF(dlchl));
	addSpawner(spawn++, "Business", dlcb, NUMOF(dlcb));
	addSpawner(spawn++, "Valentine's Day Massacre Special", dlcvdm, NUMOF(dlcvdm));
	addSpawner(spawn++, "Beach Bum", dlcbb, NUMOF(dlcbb));
	addOption(BreakOption("General").addTranslation());
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
void PlayerSpawnVehicleMenu::UpdateOnce() {}

/*Update while submenu is active*/
void PlayerSpawnVehicleMenu::Update() {}

/*Background update*/
void PlayerSpawnVehicleMenu::FeatureUpdate() {}

/*Singleton*/
PlayerSpawnVehicleMenu* _instance;
PlayerSpawnVehicleMenu* PlayerSpawnVehicleMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new PlayerSpawnVehicleMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
PlayerSpawnVehicleMenu::~PlayerSpawnVehicleMenu() { delete _instance; }