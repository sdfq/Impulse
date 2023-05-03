#pragma once
#include "menu/submenu.h"

class DeveloperMenu : public Submenu {
public:
	static DeveloperMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	DeveloperMenu() : Submenu() {}
	~DeveloperMenu();
};

namespace DeveloperMenuVars
{
	struct Vars
	{
		bool drop;
		bool header;
		bool logentities;
		bool submenu;
		bool testing;
	};
	extern Vars vars;
}