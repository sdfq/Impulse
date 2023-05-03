#include "stdafx.h"
#include "KDMenu.h"
#include "../recoveryMenu.h"

using namespace KDMenuVars;

namespace KDMenuVars {
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

void KDMenu::Init() {
	setParentSubmenu<RecoveryMenu>();
	setName("KD", true, true);

	addOption(NumberOption<int>(SCROLL, "Set kills")
		.addNumber(vars.kills, "%d", 10).addMin(0).addMax(INT_MAX)
		.addOnUpdate([] {vars.kills = Stats::GetStatI("KILLS_PLAYERS"); })
		.addFunction([] {Stats::SetStatI("KILLS_PLAYERS", vars.kills, false); })
		.addHotkey().addTranslation()
		.addTooltip("Set kills [custom input wont work for this option]"));

	addOption(NumberOption<int>(SCROLL, "Set deaths")
		.addNumber(vars.deaths, "%d", 10).addMin(0).addMax(INT_MAX)
		.addOnUpdate([] {vars.deaths = Stats::GetStatI("DEATHS_PLAYER"); })
		.addFunction([] {Stats::SetStatI("DEATHS_PLAYER", vars.deaths, false); })
		.addHotkey().addTranslation()
		.addTooltip("Set deaths [custom input wont work for this option]"));

	addOption(NumberOption<int>(SCROLL, "Set online kills")
		.addNumber(vars.okills, "%d", 10).addMin(0).addMax(INT_MAX)
		.addOnUpdate([] {StatReadType(eStatSetTypes_Int, "MPPLY_KILLS_PLAYERS", &vars.okills); })
		.addFunction([] {StatSetType(eStatSetTypes_Int, "MPPLY_KILLS_PLAYERS", vars.okills); })
		.addHotkey().addTranslation()
		.addTooltip("Set online kills [custom input wont work for this option]"));

	addOption(NumberOption<int>(SCROLL, "Set online deaths")
		.addNumber(vars.odeaths, "%d", 10).addMin(0).addMax(INT_MAX)
		.addOnUpdate([] {StatReadType(eStatSetTypes_Int, "MPPLY_DEATHS_PLAYER", &vars.odeaths); })
		.addFunction([] {StatSetType(eStatSetTypes_Int, "MPPLY_DEATHS_PLAYER", vars.odeaths); })
		.addHotkey().addTranslation()
		.addTooltip("Set online deaths [custom input wont work for this option]"));

	addOption(NumberOption<int>(SCROLL, "Set shots")
		.addNumber(vars.shots, "%d", 10).addMin(0).addMax(INT_MAX)
		.addOnUpdate([] {vars.shots = Stats::GetStatI("SHOTS"); })
		.addFunction([] {Stats::SetStatI("SHOTS", vars.shots, false); })
		.addHotkey().addTranslation()
		.addTooltip("Set shots [custom input wont work for this option]"));

	addOption(NumberOption<int>(SCROLL, "Set headshots")
		.addNumber(vars.headshots, "%d", 10).addMin(0).addMax(INT_MAX)
		.addOnUpdate([] {vars.headshots = Stats::GetStatI("HEADSHOTS"); })
		.addFunction([] {Stats::SetStatI("HEADSHOTS", vars.headshots, false); })
		.addHotkey().addTranslation()
		.addTooltip("Set headshots [custom input wont work for this option]"));

	addOption(NumberOption<int>(SCROLL, "Set hits")
		.addNumber(vars.hits, "%d", 10).addMin(0).addMax(INT_MAX)
		.addOnUpdate([] {vars.hits, Stats::GetStatI("HITS"); })
		.addFunction([] {Stats::SetStatI("HITS", vars.hits, false); })
		.addHotkey().addTranslation()
		.addTooltip("Set hits [custom input wont work for this option]"));
}

/*Update once when submenu is opened*/
void KDMenu::UpdateOnce() {}

/*Update while submenu is active*/
void KDMenu::Update() {}

/*Background update*/
void KDMenu::FeatureUpdate() {}

/*Singleton*/
KDMenu* _instance;
KDMenu* KDMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new KDMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
KDMenu::~KDMenu() { delete _instance; }