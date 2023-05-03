#pragma once
#include "menu/submenu.h"

class SettingsMenu : public Submenu {
public:
	static SettingsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	SettingsMenu() : Submenu() {}
	~SettingsMenu();
};

namespace SettingsMenuVars {
	struct Vars {
		int measurementType;
		int hideType;
		bool hideuitooltips;
		bool hideuicursortooltip;
		bool hideplayerips;
		bool hidemap;
		int openkeynew = INPUT_FRONTEND_RB;
		int openkeynew2 = INPUT_FRONTEND_LEFT;
		bool controllerKey1;
		bool controllerKey2;
		bool keeplastpos;
		int maxdisplayoptions;
		bool hideplayerrids;
		bool unoutlinestoof;
		bool speedupsmoothscrolling;
		bool disablesmoothscroll;
		bool disablecontrollerinput;
	};
	extern Vars vars;
	extern ScrollStruct<float> measurementTypes[2];
}