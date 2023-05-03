#include "stdafx.h"
#include "onlineTeleportsMenu.h"
#include "../teleportMenu.h"

using namespace OnlineTeleportsMenuVars;

namespace OnlineTeleportsMenuVars {
	vector<pair<String, Vector3>> Online = {
	{ "Casino", { 925.78f, 85.68f, 78.86f } },
	{ "Mors Mutual Insurance", { -222.1977f, -1185.8500f, 23.0294f } },
	{ "Mask Shop", { -1338.16f, -1278.11f, 4.87f } },
	{ "Tattoo Shop", { -1155.7309f, -1422.5162f, 4.7751f } },
	{ "Ammunation", { 247.3652f, -45.8777f, 69.9411f } },
	{ "Clothes Store", { -718.91f, -158.16f, 37.00f } },
	{ "LS Customs", { -373.01f, -124.91f, 38.31f } },
	{ "Benny's vehicles", { -210.6698f, -1301.3829f, 31.2959f } },
	{ "Ammunation Gun Range", { 22.153f, -1072.854f, 29.797f } },
	{ "Ammunation Office", { 12.494f, -1110.130f , 29.797f } },
	{ "LS Airport Customs",{ -1134.224f, -1984.387f, 13.166f } },
	{ "La Mesa Customs",{ 709.797f, -1082.649f, 22.398f } },
	{ "Senora Desert Customs",{ 1178.653f, 2666.179f, 37.881f } },
	{ "Beek Customs",{ 126.219f, 6608.142f, 31.866f } },
	{ "Eclipse Towers",{ -807.247f, 301.868f, 86.073f } },
	{ "Eclipse Towers Roof",{ -779.026f, 331.695f, 238.828f } },
	{ "Impound Lot",{ 401.057f, -1631.766f, 29.293f } },
	{ "Eclipse Towers Inside ", { -778.34f, 339.97f, 208.62f } },
	{ "Online Hidden Race Area", { 403.78f, -961.35f, -99.00f } },
	{ "Airport Tower", { -985.1005f, -2642.046f, 63.5170f } },
	{ "Maze Bank CEO Office Entrance", { -52.70f, -777.51f, 44.19f } },
	{ "Helipad", { -749.50f, -1476.89f, 5.0f } },
	{ "King Of The Hill", { -1192.53f, -1781.78f, 19.13f } },
	};

}

void OnlineTeleportsMenu::Init() {
	setParentSubmenu<TeleportMenu>();
	setName("Online location teleports", true, true);

	for (auto& tele : Online) {
		addOption(ButtonOption(tele.first)
			.addFunction([tele] {TeleportMenuVars::TeleportToCoords(tele.second); })
			.addHotkey().addTranslation()
			.addTooltip(tele.first));
	}
}

/*Update once when submenu is opened*/
void OnlineTeleportsMenu::UpdateOnce() {}

/*Update while submenu is active*/
void OnlineTeleportsMenu::Update() {}

/*Background update*/
void OnlineTeleportsMenu::FeatureUpdate() {}

/*Singleton*/
OnlineTeleportsMenu* _instance;
OnlineTeleportsMenu* OnlineTeleportsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new OnlineTeleportsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
OnlineTeleportsMenu::~OnlineTeleportsMenu() { delete _instance; }