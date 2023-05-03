#pragma once
#include "menu/submenu.h"

class RockstarDevActionsMenu : public Submenu {
public:
	static RockstarDevActionsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	RockstarDevActionsMenu() : Submenu() {}
	~RockstarDevActionsMenu();
};

namespace RockstarDevActionsVars
{
	struct Var {
		bool exit;
		bool bail = true;
		bool warn = true;
	};
}