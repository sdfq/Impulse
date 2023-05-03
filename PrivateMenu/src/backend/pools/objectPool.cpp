#include "stdafx.h"
#include "ObjectPool.h"
#include "EntityPool.h"
#include "PoolManager.h"

vector<Object> ObjectPool::m_storage;
uintptr_t* ObjectPool::m_address;

bool ObjectPool::Initialize() {
	if (!Hooking::ServerPatternCallback<char>("OP", [](Hooking::CallbackData<char> data) {
		m_address = reinterpret_cast<uintptr_t*>(GetAddressFromInstruction(data.m_address));
	}))return false;

	return true;
}

void ObjectPool::Update() {
	vector<Object> objects;

	const uintptr_t ObjectPool = *m_address;
	const uintptr_t EntityPool = *EntityPool::m_address;

	for (unsigned int i = 0; i < *reinterpret_cast<UINT32 *>(ObjectPool + 16); i++)
	{
		if (*reinterpret_cast<UINT32 *>(EntityPool + 16) - (*reinterpret_cast<UINT32 *>(EntityPool + 32) & 0x3FFFFFFF) <= 256)
		{
			break;
		}

		if (~(*reinterpret_cast<UINT8 *>(*reinterpret_cast<UINT64 *>(ObjectPool + 8) + i) >> 7) & 1)
		{
			const uintptr_t address = *reinterpret_cast<UINT64 *>(ObjectPool) + i * *reinterpret_cast<UINT32 *>(ObjectPool + 20);

			if (address)
			{
				objects.push_back(PoolManager::AddEntityToPool(address));
			}
		}
	}

	//Update Buffer
	for (Object o : objects) {
		if (find(m_storage.begin(), m_storage.end(), o) == m_storage.end()) {
			m_storage.push_back(o);
		}
	}

	//Remove not existing elements from Buffer
	for (Object o : m_storage) {
		if (!ENTITY::DoesEntityExist(o)) {
			m_storage.erase(remove(m_storage.begin(), m_storage.end(), o), m_storage.end());
		}
	}
}

vector<Object> ObjectPool::GetObjects() {
	return m_storage;
}