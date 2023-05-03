#include "stdafx.h"
#include "miscReportStats.h"
#include "../miscMenu.h"

using namespace MiscReportStatsMenuVars;

namespace MiscReportStatsMenuVars {
	Vars vars;
}

void MiscReportStatsMenu::Init() {
	setParentSubmenu<MiscMenu>();
	setName("Report stats", true, true);


}

/*Update once when submenu is opened*/
void MiscReportStatsMenu::UpdateOnce() {
	clearOptionsOffset(0);

	STATS::StatGetInt(Utils::GetHashKey("MPPLY_GRIEFING"), &vars.Griefing, 0);
	STATS::StatGetInt(Utils::GetHashKey("MPPLY_EXPLOITS"), &vars.Exploits, 0);
	STATS::StatGetInt(Utils::GetHashKey("MPPLY_VC_ANNOYINGME"), &vars.VCAnnoying, 0);
	STATS::StatGetInt(Utils::GetHashKey("MPPLY_VC_HATE"), &vars.VCHate, 0);
	STATS::StatGetInt(Utils::GetHashKey("MPPLY_OFFENSIVE_LANGUAGE"), &vars.OffensiveLang, 0);
	STATS::StatGetInt(Utils::GetHashKey("MPPLY_OFFENSIVE_TAGPLATE"), &vars.OffensiveTagPlate, 0);
	STATS::StatGetInt(Utils::GetHashKey("MPPLY_GAME_EXPLOITS"), &vars.GameExploit, 0);
	STATS::StatGetInt(Utils::GetHashKey("MPPLY_HELPFUL"), &vars.IsHelpful, 0);
	STATS::StatGetInt(Utils::GetHashKey("MPPLY_FRIENDLY"), &vars.IsFriendly, 0);
	STATS::StatGetInt(Utils::GetHashKey("MPPLY_COMMEND_STRENGTH"), &vars.CommendStrength, 0);
	STATS::StatGetInt(Utils::GetHashKey("MPPLY_REPORT_STRENGTH"), &vars.ReportStrength, 0);
	STATS::StatGetInt(Utils::GetHashKey("MPPLY_IS_HIGH_EARNER"), &vars.IsHighEarner, 0);
	STATS::StatGetInt(Utils::GetHashKey("MPPLY_OFFENSIVE_UGC"), &vars.OffensiveInGameChat, 0);

	addOption(ButtonOption(va("Report strength: %i", vars.ReportStrength))
		.addTooltip("Show this stat"));

	addOption(ButtonOption(va("Commend strength: %i", vars.CommendStrength))
		.addTooltip("Show this stat"));

	addOption(ButtonOption(va("Friendly commends: %i", vars.IsFriendly))
		.addTooltip("Show this stat"));

	addOption(ButtonOption(va("Helpful commends: %i", vars.IsHelpful))
		.addTooltip("Show this stat"));

	addOption(ButtonOption(va("Griefing reports: %i", vars.Griefing))
		.addTooltip("Show this stat"));

	addOption(ButtonOption(va("Exploit reports: %i", vars.Exploits))
		.addTooltip("Show this stat"));

	addOption(ButtonOption(va("Game exploit reports: %i", vars.GameExploit))
		.addTooltip("Show this stat"));

	addOption(ButtonOption(va("VC hate reports: %i", vars.VCHate))
		.addTooltip("Show this stat"));

	addOption(ButtonOption(va("VC annoying me reports: %i", vars.VCAnnoying))
		.addTooltip("Show this stat"));

	addOption(ButtonOption(va("Offensive UGC: %i", vars.OffensiveInGameChat))
		.addTooltip("Show this stat"));

	addOption(ButtonOption(va("Offensive language reports: %i", vars.OffensiveLang))
		.addTooltip("Show this stat"));

	addOption(ButtonOption(va("Offensive plate reports: %i", vars.OffensiveTagPlate))
		.addTooltip("Show this stat"));

	addOption(ButtonOption(va("Punished: %i", vars.IsPunished))
		.addTooltip("Show this stat"));

	addOption(ButtonOption(va("High earner: %i", vars.IsHighEarner))
		.addTooltip("Show this stat"));
}

/*Update while submenu is active*/
void MiscReportStatsMenu::Update() {}

/*Background update*/
void MiscReportStatsMenu::FeatureUpdate() {
	
}

/*Singleton*/
MiscReportStatsMenu* _instance;
MiscReportStatsMenu* MiscReportStatsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new MiscReportStatsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
MiscReportStatsMenu::~MiscReportStatsMenu() { delete _instance; }