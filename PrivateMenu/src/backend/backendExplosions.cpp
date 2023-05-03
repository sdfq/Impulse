#include "stdafx.h"
#include "backendExplosions.h"

Explosions::HashTranslation ExplosionFXList[] = {
	{ "EXP_VFXTAG_GRENADE", EXP_VFXTAG_GRENADE },
	{ "EXP_VFXTAG_STICKYBOMB", EXP_VFXTAG_STICKYBOMB },
	{ "EXP_VFXTAG_MOLOTOV", EXP_VFXTAG_MOLOTOV },
	{ "EXP_VFXTAG_ROCKET", EXP_VFXTAG_ROCKET },
	{ "EXP_VFXTAG_PETROL_PUMP", EXP_VFXTAG_PETROL_PUMP },
	{ "EXP_VFXTAG_VEHICLE", EXP_VFXTAG_VEHICLE },
	{ "EXP_VFXTAG_BIKE", EXP_VFXTAG_BIKE },
	{ "EXP_VFXTAG_DIR_STEAM", EXP_VFXTAG_DIR_STEAM },
	{ "EXP_VFXTAG_DIR_FLAME", EXP_VFXTAG_DIR_FLAME },
	{ "EXP_VFXTAG_DIR_WATER_HYDRANT", EXP_VFXTAG_DIR_WATER_HYDRANT },
	{ "EXP_VFXTAG_DIR_GAS_CANISTER", EXP_VFXTAG_DIR_GAS_CANISTER },
	{ "EXP_VFXTAG_TRUCK", EXP_VFXTAG_TRUCK },
	{ "EXP_VFXTAG_BULLET", EXP_VFXTAG_BULLET },
	{ "EXP_VFXTAG_SMOKE_GRENADE", EXP_VFXTAG_SMOKE_GRENADE },
	{ "EXP_VFXTAG_BZGAS", EXP_VFXTAG_BZGAS },
	{ "EXP_VFXTAG_FBI4_TRUCK_DOORS", EXP_VFXTAG_FBI4_TRUCK_DOORS },
	{ "EXP_VFXTAG_GAS_CANISTER", EXP_VFXTAG_GAS_CANISTER },
	{ "EXP_VFXTAG_EXTINGUISHER", EXP_VFXTAG_EXTINGUISHER },
	{ "EXP_VFXTAG_TRAIN", EXP_VFXTAG_TRAIN },
	{ "EXP_VFXTAG_BARREL", EXP_VFXTAG_BARREL },
	{ "EXP_VFXTAG_PROPANE", EXP_VFXTAG_PROPANE },
	{ "EXP_VFXTAG_BLIMP", EXP_VFXTAG_BLIMP },
	{ "EXP_VFXTAG_FLARE", EXP_VFXTAG_FLARE },
	{ "EXP_VFXTAG_PLANE_ROCKET", EXP_VFXTAG_PLANE_ROCKET },
	{ "EXP_VFXTAG_TANKER", EXP_VFXTAG_TANKER },
	{ "EXP_VFXTAG_PLANE", EXP_VFXTAG_PLANE },
	{ "EXP_VFXTAG_BOAT", EXP_VFXTAG_BOAT },
	{ "EXP_VFXTAG_TANKSHELL", EXP_VFXTAG_TANKSHELL },
	{ "EXP_VFXTAG_TREV3_TRAILER", EXP_VFXTAG_TREV3_TRAILER },
	{ "EXP_VFXTAG_BLIMP2", EXP_VFXTAG_BLIMP2 },
	{ "EXP_VFXTAG_BIRDCRAP", EXP_VFXTAG_BIRDCRAP },
	{ "EXP_VFXTAG_FIREWORK", EXP_VFXTAG_FIREWORK },
	{ "EXP_VFXTAG_SNOWBALL", EXP_VFXTAG_SNOWBALL },
	{ "EXP_VFXTAG_AIR_DEFENCE", EXP_VFXTAG_AIR_DEFENCE },
	{ "EXP_VFXTAG_PIPEBOMB", EXP_VFXTAG_PIPEBOMB },
	{ "EXP_VFXTAG_BOMB_CLUSTER", EXP_VFXTAG_BOMB_CLUSTER },
	{ "EXP_VFXTAG_BOMB_GAS", EXP_VFXTAG_BOMB_GAS },
	{ "EXP_VFXTAG_BOMB_INCENDIARY", EXP_VFXTAG_BOMB_INCENDIARY },
	{ "EXP_VFXTAG_BOMB_STANDARD", EXP_VFXTAG_BOMB_STANDARD },
	{ "EXP_VFXTAG_TORPEDO_UNDERWATER", EXP_VFXTAG_TORPEDO_UNDERWATER },
	{ "EXP_VFXTAG_MINE_UNDERWATER", EXP_VFXTAG_MINE_UNDERWATER },
};

Explosions::sExplosion* Explosions::ExplosionsData;
Explosions::sExplosionFX* Explosions::ExplosionsFXData;

bool Explosions::hasPopulated = false;

int Explosions::GetExplosionFXEntry(Hash hash) {
	int elemCount = sizeof(ExplosionFXList) / sizeof(HashTranslation);
	for (int i = 0; i < elemCount; i++) {
		if (ExplosionFXList[i].hash == hash) {
			return i;
		}
	}
	return 0;
}

Explosions::sExplosion* Explosions::GetExplosion(Hash ExplosionHash) {
	for (int i = 0; i < 62; i++) {
		sExplosion* Explosion = &ExplosionsData[i];
		if (MISC::GetHashKey(Explosion->ExplosionName) == ExplosionHash) {
			return Explosion;
		}
	}
	return nullptr;
}

Explosions::sExplosionFX* Explosions::GetExplosionFX(Hash ExplosionFXHash) {
	for (int i = 0; i < 48; i++) {
		sExplosionFX* ExplosionFX = &ExplosionsFXData[i];
		if (ExplosionFX->NameHash == ExplosionFXHash) {
			return ExplosionFX;
		}
	}
	return nullptr;
}

bool Explosions::PreGame() {
	if (!Hooking::PatternCallback<char>({ "EMAP", true, 0x0, "48 8D ? ? ? ? ? C1 EF 12 8B D0 89 85 88 00 00 00 40 80 E7 01 E8 ? ? ? ?" }, [](char* address) {
		ExplosionsData = *(sExplosion**)(*reinterpret_cast<int *>(address + 3) + address + 7);
	})) return false;
	if (!Hooking::PatternCallback<char>({ "EFX", true, 0x0, "48 8D ? ? ? ? ? 88 45 2C 48 8D 45 C0 4C 8B C3 48 89 44 24 20 E8 ? ? ? ?" }, [](char* address) {
		ExplosionsFXData = *(sExplosionFX**)((*reinterpret_cast<int *>(address + 3) + address + 7) + 16);
	})) return false;
	return true;
}