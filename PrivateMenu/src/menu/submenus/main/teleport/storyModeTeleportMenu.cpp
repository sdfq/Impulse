#include "stdafx.h"
#include "storyModeTeleportMenu.h"
#include "../teleportMenu.h"

using namespace StoryModeTeleportMenuVars;

namespace StoryModeTeleportMenuVars {
	vector<pair<char*, Vector3>> SinglePlayer = {
		{ "Franklin's New House",{ 7.4150f, 535.5486f, 176.0279f } },
	{ "Franklin's Old House",{ -14.9693f, -1436.4430f, 31.1185f } },
	{ "Michael's House",{ -813.6030f, 179.4738f, 72.1589f } },
	{ "Lester's House",{ 1273.69f, -1718.72f, 54.68f } },
	{ "Wayne's Cousin's House",{ -1159.034f, -1521.180f, 10.6327f } },
	{ "Trevor's House ",{ 1974.7580f, 3819.4570f, 33.4363f } },
	{ "Trevor's Meth Lab",{ 1397.5240f, 3607.4230f, 38.9419f } },
	{ "Trevor's Office",{ 97.2707f, -1290.9940f, 29.2688f } },
	{ "Floyd's Apartment",{ -1150.703f, -1520.713f, 10.633f } },
	{ "Lester's House",{ 1273.898f, -1719.304f, 54.771f } },
	};
	
}

void StoryModeTeleportMenu::Init() {
	setParentSubmenu<TeleportMenu>();
	setName("Story mode teleports", true, true);

	for (auto& tele : SinglePlayer) {
		addOption(ButtonOption(tele.first)
			.addFunction([tele] {TeleportMenuVars::TeleportToCoords(tele.second); })
			.addHotkey().addTranslation()
			.addTooltip(tele.first));
	}
}

/*Update once when submenu is opened*/
void StoryModeTeleportMenu::UpdateOnce() {}

/*Update while submenu is active*/
void StoryModeTeleportMenu::Update() {}

/*Background update*/
void StoryModeTeleportMenu::FeatureUpdate() {}

/*Singleton*/
StoryModeTeleportMenu* _instance;
StoryModeTeleportMenu* StoryModeTeleportMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new StoryModeTeleportMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
StoryModeTeleportMenu::~StoryModeTeleportMenu() { delete _instance; }