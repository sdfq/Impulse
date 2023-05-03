#pragma once
#include "menu/submenu.h"

class ownedTriggerbotMenu : public Submenu {
public:
	static ownedTriggerbotMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	ownedTriggerbotMenu() : Submenu() {}
	~ownedTriggerbotMenu();
};

namespace ownedTriggerbotVars
{

	struct Vars {
		bool triggerbotToggle = false;
		SPlayer targetPlayer;
	};

}