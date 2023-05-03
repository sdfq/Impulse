#include "stdafx.h"
#include "animationMenu.h"
#include "../localMenu.h"

using namespace AnimationMenuVars;

namespace AnimationMenuVars {
	Vars vars;

	struct AnimationTypes {
		//String m_name;
		String m_dict;
		String m_anim;
	};


	ScrollStruct<AnimationTypes> animationScrollStruct[] = {
		TranslationString("Push-Ups"),{ "amb@world_human_push_ups@male@base", "base" },
		TranslationString("Sit-Ups"),{ "amb@world_human_sit_ups@male@base", "base" },
		TranslationString("Celebrate"),{ "rcmfanatic1celebrate", "celebrate" },
		TranslationString("Electrocution"),{ "ragdoll@human", "electrocute" },
		TranslationString("Shower"),{ "mp_safehouseshower@male@", "male_shower_idle_b" },
		TranslationString("Suicide (pill)"),{ "mp_suicide", "pill" },
		TranslationString("Dog pissing"),{ "creatures@rottweiler@move", "pee_right_idle" },
		TranslationString("Dog sex"),{ "missfra0_chop_find", "hump_loop_chop" },
		TranslationString("Celebration"),{ "mini@dartsintro", "darts_outro_03_guy2" },
		TranslationString("Suicide (Pistol)"),{ "mp_suicide", "pistol" },
		TranslationString("Stripper dance"),{ "mini@strip_club@private_dance@part1", "priv_dance_p1" },
		TranslationString("Celebration 2"),{ "mini@golfclubhouse", "clubhouse_leave_win_plyr" },
		TranslationString("Wave 1"),{ "friends@frj@ig_1", "wave_a" },
		TranslationString("Wave 2"),{ "friends@frj@ig_1", "wave_b" },
		TranslationString("Mountain dance"),{ "special_ped@mountain_dancer@base", "base" },
		TranslationString("Heaven dance"),{ "special_ped@mountain_dancer@monologue_1@monologue_1a", "mtn_dnc_if_you_want_to_get_to_heaven" },
		TranslationString("Angel dance"),{ "special_ped@mountain_dancer@monologue_2@monologue_2a", "mnt_dnc_angel" },
		TranslationString("Buttwag dance"),{ "special_ped@mountain_dancer@monologue_3@monologue_3a", "mnt_dnc_buttwag" },
		TranslationString("Pole dance"),{ "mini@strip_club@pole_dance@pole_dance1", "pd_dance_01" },
		TranslationString("Pole dance 2"),{ "mini@strip_club@pole_dance@pole_dance2", "pd_dance_02" },
		TranslationString("Pole dance 3"),{ "mini@strip_club@pole_dance@pole_dance3", "pd_dance_03" },
		TranslationString("Skrillex dance"),{ "misschinese2_crystalmazemcs1_cs", "dance_loop_tao" },
		TranslationString("Hood dance"),{ "missfbi3_sniping", "dance_m_default" },
		TranslationString("Dance verse"),{ "special_ped@mountain_dancer@monologue_4@monologue_4a", "mnt_dnc_verse" },
		TranslationString("Wave arms"),{ "random@car_thief@victimpoints_ig_3", "arms_waving" },
		TranslationString("Wave 3"),{ "friends@frj@ig_1", "wave_c" },
		TranslationString("Wave 4"),{ "friends@frj@ig_1", "wave_d" },
		TranslationString("Wave 5"),{ "friends@frj@ig_1", "wave_e" },
		TranslationString("Sex receiver"),{ "rcmpaparazzo_2", "shag_loop_poppy" },
		TranslationString("Sex giver"),{ "rcmpaparazzo_2", "shag_loop_a" }
	};

	ScrollStruct<String> walkstyleScrollStruct[] = {
		TranslationString("Generic Male"), "move_m@generic",
		TranslationString("Generic Female"), "move_f@generic",
		TranslationString("Drunk (Male)"), "move_m@drunk@a",
		TranslationString("Slightly Drunk (Male)"), "move_m@drunk@slightlydrunk",
		TranslationString("Moderately Drunk (Male)"), "move_m@drunk@moderatedrunk",
		TranslationString("Moderately Drunk (Male) 2"), "move_m@drunk@moderatedrunk_head_up",
		TranslationString("Very Drunk (Male)"), "move_m@drunk@verydrunk",
		TranslationString("Very Drunk (Female)"), "move_f@drunk@verydrunk",
		TranslationString("Hiking"), "move_m@hiking",
		/*TranslationString("Burning"), "move_m@fire",
		TranslationString("Flee"), "move_m@flee@a",
		TranslationString("Flee 2"), "move_m@flee@b",
		TranslationString("Flee 3"), "move_m@flee@c",
		TranslationString("Flee 4"), "move_f@flee@a",
		TranslationString("Flee 5"), "move_f@flee@b",
		TranslationString("Flee 6"), "move_f@flee@c",
		TranslationString("Hiking (Male)"), "move_m@hiking",
		TranslationString("Hiking (Female)"), "move_f@hiking",
		TranslationString("Intimidation"), "move_m@intimidation@1h",
		TranslationString("Intimidation (Cop Unarmed)"), "move_m@intimidation@cop@unarmed",
		TranslationString("Intimidation (Unarmed)"), "move_m@intimidation@unarmed",
		TranslationString("Muscular"), "move_m@muscle@a",
		TranslationString("Shady"), "move_m@shadyped@a",
		TranslationString("Shocked"), "move_m@shocked@a",
		TranslationString("Quick"), "move_m@quick",*/
	};

	ScrollStruct<String> scenarioScrollStruct[] = {
		TranslationString("Freeway Bum"), "WORLD_HUMAN_BUM_FREEWAY",
		TranslationString("Grazing Boar"), "WORLD_BOAR_GRAZING",
		TranslationString("Yoga"), "WORLD_HUMAN_YOGA",
		TranslationString("Bench Press"), "PROP_HUMAN_SEAT_MUSCLE_BENCH_PRESS",
		TranslationString("Party"), "WORLD_HUMAN_PARTYING",
		TranslationString("Shine Flashlight"), "WORLD_HUMAN_SECURITY_SHINE_TORCH",
		TranslationString("Tourist Map"), "WORLD_HUMAN_TOURIST_MAP",
		TranslationString("Binoculars"), "WORLD_HUMAN_BINOCULARS",
		TranslationString("Parking Attendant"), "WORLD_HUMAN_CAR_PARK_ATTENDANT",
		TranslationString("Drill"), "WORLD_HUMAN_CONST_DRILL",
		TranslationString("Leaf Blower"), "WORLD_HUMAN_GARDENER_LEAF_BLOWER",
		TranslationString("Hammering"), "WORLD_HUMAN_HAMMERING",
		TranslationString("Janitor"), "WORLD_HUMAN_JANITOR",
		TranslationString("Fishing"), "WORLD_HUMAN_STAND_FISHING",
		TranslationString("Sleeping Bum"), "WORLD_HUMAN_BUM_SLUMPED",
		TranslationString("Cheer"), "WORLD_HUMAN_CHEERING",
		TranslationString("Drunk"), "WORLD_HUMAN_DRINKING",
		TranslationString("Human Statue"), "WORLD_HUMAN_HUMAN_STATUE",
		TranslationString("Coffee"), "WORLD_HUMAN_AA_COFFEE",
		TranslationString("Smoking"), "WORLD_HUMAN_AA_SMOKE",
		TranslationString("Musician"), "WORLD_HUMAN_MUSICIAN",
		TranslationString("BBQ"), "PROP_HUMAN_BBQ",
		TranslationString("Yoga"), "WORLD_HUMAN_YOGA",
		TranslationString("Maid"), "WORLD_HUMAN_MAID_CLEAN",
		TranslationString("Welding"), "WORLD_HUMAN_WELDING",
		TranslationString("Grazing Cow"), "WORLD_COW_GRAZING",
		TranslationString("Coyote Howl"), "WORLD_COYOTE_HOWL",
		TranslationString("Coyote Rest"), "WORLD_COYOTE_REST",
		TranslationString("Coyote Wander"), "WORLD_COYOTE_WANDER",
		TranslationString("Rottweiler Bark"), "WORLD_DOG_BARKING_ROTTWEILER",
		TranslationString("Idle Jogger"), "WORLD_HUMAN_JOG_STANDING",
		TranslationString("Golf"), "WORLD_HUMAN_GOLF_PLAYER",
		TranslationString("Muscle Flex"), "WORLD_HUMAN_MUSCLE_FLEX",
		TranslationString("Free Weights"), "WORLD_HUMAN_MUSCLE_FREE_WEIGHTS",
		TranslationString("Tennis"), "WORLD_HUMAN_TENNIS_PLAYER"
	};

	void DoAnimation() {
		if (!STREAMING::HasAnimDictLoaded(vars.dict)) {
			STREAMING::RequestAnimDict(vars.dict);
		} else {
			BRAIN::TaskPlayAnim(GetLocalPlayer().m_ped, vars.dict, vars.anim, 8, 1, -1, vars.flag, 0, 0, 0, 0);
			vars.run = false;
		}
	}

	void DoWalkstyle() {
		if (!STREAMING::HasAnimSetLoaded(vars.walkstyleAnim)) {
			STREAMING::RequestAnimSet(vars.walkstyleAnim);
		} else {
			PED::SetPedMovementClipset(GetLocalPlayer().m_ped, vars.walkstyleAnim, 1048576000);
			BRAIN::ClearPedTasksImmediately(GetLocalPlayer().m_ped);
			vars.runWalkstyle = false;
		}
	}
}

void AnimationMenu::Init() {
	setParentSubmenu<LocalMenu>();
	setName("Animations", true, true);

	addOption(ButtonOption("Stop all animations")
		.addFunction([] { BRAIN::ClearPedTasksImmediately(GetLocalPlayer().m_ped); })
		.addTooltip("Stop all running animations").addTranslation().addHotkey());

	addOption(ToggleOption("Controllable")
		.addToggle(vars.controllable).addTranslation().addHotkey()
		.addTooltip("Control your ped while doing an animation"));

	addOption(ToggleOption("Contort")
		.addToggle(vars.contort).addTranslation().addHotkey()
		.addTooltip("Completely fuck the animation"));

	addOption(ScrollOption<AnimationTypes>(SCROLLSELECT, "Animations")
		.addToggle(vars.animationToggle)
		.addScroll(vars.animation, 0, NUMOF(animationScrollStruct) - 1, animationScrollStruct)
		.addFunction([] {
		if (!vars.controllable && !vars.contort) {
			vars.flag = 9;
		} else if (!vars.controllable && vars.contort) {
			vars.flag = 257;
		} else if (vars.controllable && !vars.contort) {
			vars.flag = 121;
		} else if (vars.controllable && vars.contort) {
			vars.flag = 377;
		}

		vars.anim = animationScrollStruct[vars.animation].m_result.m_anim;
		vars.dict = animationScrollStruct[vars.animation].m_result.m_dict;
		vars.run = true;
	})
		.addTooltip("Play this animation").addTranslation().addHotkey());

	addOption(ScrollOption<String>(SCROLLSELECT, "Walkstyles")
		.addToggle(vars.walkstyleToggle)
		.addScroll(vars.walkstyle, 0, NUMOF(walkstyleScrollStruct) - 1, walkstyleScrollStruct)
		.addFunction([] { vars.walkstyleAnim = walkstyleScrollStruct[vars.walkstyle].m_result; vars.runWalkstyle = true; })
		.addTooltip("Play this walkstyle").addTranslation().addHotkey());

	addOption(ScrollOption<String>(SCROLLSELECT, "Scenarios")
		.addToggle(vars.scenarioToggle)
		.addScroll(vars.scenario, 0, NUMOF(scenarioScrollStruct) - 1, scenarioScrollStruct)
		.addFunction([] { BRAIN::ClearPedTasksImmediately(GetLocalPlayer().m_ped); BRAIN::TaskStartScenarioInPlace(GetLocalPlayer().m_ped, scenarioScrollStruct[vars.scenario].m_result, 0, true); })
		.addTooltip("Play this scenario").addTranslation().addHotkey());

	/*addOption(BreakOption("All Animations").addTranslation());

	addOption(ButtonOption("Search")
		.addFunction([] {
		GetMenuInput()->AddToQueue([] {
			string input;
			if (GetMenuInput()->Text("Search model", input, 0, 100)) {
				string lower = toLower(input);
				for (auto& op : m_modelOptions) {
					string temp = op->getName().GetOriginal();
					op.get()->setVisible(toLower(temp).find(lower) != string::npos);
				}
				if (input[0] == '\0') m_searchBreak.get()->setLine();
				else m_searchBreak.get()->setName(((string)input).c_str());
				if (GetMenu()->m_maxOptions + GetMenu()->m_scrollOffset > GetSubmenuHandler()->GetTotalOptions()) {
					int offset = GetMenu()->m_maxOptions + GetMenu()->m_scrollOffset - GetSubmenuHandler()->GetTotalOptions();
					Top();
					GetMenu()->m_currentOption = 8;
				}
			}
		}); }).addTranslation()
			.addTooltip("Search for a animation name"));

	m_searchBreak = addOption(BreakOption());

	for (int i = 0; i < NUMOF(m_models); i++) {
		m_modelOptions[i] = addOption(ButtonOption(m_models[i].m_name)
			.addFunction([=] {SetModel(m_models[i].m_model);
		GetFiberPool()->DoJob([=] {
			WAIT(1000);
			int Ammo = -1;
			for (int i = 0; i < 82; i++) {
				WEAPON::GetMaxAmmo(GetLocalPlayer().m_ped, usableWeaponHashes[i], &Ammo);
				WEAPON::GiveWeaponToPed(GetLocalPlayer().m_ped, usableWeaponHashes[i], Ammo, false, true);
			}
		});	})
			.addHotkey()
			.addTooltip(m_models[i].m_name));
	}*/
}

/*Update once when submenu is opened*/
void AnimationMenu::UpdateOnce() {}

/*Update while submenu is active*/
void AnimationMenu::Update() {}

/*Background update*/
void AnimationMenu::FeatureUpdate() {
	if (vars.run) DoAnimation();
	if (vars.runWalkstyle) DoWalkstyle();
}

/*Singleton*/
AnimationMenu* _instance;
AnimationMenu* AnimationMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new AnimationMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
AnimationMenu::~AnimationMenu() { delete _instance; }