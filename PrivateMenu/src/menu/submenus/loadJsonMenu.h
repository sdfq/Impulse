#pragma once
#include "menu/submenu.h"

class LoadJsonMenu : public Submenu {
public:
	static LoadJsonMenu* GetInstance();
	void LoadJsonMenu::Open(Submenu* parent, String path, void(*callback)(json& jsonOb));
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	LoadJsonMenu() : Submenu() {}
	~LoadJsonMenu();
};

namespace LoadJsonMenuVars
{
	
}