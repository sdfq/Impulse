#include "stdafx.h"
#include "dlcVehiclesMenu.h"
#include "menu\submenus\main\spawn\spawnVehicleMenu.h"
#include "menu\submenus\main\spawn\vehicle\spawnerTypeMenu.h"
#include "spawnVehicleSettingsMenu.h"

using namespace DLCVehicleMenuVars;
SpawnerTypeMenu* DLCVehicleMenu::spawnerTypeMenus[32];
namespace DLCVehicleMenuVars {
    Vars vars;
    int spawn = 0;
    int vehicleSub;

    SpawnerTypeMenu* GetVehicleSub() {
        return DLCVehicleMenu::spawnerTypeMenus[vehicleSub];
    }
}

void DLCVehicleMenu::addSpawner(int num, String name, String* vehicles, int size) {
    spawnerTypeMenus[num] = new SpawnerTypeMenu(name, vehicles, size);
    spawnerTypeMenus[num]->setParentSubmenu< DLCVehicleMenu>();
    GetSubmenuHandler()->addSubmenu(spawnerTypeMenus[num]);
    vehicleSub = num;
    addOption(SubmenuOption(name).addTranslation()
        .addSubmenu(spawnerTypeMenus[num])
        .addTooltip(name).addHotkey());
}

void DLCVehicleMenu::Init() {
    setParentSubmenu<SpawnVehicleMenu>();
    setName("DLC vehicles only", true, true);

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

}

/*Update once when submenu is opened*/
void DLCVehicleMenu::UpdateOnce() {}

/*Update while submenu is active*/
void DLCVehicleMenu::Update() {}

/*Background update*/
void DLCVehicleMenu::FeatureUpdate() {}

/*Singleton*/
DLCVehicleMenu* _instance;
DLCVehicleMenu* DLCVehicleMenu::GetInstance() {
    if (_instance == nullptr) {
        _instance = new DLCVehicleMenu();
        _instance->Init();
        GetSubmenuHandler()->addSubmenu(_instance);
    }
    return _instance;
}
DLCVehicleMenu::~DLCVehicleMenu() {
    for (int i = 0; i < spawn; i++) delete spawnerTypeMenus[i];
    delete _instance;
}