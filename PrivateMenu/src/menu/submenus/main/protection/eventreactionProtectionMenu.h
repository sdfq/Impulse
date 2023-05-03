#pragma once
#include "menu/submenu.h"

class EventReactionMenu : public Submenu {
public:
	static EventReactionMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	EventReactionMenu() : Submenu() {}
	~EventReactionMenu();
};

namespace EventReactionMenuVars
{
	enum eResponses {
		KICK,
		REPORT,
		MALICIOUS,
		NET_EVENT
	};

	struct PlayerType_t {
		char* Nickname;
		int Id; 
		int Reason;
	};

	struct Vars {
		bool enableeventreactionkick;
		bool enableeventreactionreport;
		bool enableeventreactionSE;
		bool enableeventreactionNE;
		int kicknum = 0;
		int reportnum = 0;
		int SEnum = 0;
		int NEnum = 0;
		bool autoaddtoblacklist;
		string custommessage;
	};
	extern Vars vars;

	extern ScrollStruct<int> Kickresponses[];

	extern ScrollStruct<int> Reportresponses[];

	extern ScrollStruct<int> SEresponses[];

	extern ScrollStruct<int> NEresponses[];

	extern void AddPlayer(PlayerType_t t);
}