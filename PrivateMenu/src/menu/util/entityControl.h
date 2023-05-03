#pragma once

struct EntityControlStruct
{
	String m_name;
	Entity m_entity;
	function<void(Entity)> m_function;
	int m_networkID;
	int m_tries;
	int64_t m_id;
	bool m_valid;

	inline bool operator==(const EntityControlStruct& str2) {
		return m_id == str2.m_id;
	}
};

struct EntityModelStruct {
	int m_model;
	function<void(int)> m_function;
	int m_tries;
	int64_t m_id;

	inline bool operator==(const EntityModelStruct& str2) {
		return m_id == str2.m_id;
	}
};

class EntityControl
{
private:
	queue<EntityControlStruct> m_requests;
	vector<EntityModelStruct> m_models;
public:
	static void _Update();
	void Update();

	void RequestControl(String name, Entity entity, function<void(Entity)> funcptr);
	void SimpleRequestControl(Entity entity);
	void VerySimpleRequestControl(Entity entity);
	void RequestModel(int model, function<void(int)> funcptr);
	void SimpleRequestModel(int model);
	void DeleteEntity(Entity entity);
	void SimpleDeleteEntity(Entity entity);
	void DeleteVehicle(Vehicle vehicle);
	void SimpleDeleteVehicle(Vehicle vehicle);
};

EntityControl* GetEntityControl();