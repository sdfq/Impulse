#pragma once
#include "menu/submenu.h"

class VehicleAcrobaticsMenu : public Submenu {
public:
	static VehicleAcrobaticsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	VehicleAcrobaticsMenu() : Submenu() {}
	~VehicleAcrobaticsMenu();
};

namespace VehicleAcrobaticsMenuVars
{
	
}