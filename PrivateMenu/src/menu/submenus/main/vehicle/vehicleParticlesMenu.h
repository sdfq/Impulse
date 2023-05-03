#pragma once
#include "menu/submenu.h"

class VehicleParticlesMenu : public Submenu {
public:
	static VehicleParticlesMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	VehicleParticlesMenu() : Submenu() {}
	~VehicleParticlesMenu();
};

namespace VehicleParticlesMenuVars
{
	struct Vars
	{
		int type;
		float size = 0.15f;
		bool frontleft;
		bool frontright;
		bool rearleft;
		bool rearright;
		bool exhaust;
		bool enabled;
	};
}