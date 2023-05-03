#include "stdafx.h"
#include "EntityPool.h"
#include "PedPool.h"
#include "ObjectPool.h"
#include "VehiclePool.h"

uintptr_t* EntityPool::m_address;

bool EntityPool::Initialize() {
	if (!Hooking::ServerPatternCallback<char>("EP", [](Hooking::CallbackData<char> data) {
		m_address = reinterpret_cast<uintptr_t*>(GetAddressFromInstruction(data.m_address));
	}))return false;
	return true;
}

vector<Entity> EntityPool::GetEntities() {
	vector<Entity> entities;

	for (Ped p : PedPool::GetPeds()) {
		entities.push_back(p);
	}
	for (Vehicle v : VehiclePool::GetVehicles()) {
		entities.push_back(v);
	}
	for (Object o : ObjectPool::GetObjects()) {
		entities.push_back(o);
	}

	return entities;
}