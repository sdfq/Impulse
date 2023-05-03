#include "stdafx.h"
#include "nameMenu.h"
#include "../sessionMenu.h"
#include "namePresetMenu.h"
#include "backend\backendMain.h"
#include "menu/submenus/main/sessionMenu.h"

using namespace NameMenuVars;

namespace NameMenuVars {
	enum JsonValues {
		VALUE_NAME,
		VALUE_TOGGLE
	};

	Vars vars;
	shared_ptr<ButtonOption> m_buttonOption;

	void setName(String name) {
		vector<DWORD64> vec = Backend::GetMemoryNameAddresses();
		for (int i = 0; i < vec.size(); i++) {
			strcpy((char*)vec[i], name);
		}

		vars.name = name;

		strcpy(ReClass::GetWorld()->LocalPed->PlayerInfo->Name, vars.name.c_str());
	}

	void saveName(String name) {
		GetConfig()->WriteString("General", "Name", name, GetConfig()->GetNameSavePath());
	}

	string readName() {
		return GetConfig()->ReadString("General", "Name", "File error", GetConfig()->GetNameSavePath());
	}

	bool readToggle() {
		return GetConfig()->ReadBool("General", "Load", false, GetConfig()->GetNameSavePath());
	}

	void writeToggle(bool value) {
		GetConfig()->WriteBool("General", "Load", value, GetConfig()->GetNameSavePath());
	}

	String nameColorTypes[10] = { 
		"", 
		"~r~", 
		"~b~",
		"~g~",
		"~y~", 
		"~p~", 
		"~o~", 
		"~c~", 
		"~m~", 
		"~u~"
	};

	ScrollStruct<int> nameColorTypeSelection[10] = {
		TranslationString("Normal", true), 0,
		TranslationString("Red", true), 1,
		TranslationString("Blue", true), 2,
		TranslationString("Green", true), 3,
		TranslationString("Yellow", true), 4,
		TranslationString("Purple", true), 5,
		TranslationString("Orange", true), 6,
		TranslationString("Grey", true), 7,
		TranslationString("Darker Grey", true), 8,
		TranslationString("Black", true), 9
	};

	String nameSettingTypes[4] = {
		"",
		"~bold~",
		"~italic~",
		"~n~"
	};

	ScrollStruct<int> nameSettingTypeSelection[4] = {
		TranslationString("Normal", true), 0,
		TranslationString("Bold", true), 1,
		TranslationString("Italic", true), 2,
		TranslationString("New Line", true), 3,
	};

	void ResetName() {
		vars.name = SessionMenuVars::vars.DefaultSCName;
		//LOG_PRINT("%s and %s", vars.name, SessionMenuVars::vars.DefaultSCName);
		string name = vars.name.c_str();
		NameMenuVars::setName(name.c_str());
		GetRenderer()->NotifyMap(va("Name reset to: %s \nJoin a new session to set your reset name.", name.c_str()));
	}
}

void NameMenu::Init() {
	setParentSubmenu<SessionMenu>();
	setName("Name", true, true);

	addOption(ToggleOption("Auto change name on next load")
		.addToggle(vars.saveName)
		.addFunction([=] { writeToggle(vars.saveName); })
		.addTooltip("Save your name and load it on the next startup")
		.addHotkey()
		.addTranslation());

	addOption(ButtonOption("")
		.addOnUpdate([](ButtonOption* option) {
		static char name[50];
		vaBuff(name, 50, "Saved name: %s", readName().c_str());
		option->setName(name);
	})
		.addTooltip("This displays your current saved changed name"));

	addOption(BreakOption());

	addOption(SubmenuOption("Preset names")
		.addSubmenu<NamePresetMenu>().addHotkey()
		.addTooltip("Change your name to one of our presets").addTranslation());

	addOption(ButtonOption("Reset changed name")
		.addFunction(ResetName)
		.addTooltip("Reset your changed name to your original sc name")
		.addHotkey().addTranslation());

	addOption(ButtonOption("Custom name input")
		.addFunction([this] {
			GetMenuInput()->AddToQueue([] {
				string input;
				if (GetMenuInput()->Text("Name", input, 2, 16)) {
					vars.name = input.c_str();
				}
			});
		})
		.addHotkey()
		.addTooltip("Once inputted name press set name below [using color and or settings will limit name size]").addTranslation());

	addOption(ScrollOption<int>(SCROLL, "Name color")
		.addScroll(vars.color, 0, NUMOF(nameColorTypeSelection) - 1, nameColorTypeSelection)
		.addHotkey().canBeSaved()
		.addTooltip("Set this color (this will limit the overall name size)").addTranslation());

	addOption(ScrollOption<int>(SCROLL, "Name setting")
		.addScroll(vars.setting, 0, NUMOF(nameSettingTypeSelection) - 1, nameSettingTypeSelection)
		.addHotkey().canBeSaved()
		.addTooltip("Set this setting (this will limit the overall name size)").addTranslation());

	m_buttonOption = addOption(ButtonOption("")
		.addFunction([&] { 
		NameMenuVars::setName(vars.preCompiled); GetRenderer()->NotifyMap(va("Your new name is now set, please change session or go online for this to take effect.")); 
		saveName(vars.preCompiled);
	}) //setName
		.addTooltip("Set this name (if you get an error while going online shorten name)"));
}

/*Update once when submenu is opened*/
void NameMenu::UpdateOnce() {
	if (vars.name == "") {
		vars.name = GetLocalPlayer().m_name;
		if (GetConfig()->DoesFileExist(GetConfig()->GetNameSavePath())) vars.saveName = readToggle();
	}
}

/*Update while submenu is active*/
void NameMenu::Update() {
    vaBuff(vars.preCompiled, 50, "%s%s%s", nameSettingTypes[vars.setting], nameColorTypes[vars.color], vars.name.c_str()); //IDK if this is sanitary - change if you wish. ~The dude with the huge cock
	m_buttonOption->setName(va("Set: %s", vars.preCompiled));
}

/*Background update*/
void NameMenu::FeatureUpdate() {
	static bool loadedName = false;
	vars.saveName = readToggle();
	if (!loadedName) {
		if (readToggle()) NameMenuVars::setName(readName().c_str());
		loadedName = true;
	}
}

/*Singleton*/
NameMenu* _instance;
NameMenu* NameMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new NameMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
NameMenu::~NameMenu() { delete _instance; }