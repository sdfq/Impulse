#pragma once
#include "menu/submenu.h"

class WardrobeMenu : public Submenu {
public:
	static WardrobeMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	WardrobeMenu() : Submenu() {}
	~WardrobeMenu();
};

namespace WardrobeMenuVars
{
	struct Vars {
		int hair = 0;
		int face = 0;
		int glasses = 0;
		int ears = 0;
		int faceVar = 0;
		int glassesVar = 0;
		int earsVar = 0;
		int components[12] = { 0 };
		int componentsVar[12] = { 0 };
	};
}