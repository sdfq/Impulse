#pragma once
#include "menu/submenu.h"

class AttachmentObjectsMenu : public Submenu {
public:
	static AttachmentObjectsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	AttachmentObjectsMenu() : Submenu() {}
	~AttachmentObjectsMenu();
};

namespace AttachmentObjectsMenuVars
{
	struct Vars {

	};
}