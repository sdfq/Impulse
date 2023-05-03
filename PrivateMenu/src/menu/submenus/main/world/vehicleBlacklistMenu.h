#pragma once
#include "menu/submenu.h"

class VehicleBlacklistMenu : public Submenu {
public:
	static VehicleBlacklistMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	VehicleBlacklistMenu() : Submenu() {}
	~VehicleBlacklistMenu();
};

namespace VehicleBlacklistMenuVars
{
	struct Vars
	{
		std::vector<std::string> BlacklistedVehicles;
		bool BlacklistEnabled;
		int Actiontochoose;
	};
	extern Vars vars;
}