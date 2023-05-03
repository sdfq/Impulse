#include "stdafx.h"
#include "../menu/submenus/main/settingsMenu.h"

ScreenPanel g_screenPanel;

void ScreenPanel::Init() {
	GetFiberPool()->DoJob([&] { while (m_opacity < 1.0f) {
		m_opacity = Utils::Clamp(m_opacity + 0.02f, 0.0, 1.0); GetFiberManager()->GoToMainFiber();
	}});
}

void ScreenPanel::FadeIn() {
	GetFiberPool()->DoJob([&] { while (m_opacity < 1.0f) {
		m_opacity = Utils::Clamp(m_opacity + 0.02f, 0.0, 1.0); GetFiberManager()->GoToMainFiber();
	}});
}

void ScreenPanel::FadeOut() {
	GetFiberPool()->DoJob([&] { while (m_opacity > 0.0f) {
		m_opacity = Utils::Clamp(m_opacity - 0.02f, 0.0, 1.0); GetFiberManager()->GoToMainFiber();
	}});
}

void ScreenPanel::Render() {
	/*if ((SettingsMenuVars::vars.hideType == 0 || (SettingsMenuVars::vars.hideType == 1 && GetMenu()->IsOpen())) && m_opacity < 0.01f) FadeIn();
	else if ((SettingsMenuVars::vars.hideType == 2 || (SettingsMenuVars::vars.hideType == 1 && !GetMenu()->IsOpen())) && m_opacity > 0.99f) FadeOut();
    if (SettingsMenuVars::vars.hideType == 2 && (SettingsMenuVars::vars.hideType == 1 && !GetMenu()->IsOpen())) return;*/

	if ((SettingsMenuVars::vars.hideType == 0 || (SettingsMenuVars::vars.hideType == 1 && GetMenu()->IsOpen()))) {
		int offset = 0;
		GetRenderer()->SetOpacityVariable(m_opacity);
		for (ButtonStruct& button : m_buttons) {
			if (!button.m_requirement()) continue;
			float distanceSpeed = (button.m_slide - baseSlide + 0.001f) / maxSlide / 250;
			if (Utils::Within(GetMouse()->GetMouseX(), xStart - button.m_slide, xStart)) {
				if (Utils::Within(GetMouse()->GetMouseY(), yStart + (yDistance * offset) - ySize, yStart + (yDistance * offset))) {
					if (GetMouse()->ButtonJustDown(VK_MOUSE_LEFT))button.m_onClick();
					button.m_slide = Utils::Clamp(button.m_slide + (0.002440 - distanceSpeed), baseSlide, maxSlide);
				}
				else button.m_slide = Utils::Clamp(button.m_slide - distanceSpeed, baseSlide, maxSlide);
			}
			else button.m_slide = Utils::Clamp(button.m_slide - distanceSpeed, baseSlide, maxSlide);
			GetRenderer()->DrawBox(xStart - button.m_slide / 2, yStart + (yDistance * offset) - ySize / 2, button.m_slide, ySize, "", true, GetRenderer()->m_hDialogBox);
			GetRenderer()->DrawString(button.m_name.Get(), xStart - button.m_slide + 0.004f, yStart + (yDistance * offset++) - ySize - 0.002f, GetRenderer()->m_textFont, 0.5f, { GetRenderer()->m_cOption.m_r, GetRenderer()->m_cOption.m_g, GetRenderer()->m_cOption.m_b, 200 }, true, 1, xStart - button.m_slide + 0.002f, 2);
		}
	} 
	else if (SettingsMenuVars::vars.hideType == 2) {
		GetRenderer()->SetOpacityVariable(m_opacity);
	}
}

ScreenPanel* GetScreenPanel() { return &g_screenPanel; }