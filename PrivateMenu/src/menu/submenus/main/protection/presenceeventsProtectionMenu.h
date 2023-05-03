#pragma once
#include "menu/submenu.h"

class PresenceEventsMenu : public Submenu {
public:
	static PresenceEventsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	PresenceEventsMenu() : Submenu() {}
	~PresenceEventsMenu();
};

namespace PresenceEventsMenuVars
{
	struct Vars {
		bool blocktextmessages;
		bool blockcrewmessages;
		bool blockserverrewards;
	};
	extern Vars vars;
}