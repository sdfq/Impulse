#pragma once
typedef void(__fastcall *tNetUpdateTime)(int a1, __int64 a2);
class Natives
{
private:
	static unordered_map<uint64_t, NativeHandler> m_handlerCache;
	static NativeRegistration** m_registrationTable;
	static DWORD64 m_ownedExplosionAddress;
	static DWORD64 m_changeWeatherLobbyAddress;
	static DWORD64 m_changeLobbyTimeAddress;
	static DWORD64 m_changeLobbyTimeCallAddress;

	typedef bool(__cdecl*	pNetworkRequestControlOfEntity)(Entity entity);
	static pNetworkRequestControlOfEntity fNetworkRequestControlOfEntity;

	typedef BOOL(__cdecl*	pRequestModel)(DWORD hash);
	static pRequestModel fRequestModel;

	typedef bool(__cdecl*	pHasModelLoaded)(DWORD hash);
	static pHasModelLoaded fHasModelLoaded;

	typedef void(__cdecl * pTriggerScriptEvent)(Any p0, int64_t* argsStruct, Any argsStructSize, int64_t bitset);
	static pTriggerScriptEvent fTriggerScriptEvent;

	typedef void(__cdecl * pSetCurrentPedWeapon)(Ped ped, Hash weaponHash, BOOL equipNow);
	static pSetCurrentPedWeapon OriginalSetCurrentPedWeapon;
	static void SetCurrentPedWeaponHook(Ped ped, Hash weaponHash, BOOL equipNow);

	typedef void(__cdecl * pDisableControlAction)(int inputGroup, int control, BOOL disable);
	static pDisableControlAction OriginalDisableControlAction;
	static void DisableControlActionHook(int inputGroup, int control, BOOL disable);

public:
	static bool PreGame();
	static bool InGame();
	static void Cleanup();

	static NativeHandler getNativeHandler(uint64_t hash);
	static NativeHandler getNativeHandlerCache(uint64_t hash);

	static void AddOwnedExplosion(Ped ped, float x, float y, float z, int explosionType, float damageScale, bool isAudible, bool isInvisible, float cameraShake);
	static void TriggerScriptEvent(vector<int64_t> Args, int ArgCount, Player BitsetPlayer);
	static void ObfuscatedTriggerScriptEvent(vector<int64_t> Args, int ArgCount, Player BitsetPlayer);
	static void TriggerScriptEvent(int64_t* Args, int ArgCount, Player BitsetPlayer);
	static void SetLobbyWeather(String weather);
	static void SyncLobbyTimeWithMyTime();
	static void NetworkRequestControlOfEntity(Entity entity);
	static void RequestModel(Hash model);
	static void HasModelLoaded(Hash model);


	typedef void(*pSetLobbyWeather)(int eventId, int weatherId, int identifier, int unk);
	static pSetLobbyWeather fSetLobbyWeather;
};