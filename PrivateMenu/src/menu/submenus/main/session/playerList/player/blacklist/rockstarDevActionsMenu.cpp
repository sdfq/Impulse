#include "stdafx.h"
#include "rockstarDevActionsMenu.h"
#include "BlacklistList.h"

using namespace RockstarDevActionsVars;

namespace RockstarDevActionsVars {
	Var vars;

	bool IsRockstarDevPresent1() {
		if (NETWORK::NetworkIsSessionActive()) {
			for (int i = 0; i < MAXPLAYERS; i++) {
				if (!ENTITY::DoesEntityExist(PLAYER::GetPlayerPedScriptIndex(i))) continue;
				CPed* ped = (CPed*)PoolManager::GetEntityAddress(GetPlayer(i).m_ped);
				BYTE* ExternalIP = reinterpret_cast<BYTE*>(&ped->PlayerInfo->ExternalIP);
				string ip = std::to_string(*(ExternalIP + 3)) + "." + std::to_string(*(ExternalIP + 2)) + "." + std::to_string(*(ExternalIP + 1)) + "." + std::to_string(*ExternalIP);
				if (ip.find("139.138") != string::npos) return true;
				else continue;
			}
		}
		return false;
	}

	bool IsRockstarDevPresent2() {
		if (NETWORK::NetworkIsSessionActive()) {
			for (int i = 0; i < MAXPLAYERS; i++) {
				uint64_t pedClass = PoolManager::GetEntityAddress(GetPlayer(i).m_ped);
				if (pedClass != 0) {
					CPed* ped = (CPed*)pedClass;
					int rockstarid = ped->PlayerInfo->RockstarID;
					/*if (GetPlayer(i).m_isEvolveUserHidden) {
						return false;
					} else {*/
						//LOG_DEBUG(va("id: %i", rockstarid));
						if (rockstarid == 103019313) return true; //DigitalKitsune      
						if (rockstarid == 103054099) return true; //DigitalFox9         
						if (rockstarid == 104041189) return true; //FoxesAreCool69      
						if (rockstarid == 110470958) return true; //huginn6767          
						if (rockstarid == 119266383) return true; //xCuteBunny          
						if (rockstarid == 119958356) return true; //random_123          
						if (rockstarid == 121397532) return true; //flyingcobra16       
						if (rockstarid == 121698158) return true; //CriticalRegret      
						if (rockstarid == 123839036) return true; //Highhunt            
						if (rockstarid == 123849404) return true; //bipolarcarp         
						if (rockstarid == 127531278) return true; //prosolo45473  
						if (rockstarid == 127878077) return true; //JohnnyOnThaSpotf    
						if (rockstarid == 121943600) return true; //HammerDaddy69             
						if (rockstarid == 129159629) return true; //Kakorot02                 
						if (rockstarid == 18965281)	return true; //ScentedPotter             
						if (rockstarid == 216820)	return true; //random123                 
						if (rockstarid == 56778561) return true; //Huginn5                   
						if (rockstarid == 99453545) return true; //BrexitToTheKnees          
						if (rockstarid == 99453882) return true; //SweetPlumbus
						if (rockstarid == 10612782) return true; //Tomer077x      
						if (rockstarid == 18914188) return true; //MarissaB
						///////
						if (rockstarid == 134412628) return true; //shibuz_gamer123
						if (rockstarid == 133709045) return true; //PayneInUrAbs
						if (rockstarid == 64234321) return true; //StrongBelwas1
						if (rockstarid == 131973478) return true; //RossThetic
						if (rockstarid == 137579070) return true; //M1thras
						else continue;
					//}
				}
			}
		}
		return false;
	}

}

void RockstarDevActionsMenu::Init() {
	setParentSubmenu<BlacklistList>();
	setName("Select what to do", true, true);

	addOption(ToggleOption("Warn me")
		.addToggle(vars.warn)
		.addTooltip("Warn me if rockstar are within my session"));

	addOption(ToggleOption("Exit GTA Online")
		.addToggle(vars.bail)
		.addTooltip("If rockstar are within my session bail from the session"));

	addOption(ToggleOption("Exit GTA V")
		.addToggle(vars.exit)
		.addTooltip("If rockstar are within my session quit the game process"));
}

/*Update once when submenu is opened*/
void RockstarDevActionsMenu::UpdateOnce() {


}

/*Update while submenu is active*/
void RockstarDevActionsMenu::Update() {

}

/*Background update*/
void RockstarDevActionsMenu::FeatureUpdate() {
	static int TIMER;
	static bool update = true;
	Utils::DoTimedFunction(&TIMER, 250, [] { update = true; });

	if (update && BlacklistListVars::vars.enableBlacklist) {
		if (IsRockstarDevPresent1() || IsRockstarDevPresent2()) {
			if (vars.warn) {
				GetRenderer()->NotifyMap("A rockstar dev has been detected in your lobby, you're advised to leave the game.", false);
			}
			if (vars.exit) {
				GetRenderer()->NotifyMap("A rockstar dev has been detected in your lobby, closing game.", true);
				//exit(0);
				GetFiberPool()->DoJob([=] {
					WAIT(2000);
					exit(0);
				});
			}
			if (vars.bail) {
				GetRenderer()->NotifyMap("A rockstar dev has been detected in your lobby, leaving GTA:O.", true);
				//NETWORK::NetworkBail(0xFFFFFF, 1, 1);
				GetFiberPool()->DoJob([=] {
					WAIT(2000);
					NETWORK::NetworkBail(0xFFFFFF, 1, 1);
				});
			}
		}
		update = false;
	}
}

/*Singleton*/
RockstarDevActionsMenu* _instance;
RockstarDevActionsMenu* RockstarDevActionsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new RockstarDevActionsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
RockstarDevActionsMenu::~RockstarDevActionsMenu() { delete _instance; }