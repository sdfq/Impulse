#pragma once
#include "menu/submenu.h"

class MiscMenu : public Submenu {
public:
	static MiscMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	MiscMenu() : Submenu() {}
	~MiscMenu();
};

namespace MiscMenuVars
{
	struct Vars {
		bool seethroughwalls = false;
		bool bypasschatrestrictions = false;
		bool potatopcmode = false;
		Cam OldStyleGameplayCamHandle;
		bool oldstylegameplaycam = false;
		bool bypassOrganizationChat;
		bool enablerestrictedareas;
		bool mobileradio;
		bool snowtrails;
		bool disableIdleKick;
		bool disableCinematicButton;
		bool disableStuntJumpCutscenes;
		bool disablePhoneCalls;
		bool disableNotifications;
		bool disableGameRecordings;
		bool disableHUD;
		int cameraZoomValue = 5;
		bool cameraZoom;
		bool freecam;
		int freecamHandle;
		bool freecamAttack;
		bool fps;
		int DrawFPSCache[2];
		bool spawnatfreecam;
		bool displaycoords;
		float freecamspeed = 2.0f;
		bool Outlineonscreenelements;
		Color Colorscreenelements = { 255, 255, 255, 255 };
		bool Allowmousemovements;
		bool alwaysoncontrollerfreecam;
	};
	extern Vars vars;
}