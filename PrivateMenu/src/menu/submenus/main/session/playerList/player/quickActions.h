#pragma once
#include "menu/submenu.h"

class QuickActionsMenu : public Submenu {
public:
	static QuickActionsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	QuickActionsMenu() : Submenu() {}
	~QuickActionsMenu();
};

namespace QuickActionsVars
{
	struct Vars {
		bool DisableWeapons;
	};
}