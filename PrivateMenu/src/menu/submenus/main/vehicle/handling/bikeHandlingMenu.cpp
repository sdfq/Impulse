#include "stdafx.h"
#include "bikeHandlingMenu.h"
#include "../handlingMenu.h"

using namespace BikeHandlingMenuVars;

namespace BikeHandlingMenuVars {
}

void BikeHandlingMenu::Init() {
	setParentSubmenu<HandlingMenu>();
	setName("Bike handling", true, true);
}

/*Update once when submenu is opened*/
void BikeHandlingMenu::UpdateOnce() {}

/*Update while submenu is active*/
void BikeHandlingMenu::Update() {
	clearOptions();

	Hash hash = ENTITY::GetEntityModel(GetLocalPlayer().m_vehicle);
	if (!GetLocalPlayer().m_isInVehicle || !(VEHICLE::IsThisModelABicycle(hash) || VEHICLE::IsThisModelABike(hash))) {
		GetMenu()->ResetCurrentOption();
		addOption(ButtonOption("~c~Not in a vehicle").addTranslation()
			.addTooltip("Not in a vehicle"));
		return;
	}

	CBikeHandlingData *data = &ReClass::GetWorld()->LocalPed->m_playerVehicle->m_handlingData->SubHandlingData->SubHandlingData->BikeHandlingData;

	if (VEHICLE::IsThisModelABicycle(hash))
		addOption(NumberOption<float>(SCROLL, "Jump force").addTranslation()
			.addNumber(data->fJumpForce, "%.4f", 0.1f)
			.addTooltip("Max bank angle"));

	addOption(NumberOption<float>(SCROLL, "Lean forward COM multiplier").addTranslation()
		.addNumber(data->fLeanFwdCOMMult, "%.4f", 0.1f)
		.addTooltip("Lean forward COM multiplier"));

	addOption(NumberOption<float>(SCROLL, "Lean forward force").addTranslation()
		.addNumber(data->fLeanFwdForceMult, "%.4f", 0.1f)
		.addTooltip("Lean forward force"));

	addOption(NumberOption<float>(SCROLL, "Lean backward COM multiplier").addTranslation()
		.addNumber(data->fLeanBakCOMMult, "%.4f", 0.1f)
		.addTooltip("Lean backward COM multiplier"));

	addOption(NumberOption<float>(SCROLL, "Lean backward force").addTranslation()
		.addNumber(data->fLeanBakForceMult, "%.4f", 0.1f)
		.addTooltip("Lean backward force"));

	addOption(NumberOption<float>(SCROLL, "Max bank angle").addTranslation()
		.addNumber(data->fMaxBankAngle, "%.4f", 0.1f)
		.addTooltip("Max bank angle"));

	addOption(NumberOption<float>(SCROLL, "Full animation angle").addTranslation()
		.addNumber(data->fFullAnimAngle, "%.4f", 0.1f)
		.addTooltip("Full animation angle"));

	addOption(NumberOption<float>(SCROLL, "Lean return multiplier").addTranslation()
		.addNumber(data->fDesLeanReturnFrac, "%.4f", 0.1f)
		.addTooltip("Lean return multiplier"));

	addOption(NumberOption<float>(SCROLL, "Lean stick multiplier").addTranslation()
		.addNumber(data->fStickLeanMult, "%.4f", 0.1f)
		.addTooltip("Lean stick multiplier"));

	addOption(NumberOption<float>(SCROLL, "Braking stability").addTranslation()
		.addNumber(data->fBrakingStabilityMult, "%.4f", 0.1f)
		.addTooltip("Stick lean multiplier"));

	addOption(NumberOption<float>(SCROLL, "In air steer multiplier").addTranslation()
		.addNumber(data->fInAirSteerMult, "%.4f", 0.1f)
		.addTooltip("In air steer multiplier"));

	addOption(BreakOption("Balance").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Wheelie balance point").addTranslation()
		.addNumber(data->fWheelieBalancePoint, "%.4f", 0.1f)
		.addTooltip("Wheelie balance point"));

	addOption(NumberOption<float>(SCROLL, "Stoppy balance point").addTranslation()
		.addNumber(data->fStoppieBalancePoint, "%.4f", 0.1f)
		.addTooltip("Stoppy balance point"));

	addOption(NumberOption<float>(SCROLL, "Wheelie steer multiplier").addTranslation()
		.addNumber(data->fWheelieSteerMult, "%.4f", 0.1f)
		.addTooltip("Wheelie steer multiplier"));

	addOption(NumberOption<float>(SCROLL, "Rear balance multiplier").addTranslation()
		.addNumber(data->fRearBalanceMult, "%.4f", 0.1f)
		.addTooltip("Rear balance multiplier"));

	addOption(NumberOption<float>(SCROLL, "Front balance multiplier").addTranslation()
		.addNumber(data->fFrontBalanceMult, "%.4f", 0.1f)
		.addTooltip("Front balance multiplier"));

	addOption(NumberOption<float>(SCROLL, "Standing lean angle").addTranslation()
		.addNumber(data->fBikeOnStandLeanAngle, "%.4f", 0.1f)
		.addTooltip("Standing lean angle"));

	addOption(NumberOption<float>(SCROLL, "Standing steer angle").addTranslation()
		.addNumber(data->fBikeOnStandSteerAngle, "%.4f", 0.1f)
		.addTooltip("Standing steer angle"));

	addOption(BreakOption("Friction").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Ground side friction").addTranslation()
		.addNumber(data->fBikeGroundSideFrictionMult, "%.4f", 0.1f)
		.addTooltip("Ground side friction"));

	addOption(NumberOption<float>(SCROLL, "Wheel ground side friction").addTranslation()
		.addNumber(data->fBikeWheelGroundSideFrictionMult, "%.4f", 0.1f)
		.addTooltip("Wheel ground friction"));
}

/*Background update*/
void BikeHandlingMenu::FeatureUpdate() {}

/*Singleton*/
BikeHandlingMenu* _instance;
BikeHandlingMenu* BikeHandlingMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new BikeHandlingMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
BikeHandlingMenu::~BikeHandlingMenu() { delete _instance; }