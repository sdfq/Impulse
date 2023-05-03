#pragma once
#include "menu/submenu.h"

class MiscProtectionMenu : public Submenu {
public:
	static MiscProtectionMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	MiscProtectionMenu() : Submenu() {}
	~MiscProtectionMenu();
};

namespace MiscProtectionMenuVars
{
	struct Vars {
		int aim;
		bool aimToggle;
		int selectedAim;
		bool clone;
		bool safesplace;
		bool vehicleNetworkMitigate;
		bool blame;
		bool blockinvites;
	};
	extern Vars vars;
}