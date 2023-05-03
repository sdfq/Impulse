#pragma once
#include "menu/submenu.h"

class AnimationMenu : public Submenu {
public:
	static AnimationMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	AnimationMenu() : Submenu() {}
	~AnimationMenu();
};

namespace AnimationMenuVars
{
	struct Vars {
		bool controllable;
		bool contort;
		bool run;
		bool runWalkstyle;
		
		String anim;
		String dict;
		String walkstyleAnim;

		int animation;
		bool animationToggle;
		int walkstyle;
		bool walkstyleToggle;
		int flag;
		int scenario;
		bool scenarioToggle;
	};

}