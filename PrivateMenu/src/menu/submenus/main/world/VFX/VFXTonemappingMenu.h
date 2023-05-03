#pragma once
#include "menu/submenu.h"

class VFXTonemappingMenu : public Submenu {
public:
	static VFXTonemappingMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	VFXTonemappingMenu() : Submenu() {}
	~VFXTonemappingMenu();
};

namespace VFXTonemappingMenuVars {
	void SaveToJson(json& jsonOb);
	void LoadTonemapping(json& jsonOb);

	struct Vars {
		float equationDay;
		float equationNight;
	};
}