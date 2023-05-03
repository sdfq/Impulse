#pragma once
#include "menu/submenu.h"

class ParticleMenu : public Submenu {
public:
	static ParticleMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	ParticleMenu() : Submenu() {}
	~ParticleMenu();
};

namespace ParticleMenuVars
{
	struct Vars
	{
		bool particlemanToggle;
		int particleman = 0;
		int particlemanselected = 0;
		bool dragonbreath;
	};

	struct ParticleManStruct {
		String m_pOne;
		String m_pTwo;
		float m_size;
	};

	extern ScrollStruct<ParticleManStruct> m_particleManParticles[11];
}