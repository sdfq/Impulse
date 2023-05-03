#pragma once
#include "menu/submenu.h"

class SpawnObjectManagerMenu : public Submenu {
public:
	static SpawnObjectManagerMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	SpawnObjectManagerMenu() : Submenu() {}
	~SpawnObjectManagerMenu();
};

namespace SpawnObjectManagerMenuVars
{
	struct Vars {
		Vector3 coords;
		Vector3 rot;
		float precision = 10.0f;
	};
}