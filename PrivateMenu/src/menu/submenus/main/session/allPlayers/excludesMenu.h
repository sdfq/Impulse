#pragma once
#include "menu/submenu.h"

class ExcludesMenu : public Submenu {
public:
	static ExcludesMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	ExcludesMenu() : Submenu() {}
	~ExcludesMenu();
};

namespace ExcludesMenuVars
{
	bool IsExcluded(SPlayer& p);

	struct Vars {
		bool friends;
		bool team;
		bool modders;
		bool host;
		bool self = true;
		bool evolve;
	};

	extern Vars vars;
}