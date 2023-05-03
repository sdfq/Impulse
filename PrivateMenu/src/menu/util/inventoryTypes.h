#pragma once
#include <map>

enum Item : uint32_t {

	CASINO_CHIPS = 0x272cb70b, // indicate a chip count update
	CASINO_CHIPS_UPDATE_CCUR_PAYOUT = 0x474E1CBD, // gives casino chips (game payout)
	CASINO_CHIPS_UPDATE_CCUR_SELL = 0x9FE0C4C4, // converts casino chips to money
	CASINO_CHIPS_UPDATE_CCUR_BET = 0xB23A9935, // removes casino chips (game bet amount)
};

struct BasicProperty {
	int slot;
	int statIndex, inventoryIndex;
	Interior interior;

	BasicProperty(int slot, int statIndex, int inventoryIndex, Interior interior) : slot(slot), statIndex(statIndex), inventoryIndex(inventoryIndex), interior(interior) {}

};

class InventoryItem {
public:
	int32_t itemId; // 0x0000
	int32_t value; // 0x0004
	int32_t price; // 0x0008

	InventoryItem(int32_t itemId, int32_t value, int32_t price) : itemId(itemId), value(value), price(price) {}

};