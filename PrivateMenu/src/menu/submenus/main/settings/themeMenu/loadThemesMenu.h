#pragma once
#include "menu/submenu.h"

class LoadThemesMenu : public Submenu {
public:
	static LoadThemesMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	LoadThemesMenu() : Submenu() {}
	~LoadThemesMenu();
};

namespace LoadThemesMenuVars {
	void LoadConfig();

	struct Vars {
		bool loadOnStart = false;
	};
}