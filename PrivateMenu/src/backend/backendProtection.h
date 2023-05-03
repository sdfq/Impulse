#pragma once

class Protection {
protected:
	typedef bool(__fastcall *pSpawnCNetObject)(DWORD64 a1, DWORD64 data);
	typedef __int64(__fastcall *pGetModelObject)(Hash hash, int* data);
	static pSpawnCNetObject OriginalSpawnCNetObject;
	static pSpawnCNetObject OriginalSpawnCNetObjectPed;
	static pGetModelObject OriginalGetModelObject;
	static bool SpawnCNetObjectHook(DWORD64 a1, DWORD64 data);
	static bool SpawnCNetObjectPedHook(DWORD64 a1, DWORD64 data);
	static __int64 GetModelObjectHook(Hash hash, int * data);
public:
	static bool PreGame();
	static bool InGame();
	static void Cleanup();
};

