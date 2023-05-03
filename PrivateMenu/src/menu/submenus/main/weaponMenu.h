#pragma once
#include "menu/submenu.h"

class WeaponMenu : public Submenu {
public:
	static WeaponMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	WeaponMenu() : Submenu() {}
	~WeaponMenu();
};

namespace WeaponMenuVars
{
	struct Vars {
		bool oneShotOneKill;
		bool infiniteAmmo;
		bool noReload;
		bool weaponInteriors;
		bool deadEye;
		bool shrinkRay;
		bool crazyflare;
		bool gravityGun;
		bool defibrillator;
		
		bool deleteGun;
		bool driveitgun;
		bool ropeGun;
		bool airstrikeGun;
		bool rapidFire;
		
		bool forceGun;
		
		int gravityGunTarget;
		int gravityGunNewTarget;
		int justCause2Entities[2];
		int justCause2Rope;
		
		bool modelChange;
		bool aimedexplosive = false;
		float gravityGunDistance;
		bool pickupgun;
		float pickuprange = 100.0f;
		float distancefromgun = 10.0f;
	};
	extern Vars vars;
}