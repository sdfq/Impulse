#pragma once
#include "menu/submenu.h"

class ThemeMenu : public Submenu {
public:
	static ThemeMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	ThemeMenu() : Submenu() {}
	~ThemeMenu();
};

namespace ThemeMenuVars {
	void SetHeader(int header);
	struct Vars {
		int font;
		int header;
		bool rainbow;
		bool rainbow1;
		bool rainbow2;
		bool rainbow3;
	};
}