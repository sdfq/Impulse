#pragma once
#include "menu/submenu.h"

class PlayerMovementMenu : public Submenu {
public:
	static PlayerMovementMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	PlayerMovementMenu() : Submenu() {}
	~PlayerMovementMenu();
};

namespace PlayerMovementMenuVars
{
	struct Vars {
		bool enableMovementSpeed;
		bool enableSwimSpeed;
		float movementSpeed = 1;
		float swimSpeed = 1;
		bool slowmotion = false;
		bool fastrun = false;
		bool superjump = false;
		bool ultrajump = false;
		bool walkonwater = false;
		bool walkthroughwater = false;
		bool walkonair = false;
		bool vegetablemode = false;
		bool flymode = false;
		bool noclip = false;
		float noclipspeed = 2.0f; //2.0f
		float speedmult = 0.5f;
		Vector3 noclipCoords;
		bool walkingnoclip;
		int boostKey = 0x10;
		bool boostKeyController = false;
		bool speedboost = false;
		float speedboostamount = 2;
		bool classicjumps;
		int classjumpselect;
	};
}