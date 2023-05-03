#pragma once
#include "menu/submenu.h"

class BlockAllMenu : public Submenu {
public:
	static BlockAllMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	BlockAllMenu() : Submenu() {}
	~BlockAllMenu();
};

namespace BlockAllMenuVars
{
	struct Vars {
		
	};
	extern Vars vars;
}