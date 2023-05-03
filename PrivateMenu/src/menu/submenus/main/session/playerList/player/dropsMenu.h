#pragma once
#include "menu/submenu.h"

class DropsMenu : public Submenu {
public:
	static DropsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	DropsMenu() : Submenu() {}
	~DropsMenu();
};

namespace DropsMenuVars
{
	struct Vars {
		int standarddropdelay = 750;
	};
}