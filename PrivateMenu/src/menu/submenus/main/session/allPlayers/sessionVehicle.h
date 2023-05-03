#pragma once
#include "menu/submenu.h"

class SessionVehicleMenu : public Submenu {
public:
	static SessionVehicleMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	SessionVehicleMenu() : Submenu() {}
	~SessionVehicleMenu();
};

namespace SessionVehicleMenuVars
{
	struct Vars {
		bool hornBoost;
		bool kickLoop;
		bool freeze;
	};
}