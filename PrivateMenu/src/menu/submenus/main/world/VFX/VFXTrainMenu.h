#pragma once
#include "menu/submenu.h"

class VFXTrainMenu : public Submenu {
public:
	static VFXTrainMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	VFXTrainMenu() : Submenu() {}
	~VFXTrainMenu();
};

namespace VFXTrainMenuVars {
	void SaveToJson(json& jsonOb);
	void LoadTrains(json& jsonOb);

	struct Vars {
		Color trainsColor;
	};
}