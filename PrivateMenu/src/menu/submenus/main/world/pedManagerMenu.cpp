#include "stdafx.h"
#include "pedManagerMenu.h"
#include "../worldMenu.h"

using namespace PedManagerMenuVars;

namespace PedManagerMenuVars {
	Vars vars;
	vector<Ped> nearbyPeds;

	void UpdateNearbyPeds() {
		static set<Ped> lastSeenPeds;
		nearbyPeds.clear();
		const int numElements = 20;
		const int arrSize = numElements * 2 + 2;

		Ped *peds = new Ped[arrSize];
		peds[0] = numElements;
		int found = PED::GetPedNearbyPeds(GetLocalPlayer().m_ped, peds, -1);

		for (int i = 0; i < found; i++) {
			int offsettedID = i * 2 + 2;

			if (!ENTITY::DoesEntityExist(peds[offsettedID])) continue;

			Ped xped = peds[offsettedID];

			bool inSet = lastSeenPeds.find(xped) != lastSeenPeds.end();
			if (!inSet) {
				lastSeenPeds.insert(xped);
			}
		}

		for (std::set<Ped>::iterator it = lastSeenPeds.begin(); it != lastSeenPeds.end();) {
			if (!ENTITY::DoesEntityExist(*it)) {
				lastSeenPeds.erase(it++);
			} else {
				nearbyPeds.push_back(*it);
				++it;
			}
		}

		delete peds;
	}

	void RunPedManagerWorker(PoolActions task, int player) {
		vector<Vehicle> poolPeds;
		if (vars.usepools) {
			PedPool::Update();
			poolPeds = PedPool::GetPeds();
		} else UpdateNearbyPeds();
		for (Ped& ped : vars.usepools ? poolPeds : nearbyPeds) {
			if (ped == GetLocalPlayer().m_ped) continue;
			GetEntityControl()->VerySimpleRequestControl(ped);
			Vector3 PedCoords = ENTITY::GetEntityCoords(ped, 0);
			switch (task) {
				case PED_HOSTILEPEDS: WEAPON::GiveWeaponToPed(ped, 0x7FD62962, 9999, true, true); BRAIN::TaskCombatPed(ped, GetPlayer(player).m_ped, 0, 16); PED::SetPedKeepTask(ped, true); break;
				case PED_ESP: GetRenderer()->DrawLine(GetLocalPlayer().m_coordinates.x, GetLocalPlayer().m_coordinates.y, GetLocalPlayer().m_coordinates.z, PedCoords.x, PedCoords.y, PedCoords.z, { 0, 255, 0, 255 }); break;
				case PED_CLEARTASKS:BRAIN::ClearPedTasksImmediately(ped); break;
				case PED_JUMP: BRAIN::TaskJump(ped, 1, 1, 1);	break;
				case PED_COWER:BRAIN::TaskCower(ped, 5000); break;
				case PED_HANDSUP: BRAIN::TaskHandsUp(ped, 5000, 0, 0, 0); break;
				case PED_WANDER: BRAIN::TaskWanderInArea(ped, PedCoords.x, PedCoords.y, PedCoords.z, 500, 10, 1);	break;
				case PED_COMETOME: BRAIN::TaskGoToEntity(ped, GetLocalPlayer().m_ped, -1, 2.0, 100, 2.0f, 0); break;
				case PED_KILL:PED::ApplyDamageToPed(ped, 30000, true); break;
				case PED_EXPLODE: FIRE::AddExplosion(PedCoords.x, PedCoords.y, PedCoords.z, 2, 2000, 1, 0, 0, 0); break;
				case PED_CLONE: PED::ClonePed(ped, ENTITY::GetEntityHeading(ped), 1, 0); break;
				case PED_DELETE: GetEntityControl()->SimpleDeleteEntity(ped); break;
				case PED_SHRINK: PED::SetPedConfigFlag(ped, 223, 1); break;
				case PED_ENLARGE: PED::SetPedConfigFlag(ped, 223, 0); break;
				case PED_LAUNCH: Utils::ApplyForceToEntity(ped, 0, 0, 20); break;
				case PED_CLONECREATIONPREVENTION: {
					if (ENTITY::GetEntityModel(ped) == ENTITY::GetEntityModel(GetLocalPlayer().m_ped)) {
						if (!PED::IsPedAPlayer(ped)) {
							if (PedCoords.Distance(GetLocalPlayer().m_coordinates) < 20) {
								ENTITY::SetEntityCoords(ped, 0, 0, 0, 0, 0, 0, 1);
								GetEntityControl()->DeleteEntity(ped);
							}
						}
					}
					break;
				}
				case PED_ATTACHMENTPREVENTION: {
					if (ENTITY::GetEntityAttachedTo(ped) == GetLocalPlayer().m_ped) {
						ENTITY::DetachEntity(ped, 1, 1);
						Vector3 Coords = { 0, 0, 0 };
						ENTITY::SetEntityCoords(ped, Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
						GetEntityControl()->DeleteEntity(ped);
					}
					break;
				}
			}
		}
	}
}

void PedManagerMenu::Init() {
	setParentSubmenu<WorldMenu>();
	setName("Ped manager", true, true);

	addOption(ToggleOption("Use ped pools (bigger ranger)")
		.addToggle(vars.usepools)
		.addHotkey().addTranslation()
		.addTooltip("Use entity pools to extend the range of these options"));

	addOption(ToggleOption("Ped ESP")
		.addToggle(vars.esp)
		.addHotkey().addTranslation()
		.addTooltip("Extra sensory perception"));

	addOption(ButtonOption("Kill peds")
		.addFunction([] {RunPedManagerWorker(PED_KILL); })
		.addHotkey().addTranslation()
		.addTooltip("Kill peds"));

	addOption(ButtonOption("Clone peds")
		.addFunction([] {RunPedManagerWorker(PED_CLONE); })
		.addHotkey().addTranslation()
		.addTooltip("Clone peds"));

	addOption(ButtonOption("Delete peds")
		.addFunction([] {RunPedManagerWorker(PED_DELETE); })
		.addHotkey().addTranslation()
		.addTooltip("Delete peds"));

	addOption(ButtonOption("Shrink peds")
		.addFunction([] {RunPedManagerWorker(PED_SHRINK); })
		.addHotkey().addTranslation()
		.addTooltip("Shrink peds"));

	addOption(ButtonOption("Enlarge peds")
		.addFunction([] {RunPedManagerWorker(PED_ENLARGE); })
		.addHotkey().addTranslation()
		.addTooltip("Enlarge peds"));

	addOption(ButtonOption("Launch peds")
		.addFunction([] {RunPedManagerWorker(PED_LAUNCH); })
		.addHotkey().addTranslation()
		.addTooltip("Launch peds"));

	addOption(BreakOption("Tasks").addTranslation());

	addOption(ButtonOption("Clear ped tasks")
		.addFunction([] {RunPedManagerWorker(PED_CLEARTASKS); })
		.addHotkey().addTranslation()
		.addTooltip("Clear ped tasks"));

	addOption(ButtonOption("Peds jump")
		.addFunction([] {RunPedManagerWorker(PED_JUMP); })
		.addHotkey().addTranslation()
		.addTooltip("Peds jump"));

	addOption(ButtonOption("Peds cower")
		.addFunction([] {RunPedManagerWorker(PED_COWER); })
		.addHotkey().addTranslation()
		.addTooltip("Peds cower"));

	addOption(ButtonOption("Peds hands up")
		.addFunction([] {RunPedManagerWorker(PED_HANDSUP); })
		.addHotkey().addTranslation()
		.addTooltip("Peds hands up"));

	addOption(ButtonOption("Peds wander")
		.addFunction([] {RunPedManagerWorker(PED_WANDER); })
		.addHotkey().addTranslation()
		.addTooltip("Peds wander"));

	addOption(ButtonOption("Peds come to me")
		.addFunction([] {RunPedManagerWorker(PED_COMETOME); })
		.addHotkey().addTranslation()
		.addTooltip("Peds come to me"));
}

/*Update once when submenu is opened*/
void PedManagerMenu::UpdateOnce() {}

/*Update while submenu is active*/
void PedManagerMenu::Update()
{
	if (vars.esp) RunPedManagerWorker(PED_ESP);
}

/*Background update*/
void PedManagerMenu::FeatureUpdate() {}

/*Singleton*/
PedManagerMenu* _instance;
PedManagerMenu* PedManagerMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new PedManagerMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
PedManagerMenu::~PedManagerMenu() { delete _instance; }