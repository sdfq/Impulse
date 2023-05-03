#pragma once
#include "menu/submenu.h"

class PeacefulAttachmentYourVehicleToTheirVehicleMenu : public Submenu {
public:
	static PeacefulAttachmentYourVehicleToTheirVehicleMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	PeacefulAttachmentYourVehicleToTheirVehicleMenu() : Submenu() {}
	~PeacefulAttachmentYourVehicleToTheirVehicleMenu();
};

namespace PeacefulAttachmentYourVehicleToTheirVehicleMenuVars
{
	struct Vars {

	};
}