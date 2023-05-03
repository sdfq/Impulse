#pragma once
#include "menu/submenu.h"

class LocalMenu : public Submenu {
public:
	static LocalMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	LocalMenu() : Submenu() {}
	~LocalMenu();
};

namespace LocalMenuVars {
	void DisablePhone();

	struct Vars {
		bool godmode = false;
		bool regen = false;
		bool neverwanted = false;
		int wantedlevel = 0;
		float maxhealth = 0;
		bool noragdoll = false;
		bool seatbelt = false;
		bool ignoreplayer = false;


		bool forcefield = false;
		bool midget = false;
		bool badsport = false;


		int invisibility = 0;
		bool invisibilityToggle = false;
		int opacity = 0;
		bool karma = false;
		bool reducedcollision;
		//int wantedlevel;
		
	};

	extern Vars vars;
}