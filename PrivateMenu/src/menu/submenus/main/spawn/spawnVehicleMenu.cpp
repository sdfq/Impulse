#include "stdafx.h"
#include "spawnVehicleMenu.h"
#include "vehicle/spawnVehicleSettingsMenu.h"
#include "vehicle/spawnerTypeMenu.h"
#include "../vehicle/LSCMenu.h"
#include "../spawnMenu.h"
#include "../vehicleMenu.h"
#include "menu\submenus\main\spawn\vehicle\dlcVehiclesMenu.h"
#include "manager/spawnEntityManager.h"

using namespace SpawnVehicleMenuVars;
SpawnerTypeMenu* SpawnVehicleMenu::spawnerTypeMenus[23];
namespace SpawnVehicleMenuVars {
	Vars vars;
    int vehicleSub;
    int spawn = 0;

	Vehicle SpawnVehicle(Hash model, bool spawnIn, bool spawnInvincible, bool spawnMaxed, bool deleteOld, bool spawnInAir, Color primary, Color secondary, bool blip, int spawnspeed) {
		float forward = 5.f;
		float playerHeading = ENTITY::GetEntityHeading(GetLocalPlayer().m_ped);

		float xVect = forward * sin(Utils::degToRad(playerHeading)) * -1.0f;
		float yVect = forward * cos(Utils::degToRad(playerHeading));

		Vehicle playerVeh;
		float speed = 0;
		if (STREAMING::IsModelInCdimage(model) && STREAMING::IsModelAVehicle(model)) {
			GetEntityControl()->SimpleRequestModel(model);

			if (deleteOld) {
				if (GetLocalPlayer().m_isInVehicle) {
					speed = ENTITY::GetEntitySpeed(GetLocalPlayer().m_vehicle);
					GetEntityControl()->SimpleRequestControl(GetLocalPlayer().m_vehicle);
					ENTITY::SetEntityAsMissionEntity(GetLocalPlayer().m_vehicle, 1, 1);
					Vehicle veh = GetLocalPlayer().m_vehicle;
					VEHICLE::DeleteVehicle(&veh);
				}
			}

			if (spawnIn) playerVeh = VEHICLE::CreateVehicle(model, GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, GetLocalPlayer().m_coordinates.z, playerHeading, true, true, false);
			else playerVeh = VEHICLE::CreateVehicle(model, GetLocalPlayer().m_coordinates.x + xVect, GetLocalPlayer().m_coordinates.y + yVect, GetLocalPlayer().m_coordinates.z, playerHeading, true, true, false);

			if (ENTITY::DoesEntityExist(playerVeh)) {
				VEHICLE::SetVehicleOnGroundProperly(playerVeh, 1);

				if (blip) { auto blip = HUD::AddBlipForEntity(playerVeh); HUD::SetBlipSprite(blip, 326); HUD::SetBlipColour(blip, 2); }
				if (spawnMaxed)LSCMenuVars::MaxVehicle(playerVeh);
				if (spawnInvincible)VehicleMenuVars::VehicleGodmode(playerVeh, true);

				if (!SpawnVehicleSettingsMenuVars::vars.spawndefault) {
					VEHICLE::SetVehicleCustomPrimaryColour(playerVeh, primary.m_r, primary.m_g, primary.m_b);
					VEHICLE::SetVehicleCustomSecondaryColour(playerVeh, secondary.m_r, secondary.m_g, secondary.m_b);
				}

				DECORATOR::DecorSetInt(playerVeh, "MPBitset", 0);
				VEHICLE::SetVehicleIsStolen(playerVeh, false);
				if (spawnIn)PED::SetPedIntoVehicle(GetLocalPlayer().m_ped, playerVeh, -1);

				VEHICLE::SetVehicleDirtLevel(playerVeh, 0);

				AUDIO::SetVehRadioStation(playerVeh, "OFF");

				if (spawnInAir && VEHICLE::IsThisModelAPlane(model) || VEHICLE::IsThisModelAHeli(model)) {
					Vector3 coords = ENTITY::GetEntityCoords(playerVeh, 1);
					ENTITY::SetEntityCoords(playerVeh, coords.x, coords.y, coords.z + SpawnVehicleSettingsMenuVars::vars.spawnheight, 0, 0, 0, 0);
					VEHICLE::SetVehicleEngineOn(playerVeh, true, true, false);
					VEHICLE::SetHeliBladesFullSpeed(playerVeh);
				}

				if (spawnIn) VEHICLE::SetVehicleForwardSpeed(playerVeh, speed + spawnspeed);

				/*if (SpawnVehicleSettingsMenuVars::vars.fade) {
					NETWORK::NetworkFadeInEntity(playerVeh, 0, 1);
				}*/

				if (SpawnVehicleSettingsMenuVars::vars.particles) {
					Vector3 coords = ENTITY::GetEntityCoords(playerVeh, 1);
					STREAMING::RequestNamedPtfxAsset("proj_indep_firework_v2");
					GRAPHICS::_UseParticleFxAssetNextCall("proj_indep_firework_v2");
					GRAPHICS::_StartParticleFxNonLoopedAtCoord2("scr_firework_indep_repeat_burst_rwb", coords.x, coords.y, coords.z, 0, 0, 0, 2.2, 1, 1, 1);
				}

				for (int i = 0; i < 500; i++) {
					if (!SpawnEntityManagerMenuVars::Spawned[i].m_taken) {
						SpawnEntityManagerMenuVars::Spawned[i].m_taken = true;
						SpawnEntityManagerMenuVars::Spawned[i].m_address = PoolManager::GetEntityAddress(playerVeh);
						SpawnEntityManagerMenuVars::Spawned[i].m_frozen = false;
						SpawnEntityManagerMenuVars::Spawned[i].m_godmode = spawnInvincible;
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

				AUDIO::PlaySoundFrontend(-1, "Drill_Pin_Break", "DLC_HEIST_FLEECA_SOUNDSET", 0);
			}
		} else {
			LOG_PRINT("Model not valid");
		}

		return playerVeh;
	}

	uint64_t NumericStringAsInt64(const char *hex) {
		char *_ = 0;
		__int64 ret = _strtoui64(hex, &_, 0);
		return ret;
	}

    Vehicle SpawnVehicle(String toSpawn, bool spawnIn, bool spawnInvincible, bool spawnMaxed, bool deleteOld, bool spawnInAir, Color primary, Color secondary, bool blip, int spawnspeed) {
		if (toSpawn[0] == '0' && toSpawn[1] == 'x') {
			return SpawnVehicle(NumericStringAsInt64(toSpawn), spawnIn, spawnInvincible, spawnMaxed, deleteOld, spawnInAir, primary, secondary, blip, spawnspeed);
		} else {
			return SpawnVehicle(Utils::GetHashKey(toSpawn), spawnIn, spawnInvincible, spawnMaxed, deleteOld, spawnInAir, primary, secondary, blip, spawnspeed);
		}
    }


    Vehicle SpawnVehicle(String toSpawn) {
        return SpawnVehicle(toSpawn, SpawnVehicleSettingsMenuVars::vars.spawnin, SpawnVehicleSettingsMenuVars::vars.spawninvincible, SpawnVehicleSettingsMenuVars::vars.spawnmaxed, SpawnVehicleSettingsMenuVars::vars.deleteold, SpawnVehicleSettingsMenuVars::vars.spawninair, SpawnVehicleSettingsMenuVars::vars.dprimary, SpawnVehicleSettingsMenuVars::vars.dsecondary, SpawnVehicleSettingsMenuVars::vars.blip, SpawnVehicleSettingsMenuVars::vars.spawnspeed);
    }

    Vehicle SpawnVehicle(Hash model) {
        return SpawnVehicle(model, SpawnVehicleSettingsMenuVars::vars.spawnin, SpawnVehicleSettingsMenuVars::vars.spawninvincible, SpawnVehicleSettingsMenuVars::vars.spawnmaxed, SpawnVehicleSettingsMenuVars::vars.deleteold, SpawnVehicleSettingsMenuVars::vars.spawninair, SpawnVehicleSettingsMenuVars::vars.dprimary, SpawnVehicleSettingsMenuVars::vars.dsecondary, SpawnVehicleSettingsMenuVars::vars.blip, SpawnVehicleSettingsMenuVars::vars.spawnspeed);
    }

    Vehicle SpawnVehiclePlayer(Hash model, int id, bool godmode) {
        SPlayer& player = GetPlayer(id);
        if (STREAMING::IsModelInCdimage(model) && STREAMING::IsModelAVehicle(model)) {
            GetEntityControl()->SimpleRequestModel(model);
            auto playerVeh = VEHICLE::CreateVehicle(model, player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 1, true, true, true);
            DECORATOR::DecorSetInt(playerVeh, "MPBitset", 0);
			if (godmode) ENTITY::SetEntityInvincible(playerVeh, godmode);
			return playerVeh;
        }
		return 0;
    }

    SpawnerTypeMenu* GetVehicleSub() {
        return SpawnVehicleMenu::spawnerTypeMenus[vehicleSub];
    }
}

void SpawnVehicleMenu::addSpawner(int num, String name, String* vehicles, int size) {
    spawnerTypeMenus[num] = new SpawnerTypeMenu(name, vehicles, size);
    spawnerTypeMenus[num]->setParentSubmenu<SpawnVehicleMenu>();
    GetSubmenuHandler()->addSubmenu(spawnerTypeMenus[num]);
    vehicleSub = num;
    addOption(SubmenuOption(name).addTranslation()
        .addSubmenu(spawnerTypeMenus[num])
        .addTooltip(name).addHotkey());
}

void SpawnVehicleMenu::Init() {
    setParentSubmenu<SpawnMenu>();
	MapVehicles(vars.m_map);

    setName("Spawn vehicle", true, true);

    addOption(SubmenuOption("Spawner settings")
        .addTooltip("Spawner settings")
        .addHotkey().addTranslation()
        .addSubmenu<SpawnVehicleSettingsMenu>().addTranslation());

    addOption(SubmenuOption("Manage spawned vehicles")
        .addSubmenu<SpawnEntityManagerMenu>()
        .addFunction([] { SpawnEntityManagerMenu::GetInstance()->setParentSubmenu<SpawnVehicleMenu>(); })
        .addTooltip("Manage the vehicles you've spawned").addTranslation());

    addOption(ButtonOption("Input vehicle name")
        .addFunction([] {
        GetMenuInput()->AddToQueue([] {
            string temp;
            if (GetMenuInput()->Text("Vehicle name", temp, 2, 15)) {
                SpawnVehicle(temp.c_str());
            }});
    })
        .addHotkey().addTranslation()
        .addTooltip("Input vehicle name"));

    addOption(BreakOption("Vehicles").addTranslation());

    addOption(SubmenuOption("DLC vehicles only")
        .addSubmenu<DLCVehicleMenu>().addHotkey()
        //.addFunction([] { DLCVehicleMenu::GetInstance()->setParentSubmenu<SpawnVehicleMenu>(); })
        .addTooltip("Pick only vehicles from DLC").addTranslation());

    addSpawner(spawn++, "Super", super, NUMOF(super));
    addSpawner(spawn++, "Sport", sports, NUMOF(sports));
    addSpawner(spawn++, "Sports classic", sportsclassic, NUMOF(sportsclassic));
    addSpawner(spawn++, "Off road", offroad, NUMOF(offroad));
    addSpawner(spawn++, "Sedan", sedans, NUMOF(sedans));
    addSpawner(spawn++, "SUV", suv, NUMOF(suv));
    addSpawner(spawn++, "Coupe", coupes, NUMOF(coupes));
    addSpawner(spawn++, "Muscle", muscle, NUMOF(muscle));
    addSpawner(spawn++, "Compact", compacts, NUMOF(compacts));
    addSpawner(spawn++, "Van", van, NUMOF(van));
    addSpawner(spawn++, "Commercial", commercial, NUMOF(commercial));
    addSpawner(spawn++, "Industrial", industrial, NUMOF(industrial));
    addSpawner(spawn++, "Military", military, NUMOF(military));
    addSpawner(spawn++, "Service", service, NUMOF(service));
    addSpawner(spawn++, "Emergency", emergency, NUMOF(emergency));
    addOption(BreakOption("Bikes").addTranslation());
    addSpawner(spawn++, "Motorcycle", motorcycles, NUMOF(motorcycles));
    addSpawner(spawn++, "Cycle", cycles, NUMOF(cycles));
    addOption(BreakOption("Flying").addTranslation());
    addSpawner(spawn++, "Planes", planes, NUMOF(planes));
    addSpawner(spawn++, "Helicopters", helicopters, NUMOF(helicopters));
    addOption(BreakOption("Boats").addTranslation());
    addSpawner(spawn++, "Boats", boats, NUMOF(boats));
    addOption(BreakOption("Misc").addTranslation());
    addSpawner(spawn++, "Trains", trains, NUMOF(trains));
    addSpawner(spawn++, "Trailer", trailer, NUMOF(trailer));
    addSpawner(spawn, "Utility", utility, NUMOF(utility));
}

/*Update once when submenu is opened*/
void SpawnVehicleMenu::UpdateOnce() {}

/*Update while submenu is active*/
void SpawnVehicleMenu::Update() {}

/*Background update*/
void SpawnVehicleMenu::FeatureUpdate() {}

/*Singleton*/
SpawnVehicleMenu* _instance;
SpawnVehicleMenu* SpawnVehicleMenu::GetInstance() {
    if (_instance == nullptr) {
        _instance = new SpawnVehicleMenu();
        _instance->Init();
        GetSubmenuHandler()->addSubmenu(_instance);
    }
    return _instance;
}

SpawnVehicleMenu::~SpawnVehicleMenu() {
    for (int i = 0; i < spawn; i++) delete spawnerTypeMenus[i];
    delete _instance;
}
