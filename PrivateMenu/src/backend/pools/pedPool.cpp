#include "stdafx.h"
#include "PedPool.h"
#include "PoolManager.h"
#include "EntityPool.h"

vector<Ped> PedPool::m_storage;
uintptr_t* PedPool::m_address;

bool PedPool::Initialize() {
	if (!Hooking::ServerPatternCallback<char>("PP", [](Hooking::CallbackData<char> data) {
		m_address = reinterpret_cast<uintptr_t*>(GetAddressFromInstruction(data.m_address));
	})) return false;

	return true;
}

void PedPool::Update() {
	vector<Ped> peds;

	const uintptr_t PedPool = *m_address;
	const uintptr_t EntityPool = *EntityPool::m_address;

	for (unsigned int i = 0; i < *reinterpret_cast<UINT32 *>(PedPool + 16); i++) {
		if (*reinterpret_cast<UINT32 *>(EntityPool + 16) - (*reinterpret_cast<UINT32 *>(EntityPool + 32) & 0x3FFFFFFF) <= 256) {
			break;
		}
		if (~(*reinterpret_cast<UINT8 *>(*reinterpret_cast<UINT64 *>(PedPool + 8) + i) >> 7) & 1) {
			const uintptr_t address = *reinterpret_cast<UINT64 *>(PedPool) + i * *reinterpret_cast<UINT32 *>(PedPool + 20);
			if (address) {
				peds.push_back(PoolManager::AddEntityToPool(address));
			}
		}
	}
	//Update Buffer
	for (Ped p : peds) {
		if (find(m_storage.begin(), m_storage.end(), p) == m_storage.end()) {
			m_storage.push_back(p);
		}
	}
	//Remove not existing elements from Buffer
	for (Ped p : m_storage) {
		if (!ENTITY::DoesEntityExist(p)) {
			m_storage.erase(remove(m_storage.begin(), m_storage.end(), p), m_storage.end());
		}
	}
}

vector<Ped> PedPool::GetPeds() {
	return m_storage;
}