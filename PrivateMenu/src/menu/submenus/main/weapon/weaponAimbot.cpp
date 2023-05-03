#include "stdafx.h"
#include "weaponAimbot.h"
#include "../weaponMenu.h"

using namespace WeaponAimbotMenuVars;

namespace WeaponAimbotMenuVars {
	Vars vars;

	ScrollStruct<int> entityFilterScrollStruct[] = {
		TranslationString("Ped", true), 0,
		TranslationString("Player", true), 1,
		TranslationString("Ped + Player", true), 2
	};

	ScrollStruct<int> entityBoneScrollStruct[] = {
		TranslationString("Head", true), 0x796E,
		TranslationString("Neck", true), 0x9995,
		TranslationString("Tongue", true), 0xB987,
		TranslationString("Spine", true), 0x60F0,
		TranslationString("Left Hand", true), 0x49D9,
		TranslationString("Right Hand", true), 0xE5f2,
		TranslationString("Left Foot", true), 0x3779,
		TranslationString("Right Foot", true), 0xCC4D
	};

	int GetNearestLocalPed() {
		int nearest = 0;
		float distance = 99999.0f;
		const int ElementAmount = 50;
		const int ArrSize = ElementAmount * 2 + 2;

		Ped *peds = new Ped[ArrSize];
		peds[0] = ElementAmount;
		int PedFound = PED::GetPedNearbyPeds(GetLocalPlayer().m_ped, peds, -1);

		for (int i = 0; i < PedFound; i++) {
			int OffsetID = i * 2 + 2;
			if (ENTITY::DoesEntityExist(peds[OffsetID]) && peds[OffsetID] != GetLocalPlayer().m_ped && !PED::IsPedAPlayer(peds[OffsetID])) {
				float tmpDistance = ENTITY::GetEntityCoords(peds[OffsetID], 1).Distance(GetLocalPlayer().m_coordinates);
				if (tmpDistance < distance) {
					distance = tmpDistance;
					nearest = peds[OffsetID];
				}
			}
		}

		return nearest;
	}

	int GetNearestLocalPlayerPed() {
		int nearest = 0;
		float distance = 99999.0f;

		OnlinePlayerCallback(false, [&] (SPlayer player) {
			if (NETWORK::NetworkIsPlayerConnected(player.m_id) && NETWORK::NetworkIsPlayerActive(player.m_id)) {
				if (ENTITY::DoesEntityExist(player.m_ped) && !PED::IsPedDeadOrDying(player.m_ped, 1)) {
					float tmpDistance = player.m_coordinates.Distance(GetLocalPlayer().m_coordinates);
					if (tmpDistance < distance) {
						distance = tmpDistance;
						nearest = player.m_ped;
					}
				}
			}
		});

		return nearest;
	}

	void BasicAimbot() {
		if (PED::GetPedConfigFlag(GetLocalPlayer().m_ped, 78, 1)) {
			Entity handle = GetNearestLocalPed();
			if (handle && ENTITY::DoesEntityExist(handle) && handle != GetLocalPlayer().m_ped) {
				Vector3 targetPos = ENTITY::GetEntityCoords(handle, 1);
				BOOL exists = ENTITY::DoesEntityExist(handle);
				BOOL dead = PED::IsPedDeadOrDying(handle, 1);
				if (exists && !dead) {
					float screenX, screenY; // better fix these erros otherwise yodellingahithiterthot will throw a fit
					BOOL onScreen = GRAPHICS::GetScreenCoordFromWorldCoord(targetPos.x, targetPos.y, targetPos.z, &screenX, &screenY);
					if (ENTITY::IsEntityVisible(handle) && onScreen) {
						if (ENTITY::HasEntityClearLosToEntity(GetLocalPlayer().m_ped, handle, 1)) {
							GRAPHICS::DrawMarker(2, targetPos.x, targetPos.y, targetPos.z + 1.5f, 0.f, 0.f, 0.f, 0.f, 180.f, 0.f, 0.7f, 0.7f, 0.7f, 255, 0, 0, 120, 1, 0, 1, 1, 0, 0, 0);
							Vector3 targetCoords = PED::GetPedBoneCoords(handle, 31086, 0, 0, 0);
							PLAYER::DisablePlayerFiring(GetLocalPlayer().m_ped, 1);
							if (PAD::IsControlPressed(2, 208) || (GetKeyState(VK_LBUTTON) & 0x8000))
								PED::SetPedShootsAtCoord(GetLocalPlayer().m_ped, targetCoords.x, targetCoords.y, targetCoords.z, 1);
						}
					}
				}
			}
		}
	}

	void BasicPlayerAimbot() {
		if (PED::GetPedConfigFlag(GetLocalPlayer().m_ped, 78, 1)) {
			Entity handle = GetNearestLocalPlayerPed();
			if (handle && ENTITY::DoesEntityExist(handle) && handle != GetLocalPlayer().m_ped) {
				Vector3 targetPos = ENTITY::GetEntityCoords(handle, 1);
				BOOL exists = ENTITY::DoesEntityExist(handle);
				BOOL dead = PED::IsPedDeadOrDying(handle, 1);
				if (exists && !dead) {
					float screenX, screenY;
					BOOL onScreen = GRAPHICS::GetScreenCoordFromWorldCoord(targetPos.x, targetPos.y, targetPos.z, &screenX, &screenY);
					if (ENTITY::IsEntityVisible(handle) && onScreen) {
						if (ENTITY::HasEntityClearLosToEntity(GetLocalPlayer().m_ped, handle, 1)) {
							GRAPHICS::DrawMarker(2, targetPos.x, targetPos.y, targetPos.z + 1.5f, 0, 0, 0, 0, 180, 0, 0.7f, 0.7f, 0.7f, 255, 0, 0, 120, 1, 0, 1, 1, 0, 0, 0);
							Vector3 targetCoords = PED::GetPedBoneCoords(handle, 31086, 0, 0, 0);
							PLAYER::DisablePlayerFiring(GetLocalPlayer().m_ped, 1);
							if (PAD::IsControlPressed(2, 208) || (GetKeyState(VK_LBUTTON) & 0x8000))
								PED::SetPedShootsAtCoord(GetLocalPlayer().m_ped, targetCoords.x, targetCoords.y, targetCoords.z, 1);
						}
					}
				}
			}
		}
	}

	void Aimbot() {
		Entity nearestPed = GetNearestLocalPed();
		Entity nearestPlayerPed = GetNearestLocalPlayerPed();
		Entity handle = 0;

		switch (vars.entityFilter) {
		case 0:
			handle = nearestPed;
			break;
		case 1:
			handle = nearestPlayerPed;
			break;
		case 2:
			if (vars.prioritize == 0) {
				if (nearestPed != 0)
					handle = nearestPed;
				else if (nearestPlayerPed != 0)
					handle = nearestPlayerPed;
				else handle = 0;
			}
			else if (vars.prioritize == 1) {
				if (nearestPlayerPed != 0)
					handle = nearestPlayerPed;
				else if (nearestPed != 0)
					handle = nearestPed;
				else handle = 0;
			}
			break;
		}

		if (handle) {
			Vector3 targetPos = ENTITY::GetEntityCoords(handle, 1);
			float screenX, screenY;

			if (ENTITY::IsEntityVisible(handle) && GRAPHICS::GetScreenCoordFromWorldCoord(targetPos.x, targetPos.y, targetPos.z, &screenX, &screenY)) {
				if (ENTITY::HasEntityClearLosToEntity(GetLocalPlayer().m_ped, handle, 1)) {
					Vector3 targetCoords = PED::GetPedBoneCoords(handle, vars.bone, 0, 0, 0);

					if (PAD::IsDisabledControlPressed(2, 208) || (GetKeyState(VK_LBUTTON) & 0x8000) || vars.autoShoot) {
						PED::SetPedShootsAtCoord(GetLocalPlayer().m_ped, targetCoords.x, targetCoords.y, targetCoords.z, 1);
					}
				}
			}
		}
	}

	void BasicTriggerBot() {
		Entity AimedAtEntity;
		if (PLAYER::GetEntityPlayerIsFreeAimingAt(GetLocalPlayer().m_id, &AimedAtEntity)) {
			if (ENTITY::IsEntityAPed(AimedAtEntity) && PED::IsPedAPlayer(AimedAtEntity) && ENTITY::GetEntityAlpha(AimedAtEntity) == 255) {
				if (!PED::IsPedDeadOrDying(AimedAtEntity, true)) {
					Vector3 Mouth = PED::GetPedBoneCoords(AimedAtEntity, 31086, 0.1f, 0.0f, 0.0f);
					PED::SetPedShootsAtCoord(GetLocalPlayer().m_ped, Mouth.x, Mouth.y, Mouth.z, true);
				}
			}
		}
	}
}

void WeaponAimbotMenu::Init() {
	setParentSubmenu<WeaponMenu>();
	setName("Aimbot", true, true);

	addOption(ToggleOption("Basic ped aimbot")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.basicaimbot)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Automatically aim at ped entities").addTranslation());

	addOption(ToggleOption("Basic player aimbot")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.basicplayeraimbot)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Automatically aim at player entities").addTranslation());

	addOption(ToggleOption("Basic player triggerbot")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.basictriggerbot)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Automatically shoot the entity").addTranslation());

	addOption(BreakOption("Custom Aimbot").addTranslation());

	addOption(ScrollOption<int>(SCROLL, "Entity filter")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addScroll(vars.entityFilter, 0, NUMOF(entityFilterScrollStruct) - 1, entityFilterScrollStruct).addHotkey().canBeSaved()
		.addTooltip("Select the entity filter for the aimbot").addTranslation());

	addOption(ScrollOption<int>(SCROLL, "Prioritize")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addScroll(vars.prioritize, 0, NUMOF(entityFilterScrollStruct) - 1, entityFilterScrollStruct).addHotkey().canBeSaved()
		.addTooltip("Select the entity group to prioritize for the aimbot").addTranslation());

	addOption(ScrollOption<int>(SCROLL, "Bone")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addScroll(vars.bone, 0, NUMOF(entityBoneScrollStruct) - 1, entityBoneScrollStruct).addHotkey().canBeSaved()
		.addTooltip("Select the bone to shoot").addTranslation());

	addOption(ToggleOption("Aimbot required")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.required).addHotkey().canBeSaved()
		.addTooltip("Enable this to enable the aimbot").addTranslation());

	addOption(ToggleOption("Auto shoot")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.autoShoot).addHotkey().canBeSaved()
		.addTooltip("Automatically shoot the entity").addTranslation());
}

/*Update once when submenu is opened*/
void WeaponAimbotMenu::UpdateOnce() {}

/*Update while submenu is active*/
void WeaponAimbotMenu::Update() {}

/*Background update*/
void WeaponAimbotMenu::FeatureUpdate() {
	if (vars.required) Aimbot();
	if (vars.basicaimbot) BasicAimbot();
	if (vars.basicplayeraimbot) BasicPlayerAimbot();
	if (vars.basictriggerbot) BasicTriggerBot();
}

/*Singleton*/
WeaponAimbotMenu* _instance;
WeaponAimbotMenu* WeaponAimbotMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new WeaponAimbotMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
WeaponAimbotMenu::~WeaponAimbotMenu() { delete _instance; }