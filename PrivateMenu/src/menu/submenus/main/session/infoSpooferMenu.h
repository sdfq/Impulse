#pragma once
#include "menu/submenu.h"

class InfoSpooferMenu : public Submenu {
public:
	static InfoSpooferMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	InfoSpooferMenu() : Submenu() {}
	~InfoSpooferMenu();
};

namespace InfoSpooferMenuVars
{

	struct intInfoSpoof {
		int value; // unused
		bool changed; // unused
		bool spam;
	};

	struct floatInfoSpoof {
		float value; // unused
		bool changed; // unused
		bool spam;
	};

	struct Vars {
		string profileName = "";
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
	extern Vars vars;
}