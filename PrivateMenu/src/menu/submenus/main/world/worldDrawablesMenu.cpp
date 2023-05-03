#include "stdafx.h"
#include "worldDrawablesMenu.h"
#include "../worldMenu.h"
#include "editClosestDrawableMenu.h"

using namespace WorldDrawablesVars;

namespace WorldDrawablesVars {
	Vars vars;

	bool IsValidEntity(uint64_t entityAddress) {
		uint64_t entityClass = *(uint64_t*)entityAddress;
		for (int i = 0; i < vars.entityClasses.size(); i++)
			if (entityClass == vars.entityClasses[i]) return true;
		return false;
	}

	float GetDistance(float x1, float x2, float x3, float y1, float y2, float y3) {
		float dx = y1 - x1;
		float dy = y2 - x2;
		float dz = y3 - x3;

		return sqrt((float)((dx * dx) + (dy * dy) + (dz * dz)));
	}

	void RunTaskOnAll(eTasks task) {
		if (vars.entityPoolPointer != nullptr) {
			uint64_t poolAddress = *vars.entityPoolPointer;
			if (poolAddress) {
				int entityPoolSize = *(int*)(poolAddress - 0xC) / 8;
				float closestDrawableDistance = FLT_MAX;
				for (int i = 0; i < entityPoolSize; i++) {
					UINT64 entityAddress = *(UINT64*)(poolAddress + (i * 8));
					if (entityAddress && !IsBadReadPtr((void*)entityAddress, 8) && IsValidEntity(entityAddress)) {
						CDrawable* entity = (CDrawable*)entityAddress;
						if (entity->IsDrawable()) {
							Vector3 myPos = GetLocalPlayer().m_coordinates;
							Vector3 pos = entity->GetPosition();
							switch (task) {
								case TeleportAllToMe:
									entity->SetPosition(myPos);
									break;
								case ESP: {
									GRAPHICS::DrawLine(myPos.x, myPos.y, myPos.z, pos.x, pos.y, pos.z, 255, 0, 0, 255);
									break;
								}
								case CalculateClosest: {
									float Distance = GetDistance(myPos.x, myPos.y, myPos.z, pos.x, pos.y, pos.z);
									if (Distance < closestDrawableDistance) {
										closestDrawableDistance = Distance;
										vars.closestDrawable = entity;
										vars.closestDrawableAddress = entityAddress;
									}

									break;
								}
								case x5Scale:
									entity->AddToScale(5.0f);
									break;
								case normalScale:
									entity->SetScale(1.0f);
									break;
							}
						}
					}
				}
			}
		}
	}
}

void WorldDrawablesMenu::Init() {
	setParentSubmenu<WorldMenu>();
	setName("Drawable editor", true, true);

	addOption(ToggleOption("ESP").addTranslation()
		.addToggle(vars.esp).addHotkey().canBeSaved()
		.addTooltip("Show lines to every drawable in your area"));

	addOption(SubmenuOption("Edit closest drawable")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addSubmenu<EditClosestDrawableMenu>().addHotkey()
		.addFunction([] {
		EditClosestDrawableMenuVars::vars.position = Vector3();
		vars.esp = false; // cache
		RunTaskOnAll(CalculateClosest);
		Vector3 myPos = GetLocalPlayer().m_coordinates;
		if (vars.closestDrawable != nullptr) {
			Vector3 pos = vars.closestDrawable->GetPosition();
			GRAPHICS::DrawLine(myPos.x, myPos.y, myPos.z, pos.x, pos.y, pos.z, 255, 0, 0, 255);
		}
	}).addTranslation().addTooltip("Edit the closest drawable")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addOnUpdate([](SubmenuOption* idk) {
		RunTaskOnAll(CalculateClosest);
		Vector3 myPos = GetLocalPlayer().m_coordinates;
		if (vars.closestDrawable != nullptr) {
			Vector3 pos = vars.closestDrawable->GetPosition();
			GRAPHICS::DrawLine(myPos.x, myPos.y, myPos.z, pos.x, pos.y, pos.z, 255, 0, 0, 255);
		}
	}).addTranslation());

	addOption(ButtonOption("Teleport all to me")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addFunction([] { RunTaskOnAll(TeleportAllToMe); }).addHotkey()
		.addTooltip("Teleport every drawable in your area to you").addTranslation());

	addOption(ButtonOption("x5 scale")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addFunction([] { RunTaskOnAll(x5Scale); }).addHotkey()
		.addTooltip("Set the scale of every drawable in the area to you").addTranslation());

	addOption(ButtonOption("Normal scale")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addFunction([] { RunTaskOnAll(normalScale); }).addHotkey()
		.addTooltip("Set the scale of every drawable in the area to you back to normal").addTranslation());
}

/*Update once when submenu is opened*/
void WorldDrawablesMenu::UpdateOnce() {}

/*Update while submenu is active*/
void WorldDrawablesMenu::Update() { }

/*Background update*/
void WorldDrawablesMenu::FeatureUpdate() {
	if (vars.esp) RunTaskOnAll(ESP);
}

/*Singleton*/
WorldDrawablesMenu* _instance;
WorldDrawablesMenu* WorldDrawablesMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new WorldDrawablesMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
WorldDrawablesMenu::~WorldDrawablesMenu() { delete _instance; }