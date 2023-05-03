#pragma once
#include "menu/submenu.h"

class OwnedForcefield : public Submenu {
public:
	static OwnedForcefield* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	OwnedForcefield() : Submenu() {}
	~OwnedForcefield();
};

namespace OwnedForcefieldVars
{

	struct Vars {
		bool ForcefieldToggle = false;
		SPlayer targetPlayer;
	};

}