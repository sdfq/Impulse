#pragma once
#include "menu/submenu.h"

class WorldDrawablesMenu : public Submenu {
public:
	static WorldDrawablesMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	WorldDrawablesMenu() : Submenu() {}
	~WorldDrawablesMenu();
};

namespace WorldDrawablesVars
{
	enum eTasks {
		TeleportAllToMe,
		ESP,
		CalculateClosest,
		x5Scale,
		normalScale,
	};

	struct Vars {
		bool esp;
		vector<uint64_t> entityClasses;
		uint64_t* entityPoolPointer;
		CDrawable* closestDrawable;
		uint64_t closestDrawableAddress;
	};

	extern Vars vars;

	void RunTaskOnAll(eTasks task);
}