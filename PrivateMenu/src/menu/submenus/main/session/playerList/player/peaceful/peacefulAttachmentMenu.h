#pragma once
#include "menu/submenu.h"

class PeacefulAttachmentMenu : public Submenu {
public:
	static PeacefulAttachmentMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	PeacefulAttachmentMenu() : Submenu() {}
	~PeacefulAttachmentMenu();
};

namespace PeacefulAttachmentMenuVars
{
	struct Vars {

	};
}