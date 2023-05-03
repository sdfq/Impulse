#pragma once
#include "menu/submenu.h"

class FlyingHandlingMenu : public Submenu {
public:
	static FlyingHandlingMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	FlyingHandlingMenu() : Submenu() {}
	~FlyingHandlingMenu();
};

namespace FlyingHandlingMenuVars
{
	
}