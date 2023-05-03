#include "stdafx.h"
#include "peacefulAttachmentYouToTheirVehicle.h"
#include "peacefulAttachmentMenu.h"

using namespace PeacefulAttachmentYouToTheirVehicleMenuVars;

namespace PeacefulAttachmentYouToTheirVehicleMenuVars {
	Vars vars;

	void UpdateAttachment() {
		ENTITY::AttachEntityToEntity(GetLocalPlayer().m_ped, GetSelectedPlayer().m_vehicle, -1, GetSelectedPlayer().m_attachmentMeToClientVehiclePosition.x, GetSelectedPlayer().m_attachmentMeToClientVehiclePosition.y, GetSelectedPlayer().m_attachmentMeToClientVehiclePosition.z, GetSelectedPlayer().m_attachmentMeToClientVehicleRotation.x, GetSelectedPlayer().m_attachmentMeToClientVehicleRotation.y, GetSelectedPlayer().m_attachmentMeToClientVehicleRotation.z, 1, 0, 0, 1, 2, 1);
	}
}

void PeacefulAttachmentYouToTheirVehicleMenu::Init() {
	setParentSubmenu<PeacefulAttachmentMenu>();
	setName("You to their vehicle", true, false);

	addOption(ButtonOption("Attach").addTranslation()
		.addFunction([] {
			if (GetSelectedPlayer().m_id == GetLocalPlayer().m_id) return;
			if (!GetSelectedPlayer().m_isInVehicle) {
				GetRenderer()->NotifyMap("Client isn't in a vehicle.");
				return;
			}

			ENTITY::AttachEntityToEntity(GetLocalPlayer().m_ped, GetSelectedPlayer().m_vehicle, -1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1, 0, 0, 1, 2, 1);
			GetSelectedPlayer().m_attachmentMeToClientVehiclePosition = Vector3(0, 0, 0);
			GetSelectedPlayer().m_attachmentMeToClientVehicleRotation = Vector3(0, 0, 0);
			GetSelectedPlayer().m_attachmentMeToClientVehicleAttachedTo = true;
		}));

	addOption(ButtonOption("Detach").addTranslation()
		.addFunction([] {
			ENTITY::DetachEntity(GetLocalPlayer().m_ped, true, true);
			GetSelectedPlayer().m_attachmentMeToClientVehicleAttachedTo = false;
			GetSelectedPlayer().m_attachmentMeToClientVehiclePosition = Vector3(0, 0, 0);
			GetSelectedPlayer().m_attachmentMeToClientVehicleRotation = Vector3(0, 0, 0);
		}));

	addOption(NumberOption<float>(SCROLL, "Precision").addTranslation()
		.addNumber(GetSelectedPlayer().m_attachmentMeToClientVehiclePrecision, "%.2f", 0.01f).addMin(0.0f).addMax(1000.f).setScrollSpeed(10)
		.addRequirement([] { return ENTITY::IsEntityAttachedToEntity(GetLocalPlayer().m_ped, GetSelectedPlayer().m_vehicle) && GetSelectedPlayer().m_attachmentMeToClientVehicleAttachedTo;  })
		.addTooltip("Precision"));

	addOption(NumberOption<float>(SCROLL, "Position - Horizontal (X)").addTranslation()
		.addOnUpdate([](NumberOption<float>* option) { option->addNumber(GetSelectedPlayer().m_attachmentMeToClientVehiclePosition.x, "%.3f", GetSelectedPlayer().m_attachmentMeToClientVehiclePrecision).addMin(-100.f).addMax(100.f).setScrollSpeed(10); })
		.addFunction(UpdateAttachment)
		.addRequirement([] { return ENTITY::IsEntityAttachedToEntity(GetLocalPlayer().m_ped, GetSelectedPlayer().m_vehicle) && GetSelectedPlayer().m_attachmentMeToClientVehicleAttachedTo;  })
		.addTooltip("Position X"));

	addOption(NumberOption<float>(SCROLL, "Position - Vertical (Y)").addTranslation()
		.addOnUpdate([](NumberOption<float>* option) { option->addNumber(GetSelectedPlayer().m_attachmentMeToClientVehiclePosition.y, "%.3f", GetSelectedPlayer().m_attachmentMeToClientVehiclePrecision).addMin(-100.f).addMax(100.f).setScrollSpeed(10); })
		.addFunction(UpdateAttachment)
		.addRequirement([] { return ENTITY::IsEntityAttachedToEntity(GetLocalPlayer().m_ped, GetSelectedPlayer().m_vehicle) && GetSelectedPlayer().m_attachmentMeToClientVehicleAttachedTo;  })
		.addTooltip("Position Y"));

	addOption(NumberOption<float>(SCROLL, "Position - Height (Z)").addTranslation()
		.addOnUpdate([](NumberOption<float>* option) { option->addNumber(GetSelectedPlayer().m_attachmentMeToClientVehiclePosition.z, "%.3f", GetSelectedPlayer().m_attachmentMeToClientVehiclePrecision).addMin(-100.f).addMax(100.f).setScrollSpeed(10); })
		.addFunction(UpdateAttachment)
		.addRequirement([] { return ENTITY::IsEntityAttachedToEntity(GetLocalPlayer().m_ped, GetSelectedPlayer().m_vehicle) && GetSelectedPlayer().m_attachmentMeToClientVehicleAttachedTo;  })
		.addTooltip("Position Z"));

	addOption(NumberOption<float>(SCROLL, "Rotation - Pitch (Vertical)").addTranslation()
		.addOnUpdate([](NumberOption<float>* option) { option->addNumber(GetSelectedPlayer().m_attachmentMeToClientVehicleRotation.x, "%.3f", GetSelectedPlayer().m_attachmentMeToClientVehiclePrecision).addMin(-100.f).addMax(100.f).setScrollSpeed(10); })
		.addFunction(UpdateAttachment)
		.addRequirement([] { return ENTITY::IsEntityAttachedToEntity(GetLocalPlayer().m_ped, GetSelectedPlayer().m_vehicle) && GetSelectedPlayer().m_attachmentMeToClientVehicleAttachedTo;  })
		.addTooltip("Rotation pitch"));

	addOption(NumberOption<float>(SCROLL, "Rotation - Roll (Side)").addTranslation()
		.addOnUpdate([](NumberOption<float>* option) { option->addNumber(GetSelectedPlayer().m_attachmentMeToClientVehicleRotation.y, "%.3f", GetSelectedPlayer().m_attachmentMeToClientVehiclePrecision).addMin(-100.f).addMax(100.f).setScrollSpeed(10); })
		.addFunction(UpdateAttachment)
		.addRequirement([] { return ENTITY::IsEntityAttachedToEntity(GetLocalPlayer().m_ped, GetSelectedPlayer().m_vehicle) && GetSelectedPlayer().m_attachmentMeToClientVehicleAttachedTo;  })
		.addTooltip("Rotation roll"));

	addOption(NumberOption<float>(SCROLL, "Rotation - Yaw (Heading)").addTranslation()
		.addOnUpdate([](NumberOption<float>* option) { option->addNumber(GetSelectedPlayer().m_attachmentMeToClientVehicleRotation.z, "%.3f", GetSelectedPlayer().m_attachmentMeToClientVehiclePrecision).addMin(-100.f).addMax(100.f).setScrollSpeed(10); })
		.addFunction(UpdateAttachment)
		.addRequirement([] { return ENTITY::IsEntityAttachedToEntity(GetLocalPlayer().m_ped, GetSelectedPlayer().m_vehicle) && GetSelectedPlayer().m_attachmentMeToClientVehicleAttachedTo;  })
		.addTooltip("Rotation yaw"));
}

/*Update once when submenu is opened*/
void PeacefulAttachmentYouToTheirVehicleMenu::UpdateOnce() {}

/*Update while submenu is active*/
void PeacefulAttachmentYouToTheirVehicleMenu::Update() {}

/*Background update*/
void PeacefulAttachmentYouToTheirVehicleMenu::FeatureUpdate() {}

/*Singleton*/
PeacefulAttachmentYouToTheirVehicleMenu* _instance;
PeacefulAttachmentYouToTheirVehicleMenu* PeacefulAttachmentYouToTheirVehicleMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new PeacefulAttachmentYouToTheirVehicleMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
PeacefulAttachmentYouToTheirVehicleMenu::~PeacefulAttachmentYouToTheirVehicleMenu() { delete _instance; }