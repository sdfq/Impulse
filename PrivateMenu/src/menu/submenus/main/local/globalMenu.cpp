#include "stdafx.h"
#include "globalMenu.h"
#include "../localMenu.h"

using namespace GlobalMenuVars;

namespace GlobalMenuVars {
	Vars vars;
	using namespace Globals;

	void OTR(bool toggle) {
		if (NETWORK::NetworkIsSessionActive()) {
			if (toggle) {
				Global(OTR_BASE).At(GetLocalPlayer().m_id, OTR_PADDING).At(OTR_OFFSET).As<int>() = 1;
				Global(EFFECT_TIME_BASE).At(TIME_OFFSET).As<int>() = NETWORK::GetNetworkTime();
			} else {
				Global(OTR_BASE).At(GetLocalPlayer().m_id, OTR_PADDING).At(OTR_OFFSET).As<int>() = 0;
			}
		}
	}

	/*void NoIdleKick() {
		Global(NOIDLEKICK).At(1165).As<int>() = -1;
		Global(NOIDLEKICK).At(1149).As<int>() = -1;
	}*/

	void BlindEye(bool toggle) {
		if (NETWORK::NetworkIsSessionActive()) {
			if (toggle) {
				Global(TIME_BASE).At(BLINDEYEOFFSET1).As<int>() = 5;
				Global(TIME_BASE).At(BLINDEYEOFFSET2).As<int>() = NETWORK::GetNetworkTime();
			} else {
				Global(TIME_BASE).At(BLINDEYEOFFSET1).As<int>() = 0;
			}
		}
	}

	void Testosterone() {
		Global(EFFECT_TIME_BASE).At(TESTOSTERONE_OFFSET).As<bool>() = true;
	}

	void TestosteroneL() {
		static int TIMER;
		Utils::DoTimedFunction(&TIMER, 61500, [] {
		Global(EFFECT_TIME_BASE).At(TESTOSTERONE_OFFSET).As<bool>() = true;
		});
	}

	void NoOrbitalCooldown() {
		static int TIMER;
		Utils::DoTimedFunction(&TIMER, 5000, [] {Stats::SetStatI("ORBITAL_CANNON_COOLDOWN", 0, 0); });
	}

	template <typename TYPE>
	TYPE SetPlayerStat(Player player, int stat, TYPE value) {
		return Global(Globals::PLAYER_BASE).At(player, Globals::PLAYER_PADDING).At(stat).As<TYPE>() = value;
	}

	/*void SpoofRank() {
		static int TIMER;
		Utils::DoTimedFunction(&TIMER, 500, [] {SetPlayerStat<int>(GetLocalPlayer().m_id, 217, vars.spoofranknum); });
	}*/

	/*void SpoofCash() {
		static int TIMER;
		Utils::DoTimedFunction(&TIMER, 500, [] {SetPlayerStat<int>(GetLocalPlayer().m_id, 214, vars.spoofcashnum); });
	}*/

}

void GlobalMenu::Init() {
	setParentSubmenu<LocalMenu>();
	setName("Globals", true, true);

	addOption(ToggleOption("Off the radar")
		.addToggle(vars.otr).addTranslation()
		.addFunction([] {OTR(vars.otr); })
		.addHotkey().canBeSaved()
		.addTooltip("Invisible on the radar"));

	addOption(ToggleOption("Cops turn blind eye")
		.addToggle(vars.blindeye).addTranslation()
		.addFunction([] {BlindEye(vars.blindeye); })
		.addHotkey().canBeSaved()
		.addTooltip("Cops turn blind eye"));

	addOption(ButtonOption("Bullshark testosterone")
		.addFunction([] { Testosterone(); })
		.addTranslation().addHotkey()
		.addTooltip("Get bullshark estosterone"));

	addOption(ToggleOption("Loop bullshark testosterone")
		.addToggle(vars.testosteronel).addTranslation()
		.addFunction([] {Testosterone(); })
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Bullshark testosterone"));

	addOption(ToggleOption("No orbital cannon cooldown")
		.addToggle(vars.noorbitalcooldown)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("No orbital cannon cooldown")
		.addRequirement([] { return GetAuth()->IsVIP(); }));

	//addOption(BreakOption("Spoof Rank").addTranslation());

	/*addOption(NumberOption<int>(SCROLL, "Rank input")
		.addNumber(vars.spoofranknum, "%i", 10).addMin(-2147483647).addMax(2147483647)
		.addTranslation()
		.addTooltip("Edit the input for the above option"));

	addOption(ToggleOption("Set rank")
		.addToggle(vars.spoofrank)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Set the rank that you would like to spoof too"));*/

	/*addOption(BreakOption("Spoof Cash").addTranslation());

	addOption(NumberOption<int>(SCROLL, "Cash input")
		.addNumber(vars.spoofcashnum, "%llu", 10).addMin(-2147483647).addMax(2147483647)
		.addTranslation()
		.addTooltip("Edit the input for the above option"));

	addOption(ToggleOption("Set cash")
		.addToggle(vars.spoofcash)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Set the cash that you would like to spoof too"));*/
}

/*Update once when submenu is opened*/
void GlobalMenu::UpdateOnce() {}

/*Update while submenu is active*/
void GlobalMenu::Update() {}

/*Background update*/
void GlobalMenu::FeatureUpdate() {
	if (vars.otr) OTR(true);
	//if (vars.noidlekick) NoIdleKick();
	if (vars.blindeye) BlindEye(true);
	if (vars.testosterone) Testosterone();
	if (vars.noorbitalcooldown)NoOrbitalCooldown();
	//if (vars.spoofrank)SpoofRank();
	//if (vars.spoofcash)SpoofCash();
	if (vars.testosteronel) TestosteroneL();
}

/*Singleton*/
GlobalMenu* _instance;
GlobalMenu* GlobalMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new GlobalMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
GlobalMenu::~GlobalMenu() { delete _instance; }