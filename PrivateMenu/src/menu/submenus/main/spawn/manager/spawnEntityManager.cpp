#include "stdafx.h"
#include "spawnEntityManager.h"
#include "../spawnObjectMenu.h"
#include "../spawnPedMenu.h"
#include "../spawnVehicleMenu.h"
#include "spawnVehicleManager.h"
#include "spawnPedManager.h"
#include "spawnObjectManager.h"


using namespace SpawnEntityManagerMenuVars;

namespace SpawnEntityManagerMenuVars {
	Vars vars;

	void PrintText(string text, int font, float x, float y, float scalex, float scaley, int r, int g, int b, int a, bool center, bool outline) {
		HUD::SetTextFont(font);
		HUD::SetTextScale(scalex, scaley);
		HUD::SetTextColour(r, g, b, a);
		HUD::SetTextWrap(0.0f, 1.0f);
		HUD::SetTextCentre(center);
		HUD::SetTextDropshadow(0, 0, 0, 0, 0);
		if (outline)
			HUD::SetTextOutline();
		HUD::BeginTextCommandDisplayText("STRING");
		HUD::AddTextComponentSubstringPlayerName(&text[0u]);
		HUD::EndTextCommandDisplayText(x, y, 0);
		HUD::SetTextDropshadow(0, 0, 0, 0, 0);
	}

	SpawnedEntity Spawned[500];

	int m_selectedEntityToManage = 0;

	char cprintfBuffer[0x1000];
	char* cprintf(const char* fmt, ...) {
		memset(cprintfBuffer, 0, 0x1000);
		va_list ap;
		va_start(ap, fmt);
		vsprintf(cprintfBuffer, fmt, ap);
		va_end(ap);
		return cprintfBuffer;
	}

	void DrawCoords(int pos) {
		Vector3 coords = ENTITY::GetEntityCoords(Spawned[pos].m_handle, false);
		Vector3 myCoords = GetLocalPlayer().m_coordinates;
		GRAPHICS::DrawLine(myCoords.x, myCoords.y, myCoords.z, coords.x, coords.y, coords.z, 255, 255, 0, 255);
	}

	void ShowInfoNextToEntityInWorld(Entity ent, char* text, int height = 0) {
		float xC, yC;
		Vector3 entCoords = ENTITY::GetEntityCoords(ent, 1);
		if (entCoords.Distance(GetLocalPlayer().m_coordinates) < 200) {
			GRAPHICS::GetScreenCoordFromWorldCoord(entCoords.x, entCoords.y, entCoords.z, &xC, &yC);
			PrintText(text, 0, xC, yC, .30, .30, MiscMenuVars::vars.Colorscreenelements.m_r, MiscMenuVars::vars.Colorscreenelements.m_g, MiscMenuVars::vars.Colorscreenelements.m_b, MiscMenuVars::vars.Colorscreenelements.m_a, 1, 1);
		}
	}

	bool RemoveEntityFromDB(Entity Handle) {
		for (auto i = 0; i < 500; i++) {
			if (Spawned[i].m_handle == Handle) {
				LOG_DEBUG("RDB True");
				ENTITY::SetEntityAsMissionEntity(Spawned[i].m_handle, 1, 1);
				ENTITY::DeleteEntity(&Spawned[i].m_handle);
				Spawned[i] = SpawnedEntity();
				return true;
			}
		}
		LOG_DEBUG("RDB False");
		return false;
	}
}

void SpawnEntityManagerMenu::Init() {
	setParentSubmenu<SpawnObjectMenu>();
	setName("Entity manager", true, true);
}

/*Update once when submenu is opened*/
void SpawnEntityManagerMenu::UpdateOnce() {
	clearOptionsOffset(0);

	/*string type = "";
	if (GetSubmenuHandler()->GetPreviousSubmenu() == SpawnVehicleMenu::GetInstance() || GetSubmenuHandler()->GetPreviousSubmenu() == SpawnVehicleManagerMenu::GetInstance()) {
		type = "Vehicles";
	} else if (GetSubmenuHandler()->GetPreviousSubmenu() == SpawnPedMenu::GetInstance() || GetSubmenuHandler()->GetPreviousSubmenu() == SpawnPedManagerMenu::GetInstance()) {
		type = "Peds";
	} else if (GetSubmenuHandler()->GetPreviousSubmenu() == SpawnObjectMenu::GetInstance() || GetSubmenuHandler()->GetPreviousSubmenu() == SpawnObjectManagerMenu::GetInstance()) {
		type = "Objects";
	}

	addOption(SubmenuOption(va("Manage All %s", type.c_str()))
		.addSubmenu<SpawnEntityManagerMenu>()
		.addOnUpdate([&](SubmenuOption* op) { 
			if (type == "Vehicles") {
				op->addSubmenu<SpawnEntityManagerMenu>(); // set to what ever sub manages all vehicles
			} else if (type == "Peds") {
				op->addSubmenu<SpawnEntityManagerMenu>(); // set to what ever sub manages all peds
			} else {
				op->addSubmenu<SpawnEntityManagerMenu>(); // set to what ever sub manages all objects
			}
		}) // dynamicaly update the submenu
		.addTooltip("Manage all of this entity"));

	addOption(BreakOption("Entities"));*/

	for (int i = 0; i < 500; i++) {
		if (Spawned[i].m_taken && ENTITY::DoesEntityExist(Spawned[i].m_handle)) {

			char temp[70];
			vaBuff(temp, 70, "%s %s", Spawned[i].m_type == EntityTypeVehicle ? "[Vehicle]" : Spawned[i].m_type == EntityTypePed ? "[Ped]" : Spawned[i].m_type == EntityTypeMapMod ? "[Map Mod]" : "[Object]", Spawned[i].m_name);

			if (GetSubmenuHandler()->GetPreviousSubmenu() == SpawnVehicleMenu::GetInstance() || GetSubmenuHandler()->GetPreviousSubmenu() == SpawnVehicleManagerMenu::GetInstance()) {
				if (Spawned[i].m_type == EntityTypeVehicle) {
					addOption(SubmenuOption(temp)
						.addSubmenu<SpawnVehicleManagerMenu>()
						.addCurrentOp([i] {DrawCoords(i); })
						.addFunction([=] { m_selectedEntityToManage = i; })
						.addTooltip("Manage this vehicle"));
				}
			} else if (GetSubmenuHandler()->GetPreviousSubmenu() == SpawnPedMenu::GetInstance() || GetSubmenuHandler()->GetPreviousSubmenu() == SpawnPedManagerMenu::GetInstance()) {
				if (Spawned[i].m_type == EntityTypePed) {
					addOption(SubmenuOption(temp)
						.addSubmenu<SpawnPedManagerMenu>()
						.addCurrentOp([i] {DrawCoords(i); })
						.addFunction([=] { m_selectedEntityToManage = i; })
						.addTooltip("Manage this ped"));
				}
			} else if (GetSubmenuHandler()->GetPreviousSubmenu() == SpawnObjectMenu::GetInstance() || GetSubmenuHandler()->GetPreviousSubmenu() == SpawnObjectManagerMenu::GetInstance()) {
				if (Spawned[i].m_type == EntityTypeObject || Spawned[i].m_type == EntityTypeMapMod) {
					addOption(SubmenuOption(temp)
						.addSubmenu<SpawnObjectManagerMenu>()
						.addCurrentOp([i] {DrawCoords(i); })
						.addFunction([=] { m_selectedEntityToManage = i; })
						.addTooltip("Manage this object"));
				}
			}
		}
	}
}

/*Update while submenu is active*/
void SpawnEntityManagerMenu::Update() {}

/*Background update*/
void SpawnEntityManagerMenu::FeatureUpdate() {
	for (int i = 0; i < 500; i++) {

		if (Spawned[i].m_taken && ENTITY::DoesEntityExist(Spawned[i].m_handle)) {

			if (Spawned[i].m_showcreation) {
				int hour, min, sec;
				int ms = (MISC::GetGameTimer() - Spawned[i].m_creation) / 1000;
				hour = ms / 3600;
				min = (ms % 3600) / 60;
				sec = ms % 60;
				if (Spawned[i].m_type == EntityTypeObject) {
					ShowInfoNextToEntityInWorld(Spawned[i].m_handle, cprintf("<font face=\"$gtaCash\" color=\"#09dbd8\">%s</font>\n%s\n%02dh:%02dm:%02ds", Spawned[i].m_name, ENTITY::IsEntityDead(Spawned[i].m_handle, true) ? "~c~[Removed]" : "~g~[Object]", hour, min, sec));
				} else if (Spawned[i].m_type == EntityTypePed) {
					ShowInfoNextToEntityInWorld(Spawned[i].m_handle, cprintf("<font face=\"$gtaCash\" color=\"#09dbd8\">%s</font>\n%s\n%02dh:%02dm:%02ds", Spawned[i].m_name, ENTITY::IsEntityDead(Spawned[i].m_handle, true) ? "~c~[Dead]" : "~g~[Alive]", hour, min, sec));
				} else if (Spawned[i].m_type == EntityTypeVehicle) {
					ShowInfoNextToEntityInWorld(Spawned[i].m_handle, cprintf("<font face=\"$gtaCash\" color=\"#09dbd8\">%s</font>\n%s\n%02dh:%02dm:%02ds", Spawned[i].m_name, ENTITY::IsEntityDead(Spawned[i].m_handle, true) ? "~c~[Broken]" : "~g~[Working]", hour, min, sec));
				}
			}
		}
	}
}

/*Singleton*/
SpawnEntityManagerMenu* _instance;
SpawnEntityManagerMenu* SpawnEntityManagerMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new SpawnEntityManagerMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
SpawnEntityManagerMenu::~SpawnEntityManagerMenu() { delete _instance; }