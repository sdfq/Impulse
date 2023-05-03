#include "stdafx.h"
#include "peacefulAttachmentMenu.h"
#include "peacefulAttachmentYouToThem.h"
#include "peacefulAttachmentYouToTheirVehicle.h"
#include "peacefulAttachmentYourVehicleToTheirVehicle.h"
#include "peacefulAttachmentTheirVehicleToYourVehicle.h"
#include "../peacefulMenu.h"

using namespace PeacefulAttachmentMenuVars;

namespace PeacefulAttachmentMenuVars {
	Vars vars;
}

void PeacefulAttachmentMenu::Init() {
	setParentSubmenu<PeacefulMenu>();
	setName("Attachment", true, false);

	addOption(SubmenuOption("You to them")
		.addSubmenu<PeacefulAttachmentYouToThemMenu>()
		.addTranslation().addTooltip("Attach you to them"));

	addOption(SubmenuOption("You to their vehicle")
		.addSubmenu<PeacefulAttachmentYouToTheirVehicleMenu>()
		.addTranslation().addTooltip("Attach you to their vehicle"));

	addOption(SubmenuOption("Your vehicle to their vehicle")
		.addSubmenu<PeacefulAttachmentYourVehicleToTheirVehicleMenu>()
		.addTranslation().addTooltip("Attach your vehicle to their vehicle"));

	addOption(SubmenuOption("Their vehicle to your vehicle")
		.addSubmenu<PeacefulAttachmentTheirVehicleToYourVehicleMenu>()
		.addTranslation().addTooltip("Attach their vehicle to your vehicle"));

}

/*Update once when submenu is opened*/
void PeacefulAttachmentMenu::UpdateOnce() {}

/*Update while submenu is active*/
void PeacefulAttachmentMenu::Update() {}

/*Background update*/
void PeacefulAttachmentMenu::FeatureUpdate() {}

/*Singleton*/
PeacefulAttachmentMenu* _instance;
PeacefulAttachmentMenu* PeacefulAttachmentMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new PeacefulAttachmentMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
PeacefulAttachmentMenu::~PeacefulAttachmentMenu() { delete _instance; }