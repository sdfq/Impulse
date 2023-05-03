#include "stdafx.h"
#include "searchResultsMenu.h"
#include "../mainMenu.h"

using namespace SearchResultsMenuVars;

namespace SearchResultsMenuVars {
}

void SearchResultsMenu::Init() {
	setParentSubmenu<MainMenu>();
	setName("Search results", true, false);
}

/*Update once when submenu is opened*/
void SearchResultsMenu::UpdateOnce() {}

/*Update while submenu is active*/
void SearchResultsMenu::Update() {}

/*Background update*/
void SearchResultsMenu::FeatureUpdate() {}

/*Singleton*/
SearchResultsMenu* _instance;
SearchResultsMenu* SearchResultsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new SearchResultsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
SearchResultsMenu::~SearchResultsMenu() { delete _instance; }