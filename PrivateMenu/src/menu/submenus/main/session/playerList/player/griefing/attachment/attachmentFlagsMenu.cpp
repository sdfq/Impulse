#include "stdafx.h"
#include "attachmentFlagsMenu.h"
#include "../attachmentMenu.h"

using namespace AttachmentFlagsMenuVars;

namespace AttachmentFlagsMenuVars {
	Vars vars;

	vector<pair<String, String>> flags = {
		{ "Canada", "prop_flag_canada" },
		{ "EU", "prop_flag_eu" },
		{ "France", "prop_flag_france" },
		{ "German", "prop_flag_german" },
		{ "Ireland", "prop_flag_ireland" },
		{ "Japan", "prop_flag_japan" },
		{ "LS", "prop_flag_ls" },
		{ "LSFD", "prop_flag_lsfd" },
		{ "LS services", "prop_flag_lsservices" },
		{ "Mexico", "prop_flag_mexico" },
		{ "Russia", "prop_flag_russia" },
		{ "Sherrif", "prop_flag_sheriff" },
		{ "Scotland", "prop_flag_scotland" },
		{ "UK", "prop_flag_uk" },
		{ "US", "prop_flag_us" },
		{ "US boat", "prop_flag_usboat" }
	};
}

void AttachmentFlagsMenu::Init() {
	setParentSubmenu<AttachmentMenu>();
	setName("Flags", true, false);

	for (auto& e : flags) {
		addOption(ButtonOption(e.first)
			.addFunction([=] { AttachmentMenuVars::AttachObjectToPlayer(GetSelectedPlayer(), Utils::GetHashKey(e.second)); })
			.addTooltip("Attach this flag to this player"));
	}
}

/*Update once when submenu is opened*/
void AttachmentFlagsMenu::UpdateOnce() {}

/*Update while submenu is active*/
void AttachmentFlagsMenu::Update() {}

/*Background update*/
void AttachmentFlagsMenu::FeatureUpdate() {}

/*Singleton*/
AttachmentFlagsMenu* _instance;
AttachmentFlagsMenu* AttachmentFlagsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new AttachmentFlagsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
AttachmentFlagsMenu::~AttachmentFlagsMenu() { delete _instance; }