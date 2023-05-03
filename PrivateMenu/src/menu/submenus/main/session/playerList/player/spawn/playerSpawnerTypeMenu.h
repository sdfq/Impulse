#pragma once
#include "menu/submenu.h"

class PlayerSpawnerTypeMenu : public Submenu {
public:
	PlayerSpawnerTypeMenu* GetInstance();
	String* m_vehicles;
	int m_vehicleAmount;
	void Init() override;
	void Update() override;

	PlayerSpawnerTypeMenu(String name, String* vehicles, int size) : Submenu(), m_vehicles(vehicles), m_vehicleAmount(size) {
		setName(name, false, false);
		Init();
	}
};

namespace PlayerSpawnerTypeMenuVars {

}