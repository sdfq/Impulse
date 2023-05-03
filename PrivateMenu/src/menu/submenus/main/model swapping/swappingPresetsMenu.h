#pragma once
#include "menu/submenu.h"

class SwapPresetsMenu : public Submenu {
public:
	static SwapPresetsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	SwapPresetsMenu() : Submenu() {}
	~SwapPresetsMenu();
};

namespace SwappingPresetsMenuVars
{
	struct Vars {
		bool emergencyToTrucks = false;
		bool policeToTrucks = false;
		bool superToBuffalos = false;
		bool planesToTitans = false;
		bool planesToCargos = false;
		bool vansToInsurgents = false;
	};
	extern Vars var;
}