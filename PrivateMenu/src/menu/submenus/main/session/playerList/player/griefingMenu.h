#pragma once
#include "menu/submenu.h"

class GriefingMenu : public Submenu {
public:
	static GriefingMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	GriefingMenu() : Submenu() {}
	~GriefingMenu();
};

namespace GriefingMenuVars
{
	struct Vars {
		bool disableCrashProtectionThisFrame = false;
		int attackerCount = 1;
		int JetSwarm = 0;
		bool cloneCrashing = false;
		bool laggingPlayer = false;
		bool laggingPlayer2 = false;
		int lagvehicleselect;
	};
	extern Vars vars; // declaring for the getmodelobject hook

	void Karma(SPlayer& player);
	void Hostkick(SPlayer& player);
	void CrashPlayer(SPlayer& player);
	void Explode(SPlayer& player);
	void WaterLoop(SPlayer& player);
	void FireLoop(SPlayer& player);
	void SetOnFire(SPlayer& player, bool toggle);
	void RamWithVehicle(SPlayer& player);
	void ClonePlayer(SPlayer& player, bool hostile);
	void BlamePlayer(SPlayer& player);
	void Airstrike(SPlayer& player);
	void SWATAttack(SPlayer& player);
	void JetAttack(SPlayer& player);
	void HostileTraffic(SPlayer& player);
	void HostilePeds(SPlayer& player);
	void RainRockets(SPlayer& player);
	void ShakeCamera(SPlayer& player);
	void CagePlayer(SPlayer& player);
	void Forcefield(SPlayer& player);
	void SendAttackers(SPlayer& player, int count);
	void FreezeInPlace(SPlayer& player);
	void SmokePlayer(SPlayer& player);
	void AlwaysWanted(SPlayer& player);
	void FakeMoney(SPlayer& player);
	void GlitchPed(SPlayer& player);
	void Electrocute(SPlayer& player);
	void TrapPlayer(SPlayer& player);
}