#pragma once
#include "menu/submenu.h"

class SessionTeleportMenu : public Submenu {
public:
	static SessionTeleportMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	SessionTeleportMenu() : Submenu() {}
	~SessionTeleportMenu();
};

namespace SessionTeleportMenuVars
{
	struct Vars {

	};
}