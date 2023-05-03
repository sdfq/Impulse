#include "stdafx.h"
#include "spawnObjectManager.h"
#include "spawnEntityManager.h"

using namespace SpawnObjectManagerMenuVars;

namespace SpawnObjectManagerMenuVars {
	Vars vars;

	void TeleportToMe() {
		Vector3 myCoords = GetLocalPlayer().m_coordinates;
		ENTITY::SetEntityCoordsNoOffset(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, myCoords.x, myCoords.y, myCoords.z, 0, 0, 1);
	}

	void TeleportToOrigin() {
		Vector3 origin = SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_origin;
		ENTITY::SetEntityCoordsNoOffset(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, origin.x, origin.y, origin.z, 0, 0, 1);
	}

	void TeleportToVehicle() {
		ENTITY::SetEntityCoordsNoOffset(GetLocalPlayer().m_ped, vars.coords.x, vars.coords.y, vars.coords.z, 0, 0, 1);
	}
}

void SpawnObjectManagerMenu::Init() {
	setParentSubmenu<SpawnEntityManagerMenu>();
	setName("Manage object", true, true);

	addOption(ButtonOption("Teleport to me")
		.addFunction(TeleportToMe)
		.addTooltip("Teleport object to me").addTranslation());

	addOption(ButtonOption("Teleport to spawned location")
		.addFunction(TeleportToOrigin)
		.addTooltip("Teleport object to spawned location").addTranslation());

	addOption(ButtonOption("Teleport to object")
		.addFunction(TeleportToVehicle)
		.addTooltip("Teleport to object").addTranslation());

	addOption(ButtonOption("Clone")
		.addFunction([] {
		GetEntityControl()->SimpleRequestModel(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_model);
		Object SpawnedObject = OBJECT::CreateObject(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_model, vars.coords.x, vars.coords.y, vars.coords.z, 1, 1, 0);
		if (ENTITY::DoesEntityExist(SpawnedObject)) {
			SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_frozen = true;

			AUDIO::PlaySoundFrontend(-1, "Drill_Pin_Break", "DLC_HEIST_FLEECA_SOUNDSET", 0);

			for (int i = 0; i < 500; i++) {
				if (!SpawnEntityManagerMenuVars::Spawned[i].m_taken) {
					SpawnEntityManagerMenuVars::Spawned[i].m_taken = true;
					SpawnEntityManagerMenuVars::Spawned[i].m_address = PoolManager::GetEntityAddress(SpawnedObject);
					SpawnEntityManagerMenuVars::Spawned[i].m_frozen = false;
					SpawnEntityManagerMenuVars::Spawned[i].m_godmode = false;
					SpawnEntityManagerMenuVars::Spawned[i].m_handle = SpawnedObject;
					SpawnEntityManagerMenuVars::Spawned[i].m_model = ENTITY::GetEntityModel(SpawnedObject);
					SpawnEntityManagerMenuVars::Spawned[i].m_origin = ENTITY::GetEntityCoords(SpawnedObject, 1);
					SpawnEntityManagerMenuVars::Spawned[i].m_type = SpawnEntityManagerMenuVars::EntityTypeObject;
					strcpy(SpawnEntityManagerMenuVars::Spawned[i].m_name, SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_name);
					break;
				}
			}
		}
	})
		.addTooltip("Clone the object").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Precision")
		.addNumber(vars.precision, "%.1f", 0.1f)
		.addTooltip("Set the precision for the position editor").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Position - horizontal (x)")
		.addOnUpdate([](NumberOption<float>* option) { option->addNumber(vars.coords.x, "%.3f", vars.precision).addMin(-100000.f).addMax(100000.f); })
		.addFunction([] {
		Vector3 cur = ENTITY::GetEntityCoords(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, 1);
		cur.x = vars.coords.x;
		ENTITY::SetEntityCoordsNoOffset(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, cur.x, cur.y, cur.z, 0, 0, 1);
		vars.coords = cur;
	}).addTooltip("X position").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Position - vertical (y)")
		.addOnUpdate([](NumberOption<float>* option) { option->addNumber(vars.coords.y, "%.3f", vars.precision).addMin(-100000.f).addMax(100000.f); })
		.addFunction([] {
		Vector3 cur = ENTITY::GetEntityCoords(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, 1);
		cur.y = vars.coords.y;
		ENTITY::SetEntityCoordsNoOffset(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, cur.x, cur.y, cur.z, 0, 0, 1);
		vars.coords = cur;
	}).addTooltip("Y position").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Position - height (z)")
		.addOnUpdate([](NumberOption<float>* option) { option->addNumber(vars.coords.z, "%.3f", vars.precision).addMin(-100000.f).addMax(100000.f); })
		.addFunction([] {
		Vector3 cur = ENTITY::GetEntityCoords(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, 1);
		cur.z = vars.coords.z;
		ENTITY::SetEntityCoordsNoOffset(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, cur.x, cur.y, cur.z, 0, 0, 1);
		vars.coords = cur;
	}).addTooltip("Y position").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Position - pitch (vertical)")
		.addOnUpdate([](NumberOption<float>* option) { option->addNumber(vars.rot.x, "%.3f", vars.precision).addMin(-100000.f).addMax(100000.f); })
		.addFunction([] {
		Vector3 cur = ENTITY::GetEntityRotation(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, 2);
		cur.x = vars.rot.x;
		ENTITY::SetEntityRotation(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, cur.x, cur.y, cur.z, 2, 0);
		vars.rot = cur;
	}).addTooltip("Pitch").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Position - roll (side)")
		.addOnUpdate([](NumberOption<float>* option) { option->addNumber(vars.rot.y, "%.3f", vars.precision).addMin(-100000.f).addMax(100000.f); })
		.addFunction([] {
		Vector3 cur = ENTITY::GetEntityRotation(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, 2);
		cur.y = vars.rot.y;
		ENTITY::SetEntityRotation(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, cur.x, cur.y, cur.z, 2, 0);
		vars.rot = cur;
	}).addTooltip("Roll").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Position - yaw (heading)")
		.addOnUpdate([](NumberOption<float>* option) { option->addNumber(vars.rot.z, "%.3f", vars.precision).addMin(-100000.f).addMax(100000.f); })
		.addFunction([] {
		Vector3 cur = ENTITY::GetEntityRotation(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, 2);
		cur.z = vars.rot.z;
		ENTITY::SetEntityRotation(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, cur.x, cur.y, cur.z, 2, 0);
		vars.rot = cur;
	}).addTooltip("Yaw").addTranslation());

	addOption(ToggleOption("Freeze position")
		.addToggle(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_frozen)
		.addFunction([] { ENTITY::FreezeEntityPosition(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_frozen); })
		.addTooltip("Freeze vehicle position"));

	addOption(ButtonOption("Delete object")
		.addFunction([] { 
		ENTITY::SetEntityAsMissionEntity(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, 1, 1); 
		ENTITY::DeleteEntity(&SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle); 
		GetSubmenuHandler()->SetSubPrevious(true); SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage] = SpawnEntityManagerMenuVars::SpawnedEntity(); })
		.addTooltip("Delete object").addTranslation());
}

/*Update once when submenu is opened*/
void SpawnObjectManagerMenu::UpdateOnce() {}

/*Update while submenu is active*/
void SpawnObjectManagerMenu::Update() {
	vars.coords = ENTITY::GetEntityCoords(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, 1);
	vars.rot = ENTITY::GetEntityRotation(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, 2);

	Vector3 myCoords = GetLocalPlayer().m_coordinates;
	GRAPHICS::DrawLine(myCoords.x, myCoords.y, myCoords.z, vars.coords.x, vars.coords.y, vars.coords.z, 255, 0, 255, 255);
}

/*Background update*/
void SpawnObjectManagerMenu::FeatureUpdate() {
}

/*Singleton*/
SpawnObjectManagerMenu* _instance;
SpawnObjectManagerMenu* SpawnObjectManagerMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new SpawnObjectManagerMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
SpawnObjectManagerMenu::~SpawnObjectManagerMenu() { delete _instance; }