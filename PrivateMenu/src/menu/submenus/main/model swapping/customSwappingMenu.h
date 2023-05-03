#pragma once
#include "menu/submenu.h"

class CustomSwappingMenu : public Submenu {
public:
	static CustomSwappingMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	CustomSwappingMenu() : Submenu() {}
	~CustomSwappingMenu();
};

namespace ModelSwappingMenuVars
{
	struct Vars {
		String firstInput;
		String secondInput;
	};
}