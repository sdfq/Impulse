#include "stdafx.h"
#include "ESPMenu.h"
#include "../playerMenu.h"
#include "menu/submenus/main/miscMenu.h"

using namespace ESPMenuVars;

namespace ESPMenuVars {

	Vars vars;

	void NameESP(SPlayer& player) {
		GetRenderer()->DrawString(player.m_name, player.m_w2s.x, player.m_w2s.y, 4, 0.30f, Color(255, 255, 255), true);
	}

	void LineESP(SPlayer& player) {
		Vector3 myCoords = GetLocalPlayer().m_coordinates;

		if (vars.ESPLOSGREEN && ENTITY::HasEntityClearLosToEntity(GetLocalPlayer().m_ped, player.m_ped, 1)) {
			GRAPHICS::DrawLine(myCoords.x, myCoords.y, myCoords.z, player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, vars.ESPLOSColor.m_r, vars.ESPLOSColor.m_g, vars.ESPLOSColor.m_b, vars.ESPLOSColor.m_a);
		} else {
			GRAPHICS::DrawLine(myCoords.x, myCoords.y, myCoords.z, player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, vars.ESPColor.m_r, vars.ESPColor.m_g, vars.ESPColor.m_b, vars.ESPColor.m_a);
		}
	}

	void HeadMarkerESP(SPlayer& player) {
		GRAPHICS::DrawMarker(21, player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z + 1.5, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f, 0.0f, 0.9f, 0.9f, 0.9f, vars.ESPColor.m_r, vars.ESPColor.m_g, vars.ESPColor.m_b, vars.ESPColor.m_a, true, false, 2, true, false, false, false);
	}

	void SkyLine(SPlayer& player) {
		if (player.m_id != GetLocalPlayer().m_id && player.m_coordinates.Distance(GetLocalPlayer().m_coordinates) <= 300.f) {
			GRAPHICS::DrawMarker(1, player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z + 1.5, 0.0f, 0.0f, 0.0f, 0, 0.0f, 0.0f, 0.9f, 0.9f, 200.0f, vars.ESPColor.m_r, vars.ESPColor.m_g, vars.ESPColor.m_b, vars.ESPColor.m_a, false, false, 2, true, false, false, false);
		} else {
			GRAPHICS::DrawMarker(1, player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z + 1.5, 0.0f, 0.0f, 0.0f, 0, 0.0f, 0.0f, 6.9f, 6.9f, 500.0f, vars.ESPColor.m_r, vars.ESPColor.m_g, vars.ESPColor.m_b, vars.ESPColor.m_a, false, false, 2, true, false, false, false);
		}
	}

	void FootMarkerESP(SPlayer& player) {
		GRAPHICS::DrawMarker(25, player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z - 0.90, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f, 0.0f, 0.9f, 0.9f, 0.9f, vars.ESPColor.m_r, vars.ESPColor.m_g, vars.ESPColor.m_b, vars.ESPColor.m_a, true, false, 2, true, false, false, false);
	}

	void InfoESP(SPlayer& player) {
		float x, y;
		Vector3 myCoords = GetLocalPlayer().m_coordinates;
		if (GRAPHICS::GetScreenCoordFromWorldCoord(player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, &x, &y)) {
			float dist = MISC::GetDistanceBetweenCoords(myCoords.x, myCoords.y, myCoords.z, player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, TRUE);
			if (dist < 2000.0f) {

				float speed = ENTITY::GetEntitySpeed(player.m_ped);
				int health = ENTITY::GetEntityHealth(player.m_ped);
				String name = player.m_name;
				String godmode = (player.m_isGod ? "Yes" : "No");
				String vehmodelname = VEHICLE::GetDisplayNameFromVehicleModel(ENTITY::GetEntityModel(PED::GetVehiclePedIsIn((player.m_ped), 0)));
				String veh = HUD::_GetLabelText(vehmodelname);
				float distance = player.m_coordinates.Distance(GetLocalPlayer().m_coordinates);
				if (MISC::AreStringsEqual(veh, "NULL"))	{
					veh = "On Foot";
				}

				char text[256];
				sprintf_s(text, " ~s~%s\n Vehicle: %s\n Speed: %.02f\n Health: %i\n Godmode/Int: %s\n Distance: %.02f", name, veh, speed, health, godmode, distance);
				HUD::SetTextFont(4);
				HUD::SetTextScale(0.30f, 0.30f);
				HUD::SetTextColour(255, 255, 255, 255);
				HUD::SetTextOutline();
				HUD::SetTextWrap(0.0, 1.0);
				HUD::SetTextCentre(0);
				HUD::SetTextEdge(1, 0, 0, 0, 205);
				HUD::BeginTextCommandDisplayText("STRING");
				HUD::AddTextComponentSubstringPlayerName(text);
				HUD::EndTextCommandDisplayText(x, y, 0);
			}
		}
	}

	typedef struct { int R, G, B, A; } RGBA;
	RGBA bonesColors = { vars.ESPColor.m_r, vars.ESPColor.m_g, vars.ESPColor.m_b, vars.ESPColor.m_a };

	enum eBone
	{
		SKEL_ROOT = 0x0,
		SKEL_Pelvis = 0x2e28,
		SKEL_L_Thigh = 0xe39f,
		SKEL_L_Calf = 0xf9bb,
		SKEL_L_Foot = 0x3779,
		SKEL_L_Toe0 = 0x83c,
		IK_L_Foot = 0xfedd,
		PH_L_Foot = 0xe175,
		MH_L_Knee = 0xb3fe,
		SKEL_R_Thigh = 0xca72,
		SKEL_R_Calf = 0x9000,
		SKEL_R_Foot = 0xcc4d,
		SKEL_R_Toe0 = 0x512d,
		IK_R_Foot = 0x8aae,
		PH_R_Foot = 0x60e6,
		MH_R_Knee = 0x3fcf,
		RB_L_ThighRoll = 0x5c57,
		RB_R_ThighRoll = 0x192a,
		SKEL_Spine_Root = 0xe0fd,
		SKEL_Spine0 = 0x5c01,
		SKEL_Spine1 = 0x60f0,
		SKEL_Spine2 = 0x60f1,
		SKEL_Spine3 = 0x60f2,
		SKEL_L_Clavicle = 0xfcd9,
		SKEL_L_UpperArm = 0xb1c5,
		SKEL_L_Forearm = 0xeeeb,
		SKEL_L_Hand = 0x49d9,
		SKEL_L_Finger00 = 0x67f2,
		SKEL_L_Finger01 = 0xff9,
		SKEL_L_Finger02 = 0xffa,
		SKEL_L_Finger10 = 0x67f3,
		SKEL_L_Finger11 = 0x1049,
		SKEL_L_Finger12 = 0x104a,
		SKEL_L_Finger20 = 0x67f4,
		SKEL_L_Finger21 = 0x1059,
		SKEL_L_Finger22 = 0x105a,
		SKEL_L_Finger30 = 0x67f5,
		SKEL_L_Finger31 = 0x1029,
		SKEL_L_Finger32 = 0x102a,
		SKEL_L_Finger40 = 0x67f6,
		SKEL_L_Finger41 = 0x1039,
		SKEL_L_Finger42 = 0x103a,
		PH_L_Hand = 0xeb95,
		IK_L_Hand = 0x8cbd,
		RB_L_ForeArmRoll = 0xee4f,
		RB_L_ArmRoll = 0x1470,
		MH_L_Elbow = 0x58b7,
		SKEL_R_Clavicle = 0x29d2,
		SKEL_R_UpperArm = 0x9d4d,
		SKEL_R_Forearm = 0x6e5c,
		SKEL_R_Hand = 0xdead,
		SKEL_R_Finger00 = 0xe5f2,
		SKEL_R_Finger01 = 0xfa10,
		SKEL_R_Finger02 = 0xfa11,
		SKEL_R_Finger10 = 0xe5f3,
		SKEL_R_Finger11 = 0xfa60,
		SKEL_R_Finger12 = 0xfa61,
		SKEL_R_Finger20 = 0xe5f4,
		SKEL_R_Finger21 = 0xfa70,
		SKEL_R_Finger22 = 0xfa71,
		SKEL_R_Finger30 = 0xe5f5,
		SKEL_R_Finger31 = 0xfa40,
		SKEL_R_Finger32 = 0xfa41,
		SKEL_R_Finger40 = 0xe5f6,
		SKEL_R_Finger41 = 0xfa50,
		SKEL_R_Finger42 = 0xfa51,
		PH_R_Hand = 0x6f06,
		IK_R_Hand = 0x188e,
		RB_R_ForeArmRoll = 0xab22,
		RB_R_ArmRoll = 0x90ff,
		MH_R_Elbow = 0xbb0,
		SKEL_Neck_1 = 0x9995,
		SKEL_Head = 0x796e,
		IK_Head = 0x322c,
		FACIAL_facialRoot = 0xfe2c,
		FB_L_Brow_Out_000 = 0xe3db,
		FB_L_Lid_Upper_000 = 0xb2b6,
		FB_L_Eye_000 = 0x62ac,
		FB_L_CheekBone_000 = 0x542e,
		FB_L_Lip_Corner_000 = 0x74ac,
		FB_R_Lid_Upper_000 = 0xaa10,
		FB_R_Eye_000 = 0x6b52,
		FB_R_CheekBone_000 = 0x4b88,
		FB_R_Brow_Out_000 = 0x54c,
		FB_R_Lip_Corner_000 = 0x2ba6,
		FB_Brow_Centre_000 = 0x9149,
		FB_UpperLipRoot_000 = 0x4ed2,
		FB_UpperLip_000 = 0xf18f,
		FB_L_Lip_Top_000 = 0x4f37,
		FB_R_Lip_Top_000 = 0x4537,
		FB_Jaw_000 = 0xb4a0,
		FB_LowerLipRoot_000 = 0x4324,
		FB_LowerLip_000 = 0x508f,
		FB_L_Lip_Bot_000 = 0xb93b,
		FB_R_Lip_Bot_000 = 0xc33b,
		FB_Tongue_000 = 0xb987,
		RB_Neck_1 = 0x8b93,
		IK_Root = 0xdd1c
	};

	void invisible(bool toggle) {

	}

	void drawBone(Ped ped, int firstBone, int secondBone, RGBA boneColor, RGBA boneColor2)
	{
		Vector3 tmpBneStrt = PED::GetPedBoneCoords(ped, firstBone, 0, 0, 0);
		Vector3 tmpBneEnd = PED::GetPedBoneCoords(ped, secondBone, 0, 0, 0);
		GRAPHICS::DrawLine(tmpBneStrt.x, tmpBneStrt.y, tmpBneStrt.z, tmpBneEnd.x, tmpBneEnd.y, tmpBneEnd.z, boneColor.R, boneColor.G, boneColor.B, boneColor.A);
		GRAPHICS::DrawBox(tmpBneStrt.x + 0.005f, tmpBneStrt.y + 0.005f, tmpBneStrt.z + 0.005f, tmpBneStrt.x - 0.005f, tmpBneStrt.y - 0.005f, tmpBneStrt.z - 0.005f, boneColor2.R, boneColor2.G, boneColor2.B, boneColor2.A);
	}

	void BonesShow(SPlayer & player, bool toggle) {

		Ped ESPPed = player.m_ped;

		if (player.m_id != GetLocalPlayer().m_id)ENTITY::SetEntityVisible(ESPPed, !toggle, !toggle);

		RGBA boneColornew = { vars.ESPColor.m_r, vars.ESPColor.m_g, vars.ESPColor.m_b, vars.ESPColor.m_a };
		RGBA boneColor2 = { vars.ESPColor.m_r, vars.ESPColor.m_g, vars.ESPColor.m_b, vars.ESPColor.m_a };

		//Foot to knee - right
		drawBone(ESPPed, SKEL_R_Foot, MH_R_Knee, boneColornew, boneColor2);

		//Toe to foot - right
		drawBone(ESPPed, SKEL_R_Toe0, SKEL_R_Foot, boneColornew, boneColor2);

		//Toe to foot - left
		drawBone(ESPPed, SKEL_L_Toe0, SKEL_L_Foot, boneColornew, boneColor2);

		//Foot to knee - left
		drawBone(ESPPed, SKEL_L_Foot, MH_L_Knee, boneColornew, boneColor2);

		//Knee to pelvis/hip - right
		drawBone(ESPPed, MH_R_Knee, SKEL_Pelvis, boneColornew, boneColor2);

		//Knee to pelvis/hip - left
		drawBone(ESPPed, MH_L_Knee, SKEL_Pelvis, boneColornew, boneColor2);

		//Pelvis/hip to Neck
		drawBone(ESPPed, SKEL_Pelvis, SKEL_Neck_1, boneColornew, boneColor2);

		//Neck to upper Arm - right
		drawBone(ESPPed, SKEL_Neck_1, SKEL_R_UpperArm, boneColornew, boneColor2);

		//Neck to upper Arm - left
		drawBone(ESPPed, SKEL_Neck_1, SKEL_L_UpperArm, boneColornew, boneColor2);

		//upper Arm to lower Arm - right
		drawBone(ESPPed, SKEL_R_UpperArm, SKEL_R_Forearm, boneColornew, boneColor2);

		//upper Arm to lower Arm - left
		drawBone(ESPPed, SKEL_L_UpperArm, SKEL_L_Forearm, boneColornew, boneColor2);

		//lower Arm to Hand - right
		drawBone(ESPPed, SKEL_R_Forearm, SKEL_R_Hand, boneColornew, boneColor2);

		//lower Arm to Hand - left
		drawBone(ESPPed, SKEL_L_Forearm, SKEL_L_Hand, boneColornew, boneColor2);

		//Neck to Head
		drawBone(ESPPed, SKEL_Neck_1, SKEL_Head, boneColornew, boneColor2);

		//Head
		Vector3 bone = PED::GetPedBoneCoords(ESPPed, IK_Head, 0, 0, 0);
		GRAPHICS::DrawBox(bone.x + 0.05f, bone.y + 0.05f, bone.z + 0.075f, bone.x - 0.05f, bone.y - 0.05f, bone.z - 0.05f, vars.ESPColor.m_r, vars.ESPColor.m_g, vars.ESPColor.m_b, vars.ESPColor.m_a);
	}

	void ESPBox(SPlayer& player) {
		RGBA color = { 0 ,255 ,0 ,180 };
		Vector3 handleCoords = ENTITY::GetOffsetFromEntityInWorldCoords(player.m_ped, 0, 0, 0);

		if (ENTITY::DoesEntityExist(player.m_ped)) {
			if (ENTITY::HasEntityClearLosToEntity(GetLocalPlayer().m_ped, player.m_ped, 1)) {
				GRAPHICS::DrawLine(handleCoords.x + 0.5f, handleCoords.y + 0.5f, handleCoords.z + 0.75f, handleCoords.x + 0.5f, handleCoords.y - 0.5f, handleCoords.z + 0.75f, vars.ESPColor.m_r, vars.ESPColor.m_g, vars.ESPColor.m_b, vars.ESPColor.m_a); // top Box
				GRAPHICS::DrawLine(handleCoords.x + 0.5f, handleCoords.y - 0.5f, handleCoords.z + 0.75f, handleCoords.x - 0.5f, handleCoords.y - 0.5f, handleCoords.z + 0.75f, vars.ESPColor.m_r, vars.ESPColor.m_g, vars.ESPColor.m_b, vars.ESPColor.m_a);
				GRAPHICS::DrawLine(handleCoords.x - 0.5f, handleCoords.y - 0.5f, handleCoords.z + 0.75f, handleCoords.x - 0.5f, handleCoords.y + 0.5f, handleCoords.z + 0.75f, vars.ESPColor.m_r, vars.ESPColor.m_g, vars.ESPColor.m_b, vars.ESPColor.m_a);
				GRAPHICS::DrawLine(handleCoords.x - 0.5f, handleCoords.y + 0.5f, handleCoords.z + 0.75f, handleCoords.x + 0.5f, handleCoords.y + 0.5f, handleCoords.z + 0.75f, vars.ESPColor.m_r, vars.ESPColor.m_g, vars.ESPColor.m_b, vars.ESPColor.m_a);
				GRAPHICS::DrawLine(handleCoords.x + 0.5f, handleCoords.y + 0.5f, handleCoords.z - 0.75f, handleCoords.x + 0.5f, handleCoords.y - 0.5f, handleCoords.z - 0.75f, vars.ESPColor.m_r, vars.ESPColor.m_g, vars.ESPColor.m_b, vars.ESPColor.m_a); // bottom
				GRAPHICS::DrawLine(handleCoords.x + 0.5f, handleCoords.y - 0.5f, handleCoords.z - 0.75f, handleCoords.x - 0.5f, handleCoords.y - 0.5f, handleCoords.z - 0.75f, vars.ESPColor.m_r, vars.ESPColor.m_g, vars.ESPColor.m_b, vars.ESPColor.m_a);
				GRAPHICS::DrawLine(handleCoords.x - 0.5f, handleCoords.y - 0.5f, handleCoords.z - 0.75f, handleCoords.x - 0.5f, handleCoords.y + 0.5f, handleCoords.z - 0.75f, vars.ESPColor.m_r, vars.ESPColor.m_g, vars.ESPColor.m_b, vars.ESPColor.m_a);
				GRAPHICS::DrawLine(handleCoords.x - 0.5f, handleCoords.y + 0.5f, handleCoords.z - 0.75f, handleCoords.x + 0.5f, handleCoords.y + 0.5f, handleCoords.z - 0.75f, vars.ESPColor.m_r, vars.ESPColor.m_g, vars.ESPColor.m_b, vars.ESPColor.m_a);
				GRAPHICS::DrawLine(handleCoords.x + 0.5f, handleCoords.y + 0.5f, handleCoords.z - 0.75f, handleCoords.x + 0.5f, handleCoords.y + 0.5f, handleCoords.z + 0.75f, vars.ESPColor.m_r, vars.ESPColor.m_g, vars.ESPColor.m_b, vars.ESPColor.m_a); // bottom
				GRAPHICS::DrawLine(handleCoords.x + 0.5f, handleCoords.y - 0.5f, handleCoords.z - 0.75f, handleCoords.x + 0.5f, handleCoords.y - 0.5f, handleCoords.z + 0.75f, vars.ESPColor.m_r, vars.ESPColor.m_g, vars.ESPColor.m_b, vars.ESPColor.m_a);
				GRAPHICS::DrawLine(handleCoords.x - 0.5f, handleCoords.y - 0.5f, handleCoords.z - 0.75f, handleCoords.x - 0.5f, handleCoords.y - 0.5f, handleCoords.z + 0.75f, vars.ESPColor.m_r, vars.ESPColor.m_g, vars.ESPColor.m_b, vars.ESPColor.m_a);
				GRAPHICS::DrawLine(handleCoords.x - 0.5f, handleCoords.y + 0.5f, handleCoords.z - 0.75f, handleCoords.x - 0.5f, handleCoords.y + 0.5f, handleCoords.z + 0.75f, vars.ESPColor.m_r, vars.ESPColor.m_g, vars.ESPColor.m_b, vars.ESPColor.m_a);
			}
		}
	}
}

void ESPMenu::Init() {
	setParentSubmenu<PlayerMenu>();
	setName("Extra sensory perception", true, false);

	addOption(ColorOption("ESP Color")
		.addColor(vars.ESPColor)
		.canBeSaved()
		.addTooltip("This will change all esp lines and boxes to match your chosen color").addTranslation());

	addOption(ToggleOption("ESP name")
		.addToggle(GetSelectedPlayer().m_nameESP).addTranslation()
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_nameESP); })
		.addTooltip("ESP name"));

	addOption(ToggleOption("ESP box")
		.addToggle(GetSelectedPlayer().m_boxESP).addTranslation()
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_boxESP); })
		.addTooltip("ESP line"));
	
	addOption(ToggleOption("ESP line")
		.addToggle(GetSelectedPlayer().m_lineESP).addTranslation()
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_lineESP); })
		.addTooltip("ESP line"));

	addOption(ToggleOption("ESP line of sight line")
		.addRequirement([] { return GetSelectedPlayer().m_lineESP; })
		.addToggle(GetSelectedPlayer().m_lineLOSESP).addTranslation()
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_lineLOSESP); })
		.addTooltip("This will highlight the ESP line when a player in line of sight of your ped"));

	addOption(ColorOption("ESP line of sight line color")
		.addRequirement([] { return GetSelectedPlayer().m_lineESP; })
		.addColor(vars.ESPLOSColor)
		.canBeSaved()
		.addTooltip("This will change the highlight color for the option above").addTranslation());

	addOption(ToggleOption("ESP head marker")
		.addToggle(GetSelectedPlayer().m_headMarkerESP).addTranslation()
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_headMarkerESP); })
		.addTooltip("ESP head marker"));
	
	addOption(ToggleOption("ESP foot marker")
		.addToggle(GetSelectedPlayer().m_footMarkerESP).addTranslation()
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_footMarkerESP); })
		.addTooltip("ESP foot marker"));

	addOption(ToggleOption("ESP info")
		.addToggle(GetSelectedPlayer().m_infoESP).addTranslation()
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_infoESP); })
		.addTooltip("ESP info"));

	addOption(ToggleOption("ESP skel")
		.addToggle(GetSelectedPlayer().m_bonesESP).addTranslation()
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_bonesESP); })
		.addTooltip("ESP skel"));

	addOption(ToggleOption("ESP sky line")
		.addToggle(GetSelectedPlayer().m_skylineESP).addTranslation()
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_skylineESP); })
		.addTooltip("ESP sky line"));
}

/*Update once when submenu is opened*/
void ESPMenu::UpdateOnce() {}

/*Update while submenu is active*/
void ESPMenu::Update() {}

/*Background update*/
void ESPMenu::FeatureUpdate() {
	OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_nameESP && !player.m_infoESP) NameESP(player); });
	OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_lineESP) LineESP(player); });
	OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_headMarkerESP) HeadMarkerESP(player); });
	OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_footMarkerESP) FootMarkerESP(player); });
	OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_infoESP) InfoESP(player); });
	OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_skylineESP) SkyLine(player); });
	OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_boxESP) ESPBox(player); });
	OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_bonesESP) BonesShow(player, true); });
}

/*Singleton*/
ESPMenu* _instance;
ESPMenu* ESPMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new ESPMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
ESPMenu::~ESPMenu() { delete _instance; }