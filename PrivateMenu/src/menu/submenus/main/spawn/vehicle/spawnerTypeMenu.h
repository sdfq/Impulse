#pragma once
#include "menu/submenu.h"

class SpawnerTypeMenu : public Submenu {
public:
	SpawnerTypeMenu* GetInstance();
	String* m_vehicles;
	int m_vehicleAmount;
	void Init() override;
	void Update() override;

	SpawnerTypeMenu(String name, String* vehicles, int size) : Submenu(), m_vehicles(vehicles), m_vehicleAmount(size) {
		setName(name, false, true);
		Init();
	}
};

namespace SpawnerTypeMenuVars {

}