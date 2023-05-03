#include "stdafx.h"
#include "transaction.h"
#include "menu/submenus/main/recovery/evorecMenu.h"

NetCatalog *TransactionManager::m_netCatalog;
NetshopQueue *TransactionManager::m_shopQueue;
GameTransactionSessionMgr* TransactionManager::m_sessionMgr;

TransactionManager::queueTransactionType TransactionManager::m_queueTransaction;
TransactionManager::processTransactionType TransactionManager::m_processTransaction;

void TransactionManager::Initialize() {
	Hooking::ServerPatternCallback<char>("TRQ", [](Hooking::CallbackData<char> data) {
		m_queueTransaction = reinterpret_cast<queueTransactionType>(reinterpret_cast<uint64_t>(data.m_address));
	});

	Hooking::ServerPatternCallback<char>("TRP", [](Hooking::CallbackData<char> data) {
		m_processTransaction = reinterpret_cast<processTransactionType>(reinterpret_cast<uint64_t>(data.m_address));
	});

	Hooking::PatternCallback<void>({ "TRSM", false, 0x1F, "74 7D 66 39" }, [](void* ptr) {
		auto address = (uint64_t)ptr;
		m_sessionMgr = *reinterpret_cast<GameTransactionSessionMgr * *>(address + *reinterpret_cast<int*>(address + 3) + 7);
	});

	Hooking::ServerPatternCallback<char>("TNC", [](Hooking::CallbackData<char> data) {
		m_netCatalog = reinterpret_cast<NetCatalog *>(GetAddressFromInstruction(data.m_address));
	});
}

void TransactionManager::AddTransaction(const EvolveTransaction transaction) {
	// Doesn't work if in Initialize()
	if (!m_shopQueue) {
		Hooking::ServerPatternCallback<char>("TRNSQ", [](Hooking::CallbackData<char> data) {
			m_shopQueue = *reinterpret_cast<NetshopQueue **>(GetAddressFromInstruction(data.m_address));
		});
	}

	DWORD transactionId;
	m_queueTransaction(m_shopQueue, &transactionId, transaction.m_type, transaction.m_category, transaction.m_service, transaction.m_actionType, transaction.m_amount, transaction.m_target);
	m_processTransaction(m_shopQueue, transactionId);
}

GameTransactionSessionMgr* TransactionManager::GetSessionMgr() {
	return m_sessionMgr;
}

//bool TransactionManager::SendBackendRequest(json actionPayload, const vector<string> catalogItems, function<void(bool, json)> callback) {
//	// Get routing data (serverUrl and then the rsaccess token to start a session at the server)
//	const auto routingData = Backend::GetRoutingDataAddress();
//	if (!routingData) {
//		return false;
//	}
//
//	const auto serverUrl = reinterpret_cast<char *>(routingData);
//
//	if (static_cast<char>(routingData + 0x88) == 0) {
//		return false;
//	}
//
//	const auto rsAccess = reinterpret_cast<char *>(routingData + 0x88);
//
//	GetThreadPool()->DoJob([=] {
//		// gen the catalog json 4 the server
//		json catalogData;
//		for (auto& item : catalogItems) {
//			catalogData["items"].push_back(json::object({
//					{ "hash", static_cast<int>(Utils::GetHashKey(item.c_str())) },
//					{ "value", GetItemPrice(Utils::GetHashKey(item.c_str())) }
//				}));
//		}
//
//		json payload({
//				{ "a", actionPayload },
//				{ "c", catalogData },
//				{ "r", rsAccess },
//				{ "s", serverUrl },
//				{ "sl", 0 }
//			});
//
//		LOG_DEVENH("[ERS-Backend] Sending request with payload: %s", payload.dump().c_str());
//
//		// Encrypt + base64 it
//		const auto encryptedPayload = Utils::xorStr(payload.dump(), "sp1n3_1s_4_m0nk3y");
//		const auto encodedPayload = Encryption::base64encode2((byte *)encryptedPayload.c_str(), encryptedPayload.length());
//
//		// Send it to the server aye
//		Network network("https://auth.evolve.black/Monkey/api.php");
//		const auto response = Utils::xorStr(Encryption::base64decode(network.Post(encodedPayload, "\r\nContent-Type: application/x-www-form-urlencoded\r\n", "l1f3_suck5")), "I_g0t_fr1endz0n3d_t0n1ght_:'(");
//
//		LOG_DEVENH(response.c_str()); // the response is big so we have to use a bigger buffer for the log
//
//		// check if json is valid
//		if (!json::accept(response.c_str())) {
//			GetFiberPool()->DoJob([=] { callback(false, json({})); });
//			return;
//		}
//
//		// parse response
//		const auto responseObj = json::parse(response.c_str());
//
//		if (!responseObj["success"].get<bool>()) {
//			LOG_DEBUG(va("Fail reason: %s", Encryption::base64encode(Utils::xorStr(responseObj["data"]["reason"].get<string>(), "ev0dbg")).c_str()));
//		}
//
//		GetFiberPool()->DoJob([=] {
//			callback(true, responseObj);
//		});
//	});
//
//	return true;
//}
//
//int TransactionManager::GetItemPrice(const DWORD hash) {
//	return m_netCatalog->getServiceThreshold(hash);
//}
