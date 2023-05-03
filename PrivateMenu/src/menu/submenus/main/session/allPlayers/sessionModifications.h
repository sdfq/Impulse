#pragma once
#include "menu/submenu.h"

class SessionModificationsMenu : public Submenu {
public:
	static SessionModificationsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	SessionModificationsMenu() : Submenu() {}
	~SessionModificationsMenu();
};

namespace SessionModificationsMenuVars
{
	struct Vars {
		int lobbyWeather;
		bool lockTimeToDay;
		bool lockTimeToMidnight;
		bool spamDayNight;
		bool slowTrans;
		bool fastTrans;
		bool fastDay2Night;
	};
}