#pragma once
#include "menu/submenu.h"

class WaypointMenu : public Submenu {
public:
	static WaypointMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	WaypointMenu() : Submenu() {}
	~WaypointMenu();
};

namespace WaypointMenuVars {
	struct Vars {
		bool drivingtowaypoint;
		bool explode;
		bool moneydrop;
	};

}