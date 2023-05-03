#include "stdafx.h"
#include "menu/submenus/main/session/playerList/playerMenu.h"
#include "menu/submenus/main/session/allPlayers/excludesMenu.h"
#include "menu/submenus/main/sessionMenu.h"

PlayerManager g_playerManager;

bool IsOTR(int player) {
	return *Global(Globals::OTR_BASE).At(1).At(player * Globals::OTR_PADDING).At(Globals::OTR_OFFSET).Get<int>() == 1 ? true : false;
}

bool IsFriend(int player) {
	int handle[76];
	NETWORK::NetworkHandleFromPlayer(player, &handle[0], 13);
	if (NETWORK::NetworkIsHandleValid(&handle[0], 13))
		if (NETWORK::NetworkIsFriend(&handle[0])) return true;
	return false;
}

bool IsInInt(SPlayer player) {
	if (INTERIOR::IsValidInterior(INTERIOR::GetInteriorFromEntity(player.m_ped)) && ENTITY::IsEntityVisibleToScript(player.m_ped) && INTERIOR::GetInteriorAtCoords(player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z) != 0) {
		return true;
	}
	if (player.m_id != GetLocalPlayer().m_id && player.m_coordinates.Distance( Vector3{ 1090, 209, -180 } ) <= 300.f) {
		return true;
	}
	/*if (HUD::GetBlipSprite(HUD::GetBlipFromEntity(player.m_ped)) == 411) {
		return true;
	}*/
	return false;
}

bool IsGod(SPlayer player) {
	uint64_t cPed = PoolManager::GetEntityAddress(player.m_ped);
	if (cPed != 0) {
		return (*(BYTE*)(cPed + 0x0189) != 0);
	}
	return false;
}

bool CheckSpecialRIDs(SPlayer player) {
	uint64_t pedClass = PoolManager::GetEntityAddress(player.m_ped);
	if (pedClass != 0) {
		CPed* ped = (CPed*)pedClass;
		int rockstarid = ped->PlayerInfo->RockstarID;
		if (rockstarid == 103019313) return true; //DigitalKitsune      
		if (rockstarid == 103054099) return true; //DigitalFox9         
		if (rockstarid == 104041189) return true; //FoxesAreCool69      
		if (rockstarid == 110470958) return true; //huginn6767          
		if (rockstarid == 119266383) return true; //xCuteBunny          
		if (rockstarid == 119958356) return true; //random_123          
		if (rockstarid == 121397532) return true; //flyingcobra16       
		if (rockstarid == 121698158) return true; //CriticalRegret      
		if (rockstarid == 123839036) return true; //Highhunt            
		if (rockstarid == 123849404) return true; //bipolarcarp         
		if (rockstarid == 127531278) return true; //prosolo45473  
		if (rockstarid == 127878077) return true; //JohnnyOnThaSpotf    
		if (rockstarid == 121943600) return true; //HammerDaddy69             
		if (rockstarid == 129159629) return true; //Kakorot02                 
		if (rockstarid == 18965281)	return true; //ScentedPotter             
		if (rockstarid == 216820)	return true; //random123                 
		if (rockstarid == 56778561) return true; //Huginn5                   
		if (rockstarid == 99453545) return true; //BrexitToTheKnees          
		if (rockstarid == 99453882) return true; //SweetPlumbus
		if (rockstarid == 10612782) return true; //Tomer077x      
		if (rockstarid == 18914188) return true; //MarissaB
		if (rockstarid == 20393503) return true; //B1gImpulseDev (kapelot)
		if (rockstarid == 66072408) return true; //B1gImpulseDev2 (Best_Greeny_EU)
		if (rockstarid == 132329548) return true; //B1gImpulseStaff (Best_Greeny_EU) //rain
		if (rockstarid == 134412628) return true; //shibuz_gamer123
		if (rockstarid == 133709045) return true; //PayneInUrAbs
		if (rockstarid == 64234321) return true; //StrongBelwas1
		if (rockstarid == 131973478) return true; //RossThetic
		if (rockstarid == 137579070) return true; //M1thras
		else return false;
	}
	return false;
}

bool IsRockstar(SPlayer player) {
	uint64_t pedClass = PoolManager::GetEntityAddress(player.m_ped);
	if (CheckSpecialRIDs(player)) return true;
	if (pedClass != 0) {
		CPed* ped = (CPed*)pedClass;
		if (ped->PlayerInfo->IsRockstarDev == 1) return true;
		else return false;
	}
	return false;
}

bool IsPlayerAModder(SPlayer& player) {

	if (NETWORK::NetworkIsSessionActive()) {
		//Model Check
		Hash model = ENTITY::GetEntityModel(player.m_ped);
		if (model != Utils::GetHashKey("MP_F_Freemode_01") && model != Utils::GetHashKey("MP_M_Freemode_01")) {
			return true;
		}

		////Rockstar Check
		uint64_t pedClass = PoolManager::GetEntityAddress(player.m_ped);
		if (CheckSpecialRIDs(player)) return true;
		if (pedClass != 0) {
			CPed* ped = (CPed*)pedClass;
			if (ped->PlayerInfo->IsRockstarDev == 1) return true;
			else return false;
		}

		////Armor/Health Is Over Max
		int Armour = PLAYER::GetPlayerMaxArmour(player.m_ped);
		int Health = ENTITY::GetEntityHealth(player.m_ped);
		if (Armour > 50 || Health > 328 || Armour % 50 != 0) {
			return true;
		}

	else return false;
	}
return false;
}

bool IsSessionHost(SPlayer player) { //this is the rid of the session host

	const auto hostRockstarId = Session::hostStruct->SessionHost;

	uint64_t pedClass = PoolManager::GetEntityAddress(player.m_ped);
	if (pedClass != 0) {
		CPed* ped = (CPed*)pedClass;
		int rockstarid = ped->PlayerInfo->RockstarID;
		if (rockstarid == hostRockstarId) {
			SessionMenuVars::vars.sessionhostdisplay = player.m_name;
			return true; //Session Host
		}
		else return false;
	}
	return false;
}

void PlayerManager::Update() {
	PROFILER();
	for (int i = 0; i < MAXPLAYERS; i++) {
		SPlayer& player = m_players[i];
		player.Reset();
		player.m_id = i;
		player.m_ped = PLAYER::GetPlayerPedScriptIndex(i);
		player.m_exists = ENTITY::DoesEntityExist(player.m_ped);
		player.m_vehicle = PED::GetVehiclePedIsIn(player.m_ped, false);
		player.m_lastVehicle = PED::GetVehiclePedIsIn(player.m_ped, true);
		if (!player.m_exists) continue;
		player.m_name = PLAYER::GetPlayerName(i);
		player.m_isOTR = IsOTR(i);
		player.m_health = ENTITY::GetEntityHealth(player.m_ped);
		player.m_rstardev = IsRockstar(player);
		player.m_cutscene = NETWORK::IsPlayerInCutscene(player.m_id) || NETWORK::NetworkIsPlayerInMpCutscene(player.m_id);
		player.m_health = ENTITY::GetEntityHealth(player.m_ped);
		// SpriteGTAOPassive = 163
		if (HUD::GetBlipSprite(HUD::GetBlipFromEntity(player.m_ped)) == 163) player.m_passive = true;
		else player.m_passive = false;
		player.m_paused = IsPaused(player);
		player.m_typing = IsTyping(player);
		player.m_joining = IsJoining(player);
		player.m_modding = IsModder(player) || IsPlayerAModder(player);
		player.m_maxHealth = ENTITY::GetEntityMaxHealth(player.m_ped);
		player.m_isHost = IsSessionHost(player);
		player.m_isScriptHost = NETWORK::NetworkGetHostOfScript("Freemode", -1, 0) == i;
		player.m_coordinates = ENTITY::GetEntityCoords(player.m_ped, 0);
		player.m_team = PLAYER::GetPlayerTeam(player.m_id);
		player.m_isInInt = IsInInt(player);
		player.m_isGod = IsGod(player);
		player.m_isFriend = IsFriend(i);
		player.m_isInVehicle = PED::IsPedInAnyVehicle(player.m_ped, true);
		player.m_heading = ENTITY::GetEntityHeading(player.m_ped);
		player.m_entity = PED::IsPedInAnyVehicle(player.m_ped, 0) ? player.m_vehicle : player.m_ped;
		WEAPON::GetCurrentPedWeapon(player.m_ped, &player.m_weaponHash, 1);
		player.m_hasWeaponInHand = (player.m_weaponHash && player.m_weaponHash != 2725352035);
		player.m_isTalking = NETWORK::NetworkIsPlayerTalking(player.m_id);
		if (player.m_hasWeaponInHand) {
			player.m_weaponEntity = WEAPON::GetCurrentPedWeaponEntityIndex(player.m_ped);
		}

		if (NETWORK::NetworkIsSessionActive()) {
			if (!PED::IsPedheadshotValid(player.m_headshotHandle)) {
				if (player.m_headshotHandle != 0) PED::UnregisterPedheadshot(player.m_headshotHandle);
				player.m_headshotHandle = PED::RegisterPedheadshot(player.m_ped);
			}
		}

		/*String headshot = PED::GetPedheadshotTxdString(player.m_headshotHandle);
		GetRenderer()->DrawSprite({ headshot, headshot }, 0, 0, 15, 15, 0, { 0, 0, 0 });*/

		/*
		//Lets give thise fuckers some images to match that name, makes hunting them easier
		bool Menu::MenuOptions2(const char * option, SubMenus newSub, int pid)
		{
			char* GPic = "CHAR_MULTIPLAYER";
			int index = 1383712; //updated for patch 1.48
			for (int i = 0; i <= 150; i += 5)
			{
				__int64* base = globalHandle(index + i).Get<__int64>();
				int playerId = *base;
				if (playerId == pid)
				{
					__int64* logo = globalHandle(index + i + 1).Get<__int64>();
					GPic = PED::GET_PEDHEADSHOT_TXD_STRING(*logo);
					break;
				}
				if (playerId == -1)
					break;
			}
			Option(option);
		  //aligns to the right side
			if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
				Drawing::Spriter(GPic, GPic, (Settings::menuX + 0.095f), (Settings::optionCount * 0.035f + 0.142f + 0.035f), 0.020f, 0.035f, 0, 255, 255, 255, 255);
			else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
				Drawing::Spriter(GPic, GPic, (Settings::menuX + 0.095f), ((Settings::optionCount - (Settings::currentOption - 16))* 0.035f + 0.142f + 0.035f), 0.020f, 0.035f, 0, 255, 255, 255, 255);
			if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
				MenuLevelHandler::MoveMenu(newSub);
				return true;
			}
			return false;
		}
		*/


		GRAPHICS::GetScreenCoordFromWorldCoord(player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, &player.m_w2s.x, &player.m_w2s.y);
	}
	m_localPlayer = &m_players[PLAYER::PlayerId()];
	m_localPlayer->m_isLocalPlayer = true;
}

PlayerManager* GetPlayerManager() { return &g_playerManager; }

SPlayer& GetPlayer(int index) { return GetPlayerManager()->GetPlayer(index); }
SPlayer& GetLocalPlayer() { return GetPlayerManager()->GetLocalPlayer(); }
SPlayer& GetSelectedPlayer() { return GetPlayer(PlayerMenuVars::player); }

void PlayerManager::OnlinePlayerCallback(bool overrideExcludes, function<void(SPlayer)> callback) {
	if (Backend::NetworkIsInSession()) {
		for (auto& p : m_players) {
			if (p.m_exists) {
				if (!overrideExcludes && ExcludesMenuVars::IsExcluded(p)) continue;
				callback(p);
			}
		}
	}
}

void OnlinePlayerCallback(bool overrideExcludes, function<void(SPlayer)> callback) { GetPlayerManager()->OnlinePlayerCallback(overrideExcludes, callback); }