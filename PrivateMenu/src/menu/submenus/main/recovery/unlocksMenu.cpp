#include "stdafx.h"
#include "unlocksMenu.h"
#include "../recoveryMenu.h"

using namespace UnlocksMenuVars;

namespace UnlocksMenuVars {

	void UnlockBunkerResearches() {
		std::map<int, int> map({ { 0, 15381 },{ 1, 15382 },{ 2, 15428 },{ 3, 15429 },{ 4, 15430 },{ 5, 15431 },{ 6, 15491 },{ 7, 15432 },{ 8, 15433 },{ 9, 15434 },{ 10, 15435 },{ 11, 15436 },{ 12, 15437 },{ 13, 15438 },{ 14, 15439 },{ 15, 15447 },{ 16, 15448 },{ 17, 15449 },{ 18, 15450 },{ 19, 15451 },{ 20, 15452 },{ 21, 15453 },{ 22, 15454 },{ 23, 15455 },{ 24, 15456 },{ 25, 15457 },{ 26, 15458 },{ 27, 15459 },{ 28, 15460 },{ 29, 15461 },{ 30, 15462 },{ 31, 15463 },{ 32, 15464 },{ 33, 15465 },{ 34, 15466 },{ 35, 15467 },{ 36, 15468 },{ 37, 15469 },{ 38, 15470 },{ 39, 15471 },{ 40, 15472 },{ 41, 15473 },{ 42, 15474 },{ 43, 15492 },{ 44, 15493 },{ 45, 15494 },{ 46, 15495 },{ 47, 15496 },{ 48, 15497 },{ 49, 15498 },{ 50, 15499 } });

		int currentChar;
		STATS::StatGetInt(0x2F2F120F, &currentChar, -1);
		int CurrentChar = currentChar;
		//char* currentCharacter = (currentChar ? "MP1_" : "MP0_");

		for (auto entry : map) {
			const auto hash = STATS::_GetNgstatBoolHash(entry.second - 15369, 0, 1, CurrentChar, "_DLCGUNPSTAT_BOOL");
			const auto mask = ((entry.second - 15369) - STATS::_0xF4D8E7AC2A27758C(entry.second - 15369) * 64);
			STATS::StatSetBoolMasked(hash, true, mask, true);
		}
		STATS::StatSetInt(Utils::GetHashKey(va("mp%d_gunr_research_item", CurrentChar)), -1, true);
	}

}

void UnlocksMenu::Init() {
	setParentSubmenu<RecoveryMenu>();
	setName("Unlocks", true, true);

	/*addOption(ButtonOption("Unlock fast run")
		.addHotkey().addTranslation()
		.addTooltip("Unlock fast run")
		.addFunction([this] {
		Stats::SetStatI("CHAR_FM_ABILITY_1_UNLCK", -1, true);
		Stats::SetStatI("CHAR_FM_ABILITY_2_UNLCK", -1, true);
		Stats::SetStatI("CHAR_FM_ABILITY_3_UNLCK", -1, true);
		GetRenderer()->NotifyMap("Fast run unlocked");
		AUDIO::PlaySoundFrontend(-1, "NAV_UP_DOWN", "GO", 0);
	}));*/

	addOption(ButtonOption("Unlock tattoos")
		.addHotkey().addTranslation()
		.addTooltip("Unlock all tattoos")
		.addFunction([this] {
		Stats::SetStatI("tattoo_fm_unlocks_1", -1, true);
		Stats::SetStatI("tattoo_fm_unlocks_2", -1, true);
		Stats::SetStatI("tattoo_fm_unlocks_3", -1, true);
		Stats::SetStatI("tattoo_fm_unlocks_4", -1, true);
		Stats::SetStatI("tattoo_fm_unlocks_5", -1, true);
		Stats::SetStatI("tattoo_fm_unlocks_6", -1, true);
		Stats::SetStatI("tattoo_fm_unlocks_7", -1, true);
		Stats::SetStatI("tattoo_fm_unlocks_8", -1, true);
		Stats::SetStatI("tattoo_fm_unlocks_9", -1, true);
		Stats::SetStatI("tattoo_fm_unlocks_10", -1, true);
		Stats::SetStatI("tattoo_fm_unlocks_11", -1, true);
		Stats::SetStatI("tattoo_fm_unlocks_12", -1, true);
		GetRenderer()->NotifyMap("Tattoos unlocked");
		AUDIO::PlaySoundFrontend(-1, "NAV_UP_DOWN", "GO", 0);
	}));

	addOption(ButtonOption("Unlock clothing")
		.addHotkey().addTranslation()
		.addTooltip("Unlock all clothing")
		.addFunction([this] {
		Stats::SetStatI("CLTHS_AVAILABLE_FEET_1", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_JBIB", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_JBIB_1", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_JBIB_2", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_JBIB_3", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_JBIB_4", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_JBIB_5", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_JBIB_6", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_JBIB_7", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_LEGS", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_LEGS_1", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_LEGS_2", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_LEGS_3", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_LEGS_4", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_LEGS_5", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_LEGS_6", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_LEGS_7", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_FEET", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_FEET_1", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_FEET_2", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_FEET_3", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_FEET_4", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_FEET_5", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_FEET_6", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_FEET_7", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_BERD", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_BERD_1", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_BERD_2", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_BERD_3", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_BERD_4", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_BERD_5", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_BERD_6", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_BERD_7", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_PROPS", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_PROPS_1", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_PROPS_2", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_PROPS_3", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_PROPS_4", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_PROPS_5", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_PROPS_6", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_PROPS_7", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_PROPS_8", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_PROPS_9", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_PROPS_10", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_OUTFIT", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_HAIR", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_HAIR_1", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_HAIR_2", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_HAIR_3", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_HAIR_4", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_HAIR_5", -1, true);;
		Stats::SetStatI("CLTHS_ACQUIRED_HAIR_6", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_HAIR_7", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_JBIB", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_JBIB_1", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_JBIB_2", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_JBIB_3", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_JBIB_4", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_JBIB_5", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_JBIB_6", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_JBIB_7", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_LEGS", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_LEGS_1", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_LEGS_2", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_LEGS_3", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_LEGS_4", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_LEGS_5", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_LEGS_6", -1, true);;
		Stats::SetStatI("CLTHS_ACQUIRED_LEGS_7", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_FEET", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_FEET_1", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_FEET_2", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_FEET_3", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_FEET_4", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_FEET_5", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_FEET_6", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_FEET_7", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_BERD", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_BERD_1", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_BERD_2", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_BERD_3", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_BERD_4", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_BERD_5", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_BERD_6", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_BERD_7", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_PROPS", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_PROPS_1", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_PROPS_2", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_PROPS_3", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_PROPS_4", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_PROPS_5", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_PROPS_6", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_PROPS_7", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_PROPS_8", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_PROPS_9", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_PROPS_10", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_OUTFIT", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_TORSO", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_SPECIAL", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_SPECIAL_1", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_SPECIAL_2", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_SPECIAL_3", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_SPECIAL_4", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_SPECIAL_5", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_SPECIAL_6", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_SPECIAL_7", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_SPECIAL2", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_SPECIAL2_1", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_DECL", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_TEETH", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_TEETH_1", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_TEETH_2", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_TORSO", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_SPECIAL", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_SPECIAL_1", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_SPECIAL_2", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_SPECIAL_3", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_SPECIAL_4", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_SPECIAL_5", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_SPECIAL_6", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_SPECIAL_7", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_SPECIAL2", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_SPECIAL2_1", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_DECL", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_TEETH", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_TEETH_1", -1, true);
		Stats::SetStatI("CLTHS_ACQUIRED_TEETH_2", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_0", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_1", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_2", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_3", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_4", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_5", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_6", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_7", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_8", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_9", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_10", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_11", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_12", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_13", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_14", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_15", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_16", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_17", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_18", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_19", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_21", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_22", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_23", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_24", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_24", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_25", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_26", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_27", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_28", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_29", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_30", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_31", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_32", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_33", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_34", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_35", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_36", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_37", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_38", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_39", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_40", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_41", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_42", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_43", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_44", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_45", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_46", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_47", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_48", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_49", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_50", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_51", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_52", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_53", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_54", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_55", -1, true);
		Stats::SetStatI("DLC_APPAREL_ACQUIRED_56", -1, true);
		Stats::SetStatI("ADMIN_CLOTHES_GV_BS_1", -1, true);
		Stats::SetStatI("ADMIN_CLOTHES_GV_BS_2", -1, true);
		Stats::SetStatI("ADMIN_CLOTHES_GV_BS_3", -1, true);
		Stats::SetStatI("ADMIN_CLOTHES_GV_BS_4", -1, true);
		Stats::SetStatI("ADMIN_CLOTHES_GV_BS_5", -1, true);
		Stats::SetStatI("ADMIN_CLOTHES_GV_BS_6", -1, true);
		Stats::SetStatI("ADMIN_CLOTHES_GV_BS_7", -1, true);
		Stats::SetStatI("ADMIN_CLOTHES_GV_BS_8", -1, true);
		Stats::SetStatI("ADMIN_CLOTHES_GV_BS_9", -1, true);
		Stats::SetStatI("ADMIN_CLOTHES_GV_BS_10", -1, true);
		Stats::SetStatI("ADMIN_CLOTHES_GV_BS_11", -1, true);
		Stats::SetStatI("ADMIN_CLOTHES_GV_BS_12", -1, true);
		Stats::SetStatI("ADMIN_CLOTHES_GV_BS_13", -1, true);
		Stats::SetStatI("ADMIN_CLOTHES_GV_BS_1", -1, true);
		Stats::SetStatI("ADMIN_CLOTHES_RM_BS_10", -1, true);
		Stats::SetStatI("ADMIN_CLOTHES_GV_BS_10", -1, true);
		Stats::SetStatI("ADMIN_CLOTHES_RM_BS_11", -1, true);
		Stats::SetStatI("ADMIN_CLOTHES_GV_BS_11", -1, true);
		Stats::SetStatI("ADMIN_CLOTHES_RM_BS_12", -1, true);
		Stats::SetStatI("ADMIN_CLOTHES_GV_BS_12", -1, true);
		GetRenderer()->NotifyMap("Clothing unlocked");
		AUDIO::PlaySoundFrontend(-1, "NAV_UP_DOWN", "GO", 0);
	}));

	addOption(ButtonOption("Unlock exclusive t-shirts")
		.addHotkey().addTranslation()
		.addTooltip("Unlock exclusive t-shirts")
		.addFunction([this] {
		Stats::SetStatI("AWD_FMHORDWAVESSURVIVE", 10, true);
		Stats::SetStatI("AWD_FMPICKUPDLCCRATE1ST", 1, true);
		Stats::SetStatI("AWD_WIN_CAPTURE_DONT_DYING", 25, true);
		Stats::SetStatI("AWD_DO_HEIST_AS_MEMBER", 25, true);
		Stats::SetStatI("AWD_PICKUP_CAP_PACKAGES", 100, true);
		Stats::SetStatB("AWD_FINISH_HEIST_NO_DAMAGE", 1, true);
		Stats::SetStatI("AWD_WIN_GOLD_MEDAL_HEISTS", 25, true);
		Stats::SetStatI("AWD_KILL_TEAM_YOURSELF_LTS", 25, true);
		Stats::SetStatI("AWD_KILL_PSYCHOPATHS", 100, true);
		Stats::SetStatI("AWD_DO_HEIST_AS_THE_LEADER", 25, true);
		Stats::SetStatB("AWD_STORE_20_CAR_IN_GARAGES", 1, true);
		GetRenderer()->NotifyMap("Exclusive t-shirts unlocked");
		AUDIO::PlaySoundFrontend(-1, "NAV_UP_DOWN", "GO", 0);
	}));

	addOption(ButtonOption("Unlock hairstyles")
		.addHotkey().addTranslation()
		.addTooltip("Unlock all hairstyles")
		.addFunction([this] {
		Stats::SetStatI("CLTHS_AVAILABLE_HAIR", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_HAIR_1", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_HAIR_2", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_HAIR_3", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_HAIR_4", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_HAIR_5", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_HAIR_6", -1, true);
		Stats::SetStatI("CLTHS_AVAILABLE_HAIR_7", -1, true);
		GetRenderer()->NotifyMap("Hairstyles unlocked");
		AUDIO::PlaySoundFrontend(-1, "NAV_UP_DOWN", "GO", 0);
	}));

	addOption(BreakOption("Vehicles").addTranslation());

	addOption(ButtonOption("Unlock vehicle mods")
		.addHotkey().addTranslation()
		.addTooltip("Unlock all vehicle mods")
		.addFunction([this] {
		Stats::SetStatI("RACES_WON", 50, true);
		Stats::SetStatI("CHAR_FM_CARMOD_1_UNLCK", -1, true);
		Stats::SetStatI("CHAR_FM_CARMOD_2_UNLCK", -1, true);
		Stats::SetStatI("CHAR_FM_CARMOD_3_UNLCK", -1, true);
		Stats::SetStatI("CHAR_FM_CARMOD_4_UNLCK", -1, true);
		Stats::SetStatI("CHAR_FM_CARMOD_5_UNLCK", -1, true);
		Stats::SetStatI("CHAR_FM_CARMOD_6_UNLCK", -1, true);
		Stats::SetStatI("CHAR_FM_CARMOD_7_UNLCK", -1, true);
		Stats::SetStatI("AWD_FMRALLYWONDRIVE", 1, true);
		Stats::SetStatI("AWD_FMRALLYWONNAV", 1, true);
		Stats::SetStatI("AWD_FMWINSEARACE", 1, true);
		Stats::SetStatI("AWD_FMWINAIRRACE", 1, true);
		Stats::SetStatI("NUMBER_TURBO_STARTS_IN_RACE", 50, true);
		Stats::SetStatI("USJS_COMPLETED", 50, true);
		Stats::SetStatI("AWD_FM_RACES_FASTEST_LAP", 50, true);
		Stats::SetStatI("NUMBER_SLIPSTREAMS_IN_RACE", 100, true);
		Stats::SetStatI("AWD_WIN_CAPTURES", 25, true);
		Stats::SetStatI("AWD_DROPOFF_CAP_PACKAGES", 100, true);
		Stats::SetStatI("AWD_KILL_CARRIER_CAPTURE", 100, true);
		Stats::SetStatI("AWD_FINISH_HEISTS", 50, true);
		Stats::SetStatI("AWD_FINISH_HEIST_SETUP_JOB", 50, true);
		Stats::SetStatI("AWD_NIGHTVISION_KILLS", 100, true);
		Stats::SetStatI("AWD_WIN_LAST_TEAM_STANDINGS", 50, true);
		Stats::SetStatI("AWD_ONLY_PLAYER_ALIVE_LTS", 50, true);
		Stats::SetStatI("AWD_ENEMYDRIVEBYKILLS", 600, true);
		Stats::SetStatI("USJS_FOUND", 50, true);
		Stats::SetStatI("DB_PLAYER_KILLS", 1000, true);
		Stats::SetStatI("KILLS_PLAYERS", 1000, true);
		Stats::SetStatI("AWD_FMHORDWAVESSURVIVE", 21, true);
		Stats::SetStatI("AWD_CAR_BOMBS_ENEMY_KILLS", 25, true);
		Stats::SetStatI("AWD_FM_TDM_MVP", 60, true);
		Stats::SetStatI("AWD_HOLD_UP_SHOPS", 20, true);
		Stats::SetStatI("AWD_RACES_WON", 101, true);
		Stats::SetStatI("AWD_NO_ARMWRESTLING_WINS", 21, true);
		Stats::SetStatI("AWD_FMBBETWIN", 50000, true);
		Stats::SetStatI("AWD_FM_DM_WINS", 51, true);
		Stats::SetStatI("AWD_FM_DM_TOTALKILLS", 500, true);
		Stats::SetStatI("MPPLY_DM_TOTAL_DEATHS", 412, true);
		Stats::SetStatI("MPPLY_TIMES_FINISH_DM_TOP_3", 36, true);
		Stats::SetStatI("PLAYER_HEADSHOTS", 623, true);
		Stats::SetStatI("AWD_FM_DM_WINS", 63, true);
		Stats::SetStatI("AWD_FM_TDM_WINS", 13, true);
		Stats::SetStatI("AWD_FM_GTA_RACES_WON", 12, true);
		Stats::SetStatI("AWD_FM_GOLF_WON", 2, true);
		Stats::SetStatI("AWD_FM_SHOOTRANG_TG_WON", 2, true);
		Stats::SetStatI("AWD_FM_SHOOTRANG_RT_WON", 2, true);
		Stats::SetStatI("AWD_FM_SHOOTRANG_CT_WON", 2, true);
		Stats::SetStatI("AWD_FM_SHOOTRANG_GRAN_WON", 2, true);
		Stats::SetStatI("AWD_FM_TENNIS_WON", 2, true);
		Stats::SetStatI("MPPLY_TENNIS_MATCHES_WON", 2, true);
		Stats::SetStatI("MPPLY_TOTAL_TDEATHMATCH_WON", 63, true);
		Stats::SetStatI("MPPLY_TOTAL_RACES_WON", 101, true);
		Stats::SetStatI("MPPLY_TOTAL_DEATHMATCH_LOST", 23, true);
		Stats::SetStatI("MPPLY_TOTAL_RACES_LOST", 36, true);
		Stats::SetStatI("AWD_25_KILLS_STICKYBOMBS", 50, true);
		Stats::SetStatI("AWD_50_KILLS_GRENADES", 50, true);
		Stats::SetStatI("GRENADE_ENEMY_KILLS", 50, true);
		Stats::SetStatI("AWD_20_KILLS_MELEE", 50, true);
		Stats::SetStatI("ARENAWARS_AP_TIER", 1000, true);
		GetRenderer()->NotifyMap("Vehicle mods unlocked");
		AUDIO::PlaySoundFrontend(-1, "NAV_UP_DOWN", "GO", 0);
	}));

	addOption(ButtonOption("Unlock heists")
		.addHotkey().addTranslation()
		.addTooltip("Unlock all heists")
		.addFunction([this] {
		Stats::SetStatI("CHAR_KIT_FM_PURCHASE", -1, true);
		Stats::SetStatI("CHAR_KIT_FM_PURCHASE2", -1, true);
		Stats::SetStatI("CHAR_KIT_FM_PURCHASE3", -1, true);
		Stats::SetStatI("CHAR_KIT_FM_PURCHASE4", -1, true);
		Stats::SetStatI("CHAR_KIT_FM_PURCHASE5", -1, true);
		Stats::SetStatI("CHAR_KIT_FM_PURCHASE6", -1, true);
		Stats::SetStatI("CHAR_KIT_FM_PURCHASE7", -1, true);
		Stats::SetStatI("CHAR_KIT_FM_PURCHASE8", -1, true);
		Stats::SetStatI("CHAR_KIT_FM_PURCHASE9", -1, true);
		Stats::SetStatI("CHAR_KIT_FM_PURCHASE10", -1, true);
		Stats::SetStatI("CHAR_KIT_FM_PURCHASE11", -1, true);
		Stats::SetStatI("CHAR_KIT_FM_PURCHASE12", -1, true);
		Stats::SetStatI("CHAR_KIT_1_FM_UNLCK", -1, true);
		Stats::SetStatI("CHAR_KIT_2_FM_UNLCK", -1, true);
		Stats::SetStatI("CHAR_KIT_3_FM_UNLCK", -1, true);
		Stats::SetStatI("CHAR_KIT_4_FM_UNLCK", -1, true);
		Stats::SetStatI("CHAR_KIT_5_FM_UNLCK", -1, true);
		Stats::SetStatI("CHAR_KIT_6_FM_UNLCK", -1, true);
		Stats::SetStatI("CHAR_KIT_7_FM_UNLCK", -1, true);
		Stats::SetStatI("CHAR_KIT_8_FM_UNLCK", -1, true);
		Stats::SetStatI("CHAR_KIT_9_FM_UNLCK", -1, true);
		Stats::SetStatI("CHAR_KIT_10_FM_UNLCK", -1, true);
		Stats::SetStatI("CHAR_KIT_11_FM_UNLCK", -1, true);
		Stats::SetStatI("CHAR_KIT_12_FM_UNLCK", -1, true);
		Stats::SetStatI("races_won", 100, true);
		Stats::SetStatI("usjs_found", 50, true);
		Stats::SetStatI("CHAR_FM_VEHICLE_1_UNLCK", -1, true);
		Stats::SetStatI("CHAR_FM_VEHICLE_2_UNLCK", -1, true);
		Stats::SetStatI("CHAR_FM_PACKAGE_1_COLLECT", -1, true);
		Stats::SetStatI("CHAR_FM_PACKAGE_2_COLLECT", -1, true);
		Stats::SetStatI("CHAR_FM_PACKAGE_3_COLLECT", -1, true);
		Stats::SetStatI("CHAR_FM_PACKAGE_4_COLLECT", -1, true);
		Stats::SetStatI("CHAR_FM_PACKAGE_5_COLLECT", -1, true);
		Stats::SetStatI("CHAR_FM_PACKAGE_6_COLLECT", -1, true);
		Stats::SetStatI("CHAR_FM_PACKAGE_7_COLLECT", -1, true);
		Stats::SetStatI("CHAR_FM_PACKAGE_8_COLLECT", -1, true);
		Stats::SetStatI("CHAR_FM_PACKAGE_9_COLLECT", -1, true);
		Stats::SetStatI("CHAR_FM_HEALTH_1_UNLCK", -1, true);
		Stats::SetStatI("CHAR_FM_HEALTH_2_UNLCK", -1, true);
		Stats::SetStatI("HOLDUPS_BITSET", -1, true);
		GetRenderer()->NotifyMap("Heists unlocked");
		AUDIO::PlaySoundFrontend(-1, "NAV_UP_DOWN", "GO", 0);
	}));

	addOption(BreakOption("Inventory").addTranslation());

	addOption(ButtonOption("Max snacks")
		.addHotkey().addTranslation()
		.addTooltip("Max snacks")
		.addFunction([this] {
		Stats::SetStatI("NO_BOUGHT_YUM_SNACKS", 2000000, true);
		Stats::SetStatI("NO_BOUGHT_HEALTH_SNACKS", 2000000, true);
		Stats::SetStatI("NO_BOUGHT_EPIC_SNACKS", 2000000, true);
		Stats::SetStatI("NUMBER_OF_ORANGE_BOUGHT", 2000000, true);
		Stats::SetStatI("CIGARETTES_BOUGHT", 2000000, true);
		GetRenderer()->NotifyMap("Max snacks given");
		AUDIO::PlaySoundFrontend(-1, "NAV_UP_DOWN", "GO", 0);
	}));

	addOption(ButtonOption("Max armor")
		.addHotkey().addTranslation()
		.addTooltip("Max armor")
		.addFunction([this] {
		Stats::SetStatI("MP_CHAR_ARMOUR_1_COUNT", 2000000, true);
		Stats::SetStatI("MP_CHAR_ARMOUR_2_COUNT", 2000000, true);
		Stats::SetStatI("MP_CHAR_ARMOUR_3_COUNT", 2000000, true);
		Stats::SetStatI("MP_CHAR_ARMOUR_4_COUNT", 2000000, true);
		Stats::SetStatI("MP_CHAR_ARMOUR_5_COUNT", 2000000, true);
		GetRenderer()->NotifyMap("Max armor given");
		AUDIO::PlaySoundFrontend(-1, "NAV_UP_DOWN", "GO", 0);
	}));

	addOption(ButtonOption("Max fireworks")
		.addHotkey().addTranslation()
		.addTooltip("Max fireworks")
		.addFunction([this] {
		Stats::SetStatI("FIREWORK_TYPE_1_WHITE", 2000000, true);
		Stats::SetStatI("FIREWORK_TYPE_1_RED", 2000000, true);
		Stats::SetStatI("FIREWORK_TYPE_1_BLUE", 2000000, true);
		Stats::SetStatI("FIREWORK_TYPE_2_WHITE", 2000000, true);
		Stats::SetStatI("FIREWORK_TYPE_2_RED", 2000000, true);
		Stats::SetStatI("FIREWORK_TYPE_2_BLUE", 2000000, true);
		Stats::SetStatI("FIREWORK_TYPE_3_WHITE", 2000000, true);
		Stats::SetStatI("FIREWORK_TYPE_3_RED", 2000000, true);
		Stats::SetStatI("FIREWORK_TYPE_3_BLUE", 2000000, true);
		Stats::SetStatI("FIREWORK_TYPE_4_WHITE", 2000000, true);
		Stats::SetStatI("FIREWORK_TYPE_4_RED", 2000000, true);
		Stats::SetStatI("FIREWORK_TYPE_4_BLUE", 2000000, true);
		GetRenderer()->NotifyMap("Max fireworks given");
		AUDIO::PlaySoundFrontend(-1, "NAV_UP_DOWN", "GO", 0);
	}));

	addOption(BreakOption("Misc").addTranslation());

	addOption(ButtonOption("Unlock weapon skins")
		.addHotkey().addTranslation()
		.addTooltip("Unlock all weapon skins")
		.addFunction([this] {
		Stats::SetStatI("GRENADE_ENEMY_KILLS", 50, false);
		Stats::SetStatI("AWD_20_KILLS_MELEE", 50, false);
		Stats::SetStatI("MOLOTOV_ENEMY_KILLS", 600, false);
		Stats::SetStatI("CMBTPISTOL_ENEMY_KILLS", 600, false);
		Stats::SetStatI("PISTOL50_ENEMY_KILLS", 600, false);
		Stats::SetStatI("APPISTOL_ENEMY_KILLS", 600, false);
		Stats::SetStatI("MICROSMG_ENEMY_KILLS", 600, false);
		Stats::SetStatI("SMG_ENEMY_KILLS", 600, false);
		Stats::SetStatI("ASLTSMG_ENEMY_KILLS", 600, false);
		Stats::SetStatI("ASLTRIFLE_ENEMY_KILLS", 600, false);
		Stats::SetStatI("CRBNRIFLE_ENEMY_KILLS", 600, false);
		Stats::SetStatI("ADVRIFLE_ENEMY_KILLS", 600, false);
		Stats::SetStatI("MG_ENEMY_KILLS", 600, false);
		Stats::SetStatI("CMBTMG_ENEMY_KILLS", 600, false);
		Stats::SetStatI("ASLTMG_ENEMY_KILLS", 600, false);
		Stats::SetStatI("PUMP_ENEMY_KILLS", 600, false);
		Stats::SetStatI("SAWNOFF_ENEMY_KILLS", 600, false);
		Stats::SetStatI("BULLPUP_ENEMY_KILLS", 600, false);
		Stats::SetStatI("ASLTSHTGN_ENEMY_KILLS", 600, false);
		Stats::SetStatI("SNIPERRFL_ENEMY_KILLS", 600, false);
		Stats::SetStatI("HVYSNIPER_ENEMY_KILLS", 600, false);
		Stats::SetStatI("GRNLAUNCH_ENEMY_KILLS", 600, false);
		Stats::SetStatI("RPG_ENEMY_KILLS", 600, false);
		Stats::SetStatI("MINIGUNS_ENEMY_KILLS", 600, false);
		Stats::SetStatI("GRENADE_ENEMY_KILLS", 600, false);
		Stats::SetStatI("SMKGRENADE_ENEMY_KILLS", 600, false);
		Stats::SetStatI("STKYBMB_ENEMY_KILLS", 600, false);
		Stats::SetStatI("MOLOTOV_ENEMY_KILLS", 600, false);
		GetRenderer()->NotifyMap("Weapon skins unlocked");
		AUDIO::PlaySoundFrontend(-1, "NAV_UP_DOWN", "GO", 0);
	}));

	addOption(ButtonOption("Unlock camos and parachutes")
		.addHotkey().addTranslation()
		.addTooltip("Unlock all camos and parachutes")
		.addFunction([this] {
		Stats::SetStatI("CHAR_KIT_1_FM_UNLCK", -1, true);
		Stats::SetStatI("CHAR_KIT_2_FM_UNLCK", -1, true);
		Stats::SetStatI("CHAR_KIT_3_FM_UNLCK", -1, true);
		Stats::SetStatI("CHAR_KIT_4_FM_UNLCK", -1, true);
		Stats::SetStatI("CHAR_KIT_5_FM_UNLCK", -1, true);
		Stats::SetStatI("CHAR_KIT_6_FM_UNLCK", -1, true);
		Stats::SetStatI("CHAR_KIT_7_FM_UNLCK", -1, true);
		Stats::SetStatI("CHAR_KIT_8_FM_UNLCK", -1, true);
		Stats::SetStatI("CHAR_KIT_9_FM_UNLCK", -1, true);
		Stats::SetStatI("CHAR_KIT_10_FM_UNLCK", -1, true);
		Stats::SetStatI("CHAR_KIT_11_FM_UNLCK", -1, true);
		Stats::SetStatI("CHAR_KIT_12_FM_UNLCK", -1, true);
		Stats::SetStatI("CHAR_KIT_FM_PURCHASE", -1, true);
		Stats::SetStatI("CHAR_KIT_FM_PURCHASE2", -1, true);
		Stats::SetStatI("CHAR_KIT_FM_PURCHASE3", -1, true);
		Stats::SetStatI("CHAR_KIT_FM_PURCHASE4", -1, true);
		Stats::SetStatI("CHAR_KIT_FM_PURCHASE5", -1, true);
		Stats::SetStatI("CHAR_KIT_FM_PURCHASE6", -1, true);
		Stats::SetStatI("CHAR_KIT_FM_PURCHASE7", -1, true);
		Stats::SetStatI("CHAR_KIT_FM_PURCHASE8", -1, true);
		Stats::SetStatI("CHAR_KIT_FM_PURCHASE9", -1, true);
		Stats::SetStatI("CHAR_KIT_FM_PURCHASE10", -1, true);
		Stats::SetStatI("CHAR_KIT_FM_PURCHASE11", -1, true);
		Stats::SetStatI("CHAR_KIT_FM_PURCHASE12", -1, true);
		GetRenderer()->NotifyMap("Camos and parachutes unlocked");
		AUDIO::PlaySoundFrontend(-1, "NAV_UP_DOWN", "GO", 0);
	}));

	addOption(ButtonOption("Unlock achievements and stats")
		.addHotkey().addTranslation()
		.addTooltip("Unlock all achievements and stats")
		.addFunction([this] {
		Stats::SetStatB("AWD_FMRACEWORLDRECHOLDER", 1, false);
		Stats::SetStatI("AWD_ENEMYDRIVEBYKILLS", 600, false);
		Stats::SetStatI("USJS_FOUND", 50, false);
		Stats::SetStatB("AWD_FMWINALLRACEMODES", 1, false);
		Stats::SetStatB("AWD_FMWINEVERYGAMEMODE", 1, false);
		Stats::SetStatI("DB_PLAYER_KILLS", 1000, false);
		Stats::SetStatI("KILLS_PLAYERS", 1000, false);
		Stats::SetStatI("AWD_FMHORDWAVESSURVIVE", 21, false);
		Stats::SetStatI("AWD_CAR_BOMBS_ENEMY_KILLS", 25, false);
		Stats::SetStatI("AWD_FM_TDM_MVP", 60, false);
		Stats::SetStatI("AWD_HOLD_UP_SHOPS", 20, false);
		Stats::SetStatI("AWD_RACES_WON", 101, false);
		Stats::SetStatI("AWD_NO_ARMWRESTLING_WINS", 21, false);
		Stats::SetStatB("AWD_FMATTGANGHQ", 1, false);
		Stats::SetStatI("AWD_FMBBETWIN", 50000, false);
		Stats::SetStatB("AWD_FMFULLYMODDEDCAR", 1, false);
		GetRenderer()->NotifyMap("Achievements and stats unlocked");
		AUDIO::PlaySoundFrontend(-1, "NAV_UP_DOWN", "GO", 0);
	}));

	//

	addOption(ButtonOption("Unlock office money clutter")
		.addHotkey().addTranslation()
		.addTooltip("Once activated, buy some special cargo, do mission, goto warehouse, sell cargo, do mission, go back to office.")
		.addFunction([this] {
		STATS::StatSetInt(Utils::GetHashKey("MP0_LIFETIME_BUY_COMPLETE"), 1223, 0);
		STATS::StatSetInt(Utils::GetHashKey("MP0_LIFETIME_BUY_COMPLETE"), 1223, 0);
		STATS::StatSetInt(Utils::GetHashKey("MP0_LIFETIME_SELL_COMPLETE"), 434, 0);
		STATS::StatSetInt(Utils::GetHashKey("MP0_LIFETIME_SELL_UNDERTAKEN"), 434, 0);
		STATS::StatSetInt(Utils::GetHashKey("MP0_LIFETIME_CONTRA_EARNINGS"), 1220000000, 0);
		STATS::StatSetInt(Utils::GetHashKey("MP1_LIFETIME_BUY_COMPLETE"), 1223, 0);
		STATS::StatSetInt(Utils::GetHashKey("MP1_LIFETIME_BUY_COMPLETE"), 1223, 0);
		STATS::StatSetInt(Utils::GetHashKey("MP1_LIFETIME_SELL_COMPLETE"), 434, 0);
		STATS::StatSetInt(Utils::GetHashKey("MP1_LIFETIME_SELL_UNDERTAKEN"), 434, 0);
		STATS::StatSetInt(Utils::GetHashKey("MP1_LIFETIME_CONTRA_EARNINGS"), 1220000000, 0);

		GetRenderer()->NotifyMap("Office Money Stats Set");
		AUDIO::PlaySoundFrontend(-1, "NAV_UP_DOWN", "GO", 0);
	}));

	addOption(ButtonOption("Unlock biker stuff clutter")
		.addHotkey().addTranslation()
		.addTooltip("Once activated, buy stock, do mission, goto club, sell stock, do mission, go back to club.")
		.addFunction([this] {
		Stats::SetStatI("LIFETIME_BIKER_BUY_COMPLET", 1200, false);
		Stats::SetStatI("LIFETIME_BIKER_BUY_COMPLET", 1200, false);
		Stats::SetStatI("LIFETIME_BIKER_BUY_UNDERTA", 1200, false);
		Stats::SetStatI("LIFETIME_BIKER_SELL_COMPLET", 1200, false);
		Stats::SetStatI("LIFETIME_BIKER_SELL_UNDERTA", 1200, false);
		Stats::SetStatI("LIFETIME_BKR_SELL_EARNINGS0", 1200, false);

		STATS::StatSetInt(Utils::GetHashKey("LIFETIME_BIKER_BUY_COMPLET"), 1200, 0);
		STATS::StatSetInt(Utils::GetHashKey("LIFETIME_BIKER_BUY_COMPLET"), 1200, 0);
		STATS::StatSetInt(Utils::GetHashKey("LIFETIME_BIKER_BUY_UNDERTA"), 1200, 0);
		STATS::StatSetInt(Utils::GetHashKey("LIFETIME_BIKER_SELL_COMPLET"), 1200, 0);
		STATS::StatSetInt(Utils::GetHashKey("LIFETIME_BIKER_SELL_UNDERTA"), 1200, 0);
		STATS::StatSetInt(Utils::GetHashKey("LIFETIME_BKR_SELL_EARNINGS0"), 1200, 0);

			STATS::StatSetInt(Utils::GetHashKey("MP0_LIFETIME_BIKER_BUY_COMPLET"), 1200, 0);
			STATS::StatSetInt(Utils::GetHashKey("MP0_LIFETIME_BIKER_BUY_COMPLET"), 1200, 0);
			STATS::StatSetInt(Utils::GetHashKey("MP0_LIFETIME_BIKER_BUY_UNDERTA"), 1200, 0);
			STATS::StatSetInt(Utils::GetHashKey("MP0_LIFETIME_BIKER_SELL_COMPLET"), 1200, 0);
			STATS::StatSetInt(Utils::GetHashKey("MP0_LIFETIME_BIKER_SELL_UNDERTA"), 1200, 0);
			STATS::StatSetInt(Utils::GetHashKey("MP0_LIFETIME_BKR_SELL_EARNINGS0"), 1200, 0);
			STATS::StatSetInt(Utils::GetHashKey("MP1_LIFETIME_BIKER_BUY_COMPLET"), 1200, 0);
			STATS::StatSetInt(Utils::GetHashKey("MP1_LIFETIME_BIKER_BUY_COMPLET"), 1200, 0);
			STATS::StatSetInt(Utils::GetHashKey("MP1_LIFETIME_BIKER_BUY_UNDERTA"), 1200, 0);
			STATS::StatSetInt(Utils::GetHashKey("MP1_LIFETIME_BIKER_SELL_COMPLET"), 1200, 0);
			STATS::StatSetInt(Utils::GetHashKey("MP1_LIFETIME_BIKER_SELL_UNDERTA"), 1200, 0);
			STATS::StatSetInt(Utils::GetHashKey("MP1_LIFETIME_BKR_SELL_EARNINGS0"), 1200, 0);

		GetRenderer()->NotifyMap("Biker Money Stats Set");
		AUDIO::PlaySoundFrontend(-1, "NAV_UP_DOWN", "GO", 0);
	}));

	addOption(ButtonOption("Unlock high club popularity")
		.addHotkey().addTranslation()
		.addTooltip("Once activated, increase your club popularity by any amount")
		.addFunction([this] {
		STATS::StatSetInt(Utils::GetHashKey("MP0_CLUB_POPULARITY"), 1000, 1);
		STATS::StatSetInt(Utils::GetHashKey("MP1_CLUB_POPULARITY"), 1000, 1);
		GetRenderer()->NotifyMap("Club Popularity Stats Set");
		AUDIO::PlaySoundFrontend(-1, "NAV_UP_DOWN", "GO", 0);
	}));

	addOption(ButtonOption("Unlock all casino t-shirts")
		.addHotkey()
		.addFunction([] {

		for (int i = 0; i <= 18; i++) {
			Global(2573746).At(27287 + i).As<int>() = 0;
			Global(262145).At(27287 + i).As<int>() = 1;
		}

		for (int i = 0; i <= 6; i++) {
			Global(2573746).At(25998 + i).As<int>() = 0;
			Global(262145).At(25998 + i).As<int>() = 1;
		}

	})
		.addTooltip("Unlock all of the casino related t-shirts!")
		.addTranslation());

	addOption(ButtonOption("Unlock all bunker research")
		.addFunction(UnlockBunkerResearches)
		.addTooltip("This will perma unlock all bunker research")
		.addHotkey().addTranslation());

	/*addOption(ButtonOption("Unlock bunker stuff")
		.addHotkey().addTranslation()
		.addTooltip("")
		.addFunction([this] {
		char* profit = *reinterpret_cast<char**>((char*)GetModuleHandleA(NULL) + 0x2C9EB78);
		if (profit == nullptr)
			profit = *reinterpret_cast<char**>((char*)GetModuleHandleA(NULL) + 0x2C995A8);
		char* profit1 = *reinterpret_cast<char**>(profit + 0x1180);
		int* bunkerProfit = reinterpret_cast<int*>(profit1 + 0x4088);
		*bunkerProfit = 1000;
		GetRenderer()->NotifyMap("");
		AUDIO::PlaySoundFrontend(-1, "NAV_UP_DOWN", "GO", 0);
	}));*/
}

/*Update once when submenu is opened*/
void UnlocksMenu::UpdateOnce() {}

/*Update while submenu is active*/
void UnlocksMenu::Update() {}

/*Background update*/
void UnlocksMenu::FeatureUpdate() {}

/*Singleton*/
UnlocksMenu* _instance;
UnlocksMenu* UnlocksMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new UnlocksMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
UnlocksMenu::~UnlocksMenu() { delete _instance; }