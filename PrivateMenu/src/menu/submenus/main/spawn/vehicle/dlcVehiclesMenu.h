#pragma once
#include "menu/submenu.h"

class SpawnerTypeMenu;

class DLCVehicleMenu : public Submenu {
public:
	static DLCVehicleMenu* GetInstance();
	static SpawnerTypeMenu* spawnerTypeMenus[];
	void Init() override;
	void addSpawner(int num, String name, String* vehicles, int size);
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	DLCVehicleMenu() : Submenu() {}
	~DLCVehicleMenu();
};

namespace DLCVehicleMenuVars
{
    SpawnerTypeMenu* GetVehicleSub();

	struct Vars {

	};
}