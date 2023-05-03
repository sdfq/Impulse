#include "stdafx.h"
#include "attachmentPedsMenu.h"
#include "../attachmentMenu.h"
#include "../../../../../weapon/weaponShootEntities.h"

using namespace AttachmentPedsMenuVars;

namespace AttachmentPedsMenuVars {
	Vars vars;
}

void AttachmentPedsMenu::Init() {
	setParentSubmenu<AttachmentMenu>();
	setName("Peds", true, false);

	for (int i = 0; i < NUMOF(WeaponShootEntitiesMenuVars::pedPairs) - 1; i++) {
		addOption(ButtonOption(WeaponShootEntitiesMenuVars::pedPairs[i].m_name.Get())
			.addFunction([=] { AttachmentMenuVars::AttachPedToPlayer(GetSelectedPlayer(), WeaponShootEntitiesMenuVars::pedPairs[i].m_result); })
			.addTooltip("Attach this ped to this player"));
	}
}

/*Update once when submenu is opened*/
void AttachmentPedsMenu::UpdateOnce() {}

/*Update while submenu is active*/
void AttachmentPedsMenu::Update() {}

/*Background update*/
void AttachmentPedsMenu::FeatureUpdate() {}

/*Singleton*/
AttachmentPedsMenu* _instance;
AttachmentPedsMenu* AttachmentPedsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new AttachmentPedsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
AttachmentPedsMenu::~AttachmentPedsMenu() { delete _instance; }