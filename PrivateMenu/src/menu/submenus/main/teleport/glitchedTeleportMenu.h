#pragma once
#include "menu/submenu.h"

class GlitchedTeleportMenu : public Submenu {
public:
	static GlitchedTeleportMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	GlitchedTeleportMenu() : Submenu() {}
	~GlitchedTeleportMenu();
};

namespace GlitchedTeleportMenuVars
{
	
}