#pragma once
#include "menu/submenu.h"

class BlacklistMenu : public Submenu {
public:
	static BlacklistMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	BlacklistMenu() : Submenu() {}
	~BlacklistMenu();
};

namespace BlacklistVars
{

}