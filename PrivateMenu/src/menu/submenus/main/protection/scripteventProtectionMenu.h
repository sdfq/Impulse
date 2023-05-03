#pragma once
#include "menu/submenu.h"

class ScriptEventMenu : public Submenu {
public:
	static ScriptEventMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	ScriptEventMenu() : Submenu() {}
	~ScriptEventMenu();
};

namespace ScriptEventMenuVars
{
	struct Vars {

	};
	extern Vars vars;
}