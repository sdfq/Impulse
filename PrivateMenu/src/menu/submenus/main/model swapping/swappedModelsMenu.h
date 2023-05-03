#pragma once
#include "menu/submenu.h"

class SwappedModelsMenu : public Submenu {
public:
	static SwappedModelsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	SwappedModelsMenu() : Submenu() {}
	~SwappedModelsMenu();
};

namespace SwappedMenuVars
{
	
}