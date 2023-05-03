#include "stdafx.h"
#include "weaponShootEntities.h"
#include "../weaponMenu.h"
#include "../local/modelMenu.h"

using namespace WeaponShootEntitiesMenuVars;

namespace WeaponShootEntitiesMenuVars {
	Vars vars;

	vector<Hash> allPurposeVehicleHashs = {
		0x761E2AD3,
		0x4C80EB0E,
		0xC703DB5F,
		0x9F05F101,
		0x3D6AAA9B,
		0xFE0A508C,
		0xB779A091,
		0x6322B39A,
		0x19DD9ED1,
		0xAF599F01,
		0xB44F0582,
		0x3EAB5555,
		0x3E48BF23,
		0xEC8F7094,
		0x43779C54,
		0xE2E7D4AB,
		0xB79F589E,
		0x3F119114,
		0x15F27762,
		0x45D56ADA,
		0xDC19D101,
		0x58CDAF30,
		0x2189D250
	};

	ScrollStruct<int> entityTypes[] = {
		TranslationString("Vehicle", true), 0,
		TranslationString("Object", true), 1,
		TranslationString("Ped", true), 2,
	};

	ScrollStruct<Hash> vehiclePairs[] = {
		TranslationString("Taxi"), 0xC703DB5F,
		TranslationString("Police Cruiser"), 0x9F05F101,
		TranslationString("Adder"), 0xB779A091,
		TranslationString("T20"), 0x6322B39A,
		TranslationString("Duke O'Death"), 0xEC8F7094,
		TranslationString("BMX"), 0x43779C54,
		TranslationString("Police Predator"), 0xE2E7D4AB,
		TranslationString("Nightshark"), 0x19DD9ED1,
		TranslationString("Vindicator"), 0xAF599F01,
		TranslationString("Hot Rod Blazer"), 0xB44F0582,
		TranslationString("JB 700"), 0x3EAB5555,
		TranslationString("Titan"), 0x761E2AD3,
		TranslationString("Airport Bus"), 0x4C80EB0E,
		TranslationString("Freight Train"), 0x3D6AAA9B,
		TranslationString("RM-10 Bombushka"), 0xFE0A508C,
		TranslationString("Skylift"), 0x3E48BF23,
		TranslationString("Luxor Deluxe"), 0xB79F589E,
		TranslationString("Jet"), 0x3F119114,
		TranslationString("Cargo Plane"), 0x15F27762,
		TranslationString("Ambulance"), 0x45D56ADA,
		TranslationString("Roosevelt Valor"), 0xDC19D101,
		TranslationString("Thruster"), 0x58CDAF30,
		TranslationString("APC"), 0x2189D250
	};

	ScrollStruct<Hash> objectPairs[] = {
		TranslationString("Meteor"), 0xDF9841D7,
		TranslationString("UFO"), 0xB467C540,
		TranslationString("Ferris Wheel"), 0xC42C019A,
		TranslationString("Large Xmas Tree"), 0x7121AC4,
		TranslationString("Covered Cheetah"), 0x37D80B0E,
		TranslationString("Weed Pallet"), 0xE8032E4,
		TranslationString("Burger Stand"), 0x434BFB7C,
		TranslationString("Crashed Heli"), 0x8E8C7A5B,
		TranslationString("Beer Neon"), 0x5571173D,
		TranslationString("Le Barge"), 0x8AF58425,
		TranslationString("Flat TV"), 0x3DC31836,
		TranslationString("Beach Fire"), 0xC079B265,
		TranslationString("Space Pistol"), 0xBD8AE007,
		TranslationString("Toilet"), 0x6F9939C7,
		TranslationString("Wheelchair"), 0x4B3D240F,
		TranslationString("Road Cone"), 0xE0264F5D,
		TranslationString("Alien Egg"), 0x6B795EBC,
		TranslationString("Katana"), 0xE2BA016F,
		TranslationString("Car Seat"), 0x52660DBB,
		TranslationString("Gold Bar"), 0xF046EA37,
		TranslationString("JB700 Covered"), 0x72F54E90,
		TranslationString("Guitar"), 0x369D8410,
		TranslationString("Lawnmower"), 0x1AB39621,
		TranslationString("Bucket"), 0x29E362FF,
		TranslationString("Haybail"), 0x5411322E,
		TranslationString("Safe"), 0x40F52369
	};

	ScrollStruct<Hash> pedPairs[] = {
		TranslationString("Movspace"), 0xE7B31432,
		TranslationString("Imporage"), 0x348065F5,
		TranslationString("Rs Ranger"), 0x3C438CD2,
		TranslationString("Justin"), 0x7DC3908F,
		TranslationString("Mani"), 0xC8BB1E52,
		TranslationString("Michael"), 0xD7114C9,
		TranslationString("Franklin"), 0x9B22DBAF,
		TranslationString("Trevor"), 0x9B810FA2,
		TranslationString("Boar"), 0xCE5FF074,
		TranslationString("Chimp"), 0xA8683715,
		TranslationString("Cow"), 0xFCFA9E1E,
		TranslationString("Coyote"), 0x644AC75E,
		TranslationString("Deer"), 0xD86B5A95,
		TranslationString("Fish"), 0x2FD800B7,
		TranslationString("Hen"), 0x6AF51FAF,
		TranslationString("Cat"), 0x573201B8,
		TranslationString("Hawk"), 0xAAB71F62,
		TranslationString("Cormorant"), 0x56E29962,
		TranslationString("Crow"), 0x18012A9F,
		TranslationString("Dolphin"), 0x8BBAB455,
		TranslationString("Humpback"), 0x471BE4B2,
		TranslationString("Whale"), 0x8D8AC8B9,
		TranslationString("Pigeon"), 0x6A20728,
		TranslationString("Seagull"), 0xD3939DFD,
		TranslationString("Sharkhammer"), 0x3C831724,
		TranslationString("Pig"), 0xB11BAB56,
		TranslationString("Rat"), 0xC3B52966,
		TranslationString("Rhesus"), 0xC2D06F53,
		TranslationString("Chop"), 0x14EC17EA,
		TranslationString("Husky"), 0x4E8F95A2,
		TranslationString("Mtlion"), 0x1250D7BA,
		TranslationString("Retriever"), 0x349F33E1,
		TranslationString("Sharktiger"), 0x6C3F072,
		TranslationString("Shepherd"), 0x431FC24C,
		TranslationString("Alien"), 0x64611296,
		TranslationString("Beach"), 0x303638A7,
		TranslationString("Bevhills"), 0xBE086EFD,
		TranslationString("Bevhills"), 0xA039335F,
		TranslationString("Bodybuild"), 0x3BD99114,
		TranslationString("Business"), 0x1FC37DBC,
		TranslationString("Downtown"), 0x654AD86E,
		TranslationString("Eastsa"), 0x9D3DCB7A,
		TranslationString("Eastsa"), 0x63C8D891,
		TranslationString("Fatbla"), 0xFAB48BCB,
		TranslationString("Fatcult"), 0xB5CF80E4,
		TranslationString("Fatwhite"), 0x38BAD33B,
		TranslationString("Ktown"), 0x52C824DE,
		TranslationString("Ktown"), 0x41018151,
		TranslationString("Prolhost"), 0x169BD1E1,
		TranslationString("Salton"), 0xDE0E0969,
		TranslationString("Skidrow"), 0xB097523B,
		TranslationString("Soucentmc"), 0xCDE955D2,
		TranslationString("Soucent"), 0x745855A1,
		TranslationString("Soucent"), 0xF322D338,
		TranslationString("Tourist"), 0x505603B9,
		TranslationString("Trampbeac"), 0x8CA0C266,
		TranslationString("Tramp"), 0x48F96F5B,
		TranslationString("Genstreet"), 0x61C81C85,
		TranslationString("Indian"), 0xBAD7BB80,
		TranslationString("Ktown"), 0x47CF5E96,
		TranslationString("Salton"), 0xCCFF7D8A,
		TranslationString("Soucent"), 0x3DFA1830,
		TranslationString("Soucent"), 0xA56DE716,
		TranslationString("Beach"), 0xC79F6928
	};

	void gravshootgun() {
		static Vehicle vehicle;
		Hash model = vehiclePairs[vars.vehicleVal].m_result;
		Vector3 position = ENTITY::GetOffsetFromEntityInWorldCoords(GetLocalPlayer().m_ped, 0.4f, vars.shootdistance, 0.8f);
		Vector3 camrot = CAM::_GetGameplayCamRot(2);
		Vector3 playerrot = ENTITY::GetEntityRotation(GetLocalPlayer().m_ped, 2);
		Vector3 direction = Utils::RotateToDirection(&camrot);
		Vector3 entityCoords = ENTITY::GetEntityCoords(vehicle, 0);

		if (PED::GetPedConfigFlag(GetLocalPlayer().m_ped, PED_FLAG_IS_AIMING, 1)) {
			if (!ENTITY::DoesEntityExist(vehicle)) {
				GetEntityControl()->SimpleRequestControl(vehicle);
				GetEntityControl()->SimpleRequestModel(vehiclePairs[vars.vehicleVal].m_result);
				vehicle = VEHICLE::CreateVehicle(model, GetLocalPlayer().m_coordinates.x + 5.f, GetLocalPlayer().m_coordinates.y + 5.f, GetLocalPlayer().m_coordinates.z + 7.0f, ENTITY::GetEntityHeading(GetLocalPlayer().m_ped), true, true, true);
			} else {
				Vector3 force = {

					((position.x + (direction.x *  5.0f)) - ENTITY::GetEntityCoords(vehicle, false).x) * 4,
					((position.y + (direction.y *  5.0f)) - ENTITY::GetEntityCoords(vehicle, false).y) * 4,
					((position.z + (direction.z *  5.0f)) - ENTITY::GetEntityCoords(vehicle, false).z) * 4
				};
						GetEntityControl()->SimpleRequestControl(vehicle);
						ENTITY::SetEntityVelocity(vehicle, force.x, force.y, force.z);
						ENTITY::SetEntityRotation(vehicle, playerrot.x, playerrot.y, camrot.z, 2, true);

					if (PED::IsPedShooting(GetLocalPlayer().m_ped)) {
						Vector3 Offset = ENTITY::GetOffsetFromEntityGivenWorldCoords(vehicle, GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, GetLocalPlayer().m_coordinates.z);
						ENTITY::ApplyForceToEntity(vehicle, true, -Offset.x * fabs(100.0f / Offset.y), -Offset.y * fabs(100.0f / Offset.y), -Offset.z * fabs(100.0f / Offset.y), 0, 0, 0, false, true, true, true, false, true);
						vehicle = NULL;
					}
			}
		} else {
			if (ENTITY::DoesEntityExist(vehicle)) {
				GetEntityControl()->SimpleRequestControl(vehicle);
				ENTITY::SetEntityAsMissionEntity(vehicle, true, true);
				GetEntityControl()->DeleteEntity(vehicle);
				vehicle = NULL;
			}
		}
	}
}

void WeaponShootEntitiesMenu::Init() {
	setParentSubmenu<WeaponMenu>();
	setName("Shoot entities", true, true);

	addOption(ScrollOption<int>(SCROLL, "Entity type")
		.addFunction([this] {UpdateOnce(); })
		.addScroll(vars.shootEntityType, 0, NUMOF(entityTypes) - 1, entityTypes)
		.addTooltip("Entity type").addTranslation().addHotkey().canBeSaved());

	addOption(ToggleOption("Enable entity shooting")
		.addRequirement([] { return !vars.flyinshootvehicles; })
		.addToggle(vars.shootEntities)
		.addTooltip("Enable entity shooting").addTranslation().addHotkey().canBeSaved());

	addOption(ButtonOption("~c~Enable entity shooting~s~")
		.addRequirement([] { return vars.flyinshootvehicles && vars.shootEntityType == 0; })
	);

	addOption(ButtonOption("~c~Enable gravity vehicle shooting~s~")
		.addRequirement([] { return vars.shootEntities && vars.shootEntityType == 0; })
	);

	addOption(ButtonOption("~c~Gravity vehicle distance~s~")
		.addRequirement([] { return vars.shootEntities && vars.shootEntityType == 0; })
	);

	addOption(ToggleOption("Enable gravity vehicle shooting")
		.addRequirement([] { return !vars.shootEntities && vars.shootEntityType == 0; })
		.addToggle(vars.flyinshootvehicles)
		.addTooltip("Enable entity shooting with gravity").addTranslation().addHotkey().canBeSaved());

	addOption(NumberOption<float>(SCROLL, "Gravity vehicle distance")
		.addRequirement([] { return !vars.shootEntities && vars.shootEntityType == 0; })
		.addNumber(vars.shootdistance, "%.1f", 1.0f).addMin(0.0f).addMax(50.0f)
		.addHotkey()
		.addTooltip("Control the distance between you and the gravity vehicle"));
}

/*Update once when submenu is opened*/
void WeaponShootEntitiesMenu::UpdateOnce() {
	clearOptionsOffset(7);
	switch (vars.shootEntityType) {
		case 0:
			addOption(ScrollOption<Hash>(SCROLL, "Vehicle")
				.addScroll(vars.vehicleVal, 0, NUMOF(vehiclePairs) - 1, vehiclePairs)
				.addTooltip("Choose a vehicle to shoot")
				.addTranslation().addHotkey());
			break;
		case 1:
			addOption(ScrollOption<Hash>(SCROLL, "Object")
				.addScroll(vars.objectVal, 0, NUMOF(objectPairs) - 1, objectPairs)
				.addTooltip("Choose a Object to shoot")
				.addTranslation().addHotkey());
			break;
		case 2:
			addOption(ScrollOption<Hash>(SCROLL, "Ped")
				.addScroll(vars.pedVal, 0, NUMOF(pedPairs) - 1, pedPairs)
				.addTooltip("Choose a Ped to shoot")
				.addTranslation().addHotkey());
			break;
	}
}

/*Update while submenu is active*/
void WeaponShootEntitiesMenu::Update() {

}

/*Background update*/
void WeaponShootEntitiesMenu::FeatureUpdate() {
	if (vars.flyinshootvehicles) gravshootgun();

	if (vars.shootEntities) {
		if (PED::IsPedShooting(GetLocalPlayer().m_ped)) {
			static int TIMER;
			Utils::DoTimedFunction(&TIMER, 100, [] {
				Entity handle;
				switch (vars.shootEntityType) {
					case 0: {
							GetEntityControl()->SimpleRequestModel(vehiclePairs[vars.vehicleVal].m_result);
							handle = VEHICLE::CreateVehicle(vehiclePairs[vars.vehicleVal].m_result, 0, 0, 0, 1, 1, 0, 1);
							break;
						}
					case 1: {
							//GetEntityControl()->SimpleRequestModel(objectPairs[vars.objectVal].m_result);
							handle = OBJECT::CreateObject(objectPairs[vars.objectVal].m_result, 0, 0, 0, 1, 1, 0);
							break;
						}
					case 2: {
							GetEntityControl()->SimpleRequestModel(pedPairs[vars.pedVal].m_result);
							handle = PED::CreatePed(21, pedPairs[vars.pedVal].m_result, 0, 0, 0, 1, 1, 0);
							break;
						}
				}

				if (ENTITY::DoesEntityExist(handle)) {
					ENTITY::SetEntityNoCollisionEntity(GetLocalPlayer().m_ped, handle, 1);

					Vector3 rot = CAM::GetGameplayCamRot(0);
					Vector3 posLookAt = CAM::GetGameplayCamCoord() + (Utils::RotateToDirection(&rot) * 10.0f);

					ENTITY::SetEntityCoords(handle, posLookAt.x, posLookAt.y, posLookAt.z, 0, 0, 0, 0);
					ENTITY::SetEntityRotation(handle, rot.x, 0, rot.z, 0, 1);

					if (ENTITY::IsEntityAVehicle(handle))VEHICLE::SetVehicleOutOfControl(handle, 1, 1);
					ENTITY::ApplyForceToEntityCenterOfMass(handle, 1, 0.0f, 850.0f, 0.0f, false, true, true, false);
					ENTITY::SetEntityAsNoLongerNeeded(&handle);
				}

			});
		}
	}
}

/*Singleton*/
WeaponShootEntitiesMenu* _instance;
WeaponShootEntitiesMenu* WeaponShootEntitiesMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new WeaponShootEntitiesMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
WeaponShootEntitiesMenu::~WeaponShootEntitiesMenu() { delete _instance; }