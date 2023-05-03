#include "stdafx.h"
#include "weaponVisuals.h"
#include "../weaponMenu.h"
#include "backend/backendExplosions.h"

using namespace WeaponVisualsMenuVars;

namespace WeaponVisualsMenuVars {
	Vars vars;

	ScrollStruct<int> crosshairs[] = {
		TranslationString("Cross", true), 0,
		TranslationString("Target", true), 1,
		TranslationString("Arrow", true), 2,
		TranslationString("Holy Cross", true), 3,
		TranslationString("Reticle", true), 4,
		TranslationString("Reticle Zoomed", true), 5,
		TranslationString("Dot", true), 6,
		TranslationString("Plus", true), 7,
		TranslationString("Middle Finger", true), 8,
		TranslationString("Box", true), 9,
		TranslationString("Star", true), 10
	};

	void AimedInformation() {
		Entity Target = 0;
		if (PLAYER::GetEntityPlayerIsFreeAimingAt(GetLocalPlayer().m_id, &Target)) {
			float x, y;
			Vector3 position = ENTITY::GetEntityCoords(Target, 1);
			if (GRAPHICS::GetScreenCoordFromWorldCoord(position.x, position.y, position.z, &x, &y)) {
				char* vaRes = va("Entity Address: 0x%llx\nEntity Handle: 0x%X\nEntity Model: 0x%X", PoolManager::GetEntityAddress(Target), PoolManager::AddEntityToPool(PoolManager::GetEntityAddress(Target)), ENTITY::GetEntityModel(Target));
				GetRenderer()->DrawString(vaRes, x, y, 4, 0.40f, GetRenderer()->m_cOption);
			}
		}
	}

	void AimingLaser() {
		int rnd = 0;
		if (PAD::IsDisabledControlPressed(0, 25) || PLAYER::GetEntityPlayerIsFreeAimingAt(GetLocalPlayer().m_ped, &rnd)) {
			float Distance = 200;
			float Pitch = CAM::GetGameplayCamRelativePitch();
			Vector3 Start = ENTITY::GetWorldPositionOfEntityBone(GetLocalPlayer().m_ped, PED::GetPedBoneIndex(GetLocalPlayer().m_ped, 28422));
			Vector3 RelativePos;
			RelativePos.x = 0.0f;
			RelativePos.y = Distance;
			RelativePos.z = MISC::Tan(Pitch) * RelativePos.y;
			Vector3 End = ENTITY::GetOffsetFromEntityInWorldCoords(GetLocalPlayer().m_ped, RelativePos.x, RelativePos.y, RelativePos.z);
			GRAPHICS::DrawLine(Start.x, Start.y, Start.z, End.x, End.y, End.z, 255, 0, 0, 150);
		}
	}

	void CartoonEffects() {
		GRAPHICS::EnableClownBloodVfx(true);
	}
}

void WeaponVisualsMenu::Init() {
	setParentSubmenu<WeaponMenu>();
	setName("Visuals", true, true);

	addOption(ButtonOption("~c~You don't have a weapon in hand")
		.addRequirement([] { return !GetLocalPlayer().m_hasWeaponInHand; }).addTranslation()
	.addTooltip("You don't have a weapon in hand"));

	addOption(NumberOption<float>(SCROLL, "Weapon width")
		.addRequirement([] { return GetLocalPlayer().m_hasWeaponInHand && PoolManager::GetEntityAddress(GetLocalPlayer().m_weaponEntity); })
		.addNumber(vars.width, "%.1f", 0.5f).addMin(0.0f).addMax(10.0f)
		.addFunction([] { 
			*(float*)(PoolManager::GetEntityAddress(GetLocalPlayer().m_weaponEntity) + 0x7C) = vars.width;
		})
		.addTooltip("Edit the width of the weapon in hand")
		.addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Weapon height")
		.addRequirement([] { return GetLocalPlayer().m_hasWeaponInHand && PoolManager::GetEntityAddress(GetLocalPlayer().m_weaponEntity); })
		.addNumber(vars.height, "%.1f", 0.5f).addMin(0.0f).addMax(10.0f)
		.addFunction([] {
			*(float*)(PoolManager::GetEntityAddress(GetLocalPlayer().m_weaponEntity) + 0x8C) = vars.height;
		})
		.addTooltip("Edit the height of the weapon in hand")
		.addTranslation().addHotkey());

	addOption(NumberOption<float>(SCROLL, "Overall weapon scale")
		.addRequirement([] { return GetLocalPlayer().m_hasWeaponInHand && PoolManager::GetEntityAddress(GetLocalPlayer().m_weaponEntity); })
		.addNumber(vars.overall, "%.1f", 0.5f).addMin(0.0f).addMax(10.0f)
		.addFunction([] {
			*(float*)(PoolManager::GetEntityAddress(GetLocalPlayer().m_weaponEntity) + 0x8C) = vars.overall;
			*(float*)(PoolManager::GetEntityAddress(GetLocalPlayer().m_weaponEntity) + 0x7C) = vars.overall;
		})
		.addTooltip("Edit the overall scale of the weapon in hand")
		.addTranslation().addHotkey());

	addOption(ToggleOption("Weapon invisibility")
		.addToggle(vars.invisibility)
		.addFunction([] { 
			if (!vars.invisibility) {
				ENTITY::SetEntityVisible(GetLocalPlayer().m_weaponEntity, true, false);
			} 
		}).addTranslation().addHotkey()
		.addTooltip("Change the visibility of the weapon in hand"));

	addOption(ScrollOption<int>(TOGGLE, "Cross hair")
		.addToggle(vars.crosshair)
		.addScroll(vars.selectedCrosshair, 0, NUMOF(crosshairs) - 1, crosshairs)
		.addTooltip("Draw a cross hair").addTranslation().addHotkey());

	addOption(ToggleOption("Aiming laser")
		.addToggle(vars.aimingLaser)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Attach a laser onto your weapon when aiming"));

	addOption(ToggleOption("Cartoon effects")
		.addToggle(vars.cartoonEffects)
		.addTranslation().addHotkey().canBeSaved()
		.addFunction([] {
		if (!vars.cartoonEffects) {
			GRAPHICS::EnableClownBloodVfx(false);
		}
		else {
			STREAMING::RequestNamedPtfxAsset("scr_rcbarry2");
			GRAPHICS::_UseParticleFxAssetNextCall("scr_rcbarry2");
			GRAPHICS::_StartParticleFxNonLoopedOnPedBone2("scr_clown_death", GetLocalPlayer().m_ped, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		}
	})
		.addTooltip("Shoot cool cartoon effects"));



	addOption(ToggleOption("Aimed information")
		.addToggle(vars.aimedInformation)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Show information on the aimed entity"));
}

/*Update once when submenu is opened*/
void WeaponVisualsMenu::UpdateOnce() {// YEEEEEEEEEEEEEEEEEEET
	if (GetLocalPlayer().m_hasWeaponInHand && PoolManager::GetEntityAddress(GetLocalPlayer().m_weaponEntity)) {
		vars.width = *(float*)(PoolManager::GetEntityAddress(GetLocalPlayer().m_weaponEntity) + 0x7C);
		vars.height = *(float*)(PoolManager::GetEntityAddress(GetLocalPlayer().m_weaponEntity) + 0x8C);
	}
}

/*Update while submenu is active*/
void WeaponVisualsMenu::Update() {}

/*Background update*/
void WeaponVisualsMenu::FeatureUpdate() {
	if (vars.invisibility) {
		ENTITY::SetEntityVisible(GetLocalPlayer().m_weaponEntity, false, false);
	}

	if (vars.crosshair) {
		switch (vars.selectedCrosshair) {
		case 0:
			GetRenderer()->DrawSprite({ "srange_gen", "hit_cross" }, 0.5f, 0.5f, 0.02f, 0.03f, 0, Color(0, 255, 0, 180));
			break;
		case 1:
			GetRenderer()->DrawSprite({ "helicopterhud", "hud_target" }, 0.5f, 0.5f, 0.02f, 0.03f, 0, Color(0, 255, 0, 180));
			break;
		case 2:
			GetRenderer()->DrawSprite({ "helicopterhud", "hudarrow" }, 0.5f, 0.5f, 0.02f, 0.03f, 0, Color(0, 255, 0, 180));
			break;
		case 3:
			GetRenderer()->DrawSprite({ "mptattoos3", "tattoo_reach_rank_r_10" }, 0.5f, 0.5f, 0.02f, 0.03f, 0, Color(0, 255, 0, 180));
			break;
		case 4:
			GetRenderer()->DrawSprite({ "darts", "dart_reticules" }, 0.5f, 0.5f, 0.02f, 0.03f, 0, Color(0, 255, 0, 180));
			break;
		case 5:
			GetRenderer()->DrawSprite({ "darts", "dart_reticules_zoomed" }, 0.5f, 0.5f, 0.02f, 0.03f, 0, Color(0, 255, 0, 180));
			break;
		case 6:
			GetRenderer()->DrawSprite({ "shared", "emptydot_32" }, 0.5f, 0.5f, 0.02f, 0.03f, 0, Color(0, 255, 0, 180));
			break;
		case 7:
			GetRenderer()->DrawSprite({ "shared", "menuplus_32" }, 0.5f, 0.5f, 0.02f, 0.03f, 0, Color(0, 255, 0, 180));
			break;
		case 8:
			GetRenderer()->DrawSprite({ "mp_freemode_mc", "mouse" }, 0.5f, 0.5f, 0.02f, 0.03f, 0, Color(0, 255, 0, 180));
			break;
		case 9:
			GetRenderer()->DrawSprite({ "visualflow", "crosshair" }, 0.5f, 0.5f, 0.02f, 0.03f, 0, Color(0, 255, 0, 180));
			break;
		case 10:
			GetRenderer()->DrawSprite({ "shared", "newstar_32" }, 0.5f, 0.5f, 0.02f, 0.03f, 0, Color(0, 255, 0, 180));
			break;
		}
	}
	if (vars.aimingLaser) AimingLaser();
	if (vars.cartoonEffects) CartoonEffects();
	if (vars.aimedInformation) AimedInformation();

}

/*Singleton*/
WeaponVisualsMenu* _instance;
WeaponVisualsMenu* WeaponVisualsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new WeaponVisualsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
WeaponVisualsMenu::~WeaponVisualsMenu() { delete _instance; }


/*addOption(ToggleOption("Weapon invisibility")
		.addToggle(vars.infernoFlare)
		.addFunction([] {
			Explosions::sExplosion* Explosion = Explosions::GetExplosion(EXP_TAG_FLARE);
			Explosions::sExplosionFX* ExplosionFX = Explosions::GetExplosionFX(EXP_VFXTAG_DIR_FLAME);

			if (vars.infernoFlare) {
				WEAPON::GiveDelayedWeaponToPed(GetLocalPlayer().m_ped, 0x497FACC3, -1, true);
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
		}).addTranslation().addHotkey()
		.addTooltip("Inferno flare"));*/