#pragma once
#include "menu/submenu.h"

class SessionTalkingMenu : public Submenu {
public:
	static SessionTalkingMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	SessionTalkingMenu() : Submenu() {}
	~SessionTalkingMenu();
};

namespace SessionTalkingMenuVars
{
	struct Vars {
		bool showList;
		bool explode;
		bool addWantedLevel;
	};
}