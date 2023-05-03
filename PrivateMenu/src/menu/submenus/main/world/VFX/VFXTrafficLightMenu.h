#pragma once
#include "menu/submenu.h"

class VFXTrafficLightMenu : public Submenu {
public:
	static VFXTrafficLightMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	VFXTrafficLightMenu() : Submenu() {}
	~VFXTrafficLightMenu();
};

namespace VFXTrafficLightMenuVars {
	void SaveToJson(json& jsonOb);
	void LoadTrafficLights(json& jsonOb);

	struct Vars {
		Color red;
		Color orange;
		Color green;
		Color walk;
		Color dontwalk;
	};
}