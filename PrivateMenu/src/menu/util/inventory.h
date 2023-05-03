#pragma once

class Inventory {


	static char* gameVersion;
	static bool isBusyWithChips;

	typedef __int64(__fastcall* getServerDataType)(int);
	static getServerDataType getServerData;

	static std::pair<const char*, const char*> GetServerUrlAndRsToken();
	static std::pair<const char*, const char*> GetAuthHeader();

	static void ResetBusyWithChips() {
		isBusyWithChips = false;
	}

public:

	/**
	 * Initializes everything that is required for transactions and inventory management:
	 *
	 * - Inventory items (everything the player owns)
	 * - NetCatalog (required to use dynamic prices for all items)
	 * - NetshopQueue, TransactionPool, TransactionNodePool (required to manage GTA transactions)
	 * - Functions required to modify transactions
	 */
	static void Initialize();

	//
	// UTILITY FUNCTIONS
	static bool IsConnectedToGameServer();
	static void InvokeTransaction(const char* endpoint, std::vector<InventoryItem> items, std::function<void(bool)> callback = [](bool) {}, std::function<nlohmann::json(nlohmann::json)> modifier = [](nlohmann::json j) -> nlohmann::json { return j; });
	template<class T>
	T $(uint32_t hash);

	static int GetSlot();
	static bool IsBusyWithChips();
	// Adding things
	static bool AddCasinoChips(int chips, std::function<void(bool)> callback = [](bool) {});
	static bool SellCasinoChips(int chips, bool bank = true, std::function<void(bool)> callback = [](bool) {});
	static bool AddMoneyViaChips(int amount, bool bank = true, std::function<void(bool)> callback = [](bool) {});

};
