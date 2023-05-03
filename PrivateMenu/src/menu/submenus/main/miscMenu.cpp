#include "stdafx.h"
#include "miscMenu.h"
#include "../mainMenu.h"
#include "misc/miscExternalLinks.h"
#include "misc/miscTrainOptions.h"
#include "misc/miscReportStats.h"
#include "misc/miscDisable.h"
#include "misc/miscTVMenu.h"
#include "menu\submenus\main\misc\hudEditor.h"
#include "menu/submenus/main/sessionMenu.h"
#include "menu/submenus/main/misc/tuneablesMenu.h"

using namespace MiscMenuVars;

namespace MiscMenuVars {
	Vars vars;

	void SeeThroughWalls() {
		CAM::_0x42156508606DE65E(418.490f);
	}

	void PrintText(string text, int font, float x, float y, float scalex, float scaley, int r, int g, int b, int a, bool center, bool outline) {
		HUD::SetTextFont(font);
		HUD::SetTextScale(scalex, scaley);
		HUD::SetTextColour(r, g, b, a);
		HUD::SetTextWrap(0.0f, 1.0f);
		HUD::SetTextCentre(center);
		HUD::SetTextDropshadow(0, 0, 0, 0, 0);
		if (outline)
			HUD::SetTextOutline();
		HUD::BeginTextCommandDisplayText("STRING");
		HUD::AddTextComponentSubstringPlayerName(&text[0u]);
		HUD::EndTextCommandDisplayText(x, y, 0);
		HUD::SetTextDropshadow(0, 0, 0, 0, 0);
	}

	String restrictedAreaScripts[] = {
		"am_armybase",
		"restrictedareas",
		"re_armybase",
		"re_lossantosintl",
		"re_prison",
		"re_prisonvanbreak"
	};

	void EnableRestrictedAreas() {
		if (vars.enablerestrictedareas) {
			for (String& str : restrictedAreaScripts) {
				if (SCRIPT::DoesScriptExist(str))
					MISC::TerminateAllScriptsWithThisName(str);
			}
		}
	}

	void BypassChatRestrictions() {
		NETWORK::NetworkOverrideChatRestrictions(GetLocalPlayer().m_ped, true);
		NETWORK::NetworkOverrideReceiveRestrictions(GetLocalPlayer().m_ped, true);
		NETWORK::NetworkOverrideSendRestrictions(GetLocalPlayer().m_ped, true);
	}

	void PotatoPcMode() {
		STREAMING::_SetFocusArea(9999.0f, 9999.0f, -9999.0f, 0.0f, 0.0f, 0.0f);
	}

	void MobileRadio() {
		AUDIO::SetMobileRadioEnabledDuringGameplay(1);
	}

	void SnowTrails() {
		GRAPHICS::_SetForcePedFootstepsTracks(true);
		GRAPHICS::_SetForceVehicleTrails(true);
	}

	void OldStyleGameplayCam() {
		if (!CAM::DoesCamExist(vars.OldStyleGameplayCamHandle)) {
			vars.OldStyleGameplayCamHandle = CAM::CreateCam("DEFAULT_SCRIPTED_CAMERA", 0);
			CAM::AttachCamToPedBone(vars.OldStyleGameplayCamHandle, GetLocalPlayer().m_ped, 31086, 0, 0, 15, 1);
			CAM::SetCamActive(vars.OldStyleGameplayCamHandle, 1);
			CAM::RenderScriptCams(1, 1, 1000, 1, 0, 0);
		} else {
			Vector3 Rotation = CAM::GetGameplayCamRot(2);
			CAM::SetCamRot(vars.OldStyleGameplayCamHandle, -88, Rotation.y, Rotation.z, 2);
		}
	}

}

void MiscMenu::Init() {
	setParentSubmenu<MainMenu>();
	setName("Miscellaneous", true, true);

	addOption(SubmenuOption("Report stats")
		.addTranslation().addHotkey()
		.addSubmenu<MiscReportStatsMenu>()
		.addTooltip("Report stats"));

	addOption(SubmenuOption("Mobile TV")
		.addTranslation().addHotkey()
		.addSubmenu<MiscTVMenu>()
		.addTooltip("Watch TV on the go"));

	addOption(SubmenuOption("Disables")
		.addTranslation().addHotkey()
		.addSubmenu<MiscDisableMenu>()
		.addTooltip("Disables"));

	addOption(SubmenuOption("External links")
		.addSubmenu<MiscExternalLinksMenu>()
		.addTranslation().addHotkey()
		.addTooltip("Open a submenu to show accessible links"));

	addOption(SubmenuOption("Hud editor")
		.addSubmenu<HudEditor>()
		.addTranslation().addHotkey()
		.addTooltip("Change the color of your HUD elements"));

	addOption(SubmenuOption("Train options")
		.addSubmenu<MiscTrainOptions>()
		.addTranslation().addHotkey()
		.addTooltip("Contains options to control and spawn trains"));

	addOption(SubmenuOption("Tuneables")
		.addRequirement([] { return GetAuth()->IsTester(); })
		.addSubmenu<TunablesMenu>()
		.addTranslation().addHotkey()
		.addTooltip("Control local side tuneables"));

	addOption(BreakOption("Camera").addTranslation());

	addOption(ToggleOption("Freecam")
		.addToggle(vars.freecam)
		.addFunction([] {
		if (!vars.freecam) {
			if (CAM::DoesCamExist(vars.freecamHandle)) {
				CAM::SetCamActive(vars.freecamHandle, 0);
				CAM::RenderScriptCams(0, 0, 2000, 1, 0, 1);
				if (vars.spawnatfreecam) {
					Entity teleportent = GetLocalPlayer().m_isInVehicle ? GetLocalPlayer().m_vehicle : GetLocalPlayer().m_ped;
					Vector3 camCoords = CAM::GetCamCoord(vars.freecamHandle);
					ENTITY::SetEntityCoords(teleportent, camCoords.x, camCoords.y, camCoords.z, 1, 0, 0, 1);
				}
				CAM::DestroyCam(vars.freecamHandle, 0);
				if (GetLocalPlayer().m_isInVehicle) ENTITY::FreezeEntityPosition(GetLocalPlayer().m_vehicle, false);
				if (GetLocalPlayer().m_isInVehicle)	ENTITY::ApplyForceToEntity(GetLocalPlayer().m_vehicle, true, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, true, false, true, true, true, true);
				STREAMING::SetFocusEntity(GetLocalPlayer().m_ped);
			}
		}
	}).addTranslation().addHotkey()
		.addTooltip("Freecam"));

	addOption(NumberOption<float>(SCROLL, "Freecam speed")
		.addNumber(vars.freecamspeed, "%.1f", 0.1f).addMin(0.1f).addMax(5.0f)
		.addHotkey()
		.addTooltip("Control the forward and back speed of the freecam").addTranslation());

	addOption(ToggleOption("Freecam attack mode")
		.addTranslation().canBeSaved()
		.addToggle(vars.freecamAttack)
		.addTooltip("To fire rockets press space").addHotkey()
		.addRequirement([] { return GetAuth()->IsVIP(); }));

	addOption(ToggleOption("Freecam teleport")
		.addTranslation().canBeSaved()
		.addToggle(vars.spawnatfreecam)
		.addTooltip("This will teleport you to the final location of freecam").addHotkey());

	addOption(ToggleOption("Freecam controller toggle")
		.addTranslation().canBeSaved()
		.addToggle(vars.alwaysoncontrollerfreecam)
		.addTooltip("This will allow on and off of freecam using a controller - DPAD Right = Enable / RB = Disable").addHotkey());

	addOption(ToggleOption("GTA 1 camera")
		.addToggle(vars.oldstylegameplaycam)
		.addFunction([] {
		if (!vars.oldstylegameplaycam) {
			if (CAM::DoesCamExist(vars.OldStyleGameplayCamHandle)) {
				CAM::SetCamActive(vars.OldStyleGameplayCamHandle, 0);
				CAM::RenderScriptCams(0, 1, 1000, 1, 0, 0);
				CAM::DestroyCam(vars.OldStyleGameplayCamHandle, 0);
			}
		}})
		.addHotkey().canBeSaved().addTranslation()
			.addTooltip("This will make your games camera function like gta 1"));

	addOption(NumberOption<int>(TOGGLE, "Camera zoom")
		.addToggle(vars.cameraZoom)
		.addNumber(vars.cameraZoomValue, "%i", 1).addMin(1).addMax(1000).setScrollSpeed(10)
		.addTooltip("Camera zoom"));

	//addOption(BreakOption("Bypass").addTranslation());

	/*addOption(ToggleOption("Bypass chat restrictions")
		.addToggle(vars.bypasschatrestrictions)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("This will allow you to bypass chat restrictions"));*/

	/*addOption(ToggleOption("Bypass organization chat")
		.addToggle(vars.bypassOrganizationChat)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Bypass organization chat"));*/

	addOption(BreakOption("HUD/Display Options").addTranslation());

	addOption(ToggleOption("FPS display")
		.addToggle(vars.fps)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Display your FPS"));

	addOption(ToggleOption("Coords display")
		.addToggle(SessionMenuVars::vars.showcoords)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Display your current coords"));

	addOption(ButtonOption("Remove transaction loading")
		.addFunction([] {if (HUD::_IsLoadingPromptBeingDisplayed()) HUD::_RemoveLoadingPrompt(); })
		.addHotkey().addTranslation()
		.addTooltip("Remove a stuck transaction loading"));

	addOption(ToggleOption("Decreased graphics mode")
		.addToggle(vars.potatopcmode)
		.addFunction([] { if (!vars.potatopcmode) STREAMING::SetFocusEntity(GetLocalPlayer().m_ped); })
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Warning: once enabled your game will look like ass"));

	addOption(ButtonOption("Reset graphics in your area")
		.addFunction([] {STREAMING::SetFocusEntity(GetLocalPlayer().m_ped); })
		.addHotkey().addTranslation()
		.addTooltip("Use this to fix any map loading issues"));

	addOption(BreakOption("Other").addTranslation());

	addOption(ToggleOption("Dev mode")
		.addToggle(Backend::DevMode)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Enter GTA developer mode (SCTV)"));

	addOption(ToggleOption("Mobile radio")
		.addToggle(vars.mobileradio)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("This allows you to listen to radio while on the move"));

	addOption(ButtonOption("Skip radio track")
		.addFunction([] {
		AUDIO::SkipRadioForward();
	})
		.addHotkey().addTranslation()
		.addTooltip("Skip [local] radio tracks on mobile radio (this is using your own applied music)"));

	addOption(ToggleOption("Bypass restricted areas")
		.addToggle(vars.enablerestrictedareas)
		.addFunction(EnableRestrictedAreas)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("This will allow you to access restricted areas of the game"));

	addOption(ToggleOption("See through walls")
		.addToggle(vars.seethroughwalls)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("This will allow you to see through walls when aiming"));

	addOption(ToggleOption("Enable snow trails & footsteps")
		.addToggle(vars.snowtrails)
		.addFunction([] { if (!vars.snowtrails) GRAPHICS::_SetForcePedFootstepsTracks(false);  GRAPHICS::_SetForceVehicleTrails(false); })
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Set footsteps and vehicle trails in snow (will work without too)"));

	addOption(ButtonOption("Bail to singleplayer")
		.addFunction([]
			{
				NETWORK::NetworkBail(0, 0, 0);
			})
		.addTooltip("Stuck in the clouds? Bind this option to bail back to SP and retry to join!")
		.addHotkey()
		.addTranslation());
}

/*Update once when submenu is opened*/
void MiscMenu::UpdateOnce() {}

/*Update while submenu is active*/
void MiscMenu::Update() {}

/*Background update*/
void MiscMenu::FeatureUpdate() {
	if (vars.seethroughwalls) SeeThroughWalls();
	if (vars.enablerestrictedareas) EnableRestrictedAreas();
	//if (vars.bypasschatrestrictions) BypassChatRestrictions();
	if (vars.potatopcmode) PotatoPcMode();
	if (vars.snowtrails) SnowTrails();
	if (vars.mobileradio) MobileRadio();
	if (vars.oldstylegameplaycam) OldStyleGameplayCam();
	/*if (vars.bypassOrganizationChat) {
		NETWORK::NetworkOverrideChatRestrictions(GetLocalPlayer().m_id, true);
	}*/
	if (vars.disableIdleKick) {
		Global(Globals::NOIDLEKICK).At(Globals::NOIDLEKICK2).As<int>() = -1;
		Global(Globals::NOIDLEKICK).At(Globals::NOIDLEKICK3).As<int>() = -1;
	}
	if (vars.disableCinematicButton) {
		CAM::SetCinematicButtonActive(0);
		CAM::StopGameplayHint(true);
		AUDIO::StopAudioScene("HINT_CAM_SCENE");
		GRAPHICS::_StopScreenEffect("FocusIn");
		GRAPHICS::_StopScreenEffect("FocusOut");
	}
	if (vars.disableStuntJumpCutscenes) {
		if (MISC::IsStuntJumpInProgress()) {
			MISC::CancelStuntJump();
		}
	}
	if (vars.disableNotifications) {
		//HUD::_RemoveNotification(HUD::_GetCurrentNotification());
		//
		HUD::_0x25F87B30C382FCA7();//_HIDE_NOTIFICATIONS_THIS_FRAME
		//SCRIPT::SetNoLoadingScreen(true);
		//
		//PAD::_0x6CD79468A1E595C6(2); //disable phone
	}
	if (vars.disableGameRecordings) {
		if (RECORDING::_IsRecording()) {
			RECORDING::_StopRecordingAndDiscardClip();
		}
	}
	if (vars.disableHUD) {
		HUD::HideHudAndRadarThisFrame();
	}
	if (vars.cameraZoom) {
		CAM::_AnimateGameplayCamZoom(1.0f, vars.cameraZoomValue);
	}

	if (vars.alwaysoncontrollerfreecam) {
		if (PAD::IsControlPressed(0, INPUT_FRONTEND_RIGHT)) vars.freecam = true;

		if (PAD::IsControlPressed(0, INPUT_FRONTEND_RB)) {
			vars.freecam = false;
			if (!vars.freecam) {
				if (CAM::DoesCamExist(vars.freecamHandle)) {
					CAM::SetCamActive(vars.freecamHandle, 0);
					CAM::RenderScriptCams(0, 0, 2000, 1, 0, 1);
					if (vars.spawnatfreecam) {
						Entity teleportent = GetLocalPlayer().m_isInVehicle ? GetLocalPlayer().m_vehicle : GetLocalPlayer().m_ped;
						Vector3 camCoords = CAM::GetCamCoord(vars.freecamHandle);
						ENTITY::SetEntityCoords(teleportent, camCoords.x, camCoords.y, camCoords.z, 1, 0, 0, 1);
					}
					CAM::DestroyCam(vars.freecamHandle, 0);
					if (GetLocalPlayer().m_isInVehicle) ENTITY::FreezeEntityPosition(GetLocalPlayer().m_vehicle, false);
					if (GetLocalPlayer().m_isInVehicle)	ENTITY::ApplyForceToEntity(GetLocalPlayer().m_vehicle, true, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, true, false, true, true, true, true);
					STREAMING::SetFocusEntity(GetLocalPlayer().m_ped);
				}
			}
		}
	}

	if (vars.freecam) {

		if (!CAM::DoesCamExist(vars.freecamHandle)) {
			Vector3 coords = GetLocalPlayer().m_coordinates;
			vars.freecamHandle = CAM::CreateCam("DEFAULT_SCRIPTED_CAMERA", 0);
			CAM::SetCamActive(vars.freecamHandle, 1);
			CAM::RenderScriptCams(1, 0, 2000, 1, 0, 1);
			CAM::SetCamCoord(vars.freecamHandle, coords.x, coords.y, coords.z);
		} else {
			if (GetLocalPlayer().m_isInVehicle) {
				ENTITY::FreezeEntityPosition(GetLocalPlayer().m_vehicle, true);
			}
			if (!GetLocalPlayer().m_isInVehicle) {
				BRAIN::ClearPedTasksImmediately(GetLocalPlayer().m_ped);
			}

			Vector3 camCoords = CAM::GetCamCoord(vars.freecamHandle);
			Vector3 gameCamRot = CAM::GetGameplayCamRot(0);
			CAM::SetCamRot(vars.freecamHandle, gameCamRot.x, gameCamRot.y, gameCamRot.z, 2);

			if (vars.freecamAttack) {
				GetRenderer()->DrawSprite({ "shared", "menuplus_32" }, 0.5f, 0.5f, 0.03f, 0.03f, 0.0f, Color(255, 0, 0, 180));
			}

			Vector3 infront;
			Utils::GetCameraDirection(&infront.x, &infront.y, &infront.z);

			if (vars.freecamAttack) {
				if (KeyJustDown(VK_SPACE)) {
					MISC::ShootSingleBulletBetweenCoords(camCoords.x, camCoords.y, camCoords.z, camCoords.x + infront.x * 999, camCoords.y + infront.y * 999, camCoords.z + infront.z * 999, 1000, 0, 0xb1ca77b1, GetLocalPlayer().m_ped, 1, 1, 1000);
				}
			}

			if (KeyDown('W') || PAD::IsControlPressed(0, INPUT_FRONTEND_RT)) {
				CAM::SetCamCoord(vars.freecamHandle, camCoords.x + infront.x * vars.freecamspeed, camCoords.y + infront.y * vars.freecamspeed, camCoords.z + infront.z * vars.freecamspeed); //2
			}

			if (KeyDown('S') || PAD::IsControlPressed(0, INPUT_FRONTEND_LT)) {
				CAM::SetCamCoord(vars.freecamHandle, camCoords.x - infront.x * vars.freecamspeed, camCoords.y - infront.y * vars.freecamspeed, camCoords.z - infront.z * vars.freecamspeed); //2
			}

			if (KeyDown(0x41)) {
				Vector3 gameplayCamRot_new = gameCamRot;

				gameplayCamRot_new.x = 0;
				gameplayCamRot_new.y = 0;
				gameplayCamRot_new.z += 90;

				Vector3 new_coords = Utils::get_coords_infront_of_coords(camCoords, gameplayCamRot_new, 2);
				CAM::SetCamCoord(vars.freecamHandle, new_coords.x, new_coords.y, new_coords.z);
			}

			if (KeyDown(0x44)) {
				Vector3 gameplayCamRot_new = gameCamRot;

				gameplayCamRot_new.x = 0;
				gameplayCamRot_new.y = 0;
				gameplayCamRot_new.z -= 90;

				Vector3 new_coords = Utils::get_coords_infront_of_coords(camCoords, gameplayCamRot_new, 2);
				CAM::SetCamCoord(vars.freecamHandle, new_coords.x, new_coords.y, new_coords.z);
			}

			camCoords = CAM::GetCamCoord(vars.freecamHandle);
			
			static int TIMER;
			Utils::DoTimedFunction(&TIMER, 1000, [&] { STREAMING::_SetFocusArea(camCoords.x, camCoords.y, camCoords.z, 0, 0, 0); });
		}
	}
	if (vars.fps) {
		int FPS = vars.DrawFPSCache[0] - vars.DrawFPSCache[1] - 1;
		static float c_opacity = 1.0f;
		GetRenderer()->SetOpacityVariable(c_opacity);
		//GetRenderer()->DrawString(va("FPS: %i\n", FPS), 0.5f, 0.0f, GetRenderer()->m_textFont, 0.40f, Color(vars.Colorscreenelements.m_r, vars.Colorscreenelements.m_g, vars.Colorscreenelements.m_b, vars.Colorscreenelements.m_a), vars.Outlineonscreenelements);
		PrintText(va("FPS: %i\n", FPS), GetRenderer()->m_textFont, 0.5f, 0.0f, 0.40f, 0.40f, vars.Colorscreenelements.m_r, vars.Colorscreenelements.m_g, vars.Colorscreenelements.m_b, vars.Colorscreenelements.m_a, 0, vars.Outlineonscreenelements);
	}

	if (vars.displaycoords) {
		char buf[10];
		sprintf(buf, "XYZ: %.2f, %.2f, %.2f", (float)GetLocalPlayer().m_coordinates.x, (float)GetLocalPlayer().m_coordinates.y, (float)GetLocalPlayer().m_coordinates.z);
		PrintText(buf, 0, 0.01, 0.01 + (0.0188), 0, 0.35, MiscMenuVars::vars.Colorscreenelements.m_r, MiscMenuVars::vars.Colorscreenelements.m_g, MiscMenuVars::vars.Colorscreenelements.m_b, MiscMenuVars::vars.Colorscreenelements.m_a, 0, vars.Outlineonscreenelements);
	}

	static int TIMER;
	Utils::DoTimedFunction(&TIMER, 1000, [] {
		vars.DrawFPSCache[1] = vars.DrawFPSCache[0];
		vars.DrawFPSCache[0] = MISC::GetFrameCount();
	});
}

/*Singleton*/
MiscMenu* _instance;
MiscMenu* MiscMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new MiscMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
MiscMenu::~MiscMenu() { delete _instance; }