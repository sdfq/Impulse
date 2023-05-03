#pragma once
#include "menu/submenu.h"

class OnlineTeleportsMenu : public Submenu {
public:
	static OnlineTeleportsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	OnlineTeleportsMenu() : Submenu() {}
	~OnlineTeleportsMenu();
};

namespace OnlineTeleportsMenuVars
{
	
}