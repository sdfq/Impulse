#pragma once
#include "menu/submenu.h"

class LoadWardrobeMenu : public Submenu {
public:
	static LoadWardrobeMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	LoadWardrobeMenu() : Submenu() {}
	~LoadWardrobeMenu();
};

namespace LoadWardrobeMenuVars
{
	
}