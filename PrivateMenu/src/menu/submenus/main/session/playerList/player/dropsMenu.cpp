#include "stdafx.h"
#include "dropsMenu.h"
#include "../playerMenu.h"

using namespace DropsMenuVars;

namespace DropsMenuVars {
	Vars vars;

	ScrollStruct<int> dropTypes[] = {
		TranslationString("Money", true), 0,
		TranslationString("Weapon", true), 1,
		TranslationString("Health", true), 2,
		TranslationString("Snacks", true), 3,
		TranslationString("Armour", true), 4,
		TranslationString("Parachutes", true), 5,
		TranslationString("Ammunition", true), 6,
		TranslationString("Vehicle Health", true), 7,
		TranslationString("Vehicle Armour", true), 8
	};

	ScrollStruct<int> dropModels[] = {
		TranslationString("Briefcase", true), -1666779307,
		TranslationString("Money Bag", true), (int)0x113FD533,
		TranslationString("Bong", true), -257549932,
		TranslationString("Guitar", true), -708789241,
		TranslationString("Dildo", true), -422877666,
		TranslationString("Alien Egg", true), 1803116220,
		TranslationString("Gravestone", true), -547750016,
		TranslationString("Yoga Mat", true), -232023078
	};

	void PedDrop(SPlayer& player) {
		static int TIMER[32];
		Utils::DoTimedFunction(&TIMER[player.m_id], 750, [&] {
			Ped spawnedPed = PED::CreateRandomPed(player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z - 3.0f);
			ENTITY::SetEntityVisible(spawnedPed, false, false);
			ENTITY::SetEntityCollision(spawnedPed, false, false);
			PED::SetPedMoney(spawnedPed, 2000);
			ENTITY::SetEntityHealth(spawnedPed, 0);
			ENTITY::SetEntityAlpha(spawnedPed, 0, true);
			PED::RemovePedElegantly(&spawnedPed);
			PED::DeletePed(&spawnedPed);
			ENTITY::DeleteEntity(&spawnedPed);
		});
	}

	void StandardCircleDrop2(SPlayer& player) {
		static int TIMER[32];

		GetEntityControl()->SimpleRequestModel(-1666779307);

		Utils::DoTimedFunction(&TIMER[player.m_id], vars.standarddropdelay, [&] {
			OBJECT::CreateMoneyPickups(player.m_coordinates.x + 0.4, player.m_coordinates.y + 0.6, player.m_coordinates.z, 0x1E9A99F8, player.m_dropAmount, -1666779307);
		});
	}

	void StandardMoneyDrop(SPlayer& player) {
		static int TIMER[32];

		GetEntityControl()->SimpleRequestModel(-1666779307);

		Utils::DoTimedFunction(&TIMER[player.m_id], vars.standarddropdelay, [&] {
			OBJECT::CreateAmbientPickup(0x1E9A99F8, player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 0, 2500, -1666779307, false, true);
		});
	}

	void StandardCircleDrop(SPlayer& player) {
		static int TIMER[32];

		GetEntityControl()->SimpleRequestModel(-1666779307);

		Utils::DoTimedFunction(&TIMER[player.m_id], vars.standarddropdelay, [&] {
			OBJECT::CreateMoneyPickups(player.m_coordinates.x + 0.4, player.m_coordinates.y + 0.6, player.m_coordinates.z, 0x1E9A99F8, 2500, -1666779307);
		});
	}

	void Drop(SPlayer& player) {
		float RandomX = MISC::GetRandomFloatInRange(-player.m_dropRadius, player.m_dropRadius);
		float RandomY = MISC::GetRandomFloatInRange(-player.m_dropRadius, player.m_dropRadius);
		float RandomZ = MISC::GetRandomFloatInRange(0, player.m_dropHeight);
		Vector3 SpawnLocation = ENTITY::GetOffsetFromEntityInWorldCoords(player.m_ped, RandomX, RandomY, RandomZ);

		GetEntityControl()->SimpleRequestModel(0x113FD533);

		static int TIMER[32];
		Utils::DoTimedFunction(&TIMER[player.m_id], player.m_dropDelay, [&] {
			switch (player.m_dropType) {
				case 0: {
						GetEntityControl()->SimpleRequestModel(-1666779307);
						GetEntityControl()->SimpleRequestModel(dropModels[player.m_dropModel].m_result);

						static int TIMER2[32];
						Utils::DoTimedFunction(&TIMER2[player.m_id], 50, [&] {
							if (GetSelectedPlayer().m_dropModel == 0)
							OBJECT::CreateAmbientPickup(0x1E9A99F8, SpawnLocation.x, SpawnLocation.y, SpawnLocation.z, 0, player.m_dropAmount, -1666779307, false, true);
							else
							OBJECT::CreateAmbientPickup(0x1E9A99F8, SpawnLocation.x, SpawnLocation.y, SpawnLocation.z, 0, player.m_dropAmount, dropModels[player.m_dropModel].m_result, false, true); //0xDE78F17E
						});

						break;
					}
				case 1: {
						static Hash WepPickupArray[49] = { 0x6E4E65C2, 0x741C684A, 0x6C5B941A, 0xF33C83B0, 0xDF711959, 0xB2B5325E, 0x85CAA9B1, 0xB2930A14, 0xFE2A352C, 0x693583AD, 0x1D9588D3, 0x3A4C2AD2, 0x4D36C349, 0x2F36B434, 0xA9355DCD, 0x96B412A3, 0x9299C95B, 0x5E0683A1, 0x2DD30479, 0x1CD604C7, 0x7C119D58, 0xF9AFB48F, 0x8967B4F3, 0x3B662889, 0x2E764125, 0xFD16169E, 0xCB13D282, 0xC69DE3FF, 0x278D8734, 0x5EA16D74, 0x295691A9, 0x81EE601E, 0x88EAACA7, 0x872DC888, 0x815D66E8, 0xFA51ABF5, 0xC5B72713, 0x5307A4EC, 0x9CF13918, 0x0968339D, 0xBFEE6C3B, 0xEBF89D5F, 0x22B15640, 0x763F7121, 0xBED46EC5, 0x079284A9, 0x624F7213, 0xC01EB678, 0xBD4DE242 };
						OBJECT::CreateAmbientPickup(WepPickupArray[MISC::GetRandomIntInRange(0, NUMOF(WepPickupArray) - 1)], SpawnLocation.x, SpawnLocation.y, SpawnLocation.z, 0, 0, 1, false, true);
						break;
					}
				case 2: {
						OBJECT::CreateAmbientPickup(Utils::GetHashKey("PICKUP_HEALTH_STANDARD"), SpawnLocation.x, SpawnLocation.y, SpawnLocation.z, 0, player.m_dropAmount, 0x28781518, false, true);
						break;
					}
				case 3: {
						OBJECT::CreateAmbientPickup(Utils::GetHashKey("PICKUP_HEALTH_SNACK"), SpawnLocation.x, SpawnLocation.y, SpawnLocation.z, 0, player.m_dropAmount, 0x9012D675, false, true);
						break;
					}
				case 4: {
						OBJECT::CreateAmbientPickup(Utils::GetHashKey("PICKUP_ARMOUR_STANDARD"), SpawnLocation.x, SpawnLocation.y, SpawnLocation.z, 0, player.m_dropAmount, 0x29CB0F3C, false, true);
						break;
					}
				case 5: {
						OBJECT::CreateAmbientPickup(Utils::GetHashKey("PICKUP_PARACHUTE"), SpawnLocation.x, SpawnLocation.y, SpawnLocation.z, 0, player.m_dropAmount, 0x265D5856, false, true);
						break;
					}
				case 6: {
						OBJECT::CreateAmbientPickup(Utils::GetHashKey("PICKUP_AMMO_BULLET_MP"), SpawnLocation.x, SpawnLocation.y, SpawnLocation.z, 0, player.m_dropAmount, 0xB5DAAEC, false, true);
						break;
					}
				case 7: {
						OBJECT::CreateAmbientPickup(0x98D79EF, SpawnLocation.x, SpawnLocation.y, SpawnLocation.z, 0, 0, 1, 0, 1);
						break;
					}
				case 8: {
						OBJECT::CreateAmbientPickup(0x4316CC09, SpawnLocation.x, SpawnLocation.y, SpawnLocation.z, 0, 0, 1, 0, 1);
						break;
					}
			}
		});
	}
}

void DropsMenu::Init() {
	setParentSubmenu<PlayerMenu>();
	setName("Drops", true, false);

	addOption(NumberOption<int>(SCROLL, "Standard drop delay (ms)")
		.addNumber(vars.standarddropdelay, "%i", 50).addMin(200).addMax(5000)
		.addHotkey()
		.addTooltip("Control the speed of the money drops"));

	addOption(ToggleOption("Standard money drop")
		.addToggle(GetSelectedPlayer().m_standardMoneyDrop)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_standardMoneyDrop); })
		.addTranslation().addTooltip("Standard money drop"));

	addOption(ToggleOption("Standard circle drop")
		.addToggle(GetSelectedPlayer().m_standardCircleDrop)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_standardCircleDrop); })
		.addTranslation().addTooltip("Standard circle drop"));

	/*addOption(ToggleOption("Standard ped drop")
		.addToggle(GetSelectedPlayer().m_standardPedDrop)
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_standardPedDrop); })
		.addTranslation().addTooltip("Standard ped drop"));*/

	addOption(BreakOption("Editable Drops").addTranslation());

	addOption(ScrollOption<int>(SCROLLSELECT, "Drop type")
		.addScroll(GetSelectedPlayer().m_dropType, 0, NUMOF(dropTypes) - 1, dropTypes)
		.addOnUpdate([](ScrollOption<int>* op) { op->addScroll(GetSelectedPlayer().m_dropType, 0, NUMOF(dropTypes) - 1, dropTypes); })
		.addTranslation().addTooltip("Drop type"));

	addOption(ScrollOption<int>(SCROLLSELECT, "Drop model")
		.addRequirement([] { return GetSelectedPlayer().m_dropType == 0; })
		.addScroll(GetSelectedPlayer().m_dropModel, 0, NUMOF(dropModels) - 1, dropModels)
		.addOnUpdate([](ScrollOption<int>* op) { op->addScroll(GetSelectedPlayer().m_dropModel, 0, NUMOF(dropModels) - 1, dropModels); })
		.addTranslation().addTooltip("Drop model"));

	addOption(NumberOption<int>(SCROLL, "Drop amount")
		.addRequirement([] { return GetSelectedPlayer().m_dropType == 0; })
		.addMin(0).setScrollSpeed(10)
		.addMax(GetSelectedPlayer().m_dropType == 0 ? 2500 : 1000000).addNumber(GetSelectedPlayer().m_dropAmount, "%d", 1)
		.addOnUpdate([](NumberOption<int>* op) { op->addMax(GetSelectedPlayer().m_dropType == 0 ? 2500 : 1000000).addNumber(GetSelectedPlayer().m_dropAmount, "%d", 1); })
		.addTranslation().addTooltip("Drop amount"));

	addOption(NumberOption<float>(SCROLL, "Drop height")
		.addMin(0.0f).addMax(1000.f).setScrollSpeed(10)
		.addNumber(GetSelectedPlayer().m_dropHeight, "%.1f", 0.1f)
		.addOnUpdate([](NumberOption<float>* op) { op->addNumber(GetSelectedPlayer().m_dropHeight, "%.1f", 0.1f); })
		.addTranslation().addTooltip("Drop height"));

	addOption(NumberOption<float>(SCROLL, "Drop radius")
		.addMin(0.0f).addMax(1000.f).setScrollSpeed(10)
		.addNumber(GetSelectedPlayer().m_dropRadius, "%.1f", 0.1f)
		.addOnUpdate([](NumberOption<float>* op) { op->addNumber(GetSelectedPlayer().m_dropRadius, "%.1f", 0.1f); })
		.addTranslation().addTooltip("Drop radius"));

	addOption(NumberOption<int>(SCROLL, "Drop delay (ms)")
		.addMin(0).addMax(10000).setScrollSpeed(10)
		.addOnUpdate([](NumberOption<int>* op) { op->addNumber(GetSelectedPlayer().m_dropDelay, "%d", 1); })
		.addTranslation().addTooltip("Drop delay in milliseconds"));

	addOption(ToggleOption("Enable drop")
		.addOnUpdate([](ToggleOption* option) {option->addToggle(GetSelectedPlayer().m_enableDrop); })
		.addTranslation().addTooltip("Enable drop"));
}

/*Update once when submenu is opened*/
void DropsMenu::UpdateOnce() {}

/*Update while submenu is active*/
void DropsMenu::Update() {}

/*Background update*/
void DropsMenu::FeatureUpdate() {
	OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_standardMoneyDrop) StandardMoneyDrop(player);});
	OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_standardCircleDrop) StandardCircleDrop(player); });
	OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_enableDrop) Drop(player); });
	OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_standardPedDrop) StandardCircleDrop2(player); });
}

/*Singleton*/
DropsMenu* _instance;
DropsMenu* DropsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new DropsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
DropsMenu::~DropsMenu() { delete _instance; }