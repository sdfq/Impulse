#pragma once
#include "menu/submenu.h"

class VFXMenu : public Submenu {
public:
	static VFXMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	VFXMenu() : Submenu() {}
	~VFXMenu();
};

namespace VFXMenuVars
{
	
}