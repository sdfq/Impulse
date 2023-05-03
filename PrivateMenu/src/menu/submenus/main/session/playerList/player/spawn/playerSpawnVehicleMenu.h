#pragma once
#include "menu/submenu.h"

class PlayerSpawnerTypeMenu;

class PlayerSpawnVehicleMenu : public Submenu {
public:
	static PlayerSpawnVehicleMenu* GetInstance();
	static PlayerSpawnerTypeMenu* spawnerTypeMenus[];
	void Init() override;
	void addSpawner(int num, String name, String* vehicles, int size);
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	PlayerSpawnVehicleMenu() : Submenu() {}
	~PlayerSpawnVehicleMenu();
};

namespace PlayerSpawnVehicleMenuVars
{
	PlayerSpawnerTypeMenu* GetVehicleSub();

	struct Vars {
		bool spawnInvincible = false;
	};
	extern Vars vars;
}