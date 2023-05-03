#include "stdafx.h"
#include "protectionMenu.h"
#include "protection/attachmentProtectionMenu.h"
#include "../mainMenu.h"
#include "world/pedManagerMenu.h"
#include "world/trafficManagerMenu.h"
#include "session/playerList/player/griefingMenu.h"
#include "local/modelMenu.h"
#include "protection\attachmentProtectionMenu.h"
#include "protection\blockallProtectionMenu.h"
#include "protection\eventreactionProtectionMenu.h"
#include "protection\miscProtectionMenu.h"
#include "protection\networkeventProtectionMenu.h"
#include "protection\presenceeventsProtectionMenu.h"
#include "protection\scripteventProtectionMenu.h"
#include "protection/spoofingProtectionMenu.h"

using namespace ProtectionMenuVars;

namespace ProtectionMenuVars {
	Vars vars;
}

void ProtectionMenu::Init() {
	setParentSubmenu<MainMenu>();
	setName("Protection", true, true);

	addOption(SubmenuOption("Event reaction")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addTranslation().addHotkey()
		.addSubmenu<EventReactionMenu>()
		.addTooltip("Event protection"));

	addOption(SubmenuOption("Attachment")
		.addTranslation().addHotkey()
		.addSubmenu<AttachmentProtectionMenu>()
		.addTooltip("Attachment protection"));

	addOption(SubmenuOption("Network events")
		.addTranslation().addHotkey()
		.addSubmenu<NetworkEventsMenu>()
		.addTooltip("Network event protection"));

	addOption(SubmenuOption("Script events")
		.addTranslation().addHotkey()
		.addSubmenu<ScriptEventMenu>()
		.addTooltip("Script event protection"));

	addOption(SubmenuOption("Entity")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addTranslation().addHotkey()
		.addSubmenu<BlockAllMenu>()
		.addTooltip("Entity protection"));
	
	addOption(SubmenuOption("Spoofing")
		.addRequirement([] { return NETWORK::NetworkIsSessionActive(); })
		.addTranslation().addHotkey()
		.addSubmenu<SpoofingMenu>()
		.addTooltip("Spoofing protections"));

	addOption(ButtonOption("~c~Spoofing~s~")
		.addTooltip("You need to be online to use these options")
		.addRequirement([] { return !NETWORK::NetworkIsSessionActive(); })
	);

	addOption(SubmenuOption("Presence")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addTranslation().addHotkey()
		.addSubmenu<PresenceEventsMenu>()
		.addTooltip("Presence protection"));

	addOption(SubmenuOption("Misc")
		.addTranslation().addHotkey()
		.addSubmenu<MiscProtectionMenu>()
		.addTooltip("Misc protection"));

	addOption(ToggleOption("Impulse user block")
		.addToggle(NetEvent::vars.evolveBlock)
		.addTooltip("Stop other Impulse users messing with you (can take upto 1 minute to appear for others)")
		.addTranslation().canBeSaved().addHotkey());
}

/*Update once when submenu is opened*/
void ProtectionMenu::UpdateOnce() {}

/*Update while submenu is active*/
void ProtectionMenu::Update() {}

/*Background update*/
void ProtectionMenu::FeatureUpdate() {

	if (vars.protectObjects) {
		vector<int> ent = ObjectPool::GetObjects();
		for (int i = 0; i < ent.size(); i++) {
			if (ENTITY::GetEntityAttachedTo(i) == GetLocalPlayer().m_ped) {
				Entity e = ent.at(i);
				//LOG_DEBUG("Entity attached to us");
				ENTITY::DetachEntity(e, 1, 1);
				GetEntityControl()->SimpleRequestControl(e);
				int net = NETWORK::NetworkGetNetworkIdFromEntity(e);
				Player id;
				if (IsNetObjSaved(net, &id)) {
					if (vars.redirectObjects) ENTITY::AttachEntityToEntity(e, GetPlayer(id).m_ped, 0, 0, 0, 0, 0, 0, 180, 1, 0, 0, 1, 2, 1);
					else {
						ENTITY::SetEntityCoords(e, 0, 0, 0, 0, 0, 0, 1);
						ENTITY::SetObjectAsNoLongerNeeded(&e);
						ENTITY::DeleteEntity(&e);
					}
					if (vars.notifyObjects) GetRenderer()->NotifyBottom(va("Attachment blocked from %d", GetPlayer(id).m_name));
				}
			}
		}
	}


	if (vars.spoofIp) {
		if (!vars.originalIp) {
			vars.originalIp = *(DWORD*)(Backend::GetMemoryNameAddresses()[0] - 0x38);
		}

		if (*(DWORD*)(Backend::GetMemoryNameAddresses()[0] - 0x38) != 0xD83ACC4E) {
			*(DWORD*)(Backend::GetMemoryNameAddresses()[0] - 0x38) = 0xD83ACC4E;
			*(DWORD*)(Backend::GetMemoryNameAddresses()[1] - 0x38) = 0xD83ACC4E;
			*(DWORD*)(Backend::GetMemoryNameAddresses()[2] - 0x38) = 0xD83ACC4E;
		}
		ReClass::GetWorld()->LocalPed->PlayerInfo->ExternalIP = 0xD83ACC4E;
	}

	if (vars.spoofIpt) {
		for (int i = 0; i < Backend::GetMemoryNameAddresses().size(); i++) {
			if (*(DWORD*)(Backend::GetMemoryNameAddresses()[i] - 20) == Backend::m_originalRID) {
				if (!vars.originalIp) {
					vars.originalIp = *(DWORD*)(Backend::GetMemoryNameAddresses()[i] - 0x38);
				}

				Pattern::putVP(Backend::GetMemoryNameAddresses()[i] - 0x38, 0xD83ACC4E);
			}
		}

		ReClass::GetWorld()->LocalPed->PlayerInfo->ExternalIP = 0xD83ACC4E;
	}

	
}

/*Singleton*/
ProtectionMenu* _instance;
ProtectionMenu* ProtectionMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new ProtectionMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
ProtectionMenu::~ProtectionMenu() { delete _instance; }