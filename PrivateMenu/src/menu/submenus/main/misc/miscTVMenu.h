#pragma once
#include "menu/submenu.h"

class MiscTVMenu : public Submenu {
public:
	static MiscTVMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	MiscTVMenu() : Submenu() {}
	~MiscTVMenu();
};

namespace MiscTVMenuVars
{
	struct Vars {
		bool tv;
		int channel;
		float x = 0.84f;
		float y = 0.20f;
		float w = 0.26f;
		float h = 0.27f;
		float rotation;
	};
}