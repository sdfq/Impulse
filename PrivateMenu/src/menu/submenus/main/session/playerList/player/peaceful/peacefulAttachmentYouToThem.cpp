#include "stdafx.h"
#include "peacefulAttachmentYouToThem.h"
#include "peacefulAttachmentMenu.h"

using namespace PeacefulAttachmentYouToThemMenuVars;

namespace PeacefulAttachmentYouToThemMenuVars {
	Vars vars;

	void UpdateAttachment() {
		ENTITY::AttachEntityToEntity(GetLocalPlayer().m_ped, GetSelectedPlayer().m_ped, -1, GetSelectedPlayer().m_attachmentToMeClientPosition.x, GetSelectedPlayer().m_attachmentToMeClientPosition.y, GetSelectedPlayer().m_attachmentToMeClientPosition.z, GetSelectedPlayer().m_attachmentToMeClientRotation.x, GetSelectedPlayer().m_attachmentToMeClientRotation.y, GetSelectedPlayer().m_attachmentToMeClientRotation.z, 1, 0, 0, 1, 2, 1);
	}
}

void PeacefulAttachmentYouToThemMenu::Init() {
	setParentSubmenu<PeacefulAttachmentMenu>();
	setName("You to them", true, false);

	addOption(ButtonOption("Attach").addTranslation()
		.addFunction([] {
		if (GetSelectedPlayer().m_id == GetLocalPlayer().m_id) return;
		ENTITY::AttachEntityToEntity(GetLocalPlayer().m_ped, GetSelectedPlayer().m_ped, -1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1, 0, 0, 1, 2, 1);
		GetSelectedPlayer().m_attachmentToMeClientPosition = Vector3(0, 0, 0);
		GetSelectedPlayer().m_attachmentToMeClientRotation = Vector3(0, 0, 0);
		GetSelectedPlayer().m_attachmentToMeClientAttachedTo = true;
	}).addTooltip("Attach"));

	addOption(ButtonOption("Detach").addTranslation()
		.addFunction([] {
		ENTITY::DetachEntity(GetLocalPlayer().m_ped, true, true);
		GetSelectedPlayer().m_attachmentToMeClientAttachedTo = false;
		GetSelectedPlayer().m_attachmentToMeClientPosition = Vector3(0, 0, 0);
		GetSelectedPlayer().m_attachmentToMeClientRotation = Vector3(0, 0, 0);
	}).addTooltip("Detach"));

	addOption(NumberOption<float>(SCROLL, "Precision").addTranslation()
		.addNumber(GetSelectedPlayer().m_attachmentToMeClientPrecision, "%.2f", 0.01f).addMin(0.0f).addMax(1000.f).setScrollSpeed(10)
		.addRequirement([] { return ENTITY::IsEntityAttachedToEntity(GetLocalPlayer().m_ped, GetSelectedPlayer().m_ped) && GetSelectedPlayer().m_attachmentToMeClientAttachedTo;  })
		.addTooltip("Precision"));

	addOption(NumberOption<float>(SCROLL, "Position - Horizontal (X)").addTranslation()
		.addOnUpdate([](NumberOption<float>* option) { option->addNumber(GetSelectedPlayer().m_attachmentToMeClientPosition.x, "%.3f", GetSelectedPlayer().m_attachmentToMeClientPrecision).addMin(-100.f).addMax(100.f).setScrollSpeed(10); })
		.addFunction(UpdateAttachment)
		.addRequirement([] { return ENTITY::IsEntityAttachedToEntity(GetLocalPlayer().m_ped, GetSelectedPlayer().m_ped) && GetSelectedPlayer().m_attachmentToMeClientAttachedTo;  })
		.addTooltip("Position X"));

	addOption(NumberOption<float>(SCROLL, "Position - Vertical (Y)").addTranslation()
		.addOnUpdate([](NumberOption<float>* option) { option->addNumber(GetSelectedPlayer().m_attachmentToMeClientPosition.y, "%.3f", GetSelectedPlayer().m_attachmentToMeClientPrecision).addMin(-100.f).addMax(100.f).setScrollSpeed(10); })
		.addFunction(UpdateAttachment)
		.addRequirement([] { return ENTITY::IsEntityAttachedToEntity(GetLocalPlayer().m_ped, GetSelectedPlayer().m_ped) && GetSelectedPlayer().m_attachmentToMeClientAttachedTo;  })
		.addTooltip("Position Y"));

	addOption(NumberOption<float>(SCROLL, "Position - Height (Z)").addTranslation()
		.addOnUpdate([](NumberOption<float>* option) { option->addNumber(GetSelectedPlayer().m_attachmentToMeClientPosition.z, "%.3f", GetSelectedPlayer().m_attachmentToMeClientPrecision).addMin(-100.f).addMax(100.f).setScrollSpeed(10); })
		.addFunction(UpdateAttachment)
		.addRequirement([] { return ENTITY::IsEntityAttachedToEntity(GetLocalPlayer().m_ped, GetSelectedPlayer().m_ped) && GetSelectedPlayer().m_attachmentToMeClientAttachedTo;  })
		.addTooltip("Position Z"));

	addOption(NumberOption<float>(SCROLL, "Rotation - Pitch (Vertical)").addTranslation()
		.addOnUpdate([](NumberOption<float>* option) { option->addNumber(GetSelectedPlayer().m_attachmentToMeClientRotation.x, "%.3f", GetSelectedPlayer().m_attachmentToMeClientPrecision).addMin(-100.f).addMax(100.f).setScrollSpeed(10); })
		.addFunction(UpdateAttachment)
		.addRequirement([] { return ENTITY::IsEntityAttachedToEntity(GetLocalPlayer().m_ped, GetSelectedPlayer().m_ped) && GetSelectedPlayer().m_attachmentToMeClientAttachedTo;  })
		.addTooltip("Rotation pitch"));

	addOption(NumberOption<float>(SCROLL, "Rotation - Roll (Side)").addTranslation()
		.addOnUpdate([](NumberOption<float>* option) { option->addNumber(GetSelectedPlayer().m_attachmentToMeClientRotation.y, "%.3f", GetSelectedPlayer().m_attachmentToMeClientPrecision).addMin(-100.f).addMax(100.f).setScrollSpeed(10); })
		.addFunction(UpdateAttachment)
		.addRequirement([] { return ENTITY::IsEntityAttachedToEntity(GetLocalPlayer().m_ped, GetSelectedPlayer().m_ped) && GetSelectedPlayer().m_attachmentToMeClientAttachedTo;  })
		.addTooltip("Rotation roll"));

	addOption(NumberOption<float>(SCROLL, "Rotation - Yaw (Heading)").addTranslation()
		.addOnUpdate([](NumberOption<float>* option) { option->addNumber(GetSelectedPlayer().m_attachmentToMeClientRotation.z, "%.3f", GetSelectedPlayer().m_attachmentToMeClientPrecision).addMin(-100.f).addMax(100.f).setScrollSpeed(10); })
		.addFunction(UpdateAttachment)
		.addRequirement([] { return ENTITY::IsEntityAttachedToEntity(GetLocalPlayer().m_ped, GetSelectedPlayer().m_ped) && GetSelectedPlayer().m_attachmentToMeClientAttachedTo;  })
		.addTooltip("Rotation yaw"));
}

/*Update once when submenu is opened*/
void PeacefulAttachmentYouToThemMenu::UpdateOnce() {}

/*Update while submenu is active*/
void PeacefulAttachmentYouToThemMenu::Update() {

}

/*Background update*/
void PeacefulAttachmentYouToThemMenu::FeatureUpdate() {}

/*Singleton*/
PeacefulAttachmentYouToThemMenu* _instance;
PeacefulAttachmentYouToThemMenu* PeacefulAttachmentYouToThemMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new PeacefulAttachmentYouToThemMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
PeacefulAttachmentYouToThemMenu::~PeacefulAttachmentYouToThemMenu() { delete _instance; }