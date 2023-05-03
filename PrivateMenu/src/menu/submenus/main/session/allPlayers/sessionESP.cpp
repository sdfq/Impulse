#include "stdafx.h"
#include "sessionESP.h"
#include "../allPlayersMenu.h"
#include "../playerList/player/ESPMenu.h"

using namespace SessionESPMenuVars;

namespace SessionESPMenuVars {
	Vars vars;


}

void SessionESPMenu::Init() {
	setParentSubmenu<AllPlayersMenu>();
	setName("Extra sensory perception", true, true);

	addOption(ColorOption("ESP Color")
		.addColor(ESPMenuVars::vars.ESPColor)
		.canBeSaved()
		.addTooltip("This will change all esp lines and boxes to match your chosen color").addTranslation());

	addOption(ToggleOption("Name")
		.addToggle(vars.name)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Name ESP"));

	addOption(ToggleOption("Box")
		.addToggle(vars.box)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Line ESP"));

	addOption(ToggleOption("Line")
		.addToggle(vars.line)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Line ESP"));

	addOption(ToggleOption("ESP line of sight green line")
		.addRequirement([] { return vars.line; })
		.addToggle(ESPMenuVars::vars.ESPLOSGREEN).canBeSaved()
		.addTooltip("This will highlight the ESP line when a player in line of sight of your ped"));

	addOption(ColorOption("ESP line of sight line color")
		.addRequirement([] { return vars.line; })
		.addColor(ESPMenuVars::vars.ESPLOSColor)
		.canBeSaved()
		.addTooltip("This will change the highlight color for the option above").addTranslation());

	addOption(ToggleOption("Head marker")
		.addToggle(vars.head)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Head ESP"));

	addOption(ToggleOption("Foot marker")
		.addToggle(vars.foot)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Foot ESP"));

	addOption(ToggleOption("Info")
		.addToggle(vars.info)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Info ESP"));

	addOption(ToggleOption("Skel")
		.addToggle(vars.showbones)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Skel ESP"));

	addOption(ToggleOption("Sky line")
		.addToggle(vars.skyline)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Sky ESP"));
}

/*Update once when submenu is opened*/
void SessionESPMenu::UpdateOnce() {}

/*Update while submenu is active*/
void SessionESPMenu::Update() {}

/*Background update*/
void SessionESPMenu::FeatureUpdate() {
	if (vars.name) {
		OnlinePlayerCallback(true, [](SPlayer player) { if(player.m_id != GetLocalPlayer().m_id && !player.m_infoESP && !vars.info) ESPMenuVars::NameESP(player); });
	}

	if (vars.line) {
		OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_id != GetLocalPlayer().m_id) ESPMenuVars::LineESP(player); });
	}

	if (vars.head) {
		OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_id != GetLocalPlayer().m_id) ESPMenuVars::HeadMarkerESP(player); });
	}

	if (vars.foot) {
		OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_id != GetLocalPlayer().m_id) ESPMenuVars::FootMarkerESP(player); });
	}

	if (vars.info) {
		OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_id != GetLocalPlayer().m_id) ESPMenuVars::InfoESP(player); });
	}

	if (vars.showbones) {
		OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_id != GetLocalPlayer().m_id) ESPMenuVars::BonesShow(player, true); });
	}

	if (vars.skyline) {
		OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_id != GetLocalPlayer().m_id) ESPMenuVars::SkyLine(player); });
	}

	if (vars.box) {
		OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_id != GetLocalPlayer().m_id) ESPMenuVars::ESPBox(player); });
	}
}

/*Singleton*/
SessionESPMenu* _instance;
SessionESPMenu* SessionESPMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new SessionESPMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
SessionESPMenu::~SessionESPMenu() { delete _instance; }