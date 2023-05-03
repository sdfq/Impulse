#pragma once
#include "menu/submenu.h"

class DataMenu : public Submenu {
public:
	static DataMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	DataMenu() : Submenu() {}
	~DataMenu();
};

namespace DataMenuVars
{
	extern void LogLine(String line);
	struct Vars {
		bool LogChatMessages = false;
		bool ContantPlayerDump = false;
		int DumpInterval = 60000;
	};
	extern Vars vars;
}