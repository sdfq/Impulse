#include "stdafx.h"
#include "attachmentObjectsMenu.h"
#include "../attachmentMenu.h"
#include "../../../../../weapon/weaponShootEntities.h"

using namespace AttachmentObjectsMenuVars;

namespace AttachmentObjectsMenuVars {
	Vars vars;
}

void AttachmentObjectsMenu::Init() {
	setParentSubmenu<AttachmentMenu>();
	setName("Objects", true, false);

	for (int i = 0; i < NUMOF(WeaponShootEntitiesMenuVars::objectPairs) - 1; i++) {
		addOption(ButtonOption(WeaponShootEntitiesMenuVars::objectPairs[i].m_name.Get())
			.addFunction([=] { AttachmentMenuVars::AttachObjectToPlayer(GetSelectedPlayer(), WeaponShootEntitiesMenuVars::objectPairs[i].m_result); })
			.addTooltip("Attach this ped to this player"));
	}
}

/*Update once when submenu is opened*/
void AttachmentObjectsMenu::UpdateOnce() {}

/*Update while submenu is active*/
void AttachmentObjectsMenu::Update() {}

/*Background update*/
void AttachmentObjectsMenu::FeatureUpdate() {}

/*Singleton*/
AttachmentObjectsMenu* _instance;
AttachmentObjectsMenu* AttachmentObjectsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new AttachmentObjectsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
AttachmentObjectsMenu::~AttachmentObjectsMenu() { delete _instance; }