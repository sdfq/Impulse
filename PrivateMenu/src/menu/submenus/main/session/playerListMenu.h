#pragma once
#include "menu/submenu.h"

class PlayerListMenu : public Submenu {
public:
	static PlayerListMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	PlayerListMenu() : Submenu() {}
	~PlayerListMenu();
};

namespace PlayerListMenuVars {
	struct Vars {
		int sorttype = 0;
	};
}