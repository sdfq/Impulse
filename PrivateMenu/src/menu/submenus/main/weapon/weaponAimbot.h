#pragma once
#include "menu/submenu.h"

class WeaponAimbotMenu : public Submenu {
public:
	static WeaponAimbotMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	WeaponAimbotMenu() : Submenu() {}
	~WeaponAimbotMenu();
};

namespace WeaponAimbotMenuVars
{
	struct Vars {
		int entityFilter;
		int prioritize;
		int bone;

		bool autoShoot;
		bool required;
		bool basicplayeraimbot;
		bool basicaimbot;
		bool basictriggerbot;
	};
}