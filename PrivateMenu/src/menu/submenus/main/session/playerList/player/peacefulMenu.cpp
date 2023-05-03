#include "stdafx.h"
#include "peacefulMenu.h"
#include "peaceful/peacefulAttachmentMenu.h"
#include "../playerMenu.h"

using namespace PeacefulMenuVars;

namespace PeacefulMenuVars {

	Vars vars;

	Hash WepPickupArray[49] = {
		0x6E4E65C2, 0x741C684A, 0x6C5B941A, 0xF33C83B0, 0xDF711959, 0xB2B5325E, 0x85CAA9B1, 0xB2930A14, 0xFE2A352C,
		0x693583AD, 0x1D9588D3, 0x3A4C2AD2, 0x4D36C349, 0x2F36B434, 0xA9355DCD, 0x96B412A3, 0x9299C95B, 0x5E0683A1,
		0x2DD30479, 0x1CD604C7, 0x7C119D58, 0xF9AFB48F, 0x8967B4F3, 0x3B662889, 0x2E764125, 0xFD16169E, 0xCB13D282,
		0xC69DE3FF, 0x278D8734, 0x5EA16D74, 0x295691A9, 0x81EE601E, 0x88EAACA7, 0x872DC888, 0x815D66E8, 0xFA51ABF5,
		0xC5B72713, 0x5307A4EC, 0x9CF13918, 0x0968339D, 0xBFEE6C3B, 0xEBF89D5F, 0x22B15640, 0x763F7121, 0xBED46EC5,
		0x079284A9, 0x624F7213, 0xC01EB678, 0xBD4DE242
	};

	Hash WeaponHashes[86] = {
		126349499,
		2694266206,
		1233104067,
		101631238,
		911657153,
		1834241177,
		0x1B06D571,
		0x5EF9FEC4,
		0x22D8FE39,
		0x99AEEB3B,
		0x2BE6766B,
		0x13532244,
		0xBFEFFF6D,
		0x83BF0278,
		0xAF113F99,
		0x9D07F764,
		0x7FD62962,
		0x1D073A89,
		0x7846A318,
		0xE284C527,
		0xC472FE2,
		0x5FC3C11,
		0xA284510B,
		0xB1CA77B1,
		0x42BF8A85,
		0x93E220BD,
		0xFDBC8A50,
		0x2C3731D9,
		0x24B17070,
		0x34A67B97,
		0xFBAB5776,
		0x99B507EA,
		0x678B81B1,
		0x4E875F73,
		0x958A4A8F,
		0x84BD7BFD,
		0x440E4788,
		0xEFE7E2DF,
		0x9D61E50F,
		0xF9E6AA4B,
		0xC0A3098D,
		0xBFD21232,
		0x476BF155,
		0xAF3696A1,
		0xB62D1F67,
		0xD205520E,
		0x7F229F94,
		0x61012683,
		0x83839C4,
		0x92A27487,
		0xA89CB99E,
		0x7F7497E5,
		0x47757124,
		0x3AABBBAA,
		0xC734385A,
		0xAB564B93,
		0x63AB0442,
		0xF9DCBF2D,
		0xA3D4D34,
		0xD8DF3C3C,
		0xDC4DB296,
		0xDD5DF8D9,
		0xDB1AA450,
		0xEF951FBB,
		0x624FE830,
		0x8BB05FD7,
		0xC1B3C3D1,
		0xDFE37640,
		0x78A97CD0,
		0xA914799,
		0x394F415C,
		0x19044EE0,
		0x781FE4A,
		0x12E82D3D,
		0x176898A6,
		0x787F0BB,
		0xE232C28C,
		0xD04C944D,
		0x0A3D4D34,
		0x6D544C99,
		0x2C082D7D,
		0xCD274149,
		0xBD248B55,
		0xBA45E8B8,
		0x94117305,
		0x3813FC08,
	};

	ScrollStruct<int> bulletImpactss[] = {
		TranslationString("Money Bags", true), 0,
		TranslationString("Teleport You", true), 1,
		TranslationString("Explosion", true), 2,
		TranslationString("Print Position", true), 3,
		TranslationString("Airstrike", true), 4,
		TranslationString("Flare", true), 5,
		TranslationString("Water Fountain", true), 6,
		TranslationString("Gas Fountain", true), 7
	};



	void SpawnDrop(Hash drop, Hash model, int value, Vector3 coords) {
		GetEntityControl()->SimpleRequestModel(model);
		OBJECT::CreateAmbientPickup(drop, coords.x, coords.y, coords.z, 0, value, model, 0, 1);
		STREAMING::SetModelAsNoLongerNeeded(model);
	}

	void GiveAllWeapons(SPlayer& player) {
		if (player.m_exists) {
			for (Hash& wep : WeaponHashes) {
				if (WEAPON::IsWeaponValid(wep)) {
					WEAPON::GiveDelayedWeaponToPed(player.m_ped, wep, 1000, 0);
				}
			}
		}
	}

	void SpawnCloneBodyguard(SPlayer& player) {

		Hash RailGun = Utils::GetHashKey("WEAPON_RAILGUN");
		int MyGroup = PLAYER::GetPlayerGroup(player.m_id);

		Ped clone = PED::ClonePed(player.m_ped, ENTITY::GetEntityHeading(player.m_ped), true, false);

		auto blip = HUD::AddBlipForEntity(clone); HUD::SetBlipSprite(blip, 480); HUD::SetBlipColour(blip, 63);

		PED::SetPedAsGroupLeader(player.m_ped, MyGroup);
		PED::SetPedAsGroupMember(clone, MyGroup);
		PED::SetPedNeverLeavesGroup(clone, true);
		ENTITY::SetEntityInvincible(clone, true);
		PED::SetPedCombatAbility(clone, 100);
		PED::SetPedCanSwitchWeapon(clone, true);
		PED::SetGroupFormation(MyGroup, 3);
		PED::SetPedMaxHealth(clone, 5000);
		ENTITY::SetEntityVisible(clone, true, true);
		WEAPON::GiveWeaponToPed(clone, RailGun, 9999, false, true);
		BRAIN::TaskCombatHatedTargetsAroundPed(player.m_ped, 100, clone);
		PED::SetPedCanRagdoll(clone, false);
		PED::SetPedCanRagdollFromPlayerImpact(clone, false);
		PED::SetPedCanBeKnockedOffVehicle(clone, false);
		PED::SetPedRagdollOnCollision(clone, false);
	}

	void CopyOutfit(SPlayer& player) {
		for (size_t i = 0; i < 12; i++) PED::SetPedComponentVariation(GetLocalPlayer().m_ped, i, PED::GetPedDrawableVariation(player.m_ped, i), PED::GetPedTextureVariation(player.m_ped, i), 0);
		for (size_t i = 0; i < 3; i++) PED::SetPedPropIndex(GetLocalPlayer().m_ped, i, PED::GetPedPropIndex(player.m_ped, i), PED::GetPedPropTextureIndex(player.m_ped, i), 1);
	}

	void CopyOutfitAndCharacter(SPlayer& player) { // "MP_F_Freemode_01" or "MP_M_Freemode_01"
		GetFiberPool()->DoJob([=] {
			WAIT(1000);
			int Ammo = -1;
			for (int i = 0; i < 82; i++) {
				WEAPON::GetMaxAmmo(GetLocalPlayer().m_ped, WeaponHashes[i], &Ammo);
				WEAPON::GiveWeaponToPed(GetLocalPlayer().m_ped, WeaponHashes[i], Ammo, false, true);
			}
		});
		Hash hisModel = ENTITY::GetEntityModel(player.m_ped);
		Hash myModel = ENTITY::GetEntityModel(GetLocalPlayer().m_ped);
		if (hisModel == myModel) PED::ClonePedToTarget(player.m_ped, GetLocalPlayer().m_ped); /*best native tbh*/
		else {
			GetEntityControl()->SimpleRequestModel(hisModel);
			PLAYER::SetPlayerModel(GetLocalPlayer().m_id, hisModel);
			GetFiberPool()->DoJob([=] {
				WAIT(150);
				PED::ClonePedToTarget(player.m_ped, GetLocalPlayer().m_ped);
			});
		}
	}

	void GiveMoneyGun(SPlayer& player) {

		Vector3 coords;

		if (PED::IsPedShooting(player.m_ped)) {
			if (WEAPON::GetPedLastWeaponImpactCoord(player.m_ped, &coords)) {
				constexpr int CashHash = -1666779307;
				GetEntityControl()->SimpleRequestModel(CashHash);
				Entity e = OBJECT::CreateAmbientPickup(0x1E9A99F8, coords.x, coords.y, coords.z + 2, 0, 2500, CashHash, false, true);
				ENTITY::SetEntityAsNoLongerNeeded(&e);
			}
		}
	}

	void GiveOptionGun(SPlayer& player) {

			if (PED::IsPedShooting(player.m_ped)) {
				if (vars.impactAmmoVall == 0) {
					Vector3 coords;
					if (WEAPON::GetPedLastWeaponImpactCoord(player.m_ped, &coords)) {
						constexpr int CashHash = -1666779307;
						GetEntityControl()->SimpleRequestModel(CashHash);
						Entity e = OBJECT::CreateAmbientPickup(0x1E9A99F8, coords.x, coords.y, coords.z + 2, 0, 2500, CashHash, false, true);
						ENTITY::SetEntityAsNoLongerNeeded(&e);
					}
				}
				else {
					//Raycast cast = CastInfront(999.0f, CAM::GetGameplayCamCoord(), -1);
					Vector3 Coords;
					//if (cast.endCoords != Vector3(0, 0, 0)) {
					if (WEAPON::GetPedLastWeaponImpactCoord(player.m_ped, &Coords)) {
						//Vector3 Coords = cast.endCoords;
						switch (vars.impactAmmoVall) {
						case 1:ENTITY::SetEntityCoords(GetLocalPlayer().m_ped, Coords.x, Coords.y, Coords.z, 0, 0, 0, 1); break;
						case 2:FIRE::AddExplosion(Coords.x, Coords.y, Coords.z, 0, 5, 1, 0, 0, 0); break;
						case 3:GetRenderer()->NotifyMap(va("%.3f, %.3f, %.3f", Coords.x, Coords.y, Coords.z)); break;
						case 4:MISC::ShootSingleBulletBetweenCoords(Coords.x, Coords.y, Coords.z + 50, Coords.x, Coords.y, Coords.z, 250, 0, 0xF8A3939F, player.m_ped, 1, 1, 1000); break;
						case 5:Natives::AddOwnedExplosion(player.m_ped, Coords.x, Coords.y, Coords.z, 22, 5.0, true, false, 0); break;
						case 6:Natives::AddOwnedExplosion(player.m_ped, Coords.x, Coords.y, Coords.z, 13, 5.0, true, false, 0); break;
						case 7:Natives::AddOwnedExplosion(player.m_ped, Coords.x, Coords.y, Coords.z, 9, 5.0, true, false, 0); break;
						}
					}
				}
			}
		}

	bool IsWeaponObject(Object object) {
		uint64_t EntityStruct = PoolManager::GetEntityAddress(object);
		if (EntityStruct != 0) {
			uint64_t WeaponStruct = *(uint64_t*)(EntityStruct + 0x340);
			return (WeaponStruct != 0);
		}
		return false;
	}

	void RemoveAttachments(SPlayer& player) {

					PoolManager::Update();
					auto peds = PedPool::GetPeds();
					auto _peds = &peds[0];
					for (int i = 0; i < peds.size(); ++i) {
						Ped p = _peds[i];
						if (ENTITY::DoesEntityExist(p)) {
							if (!PED::IsPedAPlayer(p)) {
								if (!PED::IsPedInAnyVehicle(p, 1)) {
									if (ENTITY::IsEntityAttachedToEntity(p, player.m_ped)) {
										GetRenderer()->NotifyMap("Removed attached ped from player");
										GetEntityControl()->RequestControl("[AP]", p, [](Entity entity) {ENTITY::DetachEntity(entity, true, true); ENTITY::DeleteEntity(&entity); });
									}
								}
							}
						}
					}

					auto vehicles = VehiclePool::GetVehicles();
					auto _vehicles = &vehicles[0];
					for (int i = 0; i < vehicles.size(); ++i) {
						Vehicle v = _vehicles[i];
						if (ENTITY::DoesEntityExist(v)) {
							if (v != player.m_vehicle) {
								if (ENTITY::GetEntityAttachedTo(v) == player.m_ped) {
									GetRenderer()->NotifyMap("Removed attached vehicle from player");
									GetEntityControl()->RequestControl("[AP]", v, [](Entity entity) {ENTITY::DetachEntity(entity, true, true); ENTITY::DeleteEntity(&entity); });
								}
							}
						}
					}

					auto objects = ObjectPool::GetObjects();
					auto _objects = &objects[0];
					for (int i = 0; i < objects.size(); ++i) {
						Object o = _objects[i];
						if (ENTITY::DoesEntityExist(o)) {
							if (!IsWeaponObject(o) && ENTITY::GetEntityModel(o) != 0x4FAA899A) {
								if (ENTITY::IsEntityAttachedToEntity(o, player.m_ped)) {
									GetRenderer()->NotifyMap("Removed attached object from player");
									GetEntityControl()->RequestControl("[AP]", o, [](Entity entity) {ENTITY::DetachEntity(entity, true, true); ENTITY::DeleteEntity(&entity); });
								}
							}
						}
					}
				}


	void RainWeapons(SPlayer& player) {
		static int TIMER[32];

		Utils::DoTimedFunction(&TIMER[player.m_id], 50, [&] {
			float RandomX = MISC::GetRandomFloatInRange(-10, 10);
			float RandomY = MISC::GetRandomFloatInRange(-10, 10);
			float RandomZ = MISC::GetRandomFloatInRange(10, 20);

			Vector3 SpawnLocation = ENTITY::GetOffsetFromEntityInWorldCoords(player.m_ped, RandomX, RandomY, RandomZ);
			Hash hash = WepPickupArray[MISC::GetRandomIntInRange(0, NUMOF(WepPickupArray) - 1)];
			GetEntityControl()->RequestModel(hash, [&](int m) {
				OBJECT::CreateAmbientPickup(m, SpawnLocation.x, SpawnLocation.y, SpawnLocation.z, 0, 0, 1, false, true);
			});
		});
	}

	void DemiGodmode(SPlayer& player) {
		if (!player.m_isInVehicle) {
			int health = ENTITY::GetEntityHealth(player.m_ped);
			int health_max = ENTITY::GetEntityMaxHealth(player.m_ped);
			if (health < health_max) {
				SpawnDrop(0x8F707C18, 0xE6CB661E, health_max - health, player.m_coordinates);
			}
		}
	}

	void BulletGodmode(SPlayer& player) {
		Hash SemigodObject = Utils::GetHashKey("prop_juicestand");
		GetEntityControl()->SimpleRequestModel(SemigodObject);
		int PropJuice = OBJECT::CreateObject(SemigodObject, 0, 0, 0, true, 1, 0);
		GetEntityControl()->SimpleRequestModel(PropJuice);
		ENTITY::SetEntityVisible(PropJuice, 0, 0);
		ENTITY::AttachEntityToEntity(PropJuice, player.m_ped, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 2, 1);
		ENTITY::SetEntityAlpha(PropJuice, 0, true);
	}

	void SetWaypoint(SPlayer& player) {
		HUD::SetNewWaypoint(player.m_coordinates.x, player.m_coordinates.y);
	}

	void SetWaypointLoop(SPlayer& player) {
		static int TIMER[32];
		Utils::DoTimedFunction(&TIMER[player.m_id], 100, [&] {
		HUD::SetNewWaypoint(player.m_coordinates.x, player.m_coordinates.y);
		});
	}

	ScrollStruct<CrewIconId> Icons[] = {
		TranslationString("Rockstar", true), CREW_ICON_ROCKSTAR,
		TranslationString("Kappa", true), CREW_ICON_KAPPA,
		TranslationString("Doge", true), CREW_ICON_DOGE,
		TranslationString("Trollface", true), CREW_ICON_TROLLFACE,
		TranslationString("Anonymous", true), CREW_ICON_ANONYMOUS,
		TranslationString("Spoderman", true), CREW_ICON_SPODERMAN,
		TranslationString("Skull", true), CREW_ICON_SKULL,
		TranslationString("U MAD?", true), CREW_ICON_UMAD,
		TranslationString("Anime Tiddies", true), CREW_ICON_ANIME_TIDDIES,
		TranslationString("Redtube", true), CREW_ICON_REDTUBE
	};

	ScrollStruct<ParticleManStruct> m_particleManParticles[] = {
		TranslationString("Light", true),{ "scr_rcbarry2", "scr_exp_clown_trails", 1.2f }, //.2
		TranslationString("Alien Teleport", true),{ "scr_rcbarry1", "scr_alien_teleport", 1.2f }, //.2
		TranslationString("Money", true),{ "scr_paletoscore", "scr_paleto_banknotes", 1.9f }, //.9
		TranslationString("Blood", true),{ "scr_solomon3", "scr_trev4_747_blood_impact", 0.9f }, //.9
		TranslationString("Alien Disintegrate", true),{ "scr_rcbarry1", "scr_alien_disintegrate", 1.2f }, //.2
		TranslationString("Electric", true),{ "scr_trevor1", "scr_trev1_trailer_boosh", 1.2f }, //.2
		TranslationString("Fire", true),{ "scr_agencyheist", "scr_fbi_dd_breach_smoke", 1.2f }, //.2
		TranslationString("Clown Death", true),{ "scr_rcbarry2", "scr_clown_death", 1.2f }, //.2
		TranslationString("Clown Appears", true),{ "scr_rcbarry2", "scr_clown_appears", 0.8f }, //.08
		TranslationString("Flowers", true),{ "scr_rcbarry2", "scr_exp_clown", 0.8f }, //.08
		TranslationString("Fireworks", true),{ "scr_indep_fireworks", "scr_indep_firework_starburst", 1.2f } //.2
	};

	void ParticleMan(ParticleManStruct& pms, SPlayer& player) {
		static int TIMER[32];

		Utils::DoTimedFunction(&TIMER[player.m_id], 200, [&] {
			STREAMING::RequestNamedPtfxAsset(pms.m_pOne);
			GRAPHICS::_UseParticleFxAssetNextCall(pms.m_pOne);
			GRAPHICS::_StartParticleFxNonLoopedAtCoord2(pms.m_pTwo, player.m_coordinates.x, player.m_coordinates.y, player.m_coordinates.z, 0, 0, 0, pms.m_size, 0, 0, 0);
		});
	}
}

void PeacefulMenu::Init() {
	setParentSubmenu<PlayerMenu>();
	setName("Peaceful", true, false);

	addOption(SubmenuOption("Attachment")
		.addSubmenu<PeacefulAttachmentMenu>()
		.addTooltip("Attaching you to them and them to you").addTranslation());

	addOption(BreakOption("General").addTranslation());

	addOption(ButtonOption("Give all weapons")
		.addFunction([] { GiveAllWeapons(GetSelectedPlayer()); })
		.addTooltip("Give all weapons").addTranslation());

	addOption(ButtonOption("Spawn clone bodyguard")
		.addFunction([] { SpawnCloneBodyguard(GetSelectedPlayer()); })
		.addTooltip("Spawn clone bodyguard").addTranslation());

	addOption(ButtonOption("Clear area")
		.addFunction([] {
		Vector3 coords = GetSelectedPlayer().m_coordinates;
		MISC::_ClearAreaOfEverything(coords.x, coords.y, coords.z, 50.0f, true, true, true, true);
	})
		.addTooltip("CLear the players area").addTranslation());

	addOption(ToggleOption("Rain weapons")
		.addToggle(GetSelectedPlayer().m_rainWeapons)
		.addOnUpdate([](ToggleOption* option) { option->addToggle(GetSelectedPlayer().m_rainWeapons); })
		.addTooltip("Rain weapons on the player").addTranslation());

	addOption(ButtonOption("Remove attachments")
		.addFunction([] { RemoveAttachments(GetSelectedPlayer()); })
		.addTranslation().addHotkey()
		.addTooltip("Clear the players attached entities").addTranslation());

	addOption(ScrollOption<ParticleManStruct>(TOGGLE, "Particles")
		.addToggle(GetSelectedPlayer().m_particles)
		.addScroll(vars.particleman, 0, NUMOF(m_particleManParticles) - 1, m_particleManParticles)
		.addOnUpdate([](ScrollOption<ParticleManStruct>* option) { option->addToggle(GetSelectedPlayer().m_particles); })
		.addTooltip("Player will emit particles").addHotkey());

	addOption(BreakOption("Edit Bullets").addTranslation());

	addOption(ScrollOption<int>(TOGGLE, "Give player impact bullets")
		.addToggle(GetSelectedPlayer().m_giveOptionGun)
		.addScroll(vars.impactAmmoVall, 0, NUMOF(bulletImpactss) - 1, bulletImpactss)
		.addOnUpdate([](ScrollOption<int>* option) { option->addToggle(GetSelectedPlayer().m_giveOptionGun); })
		.addTranslation().addHotkey()
		.addTooltip("Give player impact ammo"));

	addOption(BreakOption("Godmode Options").addTranslation());

	addOption(ToggleOption("Demi godmode")
		.addToggle(GetSelectedPlayer().m_demiGodmode)
		.addOnUpdate([](ToggleOption* option) { option->addToggle(GetSelectedPlayer().m_demiGodmode); })
		.addTooltip("Give the player demi godmode").addTranslation());

	addOption(ButtonOption("Bullet godmode")
		.addFunction([] { BulletGodmode(GetSelectedPlayer()); })
		.addTooltip("Give the player demi godmode from bullets").addTranslation());

	addOption(BreakOption("Outfit Copying").addTranslation());

	addOption(ButtonOption("Copy outfit")
		.addFunction([] { CopyOutfit(GetSelectedPlayer()); })
		.addTooltip("Copy the players outfit").addTranslation());

	addOption(ButtonOption("Copy outfit & character model")
		.addFunction([] { CopyOutfitAndCharacter(GetSelectedPlayer()); })
		.addTooltip("Copy the players outfit and his character, face included. (Your character has to be the same sex)").addTranslation());

	addOption(BreakOption("Waypoint").addTranslation());

	addOption(ButtonOption("Set waypoint on player location")
		.addFunction([] { SetWaypoint(GetSelectedPlayer()); })
		.addTooltip("This will set a waypoint on the players location").addTranslation());

	addOption(ToggleOption("Constant waypoint on player location")
		.addToggle(GetSelectedPlayer().m_setwaypoint)
		.addOnUpdate([](ToggleOption* option) { option->addToggle(GetSelectedPlayer().m_setwaypoint); })
		.addTooltip("This will constantly set a waypoint on the players location").addTranslation());

	addOption(BreakOption("Messaging").addTranslation());

	addOption(ScrollOption<CrewIconId>(SCROLLSELECT, "Send message to player")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addScroll(vars.iconIndex, 0, NUMOF(Icons) - 1, Icons)
		.addFunction([] {
		GetMenuInput()->AddToQueue([] {
			string senderID;
			string recieverID;
				string subject;
				if (GetMenuInput()->Text("Enter clan tag", subject, 0, 4)) {
					string message;
					if (GetMenuInput()->Text("Enter message", message, 0, 100)) {

						long long reciever = _atoi64(recieverID.c_str());
							uint64_t base = PoolManager::GetEntityAddress(GetSelectedPlayer().m_ped);
							if (base) {
								CPed* ped = (CPed*)(base);
								reciever = ped->PlayerInfo->RockstarID;
							}

						FingerOfGod::sendCrewMessageCommand(reciever, 0, Icons[vars.iconIndex].m_result, subject.c_str(), message.c_str());
						GetRenderer()->NotifyMap("Message Sent");
					}
				}
		});
	})
		.addTooltip("Send a message to this player"));
}

/*Update once when submenu is opened*/
void PeacefulMenu::UpdateOnce() {}

/*Update while submenu is active*/
void PeacefulMenu::Update() {}

/*Background update*/
void PeacefulMenu::FeatureUpdate() {
	OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_rainWeapons) RainWeapons(player); });
	OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_demiGodmode) DemiGodmode(player); });
	OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_bulletgodmode) BulletGodmode(player); });
	OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_giveMoneyGun) GiveMoneyGun(player); });
	OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_giveOptionGun) GiveOptionGun(player); });
	OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_particles) ParticleMan(m_particleManParticles[vars.particleman].m_result, player); });
	OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_setwaypoint) SetWaypointLoop(player); });
}

/*Singleton*/
PeacefulMenu* _instance;

PeacefulMenu* PeacefulMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new PeacefulMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}

PeacefulMenu::~PeacefulMenu() { delete _instance; }
