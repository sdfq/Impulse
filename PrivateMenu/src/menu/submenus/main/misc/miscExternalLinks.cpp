#include "stdafx.h"
#include <ShellAPI.h>
#include "miscExternalLinks.h"
#include "../miscMenu.h"

using namespace MiscExternalLinksMenuVars;

namespace MiscExternalLinksMenuVars {
	Vars vars;
}

void MiscExternalLinksMenu::Init() {
	setParentSubmenu<MiscMenu>();
	setName("External links", false, true);

	addOption(ButtonOption("Open Impulse site")
		.addFunction([] {
		ShellExecute(NULL, L"open", L"https://impulse.one", NULL, NULL, SW_SHOWNORMAL);
	})
		.addTooltip("Open Impulse.one").addTranslation());

	addOption(ButtonOption("Open Impulse youtube")
		.addFunction([] {
			ShellExecute(NULL, L"open", L"https://www.youtube.com/channel/UC1Tro0Qg29g9bOwmqiWND3Q", NULL, NULL, SW_SHOWNORMAL);
		})
		.addTooltip("Open Impulse youtube channel").addTranslation());

	addOption(ButtonOption("Open Impulse header creation tutorial")
		.addFunction([] {
		ShellExecute(NULL, L"open", L"https://www.youtube.com/watch?v=b6MqwqdxkBY", NULL, NULL, SW_SHOWNORMAL);
	})
		.addTooltip("Open Impulse header creation tutorial youtube video").addTranslation());

	addOption(ButtonOption("Open Impulse scripthook tutorial")
		.addFunction([] {
		ShellExecute(NULL, L"open", L"https://www.youtube.com/watch?v=xWiTkUk_--Q", NULL, NULL, SW_SHOWNORMAL);
	})
		.addTooltip("Open Impulse scripthook tutorial youtube video").addTranslation());

	addOption(ButtonOption("Open Impulse r* id spoofer tutorial")
		.addFunction([] {
		ShellExecute(NULL, L"open", L"https://www.youtube.com/watch?v=-CebL31BtC8", NULL, NULL, SW_SHOWNORMAL);
	})
		.addTooltip("Open Impulse r* id spoofer tutorial youtube video").addTranslation());
}

/*Update once when submenu is opened*/
void MiscExternalLinksMenu::UpdateOnce() {}

/*Update while submenu is active*/
void MiscExternalLinksMenu::Update() {}

/*Background update*/
void MiscExternalLinksMenu::FeatureUpdate() {}

/*Singleton*/
MiscExternalLinksMenu* _instance;
MiscExternalLinksMenu* MiscExternalLinksMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new MiscExternalLinksMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
MiscExternalLinksMenu::~MiscExternalLinksMenu() { delete _instance; }