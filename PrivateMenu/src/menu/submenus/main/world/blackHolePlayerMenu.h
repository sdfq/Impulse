#pragma once
#include "menu/submenu.h"

class BlackHolePlayerMenu : public Submenu {
public:
	static BlackHolePlayerMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	BlackHolePlayerMenu() : Submenu() {}
	~BlackHolePlayerMenu();
};

namespace BlackHolePlayerMenuVars
{
	struct Vars
	{
		bool FollowPlayer;
		int AttachedTo;
	};
}