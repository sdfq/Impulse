#pragma once
#include "menu/submenu.h"

class VFXDistantLightsMenu : public Submenu {
public:
	static VFXDistantLightsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	VFXDistantLightsMenu() : Submenu() {}
	~VFXDistantLightsMenu();
};

namespace VFXDistantLightsMenuVars {
	void SaveToJson(json& jsonOb);
	void LoadDistantLights(json& jsonOb);

	struct Vars {
		Color vehicle1;
		Color vehicle2;
	};
}