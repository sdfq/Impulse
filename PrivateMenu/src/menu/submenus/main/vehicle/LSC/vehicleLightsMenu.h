#pragma once
#include "menu/submenu.h"

class VehicleLightsMenu : public Submenu {
public:
	static VehicleLightsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	VehicleLightsMenu() : Submenu() {}
	~VehicleLightsMenu();
};

namespace VehicleLightsMenuVars
{
	
	struct Vars {
		bool xenonlights;
		int xenonlightcolor;
		Color neon;
		bool neonleft;
		bool neonright;
		bool neonfront;
		bool neonback;
		bool rainbowxenon;
		bool rainbowneons;
	};
}