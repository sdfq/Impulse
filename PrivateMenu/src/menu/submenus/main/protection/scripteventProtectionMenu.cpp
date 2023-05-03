#include "stdafx.h"
#include "scripteventProtectionMenu.h"
#include "../protectionMenu.h"

using namespace ScriptEventMenuVars;

namespace ScriptEventMenuVars {

	void BlockAllScriptEvents() {
		if (NETWORK::NetworkIsSessionActive()) {
			Global(1382674).At(23).As<int>() = 23; //non host kick
			Global(1382674).At(610).As<int>() = 610; //kick to sp
			Global(1382674).At(609).As<int>() = 609; //kick to sp
			//Global(1382674).At(499).As<int>() = 499; //teleport
			//Global(1382674).At(295).As<int>() = 295; //send to mission
			//Global(1382674).At(536).As<int>() = 536; //ceo kick
			//Global(1382674).At(558).As<int>() = 558; //ceo ban
			Global(1382674).At(685).As<int>() = 685;
			Global(1382674).At(584).As<int>() = 584;
			Global(1382674).At(418).As<int>() = 418;
			Global(1382674).At(417).As<int>() = 417;
			Global(1382674).At(7).As<int>() = 7;
			Global(1382674).At(2).As<int>() = 2;
		}
	}

}

void ScriptEventMenu::Init() {
	setParentSubmenu<ProtectionMenu>();
	setName("Script event protections", true, true);

	addOption(ToggleOption("Notify on attack")
		.addToggle(NetEvent::vars.notifySE)
		.canBeSaved().addHotkey()
		.addTooltip("This will notify you when the attacks are done to you by others").addTranslation());

	addOption(ToggleOption("Redirect")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(NetEvent::vars.redirectScriptEvents)
		.addTooltip("Redirect the remote events that can be redirected")
		.addTranslation().canBeSaved().addHotkey());

	addOption(ToggleOption("Script events")
		.addRequirement([] { return !NetEvent::vars.blockallncriptevents; })
		.addToggle(NetEvent::vars.scriptEvents)
		.addTooltip("Block some malicious script events with notifications")
		.addTranslation().canBeSaved().addHotkey());

	addOption(ToggleOption("Smart script event protection")
		.addRequirement([] { return !NetEvent::vars.blockallncriptevents; })
		.addToggle(NetEvent::vars.smartProtex)
		.addTooltip("Blocks every malicious event")
		.addTranslation().canBeSaved().addHotkey());

	addOption(ButtonOption("~c~Script events~s~")
		.addRequirement([] { return NetEvent::vars.blockallncriptevents; })
	);

	addOption(ButtonOption("~c~Smart script event protection~s~")
		.addRequirement([] { return NetEvent::vars.blockallncriptevents; })
	);

	addOption(ButtonOption("~c~Block all script events~s~")
		.addRequirement([] { return NetEvent::vars.smartProtex; })
	);

	addOption(ToggleOption("Block all script events")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addRequirement([] { return !NetEvent::vars.smartProtex; })
		.addToggle(NetEvent::vars.blockallncriptevents)
		.canBeSaved()
		.addTooltip("Block every script event ingame")
		.addTranslation().addHotkey());

}

/*Update once when submenu is opened*/
void ScriptEventMenu::UpdateOnce() {}

/*Update while submenu is active*/
void ScriptEventMenu::Update() {}

/*Background update*/
void ScriptEventMenu::FeatureUpdate() {

	for (int i = 0; i < NetEvent::SavedRemoteEventCount; i++) {
		if (!NetEvent::SavedRemoteEvents[i].m_redirected) {
			NetEvent::SavedRemoteEvents[i].m_redirected = true;
			Natives::TriggerScriptEvent(NetEvent::SavedRemoteEvents[i].m_args, NetEvent::SavedRemoteEvents[i].m_count, NetEvent::SavedRemoteEvents[i].m_args[1]);
		}
	}

	if (NetEvent::vars.blockallncriptevents) BlockAllScriptEvents();

	if (NetEvent::vars.scriptEvents || NetEvent::vars.smartProtex) {
		if (NETWORK::NetworkIsSessionActive()) {
			Global(1382674).At(23).As<int>() = 23; //non host kick
			Global(1382674).At(610).As<int>() = 610; //kick to sp
			Global(1382674).At(609).As<int>() = 609; //kick to sp
			//Global(1382674).At(499).As<int>() = 499; //teleport
			//Global(1382674).At(295).As<int>() = 295; //send to mission
			//Global(1382674).At(536).As<int>() = 536; //ceo kick
			//Global(1382674).At(558).As<int>() = 558; //ceo ban
			Global(1382674).At(685).As<int>() = 685; // only this just kill the rest off yeah i'll take a look 
			Global(1382674).At(584).As<int>() = 584;
			Global(1382674).At(418).As<int>() = 418;
			Global(1382674).At(417).As<int>() = 417;
			Global(1382674).At(7).As<int>() = 7;
			Global(1382674).At(2).As<int>() = 2;
		}
	}

}

/*Singleton*/
ScriptEventMenu* _instance;
ScriptEventMenu* ScriptEventMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new ScriptEventMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
ScriptEventMenu::~ScriptEventMenu() { delete _instance; }