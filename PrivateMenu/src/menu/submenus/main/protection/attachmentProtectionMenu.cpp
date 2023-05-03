#include "stdafx.h"
#include "attachmentProtectionMenu.h"
#include "../protectionMenu.h"
#include "menu\submenus\main\world\pedManagerMenu.h"
#include "menu\submenus\main\world\trafficManagerMenu.h"
#include "menu\submenus\main\session\playerList\player\griefingMenu.h"
#include "menu\submenus\main\local\modelMenu.h"

using namespace AttachmentProtectionMenuVars;

namespace AttachmentProtectionMenuVars {
	Vars vars;

	Hash usableWeaponHashes[85] = {
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
	};

	int GetNetObjID(Entity entity) {
		uint64_t entityStruct = PoolManager::GetEntityAddress(entity);
		if (entityStruct) {
			uint64_t netObjStruct = *(uint64_t*)(entityStruct + 0xD0);
			if (netObjStruct) return *(int*)(netObjStruct + 0xA);
		}
		return 0;
	}

	bool IsWeaponObject(Object object) {
		uint64_t EntityStruct = PoolManager::GetEntityAddress(object);
		if (EntityStruct != 0) {
			uint64_t WeaponStruct = *(uint64_t*)(EntityStruct + 0x340);
			return (WeaponStruct != 0);
		}
		return false;
	}

	void RemoveAttachments() {
		/*PoolManager::Update();
		vector<Object> e = ObjectPool::GetObjects();
		Object* objects = &e[0];
		for (int i = 0; i < e.size(); ++i) {
		Object obj = objects[i];
		if (ENTITY::IsEntityAttachedToEntity(obj, GetLocalPlayer().m_id)) {
		GetEntityControl()->SimpleRequestControl(obj);
		ENTITY::DetachEntity(obj, true, true);
		ENTITY::DeleteEntity(&obj);
		}
		}*/

		PoolManager::Update();
		auto peds = PedPool::GetPeds();
		auto _peds = &peds[0];
		for (int i = 0; i < peds.size(); ++i) {
			Ped p = _peds[i];
			if (ENTITY::DoesEntityExist(p)) {
				if (!PED::IsPedAPlayer(p)) {
					if (!PED::IsPedInAnyVehicle(p, 1)) {
						if (ENTITY::IsEntityAttachedToEntity(p, GetLocalPlayer().m_ped)) {
							GetRenderer()->NotifyMap("Removed attached ped");
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
				if (v != GetLocalPlayer().m_vehicle) {
					if (ENTITY::GetEntityAttachedTo(v) == GetLocalPlayer().m_ped) {
						GetRenderer()->NotifyMap("Removed attached vehicle");
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
					if (ENTITY::IsEntityAttachedToEntity(o, GetLocalPlayer().m_ped)) {
						GetRenderer()->NotifyMap("Removed attached object");
						GetEntityControl()->RequestControl("[AP]", o, [](Entity entity) {ENTITY::DetachEntity(entity, true, true); ENTITY::DeleteEntity(&entity); });
					}
				}
			}
		}
	}

	void DetachAttachments() {

		Hash CharModel = ENTITY::GetEntityModel(GetLocalPlayer().m_ped);
		GetEntityControl()->SimpleRequestModel(CharModel);

		float heading = ENTITY::GetEntityHeading(GetLocalPlayer().m_ped);

		Ped newPed = PED::CreatePed(26, CharModel, GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, GetLocalPlayer().m_coordinates.z, 1, 1, 0);

		ENTITY::SetEntityVisible(newPed, false, false);
		ENTITY::SetEntityAlpha(newPed, 0, true);

		PED::ClonePedToTarget(GetLocalPlayer().m_ped, newPed);
		PLAYER::SetPlayerModel(GetLocalPlayer().m_id, CharModel);

		GetFiberPool()->DoJob([=] {
			WAIT(100);
			GetEntityControl()->SimpleRequestModel(newPed);
			PED::ClonePedToTarget(newPed, GetLocalPlayer().m_ped);
			GetEntityControl()->SimpleRequestControl(newPed);
			ENTITY::SetEntityAsMissionEntity(newPed, true, true);
			GetEntityControl()->SimpleDeleteEntity(newPed);
		});

		GetFiberPool()->DoJob([=] {
			WAIT(1000);
			int Ammo = -1;
			for (int i = 0; i < 82; i++) {
				WEAPON::GetMaxAmmo(GetLocalPlayer().m_ped, usableWeaponHashes[i], &Ammo);
				WEAPON::GiveWeaponToPed(GetLocalPlayer().m_ped, usableWeaponHashes[i], Ammo, false, true);
			}
		});

		ENTITY::SetEntityHeading(GetLocalPlayer().m_ped, heading);
	}

}

void AttachmentProtectionMenu::Init() {
	setParentSubmenu<ProtectionMenu>();
	setName("Attachment protections", true, true);

	addOption(ToggleOption("Notify on attack")
		.addToggle(NetEvent::vars.notifyAT)
		.canBeSaved().addHotkey()
		.addTooltip("This will notify you when the attacks are done to you by others").addTranslation());

	addOption(ToggleOption("Redirect attachments")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.redirectObjects)
		.addTooltip("This will redirect attached entities to the player who sent them")
		.addTranslation().canBeSaved().addHotkey());

	addOption(ToggleOption("Entity attachment")
		.addToggle(vars.entityAttachment)
		.addTooltip("Detach all attached entities")
		.addTranslation().canBeSaved().addHotkey()
		.addRequirement([] { return GetAuth()->IsVIP(); }));

	addOption(ButtonOption("Delete nearby peds and vehicles")
		.addFunction([] {
		TrafficManagerMenuVars::RunTrafficManagerWorker(VEHICLE_DELETE);
		PedManagerMenuVars::RunPedManagerWorker(PED_DELETE);
	})
		.addTooltip("Delete all vehicles and peds near to you")
		.addHotkey().addTranslation());

	addOption(ButtonOption("Detach attached objects")
		.addFunction([] {
		DetachAttachments();
	})
		.addTooltip("Detach attached objects on yourself")
		.addHotkey().addTranslation());

	addOption(ButtonOption("Delete attached objects")
		.addFunction([] {
		RemoveAttachments();
	})
		.addTooltip("Delete attached objects on yourself")
		.addHotkey().addTranslation());



}

/*Update once when submenu is opened*/
void AttachmentProtectionMenu::UpdateOnce() {}

/*Update while submenu is active*/
void AttachmentProtectionMenu::Update() {}

/*Background update*/
void AttachmentProtectionMenu::FeatureUpdate() {
	
	if (vars.entityAttachment) {
		if (NETWORK::NetworkIsSessionActive()) {
			PoolManager::Update();

			auto peds = PedPool::GetPeds();
			for (int i = 0; i < peds.size(); ++i) {
				Ped p = peds[i];
				if (ENTITY::DoesEntityExist(p)) {
					if (!PED::IsPedAPlayer(p)) {
						if (!PED::IsPedInAnyVehicle(p, 1)) {
							if (ENTITY::GetEntityAttachedTo(p) == GetLocalPlayer().m_ped) {
								int net = GetNetObjID(p);
								Player id;
								if (IsNetObjSaved(net, &id)) {
									if (vars.redirectObjects) {
										if (NetEvent::vars.notifyAT) GetRenderer()->NotifyMap(va("Attachment: Blocked\nFrom: %s\nType: Ped", GetPlayer(id).m_name), false);
										if (NetEvent::vars.notifyAT) GetRenderer()->NotifyMap(va("Redirecting attachment to %s", GetPlayer(id).m_name), false);
										GetEntityControl()->SimpleRequestControl(p);
										ENTITY::AttachEntityToEntity(p, GetPlayer(id).m_ped, 0, 0, 0, 0, 0, 0, 180, 1, 0, 0, 1, 2, 1);
									} else {
										if (NetEvent::vars.notifyAT) GetRenderer()->NotifyMap(va("Attachment: Blocked\nFrom: %s\nType: Ped", GetPlayer(id).m_name), false);
										GetEntityControl()->SimpleRequestControl(p);
										ENTITY::SetEntityAsMissionEntity(p, true, true);
										ENTITY::DetachEntity(p, true, true);
										ENTITY::SetEntityCoords(p, 0, 0, 0, 0, 0, 0, 1);
										ENTITY::DeleteEntity(&p);
									}
								} else {
									GetRenderer()->NotifyMap("Removed attached ped");
									GetEntityControl()->RequestControl("[AP]", p, [](Entity entity) { ENTITY::DetachEntity(entity, true, true); ENTITY::DeleteEntity(&entity); });
								}
							}
						}
					}
				}
			}

			auto vehicles = VehiclePool::GetVehicles();
			for (int i = 0; i < vehicles.size(); ++i) {
				Vehicle v = vehicles[i];
				if (ENTITY::DoesEntityExist(v)) {
					if (v != GetLocalPlayer().m_vehicle) {
						if (ENTITY::GetEntityAttachedTo(v) == GetLocalPlayer().m_ped) {
							int net = GetNetObjID(v);
							Player id;
							if (IsNetObjSaved(net, &id)) {
								if (vars.redirectObjects) {
									if (NetEvent::vars.notifyAT) GetRenderer()->NotifyMap(va("Attachment: Blocked\nFrom: %s\nType: Vehicle", GetPlayer(id).m_name), false);
									if (NetEvent::vars.notifyAT) GetRenderer()->NotifyMap(va("Redirecting attachment to %s", GetPlayer(id).m_name), false);
									GetEntityControl()->SimpleRequestControl(v);
									ENTITY::AttachEntityToEntity(v, GetPlayer(id).m_ped, 0, 0, 0, 0, 0, 0, 180, 1, 0, 0, 1, 2, 1);
								} else {
									if (NetEvent::vars.notifyAT) GetRenderer()->NotifyMap(va("Attachment: Blocked\nFrom: %s\nType: Vehicle", GetPlayer(id).m_name), false);
									GetEntityControl()->SimpleRequestControl(v);
									ENTITY::SetEntityAsMissionEntity(v, true, true);
									ENTITY::DetachEntity(v, true, true);
									ENTITY::SetEntityCoords(v, 0, 0, 0, 0, 0, 0, 1);
									ENTITY::DeleteEntity(&v);
								}
							} else {
								GetRenderer()->NotifyMap("Removed attached vehicle");
								GetEntityControl()->RequestControl("[AV]", v, [](Entity entity) {ENTITY::DetachEntity(entity, true, true); ENTITY::DeleteEntity(&entity); });
							}
						}
					}
				}

			}

			auto objects = ObjectPool::GetObjects();
			for (int i = 0; i < objects.size(); ++i) {
				Object o = objects[i];
				if (ENTITY::DoesEntityExist(o)) {
					if (!IsWeaponObject(o) && ENTITY::GetEntityModel(o) != 0x4FAA899A) {
						if (ENTITY::IsEntityAttachedToEntity(o, GetLocalPlayer().m_ped)) {
							int net = GetNetObjID(o);
							Player id;
							if (IsNetObjSaved(net, &id)) {
								if (vars.redirectObjects) {
									if (NetEvent::vars.notifyAT) GetRenderer()->NotifyMap(va("Attachment: Blocked\nFrom: %s\nType: Object", GetPlayer(id).m_name), false);
									if (NetEvent::vars.notifyAT) GetRenderer()->NotifyMap(va("Redirecting attachment to %s", GetPlayer(id).m_name), false);
									GetEntityControl()->SimpleRequestControl(o);
									ENTITY::AttachEntityToEntity(o, GetPlayer(id).m_ped, 0, 0, 0, 0, 0, 0, 180, 1, 0, 0, 1, 2, 1);
								} else {
									if (NetEvent::vars.notifyAT) GetRenderer()->NotifyMap(va("Attachment: Blocked\nFrom: %s\nType: Object", GetPlayer(id).m_name), false);
									GetEntityControl()->SimpleRequestControl(o);
									ENTITY::SetEntityAsMissionEntity(o, true, true);
									ENTITY::DetachEntity(o, true, true);
									ENTITY::SetEntityCoords(o, 0, 0, 0, 0, 0, 0, 1);
									ENTITY::DeleteEntity(&o);
								}
							} else {
								GetRenderer()->NotifyMap("Removed attached object");
								GetEntityControl()->RequestControl("[AO]", o, [](Entity entity) {ENTITY::DetachEntity(entity, true, true); ENTITY::DeleteEntity(&entity); });
							}
						}
					}
				}
			}
		}
	}
}

/*Singleton*/
AttachmentProtectionMenu* _instance;
AttachmentProtectionMenu* AttachmentProtectionMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new AttachmentProtectionMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
AttachmentProtectionMenu::~AttachmentProtectionMenu() { delete _instance; }