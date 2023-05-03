#pragma once
#include "menu/submenu.h"

class GlobalMenu : public Submenu {
public:
	static GlobalMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	GlobalMenu() : Submenu() {}
	~GlobalMenu();
};

namespace GlobalMenuVars
{
	struct Vars
	{
		bool otr = false;
		bool blindeye = false;
		bool testosterone = false;
		bool noorbitalcooldown = false;
		/*int spoofranknum;
		int spoofcashnum;
		bool spoofrank;
		bool spoofcash;*/
		bool testosteronel;
	};
}