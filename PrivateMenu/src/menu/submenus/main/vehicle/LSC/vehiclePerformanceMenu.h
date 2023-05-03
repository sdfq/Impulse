#pragma once
#include "menu/submenu.h"

class VehiclePerformanceMenu : public Submenu {
public:
	static VehiclePerformanceMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	VehiclePerformanceMenu() : Submenu() {}
	~VehiclePerformanceMenu();
};

namespace VehiclePerformanceMenuVars
{
	struct Vars
	{
		bool turbo = false;
		int engineIndex = 0;
		int breaksIndex = 0;
		int transmissionIndex = 0;
		int suspensionIndex = 0;
		int armorIndex = 0;
	};
}