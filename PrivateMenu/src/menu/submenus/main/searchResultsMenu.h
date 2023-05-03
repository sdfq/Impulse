#pragma once
#include "menu/submenu.h"

class SearchResultsMenu : public Submenu {
public:
	static SearchResultsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	SearchResultsMenu() : Submenu() {}
	~SearchResultsMenu();
};

namespace SearchResultsMenuVars
{
	
}