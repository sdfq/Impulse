#pragma once
#include "menu/submenu.h"

class SoundMenu : public Submenu {
public:
	static SoundMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	SoundMenu() : Submenu() {}
	~SoundMenu();
};

namespace SoundMenuVars
{
	struct Vars {
		int soundCounter;
	};
}