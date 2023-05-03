#include "stdafx.h"
#include "VehiclePool.h"
#include "EntityPool.h"
#include "PoolManager.h"

vector<Vehicle> VehiclePool::m_storage;
uintptr_t* VehiclePool::m_address;

bool VehiclePool::Initialize() {
	if (!Hooking::ServerPatternCallback<char>("VP", [](Hooking::CallbackData<char> data) {
		m_address = reinterpret_cast<uintptr_t*>(GetAddressFromInstruction(data.m_address));
	}))return false;
	return true;
}

void VehiclePool::Update() {
	vector<Vehicle> vehicles;

	const uintptr_t VehiclePool = *m_address;
	const uintptr_t EntityPool = *EntityPool::m_address;

	const uintptr_t VehiclePoolInfo = *reinterpret_cast<UINT64 *>(VehiclePool);
	for (unsigned int i = 0; i < *reinterpret_cast<UINT32 *>(VehiclePoolInfo + 8); i++)
	{
		if (*reinterpret_cast<UINT32 *>(EntityPool + 16) - (*reinterpret_cast<UINT32 *>(EntityPool + 32) & 0x3FFFFFFF) <= 256)
		{
			break;
		}

		if ((*reinterpret_cast<UINT32 *>(*reinterpret_cast<UINT64 *>(VehiclePoolInfo + 48) + 4 * (static_cast<UINT64>(i) >> 5)) >> (i & 0x1F)) & 1)
		{
			const uintptr_t address = *reinterpret_cast<UINT64 *>(i * 8 + *reinterpret_cast<UINT64 *>(VehiclePoolInfo));

			if (address)
			{
				vehicles.push_back(PoolManager::AddEntityToPool(address));
			}
		}
	}

	//Update Buffer
	for (Vehicle v : vehicles) {
		if (find(m_storage.begin(), m_storage.end(), v) == m_storage.end()) {
			m_storage.push_back(v);
		}
	}

	//Remove not existing elements from Buffer
	for (Vehicle v : m_storage) {
		if (!ENTITY::DoesEntityExist(v)) {
			m_storage.erase(remove(m_storage.begin(), m_storage.end(), v), m_storage.end());
		}
	}
}

vector<Vehicle> VehiclePool::GetVehicles() {
	return m_storage;
}