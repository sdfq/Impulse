#pragma once
#include "menu/submenu.h"

class VFXVehicleMenu : public Submenu {
public:
	static VFXVehicleMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	VFXVehicleMenu() : Submenu() {}
	~VFXVehicleMenu();
};

namespace VFXVehicleMenuVars {
	void SaveToJson(json& jsonOb);
	void LoadVehicle(json& jsonOb);
}