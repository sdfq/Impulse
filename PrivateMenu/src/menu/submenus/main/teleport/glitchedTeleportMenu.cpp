#include "stdafx.h"
#include "glitchedTeleportMenu.h"
#include "../teleportMenu.h"

using namespace GlitchedTeleportMenuVars;

namespace GlitchedTeleportMenuVars {
	vector<pair<String, Vector3>> Glitched = {
		{ "Race Underground Bunker",{ 403.78f, -961.35f, -99.00f } },
	{ "FIB Roof Glitch",{ 135.9541f, -749.8984f, 258.1520f } },
	{ "Police Station Glitch",{ 447.0900f, -985.5400f, 30.9600f } },
	{ "Behind Bar In Strip Club",{ 126.1211f, -1278.5130f, 29.2696f } },
	{ "Building Glitch",{ -91.6870f, 33.0948f, 71.4655f } },
	{ "Inside Store",{ -1244.1380f, -1454.9980f, 4.3478f } },
	{ "City Wall Glitch",{ -254.9432f, -147.3534f, 42.7314f } },
	{ "Inside Casino",{ 937.4756f, 42.4248f, 80.8990f } },
	{ "Beach House",{ -1907.3500f, -577.2352f, 20.1223f } },
	{ "Under The Bridge Glitch",{ 721.6599f, -1000.6510f, 23.5455f } }
	};

}

void GlitchedTeleportMenu::Init() {
	setParentSubmenu<TeleportMenu>();
	setName("Glitched teleports", true, true);

	for (auto& tele : Glitched) {
		addOption(ButtonOption(tele.first)
			.addFunction([tele] {TeleportMenuVars::TeleportToCoords(tele.second); })
			.addHotkey().addTranslation()
			.addTooltip(tele.first));
	}
}

/*Update once when submenu is opened*/
void GlitchedTeleportMenu::UpdateOnce() {}

/*Update while submenu is active*/
void GlitchedTeleportMenu::Update() {}

/*Background update*/
void GlitchedTeleportMenu::FeatureUpdate() {}

/*Singleton*/
GlitchedTeleportMenu* _instance;
GlitchedTeleportMenu* GlitchedTeleportMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new GlitchedTeleportMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
GlitchedTeleportMenu::~GlitchedTeleportMenu() { delete _instance; }