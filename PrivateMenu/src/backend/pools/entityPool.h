#pragma once

class EntityPool {
public:
	static uintptr_t* m_address;
	static bool Initialize();
	static vector<Entity> GetEntities();
};