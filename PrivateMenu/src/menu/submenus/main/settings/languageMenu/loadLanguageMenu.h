#pragma once
#include "menu/submenu.h"

class LoadLanguageMenu : public Submenu {
public:
	static LoadLanguageMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	LoadLanguageMenu() : Submenu() {}
	~LoadLanguageMenu();
};

namespace LoadLanguageMenuVars {
	struct Vars {
		bool loadOnStart = false;
	};
}