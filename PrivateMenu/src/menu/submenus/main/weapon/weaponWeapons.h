#pragma once
#include "menu/submenu.h"

class WeaponWeaponsMenu : public Submenu {
public:
	static WeaponWeaponsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	WeaponWeaponsMenu() : Submenu() {}
	~WeaponWeaponsMenu();
};

namespace WeaponWeaponsMenuVars
{
	struct Vars {
		int camo;
		int camoAll;
		int selectedWeapon = 0;
		int weaponall;
		bool rainbowCamo;
		bool giveallweaponsloop;
	};
	extern Vars vars;
	extern Hash usableWeaponHashes[87];
	extern void giveallweaponeverysesh();
}