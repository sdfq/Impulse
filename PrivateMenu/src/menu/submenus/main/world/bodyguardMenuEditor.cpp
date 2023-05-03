#include "stdafx.h"
#include "bodyguardMenuEditor.h"
#include <menu\submenus\main\world\bodyguardMenu.h>
#include <menu\submenus\main\world\bodyguardSelectedMenu.h>

using namespace BodyguardMenuEditorVars;

namespace BodyguardMenuEditorVars {
	Vars vars;
}

void BodyguardMenuEditor::Init() {
	setParentSubmenu<BodyguardMenu>();
	setName("Edit your bodyguards", true, true);
	
	addOption(ButtonOption("Teleport all to me")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addFunction([] 
			{
				Vector3 pos = GetLocalPlayer().m_coordinates;
				for (auto i = 0; i < vars.SpawnedBodyguards.size(); i++)
				{
					Ped Bodyguard = vars.SpawnedBodyguards.at(i).Handle;
					ENTITY::SetEntityCoordsNoOffset(Bodyguard, pos.x, pos.y, pos.z, 0, 0, 0);
				}
			})
		.addTooltip("Teleport all your bodyguards to you.")
		.addHotkey()
		.addTranslation());
}

/*Update once when submenu is opened*/
void BodyguardMenuEditor::UpdateOnce() {}

/*Update while submenu is active*/
void BodyguardMenuEditor::Update() 
{
	clearOptionsOffset(1);
	for (auto i = 0; i < vars.SpawnedBodyguards.size(); i++)
	{
		addOption(SubmenuOption(vars.SpawnedBodyguards.at(i).Model.Get())
			.addTooltip("Edit this bodyguard")
			.addRequirement([] { return GetAuth()->IsVIP(); })
			.addSubmenu<BodyguardSelectedMenu>()
			.addFunction([=]
				{
					BodyguardSelectedMenuVars::vars.SelectedBodyguard = i;
				}));
	}
}

/*Background update*/
void BodyguardMenuEditor::FeatureUpdate() {}

/*Singleton*/
BodyguardMenuEditor* _instance;
BodyguardMenuEditor* BodyguardMenuEditor::GetInstance() {
	if (_instance == nullptr) {
		_instance = new BodyguardMenuEditor();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
BodyguardMenuEditor::~BodyguardMenuEditor() { delete _instance; }