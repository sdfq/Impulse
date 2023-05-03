#pragma once
#include "menu/submenu.h"

class StatsMenu : public Submenu {
public:
	static StatsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	StatsMenu() : Submenu() {}
	~StatsMenu();
};

namespace StatsMenuVars {
	struct Vars {
		int stamina;
		int strength;
		int lungcapacity;
		int driving;
		int flying;
		int shooting;
		int stealth;
		int days;
		int hours;
		int minutes;
		int seconds;

		//
		int racewins;
		int raceloses;
		int tdwins;
		int tdloses;
		int dmwins;
		int dmloses;

	};
}