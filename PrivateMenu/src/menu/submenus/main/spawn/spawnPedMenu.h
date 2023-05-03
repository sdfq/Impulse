#pragma once
#include "menu/submenu.h"

class SpawnPedMenu : public Submenu {
public:
	static SpawnPedMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	SpawnPedMenu() : Submenu() {}
	~SpawnPedMenu();
};

namespace SpawnPedMenuVars
{
	void SpawnPedPlayer(Hash model, int id);
}