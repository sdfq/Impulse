#include "stdafx.h"
#include "playerMenu.h"
#include "menu\submenus\main/sessionMenu.h"
#include "../playerListMenu.h"
#include "player/playerTeleportMenu.h"
#include "player/playerVehicleMenu.h"
#include "player/peacefulMenu.h"
#include "player/griefingMenu.h"
#include "player/remoteMenu.h"
#include "player/dropsMenu.h"
#include "player/ESPMenu.h"
#include "player/chatCommandMenu.h"
#include "player/spawn/playerSpawnVehicleMenu.h"
#include "player/blacklistPlayer.h"
#include "player/quickActions.h"

using namespace PlayerMenuVars;

namespace PlayerMenuVars {
	Vars vars;
	int player;

	void Spectate(SPlayer player, bool toggle) {
		GetFiberPool()->DoJob([=] {
			if (!CAM::IsScreenFadedOut()) {
				if (!CAM::IsScreenFadingOut()) {
					CAM::DoScreenFadeOut(200);
					while (!CAM::IsScreenFadingOut()) GetFiberManager()->GoToMainFiber();
					NETWORK::NetworkSetInSpectatorMode(toggle, player.m_ped);
					if (CAM::IsScreenFadingOut()) CAM::DoScreenFadeIn(200);
				}
			}
		});
	}

	int netHandle[13];
	void ShowProfile(SPlayer& player) {
		NETWORK::NetworkHandleFromPlayer(player.m_id, &*netHandle, 13);
		NETWORK::NetworkShowProfileUi(netHandle);
	}


	/*void SendFR(SPlayer& player) {
		NETWORK::NetworkAddFriend(NULL, player.m_name);
	}*/

	void SpectateZoom() {
		if (vars.spectating) {
			CAM::_AnimateGameplayCamZoom(1.0f, vars.spectatezoom);
		}
	}

	void CloseSpectate() {
		if (vars.spectating) {
			vars.spectating = false;
			Spectate(GetPlayer(0), false);
		}
	}

	/*const char* GetNameFromHandle(int player) {
		int handle[13];
		NETWORK::NetworkHandleFromPlayer(player, handle, 13);

		NETWORK::NetworkGamertagFromHandleStart(handle);
		return NETWORK::NetworkGetGamertagFromHandle(handle);
	}*/
}

void PlayerMenu::Init() {
	setParentSubmenu<PlayerListMenu>();
	setName("Player", true, false);

	addOption(ToggleOption("Spectate player")
		.addToggle(vars.spectating).addTranslation()
		.addFunction([] { Spectate(GetSelectedPlayer(), vars.spectating); GetRenderer()->NotifyBottom(va("Spectating: ~r~%s", GetSelectedPlayer().m_name)); })
		.addTooltip("Spectate player")
		.addRequirement([] { return !GetSelectedPlayer().m_isEvolveUserBlock || SessionMenuVars::vars.bypassevoblock; }));

	addOption(NumberOption<int>(TOGGLE, "Spectate distance")
		.addToggle(vars.specatezoomtog)
		.addNumber(vars.spectatezoom, "%i", 1).addMin(1).addMax(250).setScrollSpeed(5)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Spectate zoom distance")
		.addRequirement([] { return !GetSelectedPlayer().m_isEvolveUserBlock || SessionMenuVars::vars.bypassevoblock; }));

	addOption(SubmenuOption("Quick actions")
		.addSubmenu<QuickActionsMenu>().addTranslation()
		.addTooltip("Quick actions for quick reactions")
		.addRequirement([] { return !GetSelectedPlayer().m_isEvolveUserBlock || SessionMenuVars::vars.bypassevoblock; }));

	addOption(SubmenuOption("Teleport")
		.addSubmenu<PlayerTeleportMenu>().addTranslation()
		.addTooltip("Teleport player options")
		.addRequirement([] { return !GetSelectedPlayer().m_isEvolveUserBlock || SessionMenuVars::vars.bypassevoblock; }));

	addOption(SubmenuOption("Peaceful")
		.addSubmenu<PeacefulMenu>().addTranslation()
		.addTooltip("Peaceful player options")
		.addRequirement([] { return !GetSelectedPlayer().m_isEvolveUserBlock || SessionMenuVars::vars.bypassevoblock; }));

	addOption(SubmenuOption("Griefing")
		.addSubmenu<GriefingMenu>().addTranslation()
		.addTooltip("Grief player options")
		.addRequirement([] { return !GetSelectedPlayer().m_isEvolveUserBlock || SessionMenuVars::vars.bypassevoblock; }));

	addOption(SubmenuOption("Vehicle")
		.addSubmenu<PlayerVehicleMenu>().addTranslation()
		.addTooltip("Player vehicle options")
		.addRequirement([] { return !GetSelectedPlayer().m_isEvolveUserBlock || SessionMenuVars::vars.bypassevoblock; }));

	addOption(SubmenuOption("Spawn")
		.addSubmenu<PlayerSpawnVehicleMenu>().addTranslation()
		.addTooltip("Spawn vehicle options")
		.addRequirement([] { return !GetSelectedPlayer().m_isEvolveUserBlock || SessionMenuVars::vars.bypassevoblock; }));

	addOption(SubmenuOption("Remote")
		.addSubmenu<RemoteMenu>().addTranslation()
		.addTooltip("Remote player options")
		.addRequirement([] { return !GetSelectedPlayer().m_isEvolveUserBlock || SessionMenuVars::vars.bypassevoblock; }));

	addOption(SubmenuOption("Drops")
		.addSubmenu<DropsMenu>().addTranslation()
		.addTooltip("Drops options")
		.addRequirement([] { return !GetSelectedPlayer().m_isEvolveUserBlock || SessionMenuVars::vars.bypassevoblock; }));

	addOption(SubmenuOption("Extra sensory perception")
		.addSubmenu<ESPMenu>().addTranslation()
		.addTooltip("Extra sensory perception player options"));

	addOption(SubmenuOption("Chat commands")
		.addSubmenu<ChatCommandMenu>().addTranslation()
		.addTooltip("Chat command options")
		.addRequirement([] { return GetSelectedPlayer().m_id != GetLocalPlayer().m_id && !GetSelectedPlayer().m_isEvolveUserBlock && GetAuth()->IsVIP() || SessionMenuVars::vars.bypassevoblock; }));

	addOption(SubmenuOption("Overseer")
		.addSubmenu<BlacklistMenu>().addTranslation()
		.addTooltip("Choose to add the player to the session overseer")
		.addRequirement([] { return GetSelectedPlayer().m_id != GetLocalPlayer().m_id && !GetSelectedPlayer().m_isEvolveUserBlock || SessionMenuVars::vars.bypassevoblock; }));

	addOption(BreakOption()
		.addRequirement([] { return !GetSelectedPlayer().m_isEvolveUserBlock || SessionMenuVars::vars.bypassevoblock; }));

	//addOption(ButtonOption("Parachute to player")
	//	.addFunction([] {
	//		Vector3 rot = ENTITY::GetEntityRotation(GetSelectedPlayer().m_ped, 1);
	//		ENTITY::SetEntityCoords(GetLocalPlayer().m_ped, GetSelectedPlayer().m_coordinates.x + MISC::GetRandomFloatInRange(5.0f, 15.0f), GetSelectedPlayer().m_coordinates.y + MISC::GetRandomFloatInRange(5.0f, 15.0f), GetSelectedPlayer().m_coordinates.z + MISC::GetRandomFloatInRange(5.0f, 15.0f), 0, 0, 0, 0);
	//		ENTITY::SetEntityRotation(GetLocalPlayer().m_ped, rot.x, rot.y, rot.z, 1, 1);
	//		//BRAIN::TaskParachuteToTarget(GetSelectedPlayer().m_ped, GetSelectedPlayer().m_coordinates.x, GetSelectedPlayer().m_coordinates.y, GetSelectedPlayer().m_coordinates.z);
	//		BRAIN::TaskParachute(GetSelectedPlayer().m_ped, true, 1);
	//	})
	//	.addTooltip("Parachute to the player").addTranslation());

	addOption(ButtonOption("Open player log window")
		.addFunction([] {GetWindowManager()->OpenPlayerLog(GetSelectedPlayer()); })
		.addTooltip("Open player log window").addTranslation()
		.addRequirement([] { return !GetSelectedPlayer().m_isEvolveUserBlock || SessionMenuVars::vars.bypassevoblock; }));

	addOption(ButtonOption("Open player info window")
		.addFunction([] {GetWindowManager()->OpenPlayerInfo(GetSelectedPlayer()); })
		.addTooltip("Open player info window").addTranslation()
		.addRequirement([] { return !GetSelectedPlayer().m_isEvolveUserBlock || SessionMenuVars::vars.bypassevoblock; }));

	addOption(ButtonOption("Show profile")
		.addFunction([] { ShowProfile(GetSelectedPlayer()); })
		.addTooltip("Open player social club profile ui").addTranslation()
		.addRequirement([] { return !GetSelectedPlayer().m_isEvolveUserBlock || SessionMenuVars::vars.bypassevoblock; }));

	addOption(ButtonOption("Send friend request")
		.addFunction([] {
		int Handle[13];
		NETWORK::NetworkHandleFromPlayer(GetSelectedPlayer().m_id, &Handle[0], 13);
		string msg;
		if (GetMenuInput()->Text("Request message", msg, 2, 40)) {
			NETWORK::NetworkAddFriend(Handle, msg.c_str());
		} else {
			NETWORK::NetworkAddFriend(Handle, ".");
		}
	})
		.addTooltip("Add the person as a friend on your social club account")
		.addTranslation()
		.addRequirement([] { return GetSelectedPlayer().m_id != GetLocalPlayer().m_id && !GetSelectedPlayer().m_isEvolveUserBlock || SessionMenuVars::vars.bypassevoblock; }));


#ifdef HARD_DEV
	addOption(ButtonOption("Developer Crash").addRequirement([] { return GetAuth()->IsDev(); /* in case some autistic idiot removes the ifdef */ }).addTranslation().addFunction([] {
		const auto pos = ENTITY::GetEntityCoords(GetSelectedPlayer().m_ped, !ENTITY::IsEntityDead(GetSelectedPlayer().m_ped, 0));
		PED::CreatePed(26, 0x3F039CBA, pos.x, pos.y, pos.z, 0.0f, true, true);
	}).addHotkey().addTooltip("Crashes the player."));

	/*addOption(ButtonOption("test nigger")
		.addFunction([] {
			LOG_PRINT("PENIS: %s", GetNameFromHandle(GetSelectedPlayer().m_id));
		}));*/
#endif
}

/*Update once when submenu is opened*/
void PlayerMenu::UpdateOnce() {}

/*Update while submenu is active*/
void PlayerMenu::Update() {}

/*Background update*/
void PlayerMenu::FeatureUpdate() {
	if (vars.specatezoomtog) SpectateZoom();

	if (SessionMenuVars::vars.showmarkeronselectedbydefault && SessionMenuVars::vars.markertypeselector == 1) {
		//if (GetMenu()->IsOpen()
		GRAPHICS::DrawMarker(21, GetSelectedPlayer().m_coordinates.x, GetSelectedPlayer().m_coordinates.y, GetSelectedPlayer().m_coordinates.z + 1.5f, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f, 0.0f, 0.9f, 0.9f, 0.9f, 255, 0, 0, 150, true, false, 2, true, nullptr, nullptr, false);
	}
}

/*Singleton*/
PlayerMenu* _instance;
PlayerMenu* PlayerMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new PlayerMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
PlayerMenu::~PlayerMenu() { delete _instance; }