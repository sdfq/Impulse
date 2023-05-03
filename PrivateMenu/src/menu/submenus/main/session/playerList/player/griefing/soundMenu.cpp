#include "stdafx.h"
#include "soundMenu.h"
#include "../griefingMenu.h"

using namespace SoundMenuVars;

namespace SoundMenuVars {
	Vars vars;

	char* PlaySounds[3][28] = {
		{ "Orbital Cannon", "Beep", "Alien", "Endless Beep", "Short Beep", "Ring tone 1", "Ring tone 2", "Whistle", "EMP", "Helicopter", "Key card 1", "Key card 2", "Scan", "Leaf blower", "Carwash 1", "Carwash 2", "Carwash 3", "Unlock", "Brakes", "Yacht Arrive Horn", "Darts Bullseye", "Yacht Horn", "Jet Explosions", "Alarm", "Train Bell", "Long Scream", "Short Scream", "Jet Engine" },
		{ "DLC_XM_Explosions_Orbital_Cannon", "Hack_Success", "SPAWN", "CONTINUAL_BEEP", "IDLE_BEEP", "Remote_Ring", "PED_PHONE_DIAL_01", "Franklin_Whistle_For_Chop", "EMP_Vehicle_Hum", "Helicopter_Wind", "Keycard_Success", "Keycard_Fail", "SCAN", "GARDENING_LEAFBLOWER_ANIM_TRIGGERED", "SPRAY", "SPRAY_CAR", "DRYER", "Bar_Unlock_And_Raise", "MOD_SHOP_BRAKES_ONESHOT", "Arrive_Horn", "DARTS_HIT_BULLSEYE_MASTER", "Horn", "Jet_Explosions", "ALARMS_KLAXON_03_CLOSE", "Train_Bell", "TEST_SCREAM_LONG", "TEST_SCREAM_SHORT", "Trevor_4_747_Jet_Engine" },
		{ 0, "DLC_HEIST_BIOLAB_PREP_HACKING_SOUNDS", "BARRY_01_SOUNDSET", "EPSILONISM_04_SOUNDSET", "EPSILONISM_04_SOUNDSET", "Phone_SoundSet_Michael", 0, "SPEECH_RELATED_SOUNDS", "DLC_HEIST_BIOLAB_DELIVER_EMP_SOUNDS", "BASEJUMPS_SOUNDS", "DLC_HEISTS_BIOLAB_FINALE_SOUNDS", "DLC_HEISTS_BIOLAB_FINALE_SOUNDS", "EPSILONISM_04_SOUNDSET", 0, "CARWASH_SOUNDS", "CARWASH_SOUNDS", "CARWASH_SOUNDS", "DLC_IND_ROLLERCOASTER_SOUNDS", 0, "DLC_Apartment_Yacht_Streams_Soundset", 0, "DLC_Apt_Yacht_Ambient_Soundset", "exile_1", 0, "Prologue_Sounds", 0, 0, 0 },
	};

	void StopSounds() {
		for (int i = 0; i < vars.soundCounter; i++) {
			AUDIO::StopSound(i);
		}
		vars.soundCounter = 0;
	}

	void PlayTheSound(int i) {
		Vector3 coords = GetSelectedPlayer().m_coordinates;
		AUDIO::PlaySoundFromCoord(AUDIO::GetSoundId(), PlaySounds[1][i], coords.x, coords.y, coords.z, PlaySounds[2][i], true, 0, true);
		vars.soundCounter++;
	}

	void Earrape(SPlayer& player) {
		static int TIMER;
		Vector3 targetCoords = GetSelectedPlayer().m_coordinates;
		Utils::DoTimedFunction(&TIMER, 100, [&] {
		AUDIO::PlaySoundFromCoord(-1, "DLC_XM_Explosions_Orbital_Cannon", targetCoords.x, targetCoords.y, targetCoords.z, 0, 1, 0, 0);
		});
	}
}

void SoundMenu::Init() {
	setParentSubmenu<GriefingMenu>();
	setName("Sounds", true, false);

	addOption(ButtonOption("Stop sounds")
		.addFunction(StopSounds).addTranslation().addHotkey()
		.addTooltip("Stop all currently playing sounds"));

	addOption(ToggleOption("Sound rape")
		.addToggle(GetSelectedPlayer().m_soundrape)
		.addOnUpdate([](ToggleOption* option) { option->addToggle(GetSelectedPlayer().m_soundrape); })
		.addTooltip("This will spam the player with explosive sounds").addTranslation());

	for (int i = 0; i < 28; i++) {
		addOption(ButtonOption(PlaySounds[0][i])
			.addFunction([=] { PlayTheSound(i); }).addTranslation().addHotkey());
	}
}

/*Update once when submenu is opened*/
void SoundMenu::UpdateOnce() {}

/*Update while submenu is active*/
void SoundMenu::Update() {}

/*Background update*/
void SoundMenu::FeatureUpdate() {
	OnlinePlayerCallback(true, [](SPlayer player) { if (player.m_soundrape) Earrape(player); });
}

/*Singleton*/
SoundMenu* _instance;
SoundMenu* SoundMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new SoundMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
SoundMenu::~SoundMenu() { delete _instance; }