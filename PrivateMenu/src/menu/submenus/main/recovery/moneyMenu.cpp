#include "stdafx.h"
#include "moneyMenu.h"
#include "../recoveryMenu.h"

using namespace MoneyMenuVars;

namespace MoneyMenuVars {

	struct Vars vars;

	ScrollStruct<TransactionTarget> RemoveTarget[] = {
		TranslationString("Bank", true), TARGET_BANK,
		TranslationString("Cash", true), TARGET_CASH,
		TranslationString("Cash Then Bank", true), TARGET_CASH_THEN_BANK
	};


	static bool justStealth = false;
	static int stealthTimer;

	bool isLooping = false;
	int toAdd = 0;

	int previousTimer = 0;
	int lastAmount = 0;

	void doStealth(const int amount) {
		//TransactionManager::AddTransaction(EvolveTransaction(amount));
		Global(4264014 + 1).As<int>() = 2147483646;
		Global(4264014 + 7).As<int>() = 2147483647;
		Global(4264014 + 6).As<int>() = 0;
		Global(4264014 + 5).As<int>() = 0;
		Global(4264014 + 3).As<int>() = SERVICE_EARN_PROPERTY_SALES;  //312105838;  // For 15m -1586170317		10m 393059668 nah this one doesnt work they patched it
		Global(4264014 + 2).As<int>() = amount;
		//Global(0x41092C + 80).At(80).As<int>() = 4; // does not work
		Global(4264014).As<int>() = 1; // g has gay - wtf nigga oh when vrah first joined he gave me this as your method was detected lol alphahad it first smh
	}

	void removeStealth(const int amount) {
		//TransactionManager::AddTransaction(EvolveTransaction(amount));
		Global(4264014 + 1).As<int>() = 2147483646;
		Global(4264014 + 7).As<int>() = 2147483647;
		Global(4264014 + 6).As<int>() = 0;
		Global(4264014 + 5).As<int>() = 0;
		Global(4264014 + 3).As<int>() = -899802304;  // For 15m -1586170317		10m 393059668
		Global(4264014 + 2).As<int>() = amount;
		//Global(0x41092C + 80).At(80).As<int>() = 4; // does not work
		Global(4264014).As<int>() = 1; // g has gay
	}

	/* Jodels Version from Unity
	Global(4264014).As<int>() = 1;
		Global(4264014).At(0, 7).As<int>() = 2;
		Global(4264014).At(0, 7).At(1).As<int>() = 10000000;
		Global(4264014).At(0, 7).At(2).As<int>() = 312105838;
		Global(4264014).At(0, 7).At(4).As<int>() = 0;
		Global(4264014).At(0, 7).At(5).As<int>() = 0;
		Global(4264014).At(0, 7).At(6).As<int>() = 2147483647;
	*/

	void resetStealth() {}

	void stealthToWallet(int amount) {
		if (isLooping) return;
		lastAmount = amount;
		if (amount == 0) return;
		isLooping = true;
		toAdd = amount;
	}

	void updateStealth() {
		static int TIMER;
		if (!isLooping) return;
		if (toAdd == 0) {
			resetStealth();
			isLooping = false;
		}
		Utils::DoTimedFunction(&TIMER, 1000, [] {
			if (toAdd > 0) {
				if (toAdd > 10000000) {
					doStealth(10000000);
					toAdd -= 10000000;
				} else {
					doStealth(toAdd);
					toAdd = 0;
				}
			}
		});
	}

	void deposit(long amount) {
		int iVar0;
		STATS::StatGetInt(Utils::GetHashKey("mpply_last_mp_char"), &iVar0, -1);
		NETSHOP::_NetworkTransferWalletToBank(iVar0, amount);
	}

	void withdraw(long amount) {
		int iVar0;
		STATS::StatGetInt(Utils::GetHashKey("mpply_last_mp_char"), &iVar0, -1);
		NETSHOP::_NetworkTransferBankToWallet(iVar0, amount);
	}
}

void MoneyMenu::Init() {
	setParentSubmenu<RecoveryMenu>();
	setName("Money", true, true);

	/*
	addOption(ButtonOption("Adding...")
		.addOnUpdate([](ButtonOption* option) {
		static int TIMER, offset;
		static char name[50];
		Utils::DoTimedFunction(&TIMER, 250, [] { offset = offset > 2 ? 0 : offset + 1; });
		vaBuff(name, 50, "~c~Adding %d%s", toAdd, offset < 2 ? offset < 1 ? "." : ".." : "...");
		option->setName(name);
	})
		.addRequirement([] {return isLooping && toAdd > 0; })
		.addTooltip("The menu is adding money to your account!"));

	addOption(NumberOption<int>(SCROLL, "Amount")
		.addNumber(vars.stealthamount, "%d", 10000).addMin(0).addMax(500000000)
		.addHotkey().canBeSaved().addTranslation()
		.addRequirement([] {return !isLooping && toAdd < 10000000; })
		.addTooltip("Stealth money amount"));

	addOption(ButtonOption("Give money")
		.addFunction([] {
		if (vars.stealthamount <= 10000000) doStealth(10000000);
		else doStealth(vars.stealthamount);
	})
		.addHotkey().addTranslation()
		.addRequirement([] {return !isLooping && toAdd < 10000000; })
		.addTooltip("Add money to your account"));

	addOption(ToggleOption("Loop give money")
		.addToggle(vars.loop)
		.addFunction([] {if (!vars.loop) resetStealth(); })
		.addHotkey().addTranslation()
		.addTooltip("Add money to your account"));*/

	addOption(ButtonOption("")
		.addOnUpdate([](ButtonOption* option) {
		static int TIMER, offset;
		static char name[50];
		vaBuff(name, 50, "Current bank balance: ~g~$~s~%llu", NETCASH::NetworkGetVcBankBalance());
		option->setName(name);
	})
		.addTooltip("This displays your current bank balance"));

	addOption(ButtonOption("")
		.addOnUpdate([](ButtonOption* option) {
		static int TIMER, offset;
		static char name[50];
		vaBuff(name, 50, "Current wallet balance: ~g~$~s~%llu", NETCASH::NetworkGetVcWalletBalance(-1));
		option->setName(name);
	})
		.addTooltip("This displays your current wallet balance"));

	// Add
	addOption(BreakOption("Add").addTranslation());

	//addOption(NumberOption<int>(SCROLLSELECT, "Give Money")
	//	.addNumber(vars.addAmount, "%d", 100000).addMin(0).addMax(600000) //10000000
	//	.addFunction([] {
	//	Global(4264014 + 1).As<int>() = 2147483646;
	//	Global(4264014 + 7).As<int>() = 2147483647;
	//	Global(4264014 + 6).As<int>() = 0;
	//	Global(4264014 + 5).As<int>() = 0;
	//	Global(4264014 + 3).As<int>() = SERVICE_EARN_PROPERTY_SALES;  //312105838;  // For 15m -1586170317		10m 393059668 ////408A6C26    D7858229 --SERVICE_EARN_PROPERTY_SALES
	//	Global(4264014 + 2).As<int>() = vars.addAmount;
	//	//Global(0x41092C + 80).At(80).As<int>() = 4; // does not work
	//	Global(4264014).As<int>() = 1; // g has gay
	//}).addHotkey().canBeSaved().addTranslation().addTooltip("Gives you money."));
	SERVICE_EARN_PROPERTY_SALES
	/*G money method using only 600k*/
	addOption(NumberOption<int>(SCROLLSELECT, "Give money")
		.addRequirement([] { return !Inventory::IsBusyWithChips(); })
		.addNumber(vars.addAmount, "%d", 100000).addMin(0).addMax(1000000) //10000000
		.addFunction([] {
		Inventory::AddMoneyViaChips(vars.addAmount);
		//GetRenderer()->NotifyBottom("~g~Leave GTA Online and go back to singleplayer, then rejoin online to see your new money balance");
	}).addHotkey().canBeSaved().addTranslation().addTooltip("Gives money."));

	addOption(ButtonOption("~c~Give money~s~")
		.addRequirement([] { return Inventory::IsBusyWithChips(); })
		.addTooltip("Adding....")
	);

	addOption(ToggleOption("Loop give money")
		.addToggle(vars.loop)
		.addFunction([] { GetRenderer()->NotifyBottom("~g~Once desired money has been added go back to singleplayer, then rejoin online to update balance");; })
		.addHotkey().addTranslation()
		.addTooltip("Loop money. (Once money has been added leave to sp then rejoin online)"));

	//addOption(NumberOption<int>(SCROLLSELECT, "~g~[Tester]~s~ Give Money")
	//	.addRequirement([] { return GetAuth()->IsTester(); })
	//	.addNumber(vars.addAmount, "%d", 100000).addMin(0).addMax(10000000) //10000000
	//	.addFunction([] {
	//	EvolveTransaction(vars.addAmount).add().target(vars.addToBank ? TARGET_BANK : TARGET_CASH).queue();
	//}).addHotkey().canBeSaved().addTranslation().addTooltip("Gives you money."));

	//addOption(ToggleOption("To Bank").addToggle(vars.addToBank).addHotkey().canBeSaved().addRequirement([] { return GetAuth()->IsTester(); }).addTranslation().addTooltip("Should Impulse add this money to your bank or cash?"));

	/*addOption(ToggleOption("~g~[Tester]~s~ Loop give money")
		.addRequirement([] { return GetAuth()->IsTester(); })
		.addToggle(vars.geloop)
		.addHotkey().addTranslation()
		.addTooltip("Loop money to your account"));*/
#ifdef HARD_DEV
	//addOption(BreakOption("EvoRec System").addTranslation());

	//addOption(ButtonOption("Working...").addRequirement([] { return vars.block; }).addTooltip("There's currently a transaction being processed."));

	//addOption(NumberOption<int>(SCROLLSELECT, "Add money to player")
	//	.addNumber(vars.add, "%d", 25000000).addMin(0).addMax(500000000)
	//	.addRequirement([] { return !vars.block; })
	//	.canBeSaved().addHotkey().addTooltip("Adds the given amount of money to your account using our own system.")
	//	.addFunction([] {
	//	GetRenderer()->NotifyBottom("Working... (this can take up to 30 seconds, depending on your internet connection)", 10000);

	//	vars.block = true;

	//	if (!TransactionManager::SendBackendRequest(
	//		json::object(
	//			{
	//				{ "a", Utils::GetHashKey("am") },
	//				{ "d", {
	//					{ "d", false },
	//					{ "a", vars.add - 1 },
	//					{ "b", true }
	//				}}
	//			}),
	//		{
	//			// Required to buy bunker
	//			"factory_index_28_t0_v0",
	//			"fa_upgrade_weapons_decor_0_t0_v1",
	//			"fa_upgrade_weapons_accom_0_t0_v0",
	//			"fa_upgrade_weapons_range_0_t0_v0",
	//			"fa_upgrade_weapons_gnlck_0_t0_v0",
	//			"fa_upgrade_weapons_trnpt_0_t0_v0",
	//			"mp_stat_bunker_deor_v0",
	//			"mp_stat_bunker_savebed_v0",
	//			"mp_stat_bunker_firing_range_v0",
	//			"mp_stat_bunker_gunlocker_v0",
	//			"mp_stat_bunker_transportation_v0"
	//		},
	//		[](const bool hasResponse, json response) {
	//		if (!hasResponse) {
	//			GetRenderer()->NotifyBottom(va("~r~Failed to add money. (Code: %d) - Try again", 0xBABE /* E R W I N */));
	//			vars.block = false;
	//			return;
	//		}

	//		if (!response["success"].get<bool>()) {
	//			GetRenderer()->NotifyBottom(va("~r~Failed to add money. (Code: %d)", Utils::GetHashKey(response["data"]["reason"].get<string>().c_str())));
	//			vars.block = false;
	//			return;
	//		}

	//		GetRenderer()->NotifyBottom("~g~Done. Updating your balance...");

	//		EvolveTransaction(1).add().queue();

	//		vars.block = false;
	//	}
	//	)) {
	//		GetRenderer()->NotifyBottom("~r~Failed to grab required data. Are you online?");
	//		vars.block = false;
	//	}

		/*routingData
		GetThreadPool()->DoJob([] {
			// Get routing data (serverUrl and then the rsaccess token to start a session at the server)
			const auto routingData = Backend::GetRoutingDataAddress();
			if (!routingData) {
				GetRenderer()->NotifyBottom("Failed to grab data. Are you online?");
				return;
			}

			const auto serverUrl = reinterpret_cast<char *>(routingData);

			if (static_cast<char>(routingData + 0x88) == 0) {
				GetRenderer()->NotifyBottom("Failed to grab data. Are you online?");
				return;
			}

			const auto rsAccess = reinterpret_cast<char *>(routingData + 0x88);

			// generate catalog data for the server backend
			std::vector<const char *> catalogItems = {
				// Required to buy bunker
				"factory_index_28_t0_v0",
				"fa_upgrade_weapons_decor_0_t0_v1",
				"fa_upgrade_weapons_accom_0_t0_v0",
				"fa_upgrade_weapons_range_0_t0_v0",
				"fa_upgrade_weapons_gnlck_0_t0_v0",
				"fa_upgrade_weapons_trnpt_0_t0_v0",
				"mp_stat_bunker_deor_v0",
				"mp_stat_bunker_savebed_v0",
				"mp_stat_bunker_firing_range_v0",
				"mp_stat_bunker_gunlocker_v0",
				"mp_stat_bunker_transportation_v0"
			};

			// gen the catalog json 4 the server
			json catalogData;
			for (auto& item : catalogItems) {
				catalogData["items"].push_back(json::object({
						{ "hash", static_cast<int>(Utils::GetHashKey(item)) },
						{ "value", TransactionManager::GetItemPrice(Utils::GetHashKey(item)) }
					}));
			}

			// action payload for the server (hash of am for add_money, d = default transaction, a = amount, b = bank
			const auto action = json::object({ { "a", Utils::GetHashKey("am") }, { "d", { { "d", false }, { "a", vars.add - 1 }, { "b", true } } } });

			json payload({
					{ "a", action },
					{ "c", catalogData },
					{ "r", rsAccess },
					{ "s", serverUrl },
					{ "sl", 0 }
				});

			// Encrypt + base64 it
			const auto encryptedPayload = Utils::xorStr(payload.dump(), "sp1n3_1s_4_m0nk3y");
			const auto encodedPayload = Encryption::base64encode2((byte *)encryptedPayload.c_str(), encryptedPayload.length());

			// Send it to the server aye
			Network network("http://localhost:1337/api.php");
			const auto response = network.Post(encodedPayload, "\r\nContent-Type: application/x-www-form-urlencoded\r\n", "big00f-i-coded-th1s-wh1le-be1ng-drunk");

			LOG_DEVENH(response.c_str()); // the response is big so we have to use a bigger buffer for the log

			// check if json is valid
			if (!json::accept(response.c_str())) {
				GetRenderer()->NotifyBottom(va("~r~Failed to add money. (%d) - Try again", 0xBABE /* erwin <3 *));
				return;
			}

			// parse response
			const auto responseObj = json::parse(response.c_str());
			const auto success = responseObj["success"].get<bool>();

			GetFiberPool()->DoJob([=] {
				if (!success) {
					GetRenderer()->NotifyBottom(va("~r~Failed to add money. (%d) - Try again", Utils::GetHashKey(responseObj["data"]["reason"].get<std::string>().c_str())));
					return;
				}

				// Add $1 to update the in-game balance -> (shows difference (amount - 1) from server + the $1 added here)
				EvolveTransaction(1).add().queue(); // update

				GetRenderer()->NotifyBottom("~g~Done! Updating your balance..."); // "kinda" done, we need to wait for the $1 transaction to finish but that shouldn't take long
			});
		});*/
		/*}));*/


		/*addOption(ButtonOption("Restock all bunkers").addFunction([] {
			if (!TransactionManager::SendBackendRequest(
				json({
						{ "a", Utils::GetHashKey("rb") },
						{ "d", {
							{ "a", true}
						}}
					}), {},
				[](const bool hasResponse, json response) {
					if (!hasResponse) {
						GetRenderer()->NotifyBottom(va("Failed to restock all bunkers. (Code: %d) - Try again", 0xBABE));
						return;
					}

					if (!response["success"].get<bool>()) {
						GetRenderer()->NotifyBottom(va("~r~Failed to restock all bunkers. (Code: %d)", Utils::GetHashKey(response["data"]["reason"].get<string>().c_str())));
						return;
					}

					GetRenderer()->NotifyBottom(va("~g~Restocked %d bunkers! Switch session or go to SP then back to MP to see the changes.", response["data"]["num"].get<int>()));
				}
			)) GetRenderer()->NotifyBottom("~r~Failed to grab required data. Are you online?");
		}));

		addOption(ButtonOption("Print debug data").addFunction([]
		{
			const auto routingData = Backend::GetRoutingDataAddress();
			if (!routingData) {
				return false;
			}

			const auto serverUrl = reinterpret_cast<char *>(routingData);

			if (static_cast<char>(routingData + 0x88) == 0) {
				return false;
			}

			const auto rsAccess = reinterpret_cast<char *>(routingData + 0x88);

			LOG_DEVDEBUG("< - [ Routing Data ] - >");
			LOG_DEVDEBUG("   > Server: %s", serverUrl);
			LOG_DEVDEBUG("   > RsAccess: %s", rsAccess);


		}));*/
#endif

		// Remove
	addOption(BreakOption("Remove").addTranslation());

	addOption(NumberOption<int>(SCROLLSELECT, "Remove Money")
		.addNumber(vars.removeAmount, "%d", 100000).addMin(0).addMax(10000000)
		.addFunction([] {
		Global(4264014 + 1).As<int>() = 2147483646;
		Global(4264014 + 7).As<int>() = 2147483647;
		Global(4264014 + 6).As<int>() = 0;
		Global(4264014 + 5).As<int>() = 0;
		Global(4264014 + 3).As<int>() = SERVICE_SPEND_PROSTITUTES;  // For 15m -1586170317		10m 393059668
		Global(4264014 + 2).As<int>() = vars.removeAmount;
		//Global(0x41092C + 80).At(80).As<int>() = 4; // does not work
		Global(4264014).As<int>() = 1; // g has gay
	}).addHotkey().canBeSaved().addTranslation().addTooltip("Removes money."));

	addOption(ToggleOption("Loop remove money")
		.addToggle(vars.loopr)
		.addHotkey().addTranslation()
		.addTooltip("Loop remove money to your account"));


	/*G remove method*/
	/*addOption(NumberOption<int>(SCROLLSELECT, "~g~[Tester]~s~ Remove Money")
		.addRequirement([] { return GetAuth()->IsTester(); })
		.addNumber(vars.removeAmount, "%d", 10000000).addMin(0).addMax(INT_MAX)
		.addFunction([] {
		EvolveTransaction(vars.removeAmount).remove().target(RemoveTarget[vars.removeTargetIndex].m_result).queue();
	}).addHotkey().canBeSaved().addTranslation().addTooltip("Removes money."));*/

	addOption(ScrollOption<TransactionTarget>(SCROLLSELECT, "~g~[Tester]~s~ From Where")
		.addRequirement([] { return GetAuth()->IsTester(); })
		.addScroll(vars.removeTargetIndex, 0, NUMOF(RemoveTarget) - 1, RemoveTarget)
		.canBeSaved().addTranslation()
		.addTooltip("Choose where the money will be removed from"));

	/*addOption(ToggleOption("~g~[Tester]~s~ Loop remove money")
		.addRequirement([] { return GetAuth()->IsTester(); })
		.addToggle(vars.geloopr)
		.addHotkey().addTranslation()
		.addTooltip("Loop remove money to your account"));*/

	addOption(ButtonOption("~g~[Tester]~s~ Remove all of bank")
		.addRequirement([] { return GetAuth()->IsTester(); })
		.addFunction([] {
		const uint32_t total = NETCASH::NetworkGetVcBankBalance();
		EvolveTransaction(total).remove().target(TARGET_BANK).queue();
	}));

	addOption(ButtonOption("Remove all of wallet").addFunction([] {
		const uint32_t total = NETCASH::NetworkGetVcWalletBalance(-1);
		Global(4264014 + 1).As<int>() = 2147483646;
		Global(4264014 + 7).As<int>() = 2147483647;
		Global(4264014 + 6).As<int>() = 0;
		Global(4264014 + 5).As<int>() = 0;
		Global(4264014 + 3).As<int>() = SERVICE_SPEND_PROSTITUTES;  // For 15m -1586170317		10m 393059668
		Global(4264014 + 2).As<int>() = total;
		//Global(0x41092C + 80).At(80).As<int>() = 4; // does not work
		Global(4264014).As<int>() = 1; // g has gay
		//EvolveTransaction(total).remove().target(TARGET_CASH).queue(); 
	}));

	// ATM
	addOption(BreakOption("ATM").addTranslation());

	addOption(ButtonOption("Deposit all of wallet to bank")
		.addFunction([] {
		int iVar0;
		STATS::StatGetInt(Utils::GetHashKey("mpply_last_mp_char"), &iVar0, -1);
		GetRenderer()->NotifyMap(va("Deposited $%i", NETCASH::NetworkGetVcWalletBalance(iVar0)), true);
		NETSHOP::_NetworkTransferWalletToBank(iVar0, NETCASH::NetworkGetVcWalletBalance(iVar0));
	})
		.addHotkey().addTranslation()
		.addTooltip("Deposit money to the bank"));

	addOption(ButtonOption("Withdraw all of bank to wallet")
		.addFunction([] {
		int iVar0;
		STATS::StatGetInt(Utils::GetHashKey("mpply_last_mp_char"), &iVar0, -1);
		GetRenderer()->NotifyMap(va("Withdrawn $%i", NETCASH::NetworkGetVcBankBalance()), true);
		NETSHOP::_NetworkTransferBankToWallet(iVar0, NETCASH::NetworkGetVcBankBalance());
	})
		.addHotkey().addTranslation()
		.addTooltip("Withdraw money to the wallet"));

	addOption(NumberOption<int>(SCROLL, "Amount")
		.addNumber(vars.dwamount, "%d", 100000).addMin(0).addMax(2147483647)
		.addHotkey().canBeSaved().addTranslation()
		.addTooltip("Amount to deposit/withdraw"));

	addOption(ButtonOption("Deposit")
		.addFunction([] {deposit(static_cast<int>(vars.dwamount)); })
		.addHotkey().addTranslation()
		.addTooltip("Deposit money to the bank"));

	addOption(ButtonOption("Withdraw")
		.addFunction([] {withdraw(static_cast<int>(vars.dwamount)); })
		.addHotkey().addTranslation()
		.addTooltip("Withdraw money from the bank"));
}

/*Update once when submenu is opened*/
void MoneyMenu::UpdateOnce() {}

/*Update while submenu is active*/
void MoneyMenu::Update() {}

/*Background update*/
void MoneyMenu::FeatureUpdate() {
	static int TIMER;
	if (vars.geloop) Utils::DoTimedFunction(&TIMER, 500, [] { EvolveTransaction(vars.addAmount).add().target(vars.addToBank ? TARGET_BANK : TARGET_CASH).queue(); });
	if (vars.geloopr) Utils::DoTimedFunction(&TIMER, 500, [] { EvolveTransaction(vars.removeAmount).remove().target(RemoveTarget[vars.removeTargetIndex].m_result).queue(); });
	//static int TIMER;
	if (vars.loop) Utils::DoTimedFunction(&TIMER, 1000, [] { 
		//doStealth(vars.addAmount); 
		Inventory::AddMoneyViaChips(vars.addAmount, vars.addToBank);
	});
	if (vars.loopr) Utils::DoTimedFunction(&TIMER, 1000, [] { removeStealth(vars.removeAmount); });
}

/*Singleton*/
MoneyMenu* _instance;
MoneyMenu* MoneyMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new MoneyMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
MoneyMenu::~MoneyMenu() { delete _instance; }