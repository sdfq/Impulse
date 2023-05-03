#pragma once
#include "menu/submenu.h"

class VehicleMenu : public Submenu {
public:
	static VehicleMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	VehicleMenu() : Submenu() {}
	~VehicleMenu();
};

namespace VehicleMenuVars {

	struct Vars {
		bool vehiclegodmode = false;
		bool seatbelt = false;
		bool keepEngineOn;
		bool autoRepair;
		bool vehicleinvisibility = false;
		bool rainbow = false;
		bool smokecycle = false;
		bool autoflip = false;
		bool burnshell = false;
		bool fibnumberplate = false;
		bool onscreenspeedo = false;
		bool numberplatespeedo = false;
		bool nocollision = false;
		bool phasethroughvehicles = false;
		bool vehiclenuke = false;
		bool jumparoundmode;
		int opacity = 0;
		Color colors[4] = { {255, 0, 0, 255},{0, 255, 0, 255},{0, 0, 255, 255},{255, 255, 255, 255} };
	};

	void VehicleGodmode(Vehicle vehicle, bool toggle);
}