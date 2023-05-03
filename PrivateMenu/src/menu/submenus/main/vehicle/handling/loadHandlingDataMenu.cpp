#include "stdafx.h"
#include "loadHandlingDataMenu.h"
#include "../handlingMenu.h"

using namespace LoadHandlingDataMenuVars;

namespace LoadHandlingDataMenuVars {
	vector<string> m_handlingFiles;

	shared_ptr<ButtonOption> addHandlingOption;

	void LoadHandling(String filename) {
		ifstream i(va("%s/%s.json", GetConfig()->GetHandlingPath(), filename));
		json jsonOb;
		i >> jsonOb;

		if (!GetLocalPlayer().m_isInVehicle) {
			return;
		}
		CHandlingData* data = ReClass::GetWorld()->LocalPed->m_playerVehicle->m_handlingData;
		json physical = jsonGet<json>(jsonOb, "Physical", {});

		json vecCentreOfMassOffset = jsonGet<json>(physical, "vecCentreOfMassOffset", {});
		json vecInertiaMultiplier = jsonGet<json>(physical, "vecInertiaMultiplier", {});
		data->vecCentreOfMassOffset.x = jsonGet<float>(vecCentreOfMassOffset, "x", data->vecCentreOfMassOffset.x);
		data->vecCentreOfMassOffset.y = jsonGet<float>(vecCentreOfMassOffset, "y", data->vecCentreOfMassOffset.y);
		data->vecCentreOfMassOffset.z = jsonGet<float>(vecCentreOfMassOffset, "z", data->vecCentreOfMassOffset.z);
		data->vecInertiaMultiplier.x = jsonGet<float>(vecInertiaMultiplier, "x", data->vecInertiaMultiplier.x);
		data->vecInertiaMultiplier.y = jsonGet<float>(vecInertiaMultiplier, "y", data->vecInertiaMultiplier.y);
		data->vecInertiaMultiplier.z = jsonGet<float>(vecInertiaMultiplier, "z", data->vecInertiaMultiplier.z);
		data->fMass = jsonGet<float>(physical, "fMass");

		json transmission = jsonGet<json>(jsonOb, "Transmission", {});

		data->fDriveBiasFront = jsonGet<float>(transmission, "fDriveBiasFront", data->fDriveBiasFront);
		data->fDriveInertia = jsonGet<float>(transmission, "fDriveInertia", data->fDriveInertia);
		data->nInitialDriveGears = jsonGet<float>(transmission, "nInitialDriveGears", data->nInitialDriveGears);
		data->fClutchChangeRateScaleUpShift = jsonGet<float>(transmission, "fClutchChangeRateScaleUpShift", data->fClutchChangeRateScaleUpShift);
		data->fClutchChangeRateScaleDownShift = jsonGet<float>(transmission, "fClutchChangeRateScaleDownShift", data->fClutchChangeRateScaleDownShift);
		data->fInitialDriveForce = jsonGet<float>(transmission, "fInitialDriveForce", data->fInitialDriveForce);
		data->fBrakeForce = jsonGet<float>(transmission, "fBrakeForce", data->fBrakeForce);
		data->fHandBrakeForce = jsonGet<float>(transmission, "fHandBrakeForce", data->fHandBrakeForce);
		data->fSteeringLock = jsonGet<float>(transmission, "fSteeringLock", data->fSteeringLock);

		json traction = jsonGet<json>(jsonOb, "Traction", {});

		data->fTractionCurveMax = jsonGet<float>(traction, "fTractionCurveMax", data->fTractionCurveMax);
		data->fTractionSpringDeltaMax = jsonGet<float>(traction, "fTractionSpringDeltaMax", data->fTractionSpringDeltaMax);
		data->fLowSpeedTractionLossMult = jsonGet<float>(traction, "fLowSpeedTractionLossMult", data->fLowSpeedTractionLossMult);
		data->fTractionLossMult = jsonGet<float>(traction, "fTractionLossMult", data->fTractionLossMult);

		json suspension = jsonGet<json>(jsonOb, "Suspension", {});

		data->fSuspensionForce = jsonGet<float>(suspension, "fSuspensionForce", data->fSuspensionForce);
		data->fSuspensionCompDamp = jsonGet<float>(suspension, "fSuspensionCompDamp", data->fSuspensionCompDamp);
		data->fSuspensionReboundDamp = jsonGet<float>(suspension, "fSuspensionReboundDamp", data->fSuspensionReboundDamp);
		data->fSuspensionUpperLimit = jsonGet<float>(suspension, "fSuspensionUpperLimit", data->fSuspensionUpperLimit);
		data->fSuspensionLowerLimit = jsonGet<float>(suspension, "fSuspensionLowerLimit", data->fSuspensionLowerLimit);
		data->fAntiRollBarForce = jsonGet<float>(suspension, "fAntiRollBarForce", data->fAntiRollBarForce);

		json damage = jsonGet<json>(jsonOb, "Damage", {});

		data->fCollisionDamageMult = jsonGet<float>(damage, "fCollisionDamageMult", data->fCollisionDamageMult);
		data->fWeaponDamageMult = jsonGet<float>(damage, "fWeaponDamageMult", data->fWeaponDamageMult);
		data->fDeformationDamageMult = jsonGet<float>(damage, "fDeformationDamageMult", data->fDeformationDamageMult);
		data->fEngineDamageMult = jsonGet<float>(damage, "fEngineDamageMult", data->fEngineDamageMult);
		data->fPetrolTankVolume = jsonGet<float>(damage, "fPetrolTankVolume", data->fPetrolTankVolume);
		data->fOilVolume = jsonGet<float>(damage, "fOilVolume", data->fOilVolume);
	}
}

void LoadHandlingDataMenu::Init() {
	setParentSubmenu<HandlingMenu>();
	setName("Load handling data", true, false);

	addHandlingOption = addOption(ButtonOption("~c~Add handling data to ./Documents/Impulse/Handling")
		.addTooltip("Add handling data to ./Documents/Impulse/Handling").addTranslation());
}

/*Update once when submenu is opened*/
void LoadHandlingDataMenu::UpdateOnce() {}

/*Update while submenu is active*/
void LoadHandlingDataMenu::Update() {
	static int TIMER;
	static bool shouldUpdate = false;
	Utils::DoTimedFunction(&TIMER, 2500, [] {shouldUpdate = true; });
	if (shouldUpdate) {
		clearOptions();
		GetConfig()->GetFilesFromDirectory(m_handlingFiles, GetConfig()->GetHandlingPath(), ".json");
		if (!m_handlingFiles.empty()) {
			for (string& handling : m_handlingFiles) {
				addOption(ButtonOption(handling.c_str())
					//.hasNoTranslation()
					.addFunction([&] {LoadHandling(handling.c_str()); })
					.addTooltip(handling.c_str()));
			}
		} else {
			addOption(addHandlingOption);
		}
		shouldUpdate = false;
	}
}

/*Background update*/
void LoadHandlingDataMenu::FeatureUpdate() {}

/*Singleton*/
LoadHandlingDataMenu* _instance;
LoadHandlingDataMenu* LoadHandlingDataMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new LoadHandlingDataMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
LoadHandlingDataMenu::~LoadHandlingDataMenu() { delete _instance; }