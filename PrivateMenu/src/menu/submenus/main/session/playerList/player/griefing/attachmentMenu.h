#pragma once
#include "menu/submenu.h"

class AttachmentMenu : public Submenu {
public:
	static AttachmentMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	AttachmentMenu() : Submenu() {}
	~AttachmentMenu();
};

namespace AttachmentMenuVars
{
	void AttachObjectToPlayer(SPlayer& player, Hash object, int bone = 0, float x = 0, float y = 0, float z = 0, float xr = 0, float yr = 0, float zr = 0);
	void AttachPedToPlayer(SPlayer& player, Hash ped, int bone = 0, float x = 0, float y = 0, float z = 0, float xr = 0, float yr = 0, float zr = 0);
	void AttachVehicleToPlayer(SPlayer& player, Hash vehicle, int bone = 0, float x = 0, float y = 0, float z = 0, float xr = 0, float yr = 0, float zr = 0);
}