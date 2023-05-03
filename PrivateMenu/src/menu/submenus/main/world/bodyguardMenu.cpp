#include "stdafx.h"
#include "bodyguardMenu.h"
#include "bodyguardMenuEditor.h"
#include "menu/submenus/main/worldMenu.h"

using namespace BodyguardMenuVars;

namespace BodyguardMenuVars {

	Vars vars;

	void SpawnCloneBodyguard(Hash weapon, Hash ped, int health, int formation) { //Utils::GetHashKey("WEAPON_RAILGUN");

		Hash Weapon = weapon;

		vars.Bodyguard = ped;
		
		int MyGroup = PLAYER::GetPlayerGroup(GetLocalPlayer().m_id);

		if (vars.clonepick == true) {
			vars.Bodyguard = PED::ClonePed(GetLocalPlayer().m_ped, ENTITY::GetEntityHeading(GetLocalPlayer().m_ped), true, false);
		} else {
			DWORD model = ped;
			if (STREAMING::IsModelInCdimage(model)) {
				GetEntityControl()->SimpleRequestModel(model);
				vars.Bodyguard = PED::CreatePed(21, model, GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, GetLocalPlayer().m_coordinates.z, ENTITY::GetEntityHeading(GetLocalPlayer().m_ped), 1, 0);
			}
		}

		if (vars.addblip) {
			vars.blip = HUD::AddBlipForEntity(vars.Bodyguard); HUD::SetBlipSprite(vars.blip, 480); HUD::SetBlipColour(vars.blip, 63);
		}

		PED::SetPedAsGroupLeader(GetLocalPlayer().m_ped, MyGroup);
		PED::SetPedAsGroupMember(vars.Bodyguard, MyGroup);
		PED::SetPedNeverLeavesGroup(vars.Bodyguard, true);
		if (vars.godmodepick) ENTITY::SetEntityInvincible(vars.Bodyguard, true);
		PED::SetPedCombatAbility(vars.Bodyguard, 100);
		PED::SetPedCanSwitchWeapon(vars.Bodyguard, true);
		PED::SetGroupFormation(MyGroup, formation);
		PED::SetPedMaxHealth(vars.Bodyguard, health);
		ENTITY::SetEntityVisible(vars.Bodyguard, true, true);
		WEAPON::GiveWeaponToPed(vars.Bodyguard, Weapon, 9999, false, true);
		BRAIN::TaskCombatHatedTargetsAroundPed(GetLocalPlayer().m_ped, 100, vars.Bodyguard);
		if (vars.ragdollpick) {
			PED::SetPedCanRagdoll(vars.Bodyguard, false);
			PED::SetPedCanRagdollFromPlayerImpact(vars.Bodyguard, false);
			PED::SetPedCanBeKnockedOffVehicle(vars.Bodyguard, false);
			PED::SetPedRagdollOnCollision(vars.Bodyguard, false);
		}

		if (vars.Invisible)
		{
			ENTITY::SetEntityVisible(vars.Bodyguard, false, false);
		}
	}

	ScrollStruct<int> WeaponSelector[] = {
		TranslationString("Railgun", true), 1834241177,
		TranslationString("RPG", true), 2982836145,
		TranslationString("Stungun", true), 911657153,
		TranslationString("Minigun", true), 1119849093,
		TranslationString("Grenade Launcher", true), 2726580491,
		TranslationString("Heavy Sniper", true), 205991906,
		TranslationString("Marksman Rifle", true), 3342088282,
		TranslationString("Assault Shotgun", true), 3800352039,
		TranslationString("Combat MG", true), 2144741730,
		TranslationString("Baseball Bat", true), 2508868239,
		TranslationString("Machette", true), 3713923289,
		TranslationString("Firework Launcher", true), 2138347493
	};

	ScrollStruct<int> HealthSelector[] = {
		TranslationString("Regular Health", true), 100,
		TranslationString("Double Health", true), 200,
		TranslationString("Extended Health", true), 1000,
		TranslationString("Godly Health", true), 9999
	};

	ScrollStruct<int> FormationSelector[] = {
		TranslationString("Default", true), 0,
		TranslationString("Circle (Inward)", true), 1,
		TranslationString("Circle (North)", true), 2,
		TranslationString("Line", true), 3
	};

	ScrollStruct<int> PedSelector[] = {
		TranslationString("Generic", true), 0xB3F3EE34,
		TranslationString("Jesus", true), 0xCE2CB751,
		TranslationString("Juggernaut", true), 0x90EF5134,
		TranslationString("Johnny", true), 0x87CA80AE,
		TranslationString("Avon", true), -52268862,
		TranslationString("Bodybuilder", true), -636391810,
		TranslationString("Beach girl", true), 808859815,
		TranslationString("Afro Male", true), 933205398,
		TranslationString("Clown", true), 71929310,
		TranslationString("Cocaine Male", true), 1456705429,
		TranslationString("Cocaine Female", true), 1264941816,
		TranslationString("Police Man", true), 1581098148,
		TranslationString("Police Female", true), 368603149,
		TranslationString("Hip Hop Man", true), -1660909656,
		TranslationString("Fireman", true), -1229853272,
		TranslationString("Hooker", true), 42647445,
		TranslationString("Juggernaut", true), -1863364300,
		TranslationString("Lester", true), 1849883942,
		TranslationString("Meth Male", true), -306958529,
		TranslationString("Meth Female", true), -760054079,
		TranslationString("Mime", true), 1021093698,
		TranslationString("Spaceman", true), -407694286,
		TranslationString("Pogo", true), -598109171,
		TranslationString("RS Ranger", true), 1011059922,
		TranslationString("Snow Cop", true), 451459928,
		TranslationString("Stripper 1", true), 1381498905,
		TranslationString("Stripper 2", true), 1846523796,
		TranslationString("Stripper 3", true), 1544875514,
		TranslationString("Tramp", true), 1224306523,
		TranslationString("Trans", true), -521758348,
		TranslationString("Alien", true), 1684083350
	};

}

void BodyguardMenu::Init() {
	setParentSubmenu<WorldMenu>();
	setName("Bodyguards Creator", true, true);

	addOption(SubmenuOption("Edit spawned bodyguards")
		.addSubmenu<BodyguardMenuEditor>()
		.addTooltip("Edit the spawned bodyguards")
		.addTranslation()
		.addRequirement([] { return GetAuth()->IsVIP(); }));

	addOption(ScrollOption<int>(SCROLLSELECT, "Ped")
		.addRequirement([] { return GetAuth()->IsVIP() && !vars.clonepick; })
		.addScroll(vars.pedchoice, 0, NUMOF(PedSelector) - 1, PedSelector)
		.addTooltip("Select which ped you would like to use as your bodyguard").addTranslation());

	addOption(ScrollOption<int>(SCROLLSELECT, "Weapon")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addScroll(vars.weaponchoice, 0, NUMOF(WeaponSelector) - 1, WeaponSelector)
		.addTooltip("Select which weapon your bodyguard will use").addTranslation());

	addOption(ScrollOption<int>(SCROLLSELECT, "Health")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addScroll(vars.healthchoice, 0, NUMOF(HealthSelector) - 1, HealthSelector)
		.addTooltip("Select the health of your bodyguard").addTranslation());

	addOption(ScrollOption<int>(SCROLL, "Formation")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addScroll(vars.formationchoice, 0, NUMOF(FormationSelector) - 1, FormationSelector)
		.addFunction([] { 
		int MyGroup = PLAYER::GetPlayerGroup(GetLocalPlayer().m_id);
		PED::SetGroupFormation(MyGroup, FormationSelector[vars.formationchoice].m_result);
	})
		.addTooltip("Select the formation at which your bodyguards assemble").addTranslation());

	addOption(ToggleOption("Clone")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.clonepick)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("If you would like the bodyguard to be a clone of yourself instead of a different ped"));

	addOption(ToggleOption("Godmode")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.godmodepick)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("If you would like your bodyguard to have godmode"));

	addOption(ToggleOption("Invisibility")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.Invisible)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("If you would like your bodyguard to be invisible"));

	addOption(ToggleOption("No ragdoll")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.ragdollpick)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("If you would like your bodyguard to not ragdoll when shot or ran over"));

	addOption(ToggleOption("Add blip")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.addblip)
		.addTranslation().addHotkey().canBeSaved()
		.addTooltip("If you want your bodyguard to have a blip on the mini map"));

	addOption(ButtonOption("Spawn it!")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addFunction([] 
			{
				SpawnCloneBodyguard(WeaponSelector[vars.weaponchoice].m_result, PedSelector[vars.pedchoice].m_result, HealthSelector[vars.healthchoice].m_result, FormationSelector[vars.formationchoice].m_result);
				BodyguardMenuEditorVars::vars.SpawnedBodyguards.push_back({ PedSelector[vars.pedchoice].m_name, vars.Bodyguard, vars.addblip, vars.ragdollpick, vars.godmodepick, vars.blip, vars.Invisible });
			})
		.addTranslation().addHotkey().addTooltip("This will spawn your custom bodyguard based off the options you have specified above"));

}

/*Update once when submenu is opened*/
void BodyguardMenu::UpdateOnce() {}

/*Update while submenu is active*/
void BodyguardMenu::Update() {

}

/*Background update*/
void BodyguardMenu::FeatureUpdate() {

}

/*Singleton*/
BodyguardMenu* _instance;
BodyguardMenu* BodyguardMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new BodyguardMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
BodyguardMenu::~BodyguardMenu() { delete _instance; }