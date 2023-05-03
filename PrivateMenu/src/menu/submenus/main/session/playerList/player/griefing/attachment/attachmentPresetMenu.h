#pragma once
#include "menu/submenu.h"

class AttachmentPresetMenu : public Submenu {
public:
	static AttachmentPresetMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	AttachmentPresetMenu() : Submenu() {}
	~AttachmentPresetMenu();
};

namespace AttachmentPresetMenuVars
{
	struct Vars {

	};
}