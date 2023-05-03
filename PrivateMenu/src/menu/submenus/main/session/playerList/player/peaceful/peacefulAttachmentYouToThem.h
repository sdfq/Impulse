#pragma once
#include "menu/submenu.h"

class PeacefulAttachmentYouToThemMenu : public Submenu {
public:
	static PeacefulAttachmentYouToThemMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	PeacefulAttachmentYouToThemMenu() : Submenu() {}
	~PeacefulAttachmentYouToThemMenu();
};

namespace PeacefulAttachmentYouToThemMenuVars
{
	struct Vars {

	};
}