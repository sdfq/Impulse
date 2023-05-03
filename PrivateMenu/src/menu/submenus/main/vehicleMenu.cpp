#include "stdafx.h"
#include "vehicleMenu.h"
#include "vehicle/vehicleAcrobaticsMenu.h"
#include "vehicle/vehicleParticlesMenu.h"
#include "vehicle/vehicleMovementMenu.h"
#include "vehicle/vehicleWeaponsMenu.h"
#include "vehicle/cargobobMenu.h"
#include "vehicle/handlingMenu.h"
#include "vehicle/rampsMenu.h"
#include "vehicle/LSCMenu.h"
#include "vehicle/doorsMenu.h"
#include "vehicle/vehicleMultipliers.h"
#include "settingsMenu.h"
#include "../mainMenu.h"
#include "menu/submenus/main/miscMenu.h"

using namespace VehicleMenuVars;

void PaintFader(RGBA* rgbs, RGBA origin) {
	switch (rgbs->a) {
	case 0:
		rgbs->r = origin.r;
		rgbs->g = origin.g;
		rgbs->b = origin.b;
		rgbs->a++;
		break;
	case 1:
		rgbs->g++;
		if (rgbs->g == 255)
			rgbs->a++;
		break;
	case 2:
		rgbs->r--;
		if (rgbs->r == 0)
			rgbs->a++;
		break;
	case 3:
		rgbs->b++;
		if (rgbs->b == 255)
			rgbs->a++;
		break;
	case 4:
		rgbs->g--;
		if (rgbs->g == 0)
			rgbs->a++;
		break;
	case 5:
		rgbs->r++;
		if (rgbs->r == 255)
			rgbs->a++;
		break;
	case 6:
		rgbs->b--;
		if (rgbs->b == 0)
			rgbs->a = 0;
		break;
	}
};

namespace VehicleMenuVars {
	Vars vars;

	void SaveVehicle(String fileName) {
		ofstream i(fileName);
		Vehicle pedVeh = GetLocalPlayer().m_vehicle;
		json jsonOb;
		jsonOb["Vehicle"]["ModelHash"] = ENTITY::GetEntityModel(pedVeh);

		jsonOb["Vehicle"]["VehicleProperties"]["Colors"]["IsPrimaryCustom"] = VEHICLE::GetIsVehiclePrimaryColourCustom(pedVeh);
		jsonOb["Vehicle"]["VehicleProperties"]["Colors"]["IsSecondaryCustom"] = VEHICLE::GetIsVehicleSecondaryColourCustom(pedVeh);

		int prim, sec;
		VEHICLE::GetVehicleColours(pedVeh, &prim, &sec);
		jsonOb["Vehicle"]["VehicleProperties"]["Colors"]["Primary"] = prim;
		jsonOb["Vehicle"]["VehicleProperties"]["Colors"]["Secondary"] = sec;

		int r, g, b;
		VEHICLE::GetVehicleCustomPrimaryColour(pedVeh, &r, &g, &b);
		jsonOb["Vehicle"]["VehicleProperties"]["Colors"]["CPrimary"]["r"] = r;
		jsonOb["Vehicle"]["VehicleProperties"]["Colors"]["CPrimary"]["g"] = g;
		jsonOb["Vehicle"]["VehicleProperties"]["Colors"]["CPrimary"]["b"] = b;
		VEHICLE::GetVehicleCustomSecondaryColour(pedVeh, &r, &g, &b);
		jsonOb["Vehicle"]["VehicleProperties"]["Colors"]["CSecondary"]["r"] = r;
		jsonOb["Vehicle"]["VehicleProperties"]["Colors"]["CSecondary"]["g"] = g;
		jsonOb["Vehicle"]["VehicleProperties"]["Colors"]["CSecondary"]["b"] = b;

		int pearl, rim;
		VEHICLE::GetVehicleExtraColours(pedVeh, &pearl, &rim);
		jsonOb["Vehicle"]["VehicleProperties"]["Colors"]["Pearl"] = pearl;
		jsonOb["Vehicle"]["VehicleProperties"]["Colors"]["Rim"] = rim;

		jsonOb["Vehicle"]["VehicleProperties"]["Colors"]["Livery"] = VEHICLE::GetVehicleLivery(pedVeh);

		VEHICLE::GetVehicleTyreSmokeColor(pedVeh, &r, &g, &b);
		jsonOb["Vehicle"]["VehicleProperties"]["Colors"]["TyreSmoke"]["r"] = r;
		jsonOb["Vehicle"]["VehicleProperties"]["Colors"]["TyreSmoke"]["g"] = g;
		jsonOb["Vehicle"]["VehicleProperties"]["Colors"]["TyreSmoke"]["b"] = b;

		VEHICLE::_GetVehicleNeonLightsColour(pedVeh, &r, &g, &b);
		jsonOb["Vehicle"]["VehicleProperties"]["Colors"]["Neon"]["Color"]["r"] = r;
		jsonOb["Vehicle"]["VehicleProperties"]["Colors"]["Neon"]["Color"]["g"] = g;
		jsonOb["Vehicle"]["VehicleProperties"]["Colors"]["Neon"]["Color"]["b"] = b;

		jsonOb["Vehicle"]["VehicleProperties"]["Colors"]["Neon"]["Left"] = VEHICLE::_IsVehicleNeonLightEnabled(pedVeh, 0);
		jsonOb["Vehicle"]["VehicleProperties"]["Colors"]["Neon"]["Right"] = VEHICLE::_IsVehicleNeonLightEnabled(pedVeh, 1);
		jsonOb["Vehicle"]["VehicleProperties"]["Colors"]["Neon"]["Front"] = VEHICLE::_IsVehicleNeonLightEnabled(pedVeh, 2);
		jsonOb["Vehicle"]["VehicleProperties"]["Colors"]["Neon"]["Back"] = VEHICLE::_IsVehicleNeonLightEnabled(pedVeh, 3);

		jsonOb["Vehicle"]["VehicleProperties"]["Colors"]["PaintFade"] = VEHICLE::GetVehicleEnveffScale(pedVeh);

		jsonOb["Vehicle"]["VehicleProperties"]["NumberPlate"]["Text"] = VEHICLE::GetVehicleNumberPlateText(pedVeh);
		jsonOb["Vehicle"]["VehicleProperties"]["NumberPlate"]["Index"] = VEHICLE::GetVehicleNumberPlateTextIndex(pedVeh);

		jsonOb["Vehicle"]["VehicleProperties"]["WheelsType"] = VEHICLE::GetVehicleWheelType(pedVeh);

		jsonOb["Vehicle"]["VehicleProperties"]["WindowTint"] = VEHICLE::GetVehicleWindowTint(pedVeh);
		jsonOb["Vehicle"]["VehicleProperties"]["BulletProofTires"] = !VEHICLE::GetVehicleTyresCanBurst(pedVeh);

		jsonOb["Vehicle"]["VehicleProperties"]["DirtLevel"] = VEHICLE::GetVehicleDirtLevel(pedVeh);

		jsonOb["Vehicle"]["VehicleProperties"]["EngineRunning"] = VEHICLE::GetIsVehicleEngineRunning(pedVeh);
		jsonOb["Vehicle"]["VehicleProperties"]["EngineHealth"] = VEHICLE::GetVehicleEngineHealth(pedVeh);

		//Doesn't work as intended
		//bool lightson, highbeams;
		//jsonOb["Vehicle"]["VehicleProperties"]["LightsOn"] = VEHICLE::GetVehicleLightsState(pedVeh, &lightson, &highbeams);

		for (int i = 0; i < 12; i++) {
			if (VEHICLE::DoesExtraExist(pedVeh, i))
				jsonOb["Vehicle"]["VehicleProperties"]["Extras"][va("Extra_%d", i)] = !VEHICLE::IsVehicleExtraTurnedOn(pedVeh, i);
		}

		for (int i = 0; i < 49; i++) {
			jsonOb["Vehicle"]["VehicleProperties"]["Mods"][va("Mod_%d", i)] = VEHICLE::GetVehicleMod(pedVeh, i);
		}

		for (int i = 0; i < 19; i++) {
			jsonOb["Vehicle"]["VehicleProperties"]["TogMods"][va("TogMod_%d", i)] = VEHICLE::IsToggleModOn(pedVeh, i);
		}

		i << setw(4) << jsonOb;
		i.close();
	}

	void VehicleGodmode(Vehicle vehicle, bool toggle) {
		ENTITY::SetEntityInvincible(vehicle, toggle);
		ENTITY::SetEntityProofs(vehicle, toggle, toggle, toggle, toggle, toggle, toggle, toggle, toggle);
		VEHICLE::SetVehicleCanBeVisiblyDamaged(vehicle, !toggle);
		if (toggle) VEHICLE::SetVehicleEngineOn(vehicle, true, true, true);
	}

	void Seatbelt(bool toggle) {
		PED::SetPedCanBeKnockedOffVehicle(GetLocalPlayer().m_ped, toggle);
		//PED::SetPedConfigFlag(GetLocalPlayer().m_ped, PED_FLAG_CAN_FLY_THRU_WINDSCREEN, TRUE); //SP
	}

	void InvisibleVehicle(bool toggle) {
		if (!GetLocalPlayer().m_isInVehicle) return;
		ENTITY::SetEntityVisible(GetLocalPlayer().m_vehicle, !toggle, false);
	}

	void FixVehicle(Vehicle veh) {
		if (!GetLocalPlayer().m_isInVehicle) return;
		VEHICLE::SetVehicleFixed(veh);
		VEHICLE::SetVehicleDeformationFixed(veh);
		VEHICLE::SetVehicleDirtLevel(veh, 0);
		VEHICLE::SetVehicleEngineOn(veh, true, true, true);
		FIRE::StopEntityFire(veh);
	}

	void CloneVehicle(SPlayer player) {
		if (!player.m_isInVehicle)return;
		Ped ped = player.m_ped;
		Vehicle pedVeh = player.m_vehicle;
		Ped playerPed = GetLocalPlayer().m_ped;
		Vector3 playerPosition = GetLocalPlayer().m_coordinates;

		if (ENTITY::DoesEntityExist(pedVeh)) {
			auto const vehicleModelHash = ENTITY::GetEntityModel(pedVeh);
			GetEntityControl()->RequestModel(vehicleModelHash, [=](int model) {
				auto const playerVeh = VEHICLE::CreateVehicle(vehicleModelHash, playerPosition.x, playerPosition.y, playerPosition.z, GetLocalPlayer().m_heading, true, true, true);
				PED::SetPedIntoVehicle(playerPed, playerVeh, -1);
				DECORATOR::DecorSetInt(playerVeh, "MPBitset", 0);
				int primaryColor, secondaryColor;
				VEHICLE::GetVehicleColours(pedVeh, &primaryColor, &secondaryColor);
				VEHICLE::SetVehicleColours(playerVeh, primaryColor, secondaryColor);
				if (VEHICLE::IsThisModelACar(vehicleModelHash) || VEHICLE::IsThisModelABike(vehicleModelHash)) {
					VEHICLE::SetVehicleModKit(playerVeh, 0);
					VEHICLE::SetVehicleWheelType(playerVeh, VEHICLE::GetVehicleWheelType(pedVeh));
					for (int i = 0; i <= (int)MOD_BACKWHEELS; i++) {
						if (i > (int)MOD_ARMOR && i < (int)MOD_FRONTWHEELS)
							VEHICLE::ToggleVehicleMod(playerVeh, i, VEHICLE::IsToggleModOn(pedVeh, i));
						else
							VEHICLE::SetVehicleMod(playerVeh, i, VEHICLE::GetVehicleMod(pedVeh, i), VEHICLE::GetVehicleModVariation(pedVeh, i));
					}
					int tireSmokeColor[3], pearlescentColor, wheelColor;
					VEHICLE::GetVehicleTyreSmokeColor(pedVeh, &tireSmokeColor[0], &tireSmokeColor[1], &tireSmokeColor[2]);
					VEHICLE::SetVehicleTyreSmokeColor(playerVeh, tireSmokeColor[0], tireSmokeColor[1], tireSmokeColor[2]);
					VEHICLE::SetVehicleNumberPlateTextIndex(playerVeh, VEHICLE::GetVehicleNumberPlateTextIndex(pedVeh));
					VEHICLE::SetVehicleNumberPlateText(playerVeh, VEHICLE::GetVehicleNumberPlateText(pedVeh));
					VEHICLE::GetVehicleExtraColours(pedVeh, &pearlescentColor, &wheelColor);
					VEHICLE::SetVehicleExtraColours(playerVeh, pearlescentColor, wheelColor);
					if (VEHICLE::IsVehicleAConvertible(pedVeh, 0)) {
						auto const convertableState = VEHICLE::GetConvertibleRoofState(pedVeh);
						if (convertableState == 0 || convertableState == 3 || convertableState == 5)
							VEHICLE::RaiseConvertibleRoof(playerVeh, 1);
						else
							VEHICLE::LowerConvertibleRoof(playerVeh, 1);
					}
					for (int i = 0; i <= 3; i++) {
						VEHICLE::_SetVehicleNeonLightEnabled(playerVeh, i, VEHICLE::_IsVehicleNeonLightEnabled(pedVeh, i));
					}
					for (int i = 0; i <= 11; i++) {
						if (VEHICLE::DoesExtraExist(pedVeh, i))
							VEHICLE::SetVehicleExtra(playerVeh, i, !VEHICLE::IsVehicleExtraTurnedOn(pedVeh, i));
					}
					if ((VEHICLE::GetVehicleLiveryCount(pedVeh) > 1) && VEHICLE::GetVehicleLivery(pedVeh) >= 0) {
						VEHICLE::SetVehicleLivery(playerVeh, VEHICLE::GetVehicleLivery(pedVeh));
					}
					int neonColor[3];
					VEHICLE::_GetVehicleNeonLightsColour(pedVeh, &neonColor[0], &neonColor[1], &neonColor[2]);
					VEHICLE::_SetVehicleNeonLightsColour(playerVeh, neonColor[0], neonColor[1], neonColor[2]);
					VEHICLE::SetVehicleWindowTint(playerVeh, VEHICLE::GetVehicleWindowTint(pedVeh));
					VEHICLE::SetVehicleDirtLevel(playerVeh, VEHICLE::GetVehicleDirtLevel(pedVeh));
					AUDIO::PlaySoundFrontend(-1, "Drill_Pin_Break", "DLC_HEIST_FLEECA_SOUNDSET", 0);
				}
			});
		}
	}

	typedef struct
	{
		INT RED, GREEN, BLUE;
	} color_3;
	color_3 primary{ 255, 0, 0 }, secondary{ 0, 255, 0 };
	static bool shouldUpdate = true;
	static int currentColor = 0;
	RGBA RainbowPaintColor;
	void RainbowVehicle(Vehicle veh)
	{
		/*if (!GetLocalPlayer().m_isInVehicle) return;
		static Color color;
		const auto smoothColor2 = currentColor + 1 > 3 ? 0 : currentColor + 1;
		auto *col = &color;
		auto *col2 = &vars.colors[smoothColor2];
		if (shouldUpdate) {
			if (col->R < col2->R)
			{
				col->R += 1;
			}
			else if (col->R > col2->R)
			{
				col->R -= 1;
			}
			if (col->G < col2->G)
			{
				col->G += 1;
			}
			else if (col->G > col2->G)
			{
				col->G -= 1;
			}
			if (col->B < col2->B)
			{
				col->B += 1;
			}
			else if (col->B > col2->B)
			{
				col->B -= 1;
			}
			if (Utils::Within(col->R, col2->R - 2, col2->R + 2) &&
				Utils::Within(col->G, col2->G - 2, col2->G + 2) &&
				Utils::Within(col->B, col2->B - 2, col2->B + 2)) currentColor = currentColor + 1 > 3 ? 0 : currentColor + 1;
			shouldUpdate = false;
		}
		VEHICLE::SetVehicleCustomPrimaryColour(veh, col->R, col->G, col->B);
		VEHICLE::SetVehicleCustomSecondaryColour(veh, col->R, col->G, col->B);*/
		if (!GetLocalPlayer().m_isInVehicle) return;
		/*RGBA primaryColor;
		VEHICLE::GetVehicleCustomPrimaryColour(veh, &primaryColor.r, &primaryColor.g, &primaryColor.b);

		PaintFader(&RainbowPaintColor, primaryColor);
		VEHICLE::SetVehicleCustomPrimaryColour(veh, RainbowPaintColor.r, RainbowPaintColor.g, RainbowPaintColor.b);
		VEHICLE::SetVehicleCustomSecondaryColour(veh, RainbowPaintColor.r, RainbowPaintColor.g, RainbowPaintColor.b);*/
		Vehicle vehicle = GetLocalPlayer().m_vehicle;
		if (primary.RED > 0 && primary.BLUE == 0)
		{
			primary.RED--;
			primary.GREEN++;
		}
		if (primary.GREEN > 0 && primary.RED == 0)
		{
			primary.GREEN--;
			primary.BLUE++;
		}
		if (primary.BLUE > 0 && primary.GREEN == 0)
		{
			primary.RED++;
			primary.BLUE--;
		}
		if (secondary.RED > 0 && secondary.BLUE == 0)
		{
			secondary.RED--;
			secondary.GREEN++;
		}
		if (secondary.GREEN > 0 && secondary.RED == 0)
		{
			secondary.GREEN--;
			secondary.BLUE++;
		}
		if (secondary.BLUE > 0 && secondary.GREEN == 0)
		{
			secondary.RED++;
			secondary.BLUE--;
		}
		GetEntityControl()->SimpleRequestControl(GetLocalPlayer().m_vehicle);
		VEHICLE::SetVehicleCustomPrimaryColour(GetLocalPlayer().m_vehicle, primary.RED, primary.GREEN, primary.BLUE);
		VEHICLE::SetVehicleCustomSecondaryColour(GetLocalPlayer().m_vehicle, secondary.RED, secondary.GREEN, secondary.BLUE);

	}

	void SmokeCycle() {
		if (!GetLocalPlayer().m_isInVehicle)return;
		GetEntityControl()->SimpleRequestControl(GetLocalPlayer().m_vehicle);
		VEHICLE::ToggleVehicleMod(GetLocalPlayer().m_vehicle, 20, 1);
		VEHICLE::SetVehicleModKit(GetLocalPlayer().m_vehicle, 0);
		VEHICLE::SetVehicleTyreSmokeColor(GetLocalPlayer().m_vehicle, MISC::GetRandomIntInRange(0, 255), MISC::GetRandomIntInRange(0, 255), MISC::GetRandomIntInRange(0, 255));
	}

	void AutoFlip() {
		if (!GetLocalPlayer().m_isInVehicle)return;
		if (!ENTITY::IsEntityUpright(GetLocalPlayer().m_vehicle, 120)) {
			Vector3 rotation = ENTITY::GetEntityRotation(GetLocalPlayer().m_vehicle, false);
			ENTITY::SetEntityRotation(GetLocalPlayer().m_vehicle, 0, rotation.y, rotation.z, 0, 1);
		}
	}



	void BurnShell(bool toggle) {
		if (!GetLocalPlayer().m_isInVehicle)return;
		ENTITY::SetEntityRenderScorched(GetLocalPlayer().m_vehicle, toggle);
	}

	void FIBNumberPlate() {
		static int TIMER;
		static int increment = 0;
		static char* message = "IMPULSE IS DE WAE";

		if (!GetLocalPlayer().m_isInVehicle)return;
		Utils::DoTimedFunction(&TIMER, 500, [] {
			if (increment > strlen(message)) increment = 0;
			char temp[8];
			for (int i = 0; i < 8; i++) temp[i] = message[i + increment];
			increment++;

			VEHICLE::SetVehicleNumberPlateText(GetLocalPlayer().m_vehicle, temp);
		});
	}

	void PrintText(string text, int font, float x, float y, float scalex, float scaley, int r, int g, int b, int a, bool center, bool outline) {
		HUD::SetTextFont(font);
		HUD::SetTextScale(scalex, scaley);
		HUD::SetTextColour(r, g, b, a);
		HUD::SetTextWrap(0.0f, 1.0f);
		HUD::SetTextCentre(center);
		HUD::SetTextDropshadow(0, 0, 0, 0, 0);
		if (outline)
			HUD::SetTextOutline();
		HUD::BeginTextCommandDisplayText("STRING");
		HUD::AddTextComponentSubstringPlayerName(&text[0u]);
		HUD::EndTextCommandDisplayText(x, y, 0);
		HUD::SetTextDropshadow(0, 0, 0, 0, 0);
	}

	void OnScreenSpeedo() {
		if (!GetLocalPlayer().m_isInVehicle)return;
		float MetersPerSecond = ENTITY::GetEntitySpeed(GetLocalPlayer().m_vehicle);
		float measurement = SettingsMenuVars::measurementTypes[SettingsMenuVars::vars.measurementType].m_result;
		float Speed = MetersPerSecond * measurement;
		static float c_opacity = 1.0f;
		GetRenderer()->SetOpacityVariable(c_opacity);
		PrintText(va("%.0f %s", Speed, SettingsMenuVars::vars.measurementType == 0 ? "MPH" : "KMH"), GetRenderer()->m_textFont, 0.5f, 0.02f, 0.40f, 0.40f, MiscMenuVars::vars.Colorscreenelements.m_r, MiscMenuVars::vars.Colorscreenelements.m_g, MiscMenuVars::vars.Colorscreenelements.m_b, MiscMenuVars::vars.Colorscreenelements.m_a, 0, MiscMenuVars::vars.Outlineonscreenelements);
		//GetRenderer()->DrawString(va("%.0f %s", Speed, SettingsMenuVars::vars.measurementType == 0 ? "MPH" : "KMH"), 0.5f, 0.02f, GetRenderer()->m_textFont, 0.40f, { MiscMenuVars::vars.Colorscreenelements.m_r, MiscMenuVars::vars.Colorscreenelements.m_g, MiscMenuVars::vars.Colorscreenelements.m_b, MiscMenuVars::vars.Colorscreenelements.m_a }, MiscMenuVars::vars.Outlineonscreenelements);
	}

	void NumberPlateSpeedo() {
		if (!GetLocalPlayer().m_isInVehicle)return;
		float MetersPerSecond = ENTITY::GetEntitySpeed(GetLocalPlayer().m_vehicle);
		float measurement = SettingsMenuVars::measurementTypes[SettingsMenuVars::vars.measurementType].m_result;
		float Speed = MetersPerSecond * measurement;
		VEHICLE::SetVehicleNumberPlateText(GetLocalPlayer().m_vehicle, va("%.0f %s", Speed, SettingsMenuVars::vars.measurementType == 0 ? "MPH" : "KMH"));
	}

	void NoCollision(bool toggle) {
		if (!GetLocalPlayer().m_isInVehicle)return;
		ENTITY::SetEntityCollision(GetLocalPlayer().m_vehicle, !toggle, false);
	}

	void PhaseThroughVehicles(bool toggle) {
		if (!GetLocalPlayer().m_isInVehicle)return;
		ENTITY::SetEntityCollision(GetLocalPlayer().m_vehicle, !toggle, false);
		VEHICLE::SetVehicleOnGroundProperly(GetLocalPlayer().m_vehicle, 1);
	}

	void jumpAround() {
		static int TIMER;
		Utils::DoTimedFunction(&TIMER, 2500, [] {
			VehiclePool::Update();
		});
		static int TIMER2;
		Utils::DoTimedFunction(&TIMER, 1000, [] {
			vector<Vehicle> e = VehiclePool::GetVehicles();
			Vehicle* vehicles = &e[0];
			for (int i = 0; i < e.size(); i++) {
				Vehicle xveh = vehicles[i];
				if (!PED::IsPedAPlayer(VEHICLE::GetPedInVehicleSeat(xveh, 0, 0))) {
					if (xveh != PED::GetVehiclePedIsIn(GetLocalPlayer().m_ped, 0)) {
						GetEntityControl()->SimpleRequestControl(xveh);
						float rotx = MISC::GetRandomFloatInRange(-0.75, 0.75);
						float roty = MISC::GetRandomFloatInRange(-0.75, 0.75);
						float a = MISC::GetRandomFloatInRange(5, 6);
						if (ENTITY::IsEntityAVehicle(xveh))
							ENTITY::ApplyForceToEntity(xveh, 1, 0, 0, a, rotx, roty, 0, 0, 1, 1, 1, 0, 1);
					}
				}
			}
		});
	}

	void VehicleNuke()
	{
		static bool marked;
		static int count;
		static Vector3 store;
		Vector3 coords = GetLocalPlayer().m_coordinates;
		if (GetLocalPlayer().m_isInVehicle) {
			float g = ENTITY::GetEntityHeightAboveGround(GetLocalPlayer().m_vehicle);
			GRAPHICS::DrawMarker(28, (marked ? store.x : coords.x), (marked ? store.y : coords.y), (marked ? store.z : coords.z - g) + 1, 0, 0, 0, 99989, 99998, 0.860f, 15.000f, 15.000f, 15.000f, 0, 255, 0, 100, false, false, 0, 0, 0, 0, 0); //6
			if ((GetTickCount() - count > 150) && (KeyDown(' ') || PAD::IsDisabledControlPressed(0, INPUT_FRONTEND_LS))) {
				if (!marked) {
					store = { coords.x, coords.y, coords.z - g };
					count = GetTickCount();
					marked = true;
				}
				else {
					for (int i = 0; i < 45; i++) {
						FIRE::AddExplosion((store.x + MISC::GetRandomFloatInRange(-9, 9)), (store.y + MISC::GetRandomFloatInRange(-9, 9)), store.z, 9, 1000, 1, 0, 0, 0);
					}
					count = GetTickCount();
					marked = false;
				}
			}
		}
	}
}

void VehicleMenu::Init() {
	setParentSubmenu<MainMenu>();
	setName("Vehicle", true, true);

	addString("Not in a vehicle");
	addString("A file with that name already exists. Try again.");

	addOption(ButtonOption("Save json vehicle")
		.addFunction([this] {
		if (!GetLocalPlayer().m_isInVehicle) {
			GetRenderer()->NotifyBottom(getString("Not in a vehicle"));
			return;
		}
		GetMenuInput()->AddToQueue([this] {
			string temp;
			if (GetMenuInput()->Text("Vehicle name", temp, 2, 15)) {
				String file = va("%s/%s.json", GetConfig()->GetVehiclesPath(), temp.c_str());

				if (GetConfig()->DoesFileExist(file)) {
					GetRenderer()->NotifyBottom(getString("A file with that name already exists. Try again."));
				}
				else SaveVehicle(file);
			}});
	}).addTranslation()
		.addHotkey()
		.addTooltip("Save vehicle to json file"));

	addOption(BreakOption());

	addOption(SubmenuOption("Los Santos Customs")
		.addSubmenu<LSCMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Los Santos Customs"));

	addOption(SubmenuOption("Cargobob mods")
		.addSubmenu<CargobobMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Cargobob mods"));

	addOption(SubmenuOption("Attach ramps")
		.addSubmenu<RampsMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Attach ramps"));

	addOption(SubmenuOption("Vehicle weapons")
		.addSubmenu<VehicleWeaponsMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Vehicle weapons"));

	addOption(SubmenuOption("Vehicle movement")
		.addSubmenu<VehicleMovementMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Vehicle movement"));

	addOption(SubmenuOption("Vehicle handling")
		.addSubmenu<HandlingMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Vehicle handling data editor")
		.addRequirement([] { return GetAuth()->IsVIP(); }));

	addOption(SubmenuOption("Vehicle acrobatics")
		.addSubmenu<VehicleAcrobaticsMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Vehicle acrobatics"));

	addOption(SubmenuOption("Vehicle particles")
		.addSubmenu<VehicleParticlesMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Vehicle particles"));

	addOption(SubmenuOption("Vehicle doors")
		.addSubmenu<DoorsMenu>()
		.addTranslation().addHotkey()
		.addTooltip("Vehicle doors"));

	addOption(SubmenuOption("Vehicle multipliers")
		.addSubmenu<VehicleMultipliersMenu>()
		.addTranslation().addHotkey()
		.addTooltip("Vehicle multipliers"));

	addOption(BreakOption("General"));

	addOption(ToggleOption("Vehicle Godmode")
		.addToggle(vars.vehiclegodmode)
		.addFunction([] { VehicleGodmode(GetLocalPlayer().m_vehicle, vars.vehiclegodmode); })
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Vehicle godmode"));

	addOption(ToggleOption("Auto repair")
		.addToggle(vars.autoRepair)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Auto repair your vehicle"));

	addOption(ToggleOption("Vehicle invisibility")
		.addToggle(vars.vehicleinvisibility)
		.addFunction([] {InvisibleVehicle(vars.vehicleinvisibility); })
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Vehicle invisibility"));

	addOption(ToggleOption("Keep engine on")
		.addToggle(vars.keepEngineOn)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Keep your engine on"));

	addOption(ToggleOption("Seatbelt")
		.addToggle(vars.seatbelt).addTranslation()
		.addFunction([] {Seatbelt(vars.seatbelt); })
		.addHotkey().canBeSaved()
		.addTooltip("Player can't fall off vehicles"));

	addOption(ButtonOption("Fix vehicle")
		.addFunction([] {FixVehicle(GetLocalPlayer().m_vehicle); })
		.addHotkey().addTranslation()
		.addTooltip("Fix vehicle"));

	addOption(ButtonOption("Delete vehicle")
		.addFunction([] {GetEntityControl()->DeleteEntity(GetLocalPlayer().m_vehicle); })
		.addHotkey().addTranslation()
		.addTooltip("Delete vehicle"));

	addOption(BreakOption("Modify Vehicle"));

	addOption(ToggleOption("Auto flip")
		.addToggle(vars.autoflip)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Automatically flip your vehicle upright"));

	addOption(ToggleOption("Vehicle no collisions")
		.addToggle(vars.nocollision)
		.addFunction([] {NoCollision(vars.nocollision); })
		.addHotkey().canBeSaved()
		.addTooltip("Vehicle nocollision").addTranslation());

	addOption(ToggleOption("Phase through vehicles")
		.addToggle(vars.phasethroughvehicles)
		.addFunction([] {PhaseThroughVehicles(vars.nocollision); })
		.addHotkey().canBeSaved()
		.addTooltip("Phase through vehicles").addTranslation());

	addOption(ButtonOption("Ground to earth")
		.addFunction([] {VEHICLE::SetVehicleOnGroundProperly(GetLocalPlayer().m_vehicle, 1); })
		.addHotkey().addTranslation()
		.addTooltip("Ground to earth"));

	addOption(BreakOption("Misc"));

	addOption(ButtonOption("Clone vehicle")
		.addFunction([] {CloneVehicle(GetLocalPlayer()); })
		.addHotkey().addTranslation()
		.addTooltip("Clone vehicle"));

	addOption(ToggleOption("Vehicle nuke")
		.addToggle(vars.vehiclenuke)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Press Spacebar or LS on Controller to set a blast zone and then press again to nuke area")
		.addRequirement([] { return GetAuth()->IsVIP(); }));

	addOption(BreakOption("Visuals").addTranslation());

	addOption(ToggleOption("FIB numberplate")
		.addToggle(vars.fibnumberplate)
		.addHotkey().canBeSaved()
		.addTooltip("FIB numberplate").addTranslation());

	addOption(ToggleOption("Onscreen speedometer")
		.addToggle(vars.onscreenspeedo)
		.addHotkey().canBeSaved()
		.addTooltip("Onscreen speedometer").addTranslation());

	addOption(ToggleOption("Numberplate speedometer")
		.addToggle(vars.numberplatespeedo)
		.addHotkey().canBeSaved()
		.addTooltip("Numberplate speedometer").addTranslation());

	addOption(ToggleOption("Rainbow paint")
		.addToggle(vars.rainbow)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Rainbow paint"));

	addOption(ToggleOption("Wheel smoke cycle")
		.addToggle(vars.smokecycle)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Wheel smoke cycle"));

	addOption(ButtonOption("Wash")
		.addFunction([] {VEHICLE::SetVehicleDirtLevel(GetLocalPlayer().m_vehicle, 0); })
		.addHotkey().addTranslation()
		.addTooltip("Clean vehicle"));

	addOption(ButtonOption("Dirty")
		.addFunction([] {VEHICLE::SetVehicleDirtLevel(GetLocalPlayer().m_vehicle, 15.0f); })
		.addHotkey().addTranslation()
		.addTooltip("Make vehicle dirty"));

	addOption(ToggleOption("Burn vehicle shell")
		.addToggle(vars.burnshell)
		.addFunction([] {BurnShell(vars.burnshell); })
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Burn vehicle shell"));

	addOption(NumberOption<int>(SCROLL, "Opacity")
		.addNumber(vars.opacity, "%d", 1).addMin(0).addMax(100).setScrollSpeed(20)
		.addFunction([&] {ENTITY::SetEntityAlpha(GetLocalPlayer().m_vehicle, 255 - (vars.opacity *2.55f), false); })
		.addTooltip("Set player opacity (local only)").addTranslation());

}

/*Update once when submenu is opened*/
void VehicleMenu::UpdateOnce() {}

/*Update while submenu is active*/
void VehicleMenu::Update() {}

/*Background update*/
void VehicleMenu::FeatureUpdate() {
	if (vars.vehiclegodmode) VehicleGodmode(GetLocalPlayer().m_vehicle, true);
	if (vars.seatbelt)Seatbelt(vars.seatbelt);
	if (vars.vehicleinvisibility) InvisibleVehicle(true);
	if (vars.rainbow) RainbowVehicle(GetLocalPlayer().m_vehicle);
	if (vars.smokecycle) SmokeCycle();
	if (vars.autoflip) AutoFlip();
	if (vars.burnshell) BurnShell(true);
	if (vars.fibnumberplate) FIBNumberPlate();
	if (vars.onscreenspeedo) OnScreenSpeedo();
	if (vars.numberplatespeedo) NumberPlateSpeedo();
	if (vars.nocollision) NoCollision(true);
	if (vars.phasethroughvehicles) PhaseThroughVehicles(true);
	if (vars.vehiclenuke) VehicleNuke();
	if (vars.jumparoundmode) jumpAround();
	if (vars.keepEngineOn) {
		VEHICLE::SetVehicleEngineOn(GetLocalPlayer().m_vehicle, 1, 1, 1);
		VEHICLE::SetVehicleLights(GetLocalPlayer().m_vehicle, 0);
	}
	if (vars.autoRepair) {
		if (VEHICLE::_IsVehicleDamaged(GetLocalPlayer().m_vehicle)) {
			VEHICLE::SetVehicleFixed(GetLocalPlayer().m_vehicle);
		}
	}
}

/*Singleton*/
VehicleMenu* _instance;
VehicleMenu* VehicleMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new VehicleMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
VehicleMenu::~VehicleMenu() { delete _instance; }