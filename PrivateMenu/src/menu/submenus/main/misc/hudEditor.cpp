#include "stdafx.h"
#include "hudEditor.h"
#include "../miscMenu.h"

using namespace HudEditorMenuVars;

namespace HudEditorMenuVars {
	Vars vars;

	char* HudIndexNames[171] = {
		"HUD_COLOUR_PURE_WHITE",
		"HUD_COLOUR_WHITE",
		"HUD_COLOUR_BLACK",
		"HUD_COLOUR_GREY",
		"HUD_COLOUR_GREYLIGHT",
		"HUD_COLOUR_GREYDARK",
		"HUD_COLOUR_RED",
		"HUD_COLOUR_REDLIGHT",
		"HUD_COLOUR_REDDARK",
		"HUD_COLOUR_BLUE",
		"HUD_COLOUR_BLUELIGHT",
		"HUD_COLOUR_BLUEDARK",
		"HUD_COLOUR_YELLOW",
		"HUD_COLOUR_YELLOWLIGHT",
		"HUD_COLOUR_YELLOWDARK",
		"HUD_COLOUR_ORANGE",
		"HUD_COLOUR_ORANGELIGHT",
		"HUD_COLOUR_ORANGEDARK",
		"HUD_COLOUR_GREEN",
		"HUD_COLOUR_GREENLIGHT",
		"HUD_COLOUR_GREENDARK",
		"HUD_COLOUR_PURPLE",
		"HUD_COLOUR_PURPLELIGHT",
		"HUD_COLOUR_PURPLEDARK",
		"HUD_COLOUR_PINK",
		"HUD_COLOUR_RADAR_HEALTH",
		"HUD_COLOUR_RADAR_ARMOUR",
		"HUD_COLOUR_RADAR_DAMAGE",
		"HUD_COLOUR_NET_PLAYER1",
		"HUD_COLOUR_NET_PLAYER2",
		"HUD_COLOUR_NET_PLAYER3",
		"HUD_COLOUR_NET_PLAYER4",
		"HUD_COLOUR_NET_PLAYER5",
		"HUD_COLOUR_NET_PLAYER6",
		"HUD_COLOUR_NET_PLAYER7",
		"HUD_COLOUR_NET_PLAYER8",
		"HUD_COLOUR_NET_PLAYER9",
		"HUD_COLOUR_NET_PLAYER10",
		"HUD_COLOUR_NET_PLAYER11",
		"HUD_COLOUR_NET_PLAYER12",
		"HUD_COLOUR_NET_PLAYER13",
		"HUD_COLOUR_NET_PLAYER14",
		"HUD_COLOUR_NET_PLAYER15",
		"HUD_COLOUR_NET_PLAYER16",
		"HUD_COLOUR_NET_PLAYER17",
		"HUD_COLOUR_NET_PLAYER18",
		"HUD_COLOUR_NET_PLAYER19",
		"HUD_COLOUR_NET_PLAYER20",
		"HUD_COLOUR_NET_PLAYER21",
		"HUD_COLOUR_NET_PLAYER22",
		"HUD_COLOUR_NET_PLAYER23",
		"HUD_COLOUR_NET_PLAYER24",
		"HUD_COLOUR_NET_PLAYER25",
		"HUD_COLOUR_NET_PLAYER26",
		"HUD_COLOUR_NET_PLAYER27",
		"HUD_COLOUR_NET_PLAYER28",
		"HUD_COLOUR_NET_PLAYER29",
		"HUD_COLOUR_NET_PLAYER30",
		"HUD_COLOUR_NET_PLAYER31",
		"HUD_COLOUR_NET_PLAYER32",
		"HUD_COLOUR_SIMPLEBLIP_DEFAULT",
		"HUD_COLOUR_MENU_BLUE",
		"HUD_COLOUR_MENU_GREY_LIGHT",
		"HUD_COLOUR_MENU_BLUE_EXTRA_DARK",
		"HUD_COLOUR_MENU_YELLOW",
		"HUD_COLOUR_MENU_YELLOW_DARK",
		"HUD_COLOUR_MENU_GREEN",
		"HUD_COLOUR_MENU_GREY",
		"HUD_COLOUR_MENU_GREY_DARK",
		"HUD_COLOUR_MENU_HIGHLIGHT",
		"HUD_COLOUR_MENU_STANDARD",
		"HUD_COLOUR_MENU_DIMMED",
		"HUD_COLOUR_MENU_EXTRA_DIMMED",
		"HUD_COLOUR_BRIEF_TITLE",
		"HUD_COLOUR_MID_GREY_MP",
		"HUD_COLOUR_NET_PLAYER1_DARK",
		"HUD_COLOUR_NET_PLAYER2_DARK",
		"HUD_COLOUR_NET_PLAYER3_DARK",
		"HUD_COLOUR_NET_PLAYER4_DARK",
		"HUD_COLOUR_NET_PLAYER5_DARK",
		"HUD_COLOUR_NET_PLAYER6_DARK",
		"HUD_COLOUR_NET_PLAYER7_DARK",
		"HUD_COLOUR_NET_PLAYER8_DARK",
		"HUD_COLOUR_NET_PLAYER9_DARK",
		"HUD_COLOUR_NET_PLAYER10_DARK",
		"HUD_COLOUR_NET_PLAYER11_DARK",
		"HUD_COLOUR_NET_PLAYER12_DARK",
		"HUD_COLOUR_NET_PLAYER13_DARK",
		"HUD_COLOUR_NET_PLAYER14_DARK",
		"HUD_COLOUR_NET_PLAYER15_DARK",
		"HUD_COLOUR_NET_PLAYER16_DARK",
		"HUD_COLOUR_NET_PLAYER17_DARK",
		"HUD_COLOUR_NET_PLAYER18_DARK",
		"HUD_COLOUR_NET_PLAYER19_DARK",
		"HUD_COLOUR_NET_PLAYER20_DARK",
		"HUD_COLOUR_NET_PLAYER21_DARK",
		"HUD_COLOUR_NET_PLAYER22_DARK",
		"HUD_COLOUR_NET_PLAYER23_DARK",
		"HUD_COLOUR_NET_PLAYER24_DARK",
		"HUD_COLOUR_NET_PLAYER25_DARK",
		"HUD_COLOUR_NET_PLAYER26_DARK",
		"HUD_COLOUR_NET_PLAYER27_DARK",
		"HUD_COLOUR_NET_PLAYER28_DARK",
		"HUD_COLOUR_NET_PLAYER29_DARK",
		"HUD_COLOUR_NET_PLAYER30_DARK",
		"HUD_COLOUR_NET_PLAYER31_DARK",
		"HUD_COLOUR_NET_PLAYER32_DARK",
		"HUD_COLOUR_BRONZE",
		"HUD_COLOUR_SILVER",
		"HUD_COLOUR_GOLD",
		"HUD_COLOUR_PLATINUM",
		"HUD_COLOUR_GANG1",
		"HUD_COLOUR_GANG2",
		"HUD_COLOUR_GANG3",
		"HUD_COLOUR_GANG4",
		"HUD_COLOUR_SAME_CREW",
		"HUD_COLOUR_FREEMODE",
		"HUD_COLOUR_PAUSE_BG",
		"HUD_COLOUR_FRIENDLY",
		"HUD_COLOUR_ENEMY",
		"HUD_COLOUR_LOCATION",
		"HUD_COLOUR_PICKUP",
		"HUD_COLOUR_PAUSE_SINGLEPLAYER",
		"HUD_COLOUR_FREEMODE_DARK",
		"HUD_COLOUR_INACTIVE_MISSION",
		"HUD_COLOUR_DAMAGE",
		"HUD_COLOUR_PINKLIGHT",
		"HUD_COLOUR_PM_MITEM_HIGHLIGHT",
		"HUD_COLOUR_SCRIPT_VARIABLE",
		"HUD_COLOUR_YOGA",
		"HUD_COLOUR_TENNIS",
		"HUD_COLOUR_GOLF",
		"HUD_COLOUR_SHOOTING_RANGE",
		"HUD_COLOUR_FLIGHT_SCHOOL",
		"HUD_COLOUR_NORTH_BLUE",
		"HUD_COLOUR_SOCIAL_CLUB",
		"HUD_COLOUR_PLATFORM_BLUE",
		"HUD_COLOUR_PLATFORM_GREEN",
		"HUD_COLOUR_PLATFORM_GREY",
		"HUD_COLOUR_FACEBOOK_BLUE",
		"HUD_COLOUR_INGAME_BG",
		"HUD_COLOUR_DARTS",
		"HUD_COLOUR_WAYPOINT",
		"HUD_COLOUR_MICHAEL",
		"HUD_COLOUR_FRANKLIN",
		"HUD_COLOUR_TREVOR",
		"HUD_COLOUR_GOLF_P1",
		"HUD_COLOUR_GOLF_P2",
		"HUD_COLOUR_GOLF_P3",
		"HUD_COLOUR_GOLF_P4",
		"HUD_COLOUR_WAYPOINTLIGHT",
		"HUD_COLOUR_WAYPOINTDARK",
		"HUD_COLOUR_PANEL_LIGHT",
		"HUD_COLOUR_MICHAEL_DARK",
		"HUD_COLOUR_FRANKLIN_DARK",
		"HUD_COLOUR_TREVOR_DARK",
		"HUD_COLOUR_OBJECTIVE_ROUTE",
		"HUD_COLOUR_PAUSEMAP_TINT",
		"HUD_COLOUR_PAUSE_DESELECT",
		"HUD_COLOUR_PM_WEAPONS_PURCHASABLE",
		"HUD_COLOUR_PM_WEAPONS_LOCKED",
		"HUD_COLOUR_END_SCREEN_BG",
		"HUD_COLOUR_CHOP",
		"HUD_COLOUR_PAUSEMAP_TINT_HALF",
		"HUD_COLOUR_NORTH_BLUE_OFFICIAL",
		"HUD_COLOUR_SCRIPT_VARIABLE_2",
		"HUD_COLOUR_H",
		"HUD_COLOUR_HDARK",
		"HUD_COLOUR_T",
		"HUD_COLOUR_TDARK",
		"HUD_COLOUR_HSHARD"
	};
}

void HudEditor::Init() {
	setParentSubmenu<MiscMenu>();
	setName("Hud Editor", true, true);

	for (int i = 0; i < 171; i++) {
		HUD::GetHudColour(i, &vars.m_hudColor[i].R, &vars.m_hudColor[i].G, &vars.m_hudColor[i].B, &vars.m_hudColor[i].A);

		addOption(ColorOption(HudIndexNames[i])
			.addColor(vars.m_hudColor[i]).canBeSaved()
			.addFunction([=] {
				HUD::_SetHudColour(i, vars.m_hudColor[i].R, vars.m_hudColor[i].G, vars.m_hudColor[i].B, vars.m_hudColor[i].A);
			})
			.addTooltip("Change the color of your HUD elements"));
	}
}

/*Update once when submenu is opened*/
void HudEditor::UpdateOnce() {}

/*Update while submenu is active*/
void HudEditor::Update() {}

/*Background update*/
void HudEditor::FeatureUpdate() {}

/*Singleton*/
HudEditor* _instance;
HudEditor* HudEditor::GetInstance() {
	if (_instance == nullptr) {
		_instance = new HudEditor();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
HudEditor::~HudEditor() { delete _instance; }