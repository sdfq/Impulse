#pragma once

class VehicleOption : public Option {
private:
	int m_mod;

	int m_modOffset;
	int m_modSize;

	DWORD m_scrollSpeed;

	/*Scrolling*/
	bool leftDisabled = false;
	bool rightDisabled = false;
	int leftTimer = 0;
	int rightTimer = 0;

public:
	VehicleOption(String name) : Option(name), m_scrollSpeed(100) {}

	VehicleOption& addMod(int mod) {
		m_mod = mod;
		return *this;
	}

	VehicleOption& checkVisibility() {
		m_visible = GetLocalPlayer().m_isInVehicle && VEHICLE::GetNumVehicleMods(GetLocalPlayer().m_vehicle, m_mod);
		return *this;
	}

	VehicleOption& addRequirement(function<bool()> func) {
		m_requirement = func;
		return *this;
	}

	VehicleOption& addHotkey() {
		m_hasHotkey = true;
		return *this;
	}

	VehicleOption& canBeSaved() {
		m_canBeSaved = true;
		return *this;
	}

	VehicleOption& addTranslation() {
		m_name.SetHasTranslation(true);
		m_tooltip.SetHasTranslation(true);
		return *this;
	}

	VehicleOption& addTooltip(String tooltip) {
		m_tooltip.Set(tooltip);
		return *this;
	}

	void GetInput();
	void Input(int position);
	void Render(int position);
	void RenderSelected(int position);
	void HandleHotkey();
};
