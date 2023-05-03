#include "stdafx.h"
#include "attachmentMenu.h"
#include "../griefingMenu.h"
#include "attachment/attachmentFlagsMenu.h"
#include "attachment/attachmentVehiclesMenu.h"
#include "attachment/attachmentPedsMenu.h"
#include "attachment/attachmentObjectsMenu.h"
#include "attachment/attachmentPresetMenu.h"

using namespace AttachmentMenuVars;

namespace AttachmentMenuVars {
	void AttachObjectToPlayer(SPlayer& player, Hash object, int bone, float x, float y, float z, float xr, float yr, float zr) {
		GetEntityControl()->SimpleRequestModel(object);
		Object handle = OBJECT::CreateObject(object, player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 1, 1, 0);
		if (ENTITY::DoesEntityExist(handle)) {
			ENTITY::AttachEntityToEntity(handle, player.m_ped, bone, x, y, z, xr, yr, zr, 1, 0, 0, 1, 2, 1);
		}
	}

	void AttachVehicleToPlayer(SPlayer& player, Hash vehicle, int bone, float x, float y, float z, float xr, float yr, float zr) {
		GetEntityControl()->SimpleRequestModel(vehicle);
		Vehicle handle = VEHICLE::CreateVehicle(vehicle, player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 1, 1, 0, 1);
		if (ENTITY::DoesEntityExist(handle)) {
			ENTITY::AttachEntityToEntity(handle, player.m_ped, bone, x, y, z, xr, yr, zr, 1, 0, 0, 1, 2, 1);
		}
	}

	void AttachPedToPlayer(SPlayer& player, Hash ped, int bone, float x, float y, float z, float xr, float yr, float zr) {
		GetEntityControl()->SimpleRequestModel(ped);
		Ped handle = PED::CreatePed(21, ped, player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 1, 1, 0);
		if (ENTITY::DoesEntityExist(handle)) {
			ENTITY::AttachEntityToEntity(handle, player.m_ped, bone, x, y, z, xr, yr, zr, 1, 0, 0, 1, 2, 1);
		}
	}
}

void AttachmentMenu::Init() {
	setParentSubmenu<GriefingMenu>();
	setName("Attachments", true, false);

	addOption(SubmenuOption("Presets")
		.addSubmenu<AttachmentPresetMenu>()
		.addTooltip("Attach presets"));

	addOption(SubmenuOption("Flags")
		.addSubmenu<AttachmentFlagsMenu>()
		.addTooltip("Attach flags"));

	addOption(SubmenuOption("Vehicles")
		.addSubmenu<AttachmentVehiclesMenu>()
		.addTooltip("Attach vehicles"));

	addOption(SubmenuOption("Peds")
		.addSubmenu<AttachmentPedsMenu>()
		.addTooltip("Attach peds"));

	addOption(SubmenuOption("Objects")
		.addSubmenu<AttachmentObjectsMenu>()
		.addTooltip("Attach objects"));
}

/*Update once when submenu is opened*/
void AttachmentMenu::UpdateOnce() {}

/*Update while submenu is active*/
void AttachmentMenu::Update() {}

/*Background update*/
void AttachmentMenu::FeatureUpdate() {}

/*Singleton*/
AttachmentMenu* _instance;
AttachmentMenu* AttachmentMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new AttachmentMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
AttachmentMenu::~AttachmentMenu() { delete _instance; }