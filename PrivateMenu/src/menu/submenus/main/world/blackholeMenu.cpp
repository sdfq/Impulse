#include "stdafx.h"
#include "blackholeMenu.h"
#include "menu/submenus/main/worldMenu.h"
#include "blackHolePlayerMenu.h"

using namespace BlackholeMenuVars;

namespace BlackholeMenuVars {
	Vars vars;

	ScrollStruct<BlackholePerformance> Precision[] = {
		TranslationString("Weak", true), BLACKHOLE_PRECISION_WEAK,
		TranslationString("Medium", true), BLACKHOLE_PRECISION_MEDIUM,
		TranslationString("High", true), BLACKHOLE_PRECISION_HIGH
	};
}

void BlackholeMenu::Init() {
	setParentSubmenu<WorldMenu>();
	setName("Blackhole", true, true);

	addOption(SubmenuOption("Attach to players")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addSubmenu<BlackHolePlayerMenu>()
		.addTooltip("Attach the black/white hole to players."));

	// Location options
	addOption(ToggleOption("Enabled").addToggle(vars.active).addRequirement([] { return GetAuth()->IsVIP(); }).addHotkey().addTranslation().addTooltip("Enable the blackhole"));

	addOption(BreakOption("Location").addTranslation());

	addOption(NumberOption<float>(SCROLL, "X")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addNumber(vars.position.x, "%.2f", 5.0f)
		.addTranslation()
		.addTooltip("The x coordinate of the blackhole"));

	addOption(NumberOption<float>(SCROLL, "Y")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addNumber(vars.position.y, "%.2f", 5.0f)
		.addTranslation()
		.addTooltip("The y coordinate of the blackhole"));

	addOption(NumberOption<float>(SCROLL, "Z")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addNumber(vars.position.z, "%.2f", 5.0f)
		.addTranslation()
		.addTooltip("The z coordinate of the blackhole"));

	addOption(ButtonOption("Set it to my location")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addFunction([] {
		const auto position = ENTITY::GetEntityCoords(PLAYER::PlayerPedId(), !ENTITY::IsEntityDead(PLAYER::PlayerPedId(), false));
		vars.position.x = position.x;
		vars.position.y = position.y;
		vars.position.z = position.z + 0.5f;
	}).addTranslation().addHotkey()
		.addTooltip("Sets the blackhole position to your position. (Everything will fly towards you)"));

	addOption(ButtonOption("Set it above my head")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addFunction([] {
		const auto position = ENTITY::GetEntityCoords(PLAYER::PlayerPedId(), !ENTITY::IsEntityDead(PLAYER::PlayerPedId(), false));
		vars.position.x = position.x;
		vars.position.y = position.y;
		vars.position.z = position.z + 100.0f;
	}).addTranslation().addHotkey()
		.addTooltip("Sets the blackhole position above you. (Everything will fly above you)"));

	// Attraction settings
	addOption(BreakOption("Attraction Settings").addTranslation());

	addOption(ToggleOption(va("Vehicles", VehiclePool::GetVehicles().size()))
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.attractVehicles).addTranslation().canBeSaved().addHotkey()
		.addTooltip("Attracts all vehicles except player vehicles"));

	addOption(ToggleOption(va("Pedestrians", PedPool::GetPeds().size()))
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.attractPedestrians).addTranslation().canBeSaved().addHotkey()
		.addTooltip("Attracts all pedestrians"));

	addOption(ToggleOption(va("Objects", ObjectPool::GetObjects().size()))
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.attractObjects).addTranslation().canBeSaved().addHotkey()
		.addTooltip("Attracts all object that aren't frozen (e.g. traffic lights) [May be unstable for some]"));

	addOption(ToggleOption("Player Vehicles")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.attractPlayerVehicles).addTranslation().canBeSaved().addHotkey()
		.addTooltip("Attracts all vehicles from other players"));

	addOption(NumberOption<float>(SCROLL, "Strength")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addNumber(vars.strength, "%.2f", 0.1f).addMin(0.0f).addMax(100.0f)
		.addTranslation().canBeSaved().addHotkey()
		.addTooltip("The strength of the blackhole. (Low = Entities \"hover\" in the air, High = They will form a ball"));

	// Other settings
	addOption(BreakOption("Miscellaneous").addTranslation());

	addOption(ToggleOption("Whitehole")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.whitehole).addTranslation().canBeSaved().addHotkey()
		.addTooltip("Push entities away from the location"));

	addOption(ToggleOption("Explosions at location")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.explosions).addTranslation().canBeSaved().addHotkey()
		.addTooltip("Spawns random explosions at the blackhole location"));

	addOption(ToggleOption("Draw Marker").addToggle(vars.drawMarker)
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addTranslation().canBeSaved().addHotkey()
		.addTooltip("Draw a red marker at the blackhole position"));

	addOption(ToggleOption("Blackhole <-> Whitehole Switch")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addToggle(vars.typeSwitch).addTranslation().canBeSaved()
		.addTooltip("Automatically toggles between white and blackhole."));

	addOption(NumberOption<int>(SCROLL, "Switch Delay").addTranslation().canBeSaved()
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addNumber(vars.typeSwitchDelay, "%d", 50).addMin(1).addMax(10000)
		.addTooltip("Set the delay of switching to whitehole and back"));

	addOption(ScrollOption<BlackholePerformance>(SCROLL, "Precision")
		.addRequirement([] { return GetAuth()->IsVIP(); })
		.addScroll(vars.performanceIndex, 0, NUMOF(Precision) - 1, Precision)
		.addOnUpdate([] { vars.poolIndex = 0; vars.entityProcessQueue.clear(); vars.originalEntityProcessQueueSize = 0; })
		.addTranslation().canBeSaved()
		.addTooltip("Set how precise the blackhole should be. (Higher = Better but less FPS)"));
}

/*Update once when submenu is opened*/
void BlackholeMenu::UpdateOnce() {}

/*Update while submenu is active*/
void BlackholeMenu::Update() {}

/*Background update*/
void BlackholeMenu::FeatureUpdate() {
	static int TIMER;
	if (vars.active) {
		Utils::DoTimedFunction(&TIMER, 500, [] { GetFiberPool()->DoJob([] { PoolManager::Update(); }); });

		auto entitiesInPool = EntityPool::GetEntities();
		std::vector<Entity> entitiesToProcess;

		switch (Precision[vars.performanceIndex].m_result) {

		case BLACKHOLE_PRECISION_HIGH:
			entitiesToProcess = entitiesInPool;
			break;

		case BLACKHOLE_PRECISION_MEDIUM:
			if (vars.poolIndex != 0) {
				entitiesToProcess = std::vector<Entity>(&entitiesInPool[vars.poolIndex], &entitiesInPool[entitiesInPool.size() - 1]);
				vars.poolIndex = 0;
			} else {
				const auto half = entitiesInPool.size() / 2 + entitiesInPool.size() % 2;
				entitiesToProcess = std::vector<Entity>(&entitiesInPool[0], &entitiesInPool[half]);
				vars.poolIndex = half;
			}
			break;

		case BLACKHOLE_PRECISION_WEAK:
			if (vars.entityProcessQueue.empty()) {
				vars.entityProcessQueue = entitiesInPool;
				vars.originalEntityProcessQueueSize = vars.entityProcessQueue.size();
			}

			entitiesToProcess = std::vector<Entity>(&vars.entityProcessQueue[0], &vars.entityProcessQueue[vars.entityProcessQueue.size() > 10 ? 9 : vars.entityProcessQueue.size() - 1]);

			vars.entityProcessQueue.erase(vars.entityProcessQueue.begin(), vars.entityProcessQueue.begin() + (vars.entityProcessQueue.size() > 10 ? 10 : vars.entityProcessQueue.size()));

			break;
		}

		vars.currentProcessSize = entitiesToProcess.size();

		for (auto entity : entitiesToProcess) {
			if (!(vars.attractVehicles || vars.attractPlayerVehicles) && ENTITY::IsEntityAVehicle(entity)) continue;
			if (!vars.attractPedestrians && ENTITY::IsEntityAPed(entity) || ENTITY::IsEntityAPed(entity) && PED::IsPedAPlayer(entity)) continue;
			if (!vars.attractObjects && ENTITY::IsEntityAnObject(entity)) continue;

			// Check if entity is owned by a player and then check if attractPlayerVehicles is turned on and the user is VIP
			if ((vars.attractVehicles || vars.attractPlayerVehicles) && ENTITY::IsEntityAVehicle(entity)) {
				auto owner = 0;
				if (VEHICLE::_GetVehicleOwner(entity, &owner) && ENTITY::IsEntityAPed(owner) && PED::IsPedAPlayer(owner) && (!vars.attractPlayerVehicles || !GetAuth()->IsVIP())) continue;
			}

			// Request and check control
			GetEntityControl()->VerySimpleRequestControl(entity);
			if (!NETWORK::NetworkHasControlOfEntity(entity)) continue;

			// Ready to process entity
			auto position = ENTITY::GetEntityCoords(entity, !ENTITY::IsEntityDead(entity, 0));
			const auto force = (vars.whitehole ? position - vars.position : vars.position - position) / 25.0f * vars.strength;

			ENTITY::ApplyForceToEntity(entity, 1, force.x, force.y, force.z, 0.0f, 0.0f, 0.0f, 0, false, true, true, false, true);
		}

		if (vars.explosions) {
			// Random offsets make it look nicer. pew.
			const auto xOffset = MISC::GetRandomFloatInRange(-10.0f, 10.0f);
			const auto yOffset = MISC::GetRandomFloatInRange(-10.0f, 10.0f);
			const auto zOffset = MISC::GetRandomFloatInRange(-10.0f, 10.0f);
			FIRE::AddExplosion(vars.position.x + xOffset, vars.position.y + yOffset, vars.position.z + zOffset, 32 /* PlaneRocket */, 500.0f, true, false, true, false);
		}

		if (vars.typeSwitch) {
			static int timer;
			Utils::DoTimedFunction(&timer, vars.typeSwitchDelay, [] { vars.whitehole ^= 1; });
		}
	}

	if (vars.drawMarker) {
		GRAPHICS::DrawMarker(21, vars.position.x, vars.position.y, vars.position.z, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f, 0.0f, 0.9f, 0.9f, 0.9f, 255, 0, 0, 255, true, false, 2, true, nullptr, nullptr, false);
	}
}

/*Singleton*/
BlackholeMenu* _instance;
BlackholeMenu* BlackholeMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new BlackholeMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
BlackholeMenu::~BlackholeMenu() { delete _instance; }