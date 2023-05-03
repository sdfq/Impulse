#pragma once
#include "menu/submenu.h"

class SessionESPMenu : public Submenu {
public:
	static SessionESPMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	SessionESPMenu() : Submenu() {}
	~SessionESPMenu();
};

namespace SessionESPMenuVars
{
	struct Vars {
		bool name;
		bool box;
		bool line;
		bool head;
		bool foot;
		bool info;
		bool showbones;
		bool skyline;
		bool invisibility = false;
		bool lineLOSHIGHLIGHT;
	};
}