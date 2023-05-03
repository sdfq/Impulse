#include "stdafx.h"
#include "mapModsMenu.h"
#include "..//..//spawnMenu.h"
#include <menu\submenus\main\spawn\manager\spawnEntityManager.h>

using namespace MapModsMenuVars;

namespace MapModsMenuVars 
{
	Vars vars;

	Object SpawnMapModObject(String toSpawn, bool blip, Vector3 coords)
	{

		DWORD model = Utils::GetHashKey(toSpawn);
		Object object;
		if (STREAMING::IsModelInCdimage(model))
		{
			GetEntityControl()->SimpleRequestModel(model);
			object = OBJECT::CreateObject(model, coords.x, coords.y, coords.z, 1, 1, 0);
			if (blip) { auto blip = HUD::AddBlipForEntity(object); HUD::SetBlipSprite(blip, 351); HUD::SetBlipColour(blip, 4); }
		}

		AUDIO::PlaySoundFrontend(-1, "Drill_Pin_Break", "DLC_HEIST_FLEECA_SOUNDSET", 0);

		if (ENTITY::DoesEntityExist(object))
		{
			for (int i = 0; i < 500; i++)
			{
				if (!SpawnEntityManagerMenuVars::Spawned[i].m_taken)
				{
					SpawnEntityManagerMenuVars::Spawned[i].m_taken = true;
					SpawnEntityManagerMenuVars::Spawned[i].m_address = PoolManager::GetEntityAddress(object);
					SpawnEntityManagerMenuVars::Spawned[i].m_frozen = false;
					SpawnEntityManagerMenuVars::Spawned[i].m_godmode = false;
					SpawnEntityManagerMenuVars::Spawned[i].m_handle = object;
					SpawnEntityManagerMenuVars::Spawned[i].m_model = ENTITY::GetEntityModel(object);
					SpawnEntityManagerMenuVars::Spawned[i].m_origin = ENTITY::GetEntityCoords(object, 1);
					SpawnEntityManagerMenuVars::Spawned[i].m_type = SpawnEntityManagerMenuVars::EntityTypeMapMod;
					strcpy(SpawnEntityManagerMenuVars::Spawned[i].m_name, toSpawn);
					break;
				}
			}
		}
		return object;
	}
}

void MapModsMenu::Init() {
	setParentSubmenu<SpawnMenu>();
	setName("Map mods", true, true);

	addOption(ButtonOption("Unload map mods")
		.addFunction([]
		{
				GetFiberPool()->DoJob([]
				{
					for (int i = 0; i < 500; i++)
					{
						if (SpawnEntityManagerMenuVars::Spawned[i].m_taken)
						{
							if (SpawnEntityManagerMenuVars::Spawned[i].m_type == SpawnEntityManagerMenuVars::EntityTypeMapMod)
							{
								GetEntityControl()->DeleteEntity(SpawnEntityManagerMenuVars::Spawned[i].m_handle);
							}
							SpawnEntityManagerMenuVars::Spawned[i].m_taken = false;
						}
					}
				});
		})
		.addTranslation()
		.addHotkey()
		.addTooltip("Delete all the objects spawned by loading map mods"));

	//addOption(BreakOption("Map mods"));
}

/*Update once when submenu is opened*/
void MapModsMenu::UpdateOnce() {}

/*Update while submenu is active*/
void MapModsMenu::Update() 
{
	clearOptionsOffset(1);
	for (const auto& entry : experimental::filesystem::directory_iterator(GetConfig()->GetMapModsPath()))
	{
		auto const pos = entry.path().filename().string().find_last_of('.');
		string option = entry.path().filename().string().substr(0, pos);
		string mapModPath = entry.path().string();

		// Struct: { Name, Model, Pos.x, Pos.y, Pos.z, Rot.x, Rot.y, Rot.z, Pitch (Vertical), Roll, Yaw (Horizontal) }

		addOption(ButtonOption(option.c_str())
			.addTooltip("Load the map mod!")
			.addFunction([=]
				{
					GetFiberPool()->DoJob([=]
						{
							fstream mapModFile(mapModPath);
							json j = json::parse(mapModFile);

							for (auto i = 0; i < j.size(); i++)
							{
								auto& iterator = j[i];
								string Name = iterator[0].get<string>();
								Hash Model = iterator[1].get<DWORD>();
								float PosX = iterator[2].get<float>();
								float PosY = iterator[3].get<float>();
								float PosZ = iterator[4].get<float>();
								float Pitch = iterator[5].get<float>();
								float Roll = iterator[6].get<float>();
								float Yaw = iterator[7].get<float>();
								Object Obj = SpawnMapModObject(Name.c_str(), false, { PosX, PosY, PosZ });
								ENTITY::SetEntityRotation(Obj, Pitch, Roll, Yaw, 2, false);
							}
						});
				}));
	}
}

/*Background update*/
void MapModsMenu::FeatureUpdate() {}

/*Singleton*/
MapModsMenu* _instance;
MapModsMenu* MapModsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new MapModsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
MapModsMenu::~MapModsMenu() { delete _instance; }