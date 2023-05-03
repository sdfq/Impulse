#pragma once
#include "menu/submenu.h"

class JsonVehicleMenu : public Submenu {
public:
	static JsonVehicleMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	JsonVehicleMenu() : Submenu() {}
	~JsonVehicleMenu();
};

namespace JsonVehicleMenuVars
{
	
}