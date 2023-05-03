#include "stdafx.h"
#include "infoSpooferMenu.h"
#include "..\sessionMenu.h"
#include "info spoofer/infoSpooferProfilesMenu.h"
#include "nameMenu.h"

using namespace InfoSpooferMenuVars;

namespace InfoSpooferMenuVars {
	Vars vars;
	shared_ptr<ButtonOption> m_profNameOption = nullptr;

	template <typename TYPE>
	TYPE SetPlayerStat(Player player, int stat, TYPE value) {
		return Global(Globals::PLAYER_BASE).At(player, Globals::PLAYER_PADDING).At(stat).As<TYPE>() = value;
	}

	void SpoofRank() {
		static int TIMER;
		Utils::DoTimedFunction(&TIMER, 200, [] { SetPlayerStat(GetLocalPlayer().m_id, 217, vars.spoofranknum); });
	}

	void SpoofCash() {
		static int TIMER;
		Utils::DoTimedFunction(&TIMER, 200, [] { SetPlayerStat(GetLocalPlayer().m_id, 214, vars.spoofcashnum); });
	}

	void SpoofKills() {
		static int TIMER;
		Utils::DoTimedFunction(&TIMER, 200, [] { SetPlayerStat(GetLocalPlayer().m_id, 239, vars.spoofkillsnum); });
	}

	void SpoofDeaths() {
		static int TIMER;
		Utils::DoTimedFunction(&TIMER, 200, [] { SetPlayerStat(GetLocalPlayer().m_id, 240, vars.spoofdeathsnum); });
	}

	void SpoofKd() {
		SetPlayerStat(GetLocalPlayer().m_id, 237, vars.spoofkdnum);
	}
}

void InfoSpooferMenu::Init() {
	setParentSubmenu<SessionMenu>();
	setName("Spoof information", true, true);

	addOption(SubmenuOption("Info Spoofer Profiles")
		.addSubmenu<InfoSpooferProfilesMenu>().addHotkey()
		.addTooltip("Choose a previously saved profile!").addTranslation());

	addOption(NumberOption<int>(SCROLL, "Rank input")
		.addNumber(vars.spoofranknum, "%i", 10).addMin(-2147483647).addMax(2147483647)
		.addTranslation()
		.addTooltip("Edit the rank of choice to spoof to"));

	addOption(ToggleOption("Set rank")
		.addToggle(vars.spoofrankt)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Set the rank that you would like to spoof too"));

	addOption(NumberOption<int>(SCROLL, "Wallet input")
		.addNumber(vars.spoofcashnum, "%i", 10).addMin(-2147483647).addMax(2147483647)
		.addTranslation()
		.addTooltip("Edit the wallet of choice to spoof to"));

	addOption(ToggleOption("Set wallet")
		.addToggle(vars.spoofcasht)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Set the wallet that you would like to spoof too"));

	addOption(NumberOption<int>(SCROLL, "Kills input")
		.addNumber(vars.spoofkillsnum, "%i", 10).addMin(-2147483647).addMax(2147483647)
		.addTranslation()
		.addTooltip("Edit the kills of choice to spoof to"));

	addOption(ToggleOption("Set kills")
		.addToggle(vars.spoofkillst)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Set the kills that you would like to spoof too"));

	addOption(NumberOption<int>(SCROLL, "Deaths input")
		.addNumber(vars.spoofdeathsnum, "%i", 10).addMin(-2147483647).addMax(2147483647)
		.addTranslation()
		.addTooltip("Edit the deaths of choice to spoof to"));

	addOption(ToggleOption("Set deaths")
		.addToggle(vars.spoofdeathst)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Set the deaths that you would like to spoof too"));

	addOption(NumberOption<float>(SCROLL, "K/D input")
		.addNumber(vars.spoofkdnum, "%.1f", 1).addMin(-2147483647.0f).addMax(2147483647.0f)
		.addTranslation()
		.addTooltip("Edit the K/D of choice to spoof to"));

	addOption(ToggleOption("Set K/D")
		.addToggle(vars.spoofkdt)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Set the K/D that you would like to spoof too"));

	m_profNameOption = addOption(ButtonOption("Enter profile name: ")
		.addFunction([this] {
		GetMenuInput()->AddToQueue([] {
			string input;
			if (GetMenuInput()->Text("Profile", input, 2, 50)) {
				vars.profileName = input.c_str();
			}
		});
	})
	.addTooltip("Input the name for the profile you're going to save!")
	.addTranslation());

	addOption(ButtonOption("Save profile!")
		.addFunction([this] {
		char* path = va("%s%s.json", GetConfig()->GetProfilesPath(), vars.profileName.c_str());
		ofstream file(path);
		json j;
		j["name"] = NameMenuVars::vars.name;
		j["rank"] = (int)vars.spoofranknum;
		j["wallet"] = (int)vars.spoofcashnum;
		j["kills"] = (int)vars.spoofkillsnum;
		file << setw(4) << j;
		file.close();
	})
		.addHotkey()
		.addTooltip("Save the profile in the profiles folder with the name you gave it!"));

	addOption(BreakOption("Random choice spoofs").addTranslation());


	addOption(ToggleOption("Random rank spoof spam")
		.addToggle(vars.rank.spam).addTranslation().addHotkey());

	addOption(ToggleOption("Random wallet spoof spam")
		.addToggle(vars.wallet.spam).addTranslation().addHotkey());

	addOption(ToggleOption("Random K/D ratio spoof spam")
		.addToggle(vars.kdratio.spam).addTranslation().addHotkey());
}

/*Update once when submenu is opened*/
void InfoSpooferMenu::UpdateOnce() {}

/*Update while submenu is active*/
void InfoSpooferMenu::Update() {
	m_profNameOption->setName(va("Enter profile name: %s", vars.profileName.c_str()));
}

/*Background update*/
void InfoSpooferMenu::FeatureUpdate() {

	if (vars.spoofrankt) SpoofRank();
	if (vars.spoofcasht) SpoofCash();
	if (vars.spoofkillst) SpoofKills();
	if (vars.spoofdeathst) SpoofDeaths();
	if (vars.spoofkdt) SpoofKd();

	static int TIMER;
	static bool update = true;
	Utils::DoTimedFunction(&TIMER, 250, [] {update = true; });
	if (update) {
		if (vars.rank.spam) SetPlayerStat(GetLocalPlayer().m_id, 217, MISC::GetRandomIntInRange(1, 8000));
		else if (vars.rank.changed) SetPlayerStat(GetLocalPlayer().m_id, 217, vars.rank.value);

		if (vars.wallet.spam) SetPlayerStat(GetLocalPlayer().m_id, 214, MISC::GetRandomIntInRange(1, 2147483647));
		else if (vars.wallet.changed) SetPlayerStat(GetLocalPlayer().m_id, 214, vars.wallet.value);

		/*if (vars.deaths.spam) SetPlayerStat(GetLocalPlayer().m_id, 240, MISC::GetRandomIntInRange(1, 2147483647));
		else if (vars.deaths.changed) SetPlayerStat(GetLocalPlayer().m_id, 240, vars.deaths.value);

		if (vars.kills.spam) SetPlayerStat(GetLocalPlayer().m_id, 239, MISC::GetRandomIntInRange(1, 2147483647));
		else if (vars.kills.changed) SetPlayerStat(GetLocalPlayer().m_id, 239, vars.kills.value);*/

		if (vars.kdratio.spam) SetPlayerStat(GetLocalPlayer().m_id, 237, MISC::GetRandomFloatInRange(0.01f, 100.00f));
		else if (vars.kdratio.changed) SetPlayerStat(GetLocalPlayer().m_id, 237, vars.kdratio.value);
		update = false;
	}
}

/*Singleton*/
InfoSpooferMenu* _instance;
InfoSpooferMenu* InfoSpooferMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new InfoSpooferMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
InfoSpooferMenu::~InfoSpooferMenu() { delete _instance; }