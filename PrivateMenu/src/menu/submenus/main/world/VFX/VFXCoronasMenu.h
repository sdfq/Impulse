#pragma once
#include "menu/submenu.h"

class VFXCoronasMenu : public Submenu {
public:
	static VFXCoronasMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	VFXCoronasMenu() : Submenu() {}
	~VFXCoronasMenu();
};

namespace VFXCoronasMenuVars {
	void SaveToJson(json& jsonOb);
	void LoadCoronas(json& jsonOb);

	struct Vars {
		Color coronas;
	};
}