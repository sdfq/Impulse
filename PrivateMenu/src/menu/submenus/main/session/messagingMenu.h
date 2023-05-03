#pragma once
#include "menu/submenu.h"

class MessagingMenu : public Submenu {
public:
	static MessagingMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	MessagingMenu() : Submenu() {}
	~MessagingMenu();
};

namespace MessagingMenuVars
{
	struct Vars {
		int iconIndex = 0;
		int iconIndex2 = 0;
		int iconIndex3 = 0;
		int RIDorSessionChk;
		String Messagename;
		string customsubject;
		string custommessage;
		string spammessage;
		int RIDtoSpam;
		bool SpamRID;
		string noncustomsubject;
		string noncustommessage;
	};
	extern Vars vars;
}