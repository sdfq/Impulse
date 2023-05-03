#pragma once
#include "menu/submenu.h"

class TrafficManagerMenu : public Submenu {
public:
	static TrafficManagerMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	TrafficManagerMenu() : Submenu() {}
	~TrafficManagerMenu();
};

namespace TrafficManagerMenuVars {
	void RunTrafficManagerWorker(PoolActions task, int player = 0);
	struct Vars {
		bool usepools;
		bool esp;
		bool chaos;
	};
	extern Vars vars;
}