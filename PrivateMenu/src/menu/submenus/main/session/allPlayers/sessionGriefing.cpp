#include "stdafx.h"
#include "sessionGriefing.h"
#include "../allPlayersMenu.h"
#include "../playerList/player/griefingMenu.h"
#include "sessionDisablesMenu.h"

using namespace SessionGriefingMenuVars;

namespace SessionGriefingMenuVars {
	Vars vars;

	struct EclipseTowerCageNew {
		int handle;
		Vector3_t coord;
		Vector3_t rot;
	};

	vector<EclipseTowerCageNew> EclipseTowerFences = {
		{ NULL,-775.32f,312.38f,84.70f,0.00f,-0.00f,-174.23f },
		{ NULL,-775.42f,312.26f,84.64f,0.00f,0.00f,4.68f },
		{ NULL,-772.48f,312.44f,84.64f,0.00f,-0.00f,0.00f },
		{ NULL,-769.67f,312.45f,84.61f,0.00f,0.00f,-90.00f },
		{ NULL,-769.67f,309.54f,84.59f,0.00f,0.00f,-87.75f },
		{ NULL,-769.55f,306.70f,84.59f,0.00f,0.00f,-89.25f },
		{ NULL,-769.49f,303.82f,84.57f,0.00f,-0.00f,-179.18f },
		{ NULL,-772.36f,303.75f,84.58f,0.00f,-0.00f,-178.65f },
		{ NULL,-775.17f,303.68f,84.57f,0.00f,-0.00f,177.88f },
		{ NULL,-778.04f,303.87f,84.62f,0.00f,0.00f,87.39f },
		{ NULL,-777.91f,306.78f,84.57f,0.00f,-0.00f,91.46f },
		{ NULL,-777.97f,309.50f,84.57f,0.00f,0.00f,64.97f },
	};

	void EclipseTower() {
		GetEntityControl()->SimpleRequestModel(0x466EB7B8);

		for (int i = 0; i < EclipseTowerFences.size(); i++) {
			EclipseTowerFences[i].handle = OBJECT::CreateObject(0x466EB7B8, EclipseTowerFences[i].coord.x, EclipseTowerFences[i].coord.y, EclipseTowerFences[i].coord.z, 1, 1, 0);

			while (!ENTITY::DoesEntityExist(EclipseTowerFences[i].handle)) WAIT(100);

			ENTITY::FreezeEntityPosition(EclipseTowerFences[i].handle, true);
			ENTITY::SetEntityCoords(EclipseTowerFences[i].handle, EclipseTowerFences[i].coord.x, EclipseTowerFences[i].coord.y, EclipseTowerFences[i].coord.z, 0, 0, 0, 1);
			ENTITY::SetEntityRotation(EclipseTowerFences[i].handle, EclipseTowerFences[i].rot.x, EclipseTowerFences[i].rot.y, EclipseTowerFences[i].rot.z, 0, 1);
		}

		OnlinePlayerCallback(false, [](SPlayer player) {
			if (player.m_id != GetLocalPlayer().m_id) {
				Natives::TriggerScriptEvent({ SCRIPTEVENTS::ECLIPSETELEPORT, player.m_id, 0, 0, 1, 1 }, 6, player.m_id);
			}
		});
	}
}

void SessionGriefingMenu::Init() {
	setParentSubmenu<AllPlayersMenu>();
	setName("Griefing", true, true);

	addOption(SubmenuOption("Disable actions")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addSubmenu<DisableActionsLobby>()
		.addTooltip("Disable session actions")
		.addRequirement([] { return GetAuth()->IsVIP(); }));

	addOption(ButtonOption("Eclipse tower teleport / trap")
		.addRequirement([] {return GetAuth()->IsVIP(); })
		.addFunction(EclipseTower)
		.addTooltip("Spawn a box and tp session there")
		.addTranslation().addHotkey());

	addOption(BreakOption("Troll").addTranslation());

	addOption(ButtonOption("Clone")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { GriefingMenuVars::ClonePlayer(player, false); }); })
		.addTooltip("Clone session").addTranslation().addHotkey());

	addOption(ToggleOption("Freeze in place")
		.addToggle(vars.disableTasks)
		.addTooltip("Freeze the player in place")
		.addTranslation().addHotkey());

	addOption(ButtonOption("Give wanted level")
		.addFunction([] {
		OnlinePlayerCallback(false, [](SPlayer player) { PLAYER::ReportCrime(player.m_id, 8, PLAYER::GetWantedLevelThreshold(5)); });
	})
		.addTooltip("Add wanted level").addTranslation().addHotkey());

	addOption(ToggleOption("Always wanted")
		.addToggle(vars.alwaysWanted)
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addTooltip("Make the session always wanted").addTranslation().addHotkey());

	addOption(ToggleOption("Electrocute session")
		.addToggle(vars.electrocutep)
		.addTooltip("This will electrocute the session")
		.addTranslation().addHotkey());

	addOption(ToggleOption("Make traffic hostile")
		.addToggle(vars.hostileTraffic)
		.addTooltip("Make traffic hostile").addTranslation().addHotkey());

	addOption(ToggleOption("Make pedestrians hostile")
		.addToggle(vars.hostilePeds)
		.addTooltip("Make pedestrians hostile").addTranslation().addHotkey());

	addOption(ToggleOption("Fake money")
		.addToggle(vars.fakeMoney)
		.addTooltip("Drop money bags with no value").addTranslation().addHotkey());

	addOption(BreakOption("Affect Ped Vision and Movement").addTranslation());

	addOption(ButtonOption("Trap in cage")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { GriefingMenuVars::CagePlayer(player); }); })
		.addTooltip("Trap in cage").addTranslation().addHotkey());

	addOption(ButtonOption("Trap in cable cars")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { GriefingMenuVars::TrapPlayer(player); }); })
		.addTooltip("Trap in a box of cable cars").addTranslation().addHotkey());

	addOption(ButtonOption("Glitch ped")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { GriefingMenuVars::GlitchPed(player); }); })
		.addTooltip("Glitch the sessions ped").addTranslation().addHotkey());

	addOption(ToggleOption("Shake camera")
		.addToggle(vars.shakeCamera)
		.addTooltip("Shake the sessions camera").addTranslation().addHotkey());

	addOption(ToggleOption("Smoke session")
		.addToggle(vars.smokePlayer)
		.addTooltip("Spawn loads of smoke on the session")
		.addTranslation().addHotkey());

	addOption(ToggleOption("Spray with water")
		.addToggle(vars.waterLoop)
		.addTooltip("Spray with water").addTranslation().addHotkey());

	addOption(ToggleOption("Spray with fire")
		.addToggle(vars.fireLoop)
		.addTooltip("Spray with fire").addTranslation().addHotkey());

	addOption(BreakOption("Deadly Force").addTranslation());

	addOption(ButtonOption("Host kick")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { GriefingMenuVars::Hostkick(player); }); })
		.addTooltip("Host kick session [Must be session host to use this on a session]").addTranslation().addHotkey());

	addOption(ButtonOption("Kill")
		.addFunction([] {
		OnlinePlayerCallback(false, [](SPlayer player) {
		Vector3 coords = player.m_coordinates;
		FIRE::AddExplosion(coords.x, coords.y, coords.z, 29, 100, false, true, 0.0f, false);
		FIRE::AddExplosion(coords.x, coords.y, coords.z - 1, 12, 0.5f, true, false, 0.0f, false);
		FIRE::AddExplosion(coords.x, coords.y, coords.z, 18, 0.25, false, true, 0, false);
		});
	})
		.addTooltip("Kill the session").addTranslation().addHotkey());

	addOption(ButtonOption("Silent kill")
		.addFunction([] {
		OnlinePlayerCallback(false, [](SPlayer player) {
			Vector3 coords = player.m_coordinates;
			Natives::AddOwnedExplosion(player.m_ped, coords.x, coords.y, coords.z, 38, 0.1f, false, false, 0.0f);
		});
	}).addTooltip("Peaceful kill").addTranslation().addHotkey());

	addOption(ToggleOption("Set on fire")
		.addToggle(vars.fire)
		.addFunction([] {
		if (!vars.fire) {
			OnlinePlayerCallback(false, [](SPlayer player) {
				GriefingMenuVars::SetOnFire(player, false);
			});
		}})
		.addTooltip("Spray with fire").addTranslation().addHotkey());

	addOption(ButtonOption("Ram with vehicle")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { GriefingMenuVars::RamWithVehicle(player); }); })
		.addTooltip("Ram session with vehicle").addTranslation().addHotkey());

	addOption(ButtonOption("Explode")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { GriefingMenuVars::Explode(player); }); })
		.addTooltip("Explode session").addTranslation().addHotkey());

	addOption(ToggleOption("Explode loop")
		.addToggle(vars.explode)
		.addTooltip("Kill session when they kill you").addTranslation().addHotkey());

	addOption(ToggleOption("Rain rockets")
		.addToggle(vars.rainRockets)
		.addTooltip("Rain rockets").addTranslation().addHotkey());

	addOption(ToggleOption("Forcefield")
		.addToggle(vars.forceField)
		.addTooltip("Forcefield").addTranslation().addHotkey());

	addOption(BreakOption("Attackers").addTranslation());

	addOption(NumberOption<int>(SCROLLSELECT, "Send attackers")
		.addNumber(vars.attackerCount, "%d", 1).addMin(1).addMax(20)
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { GriefingMenuVars::SendAttackers(player, vars.attackerCount); }); })
		.addTooltip("Send a custom amount of attackers to the session")
		.addTranslation().addHotkey());

	addOption(ButtonOption("Hostile clone")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { GriefingMenuVars::ClonePlayer(player, true); }); })
		.addTooltip("Hostile clone").addTranslation().addHotkey());

	addOption(ButtonOption("Attack with SWAT")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { GriefingMenuVars::SWATAttack(player); }); })
		.addTooltip("Attack with SWAT").addTranslation().addHotkey());

	addOption(ButtonOption("Attack with jet")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { GriefingMenuVars::JetAttack(player); }); })
		.addTooltip("Attack with jet").addTranslation().addHotkey());

	addOption(BreakOption("Misc").addTranslation());

	/*addOption(ButtonOption("Kick from vehicle")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { BRAIN::ClearPedTasksImmediately(player.m_ped); }); })
		.addTooltip("Kick the session from their vehicle")
		.addTranslation().addHotkey());*/

	addOption(ButtonOption("Airstrike")
		.addFunction([] { OnlinePlayerCallback(false, [](SPlayer player) { GriefingMenuVars::Airstrike(player); }); })
		.addTooltip("Airstrike attack session").addTranslation().addHotkey());

	addOption(ButtonOption("Ragdoll session")
		.addFunction([] {
		OnlinePlayerCallback(false, [](SPlayer player) {
		Vector3 coords = player.m_coordinates;
		FIRE::AddExplosion(coords.x, coords.y, coords.z - 0.2f, 4, 10.f, FALSE, TRUE, 0.f, false);
		});
	})
		.addTooltip("Ragdoll the session")
		.addTranslation().addHotkey());

	addOption(ButtonOption("Attach campfire")
		.addFunction([] {
		OnlinePlayerCallback(false, [](SPlayer player) {
		Vector3 coords = player.m_coordinates;
		Hash beachfire = Utils::GetHashKey("prop_beach_fire");
		GetEntityControl()->SimpleRequestModel(beachfire);
		int beachfirecre = OBJECT::CreateObject(beachfire, 0, 0, 0, true, 1, 0);
		ENTITY::AttachEntityToEntity(beachfirecre, player.m_ped, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 2, 1);
		});
	}).addTooltip("Attaches a campfire to players that will slowly kill").addTranslation());

	addOption(ToggleOption("Karma")
		.addToggle(vars.karma)
		.addTooltip("Kill session when they kill you").addTranslation().addHotkey());
}

/*Update once when submenu is opened*/
void SessionGriefingMenu::UpdateOnce() {}

/*Update while submenu is active*/
void SessionGriefingMenu::Update() {}

/*Background update*/
void SessionGriefingMenu::FeatureUpdate() {
	OnlinePlayerCallback(false, [](SPlayer player) { if (vars.disableTasks) GriefingMenuVars::FreezeInPlace(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (vars.smokePlayer) GriefingMenuVars::SmokePlayer(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (vars.alwaysWanted) GriefingMenuVars::AlwaysWanted(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (vars.explode) GriefingMenuVars::Explode(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (vars.karma) GriefingMenuVars::Karma(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (vars.waterLoop) GriefingMenuVars::WaterLoop(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (vars.fireLoop) GriefingMenuVars::FireLoop(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (vars.fire) GriefingMenuVars::SetOnFire(player, true); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (vars.hostileTraffic) GriefingMenuVars::HostileTraffic(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (vars.hostilePeds) GriefingMenuVars::HostilePeds(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (vars.rainRockets) GriefingMenuVars::RainRockets(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (vars.shakeCamera) GriefingMenuVars::ShakeCamera(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (vars.fakeMoney) GriefingMenuVars::FakeMoney(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (vars.forceField) GriefingMenuVars::Forcefield(player); });
	OnlinePlayerCallback(false, [](SPlayer player) { if (vars.electrocutep) GriefingMenuVars::Electrocute(player); });
}

/*Singleton*/
SessionGriefingMenu* _instance;
SessionGriefingMenu* SessionGriefingMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new SessionGriefingMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
SessionGriefingMenu::~SessionGriefingMenu() { delete _instance; }