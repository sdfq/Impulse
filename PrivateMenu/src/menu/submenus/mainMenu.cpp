#include "stdafx.h"
#include "menu/submenus/mainMenu.h"
#include "main/localMenu.h"
#include "main/weaponMenu.h"
#include "main/vehicleMenu.h"
#include "main/spawnMenu.h"
#include "main/TeleportMenu.h"
#include "main/worldMenu.h"
#include "main/sessionMenu.h"
#include "main/protectionMenu.h"
#include "main/recoveryMenu.h"
#include "main/miscMenu.h"
#include "main/settingsMenu.h"
#include "main/developerMenu.h"
#include "main/testerMenu.h"
#include "main/searchResultsMenu.h"
#include "main/shv/shvMenu.h"
#include "main/model swapping/swappingPresetsMenu.h"
using namespace MainMenuVars;

namespace MainMenuVars {
	void SearchOptions(string& str) {
		SearchResultsMenu::GetInstance()->clearOptions();
		bool foundSomething = false;
		for (auto& sub : GetSubmenuHandler()->GetSubmenus()) {
			if (!sub->m_canBeSearched) continue;
			vector<shared_ptr<Option>> tempOptions;
			for (auto& op : sub->getOptions()) {
				if (op->isVisible()) {
					string opName = toLower(op->getName().Get());
					if (opName.find(str) != string::npos) {
						if (!op->isBreak()) {
							tempOptions.push_back(op);
							foundSomething = true;
						}
					}
				}
			}
			if (tempOptions.size() > 0) {
				SearchResultsMenu::GetInstance()->addOption(BreakOption(sub->getName().Get()));
				for (auto& op : tempOptions) {
					SearchResultsMenu::GetInstance()->addOption(op);
				}
			}
		}
		if (foundSomething) GetSubmenuHandler()->SetSubmenu(SearchResultsMenu::GetInstance());
		else GetRenderer()->NotifyBottom("No results found");
	}
}

void MainMenu::Init() {
	setName("Home", true, true);

	addOption(SubmenuOption("Player")
		.addSubmenu<LocalMenu>().addHotkey().addTranslation()
		.addTooltip("Player options"));

	addOption(SubmenuOption("Weapon")
		.addSubmenu<WeaponMenu>().addHotkey().addTranslation()
		.addTooltip("Weapon options"));

	addOption(SubmenuOption("Vehicle")
		.addSubmenu<VehicleMenu>().addHotkey().addTranslation()
		.addTooltip("Vehicle options"));

	addOption(SubmenuOption("Spawn")
		.addSubmenu<SpawnMenu>().addHotkey().addTranslation()
		.addTooltip("Spawn options"));

	addOption(SubmenuOption("Teleport")
		.addSubmenu<TeleportMenu>().addHotkey().addTranslation()
		.addTooltip("Teleport options"));

	addOption(SubmenuOption("World")
		.addSubmenu<WorldMenu>().addHotkey().addTranslation()
		.addTooltip("World options"));

	addOption(SubmenuOption("Session")
		.addSubmenu<SessionMenu>().addHotkey().addTranslation()
		.addTooltip("Session options"));

	addOption(SubmenuOption("Protection")
		.addSubmenu<ProtectionMenu>().addHotkey().addTranslation()
		.addTooltip("Protection options"));

	addOption(SubmenuOption("Recovery")
		.addSubmenu<RecoveryMenu>().addHotkey().addTranslation()
		.addTooltip("Recovery options [Risky]"));

	addOption(SubmenuOption("ScriptHookV")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addSubmenu<SHVMenu>().addHotkey().addTranslation()
		.addTooltip("ScriptHookV options"));

	/*addOption(ButtonOption("~c~ScriptHookV~s~")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addTooltip("Disabled")
	);*/

	addOption(SubmenuOption("Model swapping")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addSubmenu<SwapPresetsMenu>().addHotkey().addTranslation()
		.addTooltip("Swap ingame models"));

	addOption(SubmenuOption("Miscellaneous")
		.addSubmenu<MiscMenu>().addHotkey().addTranslation()
		.addTooltip("Miscellaneous options"));

	addOption(SubmenuOption("Settings")
		.addSubmenu<SettingsMenu>().addHotkey().addTranslation()
		.addTooltip("Settings options"));

	addOption(ButtonOption("Search options")
		.addFunction([] { GetMenuInput()->AddToQueue([] {string temp; if (GetMenuInput()->Text("Option name", temp, 2, 15)) SearchOptions(toLower(temp)); }); })
		.addHotkey().addTooltip("Search through the menus functions by name"));

	addOption(SubmenuOption("Staff/Testing")
		.addRequirement([] { return GetAuth()->IsStaff(); })
		.addSubmenu<TesterMenu>()
		.addTooltip("Open the staff/testing only options"));

	/*addOption(ButtonOption("Register Broadcast")
		.addFunction([] {
		void* address = &Backend::GetGlobalPtr()[0x41272 >> 18 & 0x3F][0x41272 & 0x3FFFF];
		NETWORK::NetworkRegisterHostBroadcastVariables((uint64_t*)address, 1);
		LOG_PRINT("0x%llx", address);
	}));

	addOption(ButtonOption("Set Test Broadcast Global")
		.addFunction([] {
		Global(0x41272).As<bool>() = true;
	}));

	addOption(ButtonOption("Nigger")	
		.addFunction([] {
		LOG_PRINT("0x%llx", (uint64_t)Natives::getNativeHandlerCache(0x3E9B2F01C50DF595) - (uint64_t)GetModuleHandleA(0));
		}));*/

#ifdef HARD_DEV
	addOption(SubmenuOption("Developer")
		.addSubmenu<DeveloperMenu>()
		.addTooltip("Open the dank dev options"));
#endif
}

void MainMenu::UpdateOnce() {

}

void MainMenu::Update() {
	//GetRenderer()->DrawString("MAIN", GetRenderer()->m_posX - GetRenderer()->m_width / 2 + 0.006f, GetRenderer()->m_posY - 0.0415f, 7, 1, GetRenderer()->m_cTitle, true);
	//GetRenderer()->DrawString(GetMenu()->m_version, GetRenderer()->m_posX - GetRenderer()->m_width / 2 + 0.006f, GetRenderer()->m_posY + 0.0085, 4, 0.35f, GetRenderer()->m_cTitle, true);
	//GetRenderer()->DrawString(va("~c~developer", GetAuth()->m_subscription.days, GetAuth()->m_subscription.hours), GetRenderer()->m_posX - GetRenderer()->m_width / 2 + 0.026f, GetRenderer()->m_posY + 0.0085, 4, 0.35f, GetRenderer()->m_cTitle, true);
}

void MainMenu::FeatureUpdate() {}

/*Singleton*/
MainMenu* _instance;
MainMenu* MainMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new MainMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
MainMenu::~MainMenu() { delete _instance; }