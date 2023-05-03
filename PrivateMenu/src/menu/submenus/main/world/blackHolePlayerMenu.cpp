#include "stdafx.h"
#include "blackHolePlayerMenu.h"
#include "blackholeMenu.h"

using namespace BlackHolePlayerMenuVars;

namespace BlackHolePlayerMenuVars {
	Vars vars;
}

void BlackHolePlayerMenu::Init() {
	setParentSubmenu<BlackholeMenu>();
	setName("Attach to player", true, true);

	addOption(ToggleOption("Follow the player")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.FollowPlayer)
		.addTooltip("Follow the player or simply set the blackhole to their current position.")
		.addHotkey().addTranslation().canBeSaved());
}

/*Update once when submenu is opened*/
void BlackHolePlayerMenu::UpdateOnce() {}

/*Update while submenu is active*/
void BlackHolePlayerMenu::Update() {
	static int TIMER;
	static bool update = true;
	Utils::DoTimedFunction(&TIMER, 250, [] { update = true; });
	if (update)
	{
		clearOptionsOffset(1);
		vector<SPlayer> players;
		for (int i = 0; i < MAXPLAYERS; i++)
		{
			if (GetPlayer(i).m_exists)
			{
				players.push_back(GetPlayer(i));
			}
		}
		for (SPlayer& player : players)
		{
			string displayName = player.m_name;
			if (player.m_id == vars.AttachedTo)
				displayName = "~o~" + displayName;
			addOption(ButtonOption(displayName.c_str())
				.addTooltip("Select and attach the black hole.")
				.addFunction([&] 
				{ 
					vars.AttachedTo = player.m_id;
					BlackholeMenuVars::vars.position = player.m_coordinates;
				}));
		}

		if (GetMenu()->m_currentOption > m_options.size()) GetMenu()->ResetCurrentOption();
		update = false;
	}
}

/*Background update*/
void BlackHolePlayerMenu::FeatureUpdate() {
	if (vars.FollowPlayer)
	{
		if (NETWORK::NetworkIsPlayerConnected(vars.AttachedTo))
		{
			BlackholeMenuVars::vars.position = GetPlayer(vars.AttachedTo).m_coordinates;
		}
	}
}

/*Singleton*/
BlackHolePlayerMenu* _instance;
BlackHolePlayerMenu* BlackHolePlayerMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new BlackHolePlayerMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
BlackHolePlayerMenu::~BlackHolePlayerMenu() { delete _instance; }