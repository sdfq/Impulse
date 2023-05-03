#pragma once
#include "menu/submenu.h"

class EditClosestDrawableMenu : public Submenu {
public:
	static EditClosestDrawableMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	EditClosestDrawableMenu() : Submenu() {}
	~EditClosestDrawableMenu();
};

namespace EditClosestDrawableMenuVars
{
	struct Vars {
		float accuracy = 10.0f;
		Vector3 position;
		float scale;
		int lod;
	};

	extern Vars vars;
}