#pragma once
#include "menu/submenu.h"

class PedManagerMenu : public Submenu {
public:
	static PedManagerMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	PedManagerMenu() : Submenu() {}
	~PedManagerMenu();
};

namespace PedManagerMenuVars {
	void RunPedManagerWorker(PoolActions task, int player = 0);
	struct Vars {
		bool usepools;
		bool esp;
	};
	extern Vars vars;
}