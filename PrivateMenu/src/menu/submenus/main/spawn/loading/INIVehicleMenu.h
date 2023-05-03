#pragma once
#include "menu/submenu.h"

class INIVehicleMenu : public Submenu {
public:
	static INIVehicleMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	INIVehicleMenu() : Submenu() {}
	~INIVehicleMenu();
};

namespace INIVehicleMenuVars
{
	
}