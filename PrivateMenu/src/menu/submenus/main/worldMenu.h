#pragma once
#include "menu/submenu.h"

class WorldMenu : public Submenu {
public:
	static WorldMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	WorldMenu() : Submenu() {}
	~WorldMenu();
};

namespace WorldMenuVars {

	struct Vars {

		bool freezeTime;
		bool syncWithSystemTime;
		
		bool clearwater;
		bool blackout;
		bool noocean;
		float wind = 0.0f;
		int gravity;
		int waveintensity;
		float snow = 0;
		float slipperiness = 0;
		float clearradius = 2.0f;
		bool enablePedDensity;
		bool enableTrafficDensity;
		bool enableradiusbubble;
		float pedDensity = 1.0f;
		float trafficDensity = 1.0f;
		float timeScale = 1.0f;
		bool noflybys;
		bool teleportallnearvehs;
		bool turretExcludeMe = true;
		int turretWeaponSelection;
		int turretTargetSelection;
		bool splitwater;

		sWaterTune Tune;

		void RequestControlOfEnt(Entity entity);

	};

	extern Vars vars;
}