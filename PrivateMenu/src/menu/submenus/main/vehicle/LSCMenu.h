#pragma once
#include "menu/submenu.h"

class LSCMenu : public Submenu {
public:
	static LSCMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	LSCMenu() : Submenu() {}
	~LSCMenu();
};

namespace LSCMenuVars
{
	void MaxVehicle(Vehicle veh);
	void RandomizeVehicle(Vehicle veh);

	struct Vars {
		int windowtint = 0;
		int hornIndex = 0;

		bool spamFullyTune;
		bool spamRandomTune;
	};

	void DowngradeVehicle(Vehicle veh);
}