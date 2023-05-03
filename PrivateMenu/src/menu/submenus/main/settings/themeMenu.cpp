#include "stdafx.h"
#include "themeMenu.h"
#include "../settingsMenu.h"
#include "themeMenu/loadThemesMenu.h"
#include "themeMenu/loadCustomHeaderMenu.h"
#include "UI\windowManager.h"

using namespace ThemeMenuVars;

namespace ThemeMenuVars {
	Vars vars;

	vector<SpriteAnimation> m_animatedHeaders;
	void InitializeAnimatedHeaders() {
		/*SpriteAnimation def(500, true);
		def.AddTexture({ "Bookmarks", "Hipster_Img_1" });
		def.AddTexture({ "Bookmarks", "Hipster_Img_2" });
		def.AddTexture({ "Bookmarks", "Hipster_Img_3" });*/

		/*SpriteAnimation rainbow(150, true);
		rainbow.AddTexture({ "3", "Image1" });
		rainbow.AddTexture({ "3", "Image2" });
		rainbow.AddTexture({ "3", "Image3" });
		rainbow.AddTexture({ "3", "Image4" });
		rainbow.AddTexture({ "3", "Image5" });
		rainbow.AddTexture({ "3", "Image6" });
		rainbow.AddTexture({ "3", "Image7" });
		rainbow.AddTexture({ "3", "Image8" });
		rainbow.AddTexture({ "3", "Image9" });
		rainbow.AddTexture({ "3", "Image10" });*/

		/*SpriteAnimation lightning(200, true);
		lightning.AddTexture({ "Bookmarks", "Image1" });
		lightning.AddTexture({ "Bookmarks", "Image2" });
		lightning.AddTexture({ "Bookmarks", "Image3" });
		lightning.AddTexture({ "Bookmarks", "Image4" });
		lightning.AddTexture({ "Bookmarks", "Image5" });
		lightning.AddTexture({ "Bookmarks", "Image6" });
		lightning.AddTexture({ "Bookmarks", "Image7" });
		lightning.AddTexture({ "Bookmarks", "Image8" });
		lightning.AddTexture({ "Bookmarks", "Image9" });
		lightning.AddTexture({ "Bookmarks", "Image10" });
		lightning.AddTexture({ "Bookmarks", "Image11" });
		lightning.AddTexture({ "Bookmarks", "Image12" });
		lightning.AddTexture({ "Bookmarks", "Image13" });
		lightning.AddTexture({ "Bookmarks", "Image14" });
		lightning.AddTexture({ "Bookmarks", "Image15" });
		lightning.AddTexture({ "Bookmarks", "Image16" });
		lightning.AddTexture({ "Bookmarks", "Image17" });
		lightning.AddTexture({ "Bookmarks", "Image18" });
		lightning.AddTexture({ "Bookmarks", "Image19" });
		lightning.AddTexture({ "Bookmarks", "Image20" });
		lightning.AddTexture({ "Bookmarks", "Image21" });
		lightning.AddTexture({ "Bookmarks", "Image22" });*/

		SpriteAnimation lightning(40, false);
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader00" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader01" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader02" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader03" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader04" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader05" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader06" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader07" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader08" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader09" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader11" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader12" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader13" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader14" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader15" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader16" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader17" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader18" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader19" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader20" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader21" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader22" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader23" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader24" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader25" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader26" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader27" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader28" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader29" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader30" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader31" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader32" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader33" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader34" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader35" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader36" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader37" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader38" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader39" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader40" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader41" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader42" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader43" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader44" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader45" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader46" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader47" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader48" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader49" });
		lightning.AddTexture({ "Bookmarks", "ImpulseAniHeader50" });

		//m_animatedHeaders.push_back(def);
		//m_animatedHeaders.push_back(rainbow);
		m_animatedHeaders.push_back(lightning);
	}

	ScrollStruct<int> fonts[] = {
		TranslationString("Chalet london"), FontChaletLondon,
		TranslationString("HouseScript"), FontHouseScript,
		TranslationString("Monospace"), FontMonoSpace,
		TranslationString("Windlings"), FontWindlings,
		TranslationString("Chalet comprime cologne 1"), FontChaletComprimeCologne,
		TranslationString("Chalet comprime cologne 2"), FontChaletComprimeCologne2,
		TranslationString("Chalet comprime cologne 3"), FontChaletComprimeCologne3,
		TranslationString("Pricedown"), FontPricedown,
		TranslationString("Unk"), 8
	};

	ScrollStruct<Texture> headers[] = {
		TranslationString("Default"),{ "Bookmarks", "ImpulseHeader5" },
		TranslationString("Pulse"),{ "anim", "0" },
		TranslationString("Lightning Bolt"),{ "Bookmarks", "ImpulseHeader2" },
		TranslationString("Pricedown"),{ "Bookmarks", "ImpulseHeader3" },
		TranslationString("Color Grade"),{ "Bookmarks", "ImpulseHeader4" },
		TranslationString("Space"),{ "Bookmarks", "ImpulseHeader1" },
		//TranslationString("Default animated"),{ "anim", "0" },
		//TranslationString("Rainbow Icons"),{ "anim", "1" },
		//TranslationString("Pulse"), {"anim", "0"},
		TranslationString("[C] Cityscape by Seb"),{ "Bookmarks", "Impulse1byseb" },
		TranslationString("[C] Hex gold by Kyupus"),{ "Bookmarks", "Impulse3byKyupus" },
		TranslationString("[C] Hex blue by Kyupus"),{ "Bookmarks", "Impulse4byKyupus" },
		TranslationString("[C] Twitch gold by Kyupus"),{ "Bookmarks", "Impulse5byKyupus" },
		TranslationString("[C] Twitch purple by Kyupus"),{ "Bookmarks", "Impulse6byKyupus" },
		TranslationString("[C] Grave by Kyupus"),{ "Bookmarks", "Impulse8byKyupus" },
		TranslationString("[C] Admin tool by Kyupus"),{ "Bookmarks", "Impulse9byKyupus" },
		TranslationString("[C] Anti engine by Kyupus"),{ "Bookmarks", "Impulse12byKyupus" },
		TranslationString("[C] City by LordSaphir"),{ "Bookmarks", "ImpulseCity1byLordSaphir" },
		TranslationString("[C] Profit tool by unknown"),{ "Bookmarks", "ProfitTool" },
		TranslationString("[C] Retro 1 by unknown"),{ "Bookmarks", "RetroWave1" },
		TranslationString("[C] Retro 2 by unknown"),{ "Bookmarks", "RetroWave2" },
		TranslationString("[C] Retro 3 by unknown"),{ "Bookmarks", "RetroWave3" },
		TranslationString("[C] Retro 4 by unknown"),{ "Bookmarks", "RetroWave4" },
		TranslationString("[C] Retro 5 by unknown"),{ "Bookmarks", "RetroWave5" },
	};

	void SetHeader(int header) {
		vars.header = header;
		if (strcmp(headers[vars.header].m_result.dict, "anim") == 0) {
			GetRenderer()->m_hAnimatedHeader = &m_animatedHeaders[stoi(headers[vars.header].m_result.id)];
		} else {
			GetRenderer()->m_hAnimatedHeader = nullptr;
			GetRenderer()->m_hHeader = headers[vars.header].m_result;
		}
	}

	void SaveTheme(String fileName) {
		ofstream i(fileName);
		json jsonOb = {
			{"Colors", {
				{ "Primary", GetRenderer()->m_cPrimary.getAsJson() },
				{ "Outline", GetRenderer()->m_cOutline.getAsJson() },
				{ "Scroller", GetRenderer()->m_cSelection.getAsJson() },
				{ "SubHeader", GetRenderer()->m_cSubHeader.getAsJson() },
				{ "SubHeaderTitle", GetRenderer()->m_cTitle.getAsJson() },
				{ "Text", GetRenderer()->m_cOption.getAsJson()}
				}
			},
			{ "Text",{
				{ "Font", GetRenderer()->m_textFont },
				{ "Size", GetRenderer()->m_textSize }
				}
			},
			{ "Misc",{
				{ "ColorlessToggles", GetRenderer()->m_colorlessToggles },
				{ "AnimatedArrows", GetRenderer()->m_animatedArrows },
				{ "Arrows", GetRenderer()->m_arrows }
				}
			},
			{ "Menu",{
				{ "Width", GetRenderer()->m_width },
				{ "OptionHeight", GetRenderer()->m_optionHeight},
				{ "XPosition", GetMenu()->m_position.x },
				{ "YPosition", GetMenu()->m_position.y },
				{ "WindowYPosition", GetWindowManager()->m_playerInfo.m_position.y },
				{ "WindowXPosition", GetWindowManager()->m_playerInfo.m_position.x },
				{ "VehicleImgXPosition", GetWindowManager()->m_vehicleInfo.m_position.x },
				{ "VehicleImgYPosition", GetWindowManager()->m_vehicleInfo.m_position.y }
				}
			},
				{"Header", vars.header}
		};

		i << setw(4) << jsonOb;
		i.close();
	}

	void ResetTheme() {
		GetRenderer()->m_cOutline = { 0, 246, 255, 255 };
		GetRenderer()->m_cPrimary = { 0, 0, 0, 255 };
		GetRenderer()->m_cSelection = { 22, 192, 198, 200 };
		GetRenderer()->m_cSubHeader = { 0, 0, 0, 200 };
		GetRenderer()->m_cTitle = { 225, 225, 225, 255 };
		GetRenderer()->m_cOption = { 255, 255, 255, 255 };
		GetRenderer()->m_textFont = FontChaletComprimeCologne;
		GetRenderer()->m_textSize = 0.33f;
		GetRenderer()->m_width = 0.235f;
		GetRenderer()->m_optionHeight = 0.032f;
		GetRenderer()->m_colorlessToggles = false;
		GetRenderer()->m_animatedArrows = false;
		GetRenderer()->m_arrows = 0;
		ThemeMenuVars::SetHeader(0);
	}

	void PaintFader(RGBA* rgbs, int defaultr = 255, int defaultg = 0, int defaultb = 0) {
		switch (rgbs->a) {
		case 0:
			rgbs->r = defaultr;
			rgbs->g = defaultg;
			rgbs->b = defaultb;
			rgbs->a++;
			break;
		case 1:
			rgbs->g++;
			if (rgbs->g == 255)
				rgbs->a++;
			break;
		case 2:
			rgbs->r--;
			if (rgbs->r == 0)
				rgbs->a++;
			break;
		case 3:
			rgbs->b++;
			if (rgbs->b == 255)
				rgbs->a++;
			break;
		case 4:
			rgbs->g--;
			if (rgbs->g == 0)
				rgbs->a++;
			break;
		case 5:
			rgbs->r++;
			if (rgbs->r == 255)
				rgbs->r++;
			break;
		case 6:
			rgbs->b--;
			if (rgbs->b == 0)
				rgbs->a = 0;
			break;
		}
	}

	typedef struct {
		INT RED, GREEN, BLUE;
	} color_3;

	color_3 primary{ 255, 0, 0 }, secondary{ 255, 0, 0 }, thirdly{ 255, 0, 0 };
	void RainbowMode() {

		if (primary.RED > 0 && primary.BLUE == 0) {
			primary.RED--;
			primary.GREEN++;
		}
		if (primary.GREEN > 0 && primary.RED == 0) {
			primary.GREEN--;
			primary.BLUE++;
		}
		if (primary.BLUE > 0 && primary.GREEN == 0) {
			primary.RED++;
			primary.BLUE--;
		}

		if (secondary.RED > 0 && secondary.BLUE == 0) {
			secondary.RED--;
			secondary.GREEN++;
		}
		if (secondary.GREEN > 0 && secondary.RED == 0) {
			secondary.GREEN--;
			secondary.BLUE++;
		}
		if (secondary.BLUE > 0 && secondary.GREEN == 0) {
			secondary.RED++;
			secondary.BLUE--;
		}

		if (thirdly.RED > 0 && thirdly.BLUE == 0) {
			thirdly.RED--;
			thirdly.GREEN++;
		}
		if (thirdly.GREEN > 0 && thirdly.RED == 0) {
			thirdly.GREEN--;
			thirdly.BLUE++;
		}
		if (thirdly.BLUE > 0 && thirdly.GREEN == 0) {
			thirdly.RED++;
			thirdly.BLUE--;
		}

		GetRenderer()->m_cOutline.R = primary.RED;
		GetRenderer()->m_cOutline.G = primary.GREEN;
		GetRenderer()->m_cOutline.B = primary.BLUE;

		GetRenderer()->m_cSelection.R = secondary.RED;
		GetRenderer()->m_cSelection.G = secondary.GREEN;
		GetRenderer()->m_cSelection.B = secondary.BLUE;

		GetRenderer()->m_cSubHeader.R = thirdly.RED;
		GetRenderer()->m_cSubHeader.G = thirdly.GREEN;
		GetRenderer()->m_cSubHeader.B = thirdly.BLUE;
	}

	void RainbowMode1() {

		if (secondary.RED > 0 && secondary.BLUE == 0) {
			secondary.RED--;
			secondary.GREEN++;
		}
		if (secondary.GREEN > 0 && secondary.RED == 0) {
			secondary.GREEN--;
			secondary.BLUE++;
		}
		if (secondary.BLUE > 0 && secondary.GREEN == 0) {
			secondary.RED++;
			secondary.BLUE--;
		}

		GetRenderer()->m_cOutline.R = secondary.RED;
		GetRenderer()->m_cOutline.G = secondary.GREEN;
		GetRenderer()->m_cOutline.B = secondary.BLUE;

	}
	void RainbowMode2() {

		if (secondary.RED > 0 && secondary.BLUE == 0) {
			secondary.RED--;
			secondary.GREEN++;
		}
		if (secondary.GREEN > 0 && secondary.RED == 0) {
			secondary.GREEN--;
			secondary.BLUE++;
		}
		if (secondary.BLUE > 0 && secondary.GREEN == 0) {
			secondary.RED++;
			secondary.BLUE--;
		}

		GetRenderer()->m_cSelection.R = secondary.RED;
		GetRenderer()->m_cSelection.G = secondary.GREEN;
		GetRenderer()->m_cSelection.B = secondary.BLUE;

	}

	void RainbowMode3() {

		if (secondary.RED > 0 && secondary.BLUE == 0) {
			secondary.RED--;
			secondary.GREEN++;
		}
		if (secondary.GREEN > 0 && secondary.RED == 0) {
			secondary.GREEN--;
			secondary.BLUE++;
		}
		if (secondary.BLUE > 0 && secondary.GREEN == 0) {
			secondary.RED++;
			secondary.BLUE--;
		}

		GetRenderer()->m_cSubHeader.R = secondary.RED;
		GetRenderer()->m_cSubHeader.G = secondary.GREEN;
		GetRenderer()->m_cSubHeader.B = secondary.BLUE;

	}

	
}

void ThemeMenu::Init() {
	setParentSubmenu<SettingsMenu>();
	setName("Theme", true, true);

	InitializeAnimatedHeaders();

	addString("A file with that name already exists. Try again.");

	addOption(SubmenuOption("Load custom headers")
		.addRequirement([] {return GetAuth()->IsVIP(); })
		.addSubmenu<LoadCustomHeaderMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Load custom menu headers"));

	addOption(SubmenuOption("Load themes")
		.addSubmenu<LoadThemesMenu>()
		.addHotkey().addTranslation()
		.addTooltip("Load saved themes"));

	addOption(ButtonOption("Save theme")
		.addFunction([this] {
		GetMenuInput()->AddToQueue([this] {
			string temp;
			if (GetMenuInput()->Text("Theme name", temp, 2, 15)) {
				String file = va("%s/%s.json", GetConfig()->GetThemesPath(), temp.c_str());

				if (GetConfig()->DoesFileExist(file)) {
					GetRenderer()->NotifyBottom(getString("A file with that name already exists. Try again."));
				} else SaveTheme(file);
			}});
	}).addTranslation()
		.addHotkey()
		.addTooltip("Save vehicle"));

	addOption(ButtonOption("Reset theme")
		.addFunction([] {ResetTheme(); })
		.addHotkey().addTranslation()
		.addTooltip("Rest the current menu theme"));

	addOption(BreakOption("Customize").addTranslation());

	addOption(ColorOption("Primary")
		.addOnUpdate([](ColorOption* option) {option->addColor(GetRenderer()->m_cPrimary); })
		.addHotkey().addTranslation()
		.addTooltip("Set the primary menu color"));

	addOption(ColorOption("Outline")
		.addOnUpdate([](ColorOption* option) {option->addColor(GetRenderer()->m_cOutline); })
		.addHotkey().addTranslation()
		.addTooltip("Set the menu outline color"));

	addOption(ColorOption("Scroller")
		.addOnUpdate([](ColorOption* option) {option->addColor(GetRenderer()->m_cSelection); })
		.addHotkey().addTranslation()
		.addTooltip("Selected option highlight"));

	addOption(ColorOption("Subheader")
		.addOnUpdate([](ColorOption* option) {option->addColor(GetRenderer()->m_cSubHeader); })
		.addHotkey().addTranslation()
		.addTooltip("Subheader color"));

	addOption(ColorOption("Subheader title")
		.addOnUpdate([](ColorOption* option) {option->addColor(GetRenderer()->m_cTitle); })
		.addHotkey().addTranslation()
		.addTooltip("Set the menu subheader title color"));

	addOption(ColorOption("Menu text")
		.addOnUpdate([](ColorOption* option) {option->addColor(GetRenderer()->m_cOption); })
		.addHotkey().addTranslation()
		.addTooltip("Set the menu text color"));

	addOption(BreakOption("Font").addTranslation());

	addOption(ScrollOption<int>(SCROLL, "Font")
		.addScroll(vars.font, 0, NUMOF(fonts) - 1, fonts)
		.addFunction([&] {GetRenderer()->m_textFont = fonts[vars.font].m_result; })
		.addHotkey().addTranslation()
		.addTooltip("Change the font type"));

	addOption(NumberOption<float>(SCROLL, "Font size")
		.addNumber(GetRenderer()->m_textSize, "%.3f", 0.005f).addMin(0).addMax(0.55f)
		.addHotkey().addTranslation()
		.addTooltip("Change the font size"));

	addOption(BreakOption("Menu").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Menu X axis")
		.addNumber(GetMenu()->m_position.x, "%.3f", 0.005f).addMin(-2.0f).addMax(2.0f).setScrollSpeed(20)
		.addHotkey().addTranslation()
		.addTooltip("Change the position of the trainer"));

	addOption(NumberOption<float>(SCROLL, "Menu Y axis")
		.addNumber(GetMenu()->m_position.y, "%.3f", 0.005f).addMin(-2.0f).addMax(2.0f).setScrollSpeed(20)
		.addHotkey().addTranslation()
		.addTooltip("Change the position of the trainer"));

	addOption(NumberOption<float>(SCROLL, "Infoxbox X axis")
		.addNumber(GetWindowManager()->m_playerInfo.m_position.x, "%.3f", 0.005f).addMin(-2.0f).addMax(2.0f).setScrollSpeed(20)
		.addHotkey().addTranslation()
		.addTooltip("Change the position of the infobox"));

	addOption(NumberOption<float>(SCROLL, "Infobox Y axis")
		.addNumber(GetWindowManager()->m_playerInfo.m_position.y, "%.3f", 0.005f).addMin(-2.0f).addMax(2.0f).setScrollSpeed(20)
		.addHotkey().addTranslation()
		.addTooltip("Change the position of the infoxbox"));

	addOption(NumberOption<float>(SCROLL, "Vehicle image X axis")
		.addNumber(GetWindowManager()->m_vehicleInfo.m_position.x, "%.3f", 0.005f).addMin(-2.0f).addMax(2.0f).setScrollSpeed(20)
		.addHotkey().addTranslation()
		.addTooltip("Change the position of the vehicle image box"));

	addOption(NumberOption<float>(SCROLL, "Vehicle image Y axis")
		.addNumber(GetWindowManager()->m_vehicleInfo.m_position.y, "%.3f", 0.005f).addMin(-2.0f).addMax(2.0f).setScrollSpeed(20)
		.addHotkey().addTranslation()
		.addTooltip("Change the position of the vehicle image box"));

	addOption(NumberOption<float>(SCROLL, "Menu width")
		.addNumber(GetRenderer()->m_width, "%.3f", 0.001f).addMin(0).addMax(0.5f).setScrollSpeed(20)
		.addHotkey().addTranslation()
		.addTooltip("Change the width of the menu"));

	addOption(NumberOption<float>(SCROLL, "Option height")
		.addNumber(GetRenderer()->m_optionHeight, "%.3f", 0.001f).addMin(0.02f).addMax(0.055f)
		.addHotkey().addTranslation()
		.addTooltip("Change height of the option count"));

	addOption(ScrollOption<Texture>(SCROLL, "Header")
		.addScroll(vars.header, 0, NUMOF(headers) - 1, headers)
		.addFunction([&] { SetHeader(vars.header); })
		.addHotkey().addTranslation()
		.addTooltip("Change the header ontop of the menu - community headers start with [C]"));

	addOption(BreakOption("Misc").addTranslation());

	addOption(NumberOption<int>(SCROLL, "Arrows")
		.addNumber(GetRenderer()->m_arrows, "%i", 1).addMin(0).addMax(5).setScrollSpeed(1)
		.addHotkey().addTranslation()
		.addTooltip("Change the arrow design"));

	addOption(ToggleOption("Colorless toggles")
		.addToggle(GetRenderer()->m_colorlessToggles)
		.addHotkey().addTranslation()
		.addTooltip("Use colorless toggles"));

	addOption(ToggleOption("Animated arrows")
		.addToggle(GetRenderer()->m_animatedArrows)
		.addHotkey().addTranslation()
		.addTooltip("Use animated submenu arrows"));

	addOption(ToggleOption("Rainbow elements of trainer")
		.addRequirement([] { return !vars.rainbow1 && !vars.rainbow2 && !vars.rainbow3; })
		.addToggle(vars.rainbow)
		.addHotkey().addTranslation().canBeSaved()
		.addTooltip("Make certain elements of the trainer rainbow color"));

	addOption(ButtonOption("~c~Rainbow elements of trainer~s~")
		.addRequirement([] { return vars.rainbow1 || vars.rainbow2 || vars.rainbow3; })
	);

	addOption(ToggleOption("Rainbow outline of trainer")
		.addRequirement([] { return !vars.rainbow; })
		.addToggle(vars.rainbow1)
		.addHotkey().addTranslation().canBeSaved()
		.addTooltip("Make a certain element of the trainer rainbow color"));

	addOption(ButtonOption("~c~Rainbow outline of trainer~s~")
		.addRequirement([] { return vars.rainbow; })
	);

	addOption(ToggleOption("Rainbow scroller of trainer")
		.addRequirement([] { return !vars.rainbow; })
		.addToggle(vars.rainbow2)
		.addHotkey().addTranslation().canBeSaved()
		.addTooltip("Make a certain element of the trainer rainbow color"));

	addOption(ButtonOption("~c~Rainbow scroller of trainer~s~")
		.addRequirement([] { return vars.rainbow; })
	);

	addOption(ToggleOption("Rainbow subheader of trainer")
		.addRequirement([] { return !vars.rainbow; })
		.addToggle(vars.rainbow3)
		.addHotkey().addTranslation().canBeSaved()
		.addTooltip("Make a certain element of the trainer rainbow color"));

	addOption(ButtonOption("~c~Rainbow subheader of trainer~s~")
		.addRequirement([] { return vars.rainbow; })
	);
}

/*Update once when submenu is opened*/
void ThemeMenu::UpdateOnce() {}

/*Update while submenu is active*/
void ThemeMenu::Update() {}

/*Background update*/
void ThemeMenu::FeatureUpdate() {
	if (vars.rainbow) RainbowMode();
	if (vars.rainbow1) RainbowMode1();
	if (vars.rainbow2) RainbowMode2();
	if (vars.rainbow3) RainbowMode3();
}

/*Singleton*/
ThemeMenu* _instance;
ThemeMenu* ThemeMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new ThemeMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
ThemeMenu::~ThemeMenu() { delete _instance; }