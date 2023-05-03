#pragma once
#include "menu/submenu.h"

class NetworkEventsMenu : public Submenu {
public:
	static NetworkEventsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	NetworkEventsMenu() : Submenu() {}
	~NetworkEventsMenu();
};

namespace NetworkEventsMenuVars
{
	struct Vars {
		bool toggledall = false;
	};
	extern Vars vars;
}