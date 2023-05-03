#pragma once
#include "menu/submenu.h"

class WeatherManagerMenu : public Submenu {
public:
	static WeatherManagerMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	WeatherManagerMenu() : Submenu() {}
	~WeatherManagerMenu();
};

namespace WeatherManagerMenuVars {
	struct Vars {
		float rain;
		bool lightning;
		bool meteors;
		int clouds;
	};
	extern ScrollStruct<String> Weathers[14];
}