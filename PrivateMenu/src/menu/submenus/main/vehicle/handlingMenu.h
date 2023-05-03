#pragma once
#include "menu/submenu.h"

class HandlingMenu : public Submenu {
public:
	static HandlingMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	HandlingMenu() : Submenu() {}
	~HandlingMenu();
};

namespace HandlingMenuVars {
	struct Vars {
		bool inBike, inBoat, inPlane;
		int gears;
		int drivenwheels;
		bool suspension;
		float suspensionVal;
		bool wheelWidth;
		bool wheelHeight;
		float wheelWidthVal;
		int wheelHeightVal;
	};

}