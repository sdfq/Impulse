#pragma once
#include "menu/submenu.h"

class LoadCustomHeaderMenu : public Submenu {
public:
	static LoadCustomHeaderMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	LoadCustomHeaderMenu() : Submenu() {}
	~LoadCustomHeaderMenu();
};

namespace LoadCustomHeaderMenuVars
{
	void LoadConfig();
	struct Vars
	{
		bool loadOnStart = false;
		vector<string> customYTDHeaderNames;
	};
}