#pragma once
#include "menu/submenu.h"

class SessionSpawnerTypeMenu;

class SessionSpawnVehicleMenu : public Submenu {
public:
	static SessionSpawnVehicleMenu* GetInstance();
	static SessionSpawnerTypeMenu* spawnerTypeMenus[];
	void addSpawner(int num, String name, String* vehicles, int size);
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	SessionSpawnVehicleMenu() : Submenu() {}
	~SessionSpawnVehicleMenu();
};

namespace SessionSpawnVehicleMenuVars
{
	SessionSpawnerTypeMenu* GetVehicleSub();

	struct Vars {

	};
}