#pragma once
#include "menu/submenu.h"

class VehiclePlatesMenu : public Submenu {
public:
	static VehiclePlatesMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	VehiclePlatesMenu() : Submenu() {}
	~VehiclePlatesMenu();
};

namespace VehiclePlatesMenuVars {
	struct Vars {
		int licenseplate;
	};
}