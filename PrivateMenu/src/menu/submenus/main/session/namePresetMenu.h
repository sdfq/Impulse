#pragma once
#include "menu/submenu.h"

class NamePresetMenu : public Submenu {
public:
	static NamePresetMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	NamePresetMenu() : Submenu() {}
	~NamePresetMenu();
};

namespace NamePresetMenuVars
{
	
}