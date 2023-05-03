#pragma once
#include "menu/submenu.h"

class PlayerTeleportMenu : public Submenu {
public:
	static PlayerTeleportMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	PlayerTeleportMenu() : Submenu() {}
	~PlayerTeleportMenu();
};

namespace PlayerTeleportMenuVars
{
	struct Apartment {
		int m_id;
		String m_name;
	};
	extern Apartment apartments[83];
	extern void TeleportToPlayer(SPlayer& player);
}