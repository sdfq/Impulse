#pragma once
#include "menu/submenu.h"

class LoadingMenu : public Submenu {
public:
	static LoadingMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	LoadingMenu() : Submenu() {}
	~LoadingMenu();
};

namespace LoadingMenuVars
{
	
}