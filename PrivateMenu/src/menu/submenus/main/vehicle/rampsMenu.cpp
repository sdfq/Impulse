#include "stdafx.h"
#include "rampsMenu.h"
#include "../vehicleMenu.h"

using namespace RampsMenuVars;

namespace RampsMenuVars {
	Vars vars;

	Object CreateAttachedRamp(Hash model, int pos) {
		GetEntityControl()->SimpleRequestModel(model);
		Vector3 min, max; MISC::GetModelDimensions(model, &min, &max);
		Vector3 dim = { max.x - min.x, max.y - min.y, max.z - min.z };
		Vector3 dima = { dim.x / 2, dim.y / 2, dim.z / 2 };

		Vector3 c = ENTITY::GetEntityCoords(GetLocalPlayer().m_vehicle, true);

		Object ramp = OBJECT::CreateObject(model, c.x, c.y, c.z, true, false, false);

		switch (pos) {
			case 0:ENTITY::AttachEntityToEntity(ramp, GetLocalPlayer().m_vehicle, 0, /**/ 0, dim.y, -0.5, /**/ 0, 0, 180, true, true, true, false, 2, true); break;
			case 1:ENTITY::AttachEntityToEntity(ramp, GetLocalPlayer().m_vehicle, 0, /**/ 0, (-1)*dim.y, -0.5, /**/ 0, 0, 0, true, true, true, false, 2, true); break;
			case 2:ENTITY::AttachEntityToEntity(ramp, GetLocalPlayer().m_vehicle, 0, /**/ (-1)*dim.x, 0, -0.5, /**/ 0, 0, 270, true, true, true, false, 2, true); break;
			case 3:ENTITY::AttachEntityToEntity(ramp, GetLocalPlayer().m_vehicle, 0, /**/ dim.x, 0, -0.5, /**/ 0, 0, 90, true, true, true, false, 2, true); break;
		}

		return ramp;
	}

	void Attach(RampsMenu* instance, int ramp) {
		if (!GetLocalPlayer().m_isInVehicle) {
			GetRenderer()->NotifyBottom(instance->getString("Not in a vehicle"));
			return;
		}
		
		char* propName = va("PROP_MP_RAMP_0%i", ramp);

		if (vars.front) CreateAttachedRamp(Utils::GetHashKey(propName), 0);
		if (vars.rear) CreateAttachedRamp(Utils::GetHashKey(propName), 1);
		if (vars.left)CreateAttachedRamp(Utils::GetHashKey(propName), 2);
		if (vars.right) CreateAttachedRamp(Utils::GetHashKey(propName), 3);
	}

	void Delete(RampsMenu* instance) {
		if (!GetLocalPlayer().m_isInVehicle) {
			GetRenderer()->NotifyBottom(instance->getString("Not in a vehicle"));
			return;
		}

		Vector3 myCoords = GetLocalPlayer().m_coordinates;

		Hash ramps[] = { 0xB157C9E4, 0xF4F1511E, 0x93948E5E };
		for (int i = 0; i < 3; i++) {
			int Counter = 0;
		search:
			Object ramp = OBJECT::GetClosestObjectOfType(myCoords.x, myCoords.y, myCoords.z, 20, ramps[i], false, false, false);
			GetEntityControl()->SimpleRequestControl(GetLocalPlayer().m_vehicle);
			if (ENTITY::DoesEntityExist(ramp) && ENTITY::IsEntityAttachedToEntity(ramp, GetLocalPlayer().m_vehicle)) {
				ENTITY::DeleteEntity(&ramp);
				Counter++;
				if (Counter < 20) {
					goto search;
				}
			}
		}
	}
}

void RampsMenu::Init() {
	setParentSubmenu<VehicleMenu>();
	setName("Ramps", true, true);

	addString("Not in a vehicle");

	addOption(NumberOption<int>(SCROLL, "Type")
		.addNumber(vars.type, "%d", 1).addMin(0).addMax(2)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Ramp type"));

	addOption(ToggleOption("Front")
		.addToggle(vars.front)
		.addHotkey().addTranslation()
		.addTooltip("Front side ramp"));

	addOption(ToggleOption("Rear")
		.addToggle(vars.rear)
		.addHotkey().addTranslation()
		.addTooltip("Rear side ramp"));

	addOption(ToggleOption("Right")
		.addToggle(vars.right)
		.addHotkey().addTranslation()
		.addTooltip("Right side ramp"));

	addOption(ToggleOption("Left")
		.addToggle(vars.left)
		.addHotkey().addTranslation()
		.addTooltip("Left side ramp"));

	addOption(ButtonOption("Attach")
		.addFunction([this] {Attach(this, vars.type + 1); })
		.addHotkey().addTranslation()
		.addTooltip("Attach selected ramps"));

	addOption(ButtonOption("Delete")
		.addFunction([this] {Delete(this); })
		.addHotkey().addTranslation()
		.addTooltip("Delete selected ramps"));

}

/*Update once when submenu is opened*/
void RampsMenu::UpdateOnce() {}

/*Update while submenu is active*/
void RampsMenu::Update() {}

/*Background update*/
void RampsMenu::FeatureUpdate() {}

/*Singleton*/
RampsMenu* _instance;
RampsMenu* RampsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new RampsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
RampsMenu::~RampsMenu() { delete _instance; }