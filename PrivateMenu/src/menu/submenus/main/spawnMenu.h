#pragma once
#include "menu/submenu.h"

class SpawnMenu : public Submenu {
public:
	static SpawnMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	SpawnMenu() : Submenu() {}
	~SpawnMenu();
};

namespace SpawnMenuVars
{
	struct Var {
		bool IsObjectAPed = false;
		bool CreatorMode = false;
		bool DrawMarker = false;
		bool Blip = false;
		float CreatorModeDistance = 1000;
		const char* SelectedCreatorObject = " ";
	};
	extern Var vars;
}