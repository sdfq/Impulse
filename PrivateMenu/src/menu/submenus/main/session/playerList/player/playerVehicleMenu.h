#pragma once
#include "menu/submenu.h"

class PlayerVehicleMenu : public Submenu {
public:
	static PlayerVehicleMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	PlayerVehicleMenu() : Submenu() {}
	~PlayerVehicleMenu();
};

namespace PlayerVehicleMenuVars
{
	void HornBoost(SPlayer& player);
	void SetVehicleEngineHealth(SPlayer& player, int health);
	void KickFromVehicle(SPlayer& player, bool loop);
	void RotateVehicle(SPlayer& player);
	void DeleteVehicle(SPlayer& player);
	void FixVehicle(SPlayer& player);
	void TuneVehicle(SPlayer& player);
	void LaunchVehicle(SPlayer& player);
	void BurstTires(SPlayer& player);
	void BoostVehicle(SPlayer& player);
	void StopVehicle(SPlayer& player);
	void GodmodeVehicle(SPlayer& player);
	void FreezeVehicle(SPlayer& player, bool toggle);
	void LockDoors(SPlayer& player, bool lock);
	void SlingShotVehicle(SPlayer& player);
}