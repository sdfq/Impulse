#include "stdafx.h"
#include "spawnPedManager.h"
#include "spawnEntityManager.h"

using namespace SpawnPedManagerMenuVars;

namespace SpawnPedManagerMenuVars {
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

	void MakeBodyguard() {
		int group = PLAYER::GetPlayerGroup(GetLocalPlayer().m_id);
		PED::SetPedAsGroupMember(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, group);
		PED::SetPedNeverLeavesGroup(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, true);
		PED::SetPedCombatAbility(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, 100);
		BRAIN::TaskCombatHatedTargetsAroundPed(GetLocalPlayer().m_ped, 100, SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle);
	}
}

void SpawnPedManagerMenu::Init() {
	setParentSubmenu<SpawnEntityManagerMenu>();
	setName("Manage ped", true, true);

	addOption(ToggleOption("Invincibility")
		.addToggle(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_godmode)
		.addFunction([] { ENTITY::SetEntityInvincible(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_godmode); })
		.addTooltip("Make ped invincible"));

	addOption(ButtonOption("Teleport to me")
		.addFunction(TeleportToMe)
		.addTooltip("Teleport ped to me"));

	addOption(ButtonOption("Teleport to spawned location")
		.addFunction(TeleportToOrigin)
		.addTooltip("Teleport ped to spawned location"));

	addOption(ButtonOption("Teleport to ped")
		.addFunction(TeleportToVehicle)
		.addTooltip("Teleport to ped"));

	addOption(ButtonOption("Clone")
		.addFunction([] { PED::ClonePed(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, 1, 1, 0); })
		.addTooltip("Clone the ped"));

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

	addOption(ButtonOption("Delete ped")
		.addFunction([] { ENTITY::SetEntityAsMissionEntity(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, 1, 1); ENTITY::DeleteEntity(&SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle); GetSubmenuHandler()->SetSubPrevious(); SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage] = SpawnEntityManagerMenuVars::SpawnedEntity(); })
		.addTooltip("Delete ped"));

	addOption(ButtonOption("Explode")
		.addFunction([] { FIRE::AddExplosion(vars.coords.x, vars.coords.y, vars.coords.z, 1, 1000000, true, false, 0.0f, false); })
		.addTooltip("Explode the ped"));

	addOption(ButtonOption("Sprint to me")
		.addFunction([] { Vector3 myCoords = GetLocalPlayer().m_coordinates; BRAIN::TaskGoStraightToCoord(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, myCoords.x, myCoords.y, myCoords.z, 10, 99999, 1, 0); })
		.addTooltip("Make ped sprint to you"));

	addOption(ButtonOption("Give RPG")
		.addFunction([] { WEAPON::GiveDelayedWeaponToPed(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, 0xB1CA77B1, 0, 1); })
		.addTooltip("Give ped RPG"));

	addOption(ButtonOption("Give assault SMG")
		.addFunction([] { WEAPON::GiveDelayedWeaponToPed(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, 0xEFE7E2DF, 0, 1); })
		.addTooltip("Give ped assault SMG"));

	addOption(ButtonOption("Give minigun")
		.addFunction([] { WEAPON::GiveDelayedWeaponToPed(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, 0x42BF8A85, 0, 1); })
		.addTooltip("Give ped minigun"));

	addOption(ButtonOption("Make bodyguard")
		.addFunction(MakeBodyguard)
		.addTooltip("Make this ped your bodyguard"));

	addOption(ButtonOption("Kill")
		.addFunction([] { PED::ApplyDamageToPed(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, 30000, true); })
		.addTooltip("Kill ped"));
}

/*Update once when submenu is opened*/
void SpawnPedManagerMenu::UpdateOnce() {}

/*Update while submenu is active*/
void SpawnPedManagerMenu::Update() {
	vars.coords = ENTITY::GetEntityCoords(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, 1);
	vars.rot = ENTITY::GetEntityRotation(SpawnEntityManagerMenuVars::Spawned[SpawnEntityManagerMenuVars::m_selectedEntityToManage].m_handle, 2);

	Vector3 myCoords = GetLocalPlayer().m_coordinates;
	GRAPHICS::DrawLine(myCoords.x, myCoords.y, myCoords.z, vars.coords.x, vars.coords.y, vars.coords.z, 255, 255, 0, 255);
}

/*Background update*/
void SpawnPedManagerMenu::FeatureUpdate() {}

/*Singleton*/
SpawnPedManagerMenu* _instance;
SpawnPedManagerMenu* SpawnPedManagerMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new SpawnPedManagerMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
SpawnPedManagerMenu::~SpawnPedManagerMenu() { delete _instance; }