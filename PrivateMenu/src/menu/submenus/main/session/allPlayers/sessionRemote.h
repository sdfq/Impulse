#pragma once
#include "menu/submenu.h"

class SessionRemoteMenu : public Submenu {
public:
	static SessionRemoteMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	SessionRemoteMenu() : Submenu() {}
	~SessionRemoteMenu();
};

namespace SessionRemoteMenuVars
{
	struct Vars {
		bool soundSpam;
		bool transactionSpam;
		bool spectating;
		int m_invite;
		bool gotr;
		int m_mission;
		bool gneverWanted;
		bool gblindEye;
		bool lockview;
		int m_sendmsg;
		int m_sendmmsg;
		int m_moneyamount;
		bool badsportlobby;
		bool rbadsportlobby;
	};
}