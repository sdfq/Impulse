#pragma once
#include "menu/submenu.h"

class AllPlayersMenu : public Submenu {
public:
	static AllPlayersMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	AllPlayersMenu() : Submenu() {}
	~AllPlayersMenu();
};

namespace AllPlayersMenuVars
{
	struct Vars {
		bool chat;
	};

	extern Vars vars;
}