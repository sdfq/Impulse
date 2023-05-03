#include "stdafx.h"
#include "backendModelSwap.h" // required for model swapping
#include "menu/submenus/main/session/playerList/player/griefingMenu.h" // required for not breaking crash player
#include "menu/submenus/main/model swapping/swappingPresetsMenu.h"// to make presets work in the hook
#include "menu\submenus\main\developerMenu.h"
#include "menu\submenus\main\testerMenu.h"
#include "menu\submenus\main\protection\presenceeventsProtectionMenu.h"
#include "menu/submenus/main/miscMenu.h"
#include "menu/submenus/main/session/streamermodeMenu.h"

Protection::pSpawnCNetObject Protection::OriginalSpawnCNetObject;
Protection::pSpawnCNetObject Protection::OriginalSpawnCNetObjectPed;
Protection::pGetModelObject  Protection::OriginalGetModelObject;

bool Protection::SpawnCNetObjectHook(DWORD64 a1, DWORD64 data) { 

	Hash prop = *(unsigned int*)(data + 0x140);

	//LOG_PRINT("Hash 1: 0x%X\n", prop);

	switch (prop) {
		case 0xFBF7D21F:
		case 0x6D1BB815:
		case 0x9CF21E0F:
		case 0x34315488:
		case 0x6A27FEB1:
		case 0xCB2ACC8:
		case 0xC6899CDE:
		case 0xD14B5BA3:
		case 0xD9F4474C:
		case 0x32A9996C:
		case 0x69D4F974:
		case 0xCAFC1EC3:
		case 0x79B41171:
		case 0x1075651:
		case 0xC07792D4:
		case 0x781E451D:
		case 0x762657C6:
		case 0xC2E75A21:
		case 0xC3C00861:
		case 0x81FB3FF0:
		case 0x45EF7804:
		case 0xE65EC0E4:
		case 0xE764D794:
		case 0xE1AEB708:
		case 0xA5E3D471:
		case 0xD971BBAE:
		case 0xCF7A9A9D:
		case 0xC2CC99D8:
		case 0x8FB233A4:
		case 0x24E08E1F:
		case 0x337B2B54:
		case 0xB9402F87:
		case 0x4F2526DA: {
				GetRenderer()->NotifyMap("Prevented crash prop spawn");
				LOG_DEVPRINT("[Protect] Prevented crash prop spawn");
				return false;
				} 
		default: 
			return OriginalSpawnCNetObjectPed(a1, data);
	}
}

bool Protection::SpawnCNetObjectPedHook(DWORD64 a1, DWORD64 data) {
	
	Hash ped = *(unsigned int*)(data + 0xC4);

	switch (ped) {
		case 0x3F039CBA: // slod
		case 0x856CFB02: // slod
		case 0x2D7030F3: // slod
		case 0xB881AEE:
		case 0x8D8F1B10:
		case 0x613e626c: {
				GetRenderer()->NotifyMap("Prevented crash ped spawn");
				LOG_DEVPRINT("[Protect] Prevented crash ped spawn");
				return false;
				}
		default: 
			return OriginalSpawnCNetObject(a1, data);
	}
}

__int64 Protection::GetModelObjectHook(Hash hash, int* data) {

	if (TesterMenuVars::vars.logentitiess) {
		LOG_PRINT("Entity Hash: 0x%X", hash);
	}

	if (GriefingMenuVars::vars.disableCrashProtectionThisFrame) {
		return OriginalGetModelObject(hash, data); // so we can still crash players
	}

	// model swap ( old implementation )
	/*if (ModelSwapping::modelSwaps.size() > 0)
		for (modelSwap_t m : ModelSwapping::modelSwaps)
			if (m.originalHash == hash) 
				return OriginalGetModelObject(m.newHash, data);*/

	switch (hash) { // peds and objects compatible, vehicles work too, model swapping can be performed.
		case 0x3F039CBA: // slod
		case 0x856CFB02: // slod
		case 0x2D7030F3: // slod
		//case 0xB881AEE: //check
		//case 0x8D8F1B10: //check
		//case 0x613e626c: //check
		case 0xA8683715:
		{
			//LOG_DEVPRINT("[Protect] Prevented crash ped spawn");
			return false;
		}
		//case 0x897AFC65: //check
		case 0x8077CE20:
		//case 0x4FCAD2E0: //check
		case 0x8694692B:
		case 0x54A0DFE3:
		case 0xFD0CDFAE:
		case 0x88C3E396:
		case 0x4066A56C:
		case 0x34CFCAB1:
		case 0xB43F82B4:
		case 0x4A7209B0:
		case 0x9CF21E0F:// end
		case 0x34315488://
		case 0x6A27FEB1://
		case 0xCB2ACC8://
		case 0xC6899CDE://
		case 0xD14B5BA3://
		case 0xD9F4474C://
		case 0x32A9996C://
		case 0x69D4F974://
		case 0xCAFC1EC3://
		case 0x79B41171://
		case 0x1075651://
		case 0xC07792D4://
		case 0x781E451D://
		case 0x762657C6://
		case 0xC2E75A21://
		case 0xC3C00861://
		case 0x81FB3FF0://
		case 0x45EF7804://
		case 0xE65EC0E4://
		case 0xE764D794://
		case 0xE1AEB708://
		case 0xA5E3D471://
		case 0xD971BBAE://
		case 0xCF7A9A9D://
		case 0xC2CC99D8://
		case 0x8FB233A4://
		case 0x24E08E1F://
		case 0x337B2B54://
		case 0xB9402F87://
		case 0x4F2526DA:// start
		//case 0x3E3C351E:
		{
			//LOG_DEVPRINT("[Protect] Prevented crash prop spawn");
			return false;
		}
		// EvolveKiller can suck my dick
		default:
			return OriginalGetModelObject(hash, data);
	}
}

std::unordered_map<CPlayerInfo*, std::string> cachedPlayerInfo;

typedef CPlayerInfo* (*AllocatePlayerInfo)(__int64 a1, __int64 a2);
AllocatePlayerInfo OriginalAllocatePlayerInfo;
CPlayerInfo* AllocatePlayerInfoHook(__int64 a1, __int64 a2)
{
	CPlayerInfo* result = originalAllocatePlayerInfo(rcx, rdx);
	
	if (hideNames) {
		cachedPlayerInfo[result] = result->name;
	}

	return result;
}

bool Protection::PreGame() {

	/*Model Protection*/
	if (!Hooking::ServerPatternCallback<void>("EVKSD", [](Hooking::CallbackData<void> data) {
		Backend::GetModelInfo = (Backend::pGetModelInfo)data.m_address;
		return Hooking::HookFunction(data.m_address, &GetModelObjectHook, &OriginalGetModelObject, "EVKSD");
	})) return false;

	if (!Hooking::ServerPatternCallback<void>("ACPI", [](Hooking::CallbackData<void> data) {
		return Hooking::HookFunction(data.m_address, &AllocatePlayerInfoHook, &OriginalAllocatePlayerInfo, "ACPI");
	})) return false;

	///*Spawn CNetObject*/
	//if (!Hooking::PatternCallback<void>({ "SCNO", true, 0, "48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8B EC 48 83 EC 70 8A 82 ? ? ? ?" }, [](void* address) {
	//	return Hooking::HookFunction(address, &SpawnCNetObjectHook, &OriginalSpawnCNetObject, "SCNO");
	//})) return false;

	///*Spawn CNetObjectPed*/
	//if (!Hooking::PatternCallback<void>({ "SCNOP", true, 0, "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC 20 4C 8D B1 ? ? ? ? 48 8B F9 48 8B F2" }, [](void* address) {
	//	return Hooking::HookFunction(address, &SpawnCNetObjectPedHook, &OriginalSpawnCNetObjectPed, "SCNOP");
	//})) return false;

	/*protection*/
	FingerOfGod::Init([](PresenceEvent event, FingerCommand command, String name) -> bool {
		switch (event) {
		case PRESENCE_TEXT_MESSAGE:
			if (PresenceEventsMenuVars::vars.blocktextmessages) {
				if (NetEvent::vars.notifyPE) GetFiberPool()->DoJob([=] { GetRenderer()->NotifyMap("Presence: Blocked\nFrom: Someone\nType: Text Message"); });
				return true;
			}
			break;
		case PRESENCE_ROCKSTAR_CREW_MESSAGE:
			if (PresenceEventsMenuVars::vars.blockcrewmessages) {
				if (NetEvent::vars.notifyPE) GetFiberPool()->DoJob([=] { GetRenderer()->NotifyMap("Presence: Blocked\nFrom: Someone\nType: Crew Message"); });
				return true;
			}
			break;
		case PRESENCE_GAME_SERVER:
			if (PresenceEventsMenuVars::vars.blockserverrewards) {
				if (NetEvent::vars.notifyPE) GetFiberPool()->DoJob([=] { GetRenderer()->NotifyMap("Presence: Blocked\nFrom: Game\nType: Server Reward"); });
				return true;
			}
			break;
		}
		return false;
	});

	//FingerOfGod::Init([](PresenceEvent event, FingerCommand command, String name) -> bool {
	//	switch (event) {
	//		case PRESENCE_GAME_SERVER:
	//			GetFiberPool()->DoJob([=] { GetRenderer()->NotifyMap("[FOG] Someone tried to fake a cash correct on you."); });
	//			return true;
	//		//case PRESENCE_FINGER_OF_GOD:
	//			//switch (command) {
	//			//	case FINGER_KILL:
	//			//		GetFiberPool()->DoJob([=] { GetRenderer()->NotifyMap("[FOG] Someone tried to kill you."); });
	//			//		return true; // block;
	//			//	case FINGER_ADMIN_KICK:
	//			//	case FINGER_NETWORK_KICK:
	//			//		GetFiberPool()->DoJob([=] { GetRenderer()->NotifyMap("[FOG] Someone tried to kick you."); });
	//			//		return true;
	//			//	case FINGER_RELAX:
	//			//		GetFiberPool()->DoJob([=] { GetRenderer()->NotifyMap("[FOG] Someone tried to ragdoll you."); });
	//			//		return true;
	//			//	case FINGER_VEHICLE:
	//			//		GetFiberPool()->DoJob([=] { GetRenderer()->NotifyMap("[FOG] Someone tried to spawn a vehicle."); });
	//			//		return true;
	//			//	default:
	//			//		LOG_DEVCUSTOM(ConsoleForeground::DARKGREEN, "[FOG] Blocked admin command: 0x%X from %s", command, name);
	//			//		return true;
	//			//}
	//		default: break;
	//	}
	//	return false;
	//});


	return true;
}
bool Protection::InGame() {
	return true;
}

void Protection::Cleanup() {

}
