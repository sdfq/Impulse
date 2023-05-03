#pragma once
#include "menu/submenu.h"

class LandmarksTeleportMenu : public Submenu {
public:
	static LandmarksTeleportMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	LandmarksTeleportMenu() : Submenu() {}
	~LandmarksTeleportMenu();
};

namespace LandmarksTeleportMenuVars
{
	
}