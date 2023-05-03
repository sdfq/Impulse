#include "stdafx.h"
#include "worldMenu.h"
#include "world/waypointMenu.h"
#include "world/pedManagerMenu.h"
#include "world/trafficManagerMenu.h"
#include "world/worldDrawablesMenu.h"
#include "world/weatherManagerMenu.h"
#include "world/VFXMenu.h"
#include "../mainMenu.h"
#include "world/blackholeMenu.h"
#include "world/vehicleBlacklistMenu.h"
#include "menu/submenus/main/world/bodyguardMenu.h"

using namespace WorldMenuVars;

namespace WorldMenuVars {
	Vars vars;

	void RequestControlOfid(Entity netid)
	{
		int tick = 0;

		while (!NETWORK::NetworkHasControlOfNetworkId(netid) && tick <= 25)
		{

			NETWORK::NetworkRequestControlOfEntity(netid);
			tick++;
		}
	}

	void Vars::RequestControlOfEnt(Entity entity)
	{
		int tick = 0;

		while (!NETWORK::NetworkHasControlOfEntity(entity) && tick <= 25)
		{
			NETWORK::NetworkRequestControlOfEntity(entity);
			tick++;
		}
		if (NETWORK::NetworkIsSessionStarted())
		{
			int netID = NETWORK::NetworkGetNetworkIdFromEntity(entity);
			RequestControlOfid(netID);
			NETWORK::SetNetworkIdCanMigrate(netID, 1);
		}
	}

	ScrollStruct<int> gravity[] = {
		TranslationString("Normal", true), 0,
		TranslationString("Low", true), 1,
		TranslationString("Lower", true), 2,
		TranslationString("Off", true), 3
	};

	ScrollStruct<Hash> turretWeapons[] = {
		TranslationString("RPG", true), 0xB1CA77B1,
		TranslationString("Minigun", true), 0x42BF8A85,
		TranslationString("Fire Extinguisher", true), 0x060EC506,
		TranslationString("Assault Shotgun", true), 0xE284C527,
		TranslationString("Snowball", true), 0x787F0BB,
		TranslationString("Railgun", true), 0x6D544C99,
		TranslationString("Air Defence", true), 0x2C082D7D
	};

	ScrollStruct<int> turretAimType[] = {
		TranslationString("Vehicles", true), 0,
		TranslationString("Players", true), 1,
		TranslationString("Peds", true), 2,
		TranslationString("Everything", true), 3
	};

	struct _Turrets {
		bool Populated;
		bool ExcludeSelf;
		int ID;
		int Minigun;
		int Type;
		Ped TurrentPed;
		Hash Weapon;
		bool OnGround;
		int TurrentCooldown;
	};

	vector<_Turrets> Turrets;

	void SpawnTurret() {
		Turrets.push_back(_Turrets());
		int Index = Turrets.size() - 1;

		STREAMING::RequestModel(0x3250D9D6);
		STREAMING::RequestModel(0xC89630B8);

		Vector3 Pos = ENTITY::GetOffsetFromEntityInWorldCoords(GetLocalPlayer().m_ped, 0, 1, 0);
		Turrets[Index].ID = OBJECT::CreateObject(0x3250D9D6, Pos.x, Pos.y, Pos.z, true, true, false);//prop_telescope
		Turrets[Index].Minigun = OBJECT::CreateObject(0xC89630B8, Pos.x, Pos.y, Pos.z, true, true, false);//prop_minigun_01
		ENTITY::AttachEntityToEntity(Turrets[Index].Minigun, Turrets[Index].ID, 0, 0.0f, 0.3f, 1.6f, 0.f, 0.f, 90.f, true, true, true, false, 2, true);
		ENTITY::SetEntityHeading(Turrets[Index].ID, ENTITY::GetEntityHeading(GetLocalPlayer().m_ped));
		Turrets[Index].OnGround = true;
		Turrets[Index].Type = vars.turretTargetSelection;
		Turrets[Index].ExcludeSelf = vars.turretExcludeMe;
		Turrets[Index].Weapon = turretWeapons[vars.turretWeaponSelection].m_result;
		Turrets[Index].TurrentCooldown = 0;
		Turrets[Index].Populated = true;

		STREAMING::SetModelAsNoLongerNeeded(0x3250D9D6);//prop_telescope
		STREAMING::SetModelAsNoLongerNeeded(0xC89630B8);//prop_minigun_01
	}

	void NoNearbyDrivingFlying() {
		static int TIMER;
		Utils::DoTimedFunction(&TIMER, 1000, [] {
			OnlinePlayerCallback(true, [](SPlayer player) {
				if (player.m_id != GetLocalPlayer().m_id && player.m_coordinates.Distance(GetLocalPlayer().m_coordinates) <= 3000.f) {
					if (!player.m_isInVehicle) return;
					/*if (VEHICLE::IsThisModelAHeli(player.m_vehicle) || VEHICLE::IsThisModelAPlane(player.m_vehicle) {*/
						BRAIN::ClearPedTasksImmediately(player.m_ped);
					//}
				}
			});
		});
	}


	void TeleportAllNearbyVehiclesToSea() {
		const int ElementAmount = 10;
		const int ArrSize = ElementAmount * 2 + 2;

		Vehicle *vehs = new Vehicle[ArrSize];
		vehs[0] = ElementAmount;
		int VehFound = PED::GetPedNearbyVehicles(GetLocalPlayer().m_ped, vehs);

		for (int i = 0; i < VehFound; i++)
		{
			int OffsetID = i * 2 + 2;
			if (vehs[OffsetID] != PED::GetVehiclePedIsIn(GetLocalPlayer().m_ped, false))
			{
				WorldMenuVars::vars.RequestControlOfEnt(vehs[OffsetID]);
				ENTITY::SetEntityCoords(vehs[OffsetID], 6400.f, 6400.f, 0.f, false, false, false, false);
			}
		}
		delete vehs;
	}

	void splitthesea() {
			Vector3 Coords = ENTITY::GetEntityCoords(GetLocalPlayer().m_ped, true);
			WATER::ModifyWater(Coords.x, Coords.y, -10, 10);
			WATER::ModifyWater(Coords.x + 2, Coords.y, -10, 10);
			WATER::ModifyWater(Coords.x, Coords.y + 2, -10, 10);
			WATER::ModifyWater(Coords.x + 2, Coords.y + 2, -10, 10);
			WATER::ModifyWater(Coords.x + 4, Coords.y, -10, 10);
			WATER::ModifyWater(Coords.x, Coords.y + 4, -10, 10);
			WATER::ModifyWater(Coords.x + 4, Coords.y + 4, -10, 10);
			WATER::ModifyWater(Coords.x + 6, Coords.y, -10, 10);
			WATER::ModifyWater(Coords.x, Coords.y + 6, -10, 10);
			WATER::ModifyWater(Coords.x + 6, Coords.y + 6, -10, 10);
			WATER::ModifyWater(Coords.x + 8, Coords.y, -10, 10);
			WATER::ModifyWater(Coords.x, Coords.y + 8, -10, 10);
			WATER::ModifyWater(Coords.x + 8, Coords.y + 8, -10, 10);
	}

}

void WorldMenu::Init() {
	setParentSubmenu<MainMenu>();
	setName("World", true, true);

	addOption(SubmenuOption("VFX engine")
		.addSubmenu<VFXMenu>().addHotkey().addTranslation()
		.addTooltip("Visual effects engine options"));

	addOption(SubmenuOption("Traffic manager")
		.addSubmenu<TrafficManagerMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Manage traffic"));

	addOption(SubmenuOption("Pedestrian manager")
		.addSubmenu<PedManagerMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Manage peds"));

	addOption(SubmenuOption("Weather")
		.addSubmenu<WeatherManagerMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Manage weather"));

	addOption(SubmenuOption("Waypoint")
		.addSubmenu<WaypointMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Waypoint options"));

	addOption(SubmenuOption("Drawable editor")
		.addSubmenu<WorldDrawablesMenu>().addTranslation()
		.addTooltip("Edit non-editable models")
		.addRequirement([] { return GetAuth()->IsVIP(); }));

	addOption(SubmenuOption("Blackhole")
		.addSubmenu<BlackholeMenu>()
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addHotkey().addTranslation()
		.addTooltip("Attracts entities"));

	addOption(SubmenuOption("Vehicles blacklist")
		.addSubmenu<VehicleBlacklistMenu>()
		.addTooltip("Freely blacklist vehicles")
		.addTranslation()
		.addHotkey()
		.addRequirement([] { return GetAuth()->IsVIP(); }));

	addOption(SubmenuOption("Bodyguards creator")
		.addSubmenu<BodyguardMenu>()
		.addTooltip("Create custom bodyguards")
		.addTranslation()
		.addHotkey()
		.addRequirement([] { return GetAuth()->IsVIP(); }));

	addOption(BreakOption("Time").addTranslation());

	addOption(ButtonOption("Add hour")
		.addFunction([] {
		int hour = CLOCK::GetClockHours() + 1;
		if (hour > 23) hour = 0;
		NETWORK::NetworkOverrideClockTime(hour, CLOCK::GetClockMinutes(), CLOCK::GetClockSeconds());
	}).addTranslation()
		.addTooltip("Increment the hour by 1"));

	addOption(ButtonOption("Remove hour")
		.addFunction([] {
		int hour = CLOCK::GetClockHours() - 1;
		if (hour < 0) hour = 23;
		NETWORK::NetworkOverrideClockTime(hour, CLOCK::GetClockMinutes(), CLOCK::GetClockSeconds());
	}).addTranslation()
		.addTooltip("Decrement the hour by 1"));

	addOption(ToggleOption("Freeze time")
		.addToggle(vars.freezeTime)
		.addFunction([] { CLOCK::PauseClock(vars.freezeTime); })
		.addHotkey().addTranslation()
		.addTooltip("Freeze the time"));

	addOption(ToggleOption("Sync with system time")
		.addToggle(vars.syncWithSystemTime)
		.addTooltip("Sync the games time with your computer time").addTranslation());

	addOption(BreakOption("Water").addTranslation());

	addOption(ToggleOption("Turn off ocean")
		.addToggle(vars.noocean)
		.addFunction([] {GetOceanManager()->NoOcean(vars.noocean); })
		.addHotkey().addTranslation()
		.addTooltip("Disable the ocean"));

	addOption(ToggleOption("Clear water")
		.addToggle(vars.clearwater)
		.addFunction([] {GetOceanManager()->ClearWater(vars.clearwater); })
		.addHotkey().addTranslation()
		.addTooltip("Clear water"));

	addOption(NumberOption<int>(SCROLL, "Wave intensity")
		.addNumber(vars.waveintensity, "%d", 1).addMin(-100).addMax(100)
		.addFunction([] {GetOceanManager()->SetWaveIntensity(vars.waveintensity); })
		.addHotkey().addTranslation()
		.addTooltip("Clear water"));

	/*addOption(ToggleOption("Split water walk")
		.addToggle(vars.splitwater)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("Split the water when you walk towards it"));*/

	addOption(BreakOption("Water Tune")
		.addTranslation());

	addOption(NumberOption<float>(SCROLL, "Ripple scale")
		.addTooltip("Edit the ripples water has ingame")
		.addNumber(vars.Tune.RippleScale, "%.2f", 0.2f).addMin(-10.f).addMax(10.f)
		.addFunction([] {
			GetOceanManager()->m_WaterTune->RippleScale = vars.Tune.RippleScale;
		}));

	addOption(NumberOption<float>(SCROLL, "Ocean Foam Scale")
		.addTooltip("Edit the foam water has ingame")
		.addNumber(vars.Tune.OceanFoamScale, "%.2f", 0.2f).addMin(-1000.f).addMax(1000.f).setScrollSpeed(5)
		.addFunction([] {
		GetOceanManager()->m_WaterTune->OceanFoamScale = vars.Tune.OceanFoamScale;
	}));

	addOption(NumberOption<float>(SCROLL, "Specular Falloff")
		.addTooltip("Edit the light falloff water has ingame")
		.addNumber(vars.Tune.SpecularFalloff, "%.0f", 1.f).addMin(-1000.f).addMax(1000.f).setScrollSpeed(5)
		.addFunction([] {
		GetOceanManager()->m_WaterTune->SpecularFalloff = vars.Tune.SpecularFalloff;
	}));

	addOption(BreakOption("Density").addTranslation());

	addOption(NumberOption<float>(TOGGLE, "Ped density")
		.addToggle(vars.enablePedDensity)
		.addNumber(vars.pedDensity, "%.1f", 0.1f).addMin(0).addMax(1)
		.addFunction([] {PED::SetPedDensityMultiplierThisFrame(vars.pedDensity); })
		.addHotkey().addTranslation()
		.addTooltip("Amount of peds on the street"));

	addOption(NumberOption<float>(TOGGLE, "Traffic density")
		.addToggle(vars.enableTrafficDensity)
		.addNumber(vars.trafficDensity, "%.1f", 0.1f).addMin(0).addMax(1)
		.addFunction([] {VEHICLE::SetVehicleDensityMultiplierThisFrame(vars.trafficDensity); })
		.addHotkey().addTranslation()
		.addTooltip("Amount of vehicles on the street"));

	addOption(BreakOption("Sentry")
		.addTranslation()
		.addRequirement([] { return GetAuth()->IsVIP(); }));

	addOption(ToggleOption("Exclude me (next spawn)")
		.addToggle(vars.turretExcludeMe).addTranslation()
		.addTooltip("Exclude me from the turret aiming system (on the next turret)")
		.addRequirement([] { return GetAuth()->IsVIP(); }));

	addOption(ScrollOption<Hash>(SCROLL, "Weapon selection")
		.addScroll(vars.turretWeaponSelection, 0, NUMOF(turretWeapons) - 1, turretWeapons)
		.addTooltip("Select the weapon the turret you spawn next will use").addTranslation()
		.addRequirement([] { return GetAuth()->IsVIP(); }));

	addOption(ScrollOption<int>(SCROLL, "Target")
		.addScroll(vars.turretTargetSelection, 0, NUMOF(turretAimType) - 1, turretAimType)
		.addTooltip("Select the target the turret you spawn next will aim at").addTranslation()
		.addRequirement([] { return GetAuth()->IsVIP(); }));

	addOption(ButtonOption("Spawn turret on current position")
		.addFunction([] { SpawnTurret(); })
		.addTooltip("Spawn a turret where your character is").addTranslation()
		.addRequirement([] { return GetAuth()->IsVIP(); }));

	addOption(BreakOption("Clear Area").addTranslation());

	addOption(NumberOption<float>(TOGGLE, "Clear radius")
		.addToggle(vars.enableradiusbubble)
		.addNumber(vars.clearradius, "%.1f", 1.0f).addMin(-FLT_MAX).addMax(FLT_MAX)
		.addHotkey()
		.addTooltip("Control the radius of the clear area"));

	addOption(ButtonOption("Clear area of everything")
		.addFunction([] {
		MISC::ClearArea(GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, GetLocalPlayer().m_coordinates.z, vars.clearradius, true, false, false, false);
		MISC::_ClearAreaOfEverything(GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, GetLocalPlayer().m_coordinates.z, vars.clearradius, 1, 0, 0, 1); 
		MISC::ClearAreaOfPeds(GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, GetLocalPlayer().m_coordinates.z, vars.clearradius, 0);
		MISC::ClearAreaOfVehicles(GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, GetLocalPlayer().m_coordinates.z, vars.clearradius, 0, 0, 0, 0, 0, 0);
		MISC::ClearAreaOfObjects(GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, GetLocalPlayer().m_coordinates.z, vars.clearradius, 0);
		MISC::ClearAreaOfCops(GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, GetLocalPlayer().m_coordinates.z, vars.clearradius, 0);
	})
		.addTooltip("Clear the area around you of everything").addTranslation());

	addOption(ButtonOption("Clear area of police")
		.addFunction([] {MISC::ClearAreaOfCops(GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, GetLocalPlayer().m_coordinates.z, vars.clearradius, 0); })
		.addTooltip("Clear the area around you of police").addTranslation());

	addOption(ButtonOption("Clear area of objects")
		.addFunction([] {MISC::ClearAreaOfObjects(GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, GetLocalPlayer().m_coordinates.z, vars.clearradius, 0); })
		.addTooltip("Clear the area around you of objects").addTranslation());

	addOption(ButtonOption("Clear area of vehicles")
		.addFunction([] {MISC::ClearAreaOfVehicles(GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, GetLocalPlayer().m_coordinates.z, vars.clearradius, 0, 0, 0, 0, 0, 0); })
		.addTooltip("Clear the area around you of vehicles").addTranslation());

	addOption(ButtonOption("Clear area of peds")
		.addFunction([] {MISC::ClearAreaOfPeds(GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, GetLocalPlayer().m_coordinates.z, vars.clearradius, 0); })
		.addTooltip("Clear the area around you of peds").addTranslation());

	addOption(BreakOption("Misc").addTranslation());

	addOption(ToggleOption("Kick all nearby from vehicles")
		.addToggle(vars.noflybys)
		.addHotkey().addTranslation()
		.addTooltip("This will kick anyone out their veh who enters your area (Air/Ground Vehicles)"));

	addOption(ToggleOption("Teleport all nearby vehicles to sea")
		.addToggle(vars.teleportallnearvehs)
		.addHotkey().addTranslation()
		.addTooltip("This will teleport ped/player vehicles alike to the sea when they get close"));

	addOption(NumberOption<float>(SCROLL, "Timescale")
		.addNumber(vars.timeScale, "%.1f", 0.1f).addMin(0.0f).addMax(1.0f)
		.addOnUpdate([] {MISC::SetTimeScale(vars.timeScale); })
		.addTooltip("Change the timeScale (local)").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Road slipperiness")
		.addNumber(vars.slipperiness, "%.1f", 0.1f).addMin(-5000.0f).addMax(5000.0f)
		.addHotkey()
		.addTooltip("Make the roads slippy").addTranslation());

	addOption(ScrollOption<int>(SCROLL, "Gravity")
		.addScroll(vars.gravity, 0, NUMOF(gravity) - 1, gravity)
		.addFunction([] { MISC::SetGravityLevel(gravity[vars.gravity].m_result); })
		.addTooltip("Alter gravity").addTranslation());

	addOption(ToggleOption("Blackout")
		.addToggle(vars.blackout)
		.addFunction([] {GRAPHICS::_SetBlackout(vars.blackout); })
		.addHotkey()
		.addTooltip("Blackout all ingame lights").addTranslation());

	addOption(ToggleOption("Ground snow")
		.addToggle(*Global(Globals::SNOW_BASE).At(Globals::SNOW_OFFSET).Get<bool>())
		.addHotkey()
		.addTooltip("Snow!").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Wind speed")
		.addNumber(vars.wind, "%.1f", 1.0f).addMin(-FLT_MAX).addMax(FLT_MAX)
		.addHotkey()
		.addTooltip("Control the wind speed").addTranslation());

	/*addOption(NumberOption<float>(SCROLL, "Snow")
		.addNumber(vars.snow, "%.1f", 0.1f).addMin(-FLT_MAX).addMax(FLT_MAX)
		.addHotkey()
		.addTooltip("Control the snow"));*/
}

/*Update once when submenu is opened*/
void WorldMenu::UpdateOnce() {
	vars.Tune.RippleScale = GetOceanManager()->m_WaterTune->RippleScale;
	vars.Tune.SpecularFalloff = GetOceanManager()->m_WaterTune->SpecularFalloff;
	vars.Tune.OceanFoamScale = GetOceanManager()->m_WaterTune->OceanFoamScale;
}

/*Update while submenu is active*/
void WorldMenu::Update() {}

/*Background update*/
void WorldMenu::FeatureUpdate() {
	if (vars.freezeTime) NETWORK::NetworkOverrideClockTime(CLOCK::GetClockHours(), CLOCK::GetClockMinutes(), CLOCK::GetClockSeconds());
	if (vars.enablePedDensity) PED::SetPedDensityMultiplierThisFrame(vars.pedDensity);
	if (vars.enableTrafficDensity) VEHICLE::SetVehicleDensityMultiplierThisFrame(vars.trafficDensity);
	if (vars.enableradiusbubble) GRAPHICS::DrawMarker(28, GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, GetLocalPlayer().m_coordinates.z, 0, 0, 0, 0, 0, 0, vars.clearradius, vars.clearradius, vars.clearradius, 255, 0, 0, 100, false, false, 0, 0, 0, 0, 0); (vars.clearradius);
	if (vars.noflybys) NoNearbyDrivingFlying();
	if (vars.teleportallnearvehs) TeleportAllNearbyVehiclesToSea();
	if (vars.splitwater) splitthesea();

	if (vars.syncWithSystemTime) {
		CLOCK::PauseClock(false);

		int day, month, year, hour, min, sec;
		CLOCK::GetLocalTime(&year, &month, &day, &hour, &min, &sec);
		NETWORK::NetworkOverrideClockTime(hour, min, sec);
	}

	if (Turrets.size() > 0) {
		for (int i = 0; i < Turrets.size(); i++) {
			if (ENTITY::DoesEntityExist(Turrets[i].ID)) {
				Vector3 Coords = ENTITY::GetEntityCoords(Turrets[i].ID, false);
				Entity Target = 0;
				Vector3 Rotation = { 0, 0, 0 };
				if (Turrets[i].OnGround) {
					ENTITY::SetEntityCoords(Turrets[i].ID, Coords.x, Coords.y, Coords.z - 1, false, true, true, false);
					Turrets[i].OnGround = false;
				}

				if (Turrets[i].TurrentPed == 0) {
					Vector3 rela = ENTITY::GetOffsetFromEntityInWorldCoords(Turrets[i].ID, 0, 0, -3);
					STREAMING::RequestModel(Utils::GetHashKey("a_f_y_skater_01"));
					int Ped = PED::CreatePed(21, Utils::GetHashKey("a_f_y_skater_01"), rela.x, rela.y, rela.z, ENTITY::GetEntityHeading(GetLocalPlayer().m_ped), 1, 0);//a_f_y_skater_01
					if (ENTITY::DoesEntityExist(Ped)) {
						ENTITY::SetEntityInvincible(Ped, true);
						ENTITY::SetEntityVisible(Ped, false, 1);
						ENTITY::SetEntityCollision(Ped, false, false);
						ENTITY::FreezeEntityPosition(Ped, true);
						Turrets[i].TurrentPed = Ped;
					}
				} else {
					/*
						"Vehicles", 0,
						"Players", 1,
						"Peds", 2,
						"Everything", 3
					*/

					switch (Turrets[i].Type) {
						case 3:
						case 0: {
								const int ElementAmount = 10;
								const int ArrSize = ElementAmount * 2 + 2;
								Vehicle *veh = new Vehicle[ArrSize];
								veh[0] = ElementAmount;
								int count = PED::GetPedNearbyVehicles(Turrets[i].TurrentPed, veh);
								if (veh != NULL) {
									float ClosestAlive = FLT_MAX;
									for (int i = 0; i < count; i++) {
										int offsettedID = i * 2 + 2;
										if (ENTITY::DoesEntityExist(veh[offsettedID])) {
											Vector3 Location = ENTITY::GetEntityCoords(veh[offsettedID], false);
											float Distance = MISC::GetDistanceBetweenCoords(Coords.x, Coords.y, Coords.z, Location.x, Location.y, Location.z, false);
											if (Distance < ClosestAlive) {
												Target = veh[offsettedID];
												ClosestAlive = Distance;
											}
										}
									}
								}

								if (Turrets[i].Type != 3) break;
							}
						case 1: {
								Target = PLAYER::GetPlayerPedScriptIndex(ENTITY::GetNearestPlayerToEntity(Turrets[i].ID));
								if (Turrets[i].Type != 3) break;
							}
						case 2: {
								const int ElementAmount = 10;
								const int ArrSize = ElementAmount * 2 + 2;
								Ped *ped = new Ped[ArrSize];
								ped[0] = ElementAmount;
								int count = PED::GetPedNearbyPeds(Turrets[i].TurrentPed, ped, -1);
								if (ped != NULL) {
									float ClosestAlive = FLT_MAX;
									for (int i = 0; i < count; i++) {
										int offsettedID = i * 2 + 2;
										if (ENTITY::DoesEntityExist(ped[offsettedID])) {
											Vector3 Location = ENTITY::GetEntityCoords(ped[offsettedID], false);
											float Distance = MISC::GetDistanceBetweenCoords(Coords.x, Coords.y, Coords.z, Location.x, Location.y, Location.z, false);
											if (Distance < ClosestAlive) {
												Target = ped[offsettedID];
												ClosestAlive = Distance;
											}
										}
									}
								}
								if (Turrets[i].Type != 3) break;
							}
					}

					if (ENTITY::DoesEntityExist(Target) && !ENTITY::IsEntityDead(Target, 0)) {
						Vector3 Finish = ENTITY::GetEntityCoords(Target, false);
						Vector3 Start = ENTITY::GetOffsetFromEntityInWorldCoords(Turrets[i].Minigun, 0.7f, 0.0f, 0.0f);

						Rotation.x = 0;
						float Distance = MISC::GetDistanceBetweenCoords(Start.x, Start.y, Start.z, Finish.x, Finish.y, Finish.z, false);
						Rotation.y = MISC::Atan2((Finish.z - Start.z), Distance) * -1;
						Rotation.z = MISC::Atan2((Finish.y - Start.y), (Finish.x - Start.x));

						ENTITY::SetEntityRotation(Turrets[i].ID, 0, 0, Rotation.z + 90, 0, false);
						ENTITY::AttachEntityToEntity(Turrets[i].Minigun, Turrets[i].ID, 0, 0.f, -0.3f, 1.6f, 0.f, Rotation.y, 270.f, true, true, true, false, 2, true);

						if (Turrets[i].ExcludeSelf && Target == GetLocalPlayer().m_ped || Target == GetLocalPlayer().m_vehicle) {
							continue;
						}

						GRAPHICS::DrawLine(Start.x, Start.y, Start.z, Finish.x, Finish.y, Finish.z, 255, 0, 0, 255);

						if (Turrets[i].Weapon == 0xB1CA77B1) { // rpg
							if (Turrets[i].TurrentCooldown < MISC::GetGameTimer()) {
								MISC::ShootSingleBulletBetweenCoords(Start.x, Start.y, Start.z, Finish.x, Finish.y, Finish.z, 250, 0, (Turrets[i].Weapon), Turrets[i].TurrentPed, true, false, 1000);
								Turrets[i].TurrentCooldown = MISC::GetGameTimer() + 1000;
							}
						} else {
							MISC::ShootSingleBulletBetweenCoords(Start.x, Start.y, Start.z, Finish.x, Finish.y, Finish.z, 250, 0, (Turrets[i].Weapon), Turrets[i].TurrentPed, true, false, 1000);
						}
					}
				}
			} else {
				Turrets.erase(Turrets.begin() + i);
				break;
			}
		}
	}
}

/*Singleton*/
WorldMenu* _instance;
WorldMenu* WorldMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new WorldMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
WorldMenu::~WorldMenu() { delete _instance; }