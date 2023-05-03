#pragma once
#include "menu/submenu.h"

class VFXSkyMenu : public Submenu {
public:
	static VFXSkyMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	VFXSkyMenu() : Submenu() {}
	~VFXSkyMenu();
};

namespace VFXSkyMenuVars {
	void SaveToJson(json& jsonOb);
	void LoadSky(json& jsonOb);
}