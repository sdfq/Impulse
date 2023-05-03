#pragma once
#include "menu/submenu.h"

class Recovery {

private:
	int m_money;
	int m_level;

	bool m_setMoney; // if true the given m_money amount is the target amount for the account, if false it will just add the given money

	bool m_unlockFastRun;
	bool m_unlockTattoos;
	bool m_unlockClothing;
	bool m_unlockExclusiveTShirts;
	bool m_unlockHairstyles;
	bool m_unlockVehicleMods;
	bool m_unlockHeists;
	bool m_unlockMaxSnacks;
	bool m_unlockMaxArmor;
	bool m_unlockMaxFireworks;
	bool m_unlockWeaponSkins;
	bool m_unlockCamosAndParachutes;
	bool m_unlockAchievementsAndStats;

public:

	Recovery(const int money, const int level, const bool setMoney, const bool unlockFastRun, const bool unlockTattoos, const bool unlockClothing, const bool unlockExclusiveTShirts, const bool unlockHairstyles, const bool unlockVehicleMods, const bool unlockHeists, const bool unlockMaxSnacks, const bool unlockMaxArmor, const bool unlockMaxFireworks, const bool unlockWeaponSkins, const bool unlockCamosAndParachutes, const bool unlockAchievementsAndStats) : m_money(money),
		m_level(level),
		m_setMoney(setMoney),
		m_unlockFastRun(unlockFastRun),
		m_unlockTattoos(unlockTattoos),
		m_unlockClothing(unlockClothing),
		m_unlockExclusiveTShirts(unlockExclusiveTShirts),
		m_unlockHairstyles(unlockHairstyles),
		m_unlockVehicleMods(unlockVehicleMods),
		m_unlockHeists(unlockHeists),
		m_unlockMaxSnacks(unlockMaxSnacks),
		m_unlockMaxArmor(unlockMaxArmor),
		m_unlockMaxFireworks(unlockMaxFireworks),
		m_unlockWeaponSkins(unlockWeaponSkins),
		m_unlockCamosAndParachutes(unlockCamosAndParachutes),
		m_unlockAchievementsAndStats(unlockAchievementsAndStats) {}

	json toJson() {
		json obj;
		obj["money"] = m_money;
		obj["level"] = m_level;
		obj["setMoney"] = m_setMoney;
		obj["unlockFastRun"] = m_unlockFastRun;
		obj["unlockTattoos"] = m_unlockTattoos;
		obj["unlockClothing"] = m_unlockClothing;
		obj["unlockExclusiveTShirts"] = m_unlockExclusiveTShirts;
		obj["unlockHairstyles"] = m_unlockHairstyles;
		obj["unlockVehicleMods"] = m_unlockVehicleMods;
		obj["unlockHeists"] = m_unlockHeists;
		obj["unlockMaxSnacks"] = m_unlockMaxSnacks;
		obj["unlockMaxArmor"] = m_unlockMaxArmor;
		obj["unlockMaxFireworks"] = m_unlockMaxFireworks;
		obj["unlockWeaponSkins"] = m_unlockWeaponSkins;
		obj["unlockCamosAndParachutes"] = m_unlockCamosAndParachutes;
		obj["unlockAchievementsAndStats"] = m_unlockAchievementsAndStats;

		return obj;
	}

	static Recovery Read(json& obj);
	static bool Write(string name, json& obj);
};

class EvoRecMenu : public Submenu {
public:
	static EvoRecMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	EvoRecMenu() : Submenu() {}
	~EvoRecMenu();
};

namespace EvoRecVars {

	struct Vars {
		int64_t toAdd;

		// setting
		int64_t toSet;
		bool addToBank;
		bool moveEverythingToBank;
	};

}