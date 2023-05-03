#include "stdafx.h"
#include "infoSpooferProfilesMenu.h"
#include "..\infoSpooferMenu.h"
#include "..\nameMenu.h"

using namespace InfoSpooferProfilesMenuVars;

namespace InfoSpooferProfilesMenuVars {
	
}

void InfoSpooferProfilesMenu::Init() {
	setParentSubmenu<InfoSpooferMenu>();
	setName("Spoof information", true, true);
	addOption(ButtonOption("~c~Profiles~s~"));
}

/*Update once when submenu is opened*/
void InfoSpooferProfilesMenu::UpdateOnce() {}

/*Update while submenu is active*/
void InfoSpooferProfilesMenu::Update() {
	static int TIMER;
	static bool update = true;
	Utils::DoTimedFunction(&TIMER, 250, [] {update = true; });
	if (update) {
		clearOptionsOffset(1);
		for (const auto & entry : std::experimental::filesystem::directory_iterator(GetConfig()->GetProfilesPath())) {
			auto const pos = entry.path().filename().string().find_last_of('.');
			string option = entry.path().filename().string().substr(0, pos);

			addOption(ButtonOption(option.c_str())
				.addFunction([=] {
				char* path = va("%s%s.json", GetConfig()->GetProfilesPath(), option);
				fstream file(path);
				json j;
				j = json::parse(file);
				NameMenuVars::setName(j["name"].get<string>().c_str());
				InfoSpooferMenuVars::vars.spoofranknum = j["rank"];
				InfoSpooferMenuVars::vars.spoofrankt = true;
				InfoSpooferMenuVars::vars.spoofcashnum = j["wallet"];
				InfoSpooferMenuVars::vars.spoofcasht = true;
				InfoSpooferMenuVars::vars.spoofkillsnum = j["kills"];
				InfoSpooferMenuVars::vars.spoofkillst = true;
			})
			.addTooltip("Load the selected profile!"));

		}
		update = false;
	}
	
}

/*Background update*/
void InfoSpooferProfilesMenu::FeatureUpdate() {

}

/*Singleton*/
InfoSpooferProfilesMenu* _instance;
InfoSpooferProfilesMenu* InfoSpooferProfilesMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new InfoSpooferProfilesMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
InfoSpooferProfilesMenu::~InfoSpooferProfilesMenu() { delete _instance; }