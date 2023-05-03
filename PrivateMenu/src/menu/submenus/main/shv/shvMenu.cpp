#include "stdafx.h"
#include "shvMenu.h"
#include "../../mainMenu.h"

using namespace SHVMenuVars;

namespace SHVMenuVars {
	Vars vars;

	vector<string> m_pluginFiles;
	vector<HMODULE> m_pluginHandles;

	void LoadASI(string fileName) {
		auto lib = LoadLibraryA(va("%s/%s.asi", GetConfig()->GetPluginsPath(), fileName.c_str()));
		m_pluginHandles.push_back(lib);
	}
}

void SHVMenu::Init() {
	setParentSubmenu<MainMenu>();
	setName("ScriptHookV", true, true);

	addOption(ButtonOption("Unload all scripts")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addTooltip("This will unload all currently enabled scripts (to re-enable unloaded restart game)")
		.addFunction([] {  
			for (auto& penis : m_pluginHandles) {
				ScriptHookV::scriptUnregister(penis);
			}
		}));

	addOption(BreakOption("Scripts")
		.addTranslation());
}

/*Update once when submenu is opened*/
void SHVMenu::UpdateOnce() {
	clearOptionsOffset(2);

	GetConfig()->GetFilesFromDirectory(m_pluginFiles, GetConfig()->GetPluginsPath(), ".asi");

	if (!m_pluginFiles.empty()) {
		for (string& hack : m_pluginFiles) {
			addOption(ButtonOption(hack.c_str())
				.addRequirement([] { return GetAuth()->IsVIP(); })
				.addFunction([&] {
					LoadASI(hack.c_str());
					GetRenderer()->NotifyMap("~y~Plugin Loaded...\n~g~Read controls in text document provided with scripthook plugins download");
				})
				.addTooltip(hack.c_str()));
		}
	}
}

/*Update while submenu is active*/
void SHVMenu::Update() {}

/*Background update*/
void SHVMenu::FeatureUpdate() {}

/*Singleton*/
SHVMenu* _instance;
SHVMenu* SHVMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new SHVMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
SHVMenu::~SHVMenu() { delete _instance; }