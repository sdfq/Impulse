#pragma once
#include "menu/submenu.h"

class StreamerModeMenu : public Submenu {
public:
	static StreamerModeMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	StreamerModeMenu() : Submenu() {}
	~StreamerModeMenu();
};

namespace StreamerModeMenuVars
{
	struct Vars {
		bool StreamerMode;
		string nameprefix = "Player";
		bool changelobbyrids;
	};
	extern Vars vars;
}