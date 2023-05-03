#include "stdafx.h"
#include "LSCMenu.h"
#include "../vehicleMenu.h"
#include "LSC/vehicleLightsMenu.h"
#include "LSC/vehiclePlatesMenu.h"
#include "LSC/vehicleResprayMenu.h"
#include "LSC/vehicleWheelsMenu.h"
#include "LSC/vehiclePerformanceMenu.h"

using namespace LSCMenuVars;

namespace LSCMenuVars {
	Vars vars;

	vector <shared_ptr<VehicleOption>> m_vehOptions;

	ScrollStruct<int> horns[] = {
		TranslationString("Stock", true), -1,
		TranslationString("Truck", true), 0,
		TranslationString("Police", true), 1,
		TranslationString("Clown", true), 2,
		TranslationString("Musical 1", true), 3,
		TranslationString("Musical 2", true), 4,
		TranslationString("Musical 3", true), 5,
		TranslationString("Musical 4", true), 6,
		TranslationString("Musical 5", true), 7,
		TranslationString("Sad trombone", true), 8,
		TranslationString("Classical 1", true), 9,
		TranslationString("Classical 2", true), 10,
		TranslationString("Classical 3", true), 11,
		TranslationString("Classical 4", true), 12,
		TranslationString("Classical 5", true), 13,
		TranslationString("Classical 6", true), 14,
		TranslationString("Classical 7", true), 15,
		//TranslationString("Classical 8", true), 32,
		TranslationString("Do", true), 16,
		TranslationString("Re", true), 17,
		TranslationString("Mi", true), 18,
		TranslationString("Fa", true), 19,
		TranslationString("Sol", true), 20,
		TranslationString("La", true), 21,
		TranslationString("Ti", true), 22,
		TranslationString("Do high", true), 23,
		TranslationString("Jazz 1", true), 24,
		TranslationString("Jazz 2", true), 25,
		TranslationString("Jazz 3", true), 26,
		TranslationString("Jazz loop", true), 27,
		TranslationString("The star-spangled banner 1", true), 28,
		TranslationString("The star-spangled banner 2", true), 29,
		TranslationString("The star-spangled banner 3", true), 30,
		TranslationString("The star-spangled banner 4", true), 31,
		TranslationString("Classical loop 1", true), 32,
		TranslationString("Classical loop 2", true), 34,
		TranslationString("Halloween loop 1", true), 38,
		TranslationString("Halloween Loop 2", true), 40,
		TranslationString("San Andreas Loop", true), 43,
		TranslationString("Liberty City Loop", true), 45,
		TranslationString("Christmas Loop 1", true), 46,
		TranslationString("Christmas Loop 2", true), 48,
		TranslationString("Christmas Loop 3", true), 50
	}, windowTints[] = {
		TranslationString("None", true), 0,
		TranslationString("Pure black", true), 1,
		TranslationString("Dark smoke", true), 2,
		TranslationString("Light smoke", true), 3,
		TranslationString("Stock", true), 4,
		TranslationString("Limo", true), 5,
		TranslationString("Green", true), 6
	};

	void MaxVehicle(Vehicle veh) {
		VEHICLE::SetVehicleModKit(veh, 0);
		VEHICLE::SetVehicleFixed(veh);
		VEHICLE::SetVehicleDirtLevel(veh, 0);
		VEHICLE::SetVehicleCustomPrimaryColour(veh, 0, 0, 0);
		VEHICLE::SetVehicleCustomSecondaryColour(veh, 0, 0, 0);
		VEHICLE::SetVehicleNumberPlateTextIndex(veh, 5);
		VEHICLE::SetVehicleTyresCanBurst(veh, false);
		VEHICLE::ToggleVehicleMod(veh, 18, 1);
		VEHICLE::ToggleVehicleMod(veh, 22, 1);
		VEHICLE::SetVehicleMod(veh, MOD_SPOILER, 1, 0);
		VEHICLE::SetVehicleMod(veh, MOD_FRONTBUMPER, 1, 0);
		VEHICLE::SetVehicleMod(veh, MOD_REARBUMPER, 1, 0);
		VEHICLE::SetVehicleMod(veh, MOD_SIDESKIRT, 1, 0);
		VEHICLE::SetVehicleMod(veh, MOD_EXHAUST, 1, 0);
		VEHICLE::SetVehicleMod(veh, MOD_CHASSIS, 1, 0);
		VEHICLE::SetVehicleMod(veh, MOD_GRILLE, 1, 0);
		VEHICLE::SetVehicleMod(veh, MOD_HOOD, 1, 0);
		VEHICLE::SetVehicleMod(veh, MOD_FENDER, 1, 0);
		VEHICLE::SetVehicleMod(veh, MOD_RIGHTFENDER, 1, 0);
		VEHICLE::SetVehicleMod(veh, MOD_ROOF, 1, 0);
		VEHICLE::SetVehicleMod(veh, MOD_ENGINE, 3, 0);
		VEHICLE::SetVehicleMod(veh, MOD_BRAKES, 2, 0);
		VEHICLE::SetVehicleMod(veh, MOD_TRANSMISSION, 2, 0);
		VEHICLE::SetVehicleMod(veh, MOD_HORNS, 3, 0);
		VEHICLE::SetVehicleMod(veh, MOD_SUSPENSION, 3, 0);
		VEHICLE::SetVehicleMod(veh, MOD_ARMOR, 5, 0);
		VEHICLE::SetVehicleMod(veh, MOD_FRONTWHEELS, 19, 1);

		VEHICLE::SetVehicleMod(veh, 0, VEHICLE::GetNumVehicleMods(veh, 0) - 1, 0);
		VEHICLE::SetVehicleMod(veh, 1, VEHICLE::GetNumVehicleMods(veh, 1) - 1, 0);
		VEHICLE::SetVehicleMod(veh, 2, VEHICLE::GetNumVehicleMods(veh, 2) - 1, 0);
		VEHICLE::SetVehicleMod(veh, 3, VEHICLE::GetNumVehicleMods(veh, 3) - 1, 0);
		VEHICLE::SetVehicleMod(veh, 4, VEHICLE::GetNumVehicleMods(veh, 4) - 1, 0);
		VEHICLE::SetVehicleMod(veh, 5, VEHICLE::GetNumVehicleMods(veh, 5) - 1, 0);
		VEHICLE::SetVehicleMod(veh, 6, VEHICLE::GetNumVehicleMods(veh, 6) - 1, 0);
		VEHICLE::SetVehicleMod(veh, 7, VEHICLE::GetNumVehicleMods(veh, 7) - 1, 0);
		VEHICLE::SetVehicleMod(veh, 8, VEHICLE::GetNumVehicleMods(veh, 8) - 1, 0);
		VEHICLE::SetVehicleMod(veh, 9, VEHICLE::GetNumVehicleMods(veh, 9) - 1, 0);
		VEHICLE::SetVehicleMod(veh, 10, VEHICLE::GetNumVehicleMods(veh, 10) - 1, 0);
		VEHICLE::SetVehicleMod(veh, 11, VEHICLE::GetNumVehicleMods(veh, 11) - 1, 0);
		VEHICLE::SetVehicleMod(veh, 12, VEHICLE::GetNumVehicleMods(veh, 12) - 1, 0);
		VEHICLE::SetVehicleMod(veh, 13, VEHICLE::GetNumVehicleMods(veh, 13) - 1, 0);
		VEHICLE::SetVehicleMod(veh, 14, VEHICLE::GetNumVehicleMods(veh, 14) - 1, 0);
		VEHICLE::SetVehicleMod(veh, 15, VEHICLE::GetNumVehicleMods(veh, 15) - 1, 0);
		VEHICLE::SetVehicleMod(veh, 16, VEHICLE::GetNumVehicleMods(veh, 16) - 1, 0);

		VEHICLE::SetVehicleMod(veh, 23, VEHICLE::GetNumVehicleMods(veh, 23) - 1, 0);
		VEHICLE::SetVehicleMod(veh, 25, VEHICLE::GetNumVehicleMods(veh, 25) - 1, 0);
		VEHICLE::SetVehicleMod(veh, 27, VEHICLE::GetNumVehicleMods(veh, 27) - 1, 0);
		VEHICLE::SetVehicleMod(veh, 28, VEHICLE::GetNumVehicleMods(veh, 28) - 1, 0);
		VEHICLE::SetVehicleMod(veh, 30, VEHICLE::GetNumVehicleMods(veh, 30) - 1, 0);
		VEHICLE::SetVehicleMod(veh, 33, VEHICLE::GetNumVehicleMods(veh, 33) - 1, 0);
		VEHICLE::SetVehicleMod(veh, 34, VEHICLE::GetNumVehicleMods(veh, 34) - 1, 0);
		VEHICLE::SetVehicleMod(veh, 35, VEHICLE::GetNumVehicleMods(veh, 35) - 1, 0);
		VEHICLE::SetVehicleMod(veh, 38, VEHICLE::GetNumVehicleMods(veh, 38) - 1, 0);

		VEHICLE::SetVehicleWheelType(veh, 7);
		VEHICLE::SetVehicleWindowTint(veh, 5);
		VEHICLE::SetVehicleModKit(veh, 0);
		VEHICLE::ToggleVehicleMod(veh, 20, 1);
		VEHICLE::SetVehicleModKit(veh, 0);

		for (int i = 0; i <= 50; i++) {
			if (VEHICLE::GetNumVehicleMods(veh, i) != 0) {
				VEHICLE::SetVehicleMod(veh, i, VEHICLE::GetNumVehicleMods(veh, i) - 1, 0);
			}
		}

		for (int i = 17; i <= 22; i++) {
			VEHICLE::ToggleVehicleMod(veh, i, true);
		} 

		RGBA temp = RGBA(MISC::GetRandomIntInRange(0, 255), MISC::GetRandomIntInRange(0, 255), MISC::GetRandomIntInRange(0, 255), 255);

		VEHICLE::SetVehicleCustomPrimaryColour(veh, temp.r, temp.g, temp.b);
		VEHICLE::SetVehicleCustomSecondaryColour(veh, temp.r, temp.g, temp.b);

		VEHICLE::_SetVehicleNeonLightEnabled(veh, 0, true);
		VEHICLE::_SetVehicleNeonLightEnabled(veh, 1, true);
		VEHICLE::_SetVehicleNeonLightEnabled(veh, 2, true);
		VEHICLE::_SetVehicleNeonLightEnabled(veh, 3, true);
		VEHICLE::_SetVehicleNeonLightsColour(veh, 255, 0, 0);

		//VEHICLE::SetVehicleNumberPlateText(veh, "Impulse");
		VEHICLE::SetVehicleTyreSmokeColor(veh, temp.r, temp.g, temp.b);
		VEHICLE::SetVehicleMod(veh, 23, 19, 1); 
	}

	void DowngradeVehicle(Vehicle veh) {
		VEHICLE::SetVehicleFixed(veh);
		VEHICLE::SetVehicleDirtLevel(veh, 15);
		VEHICLE::SetVehicleTyresCanBurst(veh, true);
		VEHICLE::SetVehicleModKit(veh, 0);

		for (int i = 0; i <= 16; i++) {
			VEHICLE::RemoveVehicleMod(veh, i);
		}

		VEHICLE::RemoveVehicleMod(veh, 14);
		VEHICLE::RemoveVehicleMod(veh, 23);

		for (int i = 17; i <= 22; i++) {
			VEHICLE::ToggleVehicleMod(veh, i, false);
		}

		VEHICLE::ClearVehicleCustomPrimaryColour(veh);
		VEHICLE::ClearVehicleCustomSecondaryColour(veh);
		VEHICLE::SetVehicleColours(veh, 135, 135);
		VEHICLE::SetVehicleExtraColours(veh, 135, 135);
		VEHICLE::SetVehicleWindowTint(veh, 0);
		VEHICLE::SetVehicleNumberPlateTextIndex(veh, 1);
	}

	string RandomLicense() {
		auto randchar = []() -> char {
			const char charset[] =
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";
			const size_t max_index = (sizeof(charset) - 1);
			return charset[rand() % max_index];
		};
		std::string str(8, 0);
		std::generate_n(str.begin(), 8, randchar);
		return str;
	}

	void RandomizeVehicle(Vehicle veh) {
		VEHICLE::SetVehicleModKit(veh, 0);
		for (int i = 0; i < 50; i++) {
			VEHICLE::SetVehicleMod(veh, i, MISC::GetRandomIntInRange(-1, VEHICLE::GetNumVehicleMods(veh, i)), false);
		}
		VEHICLE::SetVehicleColours(GetLocalPlayer().m_vehicle, MISC::GetRandomIntInRange(0, 160), MISC::GetRandomIntInRange(0, 160));
		VEHICLE::SetVehicleNumberPlateText(veh, RandomLicense().c_str());
		VEHICLE::SetVehicleNumberPlateTextIndex(veh, MISC::GetRandomIntInRange(0, 5));
		VEHICLE::SetVehicleEnveffScale(veh, MISC::GetRandomFloatInRange(0, 1));
	}
}

void LSCMenu::Init() {
	setParentSubmenu<VehicleMenu>();
	setName("Los Santos Customs", true, true);

	addOption(ButtonOption("~c~Not in a vehicle")
		.addRequirement([] {return !GetLocalPlayer().m_isInVehicle; })
		.addTooltip("Not in a vehicle").addTranslation());

	addOption(ButtonOption("Fully tune")
		.addFunction([] { GetEntityControl()->SimpleRequestControl(GetLocalPlayer().m_vehicle);  MaxVehicle(GetLocalPlayer().m_vehicle); })
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addHotkey().addTranslation()
		.addTooltip("Max vehicle"));

	addOption(ToggleOption("Loop fully tune")
		.addToggle(vars.spamFullyTune)
		.addTooltip("Spam fully tune").addTranslation().addHotkey());

	addOption(ButtonOption("Downgrade")
		.addFunction([] { GetEntityControl()->SimpleRequestControl(GetLocalPlayer().m_vehicle);  DowngradeVehicle(GetLocalPlayer().m_vehicle); })
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addHotkey().addTranslation()
		.addTooltip("Downgrade vehicle"));

	addOption(ButtonOption("Randomize vehicle look")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addFunction([] {RandomizeVehicle(GetLocalPlayer().m_vehicle); })
		.addTooltip("Randomize the look of your current vehicle").addTranslation());

	addOption(ToggleOption("Loop Randomize vehicle look")
		.addToggle(vars.spamRandomTune)
		.addTooltip("Loop Randomize vehicle").addTranslation().addHotkey());

	addOption(ButtonOption("Apply all vehicle extras").addTranslation()
		.addFunction([] {
		if (GetLocalPlayer().m_isInVehicle) {
			for (int i = 0; i < 13; i++) {
				if (VEHICLE::DoesExtraExist(GetLocalPlayer().m_vehicle, i)) {
					VEHICLE::SetVehicleModKit(GetLocalPlayer().m_vehicle, 0);
					VEHICLE::SetVehicleExtra(GetLocalPlayer().m_vehicle, i, true);
				}
			}
		}
	})
		.addHotkey().addTooltip("This will toggle all extra vehicle parts."));

	addOption(ButtonOption("Remove all vehicle extras").addTranslation()
		.addFunction([] {
		if (GetLocalPlayer().m_isInVehicle) {
			for (int i = 0; i < 13; i++) {
				if (VEHICLE::DoesExtraExist(GetLocalPlayer().m_vehicle, i)) {
					VEHICLE::SetVehicleModKit(GetLocalPlayer().m_vehicle, 0);
					VEHICLE::SetVehicleExtra(GetLocalPlayer().m_vehicle, i, false);
				}
			}
		}
	})
		.addHotkey().addTooltip("This will toggle all extra vehicle parts."));

	addOption(BreakOption()
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; }));;

	addOption(SubmenuOption("Lights")
		.addSubmenu<VehicleLightsMenu>()
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addTooltip("Edit vehicle lights").addTranslation());

	addOption(SubmenuOption("Plates")
		.addSubmenu<VehiclePlatesMenu>()
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addTooltip("Edit vehicle plates").addTranslation());

	addOption(SubmenuOption("Respray")
		.addSubmenu<VehicleResprayMenu>()
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addTooltip("Respray vehicle").addTranslation());

	addOption(SubmenuOption("Wheels")
		.addSubmenu<VehicleWheelsMenu>()
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addTooltip("Edit vehicle wheels").addTranslation());

	addOption(SubmenuOption("Performance")
		.addSubmenu<VehiclePerformanceMenu>()
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addTooltip("Edit vehicle performance").addTranslation());

	addOption(ScrollOption<int>(SCROLL, "Window tint")
		.addScroll(vars.windowtint, 0, NUMOF(windowTints) - 1, windowTints)
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addOnUpdate([] {vars.windowtint = VEHICLE::GetVehicleWindowTint(GetLocalPlayer().m_vehicle); })
		.addFunction([] {VEHICLE::SetVehicleWindowTint(GetLocalPlayer().m_vehicle, vars.windowtint); })
		.addTooltip("Edit vehicle window tint").addTranslation());

	addOption(ScrollOption<int>(SCROLL, "Horn")
		.addScroll(vars.hornIndex, 0, NUMOF(horns) - 1, horns)
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addOnUpdate([] { int horn = VEHICLE::GetVehicleMod(GetLocalPlayer().m_vehicle, MOD_HORNS); for (int i = 0; i < NUMOF(horns); i++) { if (horns[i].m_result == horn) vars.hornIndex = i; }})
		.addFunction([] { VEHICLE::SetVehicleMod(GetLocalPlayer().m_vehicle, MOD_HORNS, horns[vars.hornIndex].m_result, 0); })
		.addTooltip("Edit vehicle horn").addTranslation());

	m_vehOptions.push_back(addOption(VehicleOption("Spoiler")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_SPOILER).addTranslation()
		.addTooltip("Edit vehicle spoiler")));

	m_vehOptions.push_back(addOption(VehicleOption("Bumper front")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_FRONTBUMPER).addTranslation()
		.addTooltip("Edit vehicle bumper front")));

	m_vehOptions.push_back(addOption(VehicleOption("Bumper back")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_REARBUMPER).addTranslation()
		.addTooltip("Edit vehicle bumper back")));

	m_vehOptions.push_back(addOption(VehicleOption("Skirts")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_SIDESKIRT).addTranslation()
		.addTooltip("Edit vehicle skirts")));

	m_vehOptions.push_back(addOption(VehicleOption("Exhaust")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_EXHAUST).addTranslation()
		.addTooltip("Edit vehicle exhaust")));

	m_vehOptions.push_back(addOption(VehicleOption("Roll cage")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_CHASSIS).addTranslation()
		.addTooltip("Edit vehicle roll cage")));

	m_vehOptions.push_back(addOption(VehicleOption("Grille")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_GRILLE).addTranslation()
		.addTooltip("Edit vehicle grille")));

	m_vehOptions.push_back(addOption(VehicleOption("Hood")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_HOOD).addTranslation()
		.addTooltip("Edit vehicle hood")));

	m_vehOptions.push_back(addOption(VehicleOption("Fender")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_FENDER).addTranslation()
		.addTooltip("Edit vehicle fender")));

	m_vehOptions.push_back(addOption(VehicleOption("Right fender")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_RIGHTFENDER).addTranslation()
		.addTooltip("Edit vehicle right fender")));

	m_vehOptions.push_back(addOption(VehicleOption("Roof")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_ROOF).addTranslation()
		.addTooltip("Edit vehicle roof")));

	/*addOption(BreakOption("Benny's Edits").addTranslation()
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; }));*/

	m_vehOptions.push_back(addOption(VehicleOption("Plate holder")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_PLATEHOLDER).addTranslation()
		.addTooltip("Edit vehicle plate holder")));

	m_vehOptions.push_back(addOption(VehicleOption("Vanity plates")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_VANITY_PLATES).addTranslation()
		.addTooltip("Edit vehicle vanity plates")));

	m_vehOptions.push_back(addOption(VehicleOption("Trim")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_TRIM1).addTranslation()
		.addTooltip("Edit vehicle trim")));

	m_vehOptions.push_back(addOption(VehicleOption("Ornaments")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_ORNAMENTS).addTranslation()
		.addTooltip("Edit vehicle ornaments")));

	m_vehOptions.push_back(addOption(VehicleOption("Dashboard")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_DASHBOARD).addTranslation()
		.addTooltip("Edit vehicle dashboard")));

	m_vehOptions.push_back(addOption(VehicleOption("Dial")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_DIAL).addTranslation()
		.addTooltip("Edit vehicle dial")));

	m_vehOptions.push_back(addOption(VehicleOption("Door speaker")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_DOOR_SPEAKER).addTranslation()
		.addTooltip("Edit vehicle door speaker")));

	m_vehOptions.push_back(addOption(VehicleOption("Seats")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_SEATS).addTranslation()
		.addTooltip("Edit vehicle seats")));

	m_vehOptions.push_back(addOption(VehicleOption("Steering wheel")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_STEERINGWHEEL).addTranslation()
		.addTooltip("Edit vehicle steering wheel")));

	m_vehOptions.push_back(addOption(VehicleOption("Shift")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_SHIFTER_LEAVERS).addTranslation()
		.addTooltip("Edit vehicle shift")));

	m_vehOptions.push_back(addOption(VehicleOption("Plaques")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_PLAQUES).addTranslation()
		.addTooltip("Edit vehicle plaques")));

	m_vehOptions.push_back(addOption(VehicleOption("Speakers")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_SPEAKERS).addTranslation()
		.addTooltip("Edit vehicle speakers")));

	m_vehOptions.push_back(addOption(VehicleOption("Trunk")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_TRUNK).addTranslation()
		.addTooltip("Edit vehicle trunk")));

	m_vehOptions.push_back(addOption(VehicleOption("Hydraulics")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_HYDRULICS).addTranslation()
		.addTooltip("Edit vehicle hydraulics")));

	m_vehOptions.push_back(addOption(VehicleOption("Engine block")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_ENGINE_BLOCK).addTranslation()
		.addTooltip("Edit vehicle engine block")));

	m_vehOptions.push_back(addOption(VehicleOption("Air filter")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_AIR_FILTER).addTranslation()
		.addTooltip("Edit vehicle air filter")));

	m_vehOptions.push_back(addOption(VehicleOption("Struts")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_STRUTS).addTranslation()
		.addTooltip("Edit vehicle struts")));

	m_vehOptions.push_back(addOption(VehicleOption("Arch cover")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_ARCH_COVER).addTranslation()
		.addTooltip("Edit vehicle arch cover")));

	m_vehOptions.push_back(addOption(VehicleOption("Aerials")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_AERIALS).addTranslation()
		.addTooltip("Edit vehicle aerials")));

	m_vehOptions.push_back(addOption(VehicleOption("Trim")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_TRIM).addTranslation()
		.addTooltip("Edit vehicle trim")));

	m_vehOptions.push_back(addOption(VehicleOption("Tank")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_TANK).addTranslation()
		.addTooltip("Edit vehicle tank")));

	m_vehOptions.push_back(addOption(VehicleOption("Windows")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_WINDOWS).addTranslation()
		.addTooltip("Edit vehicle windows")));

	//m_vehOptions.push_back(addOption(VehicleOption("UNK47")
	//	.addMod(MOD_UNK47)
	//	.addTooltip("UNK47")));

	m_vehOptions.push_back(addOption(VehicleOption("Livery")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMod(MOD_LIVERY)
		.addTooltip("Livery").addTranslation().addHotkey()));
}

/*Update once when submenu is opened*/
void LSCMenu::UpdateOnce() {}

/*Update while submenu is active*/
void LSCMenu::Update() {
	if (!GetLocalPlayer().m_isInVehicle) {
		GetMenu()->ResetCurrentOption();
		return;
	}

	VEHICLE::SetVehicleModKit(GetLocalPlayer().m_vehicle, 0);
	for (auto& a : m_vehOptions) {
		a->checkVisibility();
	}
}

/*Background update*/
void LSCMenu::FeatureUpdate() {
	if (GetLocalPlayer().m_isInVehicle) {
		if (vars.spamFullyTune) {
			static int TIMER;
			Utils::DoTimedFunction(&TIMER, 500, [] {
				GetEntityControl()->SimpleRequestControl(GetLocalPlayer().m_vehicle);
				MaxVehicle(GetLocalPlayer().m_vehicle);
			});
		}

		if (vars.spamRandomTune) {
			static int TIMER;
			Utils::DoTimedFunction(&TIMER, 500, [] {
				GetEntityControl()->SimpleRequestControl(GetLocalPlayer().m_vehicle);
				RandomizeVehicle(GetLocalPlayer().m_vehicle);
			});
		}
	}
}

/*Singleton*/
LSCMenu* _instance;
LSCMenu* LSCMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new LSCMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
LSCMenu::~LSCMenu() { delete _instance; }