#include "stdafx.h"
#include "editClosestDrawableMenu.h"
#include "worldDrawablesMenu.h"

using namespace EditClosestDrawableMenuVars;

namespace EditClosestDrawableMenuVars {
	Vars vars;
}

void EditClosestDrawableMenu::Init() {
	setParentSubmenu<WorldDrawablesMenu>();
	setName("Edit closest drawable", true, true);

	addOption(NumberOption<float>(SCROLL, "Accuracy")
		.addNumber(vars.accuracy, "%.1f", 1.0f).addMin(0.1f).addMax(50.0f)
		.addTooltip("Edit the accuracy for the position editor").addTranslation());

	addOption(NumberOption<float>(SCROLL, "Position - Horizontal (X)").addTranslation()
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(vars.position.x, "%.3f", vars.accuracy).addMin(-100000.f).addMax(100000.f); })
		.addFunction([] {
		Vector3 pos = WorldDrawablesVars::vars.closestDrawable->GetPosition();
			pos.x = vars.position.x;
			WorldDrawablesVars::vars.closestDrawable->SetPosition(pos);
		}).addTooltip("X position"));

	addOption(NumberOption<float>(SCROLL, "Position - Vertical (Y)").addTranslation()
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(vars.position.y, "%.3f", vars.accuracy).addMin(-100000.f).addMax(100000.f); })
		.addFunction([] {
			Vector3 pos = WorldDrawablesVars::vars.closestDrawable->GetPosition();
			pos.y = vars.position.y;
			WorldDrawablesVars::vars.closestDrawable->SetPosition(pos);
		}).addTooltip("Y position"));

	addOption(NumberOption<float>(SCROLL, "Position - Height (Z)").addTranslation()
		.addOnUpdate([](NumberOption<float>* option) {option->addNumber(vars.position.z, "%.3f", vars.accuracy).addMin(-100000.f).addMax(100000.f); })
		.addFunction([] {
		Vector3 pos = WorldDrawablesVars::vars.closestDrawable->GetPosition();
			pos.z = vars.position.z;
			WorldDrawablesVars::vars.closestDrawable->SetPosition(pos);
		}).addTooltip("Z position"));

	addOption(ButtonOption("Teleport to me").addTranslation()
		.addFunction([] { WorldDrawablesVars::vars.closestDrawable->SetPosition(GetLocalPlayer().m_coordinates); })
		.addTooltip("Teleport drawable to me"));

	addOption(NumberOption<float>(SCROLL, "Scale").addTranslation()
		.addNumber(vars.scale, "%.1f", 0.1f).addMin(0.0f).addMax(50.0f)
		.addFunction([] { WorldDrawablesVars::vars.closestDrawable->SetScale(vars.scale); })
		.addTooltip("Change drawable scale"));

	addOption(NumberOption<int>(SCROLL, "LOD").addTranslation()
		.addNumber(vars.lod, "%i", 1).addMin(-10000).addMax(10000)
		.addFunction([] { WorldDrawablesVars::vars.closestDrawable->SetLod(vars.lod); })
		.addTooltip("Change drawable level of detail"));
}

/*Update once when submenu is opened*/
void EditClosestDrawableMenu::UpdateOnce() {
}

/*Update while submenu is active*/
void EditClosestDrawableMenu::Update() {
	if (vars.position == Vector3()) {
		vars.position = WorldDrawablesVars::vars.closestDrawable->GetPosition();
		vars.scale = WorldDrawablesVars::vars.closestDrawable->GetEstimatedScale();
		vars.lod = WorldDrawablesVars::vars.closestDrawable->GetLod();
		WorldDrawablesVars::vars.esp = false; // we need to have a single esp for closest (cache this later)
	}

	Vector3 myPos = GetLocalPlayer().m_coordinates;
	Vector3 pos = WorldDrawablesVars::vars.closestDrawable->GetPosition();

	GRAPHICS::DrawLine(myPos.x, myPos.y, myPos.z, pos.x, pos.y, pos.z, 255, 0, 0, 255);

	GetWindowManager()->m_drawableLogComp.clear();
	GetWindowManager()->m_drawableLogComp.addLine(va("Entity Address: 0x%llx", &WorldDrawablesVars::vars.closestDrawableAddress));
	GetWindowManager()->m_drawableLogComp.addLine(va("Entity Handle: 0x%X", PoolManager::AddEntityToPool(WorldDrawablesVars::vars.closestDrawableAddress)));
	GetWindowManager()->m_drawableLogComp.addLine(va("X: %.3f", WorldDrawablesVars::vars.closestDrawable->GetPosition().x));
	GetWindowManager()->m_drawableLogComp.addLine(va("Y: %.3f", WorldDrawablesVars::vars.closestDrawable->GetPosition().y));
	GetWindowManager()->m_drawableLogComp.addLine(va("Z: %.3f", WorldDrawablesVars::vars.closestDrawable->GetPosition().z));
	GetWindowManager()->m_drawableLogComp.addLine(va("Width: %.2f", WorldDrawablesVars::vars.closestDrawable->GetScale().x));
	GetWindowManager()->m_drawableLogComp.addLine(va("Height: %.2f", WorldDrawablesVars::vars.closestDrawable->GetScale().y));
	GetWindowManager()->m_drawableLogComp.addLine(va("Estimated Scale: %.2f", WorldDrawablesVars::vars.closestDrawable->GetEstimatedScale()));
	GetWindowManager()->m_drawableLogComp.addLine(va("LOD Distance: %i", WorldDrawablesVars::vars.closestDrawable->GetLod()));
}

/*Background update*/
void EditClosestDrawableMenu::FeatureUpdate() {}

/*Singleton*/
EditClosestDrawableMenu* _instance;
EditClosestDrawableMenu* EditClosestDrawableMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new EditClosestDrawableMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
EditClosestDrawableMenu::~EditClosestDrawableMenu() { delete _instance; }