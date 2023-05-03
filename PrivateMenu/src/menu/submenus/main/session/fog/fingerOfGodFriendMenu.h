#pragma once
#include "menu/submenu.h"

class FingerOfGodFriendMenu : public Submenu {
public:
	static FingerOfGodFriendMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	FingerOfGodFriendMenu() : Submenu() {}
	~FingerOfGodFriendMenu();
};

namespace FingerOfGodFriendMenuVars
{
	struct Vars {

	};
}