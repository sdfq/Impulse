#pragma once
#include "menu/submenu.h"

class MiscReportStatsMenu : public Submenu {
public:
	static MiscReportStatsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	MiscReportStatsMenu() : Submenu() {}
	~MiscReportStatsMenu();
};

namespace MiscReportStatsMenuVars
{
	struct Vars {
		int Griefing, VCAnnoying, VCHate, OffensiveLang, OffensiveTagPlate, GameExploit, Exploits, IsHelpful, IsFriendly, CommendStrength, ReportStrength, IsHighEarner, OffensiveInGameChat, WasIBadsport, IsPunished, AmICurrentlyBadsport;
	};
}