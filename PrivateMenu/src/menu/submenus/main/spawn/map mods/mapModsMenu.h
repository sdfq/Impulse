#pragma once
#include "menu/submenu.h"

class MapModsMenu : public Submenu {
public:
	static MapModsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	MapModsMenu() : Submenu() {}
	~MapModsMenu();
};

namespace MapModsMenuVars
{
	struct Vars
	{

	};
	extern Vars vars;
}