#include "stdafx.h"
#include "chatCommandMenu.h"
#include "../playerMenu.h"
#include "peacefulMenu.h"
#include "../../../spawn/spawnObjectMenu.h"
#include "../../../spawn/spawnPedMenu.h"
#include "../../../spawn/spawnVehicleMenu.h"
#include "../../../vehicle/LSCMenu.h"
#include "../../allPlayersMenu.h"

using namespace ChatCommandMenuVars;

namespace ChatCommandMenuVars {
	Vars vars;

	void HandleCommand(int id, string message) {
		bool lobby = AllPlayersMenuVars::vars.chat;
		SPlayer& player = GetPlayer(id);

		istringstream buf(message);
		istream_iterator<string> beg(buf), end;
		vector<string> tokens(beg, end);

		if (tokens.size() == 0) return;

		if (tokens[0].at(0) == '!' && (player.m_chatCommand || lobby)) {
			if (!tokens[0].compare("!money") && tokens.size() >= 2 && (player.m_chatCommandMoneyDrop || lobby)) {
				if (!tokens[1].compare("on")) {
					GetRenderer()->NotifyMapColor(va("Chat Commands\nMoney Drop: On\nFrom: %s", player.m_name), 18);
					player.m_standardMoneyDrop = true;
				} else if (!tokens[1].compare("off")) {
					GetRenderer()->NotifyMapColor(va("Chat Commands\nMoney Drop: Off\nFrom: %s", player.m_name), 18);
					player.m_standardMoneyDrop = false;
				}
			}

			if (!tokens[0].compare("!spawn") && tokens.size() >= 2) {
				if (!tokens[1].compare("vehicle") && (player.m_chatCommandSpawnVehicle || lobby)) {
					if (tokens.size() > 2) {
						GetRenderer()->NotifyMapColor(va("Chat Commands\nSpawn Vehicle\nFrom: %s", player.m_name), 18);
						Hash hash = Utils::GetJenkinsHashFromString((char*)tokens[2].c_str());
						SpawnVehicleMenuVars::SpawnVehiclePlayer(hash, id, 0);
					}
				} else if (!tokens[1].compare("ped") && (player.m_chatCommandSpawnPed || lobby)) {
					if (tokens.size() > 2) {
						GetRenderer()->NotifyMapColor(va("Chat Commands\nSpawn Ped\nFrom: %s", player.m_name), 18);
						Hash hash = Utils::GetJenkinsHashFromString((char*)tokens[2].c_str());
						SpawnPedMenuVars::SpawnPedPlayer(hash, id);
					}
				} else if (!tokens[1].compare("object") && (player.m_chatCommandSpawnObject || lobby)) {
					if (tokens.size() > 2) {
						GetRenderer()->NotifyMapColor(va("Chat Commands\nSpawn Object\nFrom: %s", player.m_name), 18);
						Hash hash = Utils::GetJenkinsHashFromString((char*)tokens[2].c_str());
						SpawnObjectMenuVars::SpawnObjectPlayer(hash, id);
					}
				} else if (!tokens[1].compare("bodyguard") && (player.m_chatCommandSpawnBodyguard || lobby)) {
					GetRenderer()->NotifyMapColor(va("Chat Commands\nSpawn Bodyguard\nFrom: %s", player.m_name), 18);
					if (tokens.size() > 2) {
						int count = atoi((char*)tokens[2].c_str());
						if (count > 10)count = 10;
						for (int i = 0; i < count; i++) PeacefulMenuVars::SpawnCloneBodyguard(player);
					} else {
						PeacefulMenuVars::SpawnCloneBodyguard(player);
					}
				}
			}

			if (!tokens[0].compare("!weapons") && (player.m_chatCommandGiveWeapons || lobby)) {
				GetRenderer()->NotifyMapColor(va("Chat Commands\nGiving Weapons\nFrom: %s", player.m_name), 18);
				PeacefulMenuVars::GiveAllWeapons(player);
			}

			if (!tokens[0].compare("!explodesession") && (player.m_chatCommandExplodeSession || lobby)) {
				GetRenderer()->NotifyMapColor(va("Chat Commands\nExploding Session\nFrom: %s", player.m_name), 18);
				OnlinePlayerCallback(false, [](SPlayer player) {
					FIRE::AddExplosion(player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 2, 1000, true, false, 0.0f, false);
				});
			}

			if (!tokens[0].compare("!vehicle") && tokens.size() >= 2) {
				if (player.m_isInVehicle) {
					if (!tokens[1].compare("repair") && (player.m_chatCommandVehicleRepair || lobby)) {
						GetRenderer()->NotifyMapColor(va("Chat Commands\nVehicle Repair\nFrom: %s", player.m_name), 18);
						GetEntityControl()->RequestControl("[RPV]", player.m_vehicle, [](Entity vehicle) {VEHICLE::SetVehicleFixed(vehicle); });
					} else if (!tokens[1].compare("boost") && (player.m_chatCommandVehicleBoost || lobby)) {
						GetRenderer()->NotifyMapColor(va("Chat Commands\nVehicle Boost\nFrom: %s", player.m_name), 18);
						GetEntityControl()->RequestControl("[BPV]", player.m_vehicle, [](Entity vehicle) {VEHICLE::SetVehicleForwardSpeed(vehicle, 100); });
					} else if (!tokens[1].compare("jump") && (player.m_chatCommandVehicleJump || lobby)) {
						GetRenderer()->NotifyMapColor(va("Chat Commands\nVehicle Jump\nFrom: %s", player.m_name), 18);
						GetEntityControl()->RequestControl("[JPV]", player.m_vehicle, [](Entity vehicle) {Utils::ApplyForceToEntity(vehicle, 0, 0, 20); });
					} else if (!tokens[1].compare("upgrade") && (player.m_chatCommandVehicleUpgrade || lobby)) {
						GetRenderer()->NotifyMapColor(va("Chat Commands\nVehicle Upgrade\nFrom: %s", player.m_name), 18);
						GetEntityControl()->RequestControl("[JPV]", player.m_vehicle, [](Entity vehicle) {LSCMenuVars::MaxVehicle(vehicle); });
					}
				}
			}

			if (!tokens[0].compare("!copsturnblind") && tokens.size() >= 2 && (player.m_chatCommandGlobalsCopsturnblind || lobby)) {
				if (!tokens[1].compare("on")) {
					GetRenderer()->NotifyMapColor(va("Chat Commands\nCopsTurnBlindEye: On\nFrom: %s", player.m_name), 18);
					player.m_blindEye = true;
				} else if (!tokens[1].compare("off")) {
					GetRenderer()->NotifyMapColor(va("Chat Commands\nCopsTurnBlindEye: Off\nFrom: %s", player.m_name), 18);
					player.m_blindEye = false;
				}
			}

			if (!tokens[0].compare("!offtheradar") && tokens.size() >= 2 && (player.m_chatCommandGlobalsOfftheradar || lobby)) {
				if (!tokens[1].compare("on")) {
					GetRenderer()->NotifyMapColor(va("Chat Commands\nOffTheRadar: On\nFrom: %s", player.m_name), 18);
					player.m_otr = true;
				} else if (!tokens[1].compare("off")) {
					GetRenderer()->NotifyMapColor(va("Chat Commands\nOffTheRadar: Off\nFrom: %s", player.m_name), 18);
					player.m_otr = false;
				}
			}

			if (!tokens[0].compare("!weather") && tokens.size() >= 2) {
					if (!tokens[1].compare("day") && (player.m_chatCommandWeatherDay || lobby)) {
						GetRenderer()->NotifyMapColor(va("Chat Commands\nWeather Day\nFrom: %s", player.m_name), 18);
						NETWORK::NetworkOverrideClockTime(12, CLOCK::GetClockMinutes(), CLOCK::GetClockSeconds());
						Natives::SyncLobbyTimeWithMyTime();
					} else if (!tokens[1].compare("night") && (player.m_chatCommandWeatherNight || lobby)) {
						GetRenderer()->NotifyMapColor(va("Chat Commands\nWeather Night\nFrom: %s", player.m_name), 18);
						NETWORK::NetworkOverrideClockTime(0, CLOCK::GetClockMinutes(), CLOCK::GetClockSeconds());
						Natives::SyncLobbyTimeWithMyTime();
					} else if (!tokens[1].compare("snow") && (player.m_chatCommandWeatherSnow || lobby)) {
						GetRenderer()->NotifyMapColor(va("Chat Commands\nWeather Snow\nFrom: %s", player.m_name), 18);
						Natives::SetLobbyWeather("XMAS");
					} else if (!tokens[1].compare("clear") && (player.m_chatCommandWeatherClear || lobby)) {
						GetRenderer()->NotifyMapColor(va("Chat Commands\nWeather Clear\nFrom: %s", player.m_name), 18);
						Natives::SetLobbyWeather("CLEAR");
					} else if (!tokens[1].compare("halloween") && (player.m_chatCommandWeatherHalloween || lobby)) {
						GetRenderer()->NotifyMapColor(va("Chat Commands\nWeather Halloween\nFrom: %s", player.m_name), 18);
						Natives::SetLobbyWeather("HALLOWEEN");
					}
				}
			}
		}

	void ToggleAll(SPlayer& player, bool toggle) {
		player.m_chatCommand = toggle;
		player.m_chatCommandMoneyDrop = toggle;
		player.m_chatCommandSpawnVehicle = toggle;
		player.m_chatCommandSpawnPed = toggle;
		player.m_chatCommandSpawnObject = toggle;
		player.m_chatCommandSpawnBodyguard = toggle;
		player.m_chatCommandGiveWeapons = toggle;
		player.m_chatCommandExplodeSession = toggle;
		player.m_chatCommandVehicleRepair = toggle;
		player.m_chatCommandVehicleBoost = toggle;
		player.m_chatCommandVehicleJump = toggle;
		player.m_chatCommandWeatherDay = toggle;
		player.m_chatCommandWeatherNight = toggle;
		player.m_chatCommandWeatherSnow = toggle;
		player.m_chatCommandWeatherClear = toggle;
		player.m_chatCommandWeatherHalloween = toggle;
		player.m_chatCommandVehicleUpgrade = toggle;
		player.m_chatCommandGlobalsCopsturnblind = toggle;
		player.m_chatCommandGlobalsOfftheradar = toggle;
	}
}

void ChatCommandMenu::Init() {
	setParentSubmenu<PlayerMenu>();
	setName("Chat commands", true, false);

	addOption(ButtonOption("Toggle all commands on")
		.addFunction([] {ToggleAll(GetSelectedPlayer(), true); })
		.addTranslation().addTooltip("Enable all command options for this player"));

	addOption(ButtonOption("Toggle all commands off")
		.addFunction([] {ToggleAll(GetSelectedPlayer(), false); })
		.addTranslation().addTooltip("Disable all command options for this player"));

	addOption(BreakOption());

	addOption(ToggleOption("Enable chat commands for player")
		.addToggle(GetSelectedPlayer().m_chatCommand)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_chatCommand); })
		.addTranslation().addTooltip("Enable chat commands for player"));

	addOption(BreakOption("General commands").addTranslation());

	addOption(ToggleOption("Chat command money drop")
		.addToggle(GetSelectedPlayer().m_chatCommandMoneyDrop)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_chatCommandMoneyDrop); })
		.addTranslation().addTooltip("Chat command money drop:\n!money <on/off>"));

	addOption(ToggleOption("Chat command spawn vehicle")
		.addToggle(GetSelectedPlayer().m_chatCommandSpawnVehicle)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_chatCommandSpawnVehicle); })
		.addTranslation().addTooltip("Chat command spawn vehicle:\n!spawn vehicle <hash/model name>"));

	addOption(ToggleOption("Chat command spawn ped")
		.addToggle(GetSelectedPlayer().m_chatCommandSpawnPed)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_chatCommandSpawnPed); })
		.addTranslation().addTooltip("Chat command spawn ped:\n!spawn ped <hash/model name>"));

	addOption(ToggleOption("Chat command spawn object")
		.addToggle(GetSelectedPlayer().m_chatCommandSpawnObject)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_chatCommandSpawnObject); })
		.addTranslation().addTooltip("Chat command spawn object:\n!spawn object <hash/model name>"));

	addOption(ToggleOption("Chat command spawn bodyguard")
		.addToggle(GetSelectedPlayer().m_chatCommandSpawnBodyguard)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_chatCommandSpawnBodyguard); })
		.addTranslation().addTooltip("Chat command spawn bodyguard:\n!spawn bodyguard <count>"));

	addOption(ToggleOption("Chat command give weapons")
		.addToggle(GetSelectedPlayer().m_chatCommandGiveWeapons)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_chatCommandGiveWeapons); })
		.addTranslation().addTooltip("Chat command give weapons:\n!weapons"));

	addOption(ToggleOption("Chat command explode session")
		.addToggle(GetSelectedPlayer().m_chatCommandExplodeSession)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_chatCommandExplodeSession); })
		.addTranslation().addTooltip("Chat command explode session:\n!explodesession"));

	addOption(BreakOption("Vehicle commands (close-by)").addTranslation());

	addOption(ToggleOption("Chat command vehicle repair")
		.addToggle(GetSelectedPlayer().m_chatCommandVehicleRepair)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_chatCommandVehicleRepair); })
		.addTranslation().addTooltip("Chat command vehicle repair:\n!vehicle repair"));

	addOption(ToggleOption("Chat command vehicle boost")
		.addToggle(GetSelectedPlayer().m_chatCommandVehicleBoost)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_chatCommandVehicleBoost); })
		.addTranslation().addTooltip("Chat command vehicle boost:\n!vehicle boost"));

	addOption(ToggleOption("Chat command vehicle jump")
		.addToggle(GetSelectedPlayer().m_chatCommandVehicleJump)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_chatCommandVehicleJump); })
		.addTranslation().addTooltip("Chat command vehicle jump:\n!vehicle jump"));

	addOption(ToggleOption("Chat command vehicle upgrade")
		.addToggle(GetSelectedPlayer().m_chatCommandVehicleUpgrade)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_chatCommandVehicleUpgrade); })
		.addTranslation().addTooltip("Chat command vehicle upgrade:\n!vehicle upgrade"));

	addOption(BreakOption("Give global commands").addTranslation());

	addOption(ToggleOption("Chat command cops turn blind eye")
		.addToggle(GetSelectedPlayer().m_chatCommandGlobalsCopsturnblind)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_chatCommandGlobalsCopsturnblind); })
		.addTranslation().addTooltip("Chat command cops turn blind eye:\n!copsturnblind on/off"));

	addOption(ToggleOption("Chat command off the radar")
		.addToggle(GetSelectedPlayer().m_chatCommandGlobalsOfftheradar)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_chatCommandGlobalsOfftheradar); })
		.addTranslation().addTooltip("Chat command off the radar:\n!offtheradar on/off"));

	addOption(BreakOption("Weather/time commands").addTranslation());

	addOption(ToggleOption("Chat command weather day")
		.addToggle(GetSelectedPlayer().m_chatCommandWeatherDay)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_chatCommandWeatherDay); })
		.addTranslation().addTooltip("Chat command weather day:\n!weather day"));

	addOption(ToggleOption("Chat command weather night")
		.addToggle(GetSelectedPlayer().m_chatCommandWeatherNight)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_chatCommandWeatherNight); })
		.addTranslation().addTooltip("Chat command weather night:\n!weather night"));

	addOption(ToggleOption("Chat command weather clear")
		.addToggle(GetSelectedPlayer().m_chatCommandWeatherClear)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_chatCommandWeatherClear); })
		.addTranslation().addTooltip("Chat command weather clear:\n!weather clear"));

	addOption(ToggleOption("Chat command weather snow")
		.addToggle(GetSelectedPlayer().m_chatCommandWeatherSnow)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_chatCommandWeatherSnow); })
		.addTranslation().addTooltip("Chat command weather snow:\n!weather snow"));

	addOption(ToggleOption("Chat command weather halloween")
		.addToggle(GetSelectedPlayer().m_chatCommandWeatherHalloween)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_chatCommandWeatherHalloween); })
		.addTranslation().addTooltip("Chat command weather halloween:\n!weather halloween"));

}

/*Update once when submenu is opened*/
void ChatCommandMenu::UpdateOnce() {}

/*Update while submenu is active*/
void ChatCommandMenu::Update() {}

/*Background update*/
void ChatCommandMenu::FeatureUpdate() {}

/*Singleton*/
ChatCommandMenu* _instance;
ChatCommandMenu* ChatCommandMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new ChatCommandMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
ChatCommandMenu::~ChatCommandMenu() { delete _instance; }