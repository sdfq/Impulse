#pragma once
#include "menu/submenu.h"

class SpawnVehicleSettingsMenu : public Submenu {
public:
	static SpawnVehicleSettingsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	SpawnVehicleSettingsMenu() : Submenu() {}
	~SpawnVehicleSettingsMenu();
};

namespace SpawnVehicleSettingsMenuVars
{
	struct Vars
	{
		bool blip;
		bool spawnin;
		bool spawninvincible;
		bool spawnmaxed;
		bool deleteold;
		bool spawninair;
		int spawnspeed;
		float spawnheight = 60.0f;
		Color dprimary;
		Color dsecondary;
		bool spawndefault;
		bool particles;
		bool fade;
		bool information;
	};
	extern Vars vars;
}