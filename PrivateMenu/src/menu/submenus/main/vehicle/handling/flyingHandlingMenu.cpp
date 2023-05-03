#include "stdafx.h"
#include "flyingHandlingMenu.h"
#include "../handlingMenu.h"

using namespace FlyingHandlingMenuVars;

namespace FlyingHandlingMenuVars {
}

void FlyingHandlingMenu::Init() {
	setParentSubmenu<HandlingMenu>();
	setName("Flying handling", true, true);
}

/*Update once when submenu is opened*/
void FlyingHandlingMenu::UpdateOnce() {}

/*Update while submenu is active*/
void FlyingHandlingMenu::Update() {
	clearOptions();

	Hash hash = ENTITY::GetEntityModel(GetLocalPlayer().m_vehicle);
	if (!GetLocalPlayer().m_isInVehicle || !(VEHICLE::IsThisModelAHeli(hash) || VEHICLE::IsThisModelAPlane(hash))) {
		GetMenu()->ResetCurrentOption();
		addOption(ButtonOption("~c~Not in a vehicle").addTranslation()
			.addTooltip("Not in a vehicle"));
		return;
	}

	CFlyingHandlingData *data = &ReClass::GetWorld()->LocalPed->m_playerVehicle->m_handlingData->SubHandlingData->SubHandlingData->FlyingHandlingData;

	addOption(NumberOption<float>(SCROLL, "Thrust").addTranslation()
		.addNumber(data->fThrust, "%.4f", 0.1f)
		.addTooltip("Vehicle thrust"));

	addOption(NumberOption<float>(SCROLL, "Thrust falloff").addTranslation()
		.addNumber(data->fThrustFallOff, "%.4f", 0.1f)
		.addTooltip("Vehicle thrust falloff"));

	addOption(NumberOption<float>(SCROLL, "Thrust vectoring").addTranslation()
		.addNumber(data->fThrustVectoring, "%.4f", 0.1f)
		.addTooltip("Vehicle thrust vectoring"));

	addOption(BreakOption("Movement").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Rudder multiplier").addTranslation()
		.addNumber(data->fSideSlipMult, "%.4f", 0.1f)
		.addTooltip("Rudder multiplier"));

	addOption(NumberOption<float>(SCROLL, "Yaw multiplier").addTranslation()
		.addNumber(data->fYawMult, "%.4f", 0.1f)
		.addTooltip("Yaw multiplier"));

	addOption(NumberOption<float>(SCROLL, "Yaw stabilise multiplier").addTranslation()
		.addNumber(data->fYawStabilise, "%.4f", 0.1f)
		.addTooltip("Yaw stabilise multiplier"));

	addOption(NumberOption<float>(SCROLL, "Roll multiplier").addTranslation()
		.addNumber(data->fRollMult, "%.4f", 0.1f)
		.addTooltip("Roll multiplier"));

	addOption(NumberOption<float>(SCROLL, "Roll stabilise multiplier").addTranslation()
		.addNumber(data->fRollStabilise, "%.4f", 0.1f)
		.addTooltip("Roll stabilise multiplier"));

	addOption(NumberOption<float>(SCROLL, "Pitch multiplier").addTranslation()
		.addNumber(data->fPitchMult, "%.4f", 0.1f)
		.addTooltip("Pitch multiplier"));

	addOption(NumberOption<float>(SCROLL, "Pitch stabilise multiplier").addTranslation()
		.addNumber(data->fPitchStabilise, "%.4f", 0.1f)
		.addTooltip("Pitch stabilise multiplier"));

	addOption(NumberOption<float>(SCROLL, "Base lift").addTranslation()
		.addNumber(data->fFormLiftMult, "%.4f", 0.1f)
		.addTooltip("Base lift"));

	addOption(NumberOption<float>(SCROLL, "Wing attack angle lift").addTranslation()
		.addNumber(data->fAttackLiftMult, "%.4f", 0.1f)
		.addTooltip("Wing attack angle lift"));

	addOption(NumberOption<float>(SCROLL, "Wing attack angle dive").addTranslation()
		.addNumber(data->fAttackDiveMult, "%.4f", 0.1f)
		.addTooltip("Wing attack angle dive"));

	addOption(NumberOption<float>(SCROLL, "Engine off glide multiplayer").addTranslation()
		.addNumber(data->fEngineOffGlideMulti, "%.4f", 0.1f)
		.addTooltip("Glide multiplier when engine is off"));

	addOption(BreakOption("Resistance").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Wind influence").addTranslation()
		.addNumber(data->fWindMult, "%.4f", 0.1f)
		.addTooltip("Wind influence"));

	addOption(NumberOption<float>(SCROLL, "Move resistance").addTranslation()
		.addNumber(data->fMoveRes, "%.4f", 0.1f)
		.addTooltip("Move resistance"));

	addOption(NumberOption<float>(SCROLL, "Turn resistance X").addTranslation()
		.addNumber(data->vecTurnRes.x, "%.4f", 0.1f)
		.addTooltip("Turn resistance X"));

	addOption(NumberOption<float>(SCROLL, "Turn resistance Y").addTranslation()
		.addNumber(data->vecTurnRes.y, "%.4f", 0.1f)
		.addTooltip("Turn resistance Y"));

	addOption(NumberOption<float>(SCROLL, "Turn resistance Z").addTranslation()
		.addNumber(data->vecTurnRes.z, "%.4f", 0.1f)
		.addTooltip("Turn resistance z"));

	addOption(NumberOption<float>(SCROLL, "Speed resistance X").addTranslation()
		.addNumber(data->vecSpeedRes.x, "%.4f", 0.1f)
		.addTooltip("Speed resistance X"));

	addOption(NumberOption<float>(SCROLL, "Speed resistance Y").addTranslation()
		.addNumber(data->vecSpeedRes.y, "%.4f", 0.1f)
		.addTooltip("Speed resistance Y"));

	addOption(NumberOption<float>(SCROLL, "Speed resistance Z").addTranslation()
		.addNumber(data->vecSpeedRes.z, "%.4f", 0.1f)
		.addTooltip("Speed resistance z"));

	addOption(BreakOption("Turbulence"));

	addOption(NumberOption<float>(SCROLL, "Maximum turbulence magnitude").addTranslation()
		.addNumber(data->fTurublenceMagnitudeMax, "%.4f", 0.1f)
		.addTooltip("Maximum turbulence magnitude"));

	addOption(NumberOption<float>(SCROLL, "Vertical turbulence force").addTranslation()
		.addNumber(data->fTurublenceForceMulti, "%.4f", 0.1f)
		.addTooltip("Vertical turbulence force"));

	addOption(NumberOption<float>(SCROLL, "Y axis turbulence force").addTranslation()
		.addNumber(data->fTurublenceRollTorqueMulti, "%.4f", 0.1f)
		.addTooltip("Y axis turbulence force"));

	addOption(NumberOption<float>(SCROLL, "X acis turbulence force").addTranslation()
		.addNumber(data->fTurublencePitchTorqueMulti, "%.4f", 0.1f)
		.addTooltip("X acis turbulence force"));

	addOption(BreakOption("Gear").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Gear down drag").addTranslation()
		.addNumber(data->fGearDownDragV, "%.4f", 0.1f)
		.addTooltip("Gear down drag"));

	addOption(NumberOption<float>(SCROLL, "Gear down lift").addTranslation()
		.addNumber(data->fGearDownLiftMult, "%.4f", 0.1f)
		.addTooltip("Gear down lift"));

	addOption(BreakOption("Ground").addTranslation());

	addOption(NumberOption<float>(SCROLL, "On ground speed boost peak").addTranslation()
		.addNumber(data->fOnGroundYawBoostSpeedPeak, "%.4f", 0.1f)
		.addTooltip("On ground speed boost peak"));

	addOption(NumberOption<float>(SCROLL, "On ground speed boost cap").addTranslation()
		.addNumber(data->fOnGroundYawBoostSpeedCap, "%.4f", 0.1f)
		.addTooltip("On ground speed boost cap"));

	addOption(BreakOption("Noise").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Noise factor from plane damage").addTranslation()
		.addNumber(data->fBodyDamageControlEffectMult, "%.4f", 0.1f)
		.addTooltip("Noise factor from plane damage"));

	addOption(NumberOption<float>(SCROLL, "Noise factor from flying skills").addTranslation()
		.addNumber(data->fInputSensitivityForDifficulty, "%.4f", 0.1f)
		.addTooltip("Noise factor from flying skills"));
}

/*Background update*/
void FlyingHandlingMenu::FeatureUpdate() {}

/*Singleton*/
FlyingHandlingMenu* _instance;
FlyingHandlingMenu* FlyingHandlingMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new FlyingHandlingMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
FlyingHandlingMenu::~FlyingHandlingMenu() { delete _instance; }