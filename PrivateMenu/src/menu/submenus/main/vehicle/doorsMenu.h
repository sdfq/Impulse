#pragma once
#include "menu/submenu.h"

class DoorsMenu : public Submenu {
public:
	static DoorsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	DoorsMenu() : Submenu() {}
	~DoorsMenu();
};

namespace DoorsMenuVars
{
	struct Vars {
		int openDoor;
		int closeDoor;
		int deleteDoor;

	};
}