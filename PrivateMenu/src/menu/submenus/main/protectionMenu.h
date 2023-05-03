#pragma once
#include "menu/submenu.h"

class ProtectionMenu : public Submenu {
public:
	static ProtectionMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	ProtectionMenu() : Submenu() {}
	~ProtectionMenu();
};

namespace ProtectionMenuVars
{
	struct Vars
	{
		int aim;
		bool aimToggle;
		int selectedAim;
		bool clone;
		bool safesplace;
		bool vehicleNetworkMitigate;
		bool entityAttachment;
		bool spoofIp;
		bool spoofIpt;
		bool spoofIptt;
		DWORD originalIp;
		bool blame;
		bool allScriptEvents;
		bool allScriptEvents2;
		bool blockalleventscheck;
		bool redirectObjects;
		bool protectObjects;
		bool notifyObjects;
		bool gameclock;
		bool blockallnetevents;
	};
	extern Vars vars;
}