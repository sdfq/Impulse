#include "stdafx.h"
#include "peacefulAttachmentYourVehicleToTheirVehicle.h"
#include "peacefulAttachmentMenu.h"

using namespace PeacefulAttachmentYourVehicleToTheirVehicleMenuVars;

namespace PeacefulAttachmentYourVehicleToTheirVehicleMenuVars {
	Vars vars;

	ScrollStruct<int> attachVehiclePositions[] = {
		"Front", 0,
		"Back", 1,
		"Left", 2,
		"Right", 3,
		"Top", 4
	};

	void Attach() {
		if (!GetSelectedPlayer().m_isInVehicle) {
			GetRenderer()->NotifyMap("Client is not in vehicle.");
			return;
		}

		if (GetLocalPlayer().m_isInVehicle) {
			Vector3 Min, Max;
			MISC::GetModelDimensions(ENTITY::GetEntityModel(GetSelectedPlayer().m_vehicle), &Min, &Max);
			float VehWidth = Max.x * 3;
			float VehLength = Max.y * 3;
			float Vehheight = Max.z * 3;
			ENTITY::DetachEntity(GetLocalPlayer().m_vehicle, 1, 1);
			static float x, y, z;

			switch (GetSelectedPlayer().m_attachmentMyVehicleToTheirVehicleAttachmentType) {
			case 4:
				x = 0;
				y = 0;
				z = Max.z + GetSelectedPlayer().m_attachmentMyVehicleToTheirVehicleRelativeDistance;
				break;
			case 0:
				x = 0;
				y = Max.y + GetSelectedPlayer().m_attachmentMyVehicleToTheirVehicleRelativeDistance;
				z = 0;
				break;
			case 1:
				x = 0;
				y = Min.y - GetSelectedPlayer().m_attachmentMyVehicleToTheirVehicleRelativeDistance;
				z = 0;
				break;
			case 2:
				x = Min.x - GetSelectedPlayer().m_attachmentMyVehicleToTheirVehicleRelativeDistance;
				y = 0;
				z = 0;
				break;
			case 3:
				x = Max.x + GetSelectedPlayer().m_attachmentMyVehicleToTheirVehicleRelativeDistance;
				y = 0;
				z = 0;
				break;
			}

			ENTITY::AttachEntityToEntity(GetLocalPlayer().m_vehicle, GetSelectedPlayer().m_vehicle, 0, x, y, z, 0, 0, 0, 0, 1, 1, 1, 1, 1);
		}
	}
}

void PeacefulAttachmentYourVehicleToTheirVehicleMenu::Init() {
	setParentSubmenu<PeacefulAttachmentMenu>();
	setName("Your vehicle to their vehicle", true, false);

	addOption(ScrollOption<int>(SCROLL, "Relative position")
		.addScroll(GetSelectedPlayer().m_attachmentMyVehicleToTheirVehicleAttachmentType, 0, NUMOF(attachVehiclePositions) - 1, attachVehiclePositions)
		.addTooltip("Relative position").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Relative distance")
		.addRequirement([] { return ENTITY::IsEntityAttachedToEntity(GetLocalPlayer().m_vehicle, GetSelectedPlayer().m_vehicle); })
		.addNumber(GetSelectedPlayer().m_attachmentMyVehicleToTheirVehicleRelativeDistance, "%.2f", 0.01f).addMin(0.0f).addMax(1000.0f).setScrollSpeed(10)
		.addFunction(Attach)
		.addTooltip("Relative distance").addTranslation());

	addOption(ButtonOption("Attach")
		.addFunction(Attach).addTranslation()
		.addTooltip("Attach"));

	addOption(ButtonOption("Detach")
		.addFunction([] {
			if (ENTITY::IsEntityAttached(GetLocalPlayer().m_vehicle)) {
				ENTITY::SetEntityAsMissionEntity(GetLocalPlayer().m_vehicle, 1, 1);
				ENTITY::DetachEntity(GetLocalPlayer().m_vehicle, 1, 1);
			}
		}).addTooltip("Detach").addTranslation());
}

/*Update once when submenu is opened*/
void PeacefulAttachmentYourVehicleToTheirVehicleMenu::UpdateOnce() {}

/*Update while submenu is active*/
void PeacefulAttachmentYourVehicleToTheirVehicleMenu::Update() {}

/*Background update*/
void PeacefulAttachmentYourVehicleToTheirVehicleMenu::FeatureUpdate() {}

/*Singleton*/
PeacefulAttachmentYourVehicleToTheirVehicleMenu* _instance;
PeacefulAttachmentYourVehicleToTheirVehicleMenu* PeacefulAttachmentYourVehicleToTheirVehicleMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new PeacefulAttachmentYourVehicleToTheirVehicleMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
PeacefulAttachmentYourVehicleToTheirVehicleMenu::~PeacefulAttachmentYourVehicleToTheirVehicleMenu() { delete _instance; }