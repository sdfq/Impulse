#include "stdafx.h"
#include "spoofingProtectionMenu.h"
#include "../protectionMenu.h"
#include "menu\submenus\main\session\nameMenu.h"

using namespace SpoofingMenuVars;

namespace SpoofingMenuVars {
	Vars vars;

	vector<int> staffrockstarid{
	103019313,
	103054099,
	104041189,
	110470958,
	119266383,
	119958356,
	121397532,
	121698158,
	123839036,
	123849404,
	127531278,
	127878077,
	121943600,
	129159629,
	18965281,
	216820,
	56778561,
	99453545,
	99453882,
	10612782,
	18914188,
	134412628,
	133709045,
	64234321,
	131973478,
	137579070
	};

	shared_ptr<ButtonOption> m_RIDNameOption = nullptr;

	void SpoofRockstar() {
		GetMenuInput()->AddToQueue([] {
			string input;
			if (GetMenuInput()->Text("Enter R* ID for spoof", input, 1, 15)) {
				/*vars.checkid = _atoi64(input.c_str());
				for (int currentid : staffrockstarid) {
					if (vars.checkid == currentid && !GetAuth()->IsStaff()) {
						GetRenderer()->NotifyMap("Please choose another r* id");
						return;
					}
				}*/
					Backend::m_spoofingRID = _atoi64(input.c_str());
					GetRenderer()->NotifyMap("Please enable r* spoof and join a new session to set your new r* id");
			}
		});
	}

	void ResetSpoof() {
		Backend::m_spoofingRID = Backend::m_originalRID;
	}

	void SetProfile() {

		/*vars.checkid = vars.customid;
		for (int currentid : staffrockstarid) {
			if (vars.checkid == currentid && !GetAuth()->IsStaff()) {
				GetRenderer()->NotifyMap("Please choose another r* id for this profile");
				return;
			}
		}*/

		Backend::m_spoofingRID = vars.customid;
		string name = vars.customname.c_str();
		NameMenuVars::setName(name.c_str());
		NetEvent::vars.rockstarid = true;
		GetRenderer()->NotifyMap("Join a new session to set the new r* id and chosen name");
	}

	void CustomName() {
		GetMenuInput()->AddToQueue([] {
			string input;
			if (GetMenuInput()->Text("Name", input, 1, 16)) {
				vars.customname = input;
			}
		});
	}

	void CustomID() {
		GetMenuInput()->AddToQueue([] {
			string input;
			if (GetMenuInput()->Text("ID", input, 1, 15)) {
				vars.customid = _atoi64(input.c_str());
			}
		});
	}

	void RandomSpoofRockstar() {
		Backend::m_spoofingRID = MISC::GetRandomIntInRange(1000000, 34000000);
		GetRenderer()->NotifyMap("Please enable r* spoof and join a new session to set the new r* id");
	}

	void MrBossSpoofRockstar() {
		Backend::m_spoofingRID = 26204131;
		string name = "MrBossFTW";
		NameMenuVars::setName(name.c_str());
		NetEvent::vars.rockstarid = true;
		GetRenderer()->NotifyMap("Join a new session to set the new r* id and chosen name");
	}

	void NoughtPointPCRandomSpoofRockstar() {
		Backend::m_spoofingRID = 117730150;
		string name = "NoughtPointPC";
		NameMenuVars::setName(name.c_str());
		NetEvent::vars.rockstarid = true;
		GetRenderer()->NotifyMap("Join a new session to set the new r* id and chosen name");
	}

	void KwebbelkopRandomSpoofRockstar() {
		Backend::m_spoofingRID = 91533847;
		string name = "Azzyland";
		NameMenuVars::setName(name.c_str());
		NetEvent::vars.rockstarid = true;
		GetRenderer()->NotifyMap("Join a new session to set the new r* id and chosen name");
	}


}

void SpoofingMenu::Init() {
	setParentSubmenu<ProtectionMenu>();
	setName("Spoofing", true, true);

	addOption(ToggleOption("Ped location ghost mode")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.spoofpedlocation)
		.addTooltip("Once enabled you peds location wont sync/update - only death will reset the last location").addTranslation());

	addOption(BreakOption("R* ID Spoof"));

	addOption(ButtonOption("")
		.addOnUpdate([](ButtonOption* option) {
		static int TIMER, offset;
		static char name[50];
		vaBuff(name, 50, "Selected id for spoof: %i", Backend::m_spoofingRID);
		option->setName(name);
	})
		.addTooltip("This displays what you have inputted to use for spoofing"));

	addOption(ToggleOption("Enable R* ID spoof")
		.addToggle(NetEvent::vars.rockstarid)
		.addTooltip("Enable R* ID spoofing - once enabled and id is set change session").addTranslation());

	addOption(ButtonOption("Set manual R* ID")
		.addFunction(SpoofRockstar).addTranslation()
		.addTooltip("Set the r* id manually")
		.addRequirement([] { return GetAuth()->IsVIP(); }));

	addOption(ButtonOption("Set random R* ID")
		.addFunction(RandomSpoofRockstar).addTranslation()
		.addTooltip("Set the r* id to a random number"));

	addOption(ButtonOption("Reset Spoofed R* ID")
		.addFunction(ResetSpoof)
		.addTooltip("Reset your spoofed rockstar ID to your original one")
		.addHotkey().addTranslation());

	addOption(BreakOption("R* ID Preset Profile Sets"));

	addOption(ButtonOption("Profile: MrBossFTW")
		.addFunction(MrBossSpoofRockstar).addTranslation()
		.addTooltip("This will spoof your r* id and name to match MrBossFTW"));

	addOption(ButtonOption("Profile: NoughtPointFourLIVE")
		.addFunction(NoughtPointPCRandomSpoofRockstar).addTranslation()
		.addTooltip("This will spoof your r* id and name to match NoughtPointFourLIVE"));

	addOption(ButtonOption("Profile: Kwebbelkop")
		.addFunction(KwebbelkopRandomSpoofRockstar).addTranslation()
		.addTooltip("This will spoof your r* id and name to match Kwebbelkop"));

	addOption(BreakOption("R* ID Custom Profile Sets"));

	addOption(ButtonOption("")
		.addFunction(CustomName)
		.addOnUpdate([](ButtonOption* option) {
		static int TIMER, offset;
		static char name[50];
		vaBuff(name, 50, "Name for spoof: %s", vars.customname.c_str());
		option->setName(name);
	})
		.addTooltip("This will display the name you will use for spoof profile"));

	addOption(ButtonOption("")
		.addFunction(CustomID)
		.addOnUpdate([](ButtonOption* option) {
		static int TIMER, offset;
		static char name[50];
		vaBuff(name, 50, "Id for spoof: %i", vars.customid);
		option->setName(name);
	})
		.addTooltip("This will display the r* id you will use for spoof profile"));

	m_RIDNameOption = addOption(ButtonOption("Enter profile name: ")
		.addFunction([this] {
		GetMenuInput()->AddToQueue([] {
			string input;
			if (GetMenuInput()->Text("Profile", input, 2, 50)) {
				vars.RIDprofileName = input.c_str();
			}
		});
	})
		.addTooltip("Input the name for the profile you're going to save")
		.addTranslation());

	addOption(ButtonOption("Save profile")
		.addFunction([this] {
		char* path = va("%s%s.json", GetConfig()->GetRIDSpoofPath(), vars.RIDprofileName.c_str());
		ofstream file(path);
		json j;
		j["name"] = (string)vars.customname;
		j["rid"] = (int)vars.customid;
		file << setw(4) << j;
		file.close();
	})
		.addHotkey()
		.addTooltip("Save created profile above"));

	addOption(BreakOption());

	/*addOption(ButtonOption("Set profile")
		.addFunction(SetProfile)
		.addTooltip("")
		.addHotkey().addTranslation());*/
}

/*Update once when submenu is opened*/
void SpoofingMenu::UpdateOnce() {}

/*Update while submenu is active*/
void SpoofingMenu::Update() {
	m_RIDNameOption->setName(va("Enter profile name: %s", vars.RIDprofileName.c_str()));

	static int TIMER;
	static bool update = true;
	Utils::DoTimedFunction(&TIMER, 250, [] {update = true; });
	if (update) {
		clearOptionsOffset(17);
		for (const auto & entry : std::experimental::filesystem::directory_iterator(GetConfig()->GetRIDSpoofPath())) {
			auto const pos = entry.path().filename().string().find_last_of('.');
			string option = entry.path().filename().string().substr(0, pos);

			char* path = va("%s%s.json", GetConfig()->GetRIDSpoofPath(), option.c_str());
			fstream file(path);
			json j;
			j = json::parse(file);

			addOption(ButtonOption(va("Profile: %s", option.c_str()))
				.addFunction([=] {
				char* path = va("%s%s.json", GetConfig()->GetRIDSpoofPath(), option.c_str());
				fstream file(path);
				json j;
				j = json::parse(file);
				vars.customname = (j["name"].get<string>().c_str());
				vars.customid = (int)j["rid"];
				SetProfile();
			})
				.addTooltip(va("Name: %s \nR* ID: %i \nLoad the selected profile!", j["name"].get<string>().c_str(), j["rid"].get<int>())));

		}
		update = false;
	}

}

/*Background update*/
void SpoofingMenu::FeatureUpdate() {
	/*static int TIMER;
	static bool update = true;
	Utils::DoTimedFunction(&TIMER, 1000, [] {update = true; });
	if (update) {
		clearOptionsOffset(17);
		for (const auto & entry : std::experimental::filesystem::directory_iterator(GetConfig()->GetRIDSpoofPath())) {
			auto const pos = entry.path().filename().string().find_last_of('.');
			string option = entry.path().filename().string().substr(0, pos);

			addOption(ButtonOption(va("Profile: %s", option.c_str()))
				.addFunction([=] {
				char* path = va("%s%s.json", GetConfig()->GetRIDSpoofPath(), option);
				fstream file(path);
				json j;
				j = json::parse(file);
				vars.customname = (j["name"].get<string>().c_str());
				vars.customid = (int)j["rid"];
				SetProfile();
			})
				.addTooltip("Load the selected profile!"));

		}
		update = false;
	}*/
}

/*Singleton*/
SpoofingMenu* _instance;
SpoofingMenu* SpoofingMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new SpoofingMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
SpoofingMenu::~SpoofingMenu() { delete _instance; }