#pragma once
#include "menu/submenu.h"

class SessionSpawnerTypeMenu : public Submenu {
public:
	SessionSpawnerTypeMenu* GetInstance();
	String* m_vehicles;
	int m_vehicleAmount;
	void Init() override;
	void Update() override;

	SessionSpawnerTypeMenu(String name, String* vehicles, int size) : Submenu(), m_vehicles(vehicles), m_vehicleAmount(size) {
		setName(name, false, false);
		Init();
	}
};

namespace SessionSpawnerTypeMenuVars
{
	
}