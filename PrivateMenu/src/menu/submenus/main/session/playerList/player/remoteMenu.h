#pragma once
#include "menu/submenu.h"

class RemoteMenu : public Submenu {
public:
	static RemoteMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	RemoteMenu() : Submenu() {}
	~RemoteMenu();
};

namespace RemoteMenuVars
{
	struct Vars
	{
		int m_invite;
		int m_mission;
		int m_msgs;
		int m_moneyamount;
		int m_moneymsgs;
	};

	extern ScrollStruct<int> invites[6];
	extern ScrollStruct<int> missions[6];
	extern ScrollStruct<int> msgs[10];
	extern ScrollStruct<int> moneyamount[8];
	extern ScrollStruct<int> moneymsgs[3];

	void NonHostKick(SPlayer& player);
	void KickToSingleplayer(SPlayer& player);
	void CEOKick(SPlayer& player);
	void CEOBan(SPlayer& player);
	void InfiniteLoadingScreen(SPlayer& player);
	void Invite(SPlayer& player, int index);
	void GOTR(SPlayer& player);
	void GNeverWanted(SPlayer& player);
	void GCopsTurnBlindEye(SPlayer& player);
	void Friendly(SPlayer& player);
	void Helpful(SPlayer& player);
	void BadRep(SPlayer& player);
	void RBadSport(SPlayer& player);
	void BadSport(SPlayer& player);
	void SoundSpam(SPlayer& player);
	void DisplaySpectatingMessage(SPlayer& player);
	//void TransactionSpam(SPlayer& player);
	void WantedLevelRP(SPlayer& player);
	void FaceCameraForward(SPlayer& player);
}