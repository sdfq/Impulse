#pragma once
#include "menu/submenu.h"

class BlacklistList : public Submenu {
public:
	static BlacklistList* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	BlacklistList() : Submenu() {}
	~BlacklistList();
};

namespace BlacklistListVars
{
	/*struct onlineinfo {
		int rockstarID;
		bool isOnline = false;
		bool hasNotified = false;

	};*/

	struct Var {
		vector<uint32_t> ridToCheck;
		String itemID;
		int selectedBlacklistPlayer;
		bool enableBlacklist = true;
		bool showridsonline;
		unordered_map<uint32_t, bool> elMap;
	};
	extern Var vars;
}