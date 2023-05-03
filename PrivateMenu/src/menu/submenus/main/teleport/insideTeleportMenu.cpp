#include "stdafx.h"
#include "insideTeleportMenu.h"
#include "../teleportMenu.h"

using namespace InsideTeleportMenuVars;

namespace InsideTeleportMenuVars {
	vector<pair<String, Vector3>> Inside = {
		{ "Strip Club DJ Booth",{ 126.135f, -1278.583f, 29.270f } },
		{ "Humane Labs Tunnel",{ 3525.495f, 3705.301f, 20.992f } },
		{ "Police Station",{ 436.491f, -982.172f, 30.699f } },
		{ "FIB Top Floor",{ 135.733f, -749.216f, 258.152f } },
		{ "IAA Office",{ 117.220f, -620.938f, 206.047f } },
		{ "Torture Room",{ 147.170f, -2201.804f, 4.688f } },
		{ "Ammunation Gun Range",{ 22.153f, -1072.854f, 29.797f } },
		{ "Ammunation Office",{ 12.494f, -1110.130f , 29.797f } },
		{ "Blaine County Savings Bank",{ -109.299f, 6464.035f , 31.627f } },
		{ "Fort Zancudo ATC Top Floor",{ -2358.132f, 3249.754f , 101.451f } },
	};
}

void InsideTeleportMenu::Init() {
	setParentSubmenu<TeleportMenu>();
	setName("Inside teleports", true, true);

	for (auto& tele : Inside) {
		addOption(ButtonOption(tele.first)
			.addFunction([tele] {TeleportMenuVars::TeleportToCoords(tele.second); })
			.addHotkey().addTranslation()
			.addTooltip(tele.first));
	}
}

/*Update once when submenu is opened*/
void InsideTeleportMenu::UpdateOnce() {}

/*Update while submenu is active*/
void InsideTeleportMenu::Update() {}

/*Background update*/
void InsideTeleportMenu::FeatureUpdate() {}

/*Singleton*/
InsideTeleportMenu* _instance;
InsideTeleportMenu* InsideTeleportMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new InsideTeleportMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
InsideTeleportMenu::~InsideTeleportMenu() { delete _instance; }