#pragma once
#include "menu/submenu.h"

class SpawnObjectSettingsMenu : public Submenu {
public:
	static SpawnObjectSettingsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	SpawnObjectSettingsMenu() : Submenu() {}
	~SpawnObjectSettingsMenu();
};

namespace SpawnObjectSettingsMenuVars
{
	struct Vars {
		bool blip;
		bool particles;
		bool fade;
		bool information;
	};

	extern Vars vars;
}