#pragma once
#include "menu/submenu.h"

class WeaponAmmoModifierMenu : public Submenu {
public:
	static WeaponAmmoModifierMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	WeaponAmmoModifierMenu() : Submenu() {}
	~WeaponAmmoModifierMenu();
};

namespace WeaponAmmoModifierMenuVars
{

	struct ParticleGunStruct {
		String m_pOne;
		String m_pTwo;
		float m_size;
	};

	struct Vars {

		bool impactAmmo;
		int impactAmmoVal;
		bool missilegun;
		bool missileGunRunning;
		int valkyrieTimeout;
		int missileCam;
		int missileEntity;
		bool explosiveWhale;
		bool paintvehgun;
		bool particleAmmo;
		int particleAmmoVal;
		bool explosiveBullets;
		bool fireBullets;
		bool modifyAmmo;
		int modifyAmmoVal;

		bool notimelimit;
	};
}