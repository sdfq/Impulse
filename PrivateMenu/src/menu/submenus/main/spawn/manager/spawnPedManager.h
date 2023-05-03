#pragma once
#include "menu/submenu.h"

class SpawnPedManagerMenu : public Submenu {
public:
	static SpawnPedManagerMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	SpawnPedManagerMenu() : Submenu() {}
	~SpawnPedManagerMenu();
};

namespace SpawnPedManagerMenuVars
{
	struct Vars {
		Vector3 coords;
		Vector3 rot;
		float precision = 10.0f;
	};
}