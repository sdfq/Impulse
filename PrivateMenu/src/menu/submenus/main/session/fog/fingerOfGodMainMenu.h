#pragma once
#include "menu/submenu.h"

class FingerOfGodMainMenu : public Submenu {
public:
	static FingerOfGodMainMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	FingerOfGodMainMenu() : Submenu() {}
	~FingerOfGodMainMenu();
};

namespace FingerOfGodMainMenuVars
{
	struct Vars {

	};
}