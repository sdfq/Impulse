#include "stdafx.h"
#include "particleMenu.h"
#include "../localMenu.h"

using namespace ParticleMenuVars;

namespace ParticleMenuVars {
	Vars vars;

	ScrollStruct<ParticleManStruct> m_particleManParticles[] = {
		TranslationString("Light", true),{ "scr_rcbarry2", "scr_exp_clown_trails", 0.2f },
		TranslationString("Alien Teleport", true),{ "scr_rcbarry1", "scr_alien_teleport", 0.2f },
		TranslationString("Money", true),{ "scr_paletoscore", "scr_paleto_banknotes", 0.9f },
		TranslationString("Blood", true),{ "scr_solomon3", "scr_trev4_747_blood_impact", 0.9f },
		TranslationString("Alien Disintegrate", true),{ "scr_rcbarry1", "scr_alien_disintegrate", 0.2f },
		TranslationString("Electric", true),{ "scr_trevor1", "scr_trev1_trailer_boosh", 0.2f },
		TranslationString("Fire", true),{ "scr_agencyheist", "scr_fbi_dd_breach_smoke", 0.2f },
		TranslationString("Clown Death", true),{ "scr_rcbarry2", "scr_clown_death", 0.2f },
		TranslationString("Clown Appears", true),{ "scr_rcbarry2", "scr_clown_appears", 0.08f },
		TranslationString("Flowers", true),{ "scr_rcbarry2", "scr_exp_clown", 0.08f },
		TranslationString("Fireworks", true),{ "scr_indep_fireworks", "scr_indep_firework_starburst", 0.2f }
	};

	int ParticleManBones[] = {
		31086,
		28422,
		60309,
	};

	void ParticleMan(ParticleManStruct& pms)
	{
		for (int i = 0; i < 3; i++) {
			STREAMING::RequestNamedPtfxAsset(pms.m_pOne);
			GRAPHICS::_UseParticleFxAssetNextCall(pms.m_pOne);
			GRAPHICS::_StartParticleFxNonLoopedOnPedBone2(pms.m_pTwo, GetLocalPlayer().m_ped, 0, 0, 0, 0, 0, 0, ParticleManBones[i], pms.m_size, 0, 0, 0);
		}
	}


	void DragonBreath() {
		static int TIMER;
		float XPos = 0.02, YPos = 0.2, ZPos = 0.0, XOff = 90.0, YOff = -100.0, ZOff = 90.0;

		STREAMING::RequestNamedPtfxAsset("core");
		GRAPHICS::_UseParticleFxAssetNextCall("core");
		Utils::DoTimedFunction(&TIMER, 200, [&] {
			int ptfx = GRAPHICS::_StartParticleFxNonLoopedOnPedBone2("ent_sht_flame", GetLocalPlayer().m_ped, XPos, YPos, ZPos, XOff, YOff, ZOff, 31086, 1, 1, 1, 1);
		});
		STREAMING::RemovePtfxAsset();
	}
}

void ParticleMenu::Init() {
	setParentSubmenu<LocalMenu>();
	setName("Particles", true, true);

	addOption(ScrollOption<ParticleManStruct>(TOGGLE, "Particle man")
		.addToggle(vars.particlemanToggle)
		.addScroll(vars.particleman, 0, NUMOF(m_particleManParticles) - 1, m_particleManParticles)
		.addFunction([&] {vars.particlemanselected = vars.particleman; }).addTranslation()
		.addTooltip("Emit particles").addHotkey());

	addOption(ToggleOption("Dragon breath")
		.addToggle(vars.dragonbreath).addTranslation()
		.addHotkey().canBeSaved()
		.addTooltip("This will make you spit fire"));
}

/*Update once when submenu is opened*/
void ParticleMenu::UpdateOnce() {}

/*Update while submenu is active*/
void ParticleMenu::Update() {}

/*Background update*/
void ParticleMenu::FeatureUpdate() {
	if (vars.particlemanToggle)ParticleMan(m_particleManParticles[vars.particleman].m_result);
	if (vars.dragonbreath) DragonBreath();
}

/*Singleton*/
ParticleMenu* _instance;
ParticleMenu* ParticleMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new ParticleMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
ParticleMenu::~ParticleMenu() { delete _instance; }