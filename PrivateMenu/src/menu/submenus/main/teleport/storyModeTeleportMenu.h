#pragma once
#include "menu/submenu.h"

class StoryModeTeleportMenu : public Submenu {
public:
	static StoryModeTeleportMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	StoryModeTeleportMenu() : Submenu() {}
	~StoryModeTeleportMenu();
};

namespace StoryModeTeleportMenuVars
{
	
}