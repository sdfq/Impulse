#include "stdafx.h"
#include "weaponMenu.h"
#include "../mainMenu.h"
#include "weapon/weaponVisuals.h"
#include "weapon/weaponAmmoModifier.h"
#include "weapon/weaponAimbot.h"
#include "weapon/ownedTriggerbotMenu.h"
#include "weapon/weaponWeapons.h"
#include "local/modelMenu.h"
#include "weapon/weaponShootEntities.h"
#include "menu\submenus\main\worldMenu.h"
#include "backend\backendExplosions.h"
using namespace WeaponMenuVars;

namespace WeaponMenuVars {
	Vars vars;

	double DegreeToRadian(double n) {
		return n * 0.017453292519943295;
	}
	Vector3 RotationToDirection(Vector3 rot) {
		double num = DegreeToRadian(rot.z);
		double num2 = DegreeToRadian(rot.x);
		double val = cos(num2);
		double num3 = abs(val);
		rot.x = (float)(-(float)sin(num) * num3);
		rot.y = (float)(cos(num) * num3);
		rot.z = (float)sin(num2);
		return rot;

	}
	Vector3 multiplyVector(Vector3 vector, float inc) {
		vector.x *= inc;
		vector.y *= inc;
		vector.z *= inc;
		vector._paddingx *= inc;
		vector._paddingy *= inc;
		vector._paddingz *= inc;
		return vector;
	}
	Vector3 addVector(Vector3 vector, Vector3 vector2) {
		vector.x += vector2.x;
		vector.y += vector2.y;
		vector.z += vector2.z;
		vector._paddingx += vector2._paddingx;
		vector._paddingy += vector2._paddingy;
		vector._paddingz += vector2._paddingz;
		return vector;
	}

	void OneShotOneKill(bool toggle) {
		PLAYER::SetPlayerWeaponDamageModifier(GetLocalPlayer().m_id, toggle ? 999999 : 1);
		PLAYER::SetPlayerMeleeWeaponDamageModifier(GetLocalPlayer().m_id, toggle ? 999999 : 1, 0);
	}

	void InfiniteAmmo() {
		WEAPON::SetPedInfiniteAmmoClip(GetLocalPlayer().m_ped, true);
		WEAPON::SetPedInfiniteAmmo(GetLocalPlayer().m_ped, true, GetLocalPlayer().m_weaponHash);

		for (int i = 0; i < NUMOF(WeaponWeaponsMenuVars::usableWeaponHashes) - 1; i++) {
			WEAPON::SetPedInfiniteAmmo(GetLocalPlayer().m_ped, true, WeaponWeaponsMenuVars::usableWeaponHashes[i]);
		}
	}

	void NoReload() {
		int maxAmmo;
		if (WEAPON::GetMaxAmmo(GetLocalPlayer().m_ped, GetLocalPlayer().m_weaponHash, &maxAmmo)) {
			WEAPON::SetPedAmmo(GetLocalPlayer().m_ped, GetLocalPlayer().m_weaponHash, maxAmmo, 1);

			maxAmmo = WEAPON::GetMaxAmmoInClip(GetLocalPlayer().m_ped, GetLocalPlayer().m_weaponHash, 1);
			if (maxAmmo > 0)
				WEAPON::SetAmmoInClip(GetLocalPlayer().m_ped, GetLocalPlayer().m_weaponHash, maxAmmo);
		}
	}

	void DeadEye() {
		if (PED::GetPedConfigFlag(GetLocalPlayer().m_ped, PED_FLAG_IS_AIMING, 1)) {
			MISC::SetTimeScale(0.35f);
			if (PED::IsPedShooting(GetLocalPlayer().m_ped)) {
				MISC::SetTimeScale(0.2f);
				GRAPHICS::SetTimecycleModifier("Death");
			} else {
				GRAPHICS::ClearTimecycleModifier();
			}
			GRAPHICS::_StartScreenEffect("ExplosionJosh3", -1, true);
		} else {
			MISC::SetTimeScale(1.0f);
			GRAPHICS::ClearTimecycleModifier();
			GRAPHICS::_StopScreenEffect("ExplosionJosh3");
		}
	}

	void ShrinkRay() {
		if (PED::GetPedConfigFlag(GetLocalPlayer().m_ped, PED_FLAG_IS_AIMING, 1)) {
			if (GetLocalPlayer().m_weaponHash == 0x3656C8C1) {
				Entity Target = 0;
				if (PLAYER::GetEntityPlayerIsFreeAimingAt(GetLocalPlayer().m_id, &Target)) {
					if (ENTITY::IsEntityAPed(Target)) {
						PED::SetPedConfigFlag(Target, 223, true);
					}
				}
			}
		}
	}

	

	void GravityGun() {
		Vector3 relativePosition = ENTITY::GetOffsetFromEntityInWorldCoords(GetLocalPlayer().m_ped, 0.4f, 0, 0.6f);
		Vector3 rot = CAM::_GetGameplayCamRot(0);
		Vector3 cameraDirection = Utils::RotateToDirection(&rot);

		if (!vars.gravityGunNewTarget) {
			PLAYER::GetEntityPlayerIsFreeAimingAt(GetLocalPlayer().m_id, &vars.gravityGunTarget);
		}

		if (ENTITY::DoesEntityExist(vars.gravityGunTarget)) {
			if (PED::GetPedConfigFlag(GetLocalPlayer().m_ped, PED_FLAG_IS_AIMING, 1)) {
				GetEntityControl()->SimpleRequestControl(vars.gravityGunTarget);
				if (NETWORK::NetworkHasControlOfEntity(vars.gravityGunTarget)) {
					if (KeyDown(VK_NUMPAD8) || PAD::IsDisabledControlPressed(2, INPUT_FRONTEND_UP)) {
						vars.gravityGunDistance += 0.5f;
					}

					if (KeyDown(VK_NUMPAD2) || PAD::IsDisabledControlPressed(2, INPUT_FRONTEND_DOWN)) {
						if (vars.gravityGunDistance > 8.0f) {
							vars.gravityGunDistance -= 0.5f;
						}
					}

					if (ENTITY::IsEntityAPed(vars.gravityGunTarget) && !PED::IsPedOnFoot(vars.gravityGunTarget)) {
						vars.gravityGunTarget = PED::GetVehiclePedIsIn(vars.gravityGunTarget, 0);
					}

					vars.gravityGunNewTarget = true;

					GetEntityControl()->SimpleRequestControl(vars.gravityGunTarget);
					if (NETWORK::NetworkHasControlOfEntity(vars.gravityGunTarget)) {
						ENTITY::FreezeEntityPosition(vars.gravityGunTarget, false);

						if (ENTITY::IsEntityAVehicle(vars.gravityGunTarget)) {
							VEHICLE::SetVehicleForwardSpeed(vars.gravityGunTarget, 0);
						}

						if (ENTITY::IsEntityAPed(vars.gravityGunTarget)) {
							PED::SetPedToRagdoll(vars.gravityGunTarget, 1, 1, 1, 1, 1, 1);
						}

						Vector3 entityCoords = ENTITY::GetEntityCoords(vars.gravityGunTarget, 0);

						Vector3 force;
						force.x = ((relativePosition.x + (cameraDirection.x * vars.gravityGunDistance)) - entityCoords.x) * 4;
						force.y = ((relativePosition.y + (cameraDirection.y * vars.gravityGunDistance)) - entityCoords.y) * 4;
						force.z = ((relativePosition.z + (cameraDirection.z * vars.gravityGunDistance)) - entityCoords.z) * 4;

						GetEntityControl()->SimpleRequestControl(vars.gravityGunTarget);
						if (NETWORK::NetworkHasControlOfEntity(vars.gravityGunTarget)) {
							ENTITY::SetEntityVelocity(vars.gravityGunTarget, force.x, force.y, force.z);
						}
						if (PED::GetPedConfigFlag(GetLocalPlayer().m_ped, PED_FLAG_IS_AIMING, 1) && (PAD::IsDisabledControlPressed(0, 208) || (GetKeyState(VK_LBUTTON) & 0x100) != 0)) {
							vars.gravityGunDistance += 2000;
							vars.gravityGunTarget = NULL;
							vars.gravityGunNewTarget = false;
						}

					}
				}
			} else {
				vars.gravityGunNewTarget = false;
				ENTITY::FreezeEntityPosition(vars.gravityGunTarget, false);
				vars.gravityGunTarget = NULL;
				vars.gravityGunDistance = 8.0f;
			}
		}
	}

	void Defibrillator() {
		if (PED::IsPedShooting(GetLocalPlayer().m_ped)) {
			if (GetLocalPlayer().m_weaponHash == 0x3656C8C1) {
				Entity Target = 0;
				if (PLAYER::GetEntityPlayerIsFreeAimingAt(GetLocalPlayer().m_id, &Target)) {
					if (ENTITY::IsEntityAPed(Target) && ENTITY::GetEntityHealth(Target) <= 0) {
						PED::ResurrectPed(Target);
						ENTITY::SetEntityCollision(Target, 1, 0);
						BRAIN::ClearPedTasksImmediately(Target);
					}
				}
			}
		}
	}

	void DeleteGun() {
		Entity EntityAimedAt = 0;
		if (PLAYER::GetEntityPlayerIsFreeAimingAt(GetLocalPlayer().m_id, &EntityAimedAt)) {
			if (PED::IsPedShooting(GetLocalPlayer().m_ped)) {
				GetEntityControl()->SimpleRequestControl(EntityAimedAt);
				if (NETWORK::NetworkHasControlOfEntity(EntityAimedAt)) {
					ENTITY::SetEntityAsMissionEntity(EntityAimedAt, 0, 1);
					ENTITY::DeleteEntity(&EntityAimedAt);
					ENTITY::SetEntityCoords(EntityAimedAt, 6000.0, 6000.0, 6000.0, true, false, false, true);
				}
			}
		}
	}

	void DriveItGun() {

		Entity EntityAimedAt = 0;
		if (PLAYER::GetEntityPlayerIsFreeAimingAt(GetLocalPlayer().m_id, &EntityAimedAt)) {
			if (PED::IsPedShooting(GetLocalPlayer().m_ped)) {
				if (ENTITY::IsEntityAVehicle(EntityAimedAt)) {
					GetEntityControl()->SimpleRequestControl(EntityAimedAt);
					Ped ped = VEHICLE::GetPedInVehicleSeat(EntityAimedAt, -1, 1);
					BRAIN::ClearPedTasksImmediately(ped);
					PED::SetPedIntoVehicle(GetLocalPlayer().m_ped, EntityAimedAt, -1);
				}
				else if (ENTITY::IsEntityAPed(EntityAimedAt))
				{
					if (PED::GetVehiclePedIsIn(EntityAimedAt, false) != NULL)
					{
						Vehicle veh = PED::GetVehiclePedIsIn(EntityAimedAt, false);
						Ped ped = VEHICLE::GetPedInVehicleSeat(veh, -1, 1);
						if (ped != NULL)
						{
							BRAIN::ClearPedTasksImmediately(ped);
							PED::SetPedIntoVehicle(GetLocalPlayer().m_ped, veh, -1);
						}
					}
				}
			}
		}
		//Entity EntityAimedAt = 0;
		//if (PLAYER::GetEntityPlayerIsFreeAimingAt(GetLocalPlayer().m_id, &EntityAimedAt)) {
		//	if (PED::IsPedShooting(GetLocalPlayer().m_ped)) {
		//		//if (ENTITY::IsEntityAVehicle(EntityAimedAt)) {
		//		//	GetEntityControl()->SimpleRequestControl(EntityAimedAt);
		//		GetEntityControl()->SimpleRequestControl(EntityAimedAt);
		//		if (NETWORK::NetworkHasControlOfEntity(EntityAimedAt)) {
		//			ENTITY::SetEntityAsMissionEntity(EntityAimedAt, 0, 1);
		//			Ped ped = VEHICLE::GetPedInVehicleSeat(EntityAimedAt, -1, 1);
		//			BRAIN::ClearPedTasksImmediately(ped);
		//			BRAIN::ClearPedSecondaryTask(ped);
		//			BRAIN::ClearPedTasks(ped);
		//			PED::SetPedIntoVehicle(GetLocalPlayer().m_ped, EntityAimedAt, 1);
		//		}
		//	}
		//}
	}

	void RopeGun() { 
		if (PED::IsPedShooting(GetLocalPlayer().m_ped)) {
			if (!ENTITY::DoesEntityExist(vars.justCause2Entities[0]) && !ENTITY::DoesEntityExist(vars.justCause2Entities[1])) {
				Entity aimed = 0;
				if (PLAYER::GetEntityPlayerIsFreeAimingAt(GetLocalPlayer().m_id, &aimed)) {
					vars.justCause2Entities[0] = aimed;
					Vector3 entCoord = ENTITY::GetEntityCoords(vars.justCause2Entities[0], 1);
					float length = GetLocalPlayer().m_coordinates.Distance(entCoord) + 20;
					vars.justCause2Rope = PHYSICS::AddRope(GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, GetLocalPlayer().m_coordinates.z, 0, 0, 0, length, 4, length, 0.5f, 0.5f, false, false, true, 1.0f, false, 0);
					PHYSICS::RopeLoadTextures();
					PHYSICS::ActivatePhysics(vars.justCause2Rope);
				}
			} else if (ENTITY::DoesEntityExist(vars.justCause2Entities[0]) && !ENTITY::DoesEntityExist(vars.justCause2Entities[1])) {
				Entity aimed = 0;
				if (PLAYER::GetEntityPlayerIsFreeAimingAt(GetLocalPlayer().m_id, &aimed)) {
					vars.justCause2Entities[1] = aimed;
					Vector3 entCoord0 = ENTITY::GetEntityCoords(vars.justCause2Entities[0], 1);
					Vector3 aimingCoords = ENTITY::GetEntityCoords(vars.justCause2Entities[1], 1);
					aimingCoords.z += 2;

					PHYSICS::AttachEntitiesToRope(vars.justCause2Rope, vars.justCause2Entities[0], vars.justCause2Entities[1], entCoord0.x, entCoord0.y, entCoord0.z, aimingCoords.x, aimingCoords.y, aimingCoords.z, entCoord0.Distance(aimingCoords), 0, 0, 0, 0);
					PHYSICS::PinRopeVertex(vars.justCause2Rope, PHYSICS::GetRopeVertexCount(vars.justCause2Rope) - 1, aimingCoords.x, aimingCoords.y, aimingCoords.z);
					vars.justCause2Entities[0] = 0;
					vars.justCause2Entities[1] = 0;
				}
			}
		}

		if (ENTITY::DoesEntityExist(vars.justCause2Entities[0]) && !ENTITY::DoesEntityExist(vars.justCause2Entities[1])) {
			Vector3 rHand = PED::GetPedBoneCoords(GetLocalPlayer().m_ped, 6286, 0, 0, 0);
			PHYSICS::PinRopeVertex(vars.justCause2Rope, 0, rHand.x, rHand.y, rHand.z);
			Vector3 entCoord1 = ENTITY::GetEntityCoords(vars.justCause2Entities[0], 1);
			PHYSICS::PinRopeVertex(vars.justCause2Rope, PHYSICS::GetRopeVertexCount(vars.justCause2Rope) - 1, entCoord1.x, entCoord1.y, entCoord1.z);
		}

		/*if (PED::IsPedShooting(GetLocalPlayer().m_ped)) {
			if (!ENTITY::DoesEntityExist(vars.justCause2Entities[0]) && !ENTITY::DoesEntityExist(vars.justCause2Entities[1])) {
				if (PED::GetPedConfigFlag(GetLocalPlayer().m_ped, PED_FLAG_IS_AIMING, 1)) {
					Raycast raycast = RaycastInfrontOld(9999.0f);
					Entity aimed = 0;
					if (PLAYER::GetEntityPlayerIsFreeAimingAt(GetLocalPlayer().m_id, &aimed)) {
						vars.justCause2Entities[0] = aimed;
						Vector3 entCoord = ENTITY::GetEntityCoords(vars.justCause2Entities[0], 1);
						float length = GetLocalPlayer().m_coordinates.Distance(entCoord);
						vars.justCause2Rope = PHYSICS::AddRope(GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, GetLocalPlayer().m_coordinates.z, 0, 0, 0, length, 4, length, 0.5f, 0.5f, false, false, true, 1.0f, false, 0);
						PHYSICS::RopeLoadTextures();
						PHYSICS::ActivatePhysics(vars.justCause2Rope);
					}
				}
			}
			else if (ENTITY::DoesEntityExist(vars.justCause2Entities[0]) && !ENTITY::DoesEntityExist(vars.justCause2Entities[1])) {
				if (PED::GetPedConfigFlag(GetLocalPlayer().m_ped, PED_FLAG_IS_AIMING, 1)) {
					Entity aimed2 = 0;
					if (PLAYER::GetEntityPlayerIsFreeAimingAt(GetLocalPlayer().m_id, &aimed2)) {
						vars.justCause2Entities[1] = aimed2;
						Vector3 entCoord0 = ENTITY::GetEntityCoords(vars.justCause2Entities[0], 1);
						vars.justCause2Entities[1] = aimed2;
						Vector3 aimingCoords = ENTITY::GetEntityCoords(vars.justCause2Entities[1], 1);
						aimingCoords.z += 2;
						PHYSICS::AttachEntitiesToRope(vars.justCause2Rope, vars.justCause2Entities[0], vars.justCause2Entities[1], entCoord0.x, entCoord0.y, entCoord0.z, aimingCoords.x, aimingCoords.y, aimingCoords.z, entCoord0.Distance(aimingCoords), 0, 0, 0, 0);
						PHYSICS::PinRopeVertex(vars.justCause2Rope, PHYSICS::GetRopeVertexCount(vars.justCause2Rope) - 1, aimingCoords.x, aimingCoords.y, aimingCoords.z);
						vars.justCause2Entities[0] = 0;
						vars.justCause2Entities[1] = 0;
					}
				}
			}
		}
		if (ENTITY::DoesEntityExist(vars.justCause2Entities[0]) && !ENTITY::DoesEntityExist(vars.justCause2Entities[1])) {
			Vector3 rHand = PED::GetPedBoneCoords(GetLocalPlayer().m_ped, 6286, 0, 0, 0);
			PHYSICS::PinRopeVertex(vars.justCause2Rope, 0, rHand.x, rHand.y, rHand.z);
			Vector3 entCoord1 = ENTITY::GetEntityCoords(vars.justCause2Entities[0], 1);
			PHYSICS::PinRopeVertex(vars.justCause2Rope, PHYSICS::GetRopeVertexCount(vars.justCause2Rope) - 1, entCoord1.x, entCoord1.y, entCoord1.z);
		}*/

	}

	void AirstrikeGun() {
		if (PED::IsPedShooting(GetLocalPlayer().m_ped)) {
			Vector3 coords;
			if (WEAPON::GetPedLastWeaponImpactCoord(GetLocalPlayer().m_ped, &coords)) {
				Vector3 Launch = { coords.x, coords.y, coords.z + 150 };
				MISC::ShootSingleBulletBetweenCoords(Launch.x, Launch.y, Launch.z, coords.x, coords.y, coords.z, 9999, 1, 0x63AB0442, GetLocalPlayer().m_ped, true, 0, -1);
			}
		}
	}

	void RapidFire() {
		if (!PED::IsPedInAnyVehicle(GetLocalPlayer().m_ped, 1)) {
			if (PAD::IsControlPressed(2, 208) || (GetKeyState(VK_LBUTTON) & 0x8000) != 0 && GetLocalPlayer().m_hasWeaponInHand) {
				static int TIMER;
				Utils::DoTimedFunction(&TIMER, 100, [] {
					Vector3 Start = ENTITY::GetWorldPositionOfEntityBone(GetLocalPlayer().m_ped, PED::GetPedBoneIndex(GetLocalPlayer().m_ped, 0x6F06));
					Vector3 inFrontOfWepCoords;
					inFrontOfWepCoords.x = 0.0f;
					inFrontOfWepCoords.y = 200;
					inFrontOfWepCoords.z = MISC::Tan(CAM::GetGameplayCamRelativePitch()) * inFrontOfWepCoords.y;
					Vector3 End = ENTITY::GetOffsetFromEntityInWorldCoords(GetLocalPlayer().m_ped, inFrontOfWepCoords.x, inFrontOfWepCoords.y, inFrontOfWepCoords.z);
					MISC::ShootSingleBulletBetweenCoords(Start.x, Start.y, Start.z, End.x, End.y, End.z, 250, 1, GetLocalPlayer().m_weaponHash, GetLocalPlayer().m_ped, 0, 1, 500.0f);
				});
			}
		}
	}

	void AimedExplosive() {
		if ((GetKeyState(VK_RBUTTON) & 0x100) != 0 || PAD::IsDisabledControlPressed(2, INPUT_FRONTEND_RB)) {
			ENTITY::SetEntityHeading(GetLocalPlayer().m_ped, CAM::_GetGameplayCamRot(2).z);
			Raycast cast = CastInfront(999.0f, CAM::GetGameplayCamCoord(), -1);
			Vector3 rightEye = PED::GetPedBoneCoords(GetLocalPlayer().m_ped, 31086, 0.037f, 0, 0);
			if (cast.hit) {
				GRAPHICS::DrawLine(rightEye.x, rightEye.y, rightEye.z, cast.endCoords.x, cast.endCoords.y, cast.endCoords.z, 255, 0, 0, 255);
				FIRE::AddExplosion(cast.endCoords.x, cast.endCoords.y, cast.endCoords.z, 18, 1.0f, true, false, 0.1f, false);
			}
		}
	}

	

	void ForceGun() {
		if (PED::IsPedShooting(GetLocalPlayer().m_ped)) {
			static Entity hitEntity = 0;
			if (PLAYER::GetEntityPlayerIsFreeAimingAt(GetLocalPlayer().m_id, &hitEntity)) {
				if (ENTITY::IsEntityAPed(hitEntity)) {
					hitEntity = PED::GetVehiclePedIsIn(hitEntity, 1);
				}
				GetEntityControl()->RequestControl("[FG]", hitEntity, [](Entity ent) {
					Vector3 camCoord = CAM::GetGameplayCamCoord();
					Vector3 infront;
					Utils::GetCameraDirection(&infront.x, &infront.y, &infront.z);
					ENTITY::ApplyForceToEntity(ent, 3, camCoord.x + (infront.x * 999.0f), camCoord.y + (infront.y * 999.0f), camCoord.z + (infront.z * 999.0f), 0, 0, 0, 0, false, true, true, false, true);
				});
			}
		}
	}

	bool checkNear(Vector3 a, Vector3 b, float range) {
		if (fabs(a.x - b.x) > range || fabs(a.y - b.y) > range || fabs(a.z - b.z) > range)
			return false;
		return true;
	}
	
	Entity grav_entity;

	void PickUpGun() {
		DWORD tempPed, tempWeap;

			PLAYER::GetEntityPlayerIsFreeAimingAt(GetLocalPlayer().m_id, &grav_entity);
			if (ENTITY::DoesEntityExist(grav_entity) && checkNear(ENTITY::GetEntityCoords(GetLocalPlayer().m_id, 1), ENTITY::GetEntityCoords(grav_entity, 1), vars.pickuprange));
			if (PED::IsPedInAnyVehicle(grav_entity, 0)) grav_entity = PED::GetVehiclePedIsIn(grav_entity, 0);
		
		tempPed = GetLocalPlayer().m_id; WEAPON::GetCurrentPedWeapon(GetLocalPlayer().m_id, &tempWeap, 1);
		if ((PAD::IsDisabledControlPressed(0, 25) || PLAYER::IsPlayerTargettingAnything(tempPed)) && ENTITY::DoesEntityExist(grav_entity))
		{
			Vector3 gameplayCam = CAM::_GetGameplayCamCoords();
			Vector3 gameplayCamRot = CAM::GetGameplayCamRot(0);
			Vector3 gameplayCamDirection = RotationToDirection(gameplayCamRot);
			Vector3 startCoords = addVector(gameplayCam, (multiplyVector(gameplayCamDirection, vars.distancefromgun)));
			Vector3 endCoords = addVector(gameplayCam, (multiplyVector(gameplayCamDirection, 500.0f)));
			ENTITY::SetEntityCollision(grav_entity, 0, 1);
			WorldMenuVars::vars.RequestControlOfEnt(grav_entity);
			if (ENTITY::IsEntityAPed(grav_entity)) ENTITY::SetEntityInvincible(grav_entity, 1);
			if (PED::IsPedShooting(GetLocalPlayer().m_ped) == 0) ENTITY::SetEntityCoordsNoOffset(grav_entity, startCoords.x, startCoords.y, startCoords.z, 0, 0, 0);
			if (ENTITY::IsEntityAVehicle(grav_entity) || ENTITY::IsEntityAPed(grav_entity)) ENTITY::SetEntityHeading(grav_entity, ENTITY::GetEntityHeading(GetLocalPlayer().m_ped) + 90.0f);
			if (PED::IsPedShooting(GetLocalPlayer().m_ped)){
				WorldMenuVars::vars.RequestControlOfEnt(grav_entity);
				ENTITY::SetEntityCollision(grav_entity, 1, 1);
				ENTITY::SetEntityHeading(grav_entity, ENTITY::GetEntityHeading(GetLocalPlayer().m_ped));
				ENTITY::ApplyForceToEntity(grav_entity, 1, 0.0f, 350.0f, 2.0f + endCoords.z, 2.0f, 0.0f, 0.0f, 0, 1, 1, 1, 0, 1);
				WAIT(1000);
				grav_entity = -1;
				return;
			}
		}
		else {
			WorldMenuVars::vars.RequestControlOfEnt(grav_entity);
			ENTITY::SetEntityCollision(grav_entity, 1, 1);
			grav_entity = -1;
		}
	}

	Hash usableWeaponHashes[85] = {
		126349499,
		2694266206,
		1233104067,
		101631238,
		911657153,
		1834241177,
		0x1B06D571,
		0x5EF9FEC4,
		0x22D8FE39,
		0x99AEEB3B,
		0x2BE6766B,
		0x13532244,
		0xBFEFFF6D,
		0x83BF0278,
		0xAF113F99,
		0x9D07F764,
		0x7FD62962,
		0x1D073A89,
		0x7846A318,
		0xE284C527,
		0xC472FE2,
		0x5FC3C11,
		0xA284510B,
		0xB1CA77B1,
		0x42BF8A85,
		0x93E220BD,
		0xFDBC8A50,
		0x2C3731D9,
		0x24B17070,
		0x34A67B97,
		0xFBAB5776,
		0x99B507EA,
		0x678B81B1,
		0x4E875F73,
		0x958A4A8F,
		0x84BD7BFD,
		0x440E4788,
		0xEFE7E2DF,
		0x9D61E50F,
		0xF9E6AA4B,
		0xC0A3098D,
		0xBFD21232,
		0x476BF155,
		0xAF3696A1,
		0xB62D1F67,
		0xD205520E,
		0x7F229F94,
		0x61012683,
		0x83839C4,
		0x92A27487,
		0xA89CB99E,
		0x7F7497E5,
		0x47757124,
		0x3AABBBAA,
		0xC734385A,
		0xAB564B93,
		0x63AB0442,
		0xF9DCBF2D,
		0xA3D4D34,
		0xD8DF3C3C,
		0xDC4DB296,
		0xDD5DF8D9,
		0xDB1AA450,
		0xEF951FBB,
		0x624FE830,
		0x8BB05FD7,
		0xC1B3C3D1,
		0xDFE37640,
		0x78A97CD0,
		0xA914799,
		0x394F415C,
		0x19044EE0,
		0x781FE4A,
		0x12E82D3D,
		0x176898A6,
		0x787F0BB,
		0xE232C28C,
		0xD04C944D,
		0x0A3D4D34,
		0x6D544C99,
		0x2C082D7D,
		0xCD274149,
		0xBD248B55,
		0xBA45E8B8,
		0x94117305,
	};

	void ModelChangeGun() {
		Entity EntityAimedAt = 0;
		if (PLAYER::GetEntityPlayerIsFreeAimingAt(GetLocalPlayer().m_id, &EntityAimedAt)) {
			if (ENTITY::IsEntityAPed(EntityAimedAt)) {
				Vector3 VictimRot = ENTITY::GetEntityRotation(EntityAimedAt, 0);
				Vector3 VictimPos = ENTITY::GetEntityCoords(EntityAimedAt, false);
				Hash VictimsModel = ENTITY::GetEntityModel(EntityAimedAt);

				int SWITCH_DRAWABLE_VAR[13];
				int SWITCH_TEXTURE_VAR[13];
				int SWITCH_PALETTE_VAR[13];

				for (int i = 0; i < 12; i++) {
					SWITCH_DRAWABLE_VAR[i] = PED::GetPedDrawableVariation(EntityAimedAt, i);
					SWITCH_TEXTURE_VAR[i] = PED::GetPedTextureVariation(EntityAimedAt, i);
					SWITCH_PALETTE_VAR[i] = PED::GetPedPaletteVariation(EntityAimedAt, i);
				}

				for (int i = 0; i < 12; i++)
					PED::SetPedComponentVariation(GetLocalPlayer().m_ped, i, SWITCH_DRAWABLE_VAR[i], SWITCH_TEXTURE_VAR[i], SWITCH_PALETTE_VAR[i]);

				int VehicleID = -1;
				int Seat = -1;
				if (PED::IsPedInAnyVehicle(EntityAimedAt, false)) {
					VehicleID = PED::GetVehiclePedIsIn(EntityAimedAt, false);
					for (int i = -1; i < VEHICLE::GetVehicleNumberOfPassengers(VehicleID); i++) {
						if (VEHICLE::GetPedInVehicleSeat(VehicleID, i, 0) == EntityAimedAt)
							Seat = i;
					}
				}

				Vector3 myCoords = GetLocalPlayer().m_coordinates;
				ENTITY::SetEntityCoords(EntityAimedAt, myCoords.x, myCoords.y, myCoords.z, true, false, false, true);

				Vector3 MyRot = ENTITY::GetEntityRotation(GetLocalPlayer().m_ped, 0);
				ENTITY::SetEntityRotation(EntityAimedAt, MyRot.x, MyRot.y, MyRot.z, 0, false);

				if (VehicleID != -1) {
					PED::SetPedIntoVehicle(GetLocalPlayer().m_ped, VehicleID, Seat);
				} else {
					ENTITY::SetEntityCoords(GetLocalPlayer().m_ped, VictimPos.x, VictimPos.y, VictimPos.z, true, false, false, true);
					ENTITY::SetEntityRotation(GetLocalPlayer().m_ped, VictimRot.x, VictimRot.y, VictimRot.z, 0, false);
				}

				ModelMenuVars::SetModelI(VictimsModel);

				GetFiberPool()->DoJob([=] {
					WAIT(1000);
					int Ammo = -1;
					for (int i = 0; i < 82; i++) {
						WEAPON::GetMaxAmmo(GetLocalPlayer().m_ped, usableWeaponHashes[i], &Ammo);
						WEAPON::GiveWeaponToPed(GetLocalPlayer().m_ped, usableWeaponHashes[i], Ammo, false, true);
					}
				});
			}
		}
	}

	void CrazyFlare() {

		Explosions::sExplosion* Explosion = Explosions::GetExplosion(EXP_TAG_FLARE);
		Explosions::sExplosionFX* ExplosionFX = Explosions::GetExplosionFX(EXP_VFXTAG_DIR_FLAME);

		if (Explosion == nullptr || ExplosionFX == nullptr) {
			return;
		}

		if (vars.crazyflare) {
			WEAPON::GiveWeaponToPed(GetLocalPlayer().m_ped, 0x497FACC3, -1, false, true);
			Explosion->EndRadius = 500;
			Explosion->InitSpeed = 100;
			Explosion->ForceFactor = 10000;
			Explosion->VFXTagNameHash = EXP_VFXTAG_DIR_FLAME;
			ExplosionFX->Scale = 2.5f;
		}
		else {
			Explosion->EndRadius = 1;
			Explosion->InitSpeed = 0.35f;
			Explosion->ForceFactor = 0;
			Explosion->VFXTagNameHash = EXP_VFXTAG_FLARE;
			ExplosionFX->Scale = 1;
		}


	}
}

void WeaponMenu::Init() {
	setParentSubmenu<MainMenu>();
	setName("Weapon", true, true);

	addOption(SubmenuOption("Weapons")
		.addSubmenu<WeaponWeaponsMenu>()
		.addTranslation().addHotkey()
		.addTooltip("Give weapons etc"));

	addOption(SubmenuOption("Visuals")
		.addSubmenu<WeaponVisualsMenu>()
		.addTranslation().addHotkey()
		.addTooltip("Weapon visuals"));

	addOption(SubmenuOption("Ammo modifiers")
		.addSubmenu<WeaponAmmoModifierMenu>()
		.addTranslation().addHotkey()
		.addTooltip("Weapon ammo modifiers"));

	addOption(SubmenuOption("Aimbot")
		.addSubmenu<WeaponAimbotMenu>()
		.addTranslation().addHotkey()
		.addTooltip("Weapon aimbot")
		.addRequirement([] { return GetAuth()->IsVIP(); }));

	addOption(SubmenuOption("Owned triggerbot")
		.addSubmenu<ownedTriggerbotMenu>()
		.addTranslation().addHotkey()
		.addTooltip("Kill other people giving credit to someone else, with your weapons!")
		.addRequirement([] { return GetAuth()->IsVIP(); }));

	addOption(SubmenuOption("Shoot entities")
		.addSubmenu<WeaponShootEntitiesMenu>().addTranslation().addHotkey()
		.addTooltip("Shoot entities"));

	addOption(BreakOption("General"));

	addOption(ToggleOption("No reload")
		.addToggle(vars.noReload)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("No more reloading"));

	addOption(ToggleOption("Infinite ammo")
		.addToggle(vars.infiniteAmmo)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Infinite ammo"));

	addOption(ToggleOption("Rapid fire")
		.addToggle(vars.rapidFire)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Shoot rapidly"));

	addOption(ToggleOption("One shot one kill")
		.addToggle(vars.oneShotOneKill)
		.addFunction([&] {OneShotOneKill(vars.oneShotOneKill); })
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("One bullet kills"));

	//addOption(BreakOption("Shoot Options"));

	/*addOption(ToggleOption("Delete gun")
		.addToggle(vars.deleteGun)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Delete entities you shoot"));

	addOption(ToggleOption("Drive it gun")
		.addToggle(vars.driveitgun)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Drive the vehicle you shoot"));

	addOption(ToggleOption("Shrink ray")
		.addToggle(vars.shrinkRay)
		.addTranslation().addHotkey().canBeSaved()
		.addFunction([] { if (vars.shrinkRay) WEAPON::GiveWeaponToPed(GetLocalPlayer().m_ped, 0x3656C8C1, -1, false, true); })
		.addTooltip("Shrink peds"));

	addOption(ToggleOption("Ped defibrillator")
		.addToggle(vars.defibrillator)
		.addTranslation().addHotkey().canBeSaved()
		.addFunction([] { if (vars.defibrillator) WEAPON::GiveWeaponToPed(GetLocalPlayer().m_ped, 0x3656C8C1, -1, false, true); })
		.addTooltip("Revive peds"));

	addOption(ToggleOption("Force gun")
		.addToggle(vars.forceGun)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Force entities away when you shoot them"));

	addOption(ToggleOption("Model change gun")
		.addToggle(vars.modelChange).addTranslation().addHotkey()
		.addTooltip("Model change gun"));*/

	addOption(BreakOption("Entity movement").addTranslation());

	addOption(ToggleOption("Gravity gun")
		.addToggle(vars.gravityGun)
		.addTranslation().addHotkey().canBeSaved()
		.addFunction([] {
		if (!vars.gravityGun) {
			vars.gravityGunTarget = 0;
			vars.gravityGunNewTarget = 0;
		}
	})
		.addTooltip("Move around entities (first one will hit you)"));

	addOption(ToggleOption("Pickup gun")
		.addToggle(vars.pickupgun)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Move around entities"));

	addOption(NumberOption<float>(SCROLL, "Pickup range")
		.addNumber(vars.pickuprange, "%.1f", 5.0f).addMin(1.0f).addMax(100.0f)
		.addHotkey()
		.addTooltip("Control the range that pickup gun can pick items up"));

	addOption(NumberOption<float>(SCROLL, "Distance from gun")
		.addNumber(vars.distancefromgun, "%.1f", 1.0f).addMin(1.0f).addMax(100.0f)
		.addHotkey()
		.addTooltip("Control the distance of the entity from your gun using pickup gun"));

	addOption(BreakOption("Misc"));
	
	addOption(ToggleOption("Dead eye")
		.addToggle(vars.deadEye)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Activate dead eye"));

	addOption(ToggleOption("Weapons in interiors and passive mode")
		.addToggle(vars.weaponInteriors)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Enables you to use weapons in interiors and in passive mode"));

	addOption(ToggleOption("Aimed Explosive")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.aimedexplosive).addTranslation().addHotkey()
		.addTooltip("Aim and explode what you are looking at - use right mouse button / RB"));

	/*addOption(ToggleOption("Rope gun")
		.addToggle(vars.ropeGun)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Attach two entities together with rope"));*/

	/*addOption(ToggleOption("Crazy flare")
		.addToggle(vars.crazyflare)
		.addTranslation().addHotkey().canBeSaved()
		.addFunction([] { if (vars.crazyflare) Explosions::sExplosion* Explosion = Explosions::GetExplosion(EXP_TAG_FLARE);
	Explosions::sExplosionFX* ExplosionFX = Explosions::GetExplosionFX(EXP_VFXTAG_DIR_FLAME); })
		.addTooltip(""));*/

}

/*Update once when submenu is opened*/
void WeaponMenu::UpdateOnce() {}

/*Update while submenu is active*/
void WeaponMenu::Update() {}

/*Background update*/
void WeaponMenu::FeatureUpdate() {
	if (GetLocalPlayer().m_hasWeaponInHand) {
		if (vars.oneShotOneKill) OneShotOneKill(true);
		if (vars.infiniteAmmo) InfiniteAmmo();
		if (vars.deadEye) DeadEye();
		if (vars.shrinkRay) ShrinkRay();
		if (vars.gravityGun) GravityGun();
		if (vars.defibrillator) Defibrillator();
		if (vars.deleteGun) DeleteGun();
		if (vars.driveitgun) DriveItGun();
		if (vars.ropeGun) RopeGun();
		if (vars.airstrikeGun) AirstrikeGun();
		if (vars.rapidFire) RapidFire();
		if (vars.forceGun) ForceGun();
		if (vars.noReload) NoReload();
		if (vars.modelChange) ModelChangeGun();
		if (vars.aimedexplosive) AimedExplosive();
		if (vars.pickupgun) PickUpGun();
		if (vars.crazyflare) CrazyFlare();
	}
}

/*Singleton*/
WeaponMenu* _instance;
WeaponMenu* WeaponMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new WeaponMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
WeaponMenu::~WeaponMenu() { delete _instance; }