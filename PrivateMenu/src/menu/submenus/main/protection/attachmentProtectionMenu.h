#pragma once
#include "menu/submenu.h"

class AttachmentProtectionMenu : public Submenu {
public:
	static AttachmentProtectionMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	AttachmentProtectionMenu() : Submenu() {}
	~AttachmentProtectionMenu();
};

namespace AttachmentProtectionMenuVars
{
	struct Vars {
		bool redirectObjects;
		bool protectObjects;
		bool notifyObjects;
		bool entityAttachment;
	};
	extern Vars vars;
}