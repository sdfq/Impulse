#pragma once
#include "menu/submenu.h"

class SpawnPedSettingsMenu : public Submenu {
public:
	static SpawnPedSettingsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	SpawnPedSettingsMenu() : Submenu() {}
	~SpawnPedSettingsMenu();
};

namespace SpawnPedSettingsMenuVars
{
	struct Vars {
		bool blip;
		bool godmode;
		bool particles;
		bool fade;
		bool information;
	};

	extern Vars vars;
}