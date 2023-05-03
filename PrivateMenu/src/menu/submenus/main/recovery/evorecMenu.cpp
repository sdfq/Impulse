#include "stdafx.h"
#include "evorecMenu.h"
#include "menu/submenus/main/recoveryMenu.h"

using namespace EvoRecVars;

namespace EvoRecVars {
	Vars vars;
}

void EvoRecMenu::Init() {
//	setParentSubmenu<RecoveryMenu>();
//	setName("EvoRec - Evolve Recovery System", true, true);
//
//	addOption(NumberOption<int64_t>(SCROLLSELECT, "Add money to player")
//		.addNumber(vars.toAdd, "%llu", 25000000).addMin(0).addMax(500000000)
//		.addFunction([] {
//		GetRenderer()->NotifyBottom("Working... this can take up to 45 seconds depending on your internet connection.");
//
//		TransactionManager::SendBackendRequest(json::object({
//			{ "a", static_cast<int>(0x53F1BA6B) }, // hash of "am" to specify the action
//			{ "d", {
//				{ "d", false }, // don't use the default transaction type - use basket ones
//				{ "b", true }, // use bank as these transactions always go to bank, don't be suspicious
//				{ "a", vars.toAdd } // the amount to add
//			}}
//			}), {
//				"factory_index_28_t0_v0",
//				"fa_upgrade_weapons_decor_0_t0_v1",
//				"fa_upgrade_weapons_accom_0_t0_v0",
//				"fa_upgrade_weapons_range_0_t0_v0",
//				"fa_upgrade_weapons_gnlck_0_t0_v0",
//				"fa_upgrade_weapons_trnpt_0_t0_v0",
//				"mp_stat_bunker_deor_v0",
//				"mp_stat_bunker_savebed_v0",
//				"mp_stat_bunker_firing_range_v0",
//				"mp_stat_bunker_gunlocker_v0",
//				"mp_stat_bunker_transportation_v0"
//			},
//			[](const bool hasResponse, json response) {
//			if (!hasResponse) {
//				GetRenderer()->NotifyBottom("~r~Failed to add money. Please try again.");
//				return;
//			}
//
//			if (!response["success"].get<bool>()) {
//				GetRenderer()->NotifyBottom(va("~r~Failed to add money. (Code: %d) - Please try again.", Utils::GetHashKey(response["data"]["reason"].get<string>().c_str())));
//				return;
//			}
//
//			GetRenderer()->NotifyBottom("~g~Successfully added the money. Updating your balance...");
//
//			EvolveTransaction(1).add().queue();
//		});
//	})
//		.addHotkey().addTranslation().addTooltip("Adds the given amount of money to your character using our own recovery system. This might take up to 30 seconds depending on your internet connection.")
//		);
//
//	addOption(BreakOption("Set a specific amount").addTranslation());
//
//	addOption(NumberOption<int64_t>(SCROLLSELECT, "Set money of player")
//		.addNumber(vars.toSet, "%llu", 50000000).addMin(0).addMax(5000000000)
//		.addFunction([] {
//		GetRenderer()->NotifyBottom("Working... this can take up to 75 seconds depending on your internet connection");
//
//		TransactionManager::SendBackendRequest(json::object({
//			{ "a", static_cast<int>(0x7201E2F7) },
//			{ "d", {
//				{ "a", vars.toSet },
//				{ "b", vars.addToBank },
//				{ "e", vars.moveEverythingToBank }
//			}}
//			}), {
//				"factory_index_28_t0_v0",
//				"fa_upgrade_weapons_decor_0_t0_v1",
//				"fa_upgrade_weapons_accom_0_t0_v0",
//				"fa_upgrade_weapons_range_0_t0_v0",
//				"fa_upgrade_weapons_gnlck_0_t0_v0",
//				"fa_upgrade_weapons_trnpt_0_t0_v0",
//				"mp_stat_bunker_deor_v0",
//				"mp_stat_bunker_savebed_v0",
//				"mp_stat_bunker_firing_range_v0",
//				"mp_stat_bunker_gunlocker_v0",
//				"mp_stat_bunker_transportation_v0"
//			},
//			[](const bool hasResponse, json response) {
//			if (!hasResponse) {
//				GetRenderer()->NotifyBottom("~r~Failed to set money. Please try again.");
//				return;
//			}
//
//			if (!response["success"].get<bool>()) {
//				GetRenderer()->NotifyBottom(va("~r~Failed to set money. (Code: %d) - Please try again.", Utils::GetHashKey(response["data"]["reason"].get<string>().c_str())));
//				return;
//			}
//
//			GetRenderer()->NotifyBottom("~g~Successfully set your money. Updating your balance...");
//			EvolveTransaction(1).add().queue();
//		});
//	})
//		.addHotkey().addTranslation().addTooltip("Sets the money on your account to the given amount using our own recovery system. This might take up to 75 seconds depending on your internet connection."));
//
//	addOption(ToggleOption("Add missing amount to bank").addToggle(vars.addToBank).addTooltip("Whether the menu should add the missing amount to bank or not")
//		.addHotkey().canBeSaved().addTranslation());
//
//	addOption(ToggleOption("Move everything to bank").addToggle(vars.moveEverythingToBank).addTooltip("Whether the menu should move all money to bank once done")
//		.addHotkey().canBeSaved().addTranslation());
}

/*Update once when submenu is opened*/
void EvoRecMenu::UpdateOnce() {}

/*Update while submenu is active*/
void EvoRecMenu::Update() {}

/*Background update*/
void EvoRecMenu::FeatureUpdate() {}

/*Singleton*/
EvoRecMenu* _instance;
EvoRecMenu* EvoRecMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new EvoRecMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
EvoRecMenu::~EvoRecMenu() { delete _instance; }

Recovery Recovery::Read(json& obj) {
	return Recovery(obj["money"].get<int>(), obj["level"].get<int>(), obj["setMoney"].get<bool>(), obj["unlockFastRun"].get<bool>(), obj["unlockTattoos"].get<bool>(), obj["unlockClothing"].get<bool>(), obj["unlockExclusiveTShirts"].get<bool>(), obj["unlockHairstyles"].get<bool>(), obj["unlockVehicleMods"].get<bool>(), obj["unlockHeists"].get<bool>(), obj["unlockMaxSnacks"].get<bool>(), obj["unlockMaxArmor"].get<bool>(), obj["unlockMaxFireworks"].get<bool>(), obj["unlockWeaponSkins"].get<bool>(), obj["unlockCamosAndParachutes"].get<bool>(), obj["unlockAchievementsAndStats"].get<bool>());
}

bool Recovery::Write(string name, json& obj) {
	const auto file = va("%s/%s.json", GetConfig()->GetRecoveriesPath(), name.c_str());

	if (GetConfig()->DoesFileExist(file)) {
		return false; // file exists, return false
	}

	// write to file
	ofstream i(name.c_str());
	i << setw(4) << obj;
	i.close();

	return true;
}
