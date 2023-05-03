#include "stdafx.h"
#include "weaponAmmoModifier.h"
#include "../weaponMenu.h"
#include "../local/particleMenu.h"

using namespace WeaponAmmoModifierMenuVars;

namespace WeaponAmmoModifierMenuVars {
	Vars vars;

	ScrollStruct<int> bulletImpacts[] = {
		TranslationString("Money Bags", true), 0,
		TranslationString("Teleport (Me)", true), 1,
		TranslationString("Explosion", true), 2,
		TranslationString("Print Position", true), 3,
		TranslationString("Airstrike", true), 4,
		TranslationString("Flare", true), 5,
		TranslationString("Water Fountain", true), 6,
		TranslationString("Gas Fountain", true), 7
	};

	ScrollStruct<Hash> bulletAmmo[] = {
		TranslationString("RPG", true), 0xb1ca77b1,
		TranslationString("Firework", true), 0x7f7497e5,
		//TranslationString("Red Laser", true), 0x5d6660ab,
		//TranslationString("Green Laser", true), 0xeffd014b,
		TranslationString("Tank", true), 0x73f7c04b,
		TranslationString("Space Rocket", true), 0xf8a3939f,
		TranslationString("Plane Rocket", true), 0xcf0896e0,
		TranslationString("Snowball", true), 0x787F0BB,
		TranslationString("Flare", true), 0x497FACC3,
	};

	ScrollStruct<ParticleGunStruct> m_particleGunParticles[] = {
		TranslationString("Alien Teleport", true),{ "scr_rcbarry1", "scr_alien_teleport", 1.5f },
		TranslationString("Money", true),{ "scr_paletoscore", "scr_paleto_banknotes", 2.5f },
		TranslationString("Blood", true),{ "scr_solomon3", "scr_trev4_747_blood_impact", 0.9f },
		TranslationString("Alien Disintegrate", true),{ "scr_rcbarry1", "scr_alien_disintegrate", 0.9f },
		TranslationString("Electric", true),{ "scr_trevor1", "scr_trev1_trailer_boosh", 1.5f },
		TranslationString("Fire", true),{ "scr_agencyheist", "scr_fbi_dd_breach_smoke", 0.4f },
		TranslationString("Clown Death", true),{ "scr_rcbarry2", "scr_clown_death", 2.0f },
		TranslationString("Clown Appears", true),{ "scr_rcbarry2", "scr_clown_appears", 2.0f },
		TranslationString("Flowers", true),{ "scr_rcbarry2", "scr_exp_clown", 1.5f },
		TranslationString("Fireworks", true),{ "scr_indep_fireworks", "scr_indep_firework_starburst", 0.5f }
	};

	void ExplosiveWhaleGun() {
		if (PED::IsPedShooting(GetLocalPlayer().m_ped)) {
			Hash model = Utils::GetHashKey("a_c_killerwhale");
			GetEntityControl()->SimpleRequestModel(model);

			Vector3 infront;
			Utils::GetCameraDirection(&infront.x, &infront.y, &infront.z);
			Vector3 camCoord = CAM::GetGameplayCamCoord();

			Ped spawnedPed = PED::CreatePed(26, model, camCoord.x + (infront.x * 5.f), camCoord.y + (infront.y * 5.f), camCoord.z + (infront.z * 5.f), 1, 1, 0);
			if (ENTITY::DoesEntityExist(spawnedPed)) {
				ENTITY::SetEntityRecordsCollisions(spawnedPed, true);

				Vector3 dir = Utils::RotateToDirection(&CAM::GetGameplayCamRot(0));

				for (int i = 0; i < 75; i++) {
					if (ENTITY::HasEntityCollidedWithAnything(spawnedPed)) break;
					ENTITY::ApplyForceToEntity(spawnedPed, 1, dir.x * 10.0f, dir.y * 10.0f, dir.z * 10.0f, 0.0f, 0.0f, 0.0f, 0, 0, 1, 1, 0, 1);
					WAIT(0);
				}

				Vector3 coords = ENTITY::GetEntityCoords(spawnedPed, 1);
				ENTITY::SetEntityAsMissionEntity(spawnedPed, 1, 1);
				PED::DeletePed(&spawnedPed);
				FIRE::AddExplosion(coords.x, coords.y, coords.z, 9, 25, 1, 0, 0.5, 0);
			}
		}
	}


	void MissileGun() {
		Vector3 gameplayRotation = CAM::GetGameplayCamRot(2);

		int rocketHash = Utils::GetHashKey("prop_ld_bomb_01");
		if (!STREAMING::HasModelLoaded(rocketHash))
			STREAMING::RequestModel(rocketHash);

		if (PED::IsPedShooting(GetLocalPlayer().m_ped) && !vars.missileGunRunning) {
			Vector3 spawnPos = ENTITY::GetOffsetFromEntityInWorldCoords(GetLocalPlayer().m_ped, 0.0f, 3.0f, 0.8f);

			vars.missileEntity = OBJECT::CreateObject(rocketHash, spawnPos.x, spawnPos.y, spawnPos.z, 1, 0, 1);
			if (ENTITY::DoesEntityExist(vars.missileEntity)) {
				ENTITY::SetEntityRotation(vars.missileEntity, gameplayRotation.x, gameplayRotation.y, gameplayRotation.z, 2, 1);

				Vector3 entityRotation = ENTITY::GetEntityRotation(vars.missileEntity, 2);
				vars.missileCam = CAM::CreateCamWithParams("DEFAULT_SCRIPTED_CAMERA", spawnPos.x, spawnPos.y, spawnPos.z, entityRotation.x, entityRotation.y, entityRotation.z, 65.0f, 1, 2);
				CAM::AttachCamToEntity(vars.missileCam, vars.missileEntity, 0.0f, 1.1f, 0.0f, true);
				CAM::SetCamActive(vars.missileCam, true);
				CAM::RenderScriptCams(1, 1, 750, 1, 0, 0);
				if (vars.notimelimit) {
					vars.valkyrieTimeout = MISC::GetGameTimer() + 99999999;
				} else {
					vars.valkyrieTimeout = MISC::GetGameTimer() + 12000;
				}
				GRAPHICS::SetTimecycleModifier("CAMERA_BW");
				vars.missileGunRunning = true;
			}
		}

		if (vars.missileGunRunning) {

			static int TIMER;
			Utils::DoTimedFunction(&TIMER, 1000, [&] { STREAMING::_SetFocusArea(CAM::GetCamCoord(vars.missileCam).x, CAM::GetCamCoord(vars.missileCam).y, CAM::GetCamCoord(vars.missileCam).z, 0, 0, 0); });

			if (!vars.notimelimit) {
				GRAPHICS::DrawRect(0.469f, 0.500f, 0.002f, 0.100f, 255, 255, 255, 255, 0);
				GRAPHICS::DrawRect(0.532f, 0.500f, 0.002f, 0.100f, 255, 255, 255, 255, 0);
				GRAPHICS::DrawRect(0.501f, 0.552f, 0.065f, 0.003f, 255, 255, 255, 255, 0);
				GRAPHICS::DrawRect(0.501f, 0.451f, 0.065f, 0.003f, 255, 255, 255, 255, 0);
				GRAPHICS::DrawRect(0.500f, 0.415f, 0.002f, 0.070f, 255, 255, 255, 255, 0);
				GRAPHICS::DrawRect(0.500f, 0.585f, 0.002f, 0.070f, 255, 255, 255, 255, 0);
				GRAPHICS::DrawRect(0.445f, 0.501f, 0.045f, 0.002f, 255, 255, 255, 255, 0);
				GRAPHICS::DrawRect(0.555f, 0.501f, 0.045f, 0.002f, 255, 255, 255, 255, 0);
				GRAPHICS::DrawRect(0.210f, 0.500f, 0.020f, 0.500f, 255, 255, 255, 255, 0);
			

			float height = (vars.valkyrieTimeout - MISC::GetGameTimer()) / 24000.0f;
			int usageColor[3] = {};

			if (height > 0.4f) {
				usageColor[0] = 0; usageColor[1] = 255; usageColor[2] = 0;
			}
			else if (height <= 0.4f && height > 0.3f) {
				usageColor[0] = 255; usageColor[1] = 255; usageColor[2] = 0;
			}
			else if (height <= 0.3f && height > 0.2f) {
				usageColor[0] = 255; usageColor[1] = 150; usageColor[2] = 0;
			}
			else if (height <= 0.2f) {
				usageColor[0] = 255; usageColor[1] = 0; usageColor[2] = 0;
			}
			GRAPHICS::DrawRect(0.21f, (0.5f + (0.5f / 2) - height + (height * 0.5f)), 0.02f, height, usageColor[0], usageColor[1], usageColor[2], 255, 0);
			}

			if (MISC::GetGameTimer() >= vars.valkyrieTimeout) {
				GRAPHICS::SetTimecycleModifier("");
				FIRE::AddExplosion(CAM::GetCamCoord(vars.missileCam).x, CAM::GetCamCoord(vars.missileCam).y, CAM::GetCamCoord(vars.missileCam).z, 27, 1.0f, true, false, 0.5f, false);
				ENTITY::SetEntityAsMissionEntity(vars.missileEntity, false, true);
				ENTITY::DeleteEntity(&vars.missileEntity);
				CAM::RenderScriptCams(false, 1, 750, 1, 0, 0);
				CAM::DestroyCam(vars.missileCam, true);
				vars.missileGunRunning = false;
			}
			else {

				Vector3 rocketRot = CAM::GetGameplayCamRot(2);
				CAM::SetCamRot(vars.missileCam, rocketRot.x, rocketRot.y, rocketRot.z, 2);

				ENTITY::SetEntityRotation(vars.missileEntity, rocketRot.x, rocketRot.y, rocketRot.z, 2, 1);

				float speed = 0.2f + (KeyDown(VK_SHIFT) ? 0.4f : 0.0f);
				if (KeyDown(VK_SHIFT))
					vars.valkyrieTimeout -= 20;

				Vector3 inworld = ENTITY::GetOffsetFromEntityInWorldCoords(vars.missileEntity, 0.0f, speed, 0.0f);
				ENTITY::SetEntityCoords(vars.missileEntity, inworld.x, inworld.y, inworld.z, 0, 0, 0, 1);

				Vector3 camCoord = CAM::GetCamCoord(vars.missileCam);
				Raycast cast = CastInfront(25.0f, camCoord, -1);

				if (camCoord.Distance(cast.endCoords) < 2.5f) {
					FIRE::AddExplosion(camCoord.x, camCoord.y, camCoord.z, 27, 1.0f, true, false, 0.5f, 0);
					ENTITY::SetEntityAsMissionEntity(vars.missileEntity, false, true);
					ENTITY::DeleteEntity(&vars.missileEntity);
					CAM::RenderScriptCams(false, 1, 750, 1, 0, 0);
					CAM::DestroyCam(vars.missileCam, true);
					STREAMING::SetFocusEntity(GetLocalPlayer().m_ped);
					GRAPHICS::SetTimecycleModifier("");
					vars.missileGunRunning = false;
				}
			}
		}
	}

	void ExplosiveBullets() {
		//MISC::SetExplosiveAmmoThisFrame(GetLocalPlayer().m_id);
		Raycast cast = CastInfront(999.0f, CAM::GetGameplayCamCoord(), -1);
		if (cast.endCoords != Vector3(0, 0, 0)) {
			Vector3 Coords = cast.endCoords;
			if (WEAPON::GetPedLastWeaponImpactCoord(GetLocalPlayer().m_ped, &Coords)) {
				FIRE::AddExplosion(Coords.x, Coords.y, Coords.z, 0, 5, 1, 0, 0, 0);
			}
		}
	}

	void FireBullets() {
		//MISC::SetFireAmmoThisFrame(GetLocalPlayer().m_id);
		Raycast cast = CastInfront(999.0f, CAM::GetGameplayCamCoord(), -1);
		if (cast.endCoords != Vector3(0, 0, 0)) {
			Vector3 Coords = cast.endCoords;
			if (WEAPON::GetPedLastWeaponImpactCoord(GetLocalPlayer().m_ped, &Coords)) {
				FIRE::StartScriptFire(Coords.x, Coords.y, Coords.z, 5, true);
			}
		}
	}


	void PaintVehicleGun() {

		Entity EntityAimedAt = 0;
		if (PLAYER::GetEntityPlayerIsFreeAimingAt(GetLocalPlayer().m_id, &EntityAimedAt)) {
			if (PED::IsPedShooting(GetLocalPlayer().m_ped)) {
				if (ENTITY::IsEntityAVehicle(EntityAimedAt)) {
				GetEntityControl()->SimpleRequestControl(EntityAimedAt);
				if (NETWORK::NetworkHasControlOfEntity(EntityAimedAt)) {
					ENTITY::SetEntityAsMissionEntity(EntityAimedAt, 0, 1);
					VEHICLE::SetVehicleCustomPrimaryColour(EntityAimedAt, MISC::GetRandomIntInRange(0, 255), MISC::GetRandomIntInRange(0, 255), MISC::GetRandomIntInRange(0, 255));
					VEHICLE::SetVehicleCustomSecondaryColour(EntityAimedAt, MISC::GetRandomIntInRange(0, 255), MISC::GetRandomIntInRange(0, 255), MISC::GetRandomIntInRange(0, 255));
					}
				}
				else if (ENTITY::IsEntityAPed(EntityAimedAt))
				{
					if (PED::GetVehiclePedIsIn(EntityAimedAt, false) != NULL)
					{
						Vehicle veh = PED::GetVehiclePedIsIn(EntityAimedAt, false);
						Ped ped = VEHICLE::GetPedInVehicleSeat(veh, -1, 1);
						if (ped != NULL)
						{
							VEHICLE::SetVehicleCustomPrimaryColour(veh, MISC::GetRandomIntInRange(0, 255), MISC::GetRandomIntInRange(0, 255), MISC::GetRandomIntInRange(0, 255));
							VEHICLE::SetVehicleCustomSecondaryColour(veh, MISC::GetRandomIntInRange(0, 255), MISC::GetRandomIntInRange(0, 255), MISC::GetRandomIntInRange(0, 255));
						}
					}
				}
			}
		}
	}
}

void WeaponAmmoModifierMenu::Init() {
	setParentSubmenu<WeaponMenu>();
	setName("Ammo modifiers", true, true);

	addOption(ScrollOption<int>(TOGGLE, "Impact ammo")
		.addToggle(vars.impactAmmo)
		.addScroll(vars.impactAmmoVal, 0, NUMOF(bulletImpacts) - 1, bulletImpacts)
		.addTranslation().addHotkey()
		.addTooltip("Impact ammo"));

	addOption(ScrollOption<ParticleGunStruct>(TOGGLE, "Particle ammo")
		.addToggle(vars.particleAmmo)
		.addScroll(vars.particleAmmoVal, 0, NUMOF(m_particleGunParticles) - 1, m_particleGunParticles)
		.addTranslation().addHotkey()
		.addTooltip("Particle ammo"));

	addOption(ScrollOption<Hash>(TOGGLE, "Modify ammo")
		.addToggle(vars.modifyAmmo)
		.addScroll(vars.modifyAmmoVal, 0, NUMOF(bulletAmmo) - 1, bulletAmmo)
		.addTranslation().addHotkey()
		.addTooltip("Modify ammo"));

	addOption(BreakOption("Shoot Options"));

	addOption(ToggleOption("Explosive whale gun")
		.addToggle(vars.explosiveWhale).addTranslation().addHotkey()
		.addTooltip("Explosive whale gun"));

	addOption(ToggleOption("Missile gun")
		.addToggle(vars.missilegun)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Shoot missiles"));

	addOption(ToggleOption("Disable missile gun timeout")
		.addRequirement([] { return vars.missilegun; })
		.addToggle(vars.notimelimit)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("This will disable the missile gun timeout and allow it to fly indefinitely"));

	addOption(ToggleOption("Paint vehicle gun")
		.addToggle(vars.paintvehgun)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Paint vehicles you shoot at"));

	addOption(ToggleOption("Explosive bullets")
		.addToggle(vars.explosiveBullets)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Explosion where you shoot"));

	addOption(ToggleOption("Fire bullets")
		.addToggle(vars.fireBullets)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Fire on entities you shoot"));

	addOption(ToggleOption("Delete gun")
		.addToggle(WeaponMenuVars::vars.deleteGun)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Delete entities you shoot"));

	addOption(ToggleOption("Drive it gun")
		.addToggle(WeaponMenuVars::vars.driveitgun)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Drive the vehicle you shoot"));

	addOption(ToggleOption("Shrink ray")
		.addToggle(WeaponMenuVars::vars.shrinkRay)
		.addTranslation().addHotkey().canBeSaved()
		.addFunction([] { if (WeaponMenuVars::vars.shrinkRay) WEAPON::GiveWeaponToPed(GetLocalPlayer().m_ped, 0x3656C8C1, -1, false, true); })
		.addTooltip("Shrink peds"));

	addOption(ToggleOption("Ped defibrillator")
		.addToggle(WeaponMenuVars::vars.defibrillator)
		.addTranslation().addHotkey().canBeSaved()
		.addFunction([] { if (WeaponMenuVars::vars.defibrillator) WEAPON::GiveWeaponToPed(GetLocalPlayer().m_ped, 0x3656C8C1, -1, false, true); })
		.addTooltip("Revive peds"));

	addOption(ToggleOption("Force gun")
		.addToggle(WeaponMenuVars::vars.forceGun)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Force entities away when you shoot them"));

	addOption(ToggleOption("Model change gun")
		.addToggle(WeaponMenuVars::vars.modelChange).addTranslation().addHotkey()
		.addTooltip("Model change gun"));
}

/*Update once when submenu is opened*/
void WeaponAmmoModifierMenu::UpdateOnce() {}

/*Update while submenu is active*/
void WeaponAmmoModifierMenu::Update() {}

/*Background update*/
void WeaponAmmoModifierMenu::FeatureUpdate() {
	if (vars.impactAmmo) {
		if (PED::IsPedShooting(GetLocalPlayer().m_ped)) {
			if (vars.impactAmmoVal == 0) {
				Vector3 coords;
				if (WEAPON::GetPedLastWeaponImpactCoord(GetLocalPlayer().m_ped, &coords)) {
					constexpr int CashHash = -1666779307;
					GetEntityControl()->SimpleRequestModel(CashHash);
					Entity e = OBJECT::CreateAmbientPickup(0x1E9A99F8, coords.x, coords.y, coords.z + 2, 0, 2500, CashHash, false, true);
					ENTITY::SetEntityAsNoLongerNeeded(&e);
				}
			} else {
				Raycast cast = CastInfront(999.0f, CAM::GetGameplayCamCoord(), -1);
				if (cast.endCoords != Vector3(0, 0, 0)) {
					Vector3 Coords = cast.endCoords;
					switch (vars.impactAmmoVal) {
						case 1: ENTITY::SetEntityCoords(GetLocalPlayer().m_ped, Coords.x, Coords.y, Coords.z, 0, 0, 0, 1); break;
						case 2:FIRE::AddExplosion(Coords.x, Coords.y, Coords.z, 0, 5, 1, 0, 0, 0); break;
						case 3:GetRenderer()->NotifyMap(va("%.3f, %.3f, %.3f", Coords.x, Coords.y, Coords.z)); break;
						case 4:MISC::ShootSingleBulletBetweenCoords(Coords.x, Coords.y, Coords.z + 50, Coords.x, Coords.y, Coords.z, 250, 0, 0xF8A3939F, GetLocalPlayer().m_ped, 1, 1, 1000); break;
						case 5:Natives::AddOwnedExplosion(GetLocalPlayer().m_ped, Coords.x, Coords.y, Coords.z, 22, 5.0, true, false, 0); break;
						case 6:Natives::AddOwnedExplosion(GetLocalPlayer().m_ped, Coords.x, Coords.y, Coords.z, 13, 5.0, true, false, 0); break;
						case 7:Natives::AddOwnedExplosion(GetLocalPlayer().m_ped, Coords.x, Coords.y, Coords.z, 9, 5.0, true, false, 0); break;
					}
				}
			}
		}
	}

	if (vars.explosiveBullets) ExplosiveBullets();
	if (vars.fireBullets) FireBullets();
	if (vars.explosiveWhale) ExplosiveWhaleGun();
	if (vars.paintvehgun) PaintVehicleGun();
	if (vars.missilegun) MissileGun();

	if (vars.particleAmmo) {
		if (PED::IsPedShooting(GetLocalPlayer().m_ped)) {
			Raycast cast = CastInfront(999.0f, CAM::GetGameplayCamCoord(), -1);
			if (cast.endCoords != Vector3(0, 0, 0)) {
				Vector3 Coords = cast.endCoords;
				if (WEAPON::GetPedLastWeaponImpactCoord(GetLocalPlayer().m_ped, &Coords)) {
					STREAMING::RequestNamedPtfxAsset(m_particleGunParticles[vars.particleAmmoVal].m_result.m_pOne);
					GRAPHICS::_UseParticleFxAssetNextCall(m_particleGunParticles[vars.particleAmmoVal].m_result.m_pOne);
					GRAPHICS::_StartParticleFxNonLoopedAtCoord2(m_particleGunParticles[vars.particleAmmoVal].m_result.m_pTwo, cast.endCoords.x, cast.endCoords.y, cast.endCoords.z, 0, 0, 0, m_particleGunParticles[vars.particleAmmoVal].m_result.m_size, 0, 0, 0);
				}
			}
		}
	}

	if (vars.modifyAmmo) {
		if (PED::IsPedShooting(GetLocalPlayer().m_ped)) {
			Vector3 p0 = ENTITY::GetWorldPositionOfEntityBone(GetLocalPlayer().m_ped, PED::GetPedBoneIndex(GetLocalPlayer().m_ped, 0x6F06));
			Vector3 p1 = ENTITY::GetOffsetFromEntityInWorldCoords(GetLocalPlayer().m_ped, 0.0f, 200, (MISC::Tan(CAM::GetGameplayCamRelativePitch()) * 200));
			MISC::ShootSingleBulletBetweenCoords(p0.x, p0.y, p0.z, p1.x, p1.y, p1.z, 250, 0, bulletAmmo[vars.modifyAmmoVal].m_result, GetLocalPlayer().m_ped, 1, 1, 10000.0f);
		}
	}
}

/*Singleton*/
WeaponAmmoModifierMenu* _instance;
WeaponAmmoModifierMenu* WeaponAmmoModifierMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new WeaponAmmoModifierMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
WeaponAmmoModifierMenu::~WeaponAmmoModifierMenu() { delete _instance; }