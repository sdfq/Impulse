#include "stdafx.h"
#include "Inventory.h"

char* Inventory::gameVersion;
bool Inventory::isBusyWithChips;

Inventory::getServerDataType Inventory::getServerData;

std::pair<const char*, const char*> Inventory::GetServerUrlAndRsToken() {
	auto data = getServerData(0);

	if (data && static_cast<char>(data + 0x88) != 0) {
		return { reinterpret_cast<char*>(data), reinterpret_cast<char*>(data + 0x88) };
	}

	LOG_DEVDEBUG("Failed to get serverurlandrstoken");

	return { nullptr, nullptr };
}

std::pair<const char*, const char*> Inventory::GetAuthHeader() {
	return { "Authorization", va("GSTOKEN token=%s", TransactionManager::GetSessionMgr()->GsToken) };
}

/*
if (!Hooking::PatternCallback<char>({ "EMAP", true, 0x0, "48 8D ? ? ? ? ? C1 EF 12 8B D0 89 85 88 00 00 00 40 80 E7 01 E8 ? ? ? ?" }, [](char* address) {
		ExplosionsData = *(sExplosion**)(*reinterpret_cast<int *>(address + 3) + address + 7);
	})) return false;
*/

void Inventory::Initialize() {
	Hooking::PatternCallback<void>({ "gave", false, 0x33, "B2 01 E8 ? ? ? ? BB" }, [](void *ptr) {
		auto address = (uint64_t)ptr;
		gameVersion = reinterpret_cast<char*>(address + *reinterpret_cast<int*>(address + 3) + 7);
	});

	Hooking::PatternCallback<void>({ "gsd", false, -0x16, "BA ? ? ? ? 48 8B D9 E8 ? ? ? ? 48 8B D0" }, [](void* address) {
		getServerData = reinterpret_cast<decltype(getServerData)>(address);
	});

	const auto base = (uint64_t)GetModuleHandleA(nullptr);

	LOG_DEVDEBUG("spcc: %llx | smhc: %llx", (uint64_t)Natives::getNativeHandlerCache(0x0772DF77852C2E30) - base, (uint64_t)Natives::getNativeHandlerCache(0xFD1D220394BCB824) - base);
	LOG_DEVDEBUG("vcw: %llx | vcb: %llx", (uint64_t)Natives::getNativeHandlerCache(0xA40F9C2623F6A8B5) - base, (uint64_t)Natives::getNativeHandlerCache(0x76EF28DA05EA395A) - base);

	LOG_DEVDEBUG("gameVersion: %s | getServerData: %llx", gameVersion, (uint64_t)getServerData); //sec, we can try sth else first
}

bool Inventory::IsConnectedToGameServer() {
	const auto data = GetServerUrlAndRsToken();

	LOG_DEVDEBUG("isconnectedtogameserver called (%llx)", (uint64_t)TransactionManager::GetSessionMgr());
	return data.first != nullptr && data.second != nullptr && TransactionManager::GetSessionMgr()->GsToken != nullptr;
}

int Inventory::GetSlot() {
	return Stats::GetStatI("mpply_last_mp_char");
}

bool Inventory::IsBusyWithChips() {
	return isBusyWithChips;
}

void Inventory::InvokeTransaction(const char* endpoint, std::vector<InventoryItem> items, std::function<void(bool)> callback, std::function<nlohmann::json(nlohmann::json)> modifier) {
	if (!IsConnectedToGameServer()) {
		return;
	}

	LOG_DEVDEBUG("it 1");

	const auto slot = GetSlot(); // call the native inside the script thread

	GetThreadPool()->DoJob([=] {
		Network network(va("https://%s/gta5/11/GamePlayServices/GameTransactions.asmx/%s", GetServerUrlAndRsToken().first, endpoint));

		LOG_DEVDEBUG("network created nigga");

		uint64_t price = 0;

		for (auto& item : items) {
			price += item.price;
		}

		LOG_DEVDEBUG("constructing payload (%llx)", TransactionManager::m_netCatalog);

		auto payload = nlohmann::json(
			{
				{ "catalogVersion", TransactionManager::m_netCatalog->CatalogVersion },
				{ "TransactionNonce",  TransactionManager::GetSessionMgr()->getTransactionNonce() },
				{ "slot", slot },
				{ "bank", price },
				{ "wallet", 0 },
				{ "GameVersion", (double)std::atof(gameVersion) }
			});

		LOG_DEVDEBUG("adding items");

		for (auto& item : items) {
			payload["items"].push_back(
				{
					{ "itemId", (int)item.itemId },
					{ "value", (int)item.value },
					{ "price", (int)item.price }
				});
		}

		LOG_DEVDEBUG("it 2");

		auto modified = modifier(payload).dump();

		LOG_DEVDEBUG("it 3");

		LOG_DEVDEBUG("sending: %s", modified.c_str());

		const auto response = network.AdvancedPost(modified, { GetAuthHeader() });

		LOG_DEVDEBUG(response.c_str());

		LOG_DEVDEBUG("it 4");

		auto success = !response.empty() && nlohmann::json::accept(response);

		const auto responseObj = nlohmann::json::parse(response);

		success = success && responseObj["Status"].get<int>() == 1;




		LOG_DEVDEBUG("it 5");

		GetFiberPool()->DoJob([=] {
			if (success && responseObj.find("playerBalance") != responseObj.end()) {
				LOG_DEVDEBUG("setting hud cash");
				Hooking::PatternCallback1<void>({ "shc", false, -0x3f, "48 3B CE 0F 84 ? ? ? ? 4C" }, [=](void*ptr) 					
				{
					reinterpret_cast<void(*)(uint64_t, uint64_t)>(ptr)(responseObj["playerBalance"]["wallets"][slot].get<uint64_t>(), responseObj["playerBalance"]["bank"].get<uint64_t>());
				});
			}

			LOG_DEVDEBUG("it 6");
			callback(success);
		});
	});
}

bool Inventory::AddCasinoChips(int chips, std::function<void(bool)> callback) {
	if (chips > 25000000) {
		chips = 25000000;
	}

	InvokeTransaction("BuyCasinoChips",
		{
			{ CASINO_CHIPS, chips, 0 },
			{ CASINO_CHIPS_UPDATE_CCUR_PAYOUT, 1, 0 }
		}, callback);

	return true;
}

bool Inventory::SellCasinoChips(int chips, bool bank, std::function<void(bool)> callback) {
	InvokeTransaction("SellCasinoChips",
		{
			{ CASINO_CHIPS, chips, 1 },
			{ (int32_t)CASINO_CHIPS_UPDATE_CCUR_SELL, 1, 0 }
		}, callback, [=](nlohmann::json payload) -> nlohmann::json {
		payload[bank ? "bank" : "wallet"] = chips;

		return payload;
	});
	return true;
}

bool Inventory::AddMoneyViaChips(int amount, bool bank, std::function<void(bool)> callback) {
	isBusyWithChips = true;

	amount--;

	int first = rand() % ((amount + 1 - 1) + 1); // stackoverflwo LUL
	int second = amount - first;
	LOG_PRINT("1");

	// these nested calls are really fucking gay but whatever
	AddCasinoChips(first, [=](bool b) {
		LOG_PRINT("2");
		if (!b) {
			ResetBusyWithChips();
			callback(false);
			return;
		}

		AddCasinoChips(second, [=](bool b1) {
			LOG_PRINT("3");
			if (!b1) {
				ResetBusyWithChips();
				callback(false);
				return;
			}

			SellCasinoChips(amount, bank, [=](bool b2) {
				LOG_PRINT("4");
				if (!b2) {
					ResetBusyWithChips();
					callback(false);
					return;
				}

				EvolveTransaction(1).service(SERVICE_EARN_BETTING).add().queue();

				ResetBusyWithChips();

				callback(true);
			});
		});
	});
	LOG_PRINT("6");
	return true;
}
