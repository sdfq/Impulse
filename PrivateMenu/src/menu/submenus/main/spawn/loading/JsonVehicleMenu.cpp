#include "stdafx.h"
#include "JsonVehicleMenu.h"
#include "../loadingMenu.h"
#include "../../vehicleMenu.h"
#include "../../spawn/vehicle/spawnVehicleSettingsMenu.h"
#include "menu/submenus/main/spawn/manager/spawnEntityManager.h"

using namespace JsonVehicleMenuVars;

namespace JsonVehicleMenuVars {
	vector<string> m_vehicleFiles;

	shared_ptr<ButtonOption> m_addVehiclesButton;

	void LoadVehicle(String fileName) {
		using namespace SpawnVehicleSettingsMenuVars;
		try {
			ifstream i(va("%s/%s.json", GetConfig()->GetVehiclesPath(), fileName));
			json jsonOb;
			i >> jsonOb;
			DWORD model = jsonGet<DWORD>(jsonOb["Vehicle"], "ModelHash", 0);
			if (model == 0) return;
			if (STREAMING::IsModelInCdimage(model) && STREAMING::IsModelAVehicle(model)) {
				GetEntityControl()->RequestModel(model, [jsonOb](int model) {
					json jsonObj = jsonOb;
					float forward = 5.f;
					Ped playerPed = GetLocalPlayer().m_ped;
					Vector3 playerPos = GetLocalPlayer().m_coordinates;
					float playerHeading = GetLocalPlayer().m_heading;

					float xVect = forward * sin(Utils::degToRad(playerHeading)) * -1.0f;
					float yVect = forward * cos(Utils::degToRad(playerHeading));

					Vehicle playerVeh;
					float speed = 0;
					if (vars.deleteold) {
						if (GetLocalPlayer().m_isInVehicle) {
							speed = ENTITY::GetEntitySpeed(GetLocalPlayer().m_vehicle);
							GetEntityControl()->SimpleRequestControl(GetLocalPlayer().m_vehicle);
							ENTITY::SetEntityAsMissionEntity(GetLocalPlayer().m_vehicle, 1, 1);
							Vehicle veh = GetLocalPlayer().m_vehicle;
							VEHICLE::DeleteVehicle(&veh);
						}
					}
					if (vars.spawnin) playerVeh = VEHICLE::CreateVehicle(model, GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, GetLocalPlayer().m_coordinates.z, playerHeading, true, true, true);
					else playerVeh = VEHICLE::CreateVehicle(model, GetLocalPlayer().m_coordinates.x + xVect, GetLocalPlayer().m_coordinates.y + yVect, GetLocalPlayer().m_coordinates.z, playerHeading, true, true, true);
					VEHICLE::SetVehicleOnGroundProperly(playerVeh, 1);
					VEHICLE::SetVehicleModKit(playerVeh, 0);
					//if (vars.spawninvincible)VehicleMenuVars::VehicleGodmode(playerVeh, true);

					if (vars.spawnin) VEHICLE::SetVehicleForwardSpeed(playerVeh, vars.spawnspeed);

					DECORATOR::DecorSetInt(playerVeh, "MPBitset", 0);

					bool isPrimaryCustom = jsonGet<bool>(jsonObj["Vehicle"]["VehicleProperties"]["Colors"], "IsPrimaryCustom", true);
					bool isSecondaryCustom = jsonGet<bool>(jsonObj["Vehicle"]["VehicleProperties"]["Colors"], "IsSecondaryCustom", true);


					int primary = jsonGet<int>(jsonObj["Vehicle"]["VehicleProperties"]["Colors"], "Primary", 1);
					int secondary = jsonGet<int>(jsonObj["Vehicle"]["VehicleProperties"]["Colors"], "Primary", 1);

					if (!isPrimaryCustom || !isSecondaryCustom) {
						VEHICLE::SetVehicleColours(playerVeh, jsonOb["Vehicle"]["VehicleProperties"]["Colors"]["Primary"], jsonOb["Vehicle"]["VehicleProperties"]["Colors"]["Secondary"]);
					}

					if (isPrimaryCustom) {
						int r = jsonGet<int>(jsonObj["Vehicle"]["VehicleProperties"]["Colors"]["CPrimary"], "r", 0);
						int g = jsonGet<int>(jsonObj["Vehicle"]["VehicleProperties"]["Colors"]["CPrimary"], "g", 0);
						int b = jsonGet<int>(jsonObj["Vehicle"]["VehicleProperties"]["Colors"]["CPrimary"], "b", 0);
						VEHICLE::SetVehicleCustomPrimaryColour(playerVeh, r, g, b);
					}

					if (isSecondaryCustom) {
						int r = jsonGet<int>(jsonObj["Vehicle"]["VehicleProperties"]["Colors"]["CSecondary"], "r", 0);
						int g = jsonGet<int>(jsonObj["Vehicle"]["VehicleProperties"]["Colors"]["CSecondary"], "g", 0);
						int b = jsonGet<int>(jsonObj["Vehicle"]["VehicleProperties"]["Colors"]["CSecondary"], "b", 0);
						VEHICLE::SetVehicleCustomSecondaryColour(playerVeh, r, g, b);

					}

					int pearl = jsonGet<int>(jsonObj["Vehicle"]["VehicleProperties"]["Colors"], "Pearl", 0);
					int rim = jsonGet<int>(jsonObj["Vehicle"]["VehicleProperties"]["Colors"], "Rim", 0);
					VEHICLE::SetVehicleExtraColours(playerVeh, pearl, rim);

					int livery = jsonGet<int>(jsonObj["Vehicle"]["VehicleProperties"]["Colors"], "Livery", -1);
					VEHICLE::SetVehicleLivery(playerVeh, livery);

					int tireR = jsonGet<int>(jsonObj["Vehicle"]["VehicleProperties"]["Colors"]["TyreSmoke"], "r", 0);
					int tireG = jsonGet<int>(jsonObj["Vehicle"]["VehicleProperties"]["Colors"]["TyreSmoke"], "g", 0);
					int tireB = jsonGet<int>(jsonObj["Vehicle"]["VehicleProperties"]["Colors"]["TyreSmoke"], "b", 0);
					VEHICLE::SetVehicleTyreSmokeColor(playerVeh, tireR, tireG, tireB);

					int neonCR = jsonGet<int>(jsonObj["Vehicle"]["VehicleProperties"]["Colors"]["Neon"]["Color"], "r", 0);
					int neonCG = jsonGet<int>(jsonObj["Vehicle"]["VehicleProperties"]["Colors"]["Neon"]["Color"], "g", 0);
					int neonCB = jsonGet<int>(jsonObj["Vehicle"]["VehicleProperties"]["Colors"]["Neon"]["Color"], "b", 0);
					VEHICLE::_SetVehicleNeonLightsColour(playerVeh, neonCR, neonCG, neonCB);

					bool neonL = jsonGet<bool>(jsonObj["Vehicle"]["VehicleProperties"]["Colors"]["Neon"], "Left", false);
					bool neonR = jsonGet<bool>(jsonObj["Vehicle"]["VehicleProperties"]["Colors"]["Neon"], "Right", false);
					bool neonF = jsonGet<bool>(jsonObj["Vehicle"]["VehicleProperties"]["Colors"]["Neon"], "Front", false);
					bool neonB = jsonGet<bool>(jsonObj["Vehicle"]["VehicleProperties"]["Colors"]["Neon"], "Back", false);
					VEHICLE::_SetVehicleNeonLightEnabled(playerVeh, 0, neonL);
					VEHICLE::_SetVehicleNeonLightEnabled(playerVeh, 1, neonR);
					VEHICLE::_SetVehicleNeonLightEnabled(playerVeh, 2, neonF);
					VEHICLE::_SetVehicleNeonLightEnabled(playerVeh, 3, neonB);

					int fade = jsonGet<int>(jsonObj["Vehicle"]["VehicleProperties"]["Colors"], "PaintFade", 0);
					VEHICLE::SetVehicleEnveffScale(playerVeh, fade);

					string text = jsonGet<string>(jsonObj["Vehicle"]["VehicleProperties"]["NumberPlate"], "Text", "asdf");
					int index = jsonGet<int>(jsonObj["Vehicle"]["VehicleProperties"]["NumberPlate"], "Index", 0);
					VEHICLE::SetVehicleNumberPlateText(playerVeh, text.c_str());
					VEHICLE::SetVehicleNumberPlateTextIndex(playerVeh, index);

					int wheelType = jsonGet<int>(jsonObj["Vehicle"]["VehicleProperties"], "WheelsType", 0);
					VEHICLE::SetVehicleWheelType(playerVeh, wheelType);

					int windowTint = jsonGet<int>(jsonObj["Vehicle"]["VehicleProperties"], "WindowTint", 0);
					bool bulletProofTires = jsonGet<bool>(jsonObj["Vehicle"]["VehicleProperties"], "BulletProofTires", false);
					VEHICLE::SetVehicleWindowTint(playerVeh, windowTint);
					VEHICLE::SetVehicleTyresCanBurst(playerVeh, bulletProofTires);

					float dirt = jsonGet<float>(jsonObj["Vehicle"]["VehicleProperties"], "DirtLevel", 0);
					VEHICLE::SetVehicleDirtLevel(playerVeh, dirt);

					if (vars.spawnin)PED::SetPedIntoVehicle(playerPed, playerVeh, -1);
					AUDIO::SetVehRadioStation(playerVeh, "OFF");

					bool engineRunning = jsonGet<bool>(jsonObj["Vehicle"]["VehicleProperties"], "EngineRunning", false);
					VEHICLE::SetVehicleEngineOn(playerVeh, engineRunning, engineRunning, engineRunning);

					VEHICLE::SetVehicleEngineHealth(playerVeh, jsonOb["Vehicle"]["VehicleProperties"]["EngineHealth"]);

					//Doesn't work as intended
					//VEHICLE::SetVehicleLights(playerVeh, jsonOb["Vehicle"]["VehicleProperties"]["LightsOn"]);

					for (int i = 0; i < 12; i++) {
						if (VEHICLE::DoesExtraExist(playerVeh, i)) {
							bool extra = jsonGet<bool>(jsonObj["Vehicle"]["VehicleProperties"]["Extras"], va("Extra_%d", i), false);
							VEHICLE::SetVehicleExtra(playerVeh, i, extra);
						}
					}

					for (int i = 0; i < 49; i++) {
						int val = jsonGet<int>(jsonObj["Vehicle"]["VehicleProperties"]["Mods"], va("Mod_%d", i), -1);
						if (val != -1) {
							VEHICLE::SetVehicleMod(playerVeh, i, val, 0);
						}
					}

					for (int i = 0; i < 19; i++) {
						bool TogMod = jsonGet<bool>(jsonObj["Vehicle"]["VehicleProperties"]["TogMods"], va("TogMod_%d", i), false);
						VEHICLE::ToggleVehicleMod(playerVeh, i, TogMod);
					}

						if (vars.blip) { auto blip = HUD::AddBlipForEntity(playerVeh); HUD::SetBlipSprite(blip, 326); HUD::SetBlipColour(blip, 2); }

						if (vars.spawninair && VEHICLE::IsThisModelAPlane(model) || VEHICLE::IsThisModelAHeli(model)) {
							Vector3 coords = ENTITY::GetEntityCoords(playerVeh, 1);
							ENTITY::SetEntityCoords(playerVeh, coords.x, coords.y, coords.z + SpawnVehicleSettingsMenuVars::vars.spawnheight, 0, 0, 0, 0);
							VEHICLE::SetVehicleEngineOn(playerVeh, true, true, false);
							VEHICLE::SetHeliBladesFullSpeed(playerVeh);
						}

						if (SpawnVehicleSettingsMenuVars::vars.particles) {
							Vector3 coords = ENTITY::GetEntityCoords(playerVeh, 1);
							STREAMING::RequestNamedPtfxAsset("proj_indep_firework_v2");
							GRAPHICS::_UseParticleFxAssetNextCall("proj_indep_firework_v2");
							GRAPHICS::_StartParticleFxNonLoopedAtCoord2("scr_firework_indep_repeat_burst_rwb", coords.x, coords.y, coords.z, 0, 0, 0, 2.2, 1, 1, 1);
						}

						
					//}
					AUDIO::PlaySoundFrontend(-1, "Drill_Pin_Break", "DLC_HEIST_FLEECA_SOUNDSET", 0);
					//AUDIO::PlaySoundFrontend(-1, "DLC_HEIST_FLEECA_SOUNDSET", "DLC_HEIST_FLEECA_SOUNDSET", 0);
					//GlobalVars::entityHandles.push_back(playerVeh);
					
					if (ENTITY::DoesEntityExist(playerVeh)) {
						for (int i = 0; i < 500; i++) {
							if (!SpawnEntityManagerMenuVars::Spawned[i].m_taken) {
								SpawnEntityManagerMenuVars::Spawned[i].m_taken = true;
								SpawnEntityManagerMenuVars::Spawned[i].m_address = PoolManager::GetEntityAddress(playerVeh);
								SpawnEntityManagerMenuVars::Spawned[i].m_frozen = false;
								SpawnEntityManagerMenuVars::Spawned[i].m_godmode = vars.spawninvincible;
								SpawnEntityManagerMenuVars::Spawned[i].m_handle = playerVeh;
								SpawnEntityManagerMenuVars::Spawned[i].m_model = ENTITY::GetEntityModel(playerVeh);
								SpawnEntityManagerMenuVars::Spawned[i].m_origin = ENTITY::GetEntityCoords(playerVeh, 1);
								SpawnEntityManagerMenuVars::Spawned[i].m_type = SpawnEntityManagerMenuVars::EntityTypeVehicle;
								strcpy(SpawnEntityManagerMenuVars::Spawned[i].m_name, HUD::_GetLabelText(VEHICLE::GetDisplayNameFromVehicleModel(model)));
								if (SpawnVehicleSettingsMenuVars::vars.information) {
									SpawnEntityManagerMenuVars::Spawned[i].m_creation = MISC::GetGameTimer();
									SpawnEntityManagerMenuVars::Spawned[i].m_showcreation = true;
								}
								break;
							}
						}
					}
					return playerVeh;
				});
			}
		} catch (...) {
		}
	}
}

void JsonVehicleMenu::Init() {
	setParentSubmenu<LoadingMenu>();
	setName("json vehicles", true, false);

	m_addVehiclesButton = addOption(ButtonOption("~c~Add vehicles to ./Documents/Impulse/Vehicles")
		.addTooltip("Add vehicles to ./Documents/Impulse/Vehicles").addTranslation());
}

/*Update once when submenu is opened*/
void JsonVehicleMenu::UpdateOnce() {}

/*Update while submenu is active*/
void JsonVehicleMenu::Update() {
	static int TIMER;
	static bool shouldUpdate = false;

	Utils::DoTimedFunction(&TIMER, 2500, [] {shouldUpdate = true; });
	if (shouldUpdate) {
		clearOptions();
		GetConfig()->GetFilesFromDirectory(m_vehicleFiles, GetConfig()->GetVehiclesPath(), ".json");
		if (!m_vehicleFiles.empty()) {
			for (string& vehicle : m_vehicleFiles) {
				addOption(ButtonOption(vehicle.c_str())
					.addFunction([&] {LoadVehicle(vehicle.c_str()); })
					.addTooltip(vehicle.c_str()));
			}
		} else {
			addOption(m_addVehiclesButton);
		}
		shouldUpdate = false;
	}
}

/*Background update*/
void JsonVehicleMenu::FeatureUpdate() {}

/*Singleton*/
JsonVehicleMenu* _instance;
JsonVehicleMenu* JsonVehicleMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new JsonVehicleMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
JsonVehicleMenu::~JsonVehicleMenu() { delete _instance; }