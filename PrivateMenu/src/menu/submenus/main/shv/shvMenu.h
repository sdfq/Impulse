#pragma once
#include "menu/submenu.h"

class SHVMenu : public Submenu {
public:
	static SHVMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	SHVMenu() : Submenu() {}
	~SHVMenu();
};

namespace SHVMenuVars
{
	struct Vars {

	};

	extern vector<HMODULE> m_pluginHandles;
}