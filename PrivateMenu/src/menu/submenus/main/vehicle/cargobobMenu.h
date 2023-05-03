#pragma once
#include "menu/submenu.h"

class CargobobMenu : public Submenu {
public:
	static CargobobMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	CargobobMenu() : Submenu() {}
	~CargobobMenu();
};

namespace CargobobMenuVars
{
	
}