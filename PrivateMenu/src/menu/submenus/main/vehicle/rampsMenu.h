#pragma once
#include "menu/submenu.h"

class RampsMenu : public Submenu {
public:
	static RampsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	RampsMenu() : Submenu() {}
	~RampsMenu();
};

namespace RampsMenuVars
{
	struct Vars
	{
		int type;
		bool front;
		bool rear;
		bool left;
		bool right;
	};
}