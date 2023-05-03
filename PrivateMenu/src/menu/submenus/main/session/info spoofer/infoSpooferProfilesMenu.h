#pragma once
#include "menu/submenu.h"

class InfoSpooferProfilesMenu : public Submenu {
public:
	static InfoSpooferProfilesMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	InfoSpooferProfilesMenu() : Submenu() {}
	~InfoSpooferProfilesMenu();
};

namespace InfoSpooferProfilesMenuVars
{

	struct intInfoSpoof {
		int value;
		bool changed;
		bool spam;
	};

	struct floatInfoSpoof {
		float value;
		bool changed;
		bool spam;
	};

	struct Vars {
		intInfoSpoof rank = { 0, 0, 0 };
		intInfoSpoof wallet = { 0, 0, 0 };
		intInfoSpoof kills = { 0, 0, 0 };
		intInfoSpoof deaths = { 0, 0, 0 };
		floatInfoSpoof kdratio = { 0, 0, 0 };

		bool spoofrankt;
		bool spoofcasht;
		bool spoofkillst;
		bool spoofdeathst;
		bool spoofkdt;
		int spoofranknum;
		int spoofcashnum;
		int spoofkillsnum;
		int spoofdeathsnum;
		float spoofkdnum;
	};
}