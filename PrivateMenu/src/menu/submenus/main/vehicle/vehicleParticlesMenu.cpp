#include "stdafx.h"
#include "vehicleParticlesMenu.h"
#include "../vehicleMenu.h"

using namespace VehicleParticlesMenuVars;

namespace VehicleParticlesMenuVars {
	Vars vars;

	struct ParticleStruct {
		String first;
		String second;
	};

	ScrollStruct<ParticleStruct> ParticleEffects[] = {
		TranslationString("Firework Burst"), "proj_xmas_firework", "scr_firework_xmas_burst_rgw",
		TranslationString("Firework Trailburst"), "scr_indep_fireworks", "scr_indep_firework_trailburst",
		TranslationString("Firework Shotburst"), "scr_indep_fireworks", "scr_indep_firework_shotburst",
		TranslationString("Firework Fountain"), "scr_indep_fireworks", "scr_indep_firework_fountain",
		TranslationString("Firework Starburst"), "scr_indep_fireworks", "scr_indep_firework_starburst",
		TranslationString("Wheel Burnout"), "scr_carsteal4", "scr_carsteal4_wheel_burnout",
		TranslationString("Truck Crash"), "scr_fbi4", "scr_fbi4_trucks_crash",
		TranslationString("Clown Appears"), "scr_rcbarry2", "scr_clown_appears",
		TranslationString("Lighter Sparks"), "scr_rcbarry1", "scr_alien_disintegrate",
		TranslationString("Water Splash"), "scr_fbi5a", "scr_fbi5_ped_water_splash",
		TranslationString("Trailer Splash"), "scr_trevor1", "scr_trev1_trailer_splash",
		TranslationString("Blood Impact"), "scr_solomon3", "scr_trev4_747_blood_impact",
		TranslationString("Car Impact"), "scr_exile2", "scr_ex2_car_impact",
		TranslationString("Muzzle Flash"), "scr_carsteal4", "scr_carsteal5_car_muzzle_flash",
		TranslationString("Tyre Spiked"), "scr_carsteal3", "scr_carsteal4_tyre_spiked",
		TranslationString("Pipe Smoke"), "scr_familyscenem", "scr_meth_pipe_smoke",
		TranslationString("Alien Disintegrate"), "scr_rcbarry1", "scr_alien_disintegrate",
		TranslationString("Alien Teleport"), "scr_rcbarry1", "scr_alien_teleport",
		TranslationString("Breach Smoke"), "scr_agencyheist", "scr_fbi_dd_breach_smoke",
		TranslationString("Atrium Glass"), "scr_agencyheist", "scr_agency_atrium_glass",
		TranslationString("Door Hvy Trig"), "scr_agencyheist", "scr_agency3a_door_hvy_trig",
		TranslationString("FBI Exp Building"), "scr_agencyheist", "scr_fbi_exp_building",
		TranslationString("FBI Mop Drips"), "scr_agencyheist", "scr_fbi_mop_drips",
		TranslationString("Agency Linger Smoke"), "scr_agencyheistb", "scr_agency3b_linger_smoke",
		TranslationString("Agency Atrium Silt"), "scr_agencyheistb", "scr_agency_atrium_silt",
		TranslationString("Agency Heli Expl"), "scr_agencyheistb", "scr_agency3b_heli_expl",
		TranslationString("Heli Exp Trail"), "scr_agencyheistb", "scr_agency3b_heli_exp_trail",
		TranslationString("Wood Splinter"), "scr_agencyheistb", "scr_agency3b_wood_splinter",
		TranslationString("Bong Smoke"), "scr_mp_house", "scr_sh_bong_smoke",
		TranslationString("Lighter Sparks"), "scr_mp_house", "scr_sh_lighter_sparks",
		TranslationString("Dust Impact"), "scr_exile1", "scr_ex1_dust_impact",
		TranslationString("Plane Exp"), "scr_exile1", "scr_ex1_plane_exp",
		TranslationString("Cargo Engine Burst"), "scr_exile1", "scr_ex1_cargo_engine_burst",
		TranslationString("Michael Pool Splash"), "cut_family5", "cs_fam5_michael_pool_splash",
		TranslationString("Blood Headshot"), "scr_family1", "scr_fam1_blood_headshot",
		TranslationString("Cig Exhale Nose"), "scr_family1", "cs_cig_exhale_nose",
		TranslationString("Trailer Parks"), "scr_family4", "scr_fam4_trailer_sparks",
		TranslationString("Electric SWparks"), "scr_fbi3", "scr_fbi3_elec_sparks",
		TranslationString("Dust Cloud"), "scr_mp_creator", "scr_mp_dust_cloud",
		TranslationString("Josh Light Explosion"), "scr_josh3", "scr_josh3_light_explosion",
		TranslationString("Exp Debris"), "scr_josh3", "scr_josh3_exp_debris",
		TranslationString("Josh Explosion"), "scr_josh3", "scr_josh3_explosion",
		TranslationString("Water Exp"), "scr_oddjobtraffickingair", "scr_ojdg4_water_exp",
		TranslationString("Boat Exp"), "scr_oddjobtraffickingair", "scr_ojdg4_boat_exp",
		TranslationString("Trailer Splash"), "scr_trevor1", "scr_trev1_trailer_splash",
		TranslationString("Trailer Boosh"), "scr_trevor1", "scr_trev1_trailer_boosh",
		TranslationString("Meth Dust Settle"), "scr_trevor1", "ent_ray_meth_dust_settle",
		TranslationString("Blade Blood"), "scr_trevor2", "scr_rotor_blade_blood",
		TranslationString("Bus Impact"), "scr_oddjobbusassassin", "scr_ojbusass_bus_impact",
		TranslationString("Clown Death"), "scr_rcbarry2", "scr_clown_death",
		TranslationString("Tyre Spiked"), "scr_carsteal3", "scr_carsteal4_tyre_spiked",
	};

	void Particles() {
		if (vars.frontleft) {
			Vector3 coords = ENTITY::GetWorldPositionOfEntityBone(GetLocalPlayer().m_vehicle, ENTITY::GetEntityBoneIndexByName(GetLocalPlayer().m_vehicle, "wheel_lf"));
			STREAMING::RequestNamedPtfxAsset(ParticleEffects[vars.type].m_result.first);
			GRAPHICS::_UseParticleFxAssetNextCall(ParticleEffects[vars.type].m_result.first);
			GRAPHICS::_StartParticleFxNonLoopedAtCoord2(ParticleEffects[vars.type].m_result.second, coords.x, coords.y, coords.z, 0, 0, 0, vars.size, 0, 0, 0);
		}

		if (vars.frontright) {
			Vector3 coords = ENTITY::GetWorldPositionOfEntityBone(GetLocalPlayer().m_vehicle, ENTITY::GetEntityBoneIndexByName(GetLocalPlayer().m_vehicle, "wheel_rf"));
			STREAMING::RequestNamedPtfxAsset(ParticleEffects[vars.type].m_result.first);
			GRAPHICS::_UseParticleFxAssetNextCall(ParticleEffects[vars.type].m_result.first);
			GRAPHICS::_StartParticleFxNonLoopedAtCoord2(ParticleEffects[vars.type].m_result.second, coords.x, coords.y, coords.z, 0, 0, 0, vars.size, 0, 0, 0);
		}

		if (vars.rearleft) {
			Vector3 coords = ENTITY::GetWorldPositionOfEntityBone(GetLocalPlayer().m_vehicle, ENTITY::GetEntityBoneIndexByName(GetLocalPlayer().m_vehicle, "wheel_lr"));
			STREAMING::RequestNamedPtfxAsset(ParticleEffects[vars.type].m_result.first);
			GRAPHICS::_UseParticleFxAssetNextCall(ParticleEffects[vars.type].m_result.first);
			GRAPHICS::_StartParticleFxNonLoopedAtCoord2(ParticleEffects[vars.type].m_result.second, coords.x, coords.y, coords.z, 0, 0, 0, vars.size, 0, 0, 0);
		}

		if (vars.rearright) {
			Vector3 coords = ENTITY::GetWorldPositionOfEntityBone(GetLocalPlayer().m_vehicle, ENTITY::GetEntityBoneIndexByName(GetLocalPlayer().m_vehicle, "wheel_rr"));
			STREAMING::RequestNamedPtfxAsset(ParticleEffects[vars.type].m_result.first);
			GRAPHICS::_UseParticleFxAssetNextCall(ParticleEffects[vars.type].m_result.first);
			GRAPHICS::_StartParticleFxNonLoopedAtCoord2(ParticleEffects[vars.type].m_result.second, coords.x, coords.y, coords.z, 0, 0, 0, vars.size, 0, 0, 0);
		}

		if (vars.exhaust) {
			for (int i = 0; i < 16; i++) {
				Vector3 coords = ENTITY::GetWorldPositionOfEntityBone(GetLocalPlayer().m_vehicle, ENTITY::GetEntityBoneIndexByName(GetLocalPlayer().m_vehicle, i == 0 ? "exhaust" : va("exhaust_%i", i)));
				STREAMING::RequestNamedPtfxAsset(ParticleEffects[vars.type].m_result.first);
				GRAPHICS::_UseParticleFxAssetNextCall(ParticleEffects[vars.type].m_result.first);
				GRAPHICS::_StartParticleFxNonLoopedAtCoord2(ParticleEffects[vars.type].m_result.second, coords.x, coords.y, coords.z, 0, 0, 0, vars.size, 0, 0, 0);
			}
		}
	}
}

void VehicleParticlesMenu::Init() {
	setParentSubmenu<VehicleMenu>();
	setName("Vehicle particles", true, true);

	addOption(ScrollOption<ParticleStruct>(SCROLL, "Particle type")
		.addScroll(vars.type, 0, NUMOF(ParticleEffects) - 1, ParticleEffects)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Set particle type"));

	addOption(NumberOption<float>(SCROLL, "Particle size")
		.addNumber(vars.size, "%.2f", 0.01f).addMin(0).addMax(5)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Set particle size"));

	addOption(ToggleOption("Front left wheel")
		.addToggle(vars.frontleft)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Front left wheel"));

	addOption(ToggleOption("Front right wheel")
		.addToggle(vars.frontright)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Front right wheel"));

	addOption(ToggleOption("Rear left wheel")
		.addToggle(vars.rearleft)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Rear left wheel"));

	addOption(ToggleOption("Rear right wheel")
		.addToggle(vars.rearright)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Rear right wheel"));

	addOption(ToggleOption("Exhaust")
		.addToggle(vars.exhaust)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Exhaust"));

	addOption(ToggleOption("Enable vehicle particles")
		.addToggle(vars.enabled)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Enable vehicle particles"));
}

/*Update once when submenu is opened*/
void VehicleParticlesMenu::UpdateOnce() {}

/*Update while submenu is active*/
void VehicleParticlesMenu::Update() {
	if (!GetLocalPlayer().m_isInVehicle) {
		GetMenu()->ResetCurrentOption();
		return;
	}
}

/*Background update*/
void VehicleParticlesMenu::FeatureUpdate() {
	static int TIMER;
	if (vars.enabled) Utils::DoTimedFunction(&TIMER, 5, [] {Particles(); });
}

/*Singleton*/
VehicleParticlesMenu* _instance;
VehicleParticlesMenu* VehicleParticlesMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new VehicleParticlesMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
VehicleParticlesMenu::~VehicleParticlesMenu() { delete _instance; }