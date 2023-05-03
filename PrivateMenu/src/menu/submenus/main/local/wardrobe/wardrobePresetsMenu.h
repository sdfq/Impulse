#pragma once
#include "menu/submenu.h"

class WardrobePresetsMenu : public Submenu {
public:
	static WardrobePresetsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	WardrobePresetsMenu() : Submenu() {}
	~WardrobePresetsMenu();
};

namespace WardrobePresetsMenuVars
{
	
}