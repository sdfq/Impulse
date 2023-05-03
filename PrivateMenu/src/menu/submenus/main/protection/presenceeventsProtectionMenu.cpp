#include "stdafx.h"
#include "presenceeventsProtectionMenu.h"
#include "../protectionMenu.h"

using namespace PresenceEventsMenuVars;

namespace PresenceEventsMenuVars {
	Vars vars;
}

void PresenceEventsMenu::Init() {
	setParentSubmenu<ProtectionMenu>();
	setName("Presence protection", true, true);

	addOption(ToggleOption("Notify on attack")
		.addToggle(NetEvent::vars.notifyPE)
		.canBeSaved().addHotkey()
		.addTooltip("This will notify you when the attacks are done to you by others").addTranslation());

	addOption(ToggleOption("Text messages")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.blocktextmessages)
		.addTooltip("This will block your from receiving text messages from the game and players")
		.addTranslation().canBeSaved().addHotkey());

	addOption(ToggleOption("Crew messages")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.blockcrewmessages)
		.addTooltip("This will block your from receiving Crew messages from the game and players")
		.addTranslation().canBeSaved().addHotkey());

	addOption(ToggleOption("Server rewards")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.blockserverrewards)
		.addTooltip("This will block your from receiving server reward screens from the game")
		.addTranslation().canBeSaved().addHotkey());

}

/*Update once when submenu is opened*/
void PresenceEventsMenu::UpdateOnce() {}

/*Update while submenu is active*/
void PresenceEventsMenu::Update() {}

/*Background update*/
void PresenceEventsMenu::FeatureUpdate() {}

/*Singleton*/
PresenceEventsMenu* _instance;
PresenceEventsMenu* PresenceEventsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new PresenceEventsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
PresenceEventsMenu::~PresenceEventsMenu() { delete _instance; }