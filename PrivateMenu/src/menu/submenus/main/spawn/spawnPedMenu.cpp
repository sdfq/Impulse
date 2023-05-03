#include "stdafx.h"
#include "spawnPedMenu.h"
#include "ped/spawnPedSettingsMenu.h"
#include "../spawnMenu.h"
#include "../local/modelMenu.h"
#include "manager/spawnEntityManager.h"

using namespace SpawnPedMenuVars;

namespace SpawnPedMenuVars {
	Ped SpawnPed(String toSpawn, bool godmode, bool blip) {
		DWORD model = Utils::GetHashKey(toSpawn);
		Ped ped;
		if (STREAMING::IsModelInCdimage(model)) {
			GetEntityControl()->SimpleRequestModel(model);
			ped = PED::CreatePed(21, model, GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, GetLocalPlayer().m_coordinates.z, 0, 1, 0);
			ENTITY::SetEntityInvincible(ped, godmode);
			if (blip) { auto blip = HUD::AddBlipForEntity(ped); HUD::SetBlipSprite(blip, 366); HUD::SetBlipColour(blip, 3); }

			if (SpawnPedSettingsMenuVars::vars.particles) {
				Vector3 coords = ENTITY::GetEntityCoords(ped, 1);
				STREAMING::RequestNamedPtfxAsset("proj_indep_firework_v2");
				GRAPHICS::_UseParticleFxAssetNextCall("proj_indep_firework_v2");
				GRAPHICS::_StartParticleFxNonLoopedAtCoord2("scr_firework_indep_repeat_burst_rwb", coords.x, coords.y, coords.z, 0, 0, 0, 2.2, 1, 1, 1);
			}

		}
		AUDIO::PlaySoundFrontend(-1, "Drill_Pin_Break", "DLC_HEIST_FLEECA_SOUNDSET", 0);

		if (ENTITY::DoesEntityExist(ped)) {
			for (int i = 0; i < 500; i++) {
				if (!SpawnEntityManagerMenuVars::Spawned[i].m_taken) {
					SpawnEntityManagerMenuVars::Spawned[i].m_taken = true;
					SpawnEntityManagerMenuVars::Spawned[i].m_address = PoolManager::GetEntityAddress(ped);
					SpawnEntityManagerMenuVars::Spawned[i].m_frozen = false;
					SpawnEntityManagerMenuVars::Spawned[i].m_godmode = godmode;
					SpawnEntityManagerMenuVars::Spawned[i].m_handle = ped;
					SpawnEntityManagerMenuVars::Spawned[i].m_model = ENTITY::GetEntityModel(ped);
					SpawnEntityManagerMenuVars::Spawned[i].m_origin = ENTITY::GetEntityCoords(ped, 1);
					SpawnEntityManagerMenuVars::Spawned[i].m_type = SpawnEntityManagerMenuVars::EntityTypePed;
					strcpy(SpawnEntityManagerMenuVars::Spawned[i].m_name, toSpawn);
					if (SpawnPedSettingsMenuVars::vars.information) {
						SpawnEntityManagerMenuVars::Spawned[i].m_creation = MISC::GetGameTimer();
						SpawnEntityManagerMenuVars::Spawned[i].m_showcreation = true;
					}
					break;
				}
			}
		}

		return ped;
	}

	void SpawnPedPlayer(Hash model, int id) {
		SPlayer& player = GetPlayer(id);
		if (STREAMING::IsModelInCdimage(model)) {
			GetEntityControl()->SimpleRequestModel(model);
			PED::CreatePed(21, model, player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 0, 1, 0);
		}
	}

	void SpawnPed(String name) {
		using namespace SpawnPedSettingsMenuVars;
		SpawnPed(name, vars.godmode, vars.blip);
	}
}

void SpawnPedMenu::Init() {
	setParentSubmenu<SpawnMenu>();
	setName("Ped", true, false);

	addOption(SubmenuOption("Spawner settings")
		.addTooltip("Spawner settings")
		.addSubmenu<SpawnPedSettingsMenu>().addTranslation());

	addOption(SubmenuOption("Manage spawned peds")
		.addSubmenu<SpawnEntityManagerMenu>()
		.addFunction([] { SpawnEntityManagerMenu::GetInstance()->setParentSubmenu<SpawnPedMenu>(); })
		.addTooltip("Manage the peds you've spawned").addTranslation());

	addOption(ButtonOption("Input ped name")
		.addFunction([] {
		GetMenuInput()->AddToQueue([] {
			string temp;
			if (GetMenuInput()->Text("Ped name", temp, 2, 40)) {
				if (SpawnMenuVars::vars.CreatorMode) {
					SpawnMenuVars::vars.SelectedCreatorObject = temp.c_str();
					SpawnMenuVars::vars.IsObjectAPed = true;
				}
				else {
					SpawnPed(temp.c_str());
				}
			}});
		})
		.addHotkey().addTranslation()
		.addTooltip("Input ped name").addTranslation());

	addOption(BreakOption("Peds").addTranslation());

	for (int i = 0; i < 683; i++) {
		addOption(ButtonOption(ModelMenuVars::m_models[i].m_name)
			.addFunction([=] { 
			if (SpawnMenuVars::vars.CreatorMode) {
				SpawnMenuVars::vars.SelectedCreatorObject = ModelMenuVars::m_models[i].m_model;
				SpawnMenuVars::vars.IsObjectAPed = true;
			}
			else {
				GetFiberPool()->DoJob([=] { SpawnPed(ModelMenuVars::m_models[i].m_model); });
			}
			
		})
			.addTooltip("Spawn this ped"));
	}
}

/*Update once when submenu is opened*/
void SpawnPedMenu::UpdateOnce() {}

/*Update while submenu is active*/
void SpawnPedMenu::Update() {}

/*Background update*/
void SpawnPedMenu::FeatureUpdate() {}

/*Singleton*/
SpawnPedMenu* _instance;
SpawnPedMenu* SpawnPedMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new SpawnPedMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
SpawnPedMenu::~SpawnPedMenu() { delete _instance; }