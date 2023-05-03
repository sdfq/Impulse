#include "stdafx.h"
#include "messagingMenu.h"
#include "..\sessionMenu.h"

using namespace MessagingMenuVars;

namespace MessagingMenuVars {
	Vars vars;

	ScrollStruct<CrewIconId> Icons[] = {
		TranslationString("Rockstar icon", true), CREW_ICON_ROCKSTAR,
		TranslationString("Kappa icon", true), CREW_ICON_KAPPA,
		TranslationString("Doge icon", true), CREW_ICON_DOGE,
		TranslationString("Trollface icon", true), CREW_ICON_TROLLFACE,
		TranslationString("Anonymous icon", true), CREW_ICON_ANONYMOUS,
		TranslationString("Spoderman icon", true), CREW_ICON_SPODERMAN,
		TranslationString("Skull icon", true), CREW_ICON_SKULL,
		TranslationString("U MAD? icon", true), CREW_ICON_UMAD,
		TranslationString("Anime Tiddies icon", true), CREW_ICON_ANIME_TIDDIES,
		TranslationString("Redtube icon", true), CREW_ICON_REDTUBE,
		TranslationString("Transformers icon", true), CREW_ICON_TRANSFORMERS,
		TranslationString("Joker icon", true), CREW_ICON_JOKER,
		TranslationString("Deadpool icon", true), CREW_ICON_DEADPOOL,
		TranslationString("Rolling a blunt icon", true), CREW_ICON_ROLLINGBLUNT,
		TranslationString("Blunt man icon", true), CREW_ICON_BLUNTMAN,
		TranslationString("Micky icon", true), CREW_ICON_MICKY,
		TranslationString("iFruit icon", true), CREW_ICON_IFRUIT,
		TranslationString("Monkey icon", true), CREW_ICON_MONKEY,
		TranslationString("Razer icon", true), CREW_ICON_RAZER,
		TranslationString("Batman icon", true), CREW_ICON_BATMAN,
		TranslationString("Weed icon", true), CREW_ICON_WEED,
		TranslationString("Pika icon", true), CREW_ICON_PIKA,
		TranslationString("Negro icon", true), CREW_ICON_NEGRO,
		TranslationString("Clown icon", true), CREW_ICON_CLOWN,
		TranslationString("Jesus icon", true), CREW_ICON_JESUS
	};

	ScrollStruct<CrewIconId> Icons2[] = {
		TranslationString("Rockstar icon", true), CREW_ICON_ROCKSTAR,
		TranslationString("Kappa icon", true), CREW_ICON_KAPPA,
		TranslationString("Doge icon", true), CREW_ICON_DOGE,
		TranslationString("Trollface icon", true), CREW_ICON_TROLLFACE,
		TranslationString("Anonymous icon", true), CREW_ICON_ANONYMOUS,
		TranslationString("Spoderman icon", true), CREW_ICON_SPODERMAN,
		TranslationString("Skull icon", true), CREW_ICON_SKULL,
		TranslationString("U MAD? icon", true), CREW_ICON_UMAD,
		TranslationString("Anime Tiddies icon", true), CREW_ICON_ANIME_TIDDIES,
		TranslationString("Redtube icon", true), CREW_ICON_REDTUBE,
		TranslationString("Transformers icon", true), CREW_ICON_TRANSFORMERS,
		TranslationString("Joker icon", true), CREW_ICON_JOKER,
		TranslationString("Deadpool icon", true), CREW_ICON_DEADPOOL,
		TranslationString("Rolling a blunt icon", true), CREW_ICON_ROLLINGBLUNT,
		TranslationString("Blunt man icon", true), CREW_ICON_BLUNTMAN,
		TranslationString("Micky icon", true), CREW_ICON_MICKY,
		TranslationString("iFruit icon", true), CREW_ICON_IFRUIT,
		TranslationString("Monkey icon", true), CREW_ICON_MONKEY,
		TranslationString("Razer icon", true), CREW_ICON_RAZER,
		TranslationString("Batman icon", true), CREW_ICON_BATMAN,
		TranslationString("Weed icon", true), CREW_ICON_WEED,
		TranslationString("Pika icon", true), CREW_ICON_PIKA,
		TranslationString("Negro icon", true), CREW_ICON_NEGRO,
		TranslationString("Clown icon", true), CREW_ICON_CLOWN,
		TranslationString("Jesus icon", true), CREW_ICON_JESUS
	};

	ScrollStruct<CrewIconId> Icons3[] = {
		TranslationString("Rockstar icon", true), CREW_ICON_ROCKSTAR,
		TranslationString("Kappa icon", true), CREW_ICON_KAPPA,
		TranslationString("Doge icon", true), CREW_ICON_DOGE,
		TranslationString("Trollface icon", true), CREW_ICON_TROLLFACE,
		TranslationString("Anonymous icon", true), CREW_ICON_ANONYMOUS,
		TranslationString("Spoderman icon", true), CREW_ICON_SPODERMAN,
		TranslationString("Skull icon", true), CREW_ICON_SKULL,
		TranslationString("U MAD? icon", true), CREW_ICON_UMAD,
		TranslationString("Anime Tiddies icon", true), CREW_ICON_ANIME_TIDDIES,
		TranslationString("Redtube icon", true), CREW_ICON_REDTUBE,
		TranslationString("Transformers icon", true), CREW_ICON_TRANSFORMERS,
		TranslationString("Joker icon", true), CREW_ICON_JOKER,
		TranslationString("Deadpool icon", true), CREW_ICON_DEADPOOL,
		TranslationString("Rolling a blunt icon", true), CREW_ICON_ROLLINGBLUNT,
		TranslationString("Blunt man icon", true), CREW_ICON_BLUNTMAN,
		TranslationString("Micky icon", true), CREW_ICON_MICKY,
		TranslationString("iFruit icon", true), CREW_ICON_IFRUIT,
		TranslationString("Monkey icon", true), CREW_ICON_MONKEY,
		TranslationString("Razer icon", true), CREW_ICON_RAZER,
		TranslationString("Batman icon", true), CREW_ICON_BATMAN,
		TranslationString("Weed icon", true), CREW_ICON_WEED,
		TranslationString("Pika icon", true), CREW_ICON_PIKA,
		TranslationString("Negro icon", true), CREW_ICON_NEGRO,
		TranslationString("Clown icon", true), CREW_ICON_CLOWN,
		TranslationString("Jesus icon", true), CREW_ICON_JESUS
	};

	ScrollStruct<int> RIDorSession[] = {
		TranslationString("RID", true), 0,
		TranslationString("Session", true), 1
	};

	void SendtoRID() {
		GetMenuInput()->AddToQueue([] {
			long long target;
			string senderID;
			string input;
			if (GetMenuInput()->Text("Enter the target R*ID", input, 0, 10)) {
				target = _atoi64(input.c_str());
				FingerOfGod::sendCrewMessageCommand(target, 0, Icons3[vars.iconIndex3].m_result, vars.customsubject.c_str(), vars.custommessage.c_str());
				GetRenderer()->NotifyMap("Message Sent to RID");
			}
		});
	}

	void SendtoSession() {
		GetRenderer()->NotifyMap("Message Sent to lobby");
			GetMenuInput()->AddToQueue([] {
				OnlinePlayerCallback(true, [](SPlayer player) {
					string recieverID2;
					long long reciever = _atoi64(recieverID2.c_str());
					uint64_t base = PoolManager::GetEntityAddress(player.m_ped);
					if (base) {
						CPed* ped = (CPed*)(base);
						reciever = ped->PlayerInfo->RockstarID;
					}
						if (player.m_id != GetLocalPlayer().m_id) {
							FingerOfGod::sendCrewMessageCommand(reciever, 0, Icons3[vars.iconIndex3].m_result, vars.customsubject.c_str(), vars.custommessage.c_str());
						}
				});
			});
		}

	void SendToSessionNonCustom() {
		OnlinePlayerCallback(true, [](SPlayer player) {
			string recieverID2;
			long long reciever = _atoi64(recieverID2.c_str());
			uint64_t base = PoolManager::GetEntityAddress(player.m_ped);
			if (base) {
				CPed* ped = (CPed*)(base);
				reciever = ped->PlayerInfo->RockstarID;
			}
			if (player.m_id != GetLocalPlayer().m_id) {
				FingerOfGod::sendCrewMessageCommand(reciever, 0, Icons2[vars.iconIndex2].m_result, vars.noncustomsubject.c_str(), vars.noncustommessage.c_str());
			}
		});
	}

	void SpamRID() {
		GetMenuInput()->AddToQueue([] {
			string input;
			if (GetMenuInput()->Text("RID", input, 3, 15)) {
				vars.RIDtoSpam = _atoi64(input.c_str());
			}
		});
	}

	void SpamMessage() {
		GetMenuInput()->AddToQueue([] {
			string message;
			if (GetMenuInput()->Text("Enter message", message, 0, 100)) {
				vars.spammessage = message.c_str();
			}
		});
	}

	void SpamRockstarIDMsg() {
		static int TIMER;
		Utils::DoTimedFunction(&TIMER, 10000, [] {
			string subject = to_string(MISC::GetRandomIntInRange(1000, 9999));
			FingerOfGod::sendCrewMessageCommand(vars.RIDtoSpam, 0, Icons[vars.iconIndex].m_result, subject.c_str(), vars.spammessage.c_str());
		});
	}

}

void MessagingMenu::Init() {
	setParentSubmenu<SessionMenu>();
	setName("Messenging", true, true);

	addOption(ScrollOption<CrewIconId>(SCROLLSELECT, "Send message to rockstar ID")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addScroll(vars.iconIndex, 0, NUMOF(Icons) - 1, Icons)
		.addFunction([] {
		GetMenuInput()->AddToQueue([] {
			long long target;
			string senderID;
			string input;
			if (GetMenuInput()->Text("Enter the target R*ID", input, 0, 10)) {
				target = _atoi64(input.c_str());
				string subject;
				if (GetMenuInput()->Text("Enter clan tag", subject, 0, 4)) {
					string message;
					if (GetMenuInput()->Text("Enter message", message, 0, 100)) {
						FingerOfGod::sendCrewMessageCommand(target, 0, Icons[vars.iconIndex].m_result, subject.c_str(), message.c_str());
						GetRenderer()->NotifyMap("Message Sent to RID");
					}
				}
			}
		});
	})
		.addTooltip("Send a message to a targeted rockstar ID"));

	addOption(ScrollOption<CrewIconId>(SCROLLSELECT, "Send message to session")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addScroll(vars.iconIndex2, 0, NUMOF(Icons2) - 1, Icons2)
		.addFunction([] { 
			GetMenuInput()->AddToQueue([] {
				if (GetMenuInput()->Text("Enter clan tag", vars.noncustomsubject, 0, 4)) {
					if (GetMenuInput()->Text("Enter message", vars.noncustommessage, 0, 100)) {
						SendToSessionNonCustom();
						GetRenderer()->NotifyMap("Message Sent to lobby");
					}
				}
		});
	})
		.addTooltip("Send a message to an entire session"));

	/*addOption(ButtonOption("Text message")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addFunction([] {
		GetMenuInput()->AddToQueue([] {
			long long target;
			string input;
			if (GetMenuInput()->Text("Enter the target R*ID", input, 0, 10)) {
				target = _atoi64(input.c_str());
				string Messagetext;
				if (GetMenuInput()->Text("Message", Messagetext, 0, 100)) {
					FingerOfGod::sendTextMessage(target, Messagetext.c_str(), 0);
					Player p_Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
					auto handle[26];
					NETWORK::NETWORK_HANDLE_FROM_PLAYER(p_Handle, &handle[0], 13);
					NETWORK::NETWORK_SEND_TEXT_MESSAGE("Your Shit", &handle[0]);
				}
			}
		});
	})
		.addTooltip("Send a text message"));*/

	addOption(ButtonOption("~o~[Staff]~s~ Send ad to all players")
		.addRequirement([] { return GetAuth()->IsStaff(); })
		.addFunction([] { OnlinePlayerCallback(true, [](SPlayer player) {
			string recieverID2;
			string subject = "GAME";
			string message = "<font size='40'>~y~NOTICE<font size='15'>~s~  Purchase the best mod menu at Impulse.one today!";
			long long reciever = _atoi64(recieverID2.c_str());
			uint64_t base = PoolManager::GetEntityAddress(player.m_ped);
			if (base) {
				CPed* ped = (CPed*)(base);
				reciever = ped->PlayerInfo->RockstarID;
			}
			FingerOfGod::sendCrewMessageCommand(reciever, 0, CREW_ICON_ROCKSTAR, subject.c_str(), message.c_str());
		});
	})
		.addTranslation().addHotkey()
		.addTooltip("This will send a pre-baked message to all players in session").addTranslation());

	addOption(BreakOption("Spam Messages"));

	addOption(ButtonOption("")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addFunction(SpamRID)
		.addOnUpdate([](ButtonOption* option) {
		static int TIMER, offset;
		static char name[50];
		vaBuff(name, 50, "RID to spam: %i", vars.RIDtoSpam);
		option->setName(name);
	})
		.addTooltip("Click to input a RID to spam."));

	addOption(ButtonOption("")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addFunction(SpamMessage)
		.addOnUpdate([](ButtonOption* option) {
		static int TIMER, offset;
		static char name[50];
		vaBuff(name, 50, "Message to spam with: %s", vars.spammessage.c_str());
		option->setName(name);
	})
		.addTooltip("Click to input a message to spam with."));

	addOption(ToggleOption("Spam RID with details above")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.SpamRID)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("This will spam the the chosen RID with your desired message above."));

	addOption(BreakOption("Custom Preset Messages"));

	addOption(ButtonOption("Create custom message")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addFunction([this] {
		GetMenuInput()->AddToQueue([] {
			string input;
			if (GetMenuInput()->Text("Message name", input, 2, 50)) {
				vars.Messagename = input.c_str();
				string input;
				if (GetMenuInput()->Text("Message text", input, 2, 50)) {
					vars.custommessage = input.c_str();
					string input;
					if (GetMenuInput()->Text("Message tag", input, 1, 4)) {
						vars.customsubject = input.c_str();

						char* path = va("%s%s.json", GetConfig()->GetMessagingPath(), vars.Messagename);
						ofstream file(path);
						json j;
						j["message"] = (string)vars.custommessage;
						j["tag"] = (string)vars.customsubject;
						file << setw(4) << j;
						file.close();
					}

				}
			}
		});
	})
		.addHotkey()
		.addTooltip("Save message"));

	addOption(ScrollOption<CrewIconId>(SCROLL, "Icon")
		.addScroll(vars.iconIndex3, 0, NUMOF(Icons3) - 1, Icons3)
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.canBeSaved().addTranslation().addTooltip("Select the icon that should appear when the target receives the message."));

	addOption(ScrollOption<int>(SCROLL, "Send to")
		.addScroll(vars.RIDorSessionChk, 0, NUMOF(RIDorSession) - 1, RIDorSession)
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.canBeSaved().addTranslation().addTooltip("Select if the saved messages below get sent to a RID or a lobby."));

}

/*Update once when submenu is opened*/
void MessagingMenu::UpdateOnce() {}

/*Update while submenu is active*/
void MessagingMenu::Update() {
	static int TIMER;
	static bool update = true;
	Utils::DoTimedFunction(&TIMER, 1000, [] {update = true; });
	if (update) {
		clearOptionsOffset(11);
		for (const auto & entry : std::experimental::filesystem::directory_iterator(GetConfig()->GetMessagingPath())) {
			auto const pos = entry.path().filename().string().find_last_of('.');
			string option = entry.path().filename().string().substr(0, pos);
			char* path = va("%s%s.json", GetConfig()->GetMessagingPath(), option.c_str());
			fstream file(path);
			json j;
			j = json::parse(file);
			addOption(ButtonOption(va("Message name: %s", option.c_str()))
				.addRequirement([] { return GetAuth()->IsVIP(); })
				.addFunction([=] {
				char* path = va("%s%s.json", GetConfig()->GetMessagingPath(), option.c_str());
				fstream file(path);
				json j;
				j = json::parse(file);
				vars.custommessage = j["message"].get<string>().c_str();
				vars.customsubject = j["tag"].get<string>().c_str();
				if (vars.RIDorSessionChk == 0) SendtoRID();
				if (vars.RIDorSessionChk == 1) SendtoSession();
			})
				.addTooltip(va("Message: %s \nTag: %s", j["message"].get<string>().c_str(), j["tag"].get<string>().c_str())));

		}
		update = false;
	}
}

/*Background update*/
void MessagingMenu::FeatureUpdate() {
	if (vars.SpamRID) SpamRockstarIDMsg();

	/*static int TIMER;
	static bool update = true;
	Utils::DoTimedFunction(&TIMER, 1000, [] {update = true; });
	if (update) {
		clearOptionsOffset(12);
		for (const auto & entry : std::experimental::filesystem::directory_iterator(GetConfig()->GetMessagingPath())) {
			auto const pos = entry.path().filename().string().find_last_of('.');
			string option = entry.path().filename().string().substr(0, pos);
			char* path = va("%s%s.json", GetConfig()->GetMessagingPath(), option);
			fstream file(path);
			json j;
			j = json::parse(file);
			addOption(ButtonOption(va("Message name: %s", option.c_str()))
				.addFunction([=] {
				char* path = va("%s%s.json", GetConfig()->GetMessagingPath(), option);
				fstream file(path);
				json j;
				j = json::parse(file);
				vars.custommessage = j["message"].get<string>().c_str();
				if (vars.RIDorSessionChk == 0) SendtoRID();
				if (vars.RIDorSessionChk == 1) SendtoSession();

			})
				.addTooltip(va("Message: %s", j["message"].get<string>().c_str())));

		}
		update = false;
	}*/
}

/*Singleton*/
MessagingMenu* _instance;
MessagingMenu* MessagingMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new MessagingMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
MessagingMenu::~MessagingMenu() { delete _instance; }