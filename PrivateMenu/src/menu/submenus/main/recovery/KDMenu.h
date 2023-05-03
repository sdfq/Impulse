#pragma once
#include "menu/submenu.h"

class KDMenu : public Submenu {
public:
	static KDMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	KDMenu() : Submenu() {}
	~KDMenu();
};

namespace KDMenuVars
{
	struct Vars
	{
		int kills;
		int deaths;
		int okills;
		int odeaths;
		int shots;
		int headshots;
		int hits;
	};
}