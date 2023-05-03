#pragma once
#include "menu/submenu.h"

class SpawnerTypeMenu;

class SpawnVehicleMenu : public Submenu {
public:
	static SpawnVehicleMenu* GetInstance();
	static SpawnerTypeMenu* spawnerTypeMenus[];
	void addSpawner(int num, String name, String* vehicles, int size);
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	SpawnVehicleMenu() : Submenu() {}
	~SpawnVehicleMenu();
};

namespace SpawnVehicleMenuVars{
	struct Vars{
		map<Hash, String> m_map;
	};
	extern Vars vars;
	Vehicle SpawnVehicle(Hash model, bool spawnIn, bool spawnInvincible, bool spawnMaxed, bool deleteOld, bool spawnInAir, Color primary, Color secondary, bool blip, int spawnspeed);
	Vehicle SpawnVehicle(String toSpawn, bool spawnIn, bool spawnInvincible, bool spawnMaxed, bool deleteOld, bool spawnInAir, Color primary, Color secondary, bool blip, int spawnSpeed);
	Vehicle SpawnVehicle(Hash model);
	Vehicle SpawnVehicle(String toSpawn);
	Vehicle SpawnVehiclePlayer(Hash model, int id, bool godmode = false);
	SpawnerTypeMenu* GetVehicleSub();
}
