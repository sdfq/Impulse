#pragma once
#include "menu/submenu.h"

class InsideTeleportMenu : public Submenu {
public:
	static InsideTeleportMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	InsideTeleportMenu() : Submenu() {}
	~InsideTeleportMenu();
};

namespace InsideTeleportMenuVars
{
	
}