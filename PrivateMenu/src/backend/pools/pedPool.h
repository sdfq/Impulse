#pragma once

class PedPool {
private:
	static vector<Entity> m_storage;
public:
	static uintptr_t* m_address;

	static bool Initialize();
	static void Update();
	static vector<Ped> GetPeds();
};