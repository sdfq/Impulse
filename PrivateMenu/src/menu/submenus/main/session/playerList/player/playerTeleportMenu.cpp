#include "stdafx.h"
#include "playerTeleportMenu.h"
#include "../playerMenu.h"

using namespace PlayerTeleportMenuVars;

namespace PlayerTeleportMenuVars {
	int range = 10;

	void TeleportToPlayer(SPlayer& player) {
		Vector3 coords = player.m_coordinates;
		if (GetLocalPlayer().m_isInVehicle) ENTITY::SetEntityCoords(GetLocalPlayer().m_vehicle, coords.x, coords.y, coords.z, 0, 0, 0, 1);
		else ENTITY::SetEntityCoords(GetLocalPlayer().m_ped, coords.x, coords.y, coords.z, 0, 0, 0, 1);
	}

	void TeleportInPlayersVehicle(SPlayer& player) {
		if (player.m_isInVehicle) {
			PED::SetPedIntoVehicle(GetLocalPlayer().m_ped, player.m_vehicle, Utils::GetFreeSeat(player.m_vehicle));
		} else GetRenderer()->NotifyBottom(va("%s is not in a vehicle", player.m_name));
	}

	void TeleportPlayersVehicleToMe(SPlayer& player) {
		Ped ped = player.m_ped;
		Vector3 coords = GetLocalPlayer().m_coordinates;
		if (player.m_isInVehicle) {
			GetEntityControl()->RequestControl("[TPV]", player.m_vehicle, [=](Entity entity) {ENTITY::SetEntityCoords(entity, coords.x, coords.y, coords.z, 0, 0, 0, 1); });
		} else GetRenderer()->NotifyBottom(va("%s is not in a vehicle", player.m_name));
	}

	Apartment apartments[] = {
			1, "ECLIPSE_TOWERS",
			5, "ALTA_STREET",
			7, "DEL_PERRO_HEIGHTS",
			8, "1162_POWER_ST_APT_3",
			9, "0605_SPANISH_AVE_APT_1",
			10, "0604_LAS_LAGUNAS_BLVD_APT_4",
			11, "0184_MILTON_RD_APT_13",
			12, "THE_ROYALE_APT_19",
			13, "0504_S_MO_MILTON_DR",
			14, "0115_BAY_CITY_AVE_APT_45",
			15, "0325_SOUTH_ROCKFORD_DR",
			16, "DREAM_TOWER_APT_15",
			17, "2143_LAS_LAGUNAS_BLVD_APT_9",
			18, "1561_SAN_VITAS_ST_APT_2",
			19, "0112_S_ROCKFORD_DR_APT_13",
			20, "2057_VESPUCCI_BLVD_APT_1",
			21, "0069_COUGAR_AVE_APT_19",
			22, "PROSPERITY_ST_APT_21",
			23, "1115_BLVD_DEL_PERRO_APT_18",
			24, "0120_MURRIETA_HEIGHT_GARAGE",
			25, "UNIT_14_POPULAR_ST_GARAGE",
			26, "UNIT_2_POPULAR_ST_GARAGE",
			27, "331_SUPPLY_ST_GARAGE",
			28, "UNIT_1_OLYMPIC_FWY_GARAGE",
			29, "0754_ROY_LOWENSTEIN_BLVD_GARAGE",
			30, "12_LITTLE_BIGHORN_AVE_GARAGE",
			31, "UNIT_124_POPULAR_ST_GARAGE",
			32, "0552_ROY_LOWENSTEIN_BLCD_GARAGE",
			33, "0432_DAVIS_AVE_GARAGE",
			35, "WEAZEL_PLAZA",
			38, "4_INTEGRITY_WAY",
			40, "RICHARDS_MAJESTIC",
			42, "TINSEL_TOWERS",
			44, "142_PALETO_BLVD_GARAGE",
			45, "1_STRAWBERRY_AVE_GARAGE",
			46, "1932_GRAPESEED_AVE_GARAGE",
			47, "1920_SENORA_WAY_GARAGE",
			48, "2000_GREAT_OCEAN_HIGHWAY_GARAGE",
			49, "197_ROUTE_68_GARAGE",
			50, "870_ROUTE_68_APPROACH_GARAGE",
			51, "1200_ROUTE_68_GARAGE",
			52, "8754_ROUTE_68_GARAGE",
			53, "1905_DAVIS_AVE_GARAGE",
			54, "1623_SOUTH_SHAMBLES_ST_GARAGE",
			55, "4531_DRY_DOCK_ST_GARAGE",
			56, "1337_EXCEPTIONALISTS_WAY_GARAGE",
			57, "UNIT_76_GREENWICH_PARKWAY_GARAGE",
			58, "INNOCENCE_BLVD_GARAGE",
			59, "634_BLVD_DEL_PERRO_GARAGE",
			60, "0897_MIRROR_PARK_BLVD_GARAGE",
			66, "4_HANGMAN_AVE",
			67, "12_SUSTANCIA_RD",
			68, "4584_PROCOPIO_DR",
			69, "4401_PROCOPIO_DR",
			70, "0232_PALETO_BLVD",
			71, "140_ZANCUDO_AVE",
			72, "1893_GRAPESEED_AVE",
			73, "3655_WILD_OATS_DR",
			74, "2044_NORTH_CONKER_AVE",
			75, "2868_HILLCREST_AVE",
			76, "2862_HILLCREST_AVE",
			77, "3677_WHISPYMOUND_DR",
			78, "2117_MILTON_RD",
			79, "2866_HILLCREST_AVE",
			80, "2874_HILLCREST_AVE",
			81, "2113_MAD_WAYNE_THUNDER_DR",
			82, "2045_NORTH_CONKER_AVE",
			86, "ECLIPSE_WEIRD_FREEZE",
			87, "LOMBANK_WEST_OFFICE",
			88, "MAZE_BANK_WEST_OFFICE",
			89, "ARCADIUS_OFFICE",
			90, "MAZE_BANK_TOWER_OFFICE",
			91, "RANCHO_MC_CLUBHOUSE",
			92, "VESPUCCI_MC_CLUBHOUSE",
			93, "PILLBOX_HILL_MC_CLUBHOUSE",
			94, "GRAND_SENORA_DESERT_MC_CLUBHOUSE",
			95, "PALETO_BAY_MC_CLUBHOUSE",
			96, "SANDY_SHORES_MC_CLUBHOUSE",
			97, "LA_MESA_MC_CLUBHOUSE",
			98, "VINEWOOD_MC_CLUBHOUSE",
			99, "HAWICK_MC_CLUBHOUSE",
			100, "GRAPESEED_MC_CLUBHOUSE",
			102, "VESPUCCI_BEACH_MC_CLUBHOUSE",
	};
}

void PlayerTeleportMenu::Init() {
	setParentSubmenu<PlayerMenu>();
	setName("Teleport player", true, false);

	addOption(ButtonOption("Teleport to player")
		.addFunction([] { TeleportToPlayer(GetSelectedPlayer()); })
		.addTooltip("Teleport to player").addTranslation());

	addOption(ButtonOption("Teleport in players vehicle")
		.addFunction([] { TeleportInPlayersVehicle(GetSelectedPlayer()); })
		.addTooltip("Teleport in players vehicle").addTranslation());

	addOption(ButtonOption("Teleport players vehicle to me")
		.addFunction([] { TeleportPlayersVehicleToMe(GetSelectedPlayer()); })
		.addTooltip("Teleport players vehicle to me").addTranslation());

	addOption(NumberOption<int>(SCROLLSELECT, "Teleport within range")
		.addNumber(range, "%d", 1).addMin(1).addMax(100)
		.addFunction([] {
			Vector3 to = Vector3(GetSelectedPlayer().m_coordinates.x + range, GetSelectedPlayer().m_coordinates.y + range, GetSelectedPlayer().m_coordinates.z + 3);
			ENTITY::SetEntityCoords(GetLocalPlayer().m_ped, to.x, to.y, to.z, 0, 0, 0, 1);
		}).addTooltip("Teleport closeby to the player").addTranslation());

	addOption(BreakOption("Apartments").addTranslation());

	for (auto& ap : apartments) {
		addOption(ButtonOption(NetEvent::GetTeleportLocation(ap.m_id))
			.addFunction([&] {Natives::TriggerScriptEvent({ SCRIPTEVENTS::ECLIPSETELEPORT, GetSelectedPlayer().m_id, 0, 0, ap.m_id, ap.m_id }, 6, GetSelectedPlayer().m_id); })
			.addTooltip("Teleport player to apartment"));
	}
}

/*Update once when submenu is opened*/
void PlayerTeleportMenu::UpdateOnce() {}

/*Update while submenu is active*/
void PlayerTeleportMenu::Update() {}

/*Background update*/
void PlayerTeleportMenu::FeatureUpdate() {}

/*Singleton*/
PlayerTeleportMenu* _instance;
PlayerTeleportMenu* PlayerTeleportMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new PlayerTeleportMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
PlayerTeleportMenu::~PlayerTeleportMenu() { delete _instance; }