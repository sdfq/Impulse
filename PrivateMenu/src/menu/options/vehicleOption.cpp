#include "stdafx.h"

void VehicleOption::GetInput() {
	GetMenuInput()->AddToQueue([this] {if (GetMenuInput()->Number<int>(getName().Get(), &m_modOffset, -1, true, m_modSize, true, "%d")) {}
	});
}

void VehicleOption::Input(int position) {
	if (GetMouse()->CanUse() && GetMouse()->MouseWithinCentered(GetRenderer()->m_posX, GetRenderer()->GetOptionY(position) + GetRenderer()->m_optionHeight / 2, GetRenderer()->m_width, GetRenderer()->m_optionHeight)) {
		if (m_hoverTimer > 30) GetRenderer()->RenderMouseTooltip(m_tooltip.Get());
		else m_hoverTimer++;
		GetMenu()->m_currentOption = position + GetMenu()->m_scrollOffset;
	} else m_hoverTimer = 0;
}

static TranslationString strStock("Stock", true, true);
void VehicleOption::Render(int position) {
	m_modOffset = VEHICLE::GetVehicleMod(GetLocalPlayer().m_vehicle, m_mod);
	m_modSize = VEHICLE::GetNumVehicleMods(GetLocalPlayer().m_vehicle, m_mod);
	String name = HUD::_GetLabelText(VEHICLE::GetModTextLabel(GetLocalPlayer().m_vehicle, m_mod, m_modOffset));
	if (m_modOffset == -1) name = strStock.Get();

	static char nameBuffer[128];
	bool scrollLeft = (m_modOffset != 0);
	bool scrollRight = (m_modOffset != m_modSize);
	vaBuff(nameBuffer, 128, "%s %s %s", scrollLeft ? "<" : "", name, scrollRight ? ">" : "");
	GetRenderer()->DrawString(m_name.Get(), GetRenderer()->m_posX - GetRenderer()->m_width / 2 + 0.006f, GetRenderer()->GetOptionY(position) + (GetRenderer()->m_optionHeight - 0.032f), GetRenderer()->m_textFont, GetRenderer()->m_textSize, GetRenderer()->m_cOption);
	GetRenderer()->DrawString(nameBuffer, GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.01f, GetRenderer()->GetOptionY(position) + (GetRenderer()->m_optionHeight - 0.032f), GetRenderer()->m_textFont, GetRenderer()->m_textSize, GetRenderer()->m_cOption.getOffset(-20), true, 2, 0, GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.01f);
}

void VehicleOption::RenderSelected(int position) {
	if (IsOptionPressed() && m_requirement()) {
		GetInput();
	}
	if (m_hasHotkey) {
		if (IsHotkeySavePressed()) {
			AUDIO::PlaySoundFrontend(-1, "ATM_WINDOW", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
			GetMenuInput()->AddToQueue([&] {GetMenuInput()->Hotkey(getName().Get(), this); });
		}
	}

	if (IsLJPressed()) {
		if (!leftDisabled) {
			m_modOffset -= 1;
			if (m_modOffset < -1) m_modOffset = -1;
			VEHICLE::SetVehicleMod(GetLocalPlayer().m_vehicle, m_mod, m_modOffset, 0);
		}
		leftDisabled = false;
		leftTimer = 0;
	}

	// Scroll right
	if (IsRJPressed()) {
		if (!rightDisabled) {
			m_modOffset += 1;
			if (m_modOffset >= m_modSize - 1) m_modOffset = m_modSize - 1;
			VEHICLE::SetVehicleMod(GetLocalPlayer().m_vehicle, m_mod, m_modOffset, 0);
		}
		rightDisabled = false;
		rightTimer = 0;
	}
	static int TIMER;

	// Hold left
	if (IsLPressed()) {
		if (++leftTimer > 20) {
			leftDisabled = true;
			if ((timeGetTime() - TIMER) > m_scrollSpeed) {
				m_modOffset -= 1;
				if (m_modOffset < -1) m_modOffset = -1;
				VEHICLE::SetVehicleMod(GetLocalPlayer().m_vehicle, m_mod, m_modOffset, 0);
				TIMER = timeGetTime();
			}
		}
	}
	// Hold right
	if (IsRPressed()) {
		if (++rightTimer > 20) {
			rightDisabled = true;
			if ((timeGetTime() - TIMER) > m_scrollSpeed) {
				m_modOffset += 1;
				if (m_modOffset >= m_modSize - 1) m_modOffset = m_modSize - 1;
				VEHICLE::SetVehicleMod(GetLocalPlayer().m_vehicle, m_mod, m_modOffset, 0);
				TIMER = timeGetTime();
			}
		}
	}
	static char tooltipBuffer[128];
	vaBuff(tooltipBuffer, 128, "~c~[~s~%d/%d~c~] ~s~%s", m_modOffset + 1, m_modSize, m_tooltip);
	strcpy(GetRenderer()->m_tooltip, tooltipBuffer);
}

void VehicleOption::HandleHotkey() {
	if (!m_requirement()) return;
	GetInput();
	GetRenderer()->NotifyMap(va("~c~%s", m_name.Get()));
}