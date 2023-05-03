#pragma once
#include "menu/submenu.h"

class TunablesMenu : public Submenu {
public:
	static TunablesMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	TunablesMenu() : Submenu() {}
	~TunablesMenu();
};

namespace TunablesMenuVars
{
	
}