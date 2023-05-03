#pragma once
#include "menu/submenu.h"

class VehicleWeaponsMenu : public Submenu {
public:
	static VehicleWeaponsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	VehicleWeaponsMenu() : Submenu() {}
	~VehicleWeaponsMenu();
};

namespace VehicleWeaponsMenuVars
{
	struct Vars
	{
		int bullettype;
		int bulletspeed = 5000;
		int key = 0x45;
		bool controllerKey;
		bool guided;
		bool enabled;
		bool responsibility;
	};
}