#pragma once
#include "menu/submenu.h"

class SpawnObjectMenu : public Submenu {
public:
	static SpawnObjectMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	SpawnObjectMenu() : Submenu() {}
	~SpawnObjectMenu();
};

namespace SpawnObjectMenuVars
{
	void SpawnObjectPlayer(DWORD model, int playerID);
}