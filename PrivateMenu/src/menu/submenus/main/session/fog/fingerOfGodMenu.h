#pragma once
#include "menu/submenu.h"

class FingerOfGodMenu : public Submenu {
public:
	static FingerOfGodMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	FingerOfGodMenu() : Submenu() {}
	~FingerOfGodMenu();
};

namespace FingerOfGodMenuVars
{
	struct Vars {
		long long currentID;

		int iconIndex = 0;
	};

	extern Vars vars;
}