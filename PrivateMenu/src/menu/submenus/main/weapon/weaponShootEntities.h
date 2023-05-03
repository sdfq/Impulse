#pragma once
#include "menu/submenu.h"

class WeaponShootEntitiesMenu : public Submenu {
public:
	static WeaponShootEntitiesMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	WeaponShootEntitiesMenu() : Submenu() {}
	~WeaponShootEntitiesMenu();
};

namespace WeaponShootEntitiesMenuVars
{
	struct Vars {
		int shootEntityType;
		int vehicleVal;
		int objectVal;
		int pedVal;
		float shootdistance = 3.0f;
		bool flyinshootvehicles;
		bool shootEntities;
	};

	extern ScrollStruct<Hash> vehiclePairs[23];
	extern ScrollStruct<Hash> pedPairs[64];
	extern ScrollStruct<Hash> objectPairs[26];
}