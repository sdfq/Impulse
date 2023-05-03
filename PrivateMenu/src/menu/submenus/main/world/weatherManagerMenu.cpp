#include "stdafx.h"
#include "weatherManagerMenu.h"
#include "../worldMenu.h"

using namespace WeatherManagerMenuVars;

namespace WeatherManagerMenuVars {
	Vars vars;

	ScrollStruct<String>  Clouds[] = {
		TranslationString("Cloudy", true), "cloudy 01",
		TranslationString("Rain", true), "rain",
		TranslationString("Horizon Band 1", true), "horizonband1",
		TranslationString("Horizon Band 2", true), "horizonband2",
		TranslationString("Horizon Band 3", true), "horizonband3",
		TranslationString("Puffs", true), "Puffs",
		TranslationString("Wispy", true), "Wispy",
		TranslationString("Horizon", true), "Horizon",
		TranslationString("Stormy", true), "Stormy 01",
		TranslationString("Clear", true), "Clear 01",
		TranslationString("Snowy", true), "Snowy 01",
		TranslationString("Contrails", true), "Contrails",
		TranslationString("Altostratus", true), "altostratus",
		TranslationString("Nimbus", true), "Nimbus",
		TranslationString("Cirrus", true), "Cirrus",
		TranslationString("Cirrocumulus", true), "cirrocumulus",
		TranslationString("Stratoscumulus", true), "stratoscumulus",
		TranslationString("Stripey", true), "Stripey",
		TranslationString("Horsey", true), "horsey",
		TranslationString("Shower", true), "shower"
	};


	ScrollStruct<String> Weathers[] = {
		TranslationString("Clear", true), "CLEAR",
		TranslationString("Clearing", true), "CLEARING",
		TranslationString("Neutral", true), "Neutral",
		TranslationString("Extra Sunny", true), "EXTRASUNNY",
		TranslationString("Rain", true), "RAIN",
		TranslationString("Smog", true), "SMOG",
		TranslationString("Snow", true), "SNOW",
		TranslationString("Xmas", true), "XMAS",
		TranslationString("Halloween", true), "HALLOWEEN",
		TranslationString("Snowlight", true), "SNOWLIGHT",
		TranslationString("Blizzard", true),"BLIZZARD",
		TranslationString("Thunder", true), "THUNDER",
		TranslationString("Overcast", true), "OVERCAST",
		TranslationString("Foggy", true), "FOGGY"
	};

	void Meteors() {
		static vector<int> handles(70);
		if (handles.size() != 0) {
			GetEntityControl()->SimpleRequestModel(0xDF9841D7);
			for (int i = 0; i < handles.size(); i++) {
				if (!ENTITY::DoesEntityExist(handles[i])) {
					handles[i] = OBJECT::CreateObject(0xDF9841D7, GetLocalPlayer().m_coordinates.x + MISC::GetRandomFloatInRange(-350, 350), GetLocalPlayer().m_coordinates.y + MISC::GetRandomFloatInRange(-350, 350), GetLocalPlayer().m_coordinates.z + MISC::GetRandomFloatInRange(160, 249), 1, 1, 0);
					ENTITY::ApplyForceToEntityCenterOfMass(handles[i], 1, 0, 0, -999999, 1, 1, 1, 1);
				} else if (ENTITY::GetEntityHeightAboveGround(handles[i]) < 21 || ENTITY::GetEntitySpeed(handles[i]) == 0.0) {
					Vector3 Coords = ENTITY::GetEntityCoords(handles[i], 1);
					FIRE::AddExplosion(Coords.x, Coords.y, Coords.z, 29, 1000, 1, 0, 0.9f, true);
					GetEntityControl()->SimpleDeleteEntity(handles[i]);
				}
			}
		}
	}
}

void WeatherManagerMenu::Init() {
	setParentSubmenu<WorldMenu>();
	setName("Weather manager", true, true);

	addOption(ScrollOption<String>(SCROLLSELECT, "Clouds")
		.addScroll(vars.clouds, 0, NUMOF(Clouds) - 1, Clouds)
		.addFunction([] {MISC::_SetCloudHatTransition(Clouds[vars.clouds].m_result, 0.5f); })
		.addTooltip("Set the cloud type").addTranslation().addHotkey());

	addOption(ToggleOption("Lightning storm")
		.addToggle(vars.lightning)
		.addHotkey().addTranslation()
		.addTooltip("Summon a lightning storm!"));

	addOption(ToggleOption("Meteor shower")
		.addToggle(vars.meteors)
		.addHotkey().addTranslation()
		.addTooltip("Summon a meteor shower!"));

	addOption(NumberOption<float>(SCROLL, "Rain intensity")
		.addNumber(vars.rain, "%.1f", 0.1f).addMin(0).addMax(100)
		.addFunction([] {MISC::_SetRainFxIntensity(vars.rain); })
		.addTooltip("Set rain intensity").addTranslation());

	addOption(BreakOption("Weather types").addTranslation());

	for (int i = 0; i < NUMOF(Weathers) - 1; i++) {
		addOption(ButtonOption(Weathers[i].m_name.Get())
			.addFunction([=] {MISC::SetWeatherTypeNowPersist(Weathers[i].m_result); })
			.addHotkey().addTranslation()
			.addTooltip("Change the weather"));
	}
}

/*Update once when submenu is opened*/
void WeatherManagerMenu::UpdateOnce() {}

/*Update while submenu is active*/
void WeatherManagerMenu::Update() {}

/*Background update*/
void WeatherManagerMenu::FeatureUpdate() {
	static int TIMER;
	if (vars.lightning) Utils::DoTimedFunction(&TIMER, 500, [] {MISC::_CreateLightningThunder(); });
	if (vars.meteors) Meteors();
}

/*Singleton*/
WeatherManagerMenu* _instance;
WeatherManagerMenu* WeatherManagerMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new WeatherManagerMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
WeatherManagerMenu::~WeatherManagerMenu() { delete _instance; }