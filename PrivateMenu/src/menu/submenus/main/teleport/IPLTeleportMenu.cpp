#include "stdafx.h"
#include "IPLTeleportMenu.h"
#include "../teleportMenu.h"

using namespace IPLTeleportMenuVars;

namespace IPLTeleportMenuVars {
	void RequestIPLSet(String* ipls, int count) {
		for (int i = 0; i < count; i++) {
			if (!STREAMING::IsIplActive(ipls[i])) {
				STREAMING::RequestIpl(ipls[i]);
			}
		}
	}

	void RemoveIPLSet(String* ipls, int count) {
		for (int i = 0; i < count; i++) {
			if (STREAMING::IsIplActive(ipls[i])) {
				STREAMING::RemoveIpl(ipls[i]);
			}
		}
	}
}

void IPLTeleportMenu::Init() {
	setParentSubmenu<TeleportMenu>();
	setName("IPL teleports", true, true);

	addOption(ButtonOption("Unload all IPL's")
		.addFunction([] {  
			STREAMING::RemoveIpl("ufo");
			STREAMING::RemoveIpl("cargoship");
			STREAMING::RemoveIpl("Plane_crash_trench");
			STREAMING::RemoveIpl("canyonriver01_traincrash");
			STREAMING::RemoveIpl("railing_end");
			STREAMING::RemoveIpl("Coroner_Int_on");
			STREAMING::RemoveIpl("RC12B_HospitalInterior");
			STREAMING::RemoveIpl("RC12B_Destroyed");

			static String Maps1[] = { "hei_carrier", "hei_carrier_DistantLights", "hei_Carrier_int1", "hei_Carrier_int2", "hei_Carrier_int3", "hei_Carrier_int4", "hei_Carrier_int5", "hei_Carrier_int6", "hei_carrier_LODLights" };
			RemoveIPLSet(Maps1, 9);

			static String Maps2[] = { "plg_01", "prologue01", "prologue01_lod", "prologue01c", "prologue01c_lod", "prologue01d", "prologue01d_lod", "prologue01e", "prologue01e_lod", "prologue01f", "prologue01f_lod", "prologue01g", "prologue01h", "prologue01h_lod", "prologue01i", "prologue01i_lod", "prologue01j", "prologue01j_lod", "prologue01k", "prologue01k_lod", "prologue01z", "prologue01z_lod", "plg_02", "prologue02", "prologue02_lod", "plg_03", "prologue03", "prologue03_lod", "prologue03b", "prologue03b_lod", "prologue03_grv_dug", "prologue03_grv_dug_lod", "prologue_grv_torch", "plg_04", "prologue04", "prologue04_lod", "prologue04b", "prologue04b_lod", "prologue04_cover", "des_protree_end", "des_protree_start", "des_protree_start_lod", "plg_05", "prologue05", "prologue05_lod", "prologue05b", "prologue05b_lod", "plg_06", "prologue06", "prologue06_lod", "prologue06b", "prologue06b_lod", "prologue06_int", "prologue06_int_lod", "prologue06_pannel", "prologue06_pannel_lod", "prologue_m2_door", "prologue_m2_door_lod", "plg_occl_00", "prologue_occl", "plg_rd", "prologuerd", "prologuerdb", "prologuerd_lod" };
			RemoveIPLSet(Maps2, 64);

			static String Maps3[] = { "hei_yacht_heist", "hei_yacht_heist_Bar", "hei_yacht_heist_Bedrm", "hei_yacht_heist_Bridge", "hei_yacht_heist_DistantLights", "hei_yacht_heist_enginrm", "hei_yacht_heist_LODLights", "hei_yacht_heist_Lounge" };
			RemoveIPLSet(Maps3, 8);
		})
		.addTranslation().addHotkey()
		.addTooltip("Unload all loaded IPL's"));

	addOption(ButtonOption("Porn Yacht").addTranslation()
		.addFunction([] {
		STREAMING::RequestIpl("smboat");
		static String Maps[] = { "hei_yacht_heist", "hei_yacht_heist_Bar", "hei_yacht_heist_Bedrm", "hei_yacht_heist_Bridge", "hei_yacht_heist_DistantLights", "hei_yacht_heist_enginrm", "hei_yacht_heist_LODLights", "hei_yacht_heist_Lounge" };
		RemoveIPLSet(Maps, 8);
		ENTITY::SetEntityCoords(GetLocalPlayer().m_entity, -2045.8f, -1031.2f, 11.9f, 0, 0, 0, 0);
	})
		.addHotkey()
		.addTooltip("Porn Yacht"));

	addOption(ButtonOption("Desert UFO").addTranslation()
		.addFunction([] {
		STREAMING::RequestIpl("ufo");
		ENTITY::SetEntityCoords(GetLocalPlayer().m_entity, 2490.47729f, 3774.84351f, 2414.035f, 0, 0, 0, 0);
	})
		.addHotkey()
		.addTooltip("Desert UFO"));

	addOption(ButtonOption("Carrier").addTranslation()
		.addFunction([] {
		static String Maps[] = { "hei_carrier", "hei_carrier_DistantLights", "hei_Carrier_int1", "hei_Carrier_int2", "hei_Carrier_int3", "hei_Carrier_int4", "hei_Carrier_int5", "hei_Carrier_int6", "hei_carrier_LODLights" };
		RequestIPLSet(Maps, 9);
		ENTITY::SetEntityCoords(GetLocalPlayer().m_entity, 3016.46f, -4534.09f, 14.84f, 0, 0, 0, 0);
	})
		.addHotkey()
		.addTooltip("Carrier"));

	addOption(ButtonOption("Cargoship").addTranslation()
		.addFunction([] {
		static String cargoship[] = { "cargoship" };
		RequestIPLSet(cargoship, 1);
		ENTITY::SetEntityCoords(GetLocalPlayer().m_entity, -90.0f, -2365.8f, 14.3f, 0, 0, 0, 0);
	})
		.addHotkey()
		.addTooltip("Cargoship"));

	addOption(ButtonOption("North Yankton").addTranslation()
		.addFunction([] {
		static String Maps[] = { "plg_01", "prologue01", "prologue01_lod", "prologue01c", "prologue01c_lod", "prologue01d", "prologue01d_lod", "prologue01e", "prologue01e_lod", "prologue01f", "prologue01f_lod", "prologue01g", "prologue01h", "prologue01h_lod", "prologue01i", "prologue01i_lod", "prologue01j", "prologue01j_lod", "prologue01k", "prologue01k_lod", "prologue01z", "prologue01z_lod", "plg_02", "prologue02", "prologue02_lod", "plg_03", "prologue03", "prologue03_lod", "prologue03b", "prologue03b_lod", "prologue03_grv_dug", "prologue03_grv_dug_lod", "prologue_grv_torch", "plg_04", "prologue04", "prologue04_lod", "prologue04b", "prologue04b_lod", "prologue04_cover", "des_protree_end", "des_protree_start", "des_protree_start_lod", "plg_05", "prologue05", "prologue05_lod", "prologue05b", "prologue05b_lod", "plg_06", "prologue06", "prologue06_lod", "prologue06b", "prologue06b_lod", "prologue06_int", "prologue06_int_lod", "prologue06_pannel", "prologue06_pannel_lod", "prologue_m2_door", "prologue_m2_door_lod", "plg_occl_00", "prologue_occl", "plg_rd", "prologuerd", "prologuerdb", "prologuerd_lod" };
		RequestIPLSet(Maps, 64);
		ENTITY::SetEntityCoords(GetLocalPlayer().m_entity, 3360.19f, -4849.67f, 111.8f, 0, 0, 0, 0);
	})
		.addHotkey()
		.addTooltip("North Yankton"));

	addOption(ButtonOption("Plane Crash").addTranslation()
		.addFunction([] {
		STREAMING::RequestIpl("Plane_crash_trench");
		ENTITY::SetEntityCoords(GetLocalPlayer().m_entity, 2814.7f, 4758.5f, 50.0f, 0, 0, 0, 0);
	})
		.addHotkey()
		.addTooltip("Plane Crash"));

	addOption(ButtonOption("Train Crash").addTranslation()
		.addFunction([] {
		STREAMING::RequestIpl("canyonriver01_traincrash");
		STREAMING::RequestIpl("railing_end");
		STREAMING::RemoveIpl("railing_start");
		STREAMING::RemoveIpl("canyonriver01");
		ENTITY::SetEntityCoords(GetLocalPlayer().m_entity, -532.1309f, 4526.187f, 88.7955f, 0, 0, 0, 0);
	})
		.addHotkey()
		.addTooltip("Train Crash"));

	addOption(ButtonOption("Morgue").addTranslation()
		.addFunction([] {
		STREAMING::RequestIpl("Coroner_Int_on");
		ENTITY::SetEntityCoords(GetLocalPlayer().m_entity, 244.9f, -1374.7f, 39.5f, 0, 0, 0, 0);
	})
		.addHotkey()
		.addTooltip("Morgue"));

	addOption(ButtonOption("Destroyed Hospital").addTranslation()
		.addFunction([] {
		STREAMING::RemoveIpl("RC12B_Default");
		STREAMING::RemoveIpl("RC12B_Fixed");
		STREAMING::RequestIpl("RC12B_Destroyed");
		STREAMING::RequestIpl("RC12B_HospitalInterior");
		ENTITY::SetEntityCoords(GetLocalPlayer().m_entity, 356.8f, -590.1f, 43.3f, 0, 0, 0, 0);
	})
		.addHotkey()
		.addTooltip("Destroyed Hospital"));

	addOption(ButtonOption("Fort Zancudo UFO").addTranslation()
		.addFunction([] {
		STREAMING::RequestIpl("ufo");
		ENTITY::SetEntityCoords(GetLocalPlayer().m_entity, -2051.99463f, 3237.05835f, 1456.97021f, 0, 0, 0, 0);
	})
		.addHotkey()
		.addTooltip("Fort Zancudo UFO"));

	addOption(ButtonOption("Heist Yacht").addTranslation()
		.addFunction([] {
		STREAMING::RemoveIpl("smboat");
		static String Maps[] = { "hei_yacht_heist", "hei_yacht_heist_Bar", "hei_yacht_heist_Bedrm", "hei_yacht_heist_Bridge", "hei_yacht_heist_DistantLights", "hei_yacht_heist_enginrm", "hei_yacht_heist_LODLights", "hei_yacht_heist_Lounge" };
		RequestIPLSet(Maps, 8);
		ENTITY::SetEntityCoords(GetLocalPlayer().m_entity, -2045.8f, -1031.2f, 11.9f, 0, 0, 0, 0);
	})
		.addHotkey()
		.addTooltip("Heist Yacht"));
}

/*Update once when submenu is opened*/
void IPLTeleportMenu::UpdateOnce() {}

/*Update while submenu is active*/
void IPLTeleportMenu::Update() {}

/*Background update*/
void IPLTeleportMenu::FeatureUpdate() {}

/*Singleton*/
IPLTeleportMenu* _instance;
IPLTeleportMenu* IPLTeleportMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new IPLTeleportMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
IPLTeleportMenu::~IPLTeleportMenu() { delete _instance; }