#pragma once
#include "menu/submenu.h"

class MainMenu : public Submenu
{
public:
	static MainMenu* GetInstance();

	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	MainMenu() : Submenu() { }
	~MainMenu();
};

namespace MainMenuVars
{
	
}