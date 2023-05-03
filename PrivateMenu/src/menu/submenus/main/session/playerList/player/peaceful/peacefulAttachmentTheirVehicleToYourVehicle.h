#pragma once
#include "menu/submenu.h"

class PeacefulAttachmentTheirVehicleToYourVehicleMenu : public Submenu {
public:
	static PeacefulAttachmentTheirVehicleToYourVehicleMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	PeacefulAttachmentTheirVehicleToYourVehicleMenu() : Submenu() {}
	~PeacefulAttachmentTheirVehicleToYourVehicleMenu();
};

namespace PeacefulAttachmentTheirVehicleToYourVehicleMenuVars
{
	struct Vars {

	};
}