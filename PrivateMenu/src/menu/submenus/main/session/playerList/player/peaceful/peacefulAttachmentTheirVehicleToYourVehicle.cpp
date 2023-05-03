#include "stdafx.h"
#include "peacefulAttachmentTheirVehicleToYourVehicle.h"
#include "peacefulAttachmentMenu.h"

using namespace PeacefulAttachmentTheirVehicleToYourVehicleMenuVars;

namespace PeacefulAttachmentTheirVehicleToYourVehicleMenuVars {
	Vars vars;

	ScrollStruct<int> attachVehiclePositions[] = {
		TranslationString("Front", true), 0,
		TranslationString("Back", true), 1,
		TranslationString("Left", true), 2,
		TranslationString("Right", true), 3,
		TranslationString("Top", true), 4
	};

	void Attach() {
		if (!GetSelectedPlayer().m_isInVehicle) {
			GetRenderer()->NotifyMap("Client is not in vehicle.");
			return;
		}

		if (GetLocalPlayer().m_isInVehicle) {
			GetEntityControl()->RequestControl("[ATVTYV]", GetSelectedPlayer().m_vehicle, [](Entity entity) {
				Vector3 Min, Max;
				MISC::GetModelDimensions(ENTITY::GetEntityModel(GetLocalPlayer().m_vehicle), &Min, &Max);
				float VehWidth = Max.x * 3;
				float VehLength = Max.y * 3;
				float Vehheight = Max.z * 3;
				ENTITY::DetachEntity(entity, 1, 1);
				static float x, y, z;

				switch (GetSelectedPlayer().m_attachmentTheirVehicleToMyVehicleAttachmentType) {
				case 4:
					x = 0;
					y = 0;
					z = Max.z + GetSelectedPlayer().m_attachmentTheirVehicleToMyVehicleRelativeDistance;
					break;
				case 0:
					x = 0;
					y = Max.y + GetSelectedPlayer().m_attachmentTheirVehicleToMyVehicleRelativeDistance;
					z = 0;
					break;
				case 1:
					x = 0;
					y = Min.y - GetSelectedPlayer().m_attachmentTheirVehicleToMyVehicleRelativeDistance;
					z = 0;
					break;
				case 2:
					x = Min.x - GetSelectedPlayer().m_attachmentTheirVehicleToMyVehicleRelativeDistance;
					y = 0;
					z = 0;
					break;
				case 3:
					x = Max.x + GetSelectedPlayer().m_attachmentTheirVehicleToMyVehicleRelativeDistance;
					y = 0;
					z = 0;
					break;
				}

				ENTITY::AttachEntityToEntity(entity, GetLocalPlayer().m_vehicle, 0, x, y, z, 0, 0, 0, 0, 1, 1, 1, 1, 1);
				VEHICLE::SetVehicleDoorsLocked(entity, 4);
			});
		}
	}
}

void PeacefulAttachmentTheirVehicleToYourVehicleMenu::Init() {
	setParentSubmenu<PeacefulAttachmentMenu>();
	setName("Their vehicle to your vehicle", true, false);

	addOption(ScrollOption<int>(SCROLL, "Relative position").addTranslation()
		.addScroll(GetSelectedPlayer().m_attachmentTheirVehicleToMyVehicleAttachmentType, 0, NUMOF(attachVehiclePositions) - 1, attachVehiclePositions)
		.addFunction(Attach)
		.addTooltip("Relative position"));

	addOption(NumberOption<float>(SCROLL, "Relative distance").addTranslation()
		.addRequirement([] { return ENTITY::IsEntityAttachedToEntity(GetSelectedPlayer().m_vehicle, GetLocalPlayer().m_vehicle); })
		.addNumber(GetSelectedPlayer().m_attachmentTheirVehicleToMyVehicleRelativeDistance, "%.2f", 0.01f).addMin(0.0f).addMax(1000.0f).setScrollSpeed(10)
		.addFunction(Attach)
		.addTranslation().addTooltip("Relative distance"));

	addOption(ButtonOption("Attach").addTranslation()
		.addFunction(Attach)
		.addTooltip("Attach"));

	addOption(ButtonOption("Detach").addTranslation()
		.addFunction([] {
		if (ENTITY::IsEntityAttachedToEntity(GetSelectedPlayer().m_vehicle, GetLocalPlayer().m_vehicle)) {
			GetEntityControl()->RequestControl("[DTVTYV]", GetSelectedPlayer().m_vehicle, [](Entity entity) {
				ENTITY::SetEntityAsMissionEntity(entity, 1, 1);
				ENTITY::DetachEntity(entity, 1, 1);
			});
		}
	}).addTooltip("Detach"));
}

/*Update once when submenu is opened*/
void PeacefulAttachmentTheirVehicleToYourVehicleMenu::UpdateOnce() {}

/*Update while submenu is active*/
void PeacefulAttachmentTheirVehicleToYourVehicleMenu::Update() {}

/*Background update*/
void PeacefulAttachmentTheirVehicleToYourVehicleMenu::FeatureUpdate() {}

/*Singleton*/
PeacefulAttachmentTheirVehicleToYourVehicleMenu* _instance;
PeacefulAttachmentTheirVehicleToYourVehicleMenu* PeacefulAttachmentTheirVehicleToYourVehicleMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new PeacefulAttachmentTheirVehicleToYourVehicleMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
PeacefulAttachmentTheirVehicleToYourVehicleMenu::~PeacefulAttachmentTheirVehicleToYourVehicleMenu() { delete _instance; }