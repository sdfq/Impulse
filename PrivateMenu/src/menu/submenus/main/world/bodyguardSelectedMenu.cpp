#include "stdafx.h"
#include "bodyguardSelectedMenu.h"
#include "bodyguardMenuEditor.h"

using namespace BodyguardSelectedMenuVars;

namespace BodyguardSelectedMenuVars {
	Vars vars;
}

void BodyguardSelectedMenu::Init() {
	setParentSubmenu<BodyguardMenuEditor>();
	setName("", false, false);

	addOption(ToggleOption("Godmode")
		.addToggle(BodyguardMenuEditorVars::vars.SpawnedBodyguards.at(vars.SelectedBodyguard).Godmode)
		.addFunction([] 
			{
				Ped Bodyguard = BodyguardMenuEditorVars::vars.SpawnedBodyguards.at(vars.SelectedBodyguard).Handle;
				if (BodyguardMenuEditorVars::vars.SpawnedBodyguards.at(vars.SelectedBodyguard).Godmode)
				{
					ENTITY::SetEntityInvincible(Bodyguard, true);
				}
				else
				{
					ENTITY::SetEntityInvincible(Bodyguard, false);
				}
			})
		.addTooltip("Is the bodyguard invincible?")
		.addTranslation().addHotkey());

	addOption(ToggleOption("Blip")
		.addToggle(BodyguardMenuEditorVars::vars.SpawnedBodyguards.at(vars.SelectedBodyguard).BlipBool)
		.addFunction([]
			{
				Ped Bodyguard = BodyguardMenuEditorVars::vars.SpawnedBodyguards.at(vars.SelectedBodyguard).Handle;
				if (BodyguardMenuEditorVars::vars.SpawnedBodyguards.at(vars.SelectedBodyguard).BlipBool)
				{
					auto blip = HUD::AddBlipForEntity(Bodyguard); 
					HUD::SetBlipSprite(blip, 480); 
					HUD::SetBlipColour(blip, 63);
				}
				else
				{
					HUD::RemoveBlip(&BodyguardMenuEditorVars::vars.SpawnedBodyguards.at(vars.SelectedBodyguard).Marker);
				}
			})
		.addTooltip("Does it have a blip?")
				.addTranslation().addHotkey());

	addOption(ToggleOption("No Ragdoll")
		.addToggle(BodyguardMenuEditorVars::vars.SpawnedBodyguards.at(vars.SelectedBodyguard).Ragdoll)
		.addFunction([]
			{
				Ped Bodyguard = BodyguardMenuEditorVars::vars.SpawnedBodyguards.at(vars.SelectedBodyguard).Handle;
				if (BodyguardMenuEditorVars::vars.SpawnedBodyguards.at(vars.SelectedBodyguard).Ragdoll)
				{
					PED::SetPedCanRagdoll(Bodyguard, false);
					PED::SetPedCanRagdollFromPlayerImpact(Bodyguard, false);
					PED::SetPedCanBeKnockedOffVehicle(Bodyguard, false);
					PED::SetPedRagdollOnCollision(Bodyguard, false);
				}
				else
				{
					PED::SetPedCanRagdoll(Bodyguard, true);
					PED::SetPedCanRagdollFromPlayerImpact(Bodyguard, true);
					PED::SetPedCanBeKnockedOffVehicle(Bodyguard, true);
					PED::SetPedRagdollOnCollision(Bodyguard, true);
				}
			})
		.addTooltip("Can it ragdoll?")
				.addTranslation().addHotkey());

	addOption(ToggleOption("Invisibility")
		.addToggle(BodyguardMenuEditorVars::vars.SpawnedBodyguards.at(vars.SelectedBodyguard).Invisible)
		.addFunction([]
			{
				Ped Bodyguard = BodyguardMenuEditorVars::vars.SpawnedBodyguards.at(vars.SelectedBodyguard).Handle;
				if (BodyguardMenuEditorVars::vars.SpawnedBodyguards.at(vars.SelectedBodyguard).Invisible)
				{
					ENTITY::SetEntityVisible(Bodyguard, false, false);
				}
				else
				{
					ENTITY::SetEntityVisible(Bodyguard, true, false);
				}
			})
		.addTooltip("Is it invisible?")
				.addTranslation().addHotkey());

	addOption(ButtonOption("Teleport to me")
		.addFunction([] 
			{
				Vector3 pos = GetLocalPlayer().m_coordinates;
				Ped Bodyguard = BodyguardMenuEditorVars::vars.SpawnedBodyguards.at(vars.SelectedBodyguard).Handle;
				ENTITY::SetEntityCoordsNoOffset(Bodyguard, pos.x, pos.y, pos.z, 0, 0, 0);
			})
		.addTooltip("Teleport your bodyguard to you.")
		.addTranslation()
		.addHotkey());

	/*addOption(ButtonOption("Give your outfit")
		.addFunction([] 
			{
				Ped Bodyguard = BodyguardMenuEditorVars::vars.SpawnedBodyguards.at(vars.SelectedBodyguard).Handle;
				PED::ClonePedToTarget(GetLocalPlayer().m_ped, Bodyguard);
			})
		.addTooltip("Give your outfit to the bodyguard. You must be of the same gender to avoid glitches.")
		.addTranslation()
		.addHotkey());*/

	addOption(ButtonOption("Delete bodyguard")
		.addFunction([] 
			{
				GetEntityControl()->DeleteEntity(BodyguardMenuEditorVars::vars.SpawnedBodyguards.at(vars.SelectedBodyguard).Handle);
				std::vector<BodyguardMenuEditorVars::SpawnedBodyguard> NewVector;
				for (auto i = 0; i < BodyguardMenuEditorVars::vars.SpawnedBodyguards.size(); i++)
				{
					if (i != vars.SelectedBodyguard)
					{
						NewVector.push_back(BodyguardMenuEditorVars::vars.SpawnedBodyguards.at(i));
					}
				}
				BodyguardMenuEditorVars::vars.SpawnedBodyguards = NewVector;
				GetSubmenuHandler()->SetSubPrevious(true);
			})
		.addTooltip("Delete the current bodyguard")
		.addTranslation().addHotkey());
}

/*Update once when submenu is opened*/
void BodyguardSelectedMenu::UpdateOnce() {}

/*Update while submenu is active*/
void BodyguardSelectedMenu::Update() 
{
	Ped Bodyguard = BodyguardMenuEditorVars::vars.SpawnedBodyguards.at(vars.SelectedBodyguard).Handle;
	Vector3 Coords = ENTITY::GetEntityCoords(Bodyguard, true);
	GRAPHICS::DrawMarker(21, Coords.x, Coords.y, Coords.z + 1.5f, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f, 0.0f, 0.9f, 0.9f, 0.9f, 0, 255, 255, 200, true, false, 2, true, nullptr, nullptr, false);
}

/*Background update*/
void BodyguardSelectedMenu::FeatureUpdate() {}

/*Singleton*/
BodyguardSelectedMenu* _instance;
BodyguardSelectedMenu* BodyguardSelectedMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new BodyguardSelectedMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
BodyguardSelectedMenu::~BodyguardSelectedMenu() { delete _instance; }