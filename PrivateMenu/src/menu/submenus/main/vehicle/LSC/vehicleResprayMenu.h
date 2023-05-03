#pragma once
#include "menu/submenu.h"

class VehicleResprayMenu : public Submenu {
public:
	static VehicleResprayMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	VehicleResprayMenu() : Submenu() {}
	~VehicleResprayMenu();
};

namespace VehicleResprayMenuVars {
	void SetVehiclePrimaryColor(Color color);
	void SetVehicleSecondaryColor(Color color);
	struct Vars {
		float fade;
		Color primary;
		Color secondary;

		int primaryclassic;
		int primarymatte;
		int primarymetals;
		int primarycustom;
		int secondaryclassic;
		int secondarymatte;
		int secondarymetals;
		int secondarycustom;
		int pearlclassic;
		int pearlmatte;
		int pearlmetals;
		int wheelclassic;
		int wheelmatte;
		int wheelmetals;
	};
}