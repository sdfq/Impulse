#include "stdafx.h"
#include "socialclub.h"

__int64 Socialclub::m_ticketAddress;

void Socialclub::Initialize() {
	Hooking::ServerPatternCallback<void>("SCT", [](Hooking::CallbackData<void> data) {
		auto address = (uint64_t)data.m_address;
		m_ticketAddress = static_cast<__int64>(address + *reinterpret_cast<int*>(address + 3) + 7);
	});
}

std::vector<std::pair<std::string, std::string>> Socialclub::GetRequiredHeaders() {
	return {
			{ "User-Agent", Utils::RandomString(16) },
			{ new char[17] {'X', '-', 'R', 'e', 'q', 'u', 'e', 's', 't', 'e', 'd', '-', 'W', 'i', 't', 'h', 0 }, new char[15] {'X', 'M', 'L', 'H', 't', 't', 'p', 'R', 'e', 'q', 'u', 'e', 's', 't', 0 } }, // CSRF check
			{ "Authorization", va(new char[16] {'S', 'C', 'A', 'U', 'T', 'H', ' ', 'v', 'a', 'l', '=', '"', '%', 's', '"', 0 }, GetTicket()) }, // auth format for socialclub overlay requests
	};
}

static uint64_t cooldown = 0;

void Socialclub::GetProfile(const int32_t rockstarId, std::function<void(bool, SocialclubData::RockstarAccount)> callback) {
	GetThreadPool()->DoJob([=] {
		if (GetTickCount64() - cooldown < 4000) {
			LOG_DEVPRINT("cooldown active...");
			Sleep(4000 - abs((long long)(GetTickCount64() - cooldown)));
			cooldown = GetTickCount64();
		}

		Network network(new char[65] {'h', 't', 't', 'p', 's', ':', '/', '/', 'p', 'r', 'o', 'd', '.', 'r', 'o', 's', '.', 'r', 'o', 'c', 'k', 's', 't', 'a', 'r', 'g', 'a', 'm', 'e', 's', '.', 'c', 'o', 'm', '/', 's', 'c', 'u', 'i', '/', 'v', '2', '/', 'a', 'p', 'i', '/', 'f', 'r', 'i', 'e', 'n', 'd', '/', 'g', 'e', 't', 'p', 'r', 'o', 'f', 'i', 'l', 'e', 0 });  // will do one more thing.. sec

		const auto response = network.AdvancedPost(nlohmann::json(
			{
				{ "RockstarId", rockstarId }
			}).dump(), GetRequiredHeaders(), "application/json; charset=utf-8");

		//LOG_DEVPRINT("response for %d (%d):", rockstarId, response.size()); // help
		//GetLog()->LogToFile(response.c_str());

		if (!nlohmann::json::accept(response)) {
			GetFiberPool()->DoJob([=] { callback(false, {}); });
			return;
		}

		try {
			auto json = nlohmann::json::parse(response);

			if (!json["Status"].get<bool>()) {
				// "Failed to read profile of %d (%s)", rockstarId, json["Error"]["Code"].get<std::string>().c_str()
				GetFiberPool()->DoJob([=] { callback(false, {}); });
				return;
			}

			if (json["Accounts"].get<json::array_t>().size() == 0) {
				GetFiberPool()->DoJob([=] { callback(false, {}); });
				return;
			}

			json = json["Accounts"][0]["RockstarAccount"];

			auto profile = SocialclubData::RockstarAccount(
				rockstarId,
				SafeRead<std::string>(json, "Name"),
				SafeRead<std::string>(json, "DisplayName"),
				SafeRead<std::string>(json, "Email"),
				SafeRead<std::string>(json, "CountryCode"),
				json["MutualFriendCount"].get<uint32_t>(),
				json["ProfileHidden"].get<bool>(),
				json["FriendsHidden"].get<bool>(),
				json["FriendCount"].get<uint32_t>(),
				SafeRead<uint8_t>(json, "LastUgcPlatform"),
				SafeRead<uint8_t>(json, "LastUgcTitle"),
				SafeRead<uint8_t>(json, "LastOnlineService"),
				json["WallHidden"].get<bool>(),
				json["AllowWallPost"].get<bool>(),
				json["AllowStatCompare"].get<bool>(),
				SafeRead<std::string>(json, "InviteMessage"),
				json["AllowBlock"].get<bool>(),
				json["AllowReport"].get<bool>(),
				SafeRead<std::string>(json, "Status"),
				json["Background"].get<int32_t>(),
				json["IsGamertagHidden"].get<bool>(),
				SafeRead<std::string>(json, "Gamertag"),
				SafeRead<uint32_t>(json, "UserId"),
				SafeRead<std::string>(json, "LanguageCode"),
				SafeRead<std::string>(json, "CreatedDate"),
				SafeRead<std::string>(json, "CreatedDateStr"),
				json["IsOnline"].get<bool>());

			GetFiberPool()->DoJob([=] { callback(true, profile); });
		} catch (nlohmann::json::exception e) {
			// "Failed to parse profile for %d (%s)", rockstarId, e.what()
			GetFiberPool()->DoJob([=] { callback(false, {}); });
		}
	});
}

void Socialclub::SearchAccount(const char* name, std::function<void(bool, SocialclubData::SearchResult)> callback, uint16_t pageIndex) {
	GetThreadPool()->DoJob([=] {
		Network network(new char[68] {'h', 't', 't', 'p', 's', ':', '/', '/', 'p', 'r', 'o', 'd', '.', 'r', 'o', 's', '.', 'r', 'o', 'c', 'k', 's', 't', 'a', 'r', 'g', 'a', 'm', 'e', 's', '.', 'c', 'o', 'm', '/', 's', 'c', 'u', 'i', '/', 'v', '2', '/', 'a', 'p', 'i', '/', 'f', 'r', 'i', 'e', 'n', 'd', '/', 'a', 'c', 'c', 'o', 'u', 'n', 't', 's', 'e', 'a', 'r', 'c', 'h', 0 });

		const auto response = network.AdvancedPost(nlohmann::json(
			{
				{ "env", "prod" },
				{ "title", "gta5" },
				{ "version", 11 },
				{ "searchNickname", name },
				{ "pageIndex", pageIndex }
			}).dump(), GetRequiredHeaders(), "application/json; charset=utf-8");

		if (!nlohmann::json::accept(response)) {
			GetFiberPool()->DoJob([=] { callback(false, {}); });
			return;
		}

		try {
			auto json = nlohmann::json::parse(response);

			if (!json["Status"].get<bool>()) {
				GetFiberPool()->DoJob([=] { callback(false, {}); });
				return;
			}

			auto accounts = json["Accounts"].get<nlohmann::json::array_t>();
			auto accountList = std::vector<SocialclubData::BasicAccount>();

			for (auto i = 0; i < accounts.size(); i++) {
				auto account = accounts.at(i).get<nlohmann::json::object_t>();

				accountList.emplace_back(
					SafeRead<uint32_t>(account, "RockstarId"),
					SafeRead<std::string>(account, "Nickname"),
					SafeRead<std::string>(account, "Service"),
					SafeRead<std::string>(account, "ServiceNickname"),
					SafeRead<std::string>(account, "Relationship"));
			}

			SocialclubData::SearchResult result(
				json["Total"].get<uint32_t>(),
				json["NextOffset"].get<uint32_t>(),
				json["HasMore"].get<bool>(),
				json["BlockedCount"].get<uint32_t>(),
				accountList);

			GetFiberPool()->DoJob([=] { callback(true, result); });
		} catch (nlohmann::json::exception e) {
			GetFiberPool()->DoJob([=] { callback(false, {}); });
		}
	});
}

void Socialclub::GetRockstarIdByName(const char* name, std::function<void(uint32_t)> callback) {
	SearchAccount(name, [=](bool success, SocialclubData::SearchResult result) {
		if (!success) {
			callback(0); // failed to search
			return;
		}

		if (result.getTotal() == 0) {
			callback(0); // not found
			return;
		}

		for (auto& account : result.getAccounts()) {
			if (!strcmp(account.getNickname(), name)) {
				//LOG_DEBUG("Found ID for %s: %d", name, account.getRockstarId());
				callback(account.getRockstarId());
				return;
			}
		}

		callback(0); // not found
	});
}

const char* Socialclub::GetTicket() {
	return reinterpret_cast<const char*>(m_ticketAddress);
}