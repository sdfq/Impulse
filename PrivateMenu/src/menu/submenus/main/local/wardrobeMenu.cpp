#include "stdafx.h"
#include "wardrobeMenu.h"
#include "wardrobe/wardrobePresetsMenu.h"
#include "wardrobe/loadWardrobeMenu.h"
#include "../localMenu.h"

using namespace WardrobeMenuVars;

namespace WardrobeMenuVars {
	Vars vars;
	void SaveCurrentOutfit(String fileName) {
		ofstream i(fileName);

		json j;

		int props[2][3];
		for (size_t i = 0; i < 3; i++) {
			props[0][i] = PED::GetPedPropIndex(GetLocalPlayer().m_ped, i);
			props[1][i] = PED::GetPedPropTextureIndex(GetLocalPlayer().m_ped, i);
		}

		int components[2][12];
		for (size_t i = 0; i < 12; i++) {
			components[0][i] = PED::GetPedDrawableVariation(GetLocalPlayer().m_ped, i);
			components[1][i] = PED::GetPedTextureVariation(GetLocalPlayer().m_ped, i);
		}

		j["outfit"]["components"] = json::array({
			{ components[0][0], components[0][1], components[0][2], components[0][3], components[0][4], components[0][5], components[0][6], components[0][7], components[0][8], components[0][9], components[0][10], components[0][11] },
			{ components[1][0], components[1][1], components[1][2], components[1][3], components[1][4], components[1][5], components[1][6], components[1][7], components[1][8], components[1][9], components[1][10], components[1][11] }
			});

		j["outfit"]["props"] = json::array({
			{ props[0][0], props[0][1], props[0][2] },
			{ props[1][0], props[1][1], props[1][2] }
			});

		j["outfit"]["model"] = ENTITY::GetEntityModel(GetLocalPlayer().m_ped);

		i << setw(4) << j;
		i.close();
	}

	String apparanceLabel[] = {
		"Face",
		"Masks",
		"Hair",
		"Torso",
		"Legs",
		"Parachute / Misc",
		"Shoes",
		"Extra 1",
		"Tops 1",
		"Body Armor",
		"Crew Emblem",
		"Tops 2"
	};

	String apparanceComponentLabel[] = {
		"Face variation",
		"Masks variation",
		"Hair variation",
		"Torso variation",
		"Legs variation",
		"Parachute / Misc variation",
		"Shoes variation",
		"Extra 1 variation",
		"Tops 1 variation",
		"Body Armor variation",
		"Crew Emblem variation",
		"Tops 2 variation"
	};
}

void WardrobeMenu::Init() {
	setParentSubmenu<LocalMenu>();
	setName("Wardrobe", true, true);

	//addOption(SubmenuOption("Preset outfits")
	//	.addSubmenu<WardrobePresetsMenu>().addHotkey().addTranslation()
	//	.addTooltip("Preset outfits"));

	addOption(SubmenuOption("Load outfits")
		.addSubmenu<LoadWardrobeMenu>().addHotkey().addTranslation()
		.addTooltip("Load saved outfits"));

	addOption(ButtonOption("Save outfit")
		.addFunction([] {
		GetMenuInput()->AddToQueue([] {
			string temp;
			if (GetMenuInput()->Text("Save outfit", temp, 2, 15)) {
				String file = va("%s/%s.json", GetConfig()->GetOutfitsPath(), temp.c_str());
				if (GetConfig()->DoesFileExist(file)) {
					GetRenderer()->NotifyBottom("An outfit with that name already exists. Try again.");
				} else SaveCurrentOutfit(file);
			}});
		})
		.addHotkey().addTranslation()
		.addTooltip("Save outfit"));

	addOption(ButtonOption("Random outfit")
		.addFunction([] {
		PED::SetPedRandomComponentVariation(GetLocalPlayer().m_ped, true);
		PED::SetPedRandomProps(GetLocalPlayer().m_ped);
	}).addHotkey().addTranslation()
		.addTooltip("Get a random outfit"));

	addOption(ButtonOption("Police Uniform")
		.addFunction([] {
		if (ENTITY::GetEntityModel(GetLocalPlayer().m_ped) == Utils::GetHashKey("mp_f_freemode_01")) {
			//hat
			PED::SetPedPropIndex(GetLocalPlayer().m_ped, 0, 45, 0, 0);
			//top
			PED::SetPedComponentVariation(GetLocalPlayer().m_ped, 11, 48, 0, 0);
			//pants
			PED::SetPedComponentVariation(GetLocalPlayer().m_ped, 4, 34, 0, 0);
			//torso
			PED::SetPedComponentVariation(GetLocalPlayer().m_ped, 3, 0, 0, 0);
			//shoes
			PED::SetPedComponentVariation(GetLocalPlayer().m_ped, 6, 25, 0, 0);
			//shoes
			PED::SetPedComponentVariation(GetLocalPlayer().m_ped, 8, 35, 0, 0);
		} else {
			//hat
			PED::SetPedPropIndex(GetLocalPlayer().m_ped, 0, 46, 0, 0);
			//top
			PED::SetPedComponentVariation(GetLocalPlayer().m_ped, 11, 55, 0, 0);
			//pants
			PED::SetPedComponentVariation(GetLocalPlayer().m_ped, 4, 35, 0, 0);
			//torso
			PED::SetPedComponentVariation(GetLocalPlayer().m_ped, 3, 0, 0, 0);
			//shoes
			PED::SetPedComponentVariation(GetLocalPlayer().m_ped, 6, 24, 0, 0);
			//shoes
			PED::SetPedComponentVariation(GetLocalPlayer().m_ped, 9, 0, 0, 0);
		}
	}).addHotkey().addTranslation()
		.addTooltip("Wear police uniform"));

	addOption(ButtonOption("Add Rockstar logo")
		.addFunction([] {
		PED::_SetPedDecoration(GetLocalPlayer().m_ped, -1398869298, -1730534702);
	}).addHotkey().addTranslation()
		.addTooltip("Add Rockstar logo to outfit"));

	addOption(BreakOption());

	addOption(NumberOption<int>(SCROLL, "Hair color")
		.addNumber(vars.hair, "%d", 1).addMin(0).addMax(64)
		.addFunction([] {PED::_SetPedHairColor(GetLocalPlayer().m_ped, vars.hair, 0); })
		.addHotkey().addTranslation()
		.addTooltip("Set hair color"));

	addOption(BreakOption("Props").addTranslation());

	addOption(NumberOption<int>(SCROLL, "Face")
		.addNumber(vars.face, "%d", 1).addMin(-1).addMax(200)
		.addFunction([] {PED::SetPedPropIndex(GetLocalPlayer().m_ped, 0, vars.face, 0, 1); vars.faceVar = 0; })
		.addOnUpdate([]() {vars.face = PED::GetPedPropIndex(GetLocalPlayer().m_ped, 0); })
		.addTooltip("Change face").addTranslation());

	addOption(NumberOption<int>(SCROLL, "Face variation")
		.addNumber(vars.faceVar, "%d", 1).addMin(-1).addMax(200)
		.addFunction([] {PED::SetPedPropIndex(GetLocalPlayer().m_ped, 0, vars.face, vars.faceVar, 1); })
		.addOnUpdate([] {vars.faceVar = PED::GetPedPropTextureIndex(GetLocalPlayer().m_ped, 0); })
		.addTooltip("Change face variation").addTranslation());

	addOption(NumberOption<int>(SCROLL, "Glasses")
		.addNumber(vars.glasses, "%d", 1).addMin(-1).addMax(200)
		.addFunction([] {PED::SetPedPropIndex(GetLocalPlayer().m_ped, 1, vars.glasses, 0, 1); vars.glassesVar = 0; })
		.addOnUpdate([] {vars.glasses = PED::GetPedPropIndex(GetLocalPlayer().m_ped, 1); })
		.addTooltip("Change glasses").addTranslation());

	addOption(NumberOption<int>(SCROLL, "Glasses variation")
		.addNumber(vars.glassesVar, "%d", 1).addMin(-1).addMax(200)
		.addFunction([] {PED::SetPedPropIndex(GetLocalPlayer().m_ped, 1, vars.glasses, vars.glassesVar, 1); })
		.addOnUpdate([] {vars.glassesVar = PED::GetPedPropTextureIndex(GetLocalPlayer().m_ped, 1); })
		.addTooltip("Change glasses variation").addTranslation());

	addOption(NumberOption<int>(SCROLL, "Ear pieces")
		.addNumber(vars.ears, "%d", 1).addMin(-1).addMax(200)
		.addFunction([] {PED::SetPedPropIndex(GetLocalPlayer().m_ped, 2, vars.ears, 0, 1); vars.earsVar = 0; })
		.addOnUpdate([] {vars.ears = PED::GetPedPropIndex(GetLocalPlayer().m_ped, 2); })
		.addTooltip("Change ear pieces").addTranslation());

	addOption(NumberOption<int>(SCROLL, "Ears variation")
		.addNumber(vars.earsVar, "%d", 1).addMin(-1).addMax(200)
		.addFunction([] {PED::SetPedPropIndex(GetLocalPlayer().m_ped, 2, vars.ears, vars.earsVar, 1); })
		.addOnUpdate([] {vars.earsVar = PED::GetPedPropTextureIndex(GetLocalPlayer().m_ped, 2); })
		.addTooltip("Change ear pieces variation").addTranslation());

	addOption(ButtonOption("Clear face")
		.addFunction([] {PED::ClearPedProp(GetLocalPlayer().m_ped, 0); })
		.addTooltip("Clear face variation").addTranslation());

	addOption(ButtonOption("Clear glasses")
		.addFunction([] {PED::ClearPedProp(GetLocalPlayer().m_ped, 1); })
		.addTooltip("Clear glasses variation").addTranslation());

	addOption(ButtonOption("Clear ear pieces")
		.addFunction([] {PED::ClearPedProp(GetLocalPlayer().m_ped, 2); })
		.addTooltip("Clear ear pieces variation").addTranslation());

	addOption(BreakOption("Components").addTranslation());

	for (size_t i = 0; i < 12; i++) {
		addOption(NumberOption<int>(SCROLL, apparanceLabel[i])
			.addNumber(vars.components[i], "%d", 1).addMin(-1).addMax(400)
			.addFunction([i] {PED::SetPedComponentVariation(GetLocalPlayer().m_ped, i, vars.components[i], 0, 0); vars.componentsVar[i] = 0; })
			.addOnUpdate([i] {vars.components[i] = PED::GetPedDrawableVariation(GetLocalPlayer().m_ped, i); })
			.addTooltip(apparanceLabel[i]).addTranslation());

		addOption(NumberOption<int>(SCROLL, apparanceComponentLabel[i])
			.addNumber(vars.componentsVar[i], "%d", 1).addMin(-1).addMax(400)
			.addFunction([i] {PED::SetPedComponentVariation(GetLocalPlayer().m_ped, i, vars.components[i], vars.componentsVar[i], 0); })
			.addOnUpdate([i] {vars.componentsVar[i] = PED::GetPedTextureVariation(GetLocalPlayer().m_ped, i); })
			.addTooltip(apparanceComponentLabel[i]).addTranslation());
	}
}

/*Update once when submenu is opened*/
void WardrobeMenu::UpdateOnce() {}

/*Update while submenu is active*/
void WardrobeMenu::Update() {}

/*Background update*/
void WardrobeMenu::FeatureUpdate() {}

/*Singleton*/
WardrobeMenu* _instance;
WardrobeMenu* WardrobeMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new WardrobeMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
WardrobeMenu::~WardrobeMenu() { delete _instance; }