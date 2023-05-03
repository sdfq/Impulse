#pragma once
#include "menu/submenu.h"

class BlackholeMenu : public Submenu {
public:
	static BlackholeMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	BlackholeMenu() : Submenu() {}
	~BlackholeMenu();
};

namespace BlackholeMenuVars {

	enum BlackholePerformance {
		BLACKHOLE_PRECISION_WEAK,
		BLACKHOLE_PRECISION_MEDIUM,
		BLACKHOLE_PRECISION_HIGH
	};

	struct Vars {

		bool active;
		bool drawMarker;

		Vector3 position;

		float strength = 2.0f;

		// attraction shit
		bool attractVehicles, attractPedestrians, attractObjects, attractPlayerVehicles;

		// performance
		int performanceIndex = 1;
		int poolIndex = 0;
		int originalEntityProcessQueueSize;
		std::vector<Entity> entityProcessQueue;
		int currentProcessSize = 0;

		// miscellaneous
		bool explosions;
		bool whitehole;
		bool typeSwitch;
		int typeSwitchDelay;

	};
	extern Vars vars;
}