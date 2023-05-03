#pragma once
#include "menu/submenu.h"

class RecoveryMenu : public Submenu {
public:
	static RecoveryMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	RecoveryMenu() : Submenu() {}
	~RecoveryMenu();
};

namespace RecoveryMenuVars
{
	struct Vars {
		bool rpIncreaser = false;
		bool rpIncreaserevent;
	};
}