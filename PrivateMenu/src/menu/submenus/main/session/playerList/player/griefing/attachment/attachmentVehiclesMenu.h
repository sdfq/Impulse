#pragma once
#include "menu/submenu.h"

class AttachmentVehiclesMenu : public Submenu {
public:
	static AttachmentVehiclesMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	AttachmentVehiclesMenu() : Submenu() {}
	~AttachmentVehiclesMenu();
};

namespace AttachmentVehiclesMenuVars
{
	struct Vars {

	};
}