#include "stdafx.h"
#include "miscTVMenu.h"
#include "../miscMenu.h"

using namespace MiscTVMenuVars;

namespace MiscTVMenuVars {
	Vars vars;
}

void MiscTVMenu::Init() {
	setParentSubmenu<MiscMenu>();
	setName("TV", true, true);

	addOption(ToggleOption("Toggle TV")
		.addToggle(vars.tv));

	addOption(NumberOption<int>(SCROLL, "Change channel")
		.addNumber(vars.channel, "%i", 1).addMin(0).addMax(3)
		.addFunction([] { GRAPHICS::SetTvChannel(vars.channel); }));

	addOption(NumberOption<float>(SCROLL, "X")
		.addNumber(vars.x, "%.2f", 0.01f).addMin(0.0f).addMax(1.0f));

	addOption(NumberOption<float>(SCROLL, "Y")
		.addNumber(vars.y, "%.2f", 0.01f).addMin(0.0f).addMax(1.0f));

	addOption(NumberOption<float>(SCROLL, "W")
		.addNumber(vars.w, "%.2f", 0.01f).addMin(0.0f).addMax(1.0f));

	addOption(NumberOption<float>(SCROLL, "H")
		.addNumber(vars.h, "%.2f", 0.01f).addMin(0.0f).addMax(1.0f));

	addOption(NumberOption<float>(SCROLL, "Rotation")
		.addNumber(vars.rotation, "%.2f", 0.01f).addMin(0.0f).addMax(360.0f));
}

/*Update once when submenu is opened*/
void MiscTVMenu::UpdateOnce() {}

/*Update while submenu is active*/
void MiscTVMenu::Update() {}

/*Background update*/
void MiscTVMenu::FeatureUpdate() {
	if (vars.tv) {
		HUD::SetHudComponentPosition(15, 0.0f, -0.0375f);
		HUD::SetTextRenderId(1);
		GRAPHICS::_Set2DLayer(4);
		GRAPHICS::_0xC6372ECD45D73BCD(1);
		GRAPHICS::DrawTvChannel(vars.x, vars.y, vars.w, vars.h, vars.rotation, 255, 255, 255, 255);
		HUD::SetTextRenderId(HUD::GetDefaultScriptRendertargetRenderId());
	}
}

/*Singleton*/
MiscTVMenu* _instance;
MiscTVMenu* MiscTVMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new MiscTVMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
MiscTVMenu::~MiscTVMenu() { delete _instance; }