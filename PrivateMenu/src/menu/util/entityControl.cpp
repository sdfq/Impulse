#include "stdafx.h"

EntityControl g_entityControl;

void EntityControl::Update() {
	PROFILER();
	if (m_requests.size() > 0) {
		EntityControlStruct& request = m_requests.front();
		bool exists = ENTITY::DoesEntityExist(request.m_entity);
		if (!request.m_valid) m_requests.pop();
		if (exists && (NETWORK::NetworkHasControlOfEntity(request.m_entity) || request.m_tries > 25)) {
			if (request.m_tries < 25) {
				LOG_CUSTOM(ConsoleForeground::DARKBLUE, "[Control] %s Received control of entity %d after %d tries", request.m_name, request.m_entity, request.m_tries);
				request.m_function(request.m_entity);
				request.m_valid = false;
			} else LOG_CUSTOM(ConsoleForeground::DARKBLUE, "[Control] %s Failed to get control of entity %d", request.m_name, request.m_entity);
			m_requests.pop();
		} else if (exists) {
			request.m_tries++;
			NETWORK::NetworkRequestControlOfEntity(request.m_entity);
			if (request.m_networkID != 0) {
				NETWORK::NetworkRequestControlOfNetworkId(request.m_networkID);
				NETWORK::SetNetworkIdCanMigrate(request.m_networkID, 1);
			}
		} else {
			request.m_valid = false;
			LOG_CUSTOM(ConsoleForeground::DARKBLUE, "[Control] %s Entity %d no longer exists", request.m_name, request.m_entity);
			m_requests.pop();
		}
	}
	for (EntityModelStruct& model : m_models) {
		if (STREAMING::HasModelLoaded(model.m_model) || model.m_tries > 25) {
			if (model.m_tries < 25) {
				LOG_CUSTOM(ConsoleForeground::DARKBLUE, "[Control] Successfully streamed model %d after %d tries", model.m_model, model.m_tries);
				model.m_function(model.m_model);
				STREAMING::SetModelAsNoLongerNeeded(model.m_model);
			} else LOG_CUSTOM(ConsoleForeground::DARKBLUE, "[Control] Failed to stream model %d", model.m_model);
			m_models.erase(remove(m_models.begin(), m_models.end(), model), m_models.end());
		} else {
			model.m_tries++;
			STREAMING::RequestModel(model.m_model);
		}
	}
}

void EntityControl::RequestControl(String name, Entity entity, function<void(Entity)> funcptr) {
	static int64_t c_ID;
	int networkID = NETWORK::NetworkIsSessionStarted() ? NETWORK::NetworkGetNetworkIdFromEntity(entity) : 0;
	m_requests.push({ name, entity, funcptr, networkID, 0, c_ID++, true });
}

void EntityControl::SimpleRequestControl(Entity entity) {
	int tries = 0;
	bool exists = ENTITY::DoesEntityExist(entity);
	while (exists && !NETWORK::NetworkHasControlOfEntity(entity) && tries < 25) {
		NETWORK::NetworkRequestControlOfEntity(entity);
		if (NETWORK::NetworkIsSessionStarted()) {
			NETWORK::NetworkRequestControlOfNetworkId(NETWORK::NetworkGetNetworkIdFromEntity(entity));
			NETWORK::SetNetworkIdCanMigrate(NETWORK::NetworkGetNetworkIdFromEntity(entity), 1);
		}
		GetFiberManager()->GoToMainFiber();
		tries++;
	}
}

void EntityControl::VerySimpleRequestControl(Entity entity) {
	NETWORK::NetworkRequestControlOfEntity(entity);
	if (NETWORK::NetworkIsSessionStarted()) {
		NETWORK::NetworkRequestControlOfNetworkId(NETWORK::NetworkGetNetworkIdFromEntity(entity));
		NETWORK::SetNetworkIdCanMigrate(NETWORK::NetworkGetNetworkIdFromEntity(entity), 1);
	}
}

void EntityControl::RequestModel(int model, function<void(int)> funcptr) {
	static int64_t c_ID;
	m_models.push_back({ model, funcptr, 0, c_ID++ });
}

void EntityControl::SimpleRequestModel(int model) {
	int tries = 0;
	while (!STREAMING::HasModelLoaded(model) && tries < 25) {
		STREAMING::RequestModel(model);
		tries++;
		GetFiberManager()->GoToMainFiber();
	}
}

void EntityControl::DeleteEntity(Entity entity) {
	RequestControl("[DE]", entity, [](Entity entity) {
		ENTITY::DetachEntity(entity, true, true);
		ENTITY::SetEntityAsMissionEntity(entity, 1, 1);
		ENTITY::DeleteEntity(&entity);
	});
}
void EntityControl::SimpleDeleteEntity(Entity entity) {
	SimpleRequestControl(entity);
	ENTITY::DetachEntity(entity, true, true);
	ENTITY::SetEntityAsMissionEntity(entity, 1, 1);
	ENTITY::DeleteEntity(&entity);
}

void EntityControl::DeleteVehicle(Vehicle vehicle) {
	RequestControl("[DV]", vehicle, [](Entity entity) {
		ENTITY::DetachEntity(entity, true, true);
		ENTITY::SetEntityAsMissionEntity(entity, 1, 1);
		VEHICLE::DeleteVehicle(&entity);
	});
}

void EntityControl::SimpleDeleteVehicle(Vehicle vehicle) {
	SimpleRequestControl(vehicle);
	ENTITY::DetachEntity(vehicle, true, true);
	ENTITY::SetEntityAsMissionEntity(vehicle, 1, 1);
	VEHICLE::DeleteVehicle(&vehicle);
}

void EntityControl::_Update() { GetEntityControl()->Update(); }

EntityControl* GetEntityControl() { return &g_entityControl; }