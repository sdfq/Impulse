#pragma once
#include "menu/submenu.h"

class BodyguardSelectedMenu : public Submenu {
public:
	static BodyguardSelectedMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	BodyguardSelectedMenu() : Submenu() {}
	~BodyguardSelectedMenu();
};

namespace BodyguardSelectedMenuVars
{
	struct Vars
	{
		int SelectedBodyguard;
	};
	extern Vars vars;
}