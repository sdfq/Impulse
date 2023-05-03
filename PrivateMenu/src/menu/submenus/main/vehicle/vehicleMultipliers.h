#pragma once
#include "menu/submenu.h"

class VehicleMultipliersMenu : public Submenu {
public:
	static VehicleMultipliersMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	VehicleMultipliersMenu() : Submenu() {}
	~VehicleMultipliersMenu();
};

namespace VehicleMultipliersMenuVars
{
	struct Vars {
		int rpm;
		int light;
		int torque;

		bool acceleration;
		float accelerationVal;

		bool brake;
		float brakeVal;

		bool suspension;
		float suspensionVal;
	};
}