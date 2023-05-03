#pragma once
#include "menu/submenu.h"

class VisionMenu : public Submenu {
public:
	static VisionMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	VisionMenu() : Submenu() {}
	~VisionMenu();
};

namespace VisionMenuVars
{
	
}