#include "stdafx.h"
#include "networkeventProtectionMenu.h"
#include "../protectionMenu.h"

using namespace NetworkEventsMenuVars;

namespace NetworkEventsMenuVars {
}

void NetworkEventsMenu::Init() {
	setParentSubmenu<ProtectionMenu>();
	setName("Network event protections", true, true);

	addOption(ToggleOption("Notify on attack")
		.addToggle(NetEvent::vars.notifyNE)
		.canBeSaved().addHotkey()
		.addTooltip("This will notify you when the attacks are done to you by others").addTranslation());

	addOption(ToggleOption("Redirect")
		.addToggle(NetEvent::vars.redirectNetEvents)
		.addTooltip("Redirect the network events that can be redirected")
		.addTranslation().canBeSaved().addHotkey()
		.addRequirement([] { return GetAuth()->IsVIP(); }));

	addOption(ToggleOption("Clear tasks")
		.addToggle(NetEvent::vars.clearTasks)
		.addTooltip("Stop modders freezing you in place")
		.addTranslation().canBeSaved().addHotkey());

	addOption(ToggleOption("Take weapons")
		.addToggle(NetEvent::vars.takeWeapons)
		.addTooltip("Stop modders removing your weapons")
		.addTranslation().canBeSaved().addHotkey());

	addOption(ToggleOption("Give weapons")
		.addToggle(NetEvent::vars.giveWeapons)
		.addTooltip("Stop modders giving you weapons")
		.addTranslation().canBeSaved().addHotkey());

	addOption(ToggleOption("Particle effects")
		.addToggle(NetEvent::vars.particleEffects)
		.addTooltip("Stop modders from doing particle effects on you")
		.addTranslation().canBeSaved().addHotkey());

	addOption(ToggleOption("Wanted level")
		.addToggle(NetEvent::vars.wantedLevel)
		.addTooltip("Stop modders altering your wanted level")
		.addTranslation().canBeSaved().addHotkey());

	addOption(ToggleOption("Weather")
		.addToggle(NetEvent::vars.weatherTime)
		.addTooltip("Stop modders changing your weather")
		.addTranslation().canBeSaved().addHotkey());

	addOption(ToggleOption("Time")
		.addToggle(ProtectionMenuVars::vars.gameclock)
		.addTooltip("Stop modders changing your game time")
		.addTranslation().canBeSaved().addHotkey());

	addOption(ToggleOption("Explosions")
		.addToggle(NetEvent::vars.explosions)
		.addTooltip("Stop modders doing explosions on you")
		.addTranslation().canBeSaved().addHotkey());

	addOption(ToggleOption("Control")
		.addToggle(NetEvent::vars.control)
		.addTooltip("Stop modders gaining control of your vehicle")
		.addTranslation().canBeSaved().addHotkey());

	addOption(ToggleOption("Sound")
		.addToggle(NetEvent::vars.sound)
		.addTooltip("Stop modders playing sound on your player")
		.addTranslation().canBeSaved().addHotkey());

	addOption(ToggleOption("Vote kick notification")
		.addToggle(NetEvent::vars.voteKick)
		.addTooltip("Notify you when players are trying to kick any player")
		.addTranslation().canBeSaved().addHotkey());

	addOption(ToggleOption("Report stats")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(NetEvent::vars.stat)
		.addTooltip("Displays players reporting you")
		.addTranslation().canBeSaved().addHotkey());

}

/*Update once when submenu is opened*/
void NetworkEventsMenu::UpdateOnce() {}

/*Update while submenu is active*/
void NetworkEventsMenu::Update() {}

/*Background update*/
void NetworkEventsMenu::FeatureUpdate() {}

/*Singleton*/
NetworkEventsMenu* _instance;
NetworkEventsMenu* NetworkEventsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new NetworkEventsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
NetworkEventsMenu::~NetworkEventsMenu() { delete _instance; }