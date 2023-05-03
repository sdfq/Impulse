#pragma once
#include "menu/submenu.h"
#include "util/memory/reclass.h"

class MoneyMenu : public Submenu {
public:
	static MoneyMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	MoneyMenu() : Submenu() {}
	~MoneyMenu();
};

namespace MoneyMenuVars {
	struct Vars {
		// add
		int addAmount = 1000000;
		bool addToBank = true;
		bool addLoop = false;

		// evorec
		int add = 500000000;
		bool block = false;

		// remove
		int removeAmount = 10000000;
		int removeTargetIndex = 0;

		int dwamount = 100000;
		bool loop;
		bool loopr;
		bool geloop;
		bool geloopr;
	};
}