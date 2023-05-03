#pragma once

class PoolManager {
public:
	static int(*AddEntityToPool)(UINT64 address);
	static UINT64(*GetEntityAddress)(Entity handle);
	static bool Initialize();
	static void Update();
};