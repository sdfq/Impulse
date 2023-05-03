#include "stdafx.h"
#include "vehicleWeaponsMenu.h"
#include "../vehicleMenu.h"

using namespace VehicleWeaponsMenuVars;

namespace VehicleWeaponsMenuVars {
	Vars vars;

	ScrollStruct<Hash> bulletTypes[] = {
		TranslationString("RPG", true), 0xb1ca77b1,
		TranslationString("Firework", true), 0x7f7497e5,
		//TranslationString("Red Laser", true), 0x5d6660ab,
		//TranslationString("Green Laser", true), 0xeffd014b,
		TranslationString("Tank", true), 0x73f7c04b,
		TranslationString("Space Rocket", true), 0xf8a3939f,
		TranslationString("Plane Rocket", true), 0xcf0896e0,
		TranslationString("Snowball", true), 0x787F0BB,
		TranslationString("Flare", true), 0x497FACC3,
	};

	void VehicleWeapons()
	{
		if (!GetLocalPlayer().m_isInVehicle)return;
		Vector3 ModelSizeMin;
		Vector3 ModelSizeMax;
		MISC::GetModelDimensions(ENTITY::GetEntityModel(GetLocalPlayer().m_vehicle), &ModelSizeMin, &ModelSizeMax);

		Vector3 VehL = ENTITY::GetOffsetFromEntityInWorldCoords(GetLocalPlayer().m_vehicle, -(ModelSizeMax.x + 0.25f), ModelSizeMax.y + 1.25f, 0.1f);
		Vector3 VehR = ENTITY::GetOffsetFromEntityInWorldCoords(GetLocalPlayer().m_vehicle, (ModelSizeMax.x + 0.25f), ModelSizeMax.y + 1.25f, 0.1f);
		Vector3 VehLEnd = ENTITY::GetOffsetFromEntityInWorldCoords(GetLocalPlayer().m_vehicle, -ModelSizeMax.x, ModelSizeMax.y + 100.0f, 0.1f);
		Vector3 VehREnd = ENTITY::GetOffsetFromEntityInWorldCoords(GetLocalPlayer().m_vehicle, ModelSizeMax.x, ModelSizeMax.y + 100.0f, 0.1f);

		if ((vars.controllerKey && PAD::IsDisabledControlPressed(0, vars.key)) || KeyJustDown(vars.key)){
			MISC::ShootSingleBulletBetweenCoords(VehL.x, VehL.y, VehL.z, VehLEnd.x, VehLEnd.y, VehLEnd.z, 5000, false, bulletTypes[vars.bullettype].m_result, vars.responsibility ? GetLocalPlayer().m_ped : 0, false, false, vars.bulletspeed);
			MISC::ShootSingleBulletBetweenCoords(VehR.x, VehR.y, VehR.z, VehREnd.x, VehREnd.y, VehREnd.z, 5000, false, bulletTypes[vars.bullettype].m_result, vars.responsibility ? GetLocalPlayer().m_ped : 0, false, false, vars.bulletspeed);
		}

		if (vars.guided) {
			GetRenderer()->DrawLine(VehL.x, VehL.y, VehL.z, VehLEnd.x, VehLEnd.y, VehLEnd.z, { 255, 0, 0, 255 });
			GetRenderer()->DrawLine(VehR.x, VehR.y, VehR.z, VehREnd.x, VehREnd.y, VehREnd.z, { 255, 0, 0, 255 });
		}
	}
}

void VehicleWeaponsMenu::Init() {
	setParentSubmenu<VehicleMenu>();
	setName("Vehicle weapons", true, true);

	addOption(ScrollOption<Hash>(SCROLL, "Bullet type")
		.addScroll(vars.bullettype, 0, NUMOF(bulletTypes) - 1, bulletTypes)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Bullet type"));

	addOption(NumberOption<int>(SCROLL, "Bullet speed")
		.addNumber(vars.bulletspeed, "%d", 1).addMin(0).addMax(10000)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Bullet speed"));

	addOption(ToggleOption("Guided")
		.addToggle(vars.guided)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Show where you're aiming"));

	addOption(ToggleOption("Take responsibility")
		.addToggle(vars.responsibility)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Show who shot the bullet"));

	//addOption(KeyOption("Key")
	//	.addKey(vars.key)
	//	.canBeSaved().addHotkey().addTranslation()
	//	.addTooltip("Set the key"));

	addOption(KeyOption("Vehicle weapons key")
		.addKeyWithControllerSupport(vars.key, vars.controllerKey)
		.canBeSaved().addHotkey().addTranslation()
		.addTooltip("Set the key"));

	addOption(ToggleOption("Enabled")
		.addToggle(vars.enabled)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Enable vehicle bullets"));
}

/*Update once when submenu is opened*/
void VehicleWeaponsMenu::UpdateOnce() {}

/*Update while submenu is active*/
void VehicleWeaponsMenu::Update() {}

/*Background update*/
void VehicleWeaponsMenu::FeatureUpdate()
{
	if (vars.enabled)VehicleWeapons();
}

/*Singleton*/
VehicleWeaponsMenu* _instance;
VehicleWeaponsMenu* VehicleWeaponsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new VehicleWeaponsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
VehicleWeaponsMenu::~VehicleWeaponsMenu() { delete _instance; }