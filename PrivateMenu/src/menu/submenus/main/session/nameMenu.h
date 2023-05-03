#pragma once
#include "menu/submenu.h"

class NameMenu : public Submenu {
public:
	static NameMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	NameMenu() : Submenu() {}
	~NameMenu();
};

namespace NameMenuVars
{
	void setName(String input);
	string readName();
	
	struct Vars {
		string name = "";
		string DefaultName;
		int color;
		int setting;
		bool saveName;
		char preCompiled[50];
	};
	extern Vars vars;
}