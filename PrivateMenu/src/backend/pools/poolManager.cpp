#include "stdafx.h"
#include "PoolManager.h"
#include "EntityPool.h"
#include "PedPool.h"
#include "ObjectPool.h"
#include "VehiclePool.h"

int(*PoolManager::AddEntityToPool)(UINT64 address);
UINT64(*PoolManager::GetEntityAddress)(Entity handle);

bool PoolManager::Initialize() {
	if (!Hooking::ServerPatternCallback<char>("AETP", [](Hooking::CallbackData<char> data) {
		AddEntityToPool = reinterpret_cast<int(*)(UINT64)>(data.m_address - 0x68);
	})) return false;

	if (!Hooking::ServerPatternCallback<char>("GEA", [](Hooking::CallbackData<char> data) {
		GetEntityAddress = reinterpret_cast<UINT64(*)(int)>(*reinterpret_cast<int *>(data.m_address + 1) + data.m_address + 5);
	})) return false;

	if (!EntityPool::Initialize())return false;
	if (!PedPool::Initialize())return false;
	if (!VehiclePool::Initialize())return false;
	if (!ObjectPool::Initialize())return false;
	return true;
}

void PoolManager::Update() {
	PedPool::Update();
	VehiclePool::Update();
	ObjectPool::Update();
}