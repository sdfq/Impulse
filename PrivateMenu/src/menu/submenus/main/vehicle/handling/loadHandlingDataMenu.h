#pragma once
#include "menu/submenu.h"

class LoadHandlingDataMenu : public Submenu {
public:
	static LoadHandlingDataMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	LoadHandlingDataMenu() : Submenu() {}
	~LoadHandlingDataMenu();
};

namespace LoadHandlingDataMenuVars
{
	
}