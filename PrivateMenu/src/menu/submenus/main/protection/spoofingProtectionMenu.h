#pragma once
#include "menu/submenu.h"

class SpoofingMenu : public Submenu {
public:
	static SpoofingMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	SpoofingMenu() : Submenu() {}
	~SpoofingMenu();
};

namespace SpoofingMenuVars
{
	struct Vars {
		bool spoofpedlocation;
		string customname;
		string RIDprofileName = "";
		int customid;
		int checkid;
	};
	extern Vars vars;
}