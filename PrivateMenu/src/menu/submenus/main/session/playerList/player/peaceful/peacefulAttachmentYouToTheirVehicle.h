#pragma once
#include "menu/submenu.h"

class PeacefulAttachmentYouToTheirVehicleMenu : public Submenu {
public:
	static PeacefulAttachmentYouToTheirVehicleMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	PeacefulAttachmentYouToTheirVehicleMenu() : Submenu() {}
	~PeacefulAttachmentYouToTheirVehicleMenu();
};

namespace PeacefulAttachmentYouToTheirVehicleMenuVars
{
	struct Vars {

	};
}