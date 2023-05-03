#pragma once
#pragma once
#include "menu/submenu.h"

class BlacklistActionsMenu : public Submenu {
public:
	static BlacklistActionsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	BlacklistActionsMenu() : Submenu() {}
	~BlacklistActionsMenu();
};

namespace BlacklistActionsVars
{
	struct Var {
		bool toggleKick = false;
		bool toggleWarn = false;
		bool toggleRID = false;
		bool toggleFreeze = false;
		bool toggleBlame = false;
		bool toggleExplode = false;
		int iconIndex = 0;
	};
}