#include "stdafx.h"
#include "sessionModifications.h"
#include "../allPlayersMenu.h"
#include "../../world/weatherManagerMenu.h"

using namespace SessionModificationsMenuVars;

namespace SessionModificationsMenuVars {
	Vars vars;
}

void SessionModificationsMenu::Init() {
	setParentSubmenu<AllPlayersMenu>();
	setName("Session modifications", true, true);

	addOption(ScrollOption<String>(SCROLLSELECT, "Lobby weather")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addScroll(vars.lobbyWeather, 0, NUMOF(WeatherManagerMenuVars::Weathers) - 1, WeatherManagerMenuVars::Weathers)
		.addFunction([&] {
			Natives::SetLobbyWeather(WeatherManagerMenuVars::Weathers[vars.lobbyWeather].m_result);
		}).addTranslation().addHotkey()
			.addTooltip("Lobby weather"));

	addOption(ButtonOption("Snow lobby")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addFunction([] { 
		NetEvent::vars.bypassweatherchangequick = true;
		Natives::fSetLobbyWeather(1, 13, 76, 0); 
		GetFiberPool()->DoJob([=] {
		WAIT(2000);
		NetEvent::vars.bypassweatherchangequick = false;
		});
		})
		.addTranslation().addHotkey()
		.addTooltip("Set the lobby weather to snow"));

	addOption(ButtonOption("Black screen lobby")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addFunction([] { Natives::fSetLobbyWeather(1, 15, 76, 0); })
		.addTranslation().addHotkey()
		.addTooltip("Set the lobby contrast low that it makes the screen black (doesnt show on your screen)"));

	addOption(BreakOption("Time").addTranslation());

	addOption(ButtonOption("Set lobby time to noon")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addFunction([] {
		NETWORK::NetworkOverrideClockTime(12, CLOCK::GetClockMinutes(), CLOCK::GetClockSeconds());
		Natives::SyncLobbyTimeWithMyTime();
	}).addTranslation().addHotkey()
		.addTooltip("Set lobby time to noon"));

	addOption(ButtonOption("Set lobby time to midnight")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addFunction([] {
		NETWORK::NetworkOverrideClockTime(0, CLOCK::GetClockMinutes(), CLOCK::GetClockSeconds());
		Natives::SyncLobbyTimeWithMyTime();
	}).addTranslation().addHotkey()
		.addTooltip("Set lobby time to midnight"));

	addOption(ButtonOption("Set lobby time to morning")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addFunction([] {
		NETWORK::NetworkOverrideClockTime(12, CLOCK::GetClockMinutes(), CLOCK::GetClockSeconds());
		Natives::SyncLobbyTimeWithMyTime();
	}).addTranslation().addHotkey()
		.addTooltip("Set lobby time to morning"));

	addOption(ButtonOption("Increase lobby hour")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addFunction([] {
		int hour = CLOCK::GetClockHours() + 1;
		if (hour > 23) hour = 0;
		NETWORK::NetworkOverrideClockTime(hour, CLOCK::GetClockMinutes(), CLOCK::GetClockSeconds());
		Natives::SyncLobbyTimeWithMyTime();
	}).addTranslation()
		.addTooltip("Increment the lobby hour by 1"));

	addOption(ButtonOption("Lower lobby hour")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addFunction([] {
		int hour = CLOCK::GetClockHours() - 1;
		if (hour < 0) hour = 23;
		NETWORK::NetworkOverrideClockTime(hour, CLOCK::GetClockMinutes(), CLOCK::GetClockSeconds());
		Natives::SyncLobbyTimeWithMyTime();
	}).addTranslation()
		.addTooltip("Decrement the lobby hour by 1"));

	addOption(BreakOption("Loops").addTranslation());

	addOption(ToggleOption("Lock lobby time to day")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.lockTimeToDay)
		.addTranslation().addHotkey()
		.addTooltip("Lock lobby time to day"));

	addOption(ToggleOption("Lock lobby time to midnight")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.lockTimeToMidnight)
		.addTranslation().addHotkey()
		.addTooltip("Lock lobby time to midnight"));

	addOption(ToggleOption("Spam day & midnight for lobby")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.spamDayNight)
		.addTranslation().addHotkey()
		.addTooltip("Spam day & midnight for lobby"));

	addOption(ToggleOption("Slow transition day to midnight for lobby")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.slowTrans)
		.addTranslation().addHotkey()
		.addTooltip("Slow transition day to midnight for lobby"));

	addOption(ToggleOption("Fast transition day to midnight for lobby")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.fastTrans)
		.addTranslation().addHotkey()
		.addTooltip("Fast transition day to midnight for lobby"));

	addOption(ToggleOption("Fast day to midnight for lobby")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.fastDay2Night)
		.addTranslation().addHotkey()
		.addTooltip("Fast day to midnight for lobby"));
}

/*Update once when submenu is opened*/
void SessionModificationsMenu::UpdateOnce() {}

/*Update while submenu is active*/
void SessionModificationsMenu::Update() {}

/*Background update*/
void SessionModificationsMenu::FeatureUpdate() {
	if (vars.lockTimeToDay) {
		NETWORK::NetworkOverrideClockTime(12, CLOCK::GetClockMinutes(), CLOCK::GetClockSeconds());
		Natives::SyncLobbyTimeWithMyTime();
	}

	if (vars.lockTimeToMidnight) {
		NETWORK::NetworkOverrideClockTime(0, CLOCK::GetClockMinutes(), CLOCK::GetClockSeconds());
		Natives::SyncLobbyTimeWithMyTime();
	}

	if (vars.spamDayNight) {
		static int TIMER;
		static bool loop;
		Utils::DoTimedFunction(&TIMER, 1000, [] {
			loop = !loop;
		});

		if (loop) {
			NETWORK::NetworkOverrideClockTime(12, CLOCK::GetClockMinutes(), CLOCK::GetClockSeconds());
			Natives::SyncLobbyTimeWithMyTime();
		} else {
			NETWORK::NetworkOverrideClockTime(0, CLOCK::GetClockMinutes(), CLOCK::GetClockSeconds());
			Natives::SyncLobbyTimeWithMyTime();
		}
	}

	if (vars.slowTrans) {
		static int TIMER;
		Utils::DoTimedFunction(&TIMER, 100, [] {
			int hours = CLOCK::GetClockHours();
			int minutes = CLOCK::GetClockMinutes();
			if (minutes < 60) { minutes++; }
			else { minutes = 0; hours++; }

			if (hours > 23)
				hours = 0;

			NETWORK::NetworkOverrideClockTime(hours, minutes, CLOCK::GetClockSeconds());
			Natives::SyncLobbyTimeWithMyTime();
		});
	}

	if (vars.fastTrans) {
		static int TIMER;
		Utils::DoTimedFunction(&TIMER, 100, [] {
			int hours = CLOCK::GetClockHours();
			int minutes = CLOCK::GetClockMinutes();
			if (minutes < 60) { minutes += 10; }
			else { minutes = 0; hours++; }

			if (hours > 23)
				hours = 0;

			NETWORK::NetworkOverrideClockTime(hours, minutes, CLOCK::GetClockSeconds());
			Natives::SyncLobbyTimeWithMyTime();
		});
	}

	if (vars.fastDay2Night) {
		static int TIMER;
		Utils::DoTimedFunction(&TIMER, 500, [] {
			int hours = CLOCK::GetClockHours();
			hours++;
			if (hours > 23)
				hours = 0;

			NETWORK::NetworkOverrideClockTime(hours, CLOCK::GetClockMinutes(), CLOCK::GetClockSeconds());
			Natives::SyncLobbyTimeWithMyTime();
		});
	}
}

/*Singleton*/
SessionModificationsMenu* _instance;
SessionModificationsMenu* SessionModificationsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new SessionModificationsMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
SessionModificationsMenu::~SessionModificationsMenu() { delete _instance; }