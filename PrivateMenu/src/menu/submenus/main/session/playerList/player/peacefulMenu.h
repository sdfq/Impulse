#pragma once
#include "menu/submenu.h"

class PeacefulMenu : public Submenu {
public:
	static PeacefulMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	PeacefulMenu() : Submenu() {}
	~PeacefulMenu();
};

namespace PeacefulMenuVars
{
	void GiveAllWeapons(SPlayer& player);
	void SpawnCloneBodyguard(SPlayer& player);
	void GiveOptionGun(SPlayer& player);
	void RemoveAttachments(SPlayer& player);

	struct Vars {
		int impactAmmoVall;
		int iconIndex = 0;
		bool particlemanToggle;
		int particleman = 0;
		int particlemanselected = 0;
	};

	struct ParticleManStruct {
		String m_pOne;
		String m_pTwo;
		float m_size;
	};
}