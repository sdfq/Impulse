#include "stdafx.h"
#include "eventreactionProtectionMenu.h"
#include "menu/submenus/main/session/playerList/player/remoteMenu.h"
#include "menu/submenus/main/session/playerList/player/playerTeleportMenu.h"
#include "menu/submenus/main/session/playerList/player/griefingMenu.h"
#include "menu/submenus/main/protection/miscProtectionMenu.h"
#include "../protectionMenu.h"

using namespace EventReactionMenuVars;

namespace EventReactionMenuVars {
	Vars vars;
	
	vector<PlayerType_t> users;

	enum eActions {
		KICKP,
		FREEZE,
		EXPLODE,
		TELEPORT_TO,
		CRASH,
		BLAME,
		MESSAGE
	};

	ScrollStruct<int> Kickresponses[] = {
		TranslationString("Kick", true), 0,
		TranslationString("Freeze", true), 1,
		TranslationString("Explode", true), 2,
		TranslationString("Teleport to", true), 3,
		TranslationString("Crash", true), 4,
		TranslationString("Blame", true), 5,
		TranslationString("Message", true), 6
	};

	ScrollStruct<int> Reportresponses[] = {
		TranslationString("Kick", true), 0,
		TranslationString("Freeze", true), 1,
		TranslationString("Explode", true), 2,
		TranslationString("Teleport to", true), 3,
		TranslationString("Crash", true), 4,
		TranslationString("Blame", true), 5,
		TranslationString("Message", true), 6
	};

	ScrollStruct<int> SEresponses[] = {
		TranslationString("Kick", true), 0,
		TranslationString("Freeze", true), 1,
		TranslationString("Explode", true), 2,
		TranslationString("Teleport to", true), 3,
		TranslationString("Crash", true), 4,
		TranslationString("Blame", true), 5,
		TranslationString("Message", true), 6
	};

	ScrollStruct<int> NEresponses[] = {
		TranslationString("Kick", true), 0,
		TranslationString("Freeze", true), 1,
		TranslationString("Explode", true), 2,
		TranslationString("Teleport to", true), 3,
		TranslationString("Crash", true), 4,
		TranslationString("Blame", true), 5,
		TranslationString("Message", true), 6
	};

	void AddPlayer(PlayerType_t t) {
		if (t.Reason == REPORT && !vars.enableeventreactionreport) return;
		if (t.Reason == MALICIOUS && !vars.enableeventreactionSE) return;
		if (t.Reason == KICK && !vars.enableeventreactionkick) return;
		if (t.Reason == NET_EVENT && !vars.enableeventreactionNE) return;
		for (PlayerType_t p : users) {
			if (p.Nickname == t.Nickname) return;
		}
		users.push_back(t);
	}

	void AddToBlacklistAuto(Player entity, string name, string reasonfor) {
		json j;

		if (GetConfig()->DoesFileExist(GetConfig()->GetBlacklistPath())) {
			fstream file(GetConfig()->GetBlacklistPath());
			j = json::parse(file);
			file.open(GetConfig()->GetBlacklistPath(), ofstream::out | ofstream::trunc);
			file.close();
		}
		CPed* ped = (CPed*)(PoolManager::GetEntityAddress(entity));
		if (ped != 0) {
			string rid = to_string(ped->PlayerInfo->RockstarID);
			if (Utils::DoesItExistInBlacklist(_atoi64(rid.c_str()), "", true)) return;
			string pname = name;
			string reason = reasonfor;
			string combined = pname + " - " + reason;
			j.push_back({ rid, 0, 0, 1, 0, 0, 0, combined }); // last 1, we are adding a rid
		}
		ofstream file2(GetConfig()->GetBlacklistPath());
		file2 << setw(4) << j;
		file2.close();
	}
	
	void CustomMessage() {
		GetMenuInput()->AddToQueue([] {
			string message;
			if (GetMenuInput()->Text("Enter message", message, 0, 100)) {
				vars.custommessage = message.c_str();
			}
		});
	}
}

void EventReactionMenu::Init() {
	setParentSubmenu<ProtectionMenu>();
	setName("Event reactions", true, true);

	addOption(ToggleOption("Notify on attack")
		.addToggle(NetEvent::vars.notifyER)
		.canBeSaved().addHotkey()
		.addTooltip("This will notify you when the attacks are done to you by others").addTranslation());

	addOption(ScrollOption<int>(TOGGLE, "If kick is received")
		.addToggle(vars.enableeventreactionkick)
		.addScroll(vars.kicknum, 0, NUMOF(Kickresponses) - 1, Kickresponses)
		.addTooltip("If someone sends a kick event to you it will do what you decide")
		.addTranslation().canBeSaved().addHotkey());

	addOption(ScrollOption<int>(TOGGLE, "If report is received")
		.addToggle(vars.enableeventreactionreport)
		.addScroll(vars.reportnum, 0, NUMOF(Reportresponses) - 1, Reportresponses)
		.addTooltip("If someone sends a report event to you it will do what you decide")
		.addTranslation().canBeSaved().addHotkey());

	addOption(ScrollOption<int>(TOGGLE, "If malicious script event is received")
		.addToggle(vars.enableeventreactionSE)
		.addScroll(vars.SEnum, 0, NUMOF(SEresponses) - 1, SEresponses)
		.addTooltip("If someone sends a script event to you it will do what you decide")
		.addTranslation().canBeSaved().addHotkey());

	addOption(ScrollOption<int>(TOGGLE, "If malicious network event is received")
		.addToggle(vars.enableeventreactionNE)
		.addScroll(vars.NEnum, 0, NUMOF(NEresponses) - 1, NEresponses)
		.addTooltip("If someone sends a network event to you it will do what you decide")
		.addTranslation().canBeSaved().addHotkey());

	addOption(ToggleOption("Auto add to overseer once recieved")
		.addToggle(vars.autoaddtoblacklist)
		.addTooltip("This will auto add flagging players to your overseer using rid / name and reason")
		.addTranslation().canBeSaved().addHotkey());

	/*addOption(ButtonOption("")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addFunction(CustomMessage)
		.addOnUpdate([](ButtonOption* option) {
		static int TIMER, offset;
		static char name[50];
		vaBuff(name, 50, "Custom message: %s", vars.custommessage.c_str());
		option->setName(name);
	})
		.addTooltip("Click to input a message to use with send message on recieve."));*/
#ifdef HARD_DEV
	
#endif
}

/*Update once when submenu is opened*/
void EventReactionMenu::UpdateOnce() {}

/*Update while submenu is active*/
void EventReactionMenu::Update() {}

/*Background update*/
void EventReactionMenu::FeatureUpdate() {
	static int TIMER;
	static bool update = true;
	Utils::DoTimedFunction(&TIMER, 1000, [] { update = true; });
	
	if (update) {
		for (int i = 0; i < users.size(); i++) {
			int AppropriateAction = 0;
			Vector3 coords = GetPlayer(users.at(i).Id).m_coordinates;
			//LOG_DEBUG("NICKNAME: %s ID: %d REPORT: %d", users.at(i).Nickname, users.at(i).Id, users.at(i).Reason);
			switch (users.at(i).Reason) {
			case eResponses::KICK:
				AppropriateAction = vars.kicknum;
				if (vars.autoaddtoblacklist) {
					AddToBlacklistAuto(GetPlayer(users.at(i).Id).m_ped, GetPlayer(users.at(i).Id).m_name, "Sent Kick Events");
				}
				break;
			case eResponses::MALICIOUS:
				AppropriateAction = vars.SEnum;
				if (vars.autoaddtoblacklist) {
					AddToBlacklistAuto(GetPlayer(users.at(i).Id).m_ped, GetPlayer(users.at(i).Id).m_name, "Sent Malicious Events");
				}
				break;
			case eResponses::NET_EVENT:
				AppropriateAction = vars.NEnum;
				if (vars.autoaddtoblacklist) {
					AddToBlacklistAuto(GetPlayer(users.at(i).Id).m_ped, GetPlayer(users.at(i).Id).m_name, "Sent Net Events");
				}
				break;
			case eResponses::REPORT:
				AppropriateAction = vars.reportnum;
				if (vars.autoaddtoblacklist) {
					AddToBlacklistAuto(GetPlayer(users.at(i).Id).m_ped, GetPlayer(users.at(i).Id).m_name, "Reported You");
				}
				break;
			}
			switch (AppropriateAction) {
			case eActions::KICKP:
				RemoteMenuVars::KickToSingleplayer(GetPlayer(users.at(i).Id));
				RemoteMenuVars::NonHostKick(GetPlayer(users.at(i).Id));
				if (NetEvent::vars.notifyER) GetRenderer()->NotifyMap(va("Event reaction: Kick attempt from %s", users.at(i).Nickname));
				break;
			case eActions::TELEPORT_TO:
				PlayerTeleportMenuVars::TeleportToPlayer(GetPlayer(users.at(i).Id));
				if (NetEvent::vars.notifyER) GetRenderer()->NotifyMap(va("Event reaction: Teleported to %s", users.at(i).Nickname));
				break;
			case eActions::FREEZE:
				BRAIN::ClearPedTasksImmediately(GetPlayer(users.at(i).Id).m_ped);
				if (NetEvent::vars.notifyER) GetRenderer()->NotifyMap(va("Event reaction: Frozen %s", users.at(i).Nickname));
				break;
			case eActions::EXPLODE:
				FIRE::AddExplosion(coords.x, coords.y, coords.z, 29, 10, 1, 0, 1, 0);
				if (NetEvent::vars.notifyER) GetRenderer()->NotifyMap(va("Event reaction: Exploded %s", users.at(i).Nickname));
				break;
			case eActions::BLAME:
				GriefingMenuVars::BlamePlayer(GetPlayer(users.at(i).Id));
				if (NetEvent::vars.notifyER) GetRenderer()->NotifyMap(va("Event reaction: Blamed %s", users.at(i).Nickname));
				break;
			case eActions::CRASH:
				MiscProtectionMenuVars::vars.safesplace = true;
				GriefingMenuVars::CrashPlayer(GetPlayer(users.at(i).Id));
				if (NetEvent::vars.notifyER) GetRenderer()->NotifyMap(va("Event reaction: Crashed %s", users.at(i).Nickname));
				break;
			case eActions::MESSAGE:
				string recieverID2;
				string subject = to_string(MISC::GetRandomIntInRange(1000, 9999));
				string message = "<font size='40'>~y~NOTICE<font size='15'>~s~  Dont fuck with the king of cuck";
				long long reciever = _atoi64(recieverID2.c_str());
				uint64_t base = PoolManager::GetEntityAddress(GetPlayer(users.at(i).Id).m_ped);
				if (base) {
					CPed* ped = (CPed*)(base);
					reciever = ped->PlayerInfo->RockstarID;
				}
				FingerOfGod::sendCrewMessageCommand(reciever, 0, CREW_ICON_ROCKSTAR, subject.c_str(), message.c_str());
				if (NetEvent::vars.notifyER) GetRenderer()->NotifyMap(va("Event reaction: Messaged %s", users.at(i).Nickname));
				break;
			}
		}
		users.clear();
		update = false;
	}
}

/*Singleton*/
EventReactionMenu* _instance;
EventReactionMenu* EventReactionMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new EventReactionMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
EventReactionMenu::~EventReactionMenu() { delete _instance; }