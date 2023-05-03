#include "stdafx.h"
#include "fingerOfGodMenu.h"
#include "../../sessionMenu.h"

using namespace FingerOfGodMenuVars;

namespace FingerOfGodMenuVars {
	Vars vars;

	ScrollStruct<CrewIconId> Icons[] = {
		TranslationString("Rockstar", true), CREW_ICON_ROCKSTAR,
		TranslationString("Kappa", true), CREW_ICON_KAPPA,
		TranslationString("Doge", true), CREW_ICON_DOGE,
		TranslationString("Trollface", true), CREW_ICON_TROLLFACE,
		TranslationString("Anonymous", true), CREW_ICON_ANONYMOUS,
		TranslationString("Spoderman", true), CREW_ICON_SPODERMAN,
		TranslationString("Skull", true), CREW_ICON_SKULL,
		TranslationString("U MAD?", true), CREW_ICON_UMAD,
		TranslationString("Anime Tiddies", true), CREW_ICON_ANIME_TIDDIES,
		TranslationString("Redtube", true), CREW_ICON_REDTUBE
	};

}

void FingerOfGodMenu::Init() {
	setParentSubmenu<SessionMenu>();
	setName("Presence events", true, true);

	/*addOption(ButtonOption("Ragdoll")
		.addRequirement([] {return GetAuth()->IsTester(); })
		.addFunction([] {
		FingerOfGod::sendFingerCommand(vars.currentID, FINGER_RELAX);
	})
		.addTooltip("Ragdoll"));


	addOption(ButtonOption("Kill")
		.addRequirement([] {return GetAuth()->IsTester(); })
		.addFunction([] {
		FingerOfGod::sendFingerCommand(vars.currentID, FINGER_KILL);
	})
		.addTooltip("Kill"));

	addOption(ButtonOption("Admin kick")
		.addRequirement([] {return GetAuth()->IsTester(); })
		.addFunction([] {
		FingerOfGod::sendFingerCommand(vars.currentID, FINGER_ADMIN_KICK);
	})
		.addTooltip("Admin kick"));

	addOption(ButtonOption("Network kick")
		.addRequirement([] {return GetAuth()->IsTester(); })
		.addFunction([] {
		FingerOfGod::sendFingerCommand(vars.currentID, FINGER_NETWORK_KICK);
	})
		.addTooltip("Network kick"));

	addOption(ButtonOption("Vehicle")
		.addRequirement([] {return GetAuth()->IsTester(); })
		.addFunction([] {
		GetMenuInput()->AddToQueue([] {
			string test;
			if (GetMenuInput()->Text("Vehicle", test, 0, 100))
				FingerOfGod::sendFingerCommand(vars.currentID, FINGER_VEHICLE, test.c_str());
		});
	})
		.addTooltip("Vehicle"));*/

	addOption(ButtonOption("Fake cash correction")
		.addRequirement([] { return GetAuth()->IsTester(); })
		.addFunction([] { FingerOfGod::sendCashCorrection(vars.currentID, 999999999); })
		.addTooltip("Fake cash correction"));

	addOption(ScrollOption<CrewIconId>(SCROLL, "Crew message icon").addScroll(vars.iconIndex, 0, NUMOF(Icons) - 1, Icons)
		.addRequirement([] { return GetAuth()->IsTester(); })
		.canBeSaved().addTranslation().addTooltip("Select the icon that should appear when the target receives the message."));

	addOption(ButtonOption("Crew message")
		.addRequirement([] { return GetAuth()->IsTester(); })
		.addFunction([] {
		GetMenuInput()->AddToQueue([] {
			string senderID;
				string subject;
				if (GetMenuInput()->Text("Crew tag", subject, 0, 4)) {
					string message;
					if (GetMenuInput()->Text("Message", message, 0, 100)) {
						long long sender = _atoi64(senderID.c_str());
						if (senderID.empty() || senderID.length() < 5) {
							uint64_t base = PoolManager::GetEntityAddress(GetLocalPlayer().m_ped);
							if (base) {
								CPed* ped = (CPed*)(base);
								sender = ped->PlayerInfo->RockstarID;
							}
						}
						FingerOfGod::sendCrewMessageCommand(vars.currentID, sender, Icons[vars.iconIndex].m_result, subject.c_str(), message.c_str());
					}
				}
		});
	})
	.addTooltip("Send a crew message"));


	/*addOption(ButtonOption("Text message")
		.addRequirement([] { return GetAuth()->IsTester(); })
		.addFunction([] {
		GetMenuInput()->AddToQueue([] {
			string Messagetext;
			if (GetMenuInput()->Text("Message", Messagetext, 0, 100)) {
				FingerOfGod::sendTextMessage(vars.currentID, Messagetext.c_str());
			}
		});
	})
	.addTooltip("Send a text message"));*/
}

/*Update once when submenu is opened*/
void FingerOfGodMenu::UpdateOnce() {}

/*Update while submenu is active*/
void FingerOfGodMenu::Update() {}

/*Background update*/
void FingerOfGodMenu::FeatureUpdate() {}

/*Singleton*/
FingerOfGodMenu* _instance;
FingerOfGodMenu* FingerOfGodMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new FingerOfGodMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
FingerOfGodMenu::~FingerOfGodMenu() { delete _instance; }