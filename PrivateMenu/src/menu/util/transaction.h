#pragma once

struct EvolveTransaction;

class GameTransactionSessionMgr {
public:
	char pad_0000[160]; //0x0000
	void* inventoryItems; //0x00A0
	char pad_00A8[24]; //0x00A8
	char GsToken[36]; //0x00C0
	char pad_00E4[28]; //0x00E4
	uint32_t TransactionNonceSeed; //0x0100
	char pad_0104[44]; //0x0104
	uint32_t TransactionCount; //0x0130
	char pad_0134[396]; //0x0134
	char* BalanceData; //0x02C0

	uint32_t getTransactionNonce() {
		return TransactionNonceSeed + TransactionCount;
	}
}; //Size: 0x02C8

class TransactionManager {

	static NetshopQueue *m_shopQueue;

public:

	typedef bool(__fastcall *queueTransactionType)(NetshopQueue *queue, DWORD *transactionId, TransactionType type, TransactionCategory category, TransactionService service, TransactionActionType actionType, int amount, TransactionTarget target);
	typedef bool(__fastcall *processTransactionType)(NetshopQueue *queue, DWORD transactionId);

	static queueTransactionType m_queueTransaction;
	static NetCatalog *m_netCatalog;

	static void Initialize();
	static void AddTransaction(EvolveTransaction transaction);

	static GameTransactionSessionMgr* GetSessionMgr();
	/**
	 * The requests will be done via threadPool and the callback will be called from the script thread via fiberPool
	 */
	//static bool SendBackendRequest(json actionPayload, vector<string> catalogItems, function<void(bool, json)> callback);
	//static int GetItemPrice(DWORD hash);

private:

	static processTransactionType m_processTransaction;
	static GameTransactionSessionMgr* m_sessionMgr;

};

// Goal is to replace these with the original CNetShopTransaction classes and add them directly to the pool / queue
struct EvolveTransaction {

	TransactionType m_type;
	TransactionActionType m_actionType;
	TransactionCategory m_category;
	TransactionService m_service;
	TransactionTarget m_target;

	uint32_t m_amount;

	// this one just adds money using earn_rockstar (10mil cap)
	explicit EvolveTransaction(const uint32_t amount) :
		m_type(TYPE_DEFAULT), m_actionType(ACTION_TYPE_SERVICE_EARN), m_category(CATEGORY_SERVICE_WITH_THRESHOLD), m_service(SERVICE_EARN_ROCKSTAR), m_target(TARGET_BANK), m_amount(amount)
	{}

	EvolveTransaction(const TransactionService service, const TransactionTarget target, const uint32_t amount) :
		m_type(TYPE_DEFAULT), m_actionType(ACTION_TYPE_SERVICE_EARN), m_category(CATEGORY_SERVICE_WITH_THRESHOLD), m_service(service), m_target(target), m_amount(amount)
	{}

	EvolveTransaction(const TransactionActionType actionType, const TransactionService service, const TransactionTarget target, const uint32_t amount) :
		m_type(TYPE_DEFAULT), m_actionType(actionType), m_category(CATEGORY_SERVICE_WITH_THRESHOLD), m_service(service), m_target(target), m_amount(amount)
	{}

	EvolveTransaction(const TransactionType type, const TransactionActionType actionType, const TransactionCategory category, const TransactionService service, const TransactionTarget target, const uint32_t amount) :
		m_type(type), m_actionType(actionType), m_category(category), m_service(service), m_target(target), m_amount(amount)
	{}

	EvolveTransaction add() {
		m_service = SERVICE_EARN_ROCKSTAR;
		m_actionType = ACTION_TYPE_SERVICE_EARN;
		return *this;
	}

	EvolveTransaction remove() {
		m_service = SERVICE_SPEND_PROSTITUTES;
		m_actionType = ACTION_TYPE_SERVICE_SPEND;
		return *this;
	}

	EvolveTransaction service(const TransactionService service) {
		m_service = service;
		return *this;
	}

	EvolveTransaction target(const TransactionTarget target) {
		m_target = target;
		return *this;
	}

	EvolveTransaction amount(const uint32_t amount) {
		m_amount = amount;
		return *this;
	}

	void queue() const {
		TransactionManager::AddTransaction(*this);
	}

};
