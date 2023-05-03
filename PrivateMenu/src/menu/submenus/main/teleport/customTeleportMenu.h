#pragma once
#include "menu/submenu.h"

class CustomTeleportMenu : public Submenu {
public:
	static CustomTeleportMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	CustomTeleportMenu() : Submenu() {}
	~CustomTeleportMenu();
};

namespace CustomMenuVars
{
	
}