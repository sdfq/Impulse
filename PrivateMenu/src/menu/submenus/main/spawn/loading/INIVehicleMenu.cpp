#include "stdafx.h"
#include "INIVehicleMenu.h"
#include "../loadingMenu.h"
#include "../../spawn/spawnVehicleMenu.h"

using namespace INIVehicleMenuVars;

TranslationString strFailedToLoad("Failed to load vehicle", true, true);
namespace INIVehicleMenuVars {
	vector<string> fileNames;

	Vehicle m_lastVehSpawned;
	vector<Object> m_lastObjsSpawned;
	bool deleteLast;

	const vector<int> modTypes = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 23, 24, 26, 25, 48, 37, 27, 28, 30, 33, 34, 35, 38, 39, 45 };
	const vector<int> toggleTypes = { 17, 18, 19, 20, 21, 22 };

	void LoadINIVehicle(String name) {
		if (deleteLast) {
			for (auto& e : m_lastObjsSpawned) {
				ENTITY::SetEntityAsMissionEntity(e, 1, 1);
				ENTITY::DeleteEntity(&e);
			}
			ENTITY::SetEntityAsMissionEntity(m_lastVehSpawned, 1, 1);
			ENTITY::DeleteEntity(&m_lastVehSpawned);
		}

		char path[MAX_PATH];
		vaBuff(path, MAX_PATH, "%s/%s.ini", GetConfig()->GetVehiclesPath(), name);
		Hash model = GetConfig()->ReadInt64("Vehicle", "Model", 0, path);

		if (model != 0) {
			Vehicle veh = SpawnVehicleMenuVars::SpawnVehicle(model);
			m_lastVehSpawned = veh;
			VEHICLE::SetVehicleModKit(veh, 0);
			VEHICLE::SetVehicleWheelType(veh, GetConfig()->ReadInt("Vehicle", "WheelsType", 0, path));

			bool customTyres = GetConfig()->ReadBool("Vehicle", "CustomTyres", false, path);//NEW
			for (int i = 0; i < modTypes.size(); i++) {
				int mod = GetConfig()->ReadInt("Vehicle", va("%d", modTypes[i]), 0, path);
				VEHICLE::SetVehicleMod(veh, modTypes[i], mod, customTyres);
			}
			int HUDColor = GetConfig()->ReadInt("Vehicle", "DashColor", 0, path);
			int HUDLightsColor = GetConfig()->ReadInt("Vehicle", "DashLightColor", 0, path);
			VEHICLE::_SetVehicleDashboardColour(veh, HUDLightsColor);

			for (int i = 0; i < toggleTypes.size(); i++) {
				bool mod = GetConfig()->ReadBool("Vehicle", va("TOGGLE_%d", toggleTypes[i]), false, path);
				VEHICLE::ToggleVehicleMod(veh, toggleTypes[i], mod);
			}
			int WindowTintIndex = GetConfig()->ReadInt("Vehicle", "WindowTint", 0, path);
			bool NeonEnabled = GetConfig()->ReadBool("Vehicle", "NeonEnabled", false, path);
			int NeonR = GetConfig()->ReadInt("Vehicle", "NeonR", 0, path);
			int NeonG = GetConfig()->ReadInt("Vehicle", "NeonG", 0, path);
			int NeonB = GetConfig()->ReadInt("Vehicle", "NeonB", 0, path);
			int SmokeR = GetConfig()->ReadInt("Vehicle", "SmokeR", 0, path);
			int SmokeG = GetConfig()->ReadInt("Vehicle", "SmokeG", 0, path);
			int SmokeB = GetConfig()->ReadInt("Vehicle", "SmokeB", 0, path);
			bool BulletProof = GetConfig()->ReadBool("Vehicle", "Bulletproof", false, path);
			if (BulletProof) {
				VEHICLE::SetVehicleTyresCanBurst(veh, 0);
				VEHICLE::SetVehicleWheelsCanBreak(veh, 0);
			}
			if (NeonEnabled) {
				VEHICLE::_SetVehicleNeonLightEnabled(veh, 0, 1);
				VEHICLE::_SetVehicleNeonLightEnabled(veh, 1, 1);
				VEHICLE::_SetVehicleNeonLightEnabled(veh, 2, 1);
				VEHICLE::_SetVehicleNeonLightEnabled(veh, 3, 1);
				VEHICLE::_SetVehicleNeonLightsColour(veh, NeonR, NeonG, NeonB);
			}
			VEHICLE::SetVehicleWindowTint(veh, WindowTintIndex);
			VEHICLE::SetVehicleTyreSmokeColor(veh, SmokeR, SmokeG, SmokeB);

			int PrimaryPaintType, SecondaryPaintType, PrimaryPaintID, SecondaryPaintID;
			PrimaryPaintType = GetConfig()->ReadInt("Vehicle", "PrimaryPaintT", 0, path);
			SecondaryPaintType = GetConfig()->ReadInt("Vehicle", "SecondaryPaintT", 0, path);
			PrimaryPaintID = GetConfig()->ReadInt("Vehicle", "PrimaryPaint", 0, path);
			SecondaryPaintID = GetConfig()->ReadInt("Vehicle", "SecondaryPaint", 0, path);
			VEHICLE::SetVehicleModColor1(veh, PrimaryPaintType, PrimaryPaintID, GetConfig()->ReadInt("Vehicle", "Unknown", 0, path));
			VEHICLE::SetVehicleModColor2(veh, SecondaryPaintType, SecondaryPaintID);
			VEHICLE::SetVehicleColours(veh, PrimaryPaintID, SecondaryPaintID);
			VEHICLE::SetVehicleExtraColours(veh, GetConfig()->ReadInt("Vehicle", "Pearlescent", 0, path), GetConfig()->ReadInt("Vehicle", "WheelsColor", 0, path));
			VEHICLE::SetVehicleCustomPrimaryColour(veh, GetConfig()->ReadInt("Vehicle", "PrimaryR", 0, path), GetConfig()->ReadInt("Vehicle", "PrimaryG", 0, path), GetConfig()->ReadInt("Vehicle", "PrimaryB", 0, path));
			VEHICLE::SetVehicleCustomSecondaryColour(veh, GetConfig()->ReadInt("Vehicle", "SecondaryR", 0, path), GetConfig()->ReadInt("Vehicle", "SecondaryG", 0, path), GetConfig()->ReadInt("Vehicle", "SecondaryB", 0, path));
			VEHICLE::SetVehicleNumberPlateTextIndex(veh, GetConfig()->ReadInt("Vehicle", "PlateIndex", 0, path));
			VEHICLE::SetVehicleNumberPlateText(veh, GetConfig()->ReadString("Vehicle", "PlateText", "", path));
			for (int i = 0; i < 40; i++) {
				if (VEHICLE::DoesExtraExist(veh, i)) {
					VEHICLE::SetVehicleExtra(veh, i, GetConfig()->ReadBool("Vehicle", va("Extra_%d", i), false, path));
				}
			}

			for (int i = 0; i < 150; i++) {
				String num = va("%d", i);
				Hash model = GetConfig()->ReadInt64(num, "Model", 0, path);
				if (model > 0) {
					float x = GetConfig()->ReadFloat(num, "X", 0, path);
					float y = GetConfig()->ReadFloat(num, "Y", 0, path);
					float z = GetConfig()->ReadFloat(num, "Z", 0, path);
					float rotX = GetConfig()->ReadFloat(num, "RotX", 0, path);
					float rotY = GetConfig()->ReadFloat(num, "RotY", 0, path);
					float rotZ = GetConfig()->ReadFloat(num, "RotZ", 0, path);

					GetEntityControl()->SimpleRequestModel(model);
					Vector3 coords = GetLocalPlayer().m_coordinates;
					Object obj = OBJECT::CreateObjectNoOffset(model, coords.x, coords.y, coords.z, 1, 0, 0);
					STREAMING::SetModelAsNoLongerNeeded(obj);
					ENTITY::FreezeEntityPosition(obj, 1);
					ENTITY::AttachEntityToEntity(obj, veh, 0, x, y, z, rotX, rotY, rotZ, 1, 0, 1, 0, 2, 1);

					m_lastObjsSpawned.push_back(obj);
				}
			}
			return;
		}
		GetRenderer()->NotifyBottom(strFailedToLoad.Get());
	}
}

void INIVehicleMenu::Init() {
	setParentSubmenu<LoadingMenu>();
	setName("INI vehicle", true, false);

	addOption(ToggleOption("Delete last creation")
		.addToggle(deleteLast)
		.addTooltip("Delete the previously created INI creation"));
}

/*Update once when submenu is opened*/
void INIVehicleMenu::UpdateOnce() {}

/*Update while submenu is active*/
void INIVehicleMenu::Update() {
	static int TIMER;
	static bool shouldUpdate = false;

	Utils::DoTimedFunction(&TIMER, 2500, [] {shouldUpdate = true; });

	if (shouldUpdate) {
		clearOptionsOffset(1);
		GetConfig()->GetFilesFromDirectory(fileNames, GetConfig()->GetVehiclesPath(), ".ini");
		if (!fileNames.empty()) {
			if (fileNames.size() > 0) {
				for (auto& e : fileNames) {
					addOption(ButtonOption(e.c_str())
						.addFunction([=] { GetFiberPool()->DoJob([e] {LoadINIVehicle(e.c_str()); }); })
						.addTooltip("Spawn INI vehicle"));
				}
			}
		}
		shouldUpdate = false;
	}
}

/*Background update*/
void INIVehicleMenu::FeatureUpdate() {}

/*Singleton*/
INIVehicleMenu* _instance;
INIVehicleMenu* INIVehicleMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new INIVehicleMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
INIVehicleMenu::~INIVehicleMenu() { delete _instance; }