#include "stdafx.h"
#include "boatHandlingMenu.h"
#include "../handlingMenu.h"

using namespace BoatHandlingMenuVars;

namespace BoatHandlingMenuVars {
}

void BoatHandlingMenu::Init() {
	setParentSubmenu<HandlingMenu>();
	setName("Boat handling", true, true);
}

/*Update once when submenu is opened*/
void BoatHandlingMenu::UpdateOnce() {}

/*Update while submenu is active*/
void BoatHandlingMenu::Update() {
	clearOptions();

	Hash hash = ENTITY::GetEntityModel(GetLocalPlayer().m_vehicle);
	if (!GetLocalPlayer().m_isInVehicle || !(VEHICLE::_IsThisModelAnEmergencyBoat(hash) || VEHICLE::IsThisModelABoat(hash))) {
		GetMenu()->ResetCurrentOption();
		addOption(ButtonOption("~c~Not in a boat").addTranslation()
			.addTooltip("Not in a boat"));
		return;
	}

	CBoatHandlingData *data = &ReClass::GetWorld()->LocalPed->m_playerVehicle->m_handlingData->SubHandlingData->SubHandlingData->BoatHandlingData;

	addOption(NumberOption<float>(SCROLL, "Box front multiplier").addTranslation()
		.addNumber(data->fBoxFrontMult, "%.4f", 0.1f)
		.addTooltip("Box front multiplier"));

	addOption(NumberOption<float>(SCROLL, "Box rear multiplier").addTranslation()
		.addNumber(data->fBoxRearMult, "%.4f", 0.1f)
		.addTooltip("Box rear multiplier"));

	addOption(NumberOption<float>(SCROLL, "Box side multiplier").addTranslation()
		.addNumber(data->fBoxSideMult, "%.4f", 0.1f)
		.addTooltip("Box side multiplier"));

	addOption(NumberOption<float>(SCROLL, "Sample top").addTranslation()
		.addNumber(data->fSampleTop, "%.4f", 0.1f)
		.addTooltip("Sample top"));

	addOption(NumberOption<float>(SCROLL, "Sample bottom").addTranslation()
		.addNumber(data->fSampleBottom, "%.4f", 0.1f)
		.addTooltip("Sample bottom"));

	addOption(BreakOption("Aquaplane").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Aquaplane force").addTranslation()
		.addNumber(data->fAquaplaneForce, "%.4f", 0.1f)
		.addTooltip("Aquaplane force"));

	addOption(NumberOption<float>(SCROLL, "Aquaplane push water multiplier").addTranslation()
		.addNumber(data->fAquaplanePushWaterMult, "%.4f", 0.1f)
		.addTooltip("Aquaplane push water multiplier"));

	addOption(NumberOption<float>(SCROLL, "Aquaplane push water cap").addTranslation()
		.addNumber(data->fAquaplanePushWaterCap, "%.4f", 0.1f)
		.addTooltip("Aquaplane push water cap"));

	addOption(NumberOption<float>(SCROLL, "Aquaplane push water apply").addTranslation()
		.addNumber(data->fAquaplanePushWaterApply, "%.4f", 0.1f)
		.addTooltip("Aquaplane push water apply"));

	addOption(NumberOption<float>(SCROLL, "Keelsphere size").addTranslation()
		.addNumber(data->fKeelSphereSize, "%.4f", 0.1f)
		.addTooltip("Keelsphere size"));

	addOption(NumberOption<float>(SCROLL, "Propellor radius").addTranslation()
		.addNumber(data->fPropRadius, "%.4f", 0.1f)
		.addTooltip("Propellor radius"));

	addOption(NumberOption<float>(SCROLL, "Impeller offset").addTranslation()
		.addNumber(data->fImpellerOffset, "%.4f", 0.1f)
		.addTooltip("Impeller offset"));

	addOption(NumberOption<float>(SCROLL, "Impeller force").addTranslation()
		.addNumber(data->fImpellerForceMult, "%.4f", 0.1f)
		.addTooltip("Impeller force"));

	addOption(NumberOption<float>(SCROLL, "Prow raise multiplier").addTranslation()
		.addNumber(data->fProwRaiseMult, "%.4f", 0.1f)
		.addTooltip("Prow raise multiplier"));

	addOption(BreakOption("Rudder").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Rudder force").addTranslation()
		.addNumber(data->fRudderForce, "%.4f", 0.1f)
		.addTooltip("Rudder force"));

	addOption(NumberOption<float>(SCROLL, "Rudder offset submerge").addTranslation()
		.addNumber(data->fRudderOffsetSubmerge, "%.4f", 0.1f)
		.addTooltip("Rudder offset submerge"));

	addOption(NumberOption<float>(SCROLL, "Rudder offset force").addTranslation()
		.addNumber(data->fRudderOffsetForce, "%.4f", 0.1f)
		.addTooltip("Rudder offset force"));

	addOption(NumberOption<float>(SCROLL, "Rudder offset force Z multiplier").addTranslation()
		.addNumber(data->fRudderOffsetForceZMult, "%.4f", 0.1f)
		.addTooltip("Rudder offset force Z multiplier"));

	addOption(BreakOption("Resistance").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Drag coefficient").addTranslation()
		.addNumber(data->fDragCoefficient, "%.4f", 0.1f)
		.addTooltip("Drag coefficient"));

	addOption(NumberOption<float>(SCROLL, "Turn resistance X").addTranslation()
		.addNumber(data->vecTurnResistance.x, "%.4f", 0.1f)
		.addTooltip("Turn resistance X"));

	addOption(NumberOption<float>(SCROLL, "Turn resistance Y").addTranslation()
		.addNumber(data->vecTurnResistance.y, "%.4f", 0.1f)
		.addTooltip("Turn resistance Y"));

	addOption(NumberOption<float>(SCROLL, "Turn resistance Z").addTranslation()
		.addNumber(data->vecTurnResistance.z, "%.4f", 0.1f)
		.addTooltip("Turn resistance z"));

	addOption(NumberOption<float>(SCROLL, "Move resistance X").addTranslation()
		.addNumber(data->vecMoveResistance.x, "%.4f", 0.1f)
		.addTooltip("Move resistance X"));

	addOption(NumberOption<float>(SCROLL, "Move resistance Y").addTranslation()
		.addNumber(data->vecMoveResistance.y, "%.4f", 0.1f)
		.addTooltip("Move resistance Y"));

	addOption(NumberOption<float>(SCROLL, "Move resistance Z").addTranslation()
		.addNumber(data->vecMoveResistance.z, "%.4f", 0.1f)
		.addTooltip("Move resistance z"));

	addOption(BreakOption("Misc").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Wave audio multiplier").addTranslation()
		.addNumber(data->fWaveAudioMult, "%.4f", 0.1f)
		.addTooltip("Wave audio multiplier"));

	addOption(NumberOption<float>(SCROLL, "Look L_R cam height").addTranslation()
		.addNumber(data->fLook_L_R_CamHeight, "%.4f", 0.1f)
		.addTooltip("Look L_R cam height"));

	addOption(NumberOption<float>(SCROLL, "Dinghy sphere buoy constant").addTranslation()
		.addNumber(data->fDinghySphereBuoyConst, "%.4f", 0.1f)
		.addTooltip("Dinghy sphere buoy constant"));
}

/*Background update*/
void BoatHandlingMenu::FeatureUpdate() {}

/*Singleton*/
BoatHandlingMenu* _instance;
BoatHandlingMenu* BoatHandlingMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new BoatHandlingMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
BoatHandlingMenu::~BoatHandlingMenu() { delete _instance; }