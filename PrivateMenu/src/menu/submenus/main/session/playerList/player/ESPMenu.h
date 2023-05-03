#pragma once
#include "menu/submenu.h"

class ESPMenu : public Submenu {
public:
	static ESPMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	ESPMenu() : Submenu() {}
	~ESPMenu();
};

namespace ESPMenuVars
{
	void NameESP(SPlayer& player);
	void ESPBox(SPlayer& player);
	void LineESP(SPlayer& player);
	void HeadMarkerESP(SPlayer& player);
	void FootMarkerESP(SPlayer& player);
	void InfoESP(SPlayer& player);
	void BonesShow(SPlayer& player, bool toggle);
	void SkyLine(SPlayer& player);
	struct Vars {
		Color ESPColor = { 255, 0, 0, 255 };
		Color ESPLOSColor = { 0, 255, 0, 255 };
		bool ESPLOSGREEN;
	};
	extern Vars vars;
}