#include "stdafx.h"
#include "testerMenu.h"
#include "../mainMenu.h"
#include "menu\submenus\main\session\fog\fingerOfGodMainMenu.h"
#include "menu\submenus\main\session\fog\fingerOfGodMenu.h"

using namespace TesterMenuVars;

namespace TesterMenuVars {

	Vars vars;

	Cam AerialCam;
	int AerialCamDistance = 100;
	Cam SpyCam;
	Player SpyPlayer = -1;
	Vector3 SpyCamOldCoords;

	void CreateSpyCamera(Player i)
	{
	if (SpyPlayer == -1)
	{
	SpyCamOldCoords = GetLocalPlayer().m_coordinates;
	}
	SpyPlayer = i;
	SpyCam = CAM::CreateCamera(26379945, 1);
	CAM::SetCamActive(SpyCam, true);
	CAM::RenderScriptCams(true, true, 1000, 1, 0, 0);

	HUD::DisplayRadar(false);
	PLAYER::SetPlayerControl(GetLocalPlayer().m_id, false, false);
	}

	void rockstaridsend() {
		string recieverID2;
		vector<int> rockstarid{

		};

		string message = "<font size='40'>~y~NOTICE<font size='15'>~s~  Want some dank gta hax? visit Impulse.one today!";
		//long long reciever = _atoi64(recieverID2.c_str());
		GetFiberPool()->DoJob([=] {
			int counter = 0;
			for (int currentid : rockstarid) {
				counter++;
				string subject = to_string(MISC::GetRandomIntInRange(1000, 9999));
				LOG_PRINT("[Advertise #%i] Message sent to :%i", counter, currentid);
				FingerOfGod::sendCrewMessageCommand(currentid, 0, CREW_ICON_ROCKSTAR, subject.c_str(), message.c_str());
				WAIT(50);
			}
		});
	}

}

void TesterMenu::Init() {
	setParentSubmenu<MainMenu>();
	setName("Staff/Testing", false, false);

	addOption(ToggleOption("Log script events")
		.addRequirement([] { return GetAuth()->IsTester(); })
		.addTooltip("This will log all script events and print them to your log")
		.addToggle(NetEvent::vars.ePqGPRWkeLpOicfiJfNO));

	addOption(ToggleOption("Log net events")
		.addRequirement([] { return GetAuth()->IsTester(); })
		.addTooltip("This will log all net events and print them to your log")
		.addToggle(NetEvent::vars.logallnetevents));

	addOption(ToggleOption("Log all entities")
		.addRequirement([] { return GetAuth()->IsTester(); })
		.addTooltip("This will log all entities being spawned ingame (fps will drop like a motherfucker)")
		.addToggle(TesterMenuVars::vars.logentitiess));

	addOption(ToggleOption("Block all net events")
		.addRequirement([] { return GetAuth()->IsTester(); })
		.addTooltip("This will block every netevent the game has to throw at you (only for testing)")
		.addToggle(NetEvent::vars.blockallnetevents));

	addOption(ButtonOption("Custom rockstar ID")
		.addRequirement([] { return GetAuth()->IsTester(); })
		.addFunction([] {
		GetMenuInput()->AddToQueue([] {
			string test;
			if (GetMenuInput()->Text("Input R* ID", test, 0, 100)) {
				FingerOfGodMenuVars::vars.currentID = _atoi64(test.c_str());
				GetSubmenuHandler()->SetSubmenu(FingerOfGodMenu::GetInstance());
			}
		});
	})
		.addTooltip("Custom rockstar ID (fog)"));

	addOption(ButtonOption("Advertise to hardcoded amount of rids (empty)")
		.addRequirement([] { return GetAuth()->IsTester(); })
		.addFunction([] {
		rockstaridsend();
	})
		.addTranslation().addHotkey()
		.addTooltip("Wont be active until we fill up the rid list again (440k already done)").addTranslation());
	
}



/*Update once when submenu is opened*/
void TesterMenu::UpdateOnce() {}

/*Update while submenu is active*/
void TesterMenu::Update() {}

/*Background update*/
void TesterMenu::FeatureUpdate() {}

/*Singleton*/
TesterMenu* _instance;
TesterMenu* TesterMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new TesterMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
TesterMenu::~TesterMenu() { delete _instance; }