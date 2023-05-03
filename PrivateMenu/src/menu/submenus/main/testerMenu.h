#pragma once
#include "menu/submenu.h"

class TesterMenu : public Submenu {
public:
	static TesterMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	TesterMenu() : Submenu() {}
	~TesterMenu();
};

namespace TesterMenuVars
{
	struct Vars
	{
		bool logentitiess;
	};
	extern Vars vars;
}