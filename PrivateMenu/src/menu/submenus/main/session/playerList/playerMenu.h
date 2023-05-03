#pragma once
#include "menu/submenu.h"

class PlayerMenu : public Submenu {
public:
	static PlayerMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	PlayerMenu() : Submenu() {}
	~PlayerMenu();
};

namespace PlayerMenuVars {
	void CloseSpectate();

	extern int player;
	struct Vars
	{
		bool spectating;
		bool specatezoomtog;
		int spectatezoom = 5.0f;
	};
}