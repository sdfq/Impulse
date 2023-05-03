#pragma once
#include "menu/submenu.h"

class WeaponVisualsMenu : public Submenu {
public:
	static WeaponVisualsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	WeaponVisualsMenu() : Submenu() {}
	~WeaponVisualsMenu();
};

namespace WeaponVisualsMenuVars
{
	struct Vars {
		float width;
		float height;
		float overall;
		bool aimedInformation;
		bool aimingLaser;
		bool cartoonEffects;
		bool infernoFlare;
		bool invisibility;

		int selectedCrosshair;
		bool crosshair;
	};
}