#include "stdafx.h"
#include "landmarksTeleportMenu.h"
#include "../teleportMenu.h"

using namespace LandmarksTeleportMenuVars;

namespace LandmarksTeleportMenuVars {
	vector<pair<String, Vector3>> LandMarks = {
		{ "Airport",{ -1135.1100f, -2885.2030f, 15.00f } },
	{ "Prison",{ 1679.0490f, 2513.7110f, 45.5649f } },
	{ "Prison Gym",{ 1640.7910f, 2530.0440f, 45.5649f } },
	{ "Prison Tower",{ 1541.6290f, 2470.1400f, 62.8751f } },
	{ "Lighthouse",{ 3433.6570f, 5175.4090f, 35.8053f } },
	{ "Cannibal Camp",{ -1138.67f, 4921.97f, 220.07f } },
	{ "Mount Josiah",{ -1186.1070f, 3849.7530f, 489.0641f } },
	{ "Maze Bank Helipad",{ -73.92588f, -818.455078f, 326.174377f } },
	{ "Fort Zancudo",{ -2012.8470f, 2956.5270f, 32.8101f } },
	{ "Calafia Bridge",{ -175.2189f, 4244.1940f, 44.0730f } },
	{ "Pier",{ -1709.98f, -1085.03f, 13.10f } },
	{ "Mount Chiliad",{ 496.75f, 5591.17f, 795.03f } },
	{ "Mount Chiliad (Jump)",{ 430.2037f, 5614.7340f, 766.1684f } },
	{ "Elysian Island Base",{ 574.3914f, -3121.3220f, 18.7687f } },
	{ "Ontop of Vinewood Logo",{ 776.8780f, 1175.6080f, 345.9564f } },
	{ "Trevor's Air Field",{ 1741.4960f, 3269.2570f, 41.6014f } },
	{ "Mount Gordo",{ 2948.4480f, 5323.8120f, 101.1872f } },
	};
}

void LandmarksTeleportMenu::Init() {
	setParentSubmenu<TeleportMenu>();
	setName("Landmarks teleports", true, true);

	for (auto& tele : LandMarks) {
		addOption(ButtonOption(tele.first)
			.addFunction([tele] {TeleportMenuVars::TeleportToCoords(tele.second); })
			.addHotkey().addTranslation()
			.addTooltip(tele.first));
	}
}

/*Update once when submenu is opened*/
void LandmarksTeleportMenu::UpdateOnce() {}

/*Update while submenu is active*/
void LandmarksTeleportMenu::Update() {}

/*Background update*/
void LandmarksTeleportMenu::FeatureUpdate() {}

/*Singleton*/
LandmarksTeleportMenu* _instance;
LandmarksTeleportMenu* LandmarksTeleportMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new LandmarksTeleportMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
LandmarksTeleportMenu::~LandmarksTeleportMenu() { delete _instance; }