#pragma once
#include "../../../submenu.h"

class MiscExternalLinksMenu : public Submenu {
public:
	static MiscExternalLinksMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	MiscExternalLinksMenu() : Submenu() {}
	~MiscExternalLinksMenu();
};

namespace MiscExternalLinksMenuVars
{
	struct Vars {

	};
}