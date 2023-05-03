#include "stdafx.h"
#include "statsMenu.h"
#include "../recoveryMenu.h"

using namespace StatsMenuVars;

namespace StatsMenuVars {
	Vars vars;

	char cprintfBuffer[0x1000];
	char* cprintf(const char* fmt, ...) {
		memset(cprintfBuffer, 0, 0x1000);
		va_list ap;
		va_start(ap, fmt);
		vsprintf(cprintfBuffer, fmt, ap);
		va_end(ap);
		return cprintfBuffer;
	}

	enum eStatSetTypes {
		eStatSetTypes_Int,
		eStatSetTypes_Bool,
		eStatSetTypes_Float
	};

	template<typename ValueType>
	void StatSetType(eStatSetTypes type, string stat, ValueType value) {
		bool useChar = true;
		int currentChar;

		STATS::StatGetInt(0x2F2F120F, &currentChar, -1);

		char* currentCharacter = (currentChar ? "MP1_" : "MP0_");

		if (strstr(stat.c_str(), "MPPLY") != NULL) {
			useChar = false;
		}

		switch (type) {
		case eStatSetTypes_Int:
			STATS::StatSetInt(MISC::GetHashKey(cprintf("%s%s", useChar ? currentCharacter : "", stat.c_str())), value, 1);
			break;
		case eStatSetTypes_Bool:
			STATS::StatSetInt(MISC::GetHashKey(cprintf("%s%s", useChar ? currentCharacter : "", stat.c_str())), value, 1);
			break;
		case eStatSetTypes_Float:
			STATS::StatSetInt(MISC::GetHashKey(cprintf("%s%s", useChar ? currentCharacter : "", stat.c_str())), value, 1);
			break;
		}
	}

	template<typename ValueType>
	void StatReadType(eStatSetTypes type, string stat, ValueType* value) {
		bool useChar = true;
		int currentChar;

		STATS::StatGetInt(0x2F2F120F, &currentChar, -1);

		char* currentCharacter = (currentChar ? "MP1_" : "MP0_");

		if (strstr(stat.c_str(), "MPPLY") != NULL) {
			useChar = false;
		}

		switch (type) {
		case eStatSetTypes_Int:
			STATS::StatGetInt(MISC::GetHashKey(cprintf("%s%s", useChar ? currentCharacter : "", stat.c_str())), (int*)value, -1);
			break;
		case eStatSetTypes_Bool:
			STATS::StatGetInt(MISC::GetHashKey(cprintf("%s%s", useChar ? currentCharacter : "", stat.c_str())), (BOOL*)value, -1);
			break;
		}
	}

}

void StatsMenu::Init() {
	setParentSubmenu<RecoveryMenu>();
	setName("Stats", true, true);

	addOption(ButtonOption("Max all stats")
		.addFunction([this] {
		Stats::SetStatI("SCRIPT_INCREASE_STAM", 100, false);
		Stats::SetStatI("SCRIPT_INCREASE_STRN", 100, false);
		Stats::SetStatI("SCRIPT_INCREASE_LUNG", 100, false);
		Stats::SetStatI("SCRIPT_INCREASE_DRIV", 100, false);
		Stats::SetStatI("SCRIPT_INCREASE_FLY", 100, false);
		Stats::SetStatI("SCRIPT_INCREASE_SHO", 100, false);
		Stats::SetStatI("SCRIPT_INCREASE_STL", 100, false);
	})
		.addTooltip("Max all stats (if only maxing one then do this in an invite only)").addTranslation().addHotkey());

	addOption(ButtonOption("Max stamina")
		.addFunction([this] {
		Stats::SetStatI("SCRIPT_INCREASE_STAM", 100, false);
	})
		.addTooltip("Max stamina").addTranslation().addHotkey());

	addOption(ButtonOption("Max strength")
		.addFunction([this] {
		Stats::SetStatI("SCRIPT_INCREASE_STRN", 100, false);
	})
		.addTooltip("Max strength").addTranslation().addHotkey());

	addOption(ButtonOption("Max lung capacity")
		.addFunction([this] {
		Stats::SetStatI("SCRIPT_INCREASE_LUNG", 100, false);
	})
		.addTooltip("Max lung capacity").addTranslation().addHotkey());

	addOption(ButtonOption("Max driving")
		.addFunction([this] {
		Stats::SetStatI("SCRIPT_INCREASE_DRIV", 100, false);
	})
		.addTooltip("Max driving").addTranslation().addHotkey());

	addOption(ButtonOption("Max flying")
		.addFunction([this] {
		Stats::SetStatI("SCRIPT_INCREASE_FLY", 100, false);
	})
		.addTooltip("Max flying").addTranslation().addHotkey());

	addOption(ButtonOption("Max shooting")
		.addFunction([this] {
		Stats::SetStatI("SCRIPT_INCREASE_SHO", 100, false);
	})
		.addTooltip("Max shooting").addTranslation().addHotkey());

	addOption(ButtonOption("Max stealth")
		.addFunction([this] {
		Stats::SetStatI("SCRIPT_INCREASE_STL", 100, false);
	})
		.addTooltip("Max stealth").addTranslation().addHotkey());

	addOption(BreakOption());

	addOption(NumberOption<int>(SCROLL, "~c~Stamina")
		.addNumber(vars.stamina, "%d", 1).addMin(0).addMax(100)
		.addOnUpdate([] {vars.stamina = Stats::GetStatI("STAMINA"); })
		.addFunction([] {Stats::SetStatI("SCRIPT_INCREASE_STAM", vars.stamina - 30, false); })
		.addHotkey().addTranslation()
		.addTooltip("Stamina"));

	addOption(NumberOption<int>(SCROLL, "~c~Strength")
		.addNumber(vars.strength, "%d", 1).addMin(0).addMax(100)
		.addOnUpdate([] {vars.strength = Stats::GetStatI("STRENGTH"); })
		.addFunction([] {Stats::SetStatI("SCRIPT_INCREASE_STRN", vars.strength - 30, false); })
		.addHotkey().addTranslation()
		.addTooltip("Strength"));

	addOption(NumberOption<int>(SCROLL, "~c~Lung capacity")
		.addNumber(vars.lungcapacity, "%d", 1).addMin(0).addMax(100)
		.addOnUpdate([] {vars.lungcapacity = Stats::GetStatI("LUNG_CAPACITY"); })
		.addFunction([] {Stats::SetStatI("SCRIPT_INCREASE_LUNG", vars.lungcapacity - 30, false); })
		.addHotkey().addTranslation()
		.addTooltip("Lung capacity"));

	addOption(NumberOption<int>(SCROLL, "~c~Driving")
		.addNumber(vars.driving, "%d", 1).addMin(0).addMax(100)
		.addOnUpdate([] {vars.driving = Stats::GetStatI("WHEELIE_ABILITY"); })
		.addFunction([] {Stats::SetStatI("SCRIPT_INCREASE_DRIV", vars.driving - 30, false); })
		.addHotkey().addTranslation()
		.addTooltip("Driving"));

	addOption(NumberOption<int>(SCROLL, "~c~Flying")
		.addNumber(vars.flying, "%d", 1).addMin(0).addMax(100)
		.addOnUpdate([] {vars.flying = Stats::GetStatI("FLYING_ABILITY"); })
		.addFunction([] {Stats::SetStatI("SCRIPT_INCREASE_FLY", vars.flying - 30, false); })
		.addHotkey().addTranslation()
		.addTooltip("Flying"));

	addOption(NumberOption<int>(SCROLL, "~c~Shooting")
		.addNumber(vars.shooting, "%d", 1).addMin(0).addMax(100)
		.addOnUpdate([] {vars.shooting = Stats::GetStatI("SHOOTING_ABILITY"); })
		.addFunction([] {Stats::SetStatI("SCRIPT_INCREASE_SHO", vars.shooting - 30, false); })
		.addHotkey().addTranslation()
		.addTooltip("Shooting"));

	addOption(NumberOption<int>(SCROLL, "~c~Stealth")
		.addNumber(vars.stealth, "%d", 1).addMin(0).addMax(100)
		.addOnUpdate([] {vars.stealth = Stats::GetStatI("STEALTH_ABILITY"); })
		.addFunction([] {Stats::SetStatI("SCRIPT_INCREASE_STL", vars.stealth - 30, false); })
		.addHotkey().addTranslation()
		.addTooltip("Stealth"));

	addOption(BreakOption("Playtime").addTranslation());

	addOption(NumberOption<int>(SCROLL, "Days")
		.addNumber(vars.days, "%d", 1).addMin(0).addMax(INT_MAX)
		.addOnUpdate([] {vars.days = Stats::GetStatI("TOTAL_PLAYING_TIME") / 86400 / 1000; })
		.addFunction([] {Stats::SetStatI("TOTAL_PLAYING_TIME", vars.days * 86400000, false); })
		.addHotkey().addTranslation()
		.addTooltip("Days"));

	addOption(NumberOption<int>(SCROLL, "Hours")
		.addNumber(vars.hours, "%d", 1).addMin(0).addMax(24)
		.addOnUpdate([] {vars.hours = Stats::GetStatI("TOTAL_PLAYING_TIME") / 3600 / 1000; })
		.addFunction([] {Stats::SetStatI("TOTAL_PLAYING_TIME", vars.hours * 3600000, false); })
		.addHotkey().addTranslation()
		.addTooltip("Hours"));

	addOption(NumberOption<int>(SCROLL, "Minutes")
		.addNumber(vars.minutes, "%d", 1).addMin(0).addMax(60)
		.addOnUpdate([] {vars.minutes = Stats::GetStatI("TOTAL_PLAYING_TIME") / 60 / 1000; })
		.addFunction([] {Stats::SetStatI("TOTAL_PLAYING_TIME", vars.minutes * 60000, false); })
		.addHotkey().addTranslation()
		.addTooltip("Minutes"));

	addOption(NumberOption<int>(SCROLL, "Seconds")
		.addNumber(vars.seconds, "%d", 1).addMin(0).addMax(60)
		.addOnUpdate([] {vars.seconds = Stats::GetStatI("TOTAL_PLAYING_TIME") / 1000; })
		.addFunction([] {Stats::SetStatI("TOTAL_PLAYING_TIME", vars.seconds * 1000, false); })
		.addHotkey().addTranslation()
		.addTooltip("Seconds"));

	addOption(BreakOption("Misc stats").addTranslation());

	addOption(NumberOption<int>(SCROLL, "Race wins")
		.addNumber(vars.racewins, "%d", 1).addMin(0).addMax(100000000)
		.addOnUpdate([] {StatReadType(eStatSetTypes_Int, "MPPLY_TOTAL_RACES_WINS", &vars.racewins); })
		.addFunction([] {StatSetType(eStatSetTypes_Int, "MPPLY_TOTAL_RACES_WINS", vars.racewins); })
		.addHotkey().addTranslation()
		.addTooltip("Race wins"));

	addOption(NumberOption<int>(SCROLL, "Race losses")
		.addNumber(vars.raceloses, "%d", 1).addMin(0).addMax(100000000)
		.addOnUpdate([] {StatReadType(eStatSetTypes_Int, "MPPLY_TOTAL_RACES_LOST", &vars.raceloses); })
		.addFunction([] {StatSetType(eStatSetTypes_Int, "MPPLY_TOTAL_RACES_LOST", vars.raceloses); })
		.addHotkey().addTranslation()
		.addTooltip("Race losses"));

	addOption(NumberOption<int>(SCROLL, "Team deathmatch wins")
		.addNumber(vars.tdwins, "%d", 1).addMin(0).addMax(100000000)
		.addOnUpdate([] {StatReadType(eStatSetTypes_Int, "MPPLY_TOTAL_TDEATHMATCH_WON", &vars.tdwins); })
		.addFunction([] {StatSetType(eStatSetTypes_Int, "MPPLY_TOTAL_TDEATHMATCH_WON", vars.tdwins); })
		.addHotkey().addTranslation()
		.addTooltip("Team deathmatch wins"));

	addOption(NumberOption<int>(SCROLL, "Team deathmatch losses")
		.addNumber(vars.tdloses, "%d", 1).addMin(0).addMax(100000000)
		.addOnUpdate([] {StatReadType(eStatSetTypes_Int, "MPPLY_TOTAL_TDEATHMATCH_LOST", &vars.tdloses); })
		.addFunction([] {StatSetType(eStatSetTypes_Int, "MPPLY_TOTAL_TDEATHMATCH_LOST", vars.tdloses); })
		.addHotkey().addTranslation()
		.addTooltip("Team deathmatch losses"));

	addOption(NumberOption<int>(SCROLL, "Deathmatch wins")
		.addNumber(vars.dmwins, "%d", 1).addMin(0).addMax(100000000)
		.addOnUpdate([] {StatReadType(eStatSetTypes_Int, "MPPLY_TOTAL_DEATHMATCH_WON", &vars.dmwins); })
		.addFunction([] {StatSetType(eStatSetTypes_Int, "MPPLY_TOTAL_DEATHMATCH_WON", vars.dmwins); })
		.addHotkey().addTranslation()
		.addTooltip("Deathmatch wins"));

	addOption(NumberOption<int>(SCROLL, "Deathmatch losses")
		.addNumber(vars.dmloses, "%d", 1).addMin(0).addMax(100000000)
		.addOnUpdate([] {StatReadType(eStatSetTypes_Int, "MPPLY_TOTAL_DEATHMATCH_LOST", &vars.dmloses); })
		.addFunction([] {StatSetType(eStatSetTypes_Int, "MPPLY_TOTAL_DEATHMATCH_LOST", vars.dmloses); })
		.addHotkey().addTranslation()
		.addTooltip("Deathmatch losses"));

}

/*Update once when submenu is opened*/
void StatsMenu::UpdateOnce() {}

/*Update while submenu is active*/
void StatsMenu::Update() {}

/*Background update*/
void StatsMenu::FeatureUpdate() {}

/*Singleton*/
StatsMenu* _instance;
StatsMenu* StatsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new StatsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
StatsMenu::~StatsMenu() { delete _instance; }