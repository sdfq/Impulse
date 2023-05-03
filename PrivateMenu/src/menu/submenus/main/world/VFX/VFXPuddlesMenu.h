#pragma once
#include "menu/submenu.h"

class VFXPuddlesMenu : public Submenu {
public:
	static VFXPuddlesMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	VFXPuddlesMenu() : Submenu() {}
	~VFXPuddlesMenu();
};

namespace VFXPuddlesMenuVars {
	void SaveToJson(json& jsonOb);
	void LoadRainPuddles(json& jsonOb);
}