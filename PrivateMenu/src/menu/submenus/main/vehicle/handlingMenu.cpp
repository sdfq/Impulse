#include "stdafx.h"
#include "handlingMenu.h"
#include "handling/bikeHandlingMenu.h"
#include "handling/boatHandlingMenu.h"
#include "handling/flyingHandlingMenu.h"
#include "handling/loadHandlingDataMenu.h"
#include "../vehicleMenu.h"

using namespace HandlingMenuVars;

namespace HandlingMenuVars {
	Vars vars;

	CHandlingData* GetData() {
		static CHandlingData hd;
		CHandlingData* data = ReClass::GetWorld()->LocalPed->m_playerVehicle->m_handlingData;
		return data == nullptr ? &hd : data;
	}

	void SaveHandling(String fileName) {
		ofstream i(fileName);

		CHandlingData* data = ReClass::GetWorld()->LocalPed->m_playerVehicle->m_handlingData;

		json jsonOb = {
			{
				"Physical",{
					{
						"vecCentreOfMassOffset",{
							{ "x", data->vecCentreOfMassOffset.x },
		{ "y", data->vecCentreOfMassOffset.y },
		{ "z", data->vecCentreOfMassOffset.z }
		}
					},

					{
						"vecInertiaMultiplier",{
							{ "x", data->vecInertiaMultiplier.x },
		{ "y", data->vecInertiaMultiplier.y },
		{ "z", data->vecInertiaMultiplier.z }
		}
					},

		{ "fMass", data->fMass }
		}
			},
			{
				"Transmission",{
					{ "fDriveBiasFront", data->fDriveBiasFront },
		{ "fDriveInertia", data->fDriveInertia },
		{ "nInitialDriveGears", data->nInitialDriveGears },
		{ "fClutchChangeRateScaleUpShift", data->fClutchChangeRateScaleUpShift },
		{ "fClutchChangeRateScaleDownShift", data->fClutchChangeRateScaleDownShift },
		{ "fInitialDriveForce", data->fInitialDriveForce },
		{ "fBrakeForce", data->fBrakeForce },
		{ "fHandBrakeForce", data->fHandBrakeForce },
		{ "fSteeringLock", data->fSteeringLock }
		}
			},
			{
				"Traction",{
					{ "fTractionCurveMax", data->fTractionCurveMax },
		{ "fTractionSpringDeltaMax", data->fTractionSpringDeltaMax },
		{ "fLowSpeedTractionLossMult", data->fLowSpeedTractionLossMult },
		{ "fTractionLossMult", data->fTractionLossMult }
		}
			},
			{
				"Suspension",{
					{ "fSuspensionForce", data->fSuspensionForce },
		{ "fSuspensionCompDamp", data->fSuspensionCompDamp },
		{ "fSuspensionReboundDamp", data->fSuspensionReboundDamp },
		{ "fSuspensionUpperLimit", data->fSuspensionUpperLimit },
		{ "fSuspensionLowerLimit", data->fSuspensionLowerLimit },
		{ "fAntiRollBarForce", data->fAntiRollBarForce }
		}
			},
			{
				"Damage",{
					{ "fCollisionDamageMult", data->fCollisionDamageMult },
		{ "fWeaponDamageMult", data->fWeaponDamageMult },
		{ "fDeformationDamageMult", data->fDeformationDamageMult },
		{ "fEngineDamageMult", data->fEngineDamageMult },
		{ "fPetrolTankVolume", data->fPetrolTankVolume },
		{ "fOilVolume", data->fOilVolume }
		}
			}
		};

		i << setw(4) << jsonOb;
		i.close();
	}
}

void HandlingMenu::Init() {
	setParentSubmenu<VehicleMenu>();
	setName("Vehicle handling", true, true);

	addOption(ButtonOption("~c~Not in a vehicle")
		.addRequirement([] {return !GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addTooltip("Not in a vehicle").addTranslation());
	
	addOption(ButtonOption("Save handling data")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addFunction([] {
		if (!GetLocalPlayer().m_isInVehicle) {
			GetRenderer()->NotifyBottom("Not in a vehicle");
			return;
		}
		GetMenuInput()->AddToQueue([] {
			string temp;
			if (GetMenuInput()->Text("Name", temp, 2, 15)) {
				String file = va("%s/%s.json", GetConfig()->GetHandlingPath(), temp.c_str());
				if (GetConfig()->DoesFileExist(file)) {
					GetRenderer()->NotifyBottom("A save with that name already exists. Try again.");
				} else SaveHandling(file);
			}});
	})
		.addHotkey().addTranslation()
		.addTooltip("Save the current handling data"));
	
	addOption(SubmenuOption("Load handling data")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addSubmenu<LoadHandlingDataMenu>()
		.addTooltip("Load handling data").addTranslation());
	
	addOption(NumberOption<float>(SCROLL, "Advanced suspension")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addNumber(vars.suspensionVal, "%.2f", 0.01f).addMin(-100.0f).addMax(1000.0f).setScrollSpeed(10)
		.addFunction([&] { ReClass::GetWorld()->LocalPed->m_playerVehicle->m_visualSuspension = -vars.suspensionVal; })
		.addOnUpdate([&] {vars.suspensionVal = -ReClass::GetWorld()->LocalPed->m_playerVehicle->m_visualSuspension; })
		.addTooltip("Edit the visual suspension").addTranslation());
	
	/*addOption(NumberOption<int>(SCROLL, "Wheel height")
		.addRequirement([] { return GetLocalPlayer().m_isInVehicle && ReClass::GetWorld()->LocalPed->m_playerVehicle->m_vehicleDrawHandler->m_vehicleStreamRenderGfx; })
		.addNumber(vars.wheelHeightVal, "%d", 1).addMin(0).addMax(255).setScrollSpeed(10)
		.addFunction([&] { ReClass::GetWorld()->LocalPed->m_playerVehicle->m_vehicleDrawHandler->m_vehicleStreamRenderGfx->m_tireSize = (BYTE)vars.wheelHeightVal; })
		.addOnUpdate([] { if(ReClass::GetWorld()->LocalPed->m_playerVehicle->m_vehicleDrawHandler->m_vehicleStreamRenderGfx) vars.wheelHeightVal = (int)ReClass::GetWorld()->LocalPed->m_playerVehicle->m_vehicleDrawHandler->m_vehicleStreamRenderGfx->m_tireSize; })
		.addTooltip("Set the wheel height").addTranslation());*/

	addOption(NumberOption<int>(SCROLL, "Wheel size")
		.addRequirement([] { return GetLocalPlayer().m_isInVehicle && VEHICLE::GetVehicleModVariation(GetLocalPlayer().m_vehicle, 23) && GetAuth()->IsVIP(); })
		.addNumber(vars.wheelHeightVal, "%d", 1).addMin(-1000).addMax(1000).setScrollSpeed(10)
		.addFunction([&] { ReClass::GetWorld()->LocalPed->m_playerVehicle->m_vehicleDrawHandler->m_vehicleStreamRender->TireSize = (BYTE)vars.wheelHeightVal; })
		.addOnUpdate([] {if (VEHICLE::GetVehicleModVariation(GetLocalPlayer().m_vehicle, 23)) { vars.wheelHeightVal = (int)ReClass::GetWorld()->LocalPed->m_playerVehicle->m_vehicleDrawHandler->m_vehicleStreamRender->TireSize; }})
		.addTooltip("Set the wheel size").addTranslation());

	/*addOption(NumberOption<float>(SCROLL, "Wheel width")
		.addRequirement([] { return GetLocalPlayer().m_isInVehicle && ReClass::GetWorld()->LocalPed->m_playerVehicle->m_vehicleDrawHandler->m_vehicleStreamRenderGfx; })
		.addNumber(vars.wheelWidthVal, "%.2f", 0.1f).addMin(-1000).addMax(1000).setScrollSpeed(100)
		.addFunction([&] { ReClass::GetWorld()->LocalPed->m_playerVehicle->m_vehicleDrawHandler->m_vehicleStreamRenderGfx->m_tireWidth = vars.wheelWidthVal; })
		.addOnUpdate([] { if (ReClass::GetWorld()->LocalPed->m_playerVehicle->m_vehicleDrawHandler->m_vehicleStreamRender) vars.wheelWidthVal = ReClass::GetWorld()->LocalPed->m_playerVehicle->m_vehicleDrawHandler->m_vehicleStreamRenderGfx->m_tireWidth; })
		.addTooltip("Set the wheel width").addTranslation());*/
	
	addOption(NumberOption<float>(SCROLL, "Wheel width")
		.addRequirement([] { return GetLocalPlayer().m_isInVehicle && ReClass::GetWorld()->LocalPed->m_playerVehicle->m_vehicleDrawHandler->m_vehicleStreamRender && GetAuth()->IsVIP(); })
		.addNumber(vars.wheelWidthVal, "%.2f", 0.1f).addMin(-1000).addMax(1000).setScrollSpeed(10)
		.addFunction([&] { ReClass::GetWorld()->LocalPed->m_playerVehicle->m_vehicleDrawHandler->m_vehicleStreamRender->m_tireWidth = vars.wheelWidthVal; })
		.addOnUpdate([] { if(ReClass::GetWorld()->LocalPed->m_playerVehicle->m_vehicleDrawHandler->m_vehicleStreamRender) vars.wheelWidthVal = ReClass::GetWorld()->LocalPed->m_playerVehicle->m_vehicleDrawHandler->m_vehicleStreamRender->m_tireWidth; })
		.addTooltip("Set the wheel width").addTranslation());
	
	addOption(BreakOption("Sub-handling data").addTranslation()
		.addRequirement([] { return GetLocalPlayer().m_isInVehicle && (vars.inBike || vars.inBoat || vars.inPlane) && GetAuth()->IsVIP(); }));

	addOption(SubmenuOption("Bike sub-handling data")
		.addRequirement([] { return GetLocalPlayer().m_isInVehicle && vars.inBike && GetAuth()->IsVIP(); })
		.addTooltip("Bike sub-handling data").addHotkey()
		.addSubmenu<BikeHandlingMenu>().addTranslation());

	addOption(SubmenuOption("Flying sub-handling data")
		.addRequirement([] { return GetLocalPlayer().m_isInVehicle && vars.inPlane && GetAuth()->IsVIP(); })
		.addTooltip("Flying sub-handling data").addHotkey()
		.addSubmenu<FlyingHandlingMenu>().addTranslation());

	addOption(SubmenuOption("Boat sub-handling data")
		.addRequirement([] { return GetLocalPlayer().m_isInVehicle && vars.inBoat && GetAuth()->IsVIP(); })
		.addTooltip("Boat sub-handling data").addHotkey()
		.addSubmenu<BoatHandlingMenu>().addTranslation());

	addOption(BreakOption("Physical").addTranslation()
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); }));

	addOption(NumberOption<float>(SCROLL, "Mass")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->fMass, "%.2f", 1); })
		.addMin(-FLT_MAX).addMax(FLT_MAX)
		.addTooltip("Vehicle mass").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Center of mass offset X")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->vecCentreOfMassOffset.x, "%.2f", 1); })
		.addMin(-10).addMax(10)
		.addTooltip("Center of mass offset X").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Center of mass offset Y")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->vecCentreOfMassOffset.y, "%.2f", 1); })
		.addMin(-10).addMax(10)
		.addTooltip("Center of mass offset Y").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Center of mass offset Z")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->vecCentreOfMassOffset.z, "%.2f", 1); })
		.addMin(-10).addMax(10)
		.addTooltip("Center of mass offset Z").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Inertia multiplier X")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->vecInertiaMultiplier.x, "%.2f", 1); })
		.addMin(-10).addMax(10)
		.addTooltip("Inertia multiplier X").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Inertia multiplier Y")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->vecInertiaMultiplier.y, "%.2f", 1); })
		.addMin(-10).addMax(10)
		.addTooltip("Inertia multiplier Y").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Inertia multiplier Z")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->vecInertiaMultiplier.z, "%.2f", 1); })
		.addMin(-10).addMax(10)
		.addTooltip("Inertia multiplier Z").addTranslation());

	addOption(BreakOption("Transmission").addTranslation()
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); }));

	addOption(NumberOption<float>(SCROLL, "Driven wheels")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addMin(0).addMax(1)
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->fDriveBiasFront, "%.2f", 0.1f); })
		.addTooltip("0 = RWD, 0.5 = 4WD, 1 = FWD").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Drive inertia")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addMin(0).addMax(10)
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->fDriveInertia, "%.2f", 0.1f); })
		.addTooltip("Affects how fast the engine will rev").addTranslation());

	addOption(NumberOption<int>(SCROLL, "Gears")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addNumber(vars.gears, "%d", 1)
		.addFunction([] {GetData()->nInitialDriveGears = (unsigned char)vars.gears; })
		.addMin(0).addMax(255)
		.addTooltip("Amount of gears").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Up shift speed multiplier")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->fClutchChangeRateScaleUpShift, "%.2f", 0.1f); })
		.addTooltip("Clutch up shift speed multiplier").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Down shift speed multiplier")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->fClutchChangeRateScaleDownShift, "%.2f", 0.1f); })
		.addTooltip("Clutch down shift speed multiplier").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Drive force")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addMin(0).addMax(100)
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->fInitialDriveForce, "%.2f", 0.1f); })
		.addTooltip("Drive force").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Brake force")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addMin(0).addMax(100)
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->fBrakeForce, "%.2f", 0.1f); })
		.addTooltip("Brake force").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Handbrake force")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addMin(0).addMax(100)
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->fHandBrakeForce, "%.2f", 0.1f); })
		.addTooltip("Handbrake force").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Max steering angle")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addMin(0).addMax(2)
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->fSteeringLock, "%.2f", 0.01f); })
		.addTooltip("Max steering angle").addTranslation());

	addOption(BreakOption("Traction").addTranslation()
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); }));

	addOption(NumberOption<float>(SCROLL, "Tire surface friction")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addMin(0).addMax(100)
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->fTractionCurveMax, "%.2f", 0.1f); })
		.addTooltip("Tire surface friction").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Traction loss ground distance")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addMin(-10).addMax(100)
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->fTractionSpringDeltaMax, "%.2f", 0.1f); })
		.addTooltip("Traction loss ground distance").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Traction reduction at low speed")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addMin(0).addMax(1)
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->fLowSpeedTractionLossMult, "%.2f", 0.05f); })
		.addTooltip("Traction reduction at low speed").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Traction loss multiplier")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addMin(0).addMax(1)
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->fTractionLossMult, "%.2f", 0.05f); })
		.addTooltip("Traction loss multiplier").addTranslation());

	addOption(BreakOption("Suspension").addTranslation()
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); }));

	addOption(NumberOption<float>(SCROLL, "Force")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->fSuspensionForce, "%.2f", 0.1f); })
		.addTooltip("Suspension force").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Compression damping")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->fSuspensionCompDamp, "%.2f", 0.1f); })
		.addTooltip("Suspension compression damping").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Rebound damping")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->fSuspensionReboundDamp, "%.2f", 0.1f); })
		.addTooltip("Suspension rebound damping").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Upper limit")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->fSuspensionUpperLimit, "%.2f", 0.1f); })
		.addTooltip("Suspension upper limit").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Lower limit")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->fSuspensionLowerLimit, "%.2f", 0.1f); })
		.addTooltip("Suspension lower limit").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Anti rollbar force")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->fAntiRollBarForce, "%.2f", 0.1f); })
		.addTooltip("Anti rollbar force").addTranslation());

	addOption(BreakOption("Damage").addTranslation()
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); }));

	addOption(NumberOption<float>(SCROLL, "Collision damage multiplier")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addMin(0)
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->fCollisionDamageMult, "%.2f", 1); })
		.addTooltip("Collision damage multiplier").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Weapon damage multiplier")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addMin(0)
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->fWeaponDamageMult, "%.2f", 1); })
		.addTooltip("Weapon damage multiplier").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Deformation damage multiplier")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; })
		.addMin(0)
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->fDeformationDamageMult, "%.2f", 1); })
		.addTooltip("Deformation damage multiplier").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Engine damage multiplier")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addMin(0)
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->fEngineDamageMult, "%.2f", 1); })
		.addTooltip("Engine damage multiplier").addTranslation());

	addOption(BreakOption("Info")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle; }).addTranslation());

	addOption(NumberOption<float>(SCROLL, "Petrol volume")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addMin(0)
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->fPetrolTankVolume, "%.2f", 1); })
		.addTooltip("Petrol volume").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Oil volume")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addMin(0)
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(GetData()->fOilVolume, "%.2f", 1); })
		.addTooltip("Oil volume").addTranslation());

	addOption(NumberOption<int32_t>(SCROLL, "Vehicle value")
		.addRequirement([] {return GetLocalPlayer().m_isInVehicle && GetAuth()->IsVIP(); })
		.addOnUpdate([](NumberOption<int32_t>* option) {option->addNumber(GetData()->nMonetaryValue, "%d", 0); })
		.addTooltip("Vehicle value").addTranslation());
}

/*Update once when submenu is opened*/
void HandlingMenu::UpdateOnce() {}

/*Update while submenu is active*/
void HandlingMenu::Update() {
	static int TIMER;

	if (!GetLocalPlayer().m_isInVehicle) {
		GetMenu()->ResetCurrentOption();
		return;
	}

	Utils::DoTimedFunction(&TIMER, 250, [&] { vars.gears = GetData()->nInitialDriveGears; });

	Hash hash = ENTITY::GetEntityModel(GetLocalPlayer().m_vehicle);
	vars.inBike = VEHICLE::IsThisModelABicycle(hash) || VEHICLE::IsThisModelABike(hash);
	vars.inBoat = VEHICLE::IsThisModelABoat(hash) || VEHICLE::_IsThisModelAnEmergencyBoat(hash);
	vars.inPlane = VEHICLE::IsThisModelAHeli(hash) || VEHICLE::IsThisModelAPlane(hash);
}

/*Background update*/
void HandlingMenu::FeatureUpdate() {

}

/*Singleton*/
HandlingMenu* _instance;
HandlingMenu* HandlingMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new HandlingMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
HandlingMenu::~HandlingMenu() { delete _instance; }