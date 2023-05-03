#include "stdafx.h"
#include "playerMovementMenu.h"
#include "../localMenu.h"
#include "menu\submenus\main/worldMenu.h"

using namespace PlayerMovementMenuVars;

namespace PlayerMovementMenuVars {
	struct Vars vars;

	void KeyBoost(float speed) {
		if ((vars.boostKeyController && PAD::IsDisabledControlPressed(0, vars.boostKey)) || KeyDown(vars.boostKey))
			Utils::ApplyForceToEntity(GetLocalPlayer().m_ped, 0, speed, 0);
	}

	void FlyMode() {
		WEAPON::GiveDelayedWeaponToPed(PLAYER::PlayerPedId(), Utils::GetHashKey("GADGET_PARACHUTE"), 1, 1);
		PAD::SetInputExclusive(2, INPUT_FRONTEND_ACCEPT);
		PAD::SetInputExclusive(2, INPUT_FRONTEND_CANCEL);
		PAD::SetInputExclusive(2, INPUT_FRONTEND_DOWN);
		PAD::SetInputExclusive(2, INPUT_FRONTEND_UP);
		PAD::SetInputExclusive(2, INPUT_FRONTEND_LEFT);
		PAD::SetInputExclusive(2, INPUT_FRONTEND_RIGHT);
		if (KeyDown(VK_UP) || PAD::IsControlPressed(0, INPUT_FRONTEND_RT)) { // && !HUD::_IsTextChatActive()
			Utils::ApplyForceToEntity(GetLocalPlayer().m_ped, 0, 6, 0);
		}
		if (KeyDown(VK_DOWN) || PAD::IsControlPressed(0, INPUT_FRONTEND_LT)) {
			Utils::ApplyForceToEntity(GetLocalPlayer().m_ped, 0, -6, 0);
		}
		if (KeyDown(VK_SHIFT) || PAD::IsControlPressed(0, INPUT_FRONTEND_ACCEPT)) {
			Utils::ApplyForceToEntity(GetLocalPlayer().m_ped, 0, 0, 6);
		}
		if (KeyDown(VK_CONTROL) || PAD::IsControlPressed(0, INPUT_FRONTEND_X)) {
			Utils::ApplyForceToEntity(GetLocalPlayer().m_ped, 0, 0, -6);
		}
	}

	void Noclip() {
		GetEntityControl()->SimpleRequestControl(GetLocalPlayer().m_entity);
		if (NETWORK::NetworkHasControlOfEntity(GetLocalPlayer().m_entity)) {
			Vector3 camCoords;

			Utils::GetCameraDirection(&camCoords.x, &camCoords.y, &camCoords.z);

			if (KeyDown(0x57) || PAD::IsDisabledControlPressed(0, 208)) {
				vars.noclipCoords = vars.noclipCoords + (camCoords * vars.noclipspeed);
			}

			if (KeyDown('S') || PAD::IsControlPressed(0, INPUT_FRONTEND_LT)) {
				vars.noclipCoords = vars.noclipCoords - (camCoords * vars.noclipspeed);
			}

			ENTITY::SetEntityCoords(GetLocalPlayer().m_entity, vars.noclipCoords.x, vars.noclipCoords.y, vars.noclipCoords.z, 0, 0, 0, 0);
			ENTITY::SetEntityCollision(GetLocalPlayer().m_entity, 1, 1);
		}
	}

	void FastRun() {
		PLAYER::SetRunSprintMultiplierForPlayer(GetLocalPlayer().m_ped, 1.49f);
		/*WEAPON::RemoveWeaponFromPed(GetLocalPlayer().m_ped, Utils::GetHashKey("GADGET_PARACHUTE"));
		if (PED::IsPedJumping(GetLocalPlayer().m_ped)) {
			Utils::ApplyForceToEntity(GetLocalPlayer().m_ped, 0, 0, 2);
		}*/
	}

	void SuperJump() {

		/*if (vars.classjumpselect == 1) {
			WEAPON::RemoveWeaponFromPed(GetLocalPlayer().m_ped, Utils::GetHashKey("GADGET_PARACHUTE"));
			MISC::SetSuperJumpThisFrame(GetLocalPlayer().m_id);
		} else {*/

			static bool wasJumping;
			static int isJumpingTimer;

			bool isJumping = PED::IsPedJumping(GetLocalPlayer().m_ped);
			if (isJumping && wasJumping) {
				wasJumping = true;
				if (isJumpingTimer > 0) {
					isJumpingTimer--;
					PED::SetPedCanRagdoll(GetLocalPlayer().m_ped, false);
					WEAPON::RemoveWeaponFromPed(GetLocalPlayer().m_ped, Utils::GetHashKey("GADGET_PARACHUTE"));
					Utils::ApplyForceToEntity(GetLocalPlayer().m_ped, 0, 2, 4);
				}
			} else if (isJumping && !wasJumping) {
				wasJumping = true;
				isJumpingTimer = 10;
			} else if (!isJumping) {
				wasJumping = false;
			}
		//}
	}

	void UltraJump() {

		/*if (vars.classjumpselect == 1) {
			MISC::SetSuperJumpThisFrame(GetLocalPlayer().m_id);
			WEAPON::RemoveWeaponFromPed(GetLocalPlayer().m_ped, Utils::GetHashKey("GADGET_PARACHUTE"));
			if (PED::IsPedJumping(GetLocalPlayer().m_ped)) {
				ENTITY::ApplyForceToEntity(GetLocalPlayer().m_ped, true, 0, 0, 5, 0, 0, 0, true, true, true, true, false, true);
			}
		} else {*/

			static bool wasJumping;
			static int isJumpingTimer;

			bool isJumping = PED::IsPedJumping(GetLocalPlayer().m_ped);
			if (isJumping && wasJumping) {
				wasJumping = true;
				if (isJumpingTimer > 0) {
					isJumpingTimer--;
					PED::SetPedCanRagdoll(GetLocalPlayer().m_ped, false);
					WEAPON::RemoveWeaponFromPed(GetLocalPlayer().m_ped, Utils::GetHashKey("GADGET_PARACHUTE"));
					Utils::ApplyForceToEntity(GetLocalPlayer().m_ped, 0, 2.5, 20);
				}
			} else if (isJumping && !wasJumping) {
				wasJumping = true;
				isJumpingTimer = 10;
			} else if (!isJumping) {
				wasJumping = false;
			}
		//}
	}

	void WalkOnWater() {
		static float z;
		static Object waterObject;
		if (ENTITY::DoesEntityExist(waterObject)) {
			WATER::GetWaterHeight(GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, GetLocalPlayer().m_coordinates.z, &z);
			ENTITY::SetEntityVisible(waterObject, false, true);
			ENTITY::SetEntityCoords(waterObject, GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, z - 1.9f, true, false, false, true);
			ENTITY::SetEntityRotation(waterObject, 180, 90, 180, 2, false);
			ENTITY::FreezeEntityPosition(waterObject, true);
		} else {
			GetEntityControl()->SimpleRequestModel(-1003748966);
			waterObject = OBJECT::CreateObject(-1003748966, GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, GetLocalPlayer().m_coordinates.z, 1, 1, 0);
			ENTITY::FreezeEntityPosition(waterObject, true);
			ENTITY::SetEntityCollision(waterObject, true, false);
		}
	}

	void WalkThroughWater() {
		float offset[] = { -4, 4 };
		for (int i = 0; i < 5; i++) {
			Vector3 coords = GetLocalPlayer().m_coordinates;
			if (i < 2)  coords.x += offset[(i % 2 == 0)];
			else if (i < 4) coords.y += offset[(i % 2 == 0)];
			WATER::ModifyWater(coords.x, coords.y, -500000.0f, 0.2f);
		}
	}

	void SlowMotion(bool toggle) {
		MISC::SetTimeScale(toggle ? 0.5f : 1);
	}

	void VegetableMode() {
		PED::SetPedToRagdoll(GetLocalPlayer().m_ped, 10, 10, 0, true, true, true);
		if (KeyDown('W')) Utils::ApplyForceToEntity(GetLocalPlayer().m_ped, 0, 2, 0);
		if (KeyDown('S')) Utils::ApplyForceToEntity(GetLocalPlayer().m_ped, 0, -2, 0);
		if (KeyDown('A')) Utils::ApplyForceToEntity(GetLocalPlayer().m_ped, 2, 0, 0);
		if (KeyDown('D')) Utils::ApplyForceToEntity(GetLocalPlayer().m_ped, -2, 0, 0);
	}

	void WalkOnAir() {
		float zPlane;
		Hash objectHash = Utils::GetHashKey("p_oil_slick_01");
		static Object WalkOnAirHandle;

		if (!ENTITY::DoesEntityExist(WalkOnAirHandle)) {
			if (!STREAMING::HasModelLoaded(objectHash)) {
				STREAMING::RequestModel(objectHash);
			} else {
				WalkOnAirHandle = OBJECT::CreateObject(objectHash, GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, GetLocalPlayer().m_coordinates.z, 1, 1, 0);
				ENTITY::FreezeEntityPosition(WalkOnAirHandle, 1);
				ENTITY::SetEntityVisible(WalkOnAirHandle, 0, 0);
			}
		} else {
			if (KeyDown(VK_SHIFT)) {
				zPlane = GetLocalPlayer().m_coordinates.z - 1.60;
			} else if (KeyDown(VK_SPACE)) {
				zPlane = GetLocalPlayer().m_coordinates.z - 0.40;
			} else {
				zPlane = GetLocalPlayer().m_coordinates.z - 1.0225;
			}
			GetScaleform()->DrawInstructional("Up", g_keyNamesInstructional[VK_SPACE]);
			GetScaleform()->DrawInstructional("Down", g_keyNamesInstructional[VK_SHIFT]);

			ENTITY::SetEntityCoords(WalkOnAirHandle, GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, zPlane, 1, 0, 0, 0);

		}
	}

	const int KEYS_SIZE = 255;
	const int NOW_PERIOD = 100, MAX_DOWN = 5000; // ms

	struct {
		DWORD time;
		BOOL isWithAlt;
		BOOL wasDownBefore;
		BOOL isUpNow;
	} keyStates[KEYS_SIZE];

	bool get_key_pressed(int nVirtKey)
	{
		return (GetAsyncKeyState(nVirtKey) & 0x8000) != 0;
	}

	bool IsKeyDown(DWORD key)
	{
		return (key < KEYS_SIZE) ? ((GetTickCount() < keyStates[key].time + MAX_DOWN) && !keyStates[key].isUpNow) : false;
	}

	float speedmult2 = 0.5f;
	void WalkingNoclip() {
		bool jumping = PED::IsPedJumping(GetLocalPlayer().m_ped);
		bool falling = PED::IsPedFalling(GetLocalPlayer().m_ped);
		bool paraState = PED::GetPedParachuteState(GetLocalPlayer().m_ped);
		float speed = ENTITY::GetEntitySpeed(GetLocalPlayer().m_ped);
		Vector3 velocity = ENTITY::GetEntityVelocity(GetLocalPlayer().m_ped);
		Vector3 rotation = ENTITY::GetEntityRotation(GetLocalPlayer().m_ped, false);
		Vector3 position = ENTITY::GetEntityCoords(GetLocalPlayer().m_ped, true);
		Vector3 direction = ENTITY::GetEntityForwardVector(GetLocalPlayer().m_ped);
		int vehiclerotation = 0;


		{
			ENTITY::SetEntityMaxSpeed(GetLocalPlayer().m_entity, 0);
			if (get_key_pressed(VK_NUMPAD7)) {
				vars.speedmult += 0.5f;
			}
			else if (get_key_pressed(VK_NUMPAD1)) {
				if (!vars.speedmult < 0.01f)
					vars.speedmult -= 0.5f;
			}
			if (!GetLocalPlayer().m_isInVehicle) {
				ENTITY::SetEntityCollision(GetLocalPlayer().m_ped, 0, 0);
				vehiclerotation = 0;
				ENTITY::SetEntityCollision(GetLocalPlayer().m_vehicle, true, true);
				Vector3 weirdRotation = ENTITY::GetEntityRotation(GetLocalPlayer().m_ped, 2);
				float yaw = weirdRotation.z;
				if (get_key_pressed('W') || get_key_pressed('A') || get_key_pressed('D') || get_key_pressed('S') || PAD::IsControlPressed(0, INPUT_FRONTEND_ACCEPT)) {
					if (PAD::IsDisabledControlPressed(0, 25)) {//d=-a=+
						if (get_key_pressed('S')) {
							ENTITY::SetEntityCoords(GetLocalPlayer().m_ped, position.x - ENTITY::GetEntityForwardX(GetLocalPlayer().m_ped)*vars.speedmult, position.y - ENTITY::GetEntityForwardY(GetLocalPlayer().m_ped)*vars.speedmult, (position.z - 1), true, true, true, true);
						}
						else {
							ENTITY::SetEntityCoords(GetLocalPlayer().m_ped, position.x + ENTITY::GetEntityForwardX(GetLocalPlayer().m_ped)*vars.speedmult, position.y + ENTITY::GetEntityForwardY(GetLocalPlayer().m_ped)*vars.speedmult, (position.z - 1), true, true, true, true);
						}
					}
					else {
						if (get_key_pressed('A')) {
							yaw += 2;
							ENTITY::SetEntityRotation(GetLocalPlayer().m_ped, 0, 0, yaw, 0, 0);
						}
						else if (get_key_pressed('D')) {
							yaw -= 2;
							ENTITY::SetEntityRotation(GetLocalPlayer().m_ped, 0, 0, yaw, 0, 0);
						}
						if (IsKeyDown('S')) {
							ENTITY::SetEntityRotation(GetLocalPlayer().m_ped, 0, 0, yaw, 0, 0);
							ENTITY::SetEntityCoords(GetLocalPlayer().m_ped, position.x - ENTITY::GetEntityForwardX(GetLocalPlayer().m_ped)*vars.speedmult, position.y - ENTITY::GetEntityForwardY(GetLocalPlayer().m_ped)*vars.speedmult, (position.z - 1), true, true, true, true);
						}
						else {
							ENTITY::SetEntityCoords(GetLocalPlayer().m_ped, position.x + ENTITY::GetEntityForwardX(GetLocalPlayer().m_ped)*vars.speedmult, position.y + ENTITY::GetEntityForwardY(GetLocalPlayer().m_ped)*vars.speedmult, (position.z - 1), true, true, true, true);
						}
					}
				}
				position = ENTITY::GetEntityCoords(GetLocalPlayer().m_ped, true);
				direction = ENTITY::GetEntityForwardVector(GetLocalPlayer().m_ped);
				if (get_key_pressed(VK_SPACE) || PAD::IsControlPressed(0, INPUT_FRONTEND_RB)) {
					ENTITY::SetEntityCoords(GetLocalPlayer().m_ped, position.x, position.y, ((position.z - 1) + 0.5*speedmult2), true, true, true, true);
				}
				position = ENTITY::GetEntityCoords(GetLocalPlayer().m_ped, true);
				direction = ENTITY::GetEntityForwardVector(GetLocalPlayer().m_ped);
				if (get_key_pressed(VK_LCONTROL) || PAD::IsControlPressed(0, INPUT_FRONTEND_LT)) {
					ENTITY::SetEntityCoords(GetLocalPlayer().m_ped, position.x, position.y, ((position.z - 1) - 0.5*speedmult2), true, true, true, true);
				}
			}
			else {
				WorldMenuVars::vars.RequestControlOfEnt(GetLocalPlayer().m_vehicle);
				Vector3 position = ENTITY::GetEntityCoords(GetLocalPlayer().m_vehicle, true);
				ENTITY::SetEntityCollision(GetLocalPlayer().m_ped, 0, 0);
				ENTITY::SetEntityCollision(GetLocalPlayer().m_vehicle, 0, 0);
				vehiclerotation = 0;
				Vector3 weirdRotation = ENTITY::GetEntityRotation(GetLocalPlayer().m_vehicle, 2);
				float roll = ENTITY::GetEntityRoll(GetLocalPlayer().m_vehicle);
				float yaw/*A CHANGE*/ = weirdRotation.z;
				float pitch = ENTITY::GetEntityPitch(GetLocalPlayer().m_vehicle);
				vehiclerotation = yaw;
				if (get_key_pressed('W') || get_key_pressed('A') || get_key_pressed('D') || get_key_pressed('S')) {
					if (get_key_pressed('S')) {
						ENTITY::SetEntityCoordsNoOffset(GetLocalPlayer().m_vehicle, position.x - ENTITY::GetEntityForwardX(GetLocalPlayer().m_ped)*vars.speedmult, position.y - ENTITY::GetEntityForwardY(GetLocalPlayer().m_ped)*vars.speedmult, position.z, 0, 0, 0);

					}
					else {
						ENTITY::SetEntityCoordsNoOffset(GetLocalPlayer().m_vehicle, position.x + ENTITY::GetEntityForwardX(GetLocalPlayer().m_ped)*vars.speedmult, position.y + ENTITY::GetEntityForwardY(GetLocalPlayer().m_ped)*vars.speedmult, position.z, 0, 0, 0);
					}
					if (get_key_pressed('A'))
						yaw += 4;
					if (get_key_pressed('D'))
						yaw -= 4;
					ENTITY::SetEntityRotation(GetLocalPlayer().m_vehicle, 0, 0, yaw, 0, 0);
				}

				position = ENTITY::GetEntityCoords(GetLocalPlayer().m_ped, true);
				if (get_key_pressed(VK_SPACE)) {
					ENTITY::SetEntityCoordsNoOffset(GetLocalPlayer().m_vehicle, position.x, position.y, ((position.z + 1) + 0.5*speedmult2), 0, 0, 0);
				}
				if (get_key_pressed(VK_LCONTROL)) {
					ENTITY::SetEntityCoordsNoOffset(GetLocalPlayer().m_vehicle, position.x, position.y, ((position.z - 1) - 0.5*speedmult2), 0, 0, 0);
				}
			}

			if (!GetLocalPlayer().m_isInVehicle) {
				if (jumping || falling || paraState == 0) {
					ENTITY::SetEntityCoords(GetLocalPlayer().m_ped, position.x, position.y, (position.z - 1), 0, 0, 0, 0);
				}

				ENTITY::SetEntityVelocity(GetLocalPlayer().m_ped, 0, 0, 0);
			}
			else {
				ENTITY::SetEntityMaxSpeed(GetLocalPlayer().m_vehicle, 500);
				ENTITY::SetEntityCollision(GetLocalPlayer().m_vehicle, 1, 0);

				vehiclerotation = 0;
				WorldMenuVars::vars.RequestControlOfEnt(GetLocalPlayer().m_vehicle);
				ENTITY::SetEntityCollision(GetLocalPlayer().m_vehicle, true, true);
				ENTITY::SetEntityMaxSpeed(GetLocalPlayer().m_vehicle, 500);
			}
		}
	}

	ScrollStruct<int> jumpmode[] = {
		TranslationString("Modified", true), 0,
		TranslationString("Classic", true), 1
	};

}

void PlayerMovementMenu::Init() {
	setParentSubmenu<LocalMenu>();
	setName("Movement", true, true);

	//addOption(ToggleOption("Fast run")
	//	.addToggle(vars.fastrun)
	//	.addHotkey().canBeSaved()
	//	.addTooltip("Fly using shift, ctrl, up and down"));

	/*addOption(ScrollOption<int>(TOGGLE, "Super jump")
		.addToggle(vars.superjump)
		.addScroll(vars.classjumpselect, 0, NUMOF(jumpmode) - 1, jumpmode)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Super jump"));*/

	addOption(ToggleOption("Super jump")
		.addToggle(vars.superjump)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Super jump"));

	addOption(ToggleOption("Ultra jump")
		.addToggle(vars.ultrajump)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Ultra jump"));

	addOption(NumberOption<float>(TOGGLE, "Movement speed multiplier")
		.addToggle(vars.enableMovementSpeed)
		.addNumber(vars.movementSpeed, "%.2f", 0.2f)
		.addHotkey().addTranslation()
		.addFunction([] {ReClass::GetWorld()->LocalPed->PlayerInfo->RunSpeed = vars.enableMovementSpeed ? vars.movementSpeed : 1.0f; })
		.addTooltip("Movement speed multiplier"));

	addOption(NumberOption<float>(TOGGLE, "Swim speed multiplier")
		.addToggle(vars.enableSwimSpeed)
		.addNumber(vars.swimSpeed, "%.2f", 0.2f)
		.addHotkey().addTranslation()
		.addFunction([] {ReClass::GetWorld()->LocalPed->PlayerInfo->SwimSpeed = vars.enableSwimSpeed ? vars.movementSpeed : 1.0f; })
		.addTooltip("Swim speed multiplier"));

	addOption(ToggleOption("Flymode")
		.addToggle(vars.flymode)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Fly using shift, ctrl, up and down || RT / LT - A / X"));

	addOption(ToggleOption("Walk on air")
		.addToggle(vars.walkonair)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Shift to go down, Space to go up"));

	addOption(ToggleOption("Vegetable mode")
		.addToggle(vars.vegetablemode).addTranslation()
		.addHotkey().canBeSaved()
		.addTooltip("Ragdoll! make sure to turn off no ragdoll!"));

	addOption(ToggleOption("Slow motion")
		.addToggle(vars.slowmotion).addTranslation()
		.addFunction([] {SlowMotion(vars.slowmotion); })
		.addHotkey().canBeSaved()
		.addTooltip("Slow time"));

	addOption(BreakOption("Noclip").addTranslation());

	addOption(ToggleOption("Noclip")
		.addToggle(vars.noclip)
		.addFunction([] { vars.noclipCoords = GetLocalPlayer().m_coordinates; })
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Aim with mouse/controller then use W or right trigger"));

	addOption(NumberOption<float>(SCROLL, "Noclip speed")
		.addNumber(vars.noclipspeed, "%.1f", 1.0f).addMin(1.0f).addMax(50.0f)
		.addHotkey()
		.addTooltip("Control the speed of your noclip"));

	addOption(ToggleOption("Walking noclip")
		.addToggle(vars.walkingnoclip)
		.addFunction([] {
		ENTITY::SetEntityMaxSpeed(GetLocalPlayer().m_ped, 1000);
		ENTITY::SetEntityCollision(GetLocalPlayer().m_ped, 1, 0);
		if (PED::IsPedInAnyVehicle(GetLocalPlayer().m_ped, 1)) {
			WorldMenuVars::vars.RequestControlOfEnt(GetLocalPlayer().m_vehicle);
			ENTITY::SetEntityCollision(GetLocalPlayer().m_vehicle, 1, 0);
		}
	})
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("This will allow you to walk and shoot while noclipping (CTRL to go down - Space to go up) || A / RB / LT"));

	addOption(NumberOption<float>(SCROLL, "Walking noclip speed")
		.addNumber(vars.speedmult, "%.1f", 0.5f).addMin(0.5f).addMax(10.0f)
		.addHotkey()
		.addTooltip("Control the speed of your walking noclip"));

	addOption(BreakOption("Super run").addTranslation());

	addOption(NumberOption<float>(TOGGLE, "Super run")
		.addToggle(vars.speedboost)
		.addNumber(vars.speedboostamount, "%.1f", 0.2f).addMin(0).addMax(10)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Use the assigned key to super run"));

	addOption(KeyOption("Super run key")
		.addKeyWithControllerSupport(vars.boostKey, vars.boostKeyController)
		.canBeSaved().addHotkey().addTranslation()
		.addTooltip("Set the key"));

	addOption(BreakOption("Water").addTranslation());

	addOption(ToggleOption("Walk on water")
		.addToggle(vars.walkonwater)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Walk on water"));

	addOption(ToggleOption("Walk through water")
		.addToggle(vars.walkthroughwater)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Walk through water"));
}

/*Update once when submenu is opened*/
void PlayerMovementMenu::UpdateOnce() {}

/*Update while submenu is active*/
void PlayerMovementMenu::Update() {}

/*Background update*/
void PlayerMovementMenu::FeatureUpdate() {
	if (vars.flymode) FlyMode();
	if (vars.speedboost)KeyBoost(vars.speedboostamount);
	if (vars.noclip) Noclip();
	if (vars.fastrun)FastRun();
	if (vars.superjump)SuperJump();
	if (vars.ultrajump)UltraJump();
	if (vars.walkonwater)WalkOnWater();
	if (vars.walkthroughwater)WalkThroughWater();
	if (vars.walkonair)WalkOnAir();
	if (vars.slowmotion)SlowMotion(true);
	if (vars.vegetablemode)VegetableMode();
	if (vars.walkingnoclip) WalkingNoclip();
}

/*Singleton*/
PlayerMovementMenu* _instance;
PlayerMovementMenu* PlayerMovementMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new PlayerMovementMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
PlayerMovementMenu::~PlayerMovementMenu() { delete _instance; }