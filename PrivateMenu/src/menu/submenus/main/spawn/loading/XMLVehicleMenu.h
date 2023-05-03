#pragma once
#include "menu/submenu.h"

class XMLVehicleMenu : public Submenu {
public:
	static XMLVehicleMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	XMLVehicleMenu() : Submenu() {}
	~XMLVehicleMenu();
};

namespace XMLVehicleMenuVars
{
	struct Vars {
		bool deletePreviousCreation;
		bool spawnWithCollision;
		vector<Entity> spoonerSpawnedVehicles;
		vector<Entity> spoonerSpawnedAttachments;
		vector<string> fileNames;
	};
}