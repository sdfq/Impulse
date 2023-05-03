#pragma once
#include "menu/submenu.h"

class DisableActionsLobby : public Submenu {
public:
	static DisableActionsLobby* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	DisableActionsLobby() : Submenu() {}
	~DisableActionsLobby();
};

namespace DisableActionsLobbyVars
{
	struct Vars {
		bool DisableVehicles;
		bool DisableInteriors;
		bool DisableWeapons;
	};
}