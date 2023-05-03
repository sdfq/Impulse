#include "stdafx.h"
#include "blockallProtectionMenu.h"
#include "../protectionMenu.h"

using namespace BlockAllMenuVars;

namespace BlockAllMenuVars {
}

void BlockAllMenu::Init() {
	setParentSubmenu<ProtectionMenu>();
	setName("Block all protections", true, true);

	addOption(ToggleOption("Block all pickups")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(NetEvent::vars.pickups)
		.addTooltip("Stop modders spawning drops on you")
		.addTranslation().canBeSaved().addHotkey());

	addOption(ToggleOption("Block all peds")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(NetEvent::vars.blockpednet)
		.addTooltip("Stop any peds being spawned (not recommended to leave on)")
		.addTranslation().addHotkey());

	addOption(ToggleOption("Block all objects")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(NetEvent::vars.blockobjectnet)
		.addTooltip("Stop any objects being spawned (not recommended to leave on)")
		.addTranslation().addHotkey());

	addOption(ToggleOption("Block all cars")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(NetEvent::vars.blockautomobilenet)
		.addTooltip("Stop any cars being spawned (not recommended to leave on)")
		.addTranslation().addHotkey());

	addOption(ToggleOption("Block all bikes")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(NetEvent::vars.blockbikenet)
		.addTooltip("Stop any bikes being spawned (not recommended to leave on)")
		.addTranslation().addHotkey());

	addOption(ToggleOption("Block all planes")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(NetEvent::vars.blockplanenet)
		.addTooltip("Stop any planes being spawned (not recommended to leave on)")
		.addTranslation().addHotkey());

	addOption(ToggleOption("Block all helicopters")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(NetEvent::vars.blockhelinet)
		.addTooltip("Stop any helicopters being spawned (not recommended to leave on)")
		.addTranslation().addHotkey());

}

/*Update once when submenu is opened*/
void BlockAllMenu::UpdateOnce() {}

/*Update while submenu is active*/
void BlockAllMenu::Update() {}

/*Background update*/
void BlockAllMenu::FeatureUpdate() {}

/*Singleton*/
BlockAllMenu* _instance;
BlockAllMenu* BlockAllMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new BlockAllMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
BlockAllMenu::~BlockAllMenu() { delete _instance; }