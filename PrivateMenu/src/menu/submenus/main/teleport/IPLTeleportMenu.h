#pragma once
#include "menu/submenu.h"

class IPLTeleportMenu : public Submenu {
public:
	static IPLTeleportMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	IPLTeleportMenu() : Submenu() {}
	~IPLTeleportMenu();
};

namespace IPLTeleportMenuVars
{
	
}