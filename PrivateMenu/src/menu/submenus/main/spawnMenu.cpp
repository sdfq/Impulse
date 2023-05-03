#include "stdafx.h"
#include "spawnMenu.h"
#include "spawn/spawnVehicleMenu.h"
#include "spawn/spawnPedMenu.h"
#include "spawn/spawnObjectMenu.h"
#include "spawn/loadingMenu.h"
#include "spawn/manager/spawnEntityManager.h"
#include "../mainMenu.h"
#include "miscMenu.h"
#include "localMenu.h"
#include <menu\submenus\main\spawn\map mods\mapModsMenu.h>

using namespace SpawnMenuVars;

namespace SpawnMenuVars {
	Var vars;

	Ped SpawnPed(String toSpawn, bool godmode, bool blip, Vector3 coords) {
		DWORD model = Utils::GetHashKey(toSpawn);
		Ped ped;
		if (STREAMING::IsModelInCdimage(model)) {
			GetEntityControl()->SimpleRequestModel(model);
			ped = PED::CreatePed(21, model, coords.x, coords.y, coords.z, 0, 1, 0);
			ENTITY::SetEntityInvincible(ped, godmode);
			if (blip) { auto blip = HUD::AddBlipForEntity(ped); HUD::SetBlipSprite(blip, 366); HUD::SetBlipColour(blip, 3); }
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
					break;
				}
			}
		}

		return ped;
	}

	Object SpawnObject(String toSpawn, bool blip, Vector3 coords) {

		DWORD model = Utils::GetHashKey(toSpawn);
		Object object;
		if (STREAMING::IsModelInCdimage(model)) {
			GetEntityControl()->SimpleRequestModel(model);
			object = OBJECT::CreateObject(model, coords.x, coords.y, coords.z, 1, 1, 0);
			if (blip) { auto blip = HUD::AddBlipForEntity(object); HUD::SetBlipSprite(blip, 351); HUD::SetBlipColour(blip, 4); }
		}

		AUDIO::PlaySoundFrontend(-1, "Drill_Pin_Break", "DLC_HEIST_FLEECA_SOUNDSET", 0);

		if (ENTITY::DoesEntityExist(object)) {
			for (int i = 0; i < 500; i++) {
				if (!SpawnEntityManagerMenuVars::Spawned[i].m_taken) {
					SpawnEntityManagerMenuVars::Spawned[i].m_taken = true;
					SpawnEntityManagerMenuVars::Spawned[i].m_address = PoolManager::GetEntityAddress(object);
					SpawnEntityManagerMenuVars::Spawned[i].m_frozen = false;
					SpawnEntityManagerMenuVars::Spawned[i].m_godmode = false;
					SpawnEntityManagerMenuVars::Spawned[i].m_handle = object;
					SpawnEntityManagerMenuVars::Spawned[i].m_model = ENTITY::GetEntityModel(object);
					SpawnEntityManagerMenuVars::Spawned[i].m_origin = ENTITY::GetEntityCoords(object, 1);
					SpawnEntityManagerMenuVars::Spawned[i].m_type = SpawnEntityManagerMenuVars::EntityTypeObject;
					strcpy(SpawnEntityManagerMenuVars::Spawned[i].m_name, toSpawn);
					break;
				}
			}
		}
		return object;
	}
}

void SpawnMenu::Init() {
	setParentSubmenu<MainMenu>();
	setName("Spawn", true, true);

	addOption(SubmenuOption("Vehicle")
		.addSubmenu<SpawnVehicleMenu>().addTranslation()
		.addTooltip("Vehicle spawning options"));

	addOption(SubmenuOption("Ped")
		.addSubmenu<SpawnPedMenu>().addTranslation()
		.addTooltip("Ped spawning options"));

	addOption(SubmenuOption("Object")
		.addSubmenu<SpawnObjectMenu>().addTranslation()
		.addTooltip("Object spawning options"));

	addOption(SubmenuOption("Saved vehicle loading")
		.addSubmenu<LoadingMenu>().addHotkey().addTranslation()
		.addTooltip("Load saved vehicles"));

	addOption(SubmenuOption("Map mods")
		.addSubmenu<MapModsMenu>().addHotkey().addTranslation()
		.addTooltip("You can save and load your creations from the spawning mode!"));

	addOption(BreakOption("Spawn Editor").addTranslation());

	addOption(ButtonOption("Save current creation")
		.addFunction([]
			{
				String mapModsPath = GetConfig()->GetMapModsPath();
				GetMenuInput()->AddToQueue([=]
					{
						string inputTemp;
						if (GetMenuInput()->Text("Map name", inputTemp, 2, 20))
						{
							String mapModName = inputTemp.c_str();
							ofstream mapModFile(va("%s%s.json", mapModsPath, inputTemp));
							json j;
							// Push: { Name, Model, Pos.x, Pos.y, Pos.z, Rot.x, Rot.y, Rot.z, Pitch (Vertical), Roll, Yaw (Horizontal) }
							for (int i = 0; i < 500; i++)
							{
								if (SpawnEntityManagerMenuVars::Spawned[i].m_taken)
								{
									if (SpawnEntityManagerMenuVars::Spawned[i].m_type == SpawnEntityManagerMenuVars::EntityTypeObject)
									{
										using namespace SpawnEntityManagerMenuVars;
										string Name = Spawned[i].m_name;
										Hash Model = Spawned[i].m_model;
										Vector3 Position = ENTITY::GetEntityCoords(Spawned[i].m_handle, false);
										Vector3 Rotation = ENTITY::GetEntityRotation(Spawned[i].m_handle, 2);
										j.push_back({ Name, Model, Position.x, Position.y, Position.z, Rotation.x, Rotation.y, Rotation.z });
									}
								}
							}
							mapModFile << setw(4) << j;
							mapModFile.close();
						}
					});
			})
		.addTooltip("Save the current creation in the map mods folder.")
		.addHotkey()
		.addTranslation());

	addOption(ButtonOption("Clear spawned objects")
		.addFunction([] 
			{
				GetFiberPool()->DoJob([]
					{
						for (int i = 0; i < 500; i++)
						{
							if (SpawnEntityManagerMenuVars::Spawned[i].m_taken)
							{
								if (SpawnEntityManagerMenuVars::Spawned[i].m_type == SpawnEntityManagerMenuVars::EntityTypeObject)
								{
									GetEntityControl()->DeleteEntity(SpawnEntityManagerMenuVars::Spawned[i].m_handle);
								}
								SpawnEntityManagerMenuVars::Spawned[i].m_taken = false;
							}
						}
					});
			})
		.addTranslation().addHotkey()
		.addTooltip("Delete all the objects spawned using spawner mode"));

	addOption(ToggleOption("Spawner mode")
		.addToggle(vars.CreatorMode)
		.addTooltip("This will enter you into a spawning mode that allows you to spawn peds and objects where you aim [Alpha]")
		.addFunction([]
		{
			if (vars.CreatorMode)
			{
				MiscMenuVars::vars.freecam = true;
			}
			else
			{
				MiscMenuVars::vars.freecam = false;
				if (CAM::DoesCamExist(MiscMenuVars::vars.freecamHandle))
				{
					CAM::SetCamActive(MiscMenuVars::vars.freecamHandle, 0);
					CAM::RenderScriptCams(0, 0, 2000, 1, 0, 1);
					CAM::DestroyCam(MiscMenuVars::vars.freecamHandle, 0);
					STREAMING::SetFocusEntity(GetLocalPlayer().m_ped);
				}
			}
		}
	));

	addOption(ToggleOption("Spawner mode marker")
		.addToggle(vars.DrawMarker)
		.addRequirement([] { return vars.CreatorMode; })
		.addTooltip("Draw a marker wherever the creator's object is going to be placed")
		.addHotkey().addTranslation());

	addOption(NumberOption<float>(SCROLL, "Effective distance")
		.addNumber(vars.CreatorModeDistance, "%.0f", 10.0f)
		.addTranslation()
		.addHotkey()
		.addRequirement([] { return vars.CreatorMode;  })
		.addTooltip("The higher the number, further the marker will go if you want to place objects in the sky instead of the ground."));

	addOption(ToggleOption("Add blip")
		.addToggle(vars.Blip)
		.addTooltip("Adds a blip to the spawned vehicle / object to prevent it from disappearing.")
		.addRequirement([] { return vars.CreatorMode; })
		.addHotkey()
		.addTranslation());
}

/*Update once when submenu is opened*/
void SpawnMenu::UpdateOnce() {}

/*Update while submenu is active*/
void SpawnMenu::Update() {}

/*Background update*/
void SpawnMenu::FeatureUpdate() {	
	static auto leftPressed = false;
	if (vars.CreatorMode) {
		LocalMenuVars::vars.invisibility = true;
		Vector3 coords = CAM::GetCamCoord(MiscMenuVars::vars.freecamHandle);
		ENTITY::SetEntityCoordsNoOffset(GetLocalPlayer().m_ped, coords.x, coords.y, coords.x + 20, 0, 0, 0);

		Raycast Ray = Raycast::Raycast(CastInfront(vars.CreatorModeDistance, CAM::GetCamCoord(MiscMenuVars::vars.freecamHandle), -1));
		Vector3 Front = FrontCoords(vars.CreatorModeDistance, CAM::GetCamCoord(MiscMenuVars::vars.freecamHandle));
		Vector3 FinalCoords = Ray.hit ? Ray.endCoords : Front;

		if (vars.DrawMarker) GRAPHICS::DrawMarker(28, FinalCoords.x, FinalCoords.y, FinalCoords.z,
			0, 0, 0, 0, 180, 0, 1, 1, 1, 0, 0, 255, 75, 0, 1, 1, 0, 0, 0, 0);

		if (GetAsyncKeyState(VK_LBUTTON) && !leftPressed)
		{
			leftPressed = true;
			if (!vars.IsObjectAPed) GetFiberPool()->DoJob([=] { SpawnObject(vars.SelectedCreatorObject, vars.Blip, FinalCoords); });
			else GetFiberPool()->DoJob([=] { SpawnPed(vars.SelectedCreatorObject, false, vars.Blip, FinalCoords); });
		}
		else if (!GetAsyncKeyState(VK_LBUTTON) && leftPressed) 
		{
			leftPressed = false;
		}
	}

}


/*Singleton*/
SpawnMenu* _instance;
SpawnMenu* SpawnMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new SpawnMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
SpawnMenu::~SpawnMenu() { delete _instance; }