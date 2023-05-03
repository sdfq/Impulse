#pragma once
#include "menu/submenu.h"

class VehicleWheelsMenu : public Submenu {
public:
	static VehicleWheelsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	VehicleWheelsMenu() : Submenu() {}
	~VehicleWheelsMenu();
};

namespace VehicleWheelsMenuVars
{
	struct Vars {
		bool tiresmoke;
		Color tiresmokecol;
		int wheeltype;
		bool bulletproofwheels;
	};
}