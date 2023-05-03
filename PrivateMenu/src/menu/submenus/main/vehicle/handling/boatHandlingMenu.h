#pragma once
#include "menu/submenu.h"

class BoatHandlingMenu : public Submenu {
public:
	static BoatHandlingMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	BoatHandlingMenu() : Submenu() {}
	~BoatHandlingMenu();
};

namespace BoatHandlingMenuVars
{
	
}