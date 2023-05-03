#pragma once
#include "menu/submenu.h"

class TeleportMenu : public Submenu {
public:
	static TeleportMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	TeleportMenu() : Submenu() {}
	~TeleportMenu();
};

namespace TeleportMenuVars
{
	void TeleportToCoords(Vector3 coords);
	Vector3 GetWaypointCoords();
	Vector3 GetTeleportCoordsFixedHeight();
	

	struct Vars {
		int teleportToWaypointKey;
		bool teleportToWaypointIsController;
		bool transition = false;
	};
}