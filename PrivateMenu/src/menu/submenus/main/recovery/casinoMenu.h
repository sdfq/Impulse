#pragma once
#include "menu/submenu.h"

class CasinoMenu : public Submenu {
public:
	static CasinoMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	CasinoMenu() : Submenu() {}
	~CasinoMenu();
};

namespace CasinoMenuVars
{
	struct Vars
	{
		bool DisableChipsBuyTimer;
		bool BillionChips;
		bool UnlockShirts;
	};
	extern Vars vars;
}