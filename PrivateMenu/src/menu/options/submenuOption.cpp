#include "stdafx.h"

void SubmenuOption::Input(int position) {
	if (GetMouse()->CanUse() && GetMouse()->MouseWithinCentered(GetRenderer()->m_posX, GetRenderer()->GetOptionY(position) + GetRenderer()->m_optionHeight / 2, GetRenderer()->m_width, GetRenderer()->m_optionHeight)) {
		if (m_hoverTimer > 30) GetRenderer()->RenderMouseTooltip(m_tooltip.Get());
		else m_hoverTimer++;
		GetMenu()->m_currentOption = position + GetMenu()->m_scrollOffset;
		if (GetMouse()->ButtonJustDown(VK_MOUSE_LEFT)) {
			m_function();
			GetSubmenuHandler()->SetSubmenu(m_submenu);
		} //else if (GetMouse()->ButtonJustUp(VK_MOUSE_MIDDLE)) {
			//GetContextMenu()->DrawMenu(position, { ContextMenuOption("test", [] {}), ContextMenuOption("test2", [] {}) });
		//}
	} else m_hoverTimer = 0;
}

once_flag once;
SpriteAnimation m_animatedArrows(750, false);
void SubmenuOption::Render(int position) {
	call_once(once, [] {
		m_animatedArrows.AddTexture({ "Bookmarks", "Arrows-v2" });
		m_animatedArrows.AddTexture({ "Bookmarks", "Arrows-v2-2" });
	});
	m_onUpdate(this);
	float offset = m_onDraw(position);

	GetRenderer()->DrawString(m_name.Get(), offset + GetRenderer()->m_posX - GetRenderer()->m_width / 2 + 0.006f, GetRenderer()->GetOptionY(position) + (GetRenderer()->m_optionHeight - 0.032f) / 2, GetRenderer()->m_textFont, GetRenderer()->m_textSize, GetRenderer()->m_cOption);
	if (GetRenderer()->m_animatedArrows) {
		m_animatedArrows.Draw(GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.010f, GetRenderer()->GetOptionY(position) + (GetRenderer()->m_optionHeight / 2), 0.013f, 0.021f);
	} else if (GetRenderer()->m_arrows == 0) {
		GetRenderer()->DrawSprite({ "Bookmarks", "ImpulseArrow" }, GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.010f, GetRenderer()->GetOptionY(position) + (GetRenderer()->m_optionHeight / 2), 0.015f, 0.030f, 0, { 255, 255, 255, 255 }); //0.013f, 0.021f 
	} else if (GetRenderer()->m_arrows == 1) {
		GetRenderer()->DrawSprite({ "golfputting", "puttingmarker" }, GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.010f, GetRenderer()->GetOptionY(position) + (GetRenderer()->m_optionHeight / 2), 0.010f, 0.020f, 270, { 255, 255, 255, 200 }); //0.013f, 0.021f 
	} else if (GetRenderer()->m_arrows == 2) {
		GetRenderer()->DrawSprite({ "Bookmarks", "ImpulseArrow2" }, GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.010f, GetRenderer()->GetOptionY(position) + (GetRenderer()->m_optionHeight / 2), 0.015f, 0.030f, 0, { 255, 255, 255, 255 }); //0.013f, 0.021f 
	} else if (GetRenderer()->m_arrows == 3) {
		GetRenderer()->DrawSprite({ "Bookmarks", "ImpulseArrow3" }, GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.010f, GetRenderer()->GetOptionY(position) + (GetRenderer()->m_optionHeight / 2), 0.015f, 0.030f, 0, { 255, 255, 255, 200 }); //0.013f, 0.021f 
	} else if (GetRenderer()->m_arrows == 4) {
		GetRenderer()->DrawSprite({ "helicopterhud", "hudarrow" }, GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.010f, GetRenderer()->GetOptionY(position) + (GetRenderer()->m_optionHeight / 2), 0.008f, 0.016f, 90, { 255, 255, 255, 200 }); //0.013f, 0.021f 
	} else if (GetRenderer()->m_arrows == 5) {
		GetRenderer()->DrawSprite({ "hunting", "huntingwindarrow_32" }, GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.010f, GetRenderer()->GetOptionY(position) + (GetRenderer()->m_optionHeight / 2), 0.005f, 0.010f, 90, { 255, 255, 255, 200 }); //0.013f, 0.021f 
	}
}

void SubmenuOption::RenderSelected(int position) {
	m_currentOp();
	if (IsOptionPressed() && m_requirement()) {
		m_function();
		//LOG_PRINT("%s", m_submenu->getName());
		GetSubmenuHandler()->SetSubmenu(m_submenu);
	}

	if (m_hasHotkey) {
		if (IsHotkeySavePressed()) {
			AUDIO::PlaySoundFrontend(-1, "ATM_WINDOW", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
			GetMenuInput()->AddToQueue([&] {GetMenuInput()->Hotkey(getName().Get(), this); });
		}
	}
};

TranslationString strOpened("opened");
void SubmenuOption::HandleHotkey() {
	if (!m_requirement()) return;
	m_function();
	if (!GetMenu()->IsOpen())GetMenu()->Open();
	GetSubmenuHandler()->SetSubmenu(m_submenu);
	GetRenderer()->NotifyBottom(va("~c~%s %s", m_name.Get(), strOpened.Get()));
}