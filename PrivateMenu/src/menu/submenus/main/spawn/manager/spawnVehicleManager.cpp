#include "stdafx.h"
#include "spawnVehicleManager.h"
#include "spawnEntityManager.h"
#include "../../vehicle/LSCMenu.h"

using namespace SpawnVehicleManagerMenuVars;

namespace SpawnVehicleManagerMenuVars {
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

void SpawnVehicleManagerMenu::Init() {
	setParentSubmenu<SpawnEntityManagerMenu>();
	setName("Manage vehicle", true, true);

	addOption(ButtonOption("Fully tune")
		.addFunction([] { GetEntityControl()->SimpleRequestControl(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle); LSCMenuVars::MaxVehicle(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle); })
		.addTooltip("Max vehicle"));

	addOption(ButtonOption("Downgrade")
		.addFunction([] { GetEntityControl()->SimpleRequestControl(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle); LSCMenuVars::DowngradeVehicle(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle); })
		.addTooltip("Downgrade vehicle"));

	addOption(ButtonOption("Place on ground")
		.addFunction([] { GetEntityControl()->SimpleRequestControl(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle); VEHICLE::SetVehicleDeformationFixed(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle); })
		.addTooltip("Place vehicle on ground upright"));

	addOption(ToggleOption("Invincibility")
		.addToggle(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_godmode)
		.addFunction([] { ENTITY::SetEntityInvincible(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_godmode); })
		.addTooltip("Make vehicle invincible"));

	addOption(ButtonOption("Teleport to me")
		.addFunction(TeleportToMe)
		.addTooltip("Teleport vehicle to me"));

	addOption(ButtonOption("Teleport to spawned location")
		.addFunction(TeleportToOrigin)
		.addTooltip("Teleport vehicle to spawned location"));

	addOption(ButtonOption("Teleport to vehicle")
		.addFunction(TeleportToVehicle)
		.addTooltip("Teleport to vehicle"));

	addOption(NumberOption<float>(SCROLL, "Precision")
		.addNumber(vars.precision, "%.1f", 0.1f)
		.addTooltip("Set the precision for the position editor"));

	addOption(NumberOption<float>(SCROLL, "Position - horizontal (x)")
		.addOnUpdate([](NumberOption<float>* option) { option->addNumber(vars.coords.x, "%.3f", vars.precision).addMin(-100000.f).addMax(100000.f); })
		.addFunction([] {
			Vector3 cur = ENTITY::GetEntityCoords(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, 1);
			cur.x = vars.coords.x;
			ENTITY::SetEntityCoordsNoOffset(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, cur.x, cur.y, cur.z, 0, 0, 1);
			vars.coords = cur;
		}).addTooltip("X position"));

	addOption(NumberOption<float>(SCROLL, "Position - vertical (y)")
		.addOnUpdate([](NumberOption<float>* option) { option->addNumber(vars.coords.y, "%.3f", vars.precision).addMin(-100000.f).addMax(100000.f); })
		.addFunction([] {
			Vector3 cur = ENTITY::GetEntityCoords(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, 1);
			cur.y = vars.coords.y;
			ENTITY::SetEntityCoordsNoOffset(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, cur.x, cur.y, cur.z, 0, 0, 1);
			vars.coords = cur;
		}).addTooltip("Y position"));

	addOption(NumberOption<float>(SCROLL, "Position - height (z)")
		.addOnUpdate([](NumberOption<float>* option) { option->addNumber(vars.coords.z, "%.3f", vars.precision).addMin(-100000.f).addMax(100000.f); })
		.addFunction([] {
			Vector3 cur = ENTITY::GetEntityCoords(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, 1);
			cur.z = vars.coords.z;
			ENTITY::SetEntityCoordsNoOffset(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, cur.x, cur.y, cur.z, 0, 0, 1);
			vars.coords = cur;
		}).addTooltip("Y position"));

	addOption(NumberOption<float>(SCROLL, "Position - pitch (vertical)")
		.addOnUpdate([](NumberOption<float>* option) { option->addNumber(vars.rot.x, "%.3f", vars.precision).addMin(-100000.f).addMax(100000.f); })
		.addFunction([] {
			Vector3 cur = ENTITY::GetEntityRotation(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, 2);
			cur.x = vars.rot.x;
			ENTITY::SetEntityRotation(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, cur.x, cur.y, cur.z, 2, 0);
			vars.rot = cur;
		}).addTooltip("Pitch"));

	addOption(NumberOption<float>(SCROLL, "Position - roll (side)")
		.addOnUpdate([](NumberOption<float>* option) { option->addNumber(vars.rot.y, "%.3f", vars.precision).addMin(-100000.f).addMax(100000.f); })
		.addFunction([] {
			Vector3 cur = ENTITY::GetEntityRotation(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, 2);
			cur.y = vars.rot.y;
			ENTITY::SetEntityRotation(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, cur.x, cur.y, cur.z, 2, 0);
			vars.rot = cur;
		}).addTooltip("Roll"));

	addOption(NumberOption<float>(SCROLL, "Position - yaw (heading)")
		.addOnUpdate([](NumberOption<float>* option) { option->addNumber(vars.rot.z, "%.3f", vars.precision).addMin(-100000.f).addMax(100000.f); })
		.addFunction([] {
			Vector3 cur = ENTITY::GetEntityRotation(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, 2);
			cur.z = vars.rot.z;
			ENTITY::SetEntityRotation(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, cur.x, cur.y, cur.z, 2, 0);
			vars.rot = cur;
		}).addTooltip("Yaw"));

	addOption(ToggleOption("Freeze position")
		.addToggle(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_frozen)
		.addFunction([] { ENTITY::FreezeEntityPosition(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_frozen); })
		.addTooltip("Freeze vehicle position"));

	addOption(ButtonOption("Delete vehicle")
		.addFunction([] { ENTITY::SetEntityAsMissionEntity(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, 1, 1); ENTITY::DeleteEntity(&SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle); GetSubmenuHandler()->SetSubPrevious(true); SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage] = SpawnEntityManagerMenuVars::SpawnedEntity(); })
		.addTooltip("Delete vehicle"));

	addOption(ButtonOption("Explode")
		.addFunction([] { FIRE::AddExplosion(vars.coords.x, vars.coords.y, vars.coords.z, 1, 1000000, true, false, 0.0f, false); })
		.addTooltip("Explode the vehicle"));
}

/*Update once when submenu is opened*/
void SpawnVehicleManagerMenu::UpdateOnce() {
	//vars.coords = ENTITY::GetEntityCoords(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, 1);
}

/*Update while submenu is active*/
void SpawnVehicleManagerMenu::Update() {
	vars.coords = ENTITY::GetEntityCoords(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, 1);
	vars.rot = ENTITY::GetEntityRotation(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, 2);

	Vector3 myCoords = GetLocalPlayer().m_coordinates;
	GRAPHICS::DrawLine(myCoords.x, myCoords.y, myCoords.z, vars.coords.x, vars.coords.y, vars.coords.z, 255, 0, 0, 255);
}

/*Background update*/
void SpawnVehicleManagerMenu::FeatureUpdate() {}

/*Singleton*/
SpawnVehicleManagerMenu* _instance;
SpawnVehicleManagerMenu* SpawnVehicleManagerMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new SpawnVehicleManagerMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
SpawnVehicleManagerMenu::~SpawnVehicleManagerMenu() { delete _instance; }