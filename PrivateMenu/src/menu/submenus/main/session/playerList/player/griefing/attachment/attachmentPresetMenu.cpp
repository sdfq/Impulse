#include "stdafx.h"
#include "attachmentPresetMenu.h"
#include "../attachmentMenu.h"

using namespace AttachmentPresetMenuVars;

namespace AttachmentPresetMenuVars {
	Vars vars;

	void Alien() {
		Hash model = Utils::GetHashKey("prop_alien_egg_01");
		GetEntityControl()->SimpleRequestModel(model);

		AttachmentMenuVars::AttachObjectToPlayer(GetSelectedPlayer(), model, PED::GetPedBoneIndex(GetSelectedPlayer().m_ped, 0xfe2c), 0.0f, 0.0f, 0.0f, -90.0f, 0.0f, 0.0f);
	}

	void Balls() {
		Hash model = 136236575; 
		GetEntityControl()->SimpleRequestModel(model);

		AttachmentMenuVars::AttachObjectToPlayer(GetSelectedPlayer(), model, PED::GetPedBoneIndex(GetSelectedPlayer().m_ped, 0xfe2c));
		AttachmentMenuVars::AttachObjectToPlayer(GetSelectedPlayer(), model, PED::GetPedBoneIndex(GetSelectedPlayer().m_ped, 0x8cbd));
		AttachmentMenuVars::AttachObjectToPlayer(GetSelectedPlayer(), model, PED::GetPedBoneIndex(GetSelectedPlayer().m_ped, 0x188e));
		AttachmentMenuVars::AttachObjectToPlayer(GetSelectedPlayer(), model, PED::GetPedBoneIndex(GetSelectedPlayer().m_ped, 0xfedd));
		AttachmentMenuVars::AttachObjectToPlayer(GetSelectedPlayer(), model, PED::GetPedBoneIndex(GetSelectedPlayer().m_ped, 0x8aae));
	}

	void Saucers() {
		Hash model = -956377380;
		GetEntityControl()->SimpleRequestModel(model);

		AttachmentMenuVars::AttachObjectToPlayer(GetSelectedPlayer(), model, PED::GetPedBoneIndex(GetSelectedPlayer().m_ped, 0xfe2c));
		AttachmentMenuVars::AttachObjectToPlayer(GetSelectedPlayer(), model, PED::GetPedBoneIndex(GetSelectedPlayer().m_ped, 0x8cbd));
		AttachmentMenuVars::AttachObjectToPlayer(GetSelectedPlayer(), model, PED::GetPedBoneIndex(GetSelectedPlayer().m_ped, 0x188e));
		AttachmentMenuVars::AttachObjectToPlayer(GetSelectedPlayer(), model, PED::GetPedBoneIndex(GetSelectedPlayer().m_ped, 0xfedd));
		AttachmentMenuVars::AttachObjectToPlayer(GetSelectedPlayer(), model, PED::GetPedBoneIndex(GetSelectedPlayer().m_ped, 0x8aae));
	}

	void SwordBody() {
		Hash model = -491126417;
		GetEntityControl()->SimpleRequestModel(model);

		AttachmentMenuVars::AttachObjectToPlayer(GetSelectedPlayer(), model, PED::GetPedBoneIndex(GetSelectedPlayer().m_ped, 0xfe2c));
		AttachmentMenuVars::AttachObjectToPlayer(GetSelectedPlayer(), model, PED::GetPedBoneIndex(GetSelectedPlayer().m_ped, 0x8cbd));
		AttachmentMenuVars::AttachObjectToPlayer(GetSelectedPlayer(), model, PED::GetPedBoneIndex(GetSelectedPlayer().m_ped, 0x188e));
		AttachmentMenuVars::AttachObjectToPlayer(GetSelectedPlayer(), model, PED::GetPedBoneIndex(GetSelectedPlayer().m_ped, 0xfedd));
		AttachmentMenuVars::AttachObjectToPlayer(GetSelectedPlayer(), model, PED::GetPedBoneIndex(GetSelectedPlayer().m_ped, 0x8aae));
	}

	void Snowman() {
		Hash model = Utils::GetHashKey("prop_prlg_snowpile");
		GetEntityControl()->SimpleRequestModel(model);

		AttachmentMenuVars::AttachObjectToPlayer(GetSelectedPlayer(), model, PED::GetPedBoneIndex(GetSelectedPlayer().m_ped, 0xe0fd), -0.2f, 0.0f, 0.05f, 0.0f, 90.0f, -90.0f);
	}

	void ConeFace() {
		Hash model = Utils::GetHashKey("prop_mp_cone_01");
		GetEntityControl()->SimpleRequestModel(model);

		AttachmentMenuVars::AttachObjectToPlayer(GetSelectedPlayer(), model, PED::GetPedBoneIndex(GetSelectedPlayer().m_ped, 0xfe2c));
	}

	void Miniguns() {
		Hash model = Utils::GetHashKey("prop_minigun_01");
		GetEntityControl()->SimpleRequestModel(model);

		AttachmentMenuVars::AttachObjectToPlayer(GetSelectedPlayer(), model, 0, -0.3f, 0.2f, 0.6f, 0.0f, 0.0f, 90.0f);
		AttachmentMenuVars::AttachObjectToPlayer(GetSelectedPlayer(), model, 0, 0.3f, 0.2f, 0.6f, 0.0f, 0.0f, 90.0f);
	}

	void Penis() {
		Hash model = Utils::GetHashKey("prop_ld_bomb_01");
		GetEntityControl()->SimpleRequestModel(model);

		AttachmentMenuVars::AttachObjectToPlayer(GetSelectedPlayer(), model, 0, 0.0f, 0.5f, -0.17f, 180.0f, 0.0f, 0.0f);
	}
}

void AttachmentPresetMenu::Init() {
	setParentSubmenu<AttachmentMenu>();
	setName("Presets", true, false);

	addOption(ButtonOption("Alien")
		.addFunction(Alien));

	addOption(ButtonOption("Balls")
		.addFunction(Balls));

	addOption(ButtonOption("Saucers")
		.addFunction(Saucers));

	addOption(ButtonOption("Sword body")
		.addFunction(SwordBody));

	addOption(ButtonOption("Snowman")
		.addFunction(Snowman));

	addOption(ButtonOption("Cone face")
		.addFunction(ConeFace));

	addOption(ButtonOption("Miniguns")
		.addFunction(Miniguns));

	addOption(ButtonOption("Penis")
		.addFunction(Penis));
}

/*Update once when submenu is opened*/
void AttachmentPresetMenu::UpdateOnce() {}

/*Update while submenu is active*/
void AttachmentPresetMenu::Update() {}

/*Background update*/
void AttachmentPresetMenu::FeatureUpdate() {}

/*Singleton*/
AttachmentPresetMenu* _instance;
AttachmentPresetMenu* AttachmentPresetMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new AttachmentPresetMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
AttachmentPresetMenu::~AttachmentPresetMenu() { delete _instance; }