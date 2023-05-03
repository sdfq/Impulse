#include "stdafx.h"
#include "TeleportMenu.h"
#include "teleport/landmarksTeleportMenu.h"
#include "teleport/storyModeTeleportMenu.h"
#include "teleport/glitchedTeleportMenu.h"
#include "teleport/customTeleportMenu.h"
#include "teleport/insideTeleportMenu.h"
#include "teleport/IPLTeleportMenu.h"
#include "teleport/onlineTeleportsMenu.h"
#include "../mainMenu.h"

using namespace TeleportMenuVars;

namespace TeleportMenuVars {
	Vars vars;

	enum eBlipColor {
		ColorWhite = 0,
		ColorRed = 1,
		ColorGreen = 2,
		ColorBlue = 3,
		ColorPlayer = 4,
		ColorYellow = 5,
		ColorPurple = 7,
		ColorVehicle = 38,
		ColorMichael = 42,
		ColorFranklin = 43,
		ColorTrevor = 44,
		ColorMissionRed = 49,
		ColorMissionVehicle = 54,
		ColorYellowMission = 66,
		ColorYellowMission2 = 60,
		ColorWaypoint = 83,
	};

	Vector3 GetWaypointCoords() {
		static Vector3 zero;
		Vector3 coords;

		bool blipFound = false;
		int blipIterator = HUD::_GetBlipInfoIdIterator();
		for (Blip i = HUD::GetFirstBlipInfoId(blipIterator); HUD::DoesBlipExist(i) != 0; i = HUD::GetNextBlipInfoId(blipIterator)) {
			if (HUD::GetBlipInfoIdType(i) == 4) {
				coords = HUD::GetBlipInfoIdCoord(i);
				blipFound = true;
				break;
			}
		}
		if (blipFound) return coords;

		return zero;
	}

	Cam TransitionCam;
	void TeleportToCoords(float x, float y, float z, bool exception = true) {
		if (vars.transition && exception) {
			if (!CAM::DoesCamExist(TransitionCam)) {
				TransitionCam = CAM::CreateCam("DEFAULT_SCRIPTED_CAMERA", 0);
				if (GetLocalPlayer().m_isInVehicle) {
					ENTITY::SetEntityCoords(GetLocalPlayer().m_vehicle, x, y, z, 0, 0, 0, 1);
				} else {
					ENTITY::SetEntityCoords(GetLocalPlayer().m_ped, x, y, z, 0, 0, 0, 1);
				}
				CAM::SetCamActive(TransitionCam, 1);
				CAM::RenderScriptCams(1, 1, 4000, 1, 0, 0);
				STREAMING::_SetFocusArea(x, y, z, 0, 0, 0);
				CAM::SetCamCoord(TransitionCam, x, y, (z + 500));
				STREAMING::SetFocusEntity(GetLocalPlayer().m_ped);
				WAIT(4000);
				STREAMING::SetFocusEntity(GetLocalPlayer().m_ped);
				CAM::SetCamActive(TransitionCam, 0);
				CAM::RenderScriptCams(0, 1, 3000, 1, 0, 0);
				CAM::DestroyCam(TransitionCam, 0);
			}
		} 
		else if (GetLocalPlayer().m_isInVehicle) ENTITY::SetEntityCoords(GetLocalPlayer().m_vehicle, x, y, z, 0, 0, 0, 1);
		else ENTITY::SetEntityCoords(GetLocalPlayer().m_ped, x, y, z, 0, 0, 0, 1);
	}

	void TeleportToCoords(Vector3 coords) { TeleportToCoords(coords.x, coords.y, coords.z); }

	void TeleportForward() {
		Vector3 pos = GetLocalPlayer().m_coordinates;
		Vector3 dir = ENTITY::GetEntityForwardVector(GetLocalPlayer().m_ped);
		TeleportToCoords(pos.x + (dir.x * 8.0f), pos.y + (dir.y * 8.0f), pos.z - 0.5f, false);
	}

	void TeleportUp() {
		Vector3 pos = GetLocalPlayer().m_coordinates;
		TeleportToCoords(pos.x, pos.y, pos.z + 8, false);
	}

	Vehicle GetClosestVeh() {
		Vector3 coords = ENTITY::GetOffsetFromEntityInWorldCoords(GetLocalPlayer().m_ped, 0, 0, 0);;
		Vehicle vehicle = VEHICLE::GetClosestVehicle(coords.x, coords.y, coords.z, 10000.f, 0, 100359);
		return ENTITY::DoesEntityExist(vehicle) ? vehicle : NULL;
	}

	void TeleportToNearestVehicle(bool drive) {
		Vehicle xveh = GetClosestVeh();
		if (xveh != NULL) {
			if (drive) {
				Ped ped = VEHICLE::GetPedInVehicleSeat(xveh, -1, 1);
				while (ENTITY::DoesEntityExist(ped) && PED::IsPedInAnyVehicle(ped, false)) {
					BRAIN::ClearPedTasksImmediately(ped);
				}
				PED::SetPedIntoVehicle(GetLocalPlayer().m_ped, xveh, -1);
			} else PED::SetPedIntoVehicle(GetLocalPlayer().m_ped, xveh, Utils::GetFreeSeat(xveh));
		}
	}

	void TeleportToLastDrivenVehicle() {
		Vehicle vehicle = GetLocalPlayer().m_lastVehicle;
		if (ENTITY::DoesEntityExist(vehicle)) {
			Ped ped = VEHICLE::GetLastPedInVehicleSeat(vehicle, -1);
			GetEntityControl()->SimpleRequestControl(ped);
			BRAIN::ClearPedTasksImmediately(ped);
			PED::SetPedIntoVehicle(GetLocalPlayer().m_ped, vehicle, -1);
		} else GetRenderer()->NotifyBottom("Can't find last driven vehicle");
	}

	void TeleportToWaypoint() {
		Vector3 coords = GetWaypointCoords();

		/*if (coords.x == 0 && coords.y == 0) {
			GetRenderer()->NotifyBottom("No waypoint has been set!");
			return;
		}*/

		bool blipFound = false;
		int blipIterator = HUD::_GetBlipInfoIdIterator();
		for (Blip i = HUD::GetFirstBlipInfoId(blipIterator); HUD::DoesBlipExist(i) != 0; i = HUD::GetNextBlipInfoId(blipIterator)) {
			if (HUD::GetBlipInfoIdType(i) == 4) {
				coords = HUD::GetBlipInfoIdCoord(i);
				blipFound = true;
				break;
			}
		}

		if (coords.x == 0 && coords.y == 0 && !blipFound) {
			GetRenderer()->NotifyBottom("No waypoint has been set!");
			return;
		}

		// get entity to teleport
		Entity e = GetLocalPlayer().m_isInVehicle ? GetLocalPlayer().m_vehicle : GetLocalPlayer().m_ped;

		bool groundFound = false;
		static float groundCheckHeight[] =
		{ 100.0, 150.0, 50.0, 0.0, 200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0 };
		for (int i = 0; i < sizeof(groundCheckHeight) / sizeof(float); i++) {
			ENTITY::SetEntityCoordsNoOffset(e, coords.x, coords.y, groundCheckHeight[i], 0, 0, 1);
			WAIT(100);
			if (MISC::GetGroundZFor3DCoord(coords.x, coords.y, groundCheckHeight[i], &coords.z, 0)) {
				groundFound = true;
				coords.z += 3.0;
				break;
			}
		}
		if (!groundFound) {
			coords.z = 1000.0;
			WEAPON::GiveDelayedWeaponToPed(GetLocalPlayer().m_ped, 0xFBAB5776, 1, 0);
		}
		TeleportToCoords(coords.x, coords.y, coords.z, false);
	}

	Vector3 GetTeleportCoordsFixedHeight() {
		Vector3 coords = GetWaypointCoords();

		if (coords.x == 0.f && coords.y == 0.f) {
			return Vector3();
		}

		bool groundFound = false;
		for (float i = 100.0f; i <= 800.0f; i += 50.0f) {
			if (MISC::GetGroundZFor3DCoord(coords.x, coords.y, i, &coords.z, 0)) {
				groundFound = true;
				coords.z += 3.0f;
				break;
			}
		}

		if (!groundFound) {
			coords.z = 1000.0f;
		}

		return coords;
	}

	void TeleportToMissionObjective() {
		static Vector3 v3BlipCoords;
		Entity ent = GetLocalPlayer().m_entity;
		bool bBlipFound = false, bSuccess = false;

		if (bBlipFound == false) {
			for (Blip j = HUD::GetFirstBlipInfoId(38); HUD::DoesBlipExist(j) != 0; j = HUD::GetNextBlipInfoId(38)) {
				if (HUD::GetBlipColour(j) == 0x0) {
					v3BlipCoords = HUD::GetBlipCoords(j);
					bBlipFound = true;
					break;
				}
			}

			for (Blip k = HUD::GetFirstBlipInfoId(431); HUD::DoesBlipExist(k) != 0; k = HUD::GetNextBlipInfoId(431)) {
				if (HUD::GetBlipColour(k) == 0x3C) {
					v3BlipCoords = HUD::GetBlipCoords(k);
					bBlipFound = true;
					break;
				}
			}
			for (Blip i = HUD::GetFirstBlipInfoId(1); HUD::DoesBlipExist(i) != 0; i = HUD::GetNextBlipInfoId(1)) {
				if (HUD::GetBlipColour(i) == 0x42 || HUD::GetBlipColour(i) == 0x5 || HUD::GetBlipColour(i) == 0x3C || HUD::GetBlipColour(i) == 0x2) {
					v3BlipCoords = HUD::GetBlipCoords(i);
					bBlipFound = true;
					break;
				}
			}

			if (bBlipFound) {
				TeleportToCoords(v3BlipCoords.x, v3BlipCoords.y, v3BlipCoords.z);
			} else {
				GetRenderer()->NotifyBottom("No objective found");
			}
		}
	}

	void TeleportToPV() {
		bool found = false;
		Vector3 WaypointPos;
		for (size_t i = 225; i < 227; i++) {
			int WaypointHandle = HUD::GetFirstBlipInfoId(i);
			if (HUD::DoesBlipExist(WaypointHandle)) {
				WaypointPos = HUD::GetBlipCoords(WaypointHandle);
				TeleportToCoords(WaypointPos.x, WaypointPos.y, WaypointPos.z);
			}
		}
		if (found) {
			Vehicle veh = VEHICLE::GetClosestVehicle(WaypointPos.x, WaypointPos.y, WaypointPos.z, 1, 0, 70);
			PED::SetPedIntoVehicle(GetLocalPlayer().m_ped, veh, Utils::GetFreeSeat(veh));
		} else GetRenderer()->NotifyBottom("Personal vehicle not found");
	}

	void TeleportToBlip(int blipID, char* notFound) {
		int WaypointHandle = HUD::GetFirstBlipInfoId(blipID);
		if (HUD::DoesBlipExist(WaypointHandle)) {
			Vector3 WaypointPos = HUD::GetBlipCoords(WaypointHandle);
			TeleportToCoords(WaypointPos.x, WaypointPos.y, WaypointPos.z);
		} else GetRenderer()->NotifyBottom(notFound);
	}

	void TeleportToBlipColor(int blipID, int col, char* notFound) {
		int blip = HUD::GetFirstBlipInfoId(blipID);
		if (HUD::DoesBlipExist(blip)) {
			if (HUD::GetBlipColour(blip) == col) {
				Vector3 WaypointPos = HUD::GetBlipCoords(blip);
				TeleportToCoords(WaypointPos.x, WaypointPos.y, WaypointPos.z);
			}
		} else {
			GetRenderer()->NotifyBottom(notFound);
		}
	}

	void TeleportToWaypointHotkey() {
		if ((vars.teleportToWaypointIsController && PAD::IsDisabledControlPressed(0, vars.teleportToWaypointKey)) || KeyDown(vars.teleportToWaypointKey)) {
			TeleportToWaypoint();
		}
	}

	void SaveTeleportLoc(String fileName) {
		ofstream i(fileName);

		json j;

		j["teleport"]["location"] = json::array({
			{ GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, GetLocalPlayer().m_coordinates.z }
			});

		i << setw(4) << j;
		i.close();
	}
}

void TeleportMenu::Init() {
	setParentSubmenu<MainMenu>();
	setName("Teleport", true, true);

	addOption(ButtonOption("Teleport to waypoint")
		.addFunction([] {TeleportToWaypoint(); })
		.addTranslation()
		.addTooltip("Teleport to waypoint"));

	addOption(KeyOption("Waypoint hotkey")
		.addKeyWithControllerSupport(vars.teleportToWaypointKey, vars.teleportToWaypointIsController)
		.canBeSaved().addTranslation()
		.addTooltip("Set a hotkey for teleporting to your current waypoint"));

	addOption(BreakOption("Custom saved locations").addTranslation());

	addOption(ButtonOption("Save current location")
		.addFunction([this] {
		GetMenuInput()->AddToQueue([this] {
			string temp;
			if (GetMenuInput()->Text("Teleport name", temp, 2, 15)) {
				String file = va("%s/%s.json", GetConfig()->GetTeleportsPath(), temp.c_str());
				if (GetConfig()->DoesFileExist(file)) {
					GetRenderer()->NotifyBottom(getString("A file with that name already exists. Try again."));
				}
				else SaveTeleportLoc(file);
			}});
	}).addTranslation()
		.addHotkey()
		.addTooltip("Save teleport to json file"));

	addOption(SubmenuOption("Load custom locations")
		.addSubmenu<CustomTeleportMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Teleports to custom saved locations"));

	addOption(BreakOption("Locations").addTranslation());

	addOption(ToggleOption("Teleport transition")
		.addToggle(vars.transition)
		.addTooltip("Use a transition for your teleporting")
		.addTranslation().canBeSaved().addHotkey());

	addOption(SubmenuOption("Online")
		.addSubmenu<OnlineTeleportsMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Teleports to online locations"));

	addOption(SubmenuOption("Landmarks")
		.addSubmenu<LandmarksTeleportMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Teleports to landmarks"));

	addOption(SubmenuOption("Inside")
		.addSubmenu<InsideTeleportMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Teleports to inside locations"));

	addOption(SubmenuOption("Story mode locations")
		.addSubmenu<StoryModeTeleportMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Teleports to story mode locations"));

	addOption(SubmenuOption("Glitched locations")
		.addSubmenu<GlitchedTeleportMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Teleports to glitched locations"));

	addOption(SubmenuOption("IPL Locations")
		.addSubmenu<IPLTeleportMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Teleports to IPL locations"));

	addOption(BreakOption("Blips").addTranslation());

	addOption(ButtonOption("Teleport to objective")
		.addFunction([] {TeleportToMissionObjective(); })
		.addHotkey().addTranslation()
		.addTooltip("Teleport to objective"));

	addOption(ButtonOption("Teleport to apartment")
		.addFunction([] {TeleportToBlip(40, "Apartment not found"); })
		.addHotkey().addTranslation()
		.addTooltip("Teleport to apartment"));

	addOption(ButtonOption("Teleport to yacht")
		.addFunction([] {TeleportToBlip(455, "Yacht not found"); })
		.addHotkey().addTranslation()
		.addTooltip("Teleport to yacht"));

	addOption(ButtonOption("Teleport to office")
		.addFunction([] {TeleportToBlip(475, "Office not found"); })
		.addHotkey().addTranslation()
		.addTooltip("Teleport to office"));

	//

	addOption(ButtonOption("Teleport to clubhouse")
		.addFunction([] {TeleportToBlip(492, "clubhouse not found"); })
		.addHotkey().addTranslation()
		.addTooltip("Teleport to clubhouse"));

	addOption(ButtonOption("Teleport to weed farm")
		.addFunction([] {TeleportToBlip(496, "weed farm not found"); })
		.addHotkey().addTranslation()
		.addTooltip("Teleport to weed farm"));

	addOption(ButtonOption("Teleport to counterfeit cash")
		.addFunction([] {TeleportToBlip(500, "counterfeit cash not found"); })
		.addHotkey().addTranslation()
		.addTooltip("Teleport to counterfeit cash"));

	addOption(ButtonOption("Teleport to meth lab")
		.addFunction([] {TeleportToBlip(499, "meth lab not found"); })
		.addHotkey().addTranslation()
		.addTooltip("Teleport to meth lab"));

	addOption(ButtonOption("Teleport to cocaine factory")
		.addFunction([] {TeleportToBlip(497, "cocaine factory not found"); })
		.addHotkey().addTranslation()
		.addTooltip("Teleport to cocaine factory"));

	addOption(ButtonOption("Teleport to own package")
		.addFunction([] {TeleportToBlipColor(501, ColorGreen, "own package not found"); })
		.addHotkey().addTranslation()
		.addTooltip("Teleport to own package"));

	addOption(ButtonOption("Teleport to enemy package")
		.addFunction([] {TeleportToBlipColor(501, ColorRed, "enemy package not found"); })
		.addHotkey().addTranslation()
		.addTooltip("Teleport to enemy package"));

	addOption(ButtonOption("Teleport to own crate")
		.addFunction([] {TeleportToBlipColor(478, ColorGreen, "own crate not found"); })
		.addHotkey().addTranslation()
		.addTooltip("Teleport to own crate"));

	addOption(ButtonOption("Teleport to enemy crate")
		.addFunction([] {TeleportToBlipColor(478, ColorRed, "enemy crate not found"); })
		.addHotkey().addTranslation()
		.addTooltip("Teleport to enemy crate"));

	addOption(BreakOption("Vehicle").addTranslation());

	addOption(ButtonOption("Nearest car (become driver)")
		.addFunction([] {TeleportToNearestVehicle(true); })
		.addHotkey().addTranslation()
		.addTooltip("Drive the closest vehicle"));

	addOption(ButtonOption("Nearest car (any free seat)")
		.addFunction([] {TeleportToNearestVehicle(false); })
		.addHotkey().addTranslation()
		.addTooltip("Join the closest vehicle"));

	addOption(ButtonOption("Teleport to last driven vehicle")
		.addFunction([] {TeleportToLastDrivenVehicle(); })
		.addHotkey().addTranslation()
		.addTooltip("Teleport to last driven vehicle"));

	addOption(ButtonOption("Teleport to personal vehicle")
		.addFunction([] {TeleportToPV(); })
		.addHotkey().addTranslation()
		.addTooltip("Teleport to personal vehicle"));

	addOption(BreakOption("Directional").addTranslation());

	addOption(ButtonOption("Teleport forward")
		.addFunction([] {TeleportForward(); })
		.addHotkey().addTranslation()
		.addTooltip("Teleport forward"));

	addOption(ButtonOption("Teleport up")
		.addFunction([] {TeleportUp(); })
		.addHotkey().addTranslation()
		.addTooltip("Teleport up"));
}

/*Update once when submenu is opened*/
void TeleportMenu::UpdateOnce() {}

/*Update while submenu is active*/
void TeleportMenu::Update() {}

/*Background update*/
void TeleportMenu::FeatureUpdate() {
	TeleportToWaypointHotkey();

}

/*Singleton*/
TeleportMenu* _instance;
TeleportMenu* TeleportMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new TeleportMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
TeleportMenu::~TeleportMenu() { delete _instance; }