#include "stdafx.h"
#include "vehicleResprayMenu.h"
#include "../LSCMenu.h"

using namespace VehicleResprayMenuVars;

namespace VehicleResprayMenuVars {
	Vars vars;

	ScrollStruct<int> ClassicColors[] = {
		TranslationString("Black"), 0,
		TranslationString("Carbon black"), 147,
		TranslationString("Graphite"), 1,
		TranslationString("Anhracite black"), 11,
		TranslationString("Black steel"), 2,
		TranslationString("Dark steel"), 3,
		TranslationString("Silver"), 4,
		TranslationString("Bluish silver"), 5,
		TranslationString("Rolled steel"), 6,
		TranslationString("Shadow silver"), 7,
		TranslationString("Stone silver"), 8,
		TranslationString("Midnight silver"), 9,
		TranslationString("Cast iron silver"), 10,
		TranslationString("Red"), 27,
		TranslationString("Torino red"), 28,
		TranslationString("Formula red"), 29,
		TranslationString("Lava red"), 150,
		TranslationString("Blaze red"), 30,
		TranslationString("Grace red"), 31,
		TranslationString("Garnet red"), 32,
		TranslationString("Sunset red"), 33,
		TranslationString("Cabernet red"), 34,
		TranslationString("Wine red"), 143,
		TranslationString("Candy red"), 35,
		TranslationString("Hot pink"), 135,
		TranslationString("Pfsiter pink"), 137,
		TranslationString("Salmon pink"), 136,
		TranslationString("Sunrise orange"), 36,
		TranslationString("Orange"), 38,
		TranslationString("Bright orange"), 138,
		TranslationString("Gold"), 99,
		TranslationString("Bronze"), 90,
		TranslationString("Yellow"), 88,
		TranslationString("Race yellow"), 89,
		TranslationString("Dew yellow"), 91,
		TranslationString("Dark green"), 49,
		TranslationString("Racing green"), 50,
		TranslationString("Sea green"), 51,
		TranslationString("Olive green"), 52,
		TranslationString("Bright green"), 53,
		TranslationString("Gasoline green"), 54,
		TranslationString("Lime green"), 92,
		TranslationString("Midnight blue"), 141,
		TranslationString("Galaxy blue"), 61,
		TranslationString("Dark blue"), 62,
		TranslationString("Saxon blue"), 63,
		TranslationString("Blue"), 64,
		TranslationString("Mariner blue"), 65,
		TranslationString("Harbor blue"), 66,
		TranslationString("Diamond blue"), 67,
		TranslationString("Surf blue"), 68,
		TranslationString("Nautical blue"), 69,
		TranslationString("Racing blue"), 73,
		TranslationString("Ultra blue"), 70,
		TranslationString("Light blue"), 74,
		TranslationString("Chocolate brown"), 96,
		TranslationString("Bison brown"), 101,
		TranslationString("Creeen brown"), 95,
		TranslationString("Feltzer brown"), 94,
		TranslationString("Maple brown"), 97,
		TranslationString("Beechwood brown"), 103,
		TranslationString("Sienna brown"), 104,
		TranslationString("Saddle brown"), 98,
		TranslationString("Moss brown"), 100,
		TranslationString("Woodbeech brown"), 102,
		TranslationString("Straw brown"), 99,
		TranslationString("Sandy brown"), 105,
		TranslationString("Bleached brown"), 106,
		TranslationString("Schafter purple"), 71,
		TranslationString("Spinnaker purple"), 72,
		TranslationString("Midnight purple"), 142,
		TranslationString("Bright purple"), 145,
		TranslationString("Cream"), 107,
		TranslationString("Ice white"), 111,
		TranslationString("Frost white"), 112
	}, MatteColors[] = {
		TranslationString("Black"), 12,
		TranslationString("Gray"), 13,
		TranslationString("Light gray"), 14,
		TranslationString("Ice white"), 131,
		TranslationString("Blue"), 83,
		TranslationString("Dark blue"), 82,
		TranslationString("Midnight blue"), 84,
		TranslationString("Midnight purple"), 149,
		TranslationString("Schafter purple"), 148,
		TranslationString("Red"), 39,
		TranslationString("Dark red"), 40,
		TranslationString("Orange"), 41,
		TranslationString("Yellow"), 42,
		TranslationString("Lime green"), 55,
		TranslationString("Green"), 128,
		TranslationString("Forest green"), 151,
		TranslationString("Foliage green"), 155,
		TranslationString("Olive darb"), 152,
		TranslationString("Dark earth"), 153,
		TranslationString("Desert tan"), 154
	}, MetalColors[] = {
		TranslationString("Pearlescent steel"), 18,
		TranslationString("Brushed steel"), 117,
		TranslationString("Brushed black steel"), 118,
		TranslationString("Brushed aluminum"), 119,
		TranslationString("Pure gold"), 158,
		TranslationString("Brushed gold"), 159,
		TranslationString("Pearlescent gold"), 160
	};

	void SetVehiclePrimaryColor(Color color) {
		VEHICLE::SetVehicleCustomPrimaryColour(GetLocalPlayer().m_vehicle, color.m_r, color.m_g, color.m_b);
	}
	void SetVehicleSecondaryColor(Color color) {
		VEHICLE::SetVehicleCustomSecondaryColour(GetLocalPlayer().m_vehicle, color.m_r, color.m_g, color.m_b);
	}

	void ClearCustomVehicleColors() {
		VEHICLE::ClearVehicleCustomPrimaryColour(GetLocalPlayer().m_vehicle);
		VEHICLE::ClearVehicleCustomSecondaryColour(GetLocalPlayer().m_vehicle);
	}

	void SetVehiclePrimaryColor(int color) {
		int r, g, b;
		VEHICLE::GetVehicleCustomSecondaryColour(GetLocalPlayer().m_vehicle, &r, &g, &b);
		Color col = { r, g, b, 0 };
		VEHICLE::SetVehicleColours(GetLocalPlayer().m_vehicle, color, color);
		SetVehicleSecondaryColor(col);
	}

	void SetVehicleSecondaryColor(int color) {
		int r, g, b;
		VEHICLE::GetVehicleCustomPrimaryColour(GetLocalPlayer().m_vehicle, &r, &g, &b);
		Color col = { r, g, b, 0 };
		VEHICLE::SetVehicleColours(GetLocalPlayer().m_vehicle, color, color);
		SetVehiclePrimaryColor(col);
	}

	void SetVehiclePearlescentColor(int color) {
		int colTemp, nullCol;
		VEHICLE::GetVehicleExtraColours(GetLocalPlayer().m_vehicle, &nullCol, &colTemp);
		VEHICLE::SetVehicleExtraColours(GetLocalPlayer().m_vehicle, color, colTemp);
	}

	void SetVehicleWheelColor(int color) {
		int colTemp, nullCol;
		VEHICLE::GetVehicleExtraColours(GetLocalPlayer().m_vehicle, &colTemp, &nullCol);
		VEHICLE::SetVehicleExtraColours(GetLocalPlayer().m_vehicle, colTemp, color);
	}
}

void VehicleResprayMenu::Init() {
	setParentSubmenu<LSCMenu>();
	setName("Respray", true, true);

	addOption(NumberOption<float>(SCROLL, "Enveff scale")
		.addNumber(vars.fade, "%.2f", 0.02f).addMin(0).addMax(1)
		.addFunction([] {VEHICLE::SetVehicleEnveffScale(GetLocalPlayer().m_vehicle, vars.fade); })
		.addTooltip("Sets the vehicle enveff scale").addTranslation());

	addOption(BreakOption("Primary").addTranslation());

	addOption(ColorOption("Primary")
		.addColor(vars.primary)
		.addFunction([] {SetVehiclePrimaryColor(vars.primary); })
		.addTooltip("Set the primary vehicle color").addTranslation());

	addOption(ButtonOption("Chrome")
		.addFunction([] {SetVehiclePrimaryColor(120); })
		.addTooltip("Chrome").addTranslation());

	addOption(ScrollOption<int>(SCROLL, "Classic")
		.addScroll(vars.primaryclassic, 0, NUMOF(ClassicColors) - 1, ClassicColors).canLoop()
		.addFunction([] {ClearCustomVehicleColors(); SetVehiclePrimaryColor(ClassicColors[vars.primaryclassic].m_result); })
		.addTooltip("Classic").addTranslation());

	addOption(ScrollOption<int>(SCROLL, "Matte")
		.addScroll(vars.primarymatte, 0, NUMOF(MatteColors) - 1, MatteColors).canLoop()
		.addFunction([] {ClearCustomVehicleColors(); SetVehiclePrimaryColor(MatteColors[vars.primarymatte].m_result); })
		.addTooltip("Matte").addTranslation());

	addOption(ScrollOption<int>(SCROLL, "Metals")
		.addScroll(vars.primarymetals, 0, NUMOF(MetalColors) - 1, MetalColors).canLoop()
		.addFunction([] {ClearCustomVehicleColors(); SetVehiclePrimaryColor(MetalColors[vars.primarymetals].m_result); })
		.addTooltip("Metals").addTranslation());

	addOption(BreakOption("Secondary").addTranslation());

	addOption(ColorOption("Secondary")
		.addColor(vars.secondary)
		.addFunction([] {SetVehicleSecondaryColor(vars.secondary); })
		.addTooltip("Set the secondary vehicle color").addTranslation());

	addOption(ButtonOption("Chrome")
		.addFunction([] {SetVehicleSecondaryColor(120); })
		.addTooltip("Chrome").addTranslation());

	addOption(ScrollOption<int>(SCROLL, "Classic")
		.addScroll(vars.secondaryclassic, 0, NUMOF(ClassicColors) - 1, ClassicColors).canLoop()
		.addFunction([] {ClearCustomVehicleColors(); SetVehicleSecondaryColor(ClassicColors[vars.secondaryclassic].m_result); })
		.addTooltip("Classic").addTranslation());

	addOption(ScrollOption<int>(SCROLL, "Matte")
		.addScroll(vars.secondarymatte, 0, NUMOF(MatteColors) - 1, MatteColors).canLoop()
		.addFunction([] {ClearCustomVehicleColors(); SetVehicleSecondaryColor(MatteColors[vars.secondarymatte].m_result); })
		.addTooltip("Matte").addTranslation());

	addOption(ScrollOption<int>(SCROLL, "Metals")
		.addScroll(vars.secondarymetals, 0, NUMOF(MetalColors) - 1, MetalColors).canLoop()
		.addFunction([] {ClearCustomVehicleColors(); SetVehicleSecondaryColor(MetalColors[vars.secondarymetals].m_result); })
		.addTooltip("Metals").addTranslation());

	addOption(BreakOption("Pearlescent").addTranslation());

	addOption(ButtonOption("Chrome")
		.addFunction([] {SetVehiclePearlescentColor(120); })
		.addTooltip("Chrome").addTranslation());

	addOption(ScrollOption<int>(SCROLL, "Classic")
		.addScroll(vars.pearlclassic, 0, NUMOF(ClassicColors) - 1, ClassicColors).canLoop()
		.addFunction([] {SetVehiclePearlescentColor(ClassicColors[vars.pearlclassic].m_result); })
		.addTooltip("Classic").addTranslation());

	addOption(ScrollOption<int>(SCROLL, "Matte")
		.addScroll(vars.pearlmatte, 0, NUMOF(MatteColors) - 1, MatteColors).canLoop()
		.addFunction([] {SetVehiclePearlescentColor(MatteColors[vars.pearlmatte].m_result); })
		.addTooltip("Matte").addTranslation());

	addOption(ScrollOption<int>(SCROLL, "Metals")
		.addScroll(vars.pearlmetals, 0, NUMOF(MetalColors) - 1, MetalColors).canLoop()
		.addFunction([] {SetVehiclePearlescentColor(MetalColors[vars.pearlmetals].m_result); })
		.addTooltip("Metals").addTranslation());

	addOption(BreakOption("Wheels").addTranslation());

	addOption(ButtonOption("Chrome")
		.addFunction([] {SetVehicleWheelColor(120); })
		.addTooltip("Chrome").addTranslation());

	addOption(ScrollOption<int>(SCROLL, "Classic")
		.addScroll(vars.wheelclassic, 0, NUMOF(ClassicColors) - 1, ClassicColors).canLoop()
		.addFunction([] {SetVehicleWheelColor(ClassicColors[vars.wheelclassic].m_result); })
		.addTooltip("Classic").addTranslation());

	addOption(ScrollOption<int>(SCROLL, "Matte")
		.addScroll(vars.wheelmatte, 0, NUMOF(MatteColors) - 1, MatteColors).canLoop()
		.addFunction([] {SetVehicleWheelColor(MatteColors[vars.wheelmatte].m_result); })
		.addTooltip("Matte").addTranslation());

	addOption(ScrollOption<int>(SCROLL, "Metals")
		.addScroll(vars.wheelmetals, 0, NUMOF(MetalColors) - 1, MetalColors).canLoop()
		.addFunction([] {SetVehicleWheelColor(MetalColors[vars.wheelmetals].m_result); })
		.addTooltip("Metals").addTranslation());
}

/*Update once when submenu is opened*/
void VehicleResprayMenu::UpdateOnce() {}

/*Update while submenu is active*/
void VehicleResprayMenu::Update() {
	if (!GetLocalPlayer().m_isInVehicle) GetSubmenuHandler()->SetSubPrevious();
	VEHICLE::SetVehicleModKit(GetLocalPlayer().m_vehicle, 0);

	static int TIMER;
	Utils::DoTimedFunction(&TIMER, 500, [] {
		vars.fade = VEHICLE::GetVehicleEnveffScale(GetLocalPlayer().m_vehicle);
		int r, g, b;
		VEHICLE::GetVehicleCustomPrimaryColour(GetLocalPlayer().m_vehicle, &r, &g, &b);
		vars.primary = { r, g, b, 255 };
		VEHICLE::GetVehicleCustomSecondaryColour(GetLocalPlayer().m_vehicle, &r, &g, &b);
		vars.secondary = { r, g, b, 255 };
	});
}

/*Background update*/
void VehicleResprayMenu::FeatureUpdate() {}

/*Singleton*/
VehicleResprayMenu* _instance;
VehicleResprayMenu* VehicleResprayMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new VehicleResprayMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
VehicleResprayMenu::~VehicleResprayMenu() { delete _instance; }