#pragma once
#include "menu/submenu.h"

class AttachmentFlagsMenu : public Submenu {
public:
	static AttachmentFlagsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	AttachmentFlagsMenu() : Submenu() {}
	~AttachmentFlagsMenu();
};

namespace AttachmentFlagsMenuVars
{
	struct Vars {

	};
}