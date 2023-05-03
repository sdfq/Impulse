#include "stdafx.h"
#include "localMenu.h"
#include "local/playerMovementMenu.h"
#include "local/modelMenu.h"
#include "local/wardrobeMenu.h"
#include "local/animationMenu.h"
#include "local/visionMenu.h"
#include "local/globalMenu.h"
#include "local/particleMenu.h"
#include "local/OwnedForcefield.h"
#include "../mainMenu.h"
#include "world/trafficManagerMenu.h"
using namespace LocalMenuVars;

namespace LocalMenuVars {
	Vars vars;

	ScrollStruct<int> invisibilityTypes[] = {
		TranslationString("Invisible (not for self)", true), 0,
		TranslationString("Invisible", true), 1
	};

	void Regenerate() {
		static int TIMER;
		CPed* ped = ReClass::GetWorld()->LocalPed;
		Utils::DoTimedFunction(&TIMER, 500, [&] {
			if (ped->Health < ped->MaxHealth)ped->Health += ped->MaxHealth / 100; });
	}

	void NeverWanted(bool toggle) {
		if (toggle) PLAYER::ClearPlayerWantedLevel(GetLocalPlayer().m_id);
		//PLAYER::SetPoliceIgnorePlayer(GetLocalPlayer().m_id, toggle);
		//PLAYER::SetMaxWantedLevel(toggle ? 0 : 5);
	}

	void NoRagdoll(bool toggle) {
		PED::SetPedCanRagdoll(GetLocalPlayer().m_ped, !toggle);
		PED::SetPedCanRagdollFromPlayerImpact(GetLocalPlayer().m_ped, !toggle);
		PED::SetPedCanBeKnockedOffVehicle(GetLocalPlayer().m_ped, !toggle);
		PED::SetPedRagdollOnCollision(GetLocalPlayer().m_ped, !toggle);
		PLAYER::GivePlayerRagdollControl(GetLocalPlayer().m_id, toggle);
	}

	void IgnorePlayer() {
		PLAYER::SetPoliceIgnorePlayer(GetLocalPlayer().m_ped, false);
		PLAYER::SetEveryoneIgnorePlayer(GetLocalPlayer().m_ped, false);
		PLAYER::SetPlayerCanBeHassledByGangs(GetLocalPlayer().m_ped, true);
		PLAYER::SetIgnoreLowPriorityShockingEvents(GetLocalPlayer().m_ped, false);
	}

	void DisablePhone() {
		using namespace Globals;
		int Unk_1 = 15745;

		if (*Global(PHONE_BASE).At(1).Get<bool>() != 1) {
			if (SCRIPT::_GetNumberOfInstancesOfScriptWithNameHash(Utils::GetHashKey("cellphone_flashhand")) > 0 ||
				*Global(PHONE_BASE).At(1).Get<int>() > 3) {
				if (*Global(PHONE_BOOL1).Get<bool>()) {
					Global(PHONE_BOOL1).As<int>() = 0;
					Global(PHONE_POSSET).As<int>() = *Global(PHONE_POSGET).Get<int>();
					Global(PHONE_POSSET).At(1).As<int>() = *Global(PHONE_POSGET).At(1).Get<int>();
					Global(PHONE_POSSET).At(2).As<int>() = *Global(PHONE_POSGET).At(2).Get<int>();
					MOBILE::SetMobilePhonePosition(
						*Global(PHONE_POSSET).Get<float>(),
						*Global(PHONE_POSSET).At(1).Get<float>(),
						*Global(PHONE_POSSET).At(2).Get<float>()
					);
				}

				if (*Global(PHONE_BASE).At(1).Get<int>() == 10 && *Global(PHONE_BASE).At(1).Get<int>() == 9) {
					MISC::SetBit(Global(PHONE_BITSET1).Get<int>(), 16);
				}

				if (AUDIO::IsMobilePhoneCallOngoing()) {
					AUDIO::StopScriptedConversation(false);
				}

				Global(Unk_1).As<int>() = 5;
				MISC::ClearBit((int*)Global(PHONE_BITSET2).Get<int64_t>(), 30);

				if (*Global(PHONE_BASE).At(1).Get<int>() != 1 && *Global(PHONE_BASE).At(1).Get<int>() != 0) {
					Global(PHONE_BASE).At(1).As<int>() = 3;
				}
			}
			MISC::SetBit((int*)Global(PHONE_BITSET1).Get<int>(), 2);
		}
	}

	void CleanPed() {
		PED::ClearPedBloodDamage(GetLocalPlayer().m_ped);
		PED::ResetPedVisibleDamage(GetLocalPlayer().m_ped);
		BRAIN::ClearPedTasksImmediately(GetLocalPlayer().m_id);
	}

	/*void PushForcefield() {
		if (GetLocalPlayer().m_coordinates.Distance(RunTrafficManagerWorker.VehicleCoords) <= 10.0f) {
			TrafficManagerMenuVars::RunTrafficManagerWorker(VEHICLE_PUSH);
		}
	}*/

	void RemoveAttachments() {
		PoolManager::Update();
		vector<Entity> e = EntityPool::GetEntities();
		Entity* objects = &e[0];
		for (int i = 0; i < e.size(); ++i) {
			Object obj = objects[i];
			if (ENTITY::IsEntityAttachedToEntity(obj, GetLocalPlayer().m_ped)) {
				GetEntityControl()->RequestControl("[RA]", obj, [](Entity entity) {ENTITY::DetachEntity(entity, true, true); ENTITY::DeleteEntity(&entity); });
			}
		}
	}

	void Karma() {
		if (ENTITY::IsEntityDead(GetLocalPlayer().m_ped, 0)) {
			int killer = PED::GetPedSourceOfDeath(GetLocalPlayer().m_ped);
			if (!ENTITY::IsEntityDead(killer, 0)) {
				Vector3 Pos = ENTITY::GetEntityCoords(killer, 1);
				FIRE::AddExplosion(Pos.x, Pos.y, Pos.z, 0, 10, 1, 0, 0.0f, 0);
			}
		}
	}

	void ForceField() {
		ENTITY::SetEntityInvincible(GetLocalPlayer().m_ped, true);
		FIRE::AddExplosion(GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, GetLocalPlayer().m_coordinates.z, 29, 100, false, true, 0.0f, false);
	}

	void Shrink(bool toggle) {
		PED::SetPedConfigFlag(GetLocalPlayer().m_ped, 223, toggle);
	}

	void ReducedCollision() {
		PED::SetPedCapsule(GetLocalPlayer().m_ped, 0.0001);
	}

	void Invisibility(int type, bool toggle) {
		GetLocalPlayer().setVisible(!toggle);
		if (type == 0) {
			NETWORK::SetEntityLocallyVisible(GetLocalPlayer().m_ped);
			NETWORK::SetPlayerVisibleLocally(GetLocalPlayer().m_id, true);
		}
	}
}

void LocalMenu::Init() {
	setParentSubmenu<MainMenu>();
	setName("Player", true, true);

	/*addOption(make_shared<SubmenuOption>("Movement"))->
		addSubmenu<PlayerMovementMenu>().addHotkey().addTranslation()
		.addTooltip("Player movement options");*/

	addOption(SubmenuOption("Movement")
		.addSubmenu<PlayerMovementMenu>().addHotkey().addTranslation()
		.addTooltip("Player movement options"));

	addOption(SubmenuOption("Owned forcefield")
		.addSubmenu<OwnedForcefield>().addHotkey().addTranslation()
		.addTooltip("Create a forcefield that kills on someone else's behalf"));

	addOption(SubmenuOption("Global")
		.addSubmenu<GlobalMenu>().addHotkey().addTranslation()
		.addTooltip("Global options"));

	addOption(SubmenuOption("Model")
		.addSubmenu<ModelMenu>().addHotkey().addTranslation()
		.addTooltip("Model options"));

	addOption(SubmenuOption("Wardrobe")
		.addSubmenu<WardrobeMenu>().addHotkey().addTranslation()
		.addTooltip("Wardrobe options"));

	addOption(SubmenuOption("Animation")
		.addSubmenu<AnimationMenu>().addHotkey().addTranslation()
		.addTooltip("Animation options"));

	addOption(SubmenuOption("Vision")
		.addSubmenu<VisionMenu>().addHotkey().addTranslation()
		.addTooltip("Vision options"));

	addOption(SubmenuOption("Particle effects")
		.addSubmenu<ParticleMenu>().addHotkey().addTranslation()
		.addTooltip("Particle Effects options"));

	addOption(BreakOption("General"));

	addOption(ToggleOption("God mode")
		.addToggle(vars.godmode).addTranslation()
		.addFunction([] { GetLocalPlayer().setInvincible(vars.godmode); })
		.addHotkey().canBeSaved()
		.addTooltip("Player won't be able to die"));

	addOption(ToggleOption("Regenerate health")
		.addToggle(vars.regen).addTranslation()
		.addHotkey().canBeSaved()
		.addTooltip("Slowly regenerate health"));

	addOption(ScrollOption<int>(TOGGLE, "Invisibility")
		.addToggle(vars.invisibilityToggle)
		.addScroll(vars.invisibility, 0, NUMOF(invisibilityTypes) - 1, invisibilityTypes)
		.addFunction([] { Invisibility(vars.invisibility, vars.invisibilityToggle); }).addTranslation()
		.addHotkey().canBeSaved()
		.addTooltip("Player will be invisible"));

	addOption(NumberOption<int>(SCROLL, "Opacity")
		.addNumber(vars.opacity, "%d", 1).addMin(0).addMax(100).setScrollSpeed(20).addTranslation().addHotkey()
		.addFunction([&] {ENTITY::SetEntityAlpha(GetLocalPlayer().m_ped, 255 - (vars.opacity *2.55f), false); })
		.addTooltip("Set player opacity (local only)"));

	/*addOption(NumberOption<int>(SCROLL, "Wanted level")
		.addNumber(vars.wantedlevel, "%i", 1).addMin(0).addMax(5).setScrollSpeed(1).addTranslation().addHotkey()
		.addFunction([&] {  })
		.addTooltip(""));*/

	addOption(ToggleOption("Never wanted")
		.addToggle(vars.neverwanted).addTranslation()
		.addFunction([] {NeverWanted(vars.neverwanted); })
		.addHotkey().canBeSaved()
		.addTooltip("No wanted stars"));

	addOption(ToggleOption("No ragdoll")
		.addToggle(vars.noragdoll).addTranslation()
		.addFunction([] {NoRagdoll(vars.noragdoll); })
		.addHotkey().canBeSaved()
		.addTooltip("Player can't ragdoll"));

	addOption(BreakOption("Modify Ped"));

	addOption(ButtonOption("Clone")
		.addFunction([] {PED::ClonePed(GetLocalPlayer().m_ped, ENTITY::GetEntityHeading(GetLocalPlayer().m_ped), 1, 0); })
		.addHotkey().addTranslation()
		.addTooltip("Clone your ped"));

	addOption(ToggleOption("Midget mode")
		.addToggle(vars.midget).addTranslation()
		.addFunction([] {Shrink(vars.midget); })
		.addHotkey().canBeSaved()
		.addTooltip("Shrink!"));

	addOption(ToggleOption("Reduced Collision")
		.addToggle(vars.reducedcollision).addTranslation().addHotkey()
		.addTooltip("Reduce the collision on your player model"));

	addOption(ButtonOption("Clean ped")
		.addFunction([] {CleanPed(); })
		.addHotkey().addTranslation()
		.addTooltip("Reset the player"));

	addOption(ToggleOption("Peds ignore player")
		.addToggle(vars.ignoreplayer).addTranslation()
		.addHotkey().canBeSaved()
		.addTooltip("Make peds ignore the player"));

	addOption(ButtonOption("Suicide")
		.addFunction([] {ReClass::GetWorld()->LocalPed->Health = 0; })
		.addHotkey().addTranslation()
		.addTooltip("Suicide"));

	addOption(ButtonOption("Remove all attachments")
		.addFunction([] {RemoveAttachments(); })
		.addHotkey().addTranslation()
		.addTooltip("Remove all attachments"));

	addOption(BreakOption("Misc"));

	addOption(ToggleOption("Forcefield")
		.addToggle(vars.forcefield).addTranslation()
		.addHotkey().canBeSaved()
		.addTooltip("Forcefield"));

	addOption(ToggleOption("Badsport yourself")
		.addToggle(vars.badsport).addTranslation()
		.addFunction([] {
		if (!vars.badsport) {
			STATS::StatSetFloat(0xBE89A9D2, 0.f, 0);
			STATS::StatSetBool(0x8C1C0FAF, false, 0);
		}
	})
		.addHotkey()
		.addTooltip("Place yourself in badsport"));

	addOption(ToggleOption("Karma")
		.addToggle(vars.karma).addTranslation().addHotkey()
		.addTooltip("Kill the player that kills you"));
}


void LocalMenu::UpdateOnce() {}

void LocalMenu::Update() {
	//if (vars.width)*reinterpret_cast<int*>(Pattern::getMultilayerPointer(Backend::GetWorldPtr(), {  0x10B8, 0x06F0 + 0x00A8 })) = (int)vars.editWidth;
}

void LocalMenu::FeatureUpdate() {
	if (vars.godmode)GetLocalPlayer().setInvincible(vars.godmode);
	if (vars.regen)Regenerate();
	if (vars.neverwanted)NeverWanted(vars.neverwanted);
	if (vars.noragdoll)NoRagdoll(vars.noragdoll);
	if (vars.invisibilityToggle) Invisibility(vars.invisibility, vars.invisibilityToggle);
	if (vars.ignoreplayer)IgnorePlayer();
	if (vars.karma) Karma();
	if (vars.forcefield)ForceField();
	if (vars.midget)Shrink(true);
	if (vars.reducedcollision) ReducedCollision();

	if (vars.badsport) {
		STATS::StatSetFloat(0xBE89A9D2, 300.f, false);
	}
	
}

/*Singleton*/
LocalMenu* _instance;
LocalMenu* LocalMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new LocalMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
LocalMenu::~LocalMenu() { delete _instance; }