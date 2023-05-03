#pragma once
#include "menu/submenu.h"

class SessionMenu : public Submenu {
public:
	static SessionMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	SessionMenu() : Submenu() {}
	~SessionMenu();
};

namespace SessionMenuVars
{

	struct Vars {
		int toJoin;
		bool showtalkingplayers = false;
		bool bypassevoblock;
		bool showmarkeronselectedbydefault;
		int markertypeselector;
		String message = "";
		bool showAsEvolve;
		bool showAsEvolveStaff;
		bool showAsEvolveVIP;
		bool warncashcreation;
		bool warnonplayerjoin;
		bool showotr;
		bool showconnectandfree;
		int testing1;
		int testing2;
		int testing3;
		int testing4;
		bool showcoords;
		string DefaultSCName;
		String sessionhostdisplay = "";
	};
	extern Vars vars;
}