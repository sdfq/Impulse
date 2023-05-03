#pragma once
#include "menu/submenu.h"

class SpawnVehicleManagerMenu : public Submenu {
public:
	static SpawnVehicleManagerMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	SpawnVehicleManagerMenu() : Submenu() {}
	~SpawnVehicleManagerMenu();
};

namespace SpawnVehicleManagerMenuVars
{
	struct Vars {
		Vector3 coords;
		Vector3 rot;
		float precision = 10.0f;
	};
}