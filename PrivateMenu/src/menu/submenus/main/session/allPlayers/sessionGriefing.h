#pragma once
#include "menu/submenu.h"

class SessionGriefingMenu : public Submenu {
public:
	static SessionGriefingMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	SessionGriefingMenu() : Submenu() {}
	~SessionGriefingMenu();
};

namespace SessionGriefingMenuVars
{
	struct Vars {
		int attackerCount = 1;
		bool disableTasks;
		bool smokePlayer;
		bool alwaysWanted;
		bool explode;
		bool karma;
		bool waterLoop;
		bool fireLoop;
		bool fire;
		bool hostileTraffic;
		bool hostilePeds;
		bool rainRockets;
		bool shakeCamera;
		bool fakeMoney;
		bool forceField;
		bool eclipseTower;
		bool electrocutep;
	};
	extern Vars vars;
}