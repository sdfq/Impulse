#pragma once
#include "menu/submenu.h"

class SessionPeacefulMenu : public Submenu {
public:
	static SessionPeacefulMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	SessionPeacefulMenu() : Submenu() {}
	~SessionPeacefulMenu();
};

namespace SessionPeacefulMenuVars
{
	struct Vars {
		bool nearbyMoneyDrop;
		bool selfMoneyDrop;
		bool nearbyMoneyDropnoncir;
		int droptime = 1000;
		int spoofranknum;
		bool spoofrank;
		bool locationmoneydrop;
		Vector3 dropposition;
		Vector3 dropposition2;
		Vector3 dropposition3;
		int drops;
		bool drawDropMarker;
		int presetdroploc;
		int howmanylocsforcus;
		bool presetloccheck = true;
		int locationmoneydelay = 1000;
		int nearbydropdelay = 1000;
	};
	extern Vars vars;
	extern ScrollStruct<int> presetlocations[7];
}