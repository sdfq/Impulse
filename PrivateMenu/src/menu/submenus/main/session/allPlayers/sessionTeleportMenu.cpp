#include "stdafx.h"
#include "sessionTeleportMenu.h"
#include "../allPlayersMenu.h"
#include "../playerList/player/playerTeleportMenu.h"

using namespace SessionTeleportMenuVars;

namespace SessionTeleportMenuVars {
	Vars vars;

	void TeleportPlayersVehicleToMe(SPlayer& player) {
		if (player.m_exists) {
			Ped ped = player.m_ped;
			Vector3 coords = GetLocalPlayer().m_coordinates;
			if (player.m_isInVehicle) {
				GetEntityControl()->RequestControl("[TPV]", player.m_vehicle, [=](Entity entity) {ENTITY::SetEntityCoords(entity, coords.x, coords.y, coords.z, 0, 0, 0, 1); });
			}
		}
	}

	void TeleportPlayersToApartment(SPlayer& player, int id) {
		Natives::TriggerScriptEvent({ SCRIPTEVENTS::ECLIPSETELEPORT, player.m_id, 0, 0, id, id }, 6, player.m_id);
	}

	void TeleportClosestVehicleToPlayer(SPlayer& player) {
		Entity entity = VEHICLE::GetClosestVehicle(player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 600.0f, 0, 0);
		if (ENTITY::DoesEntityExist(entity)) {
			GetEntityControl()->RequestControl("[TPCV]", entity, [=](Entity entity) {ENTITY::SetEntityCoords(entity, player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 0, 0, 0, 1); });
		}
	}
}

void SessionTeleportMenu::Init() {
	setParentSubmenu<AllPlayersMenu>();
	setName("Teleport", true, true);

	addOption(ButtonOption("Teleport all players vehicle to me")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { if (player.m_id != GetLocalPlayer().m_id) TeleportPlayersVehicleToMe(player); }); })
		.addTooltip("Teleport all players vehicle to me").addTranslation().addHotkey());

	addOption(ButtonOption("Teleport nearest vehicle to all players")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { TeleportClosestVehicleToPlayer(player); }); })
		.addTooltip("Teleport the nearest vehicle to the player to the player")
		.addTranslation().addHotkey());

	addOption(BreakOption("Apartments"));

	for (auto& ap : PlayerTeleportMenuVars::apartments) {
		addOption(ButtonOption(NetEvent::GetTeleportLocation(ap.m_id))
			.addFunction([&] { OnlinePlayerCallback(false, [&](SPlayer player) {Natives::TriggerScriptEvent({ SCRIPTEVENTS::ECLIPSETELEPORT, player.m_id, 0, 0, ap.m_id, ap.m_id }, 6, player.m_id); }); })
			.addTooltip("Teleport session to apartment"));
	}
}

/*Update once when submenu is opened*/
void SessionTeleportMenu::UpdateOnce() {}

/*Update while submenu is active*/
void SessionTeleportMenu::Update() {}

/*Background update*/
void SessionTeleportMenu::FeatureUpdate() {}

/*Singleton*/
SessionTeleportMenu* _instance;
SessionTeleportMenu* SessionTeleportMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new SessionTeleportMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
SessionTeleportMenu::~SessionTeleportMenu() { delete _instance; }