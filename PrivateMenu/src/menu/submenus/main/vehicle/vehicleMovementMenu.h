#pragma once
#include "menu/submenu.h"

class VehicleMovementMenu : public Submenu {
public:
	static VehicleMovementMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	VehicleMovementMenu() : Submenu() {}
	~VehicleMovementMenu();
};

namespace VehicleMovementMenuVars {
	struct Vars {
		Object driveonwaterobject;
		bool fly;
		bool jump;
		bool drift;
		bool wheelie;
		bool autodrive;
		bool hornboost;
		bool speedlimit;
		bool driveonwater;
		bool driveonwalls;
		bool unlimitedboost;
		bool bypassmaxspeed;
		int flyspeed = 1;
		int brakeforce = 0;
		int driftamount = 5;
		int hornboostspeed = 3;
		int autodrivespeed = 10;
		int driftkey = 0x10;
		bool driftkeyController = false;
		float downforce = 0;
		float speedlimitamount = 1;
		bool craterider;
		int crateriderent;
		bool lowerrideheight = false;
		bool flyingvehicle;
		bool basicflyingvehicle;
		float basicflyspeed = 25.0f;
	};
}