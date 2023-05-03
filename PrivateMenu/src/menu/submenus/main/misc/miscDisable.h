#pragma once
#include "menu/submenu.h"

class MiscDisableMenu : public Submenu {
public:
	static MiscDisableMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	MiscDisableMenu() : Submenu() {}
	~MiscDisableMenu();
};

namespace MiscDisableMenuVars
{
	struct Vars {
		bool disablePhoneCalls;
		bool cinematicdisable;
	};
}