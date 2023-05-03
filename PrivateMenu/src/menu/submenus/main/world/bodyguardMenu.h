#pragma once
#include "menu/submenu.h"

class BodyguardMenu : public Submenu {
public:
	static BodyguardMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	BodyguardMenu() : Submenu() {}
	~BodyguardMenu();
};

namespace BodyguardMenuVars
{
	struct Vars {
		Ped Bodyguard;
		int weaponchoice;
		int healthchoice;
		int formationchoice;
		int pedchoice;
		bool godmodepick;
		bool ragdollpick;
		bool clonepick;
		bool addblip;
		Blip blip;
		bool Invisible;
	};
	extern Vars vars;
}