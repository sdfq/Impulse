#pragma once
#include "menu/submenu.h"

class BikeHandlingMenu : public Submenu {
public:
	static BikeHandlingMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	BikeHandlingMenu() : Submenu() {}
	~BikeHandlingMenu();
};

namespace BikeHandlingMenuVars
{
	
}