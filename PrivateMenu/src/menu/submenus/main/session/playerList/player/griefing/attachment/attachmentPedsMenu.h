#pragma once
#include "menu/submenu.h"

class AttachmentPedsMenu : public Submenu {
public:
	static AttachmentPedsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	AttachmentPedsMenu() : Submenu() {}
	~AttachmentPedsMenu();
};

namespace AttachmentPedsMenuVars
{
	struct Vars {

	};
}