#pragma once
#include "menu/submenu.h"

class DisableActionsMenu : public Submenu {
public:
	static DisableActionsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	DisableActionsMenu() : Submenu() {}
	~DisableActionsMenu();
};

namespace DisableActionsVars
{
	struct Vars {
		bool DisableVehicle = false;
		bool DisableInteriors = false;
		bool DisableWeapons = false;
	};
}