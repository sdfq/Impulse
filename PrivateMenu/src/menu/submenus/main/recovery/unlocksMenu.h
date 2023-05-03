#pragma once
#include "menu/submenu.h"

class UnlocksMenu : public Submenu {
public:
	static UnlocksMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	UnlocksMenu() : Submenu() {}
	~UnlocksMenu();
};

namespace UnlocksMenuVars
{
	
}