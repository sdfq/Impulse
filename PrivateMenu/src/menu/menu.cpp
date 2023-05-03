#include "stdafx.h"
#include "menu/submenus/main/localMenu.h"
Menu g_menu;

void Menu::Initialize() {
	m_position.x = 0.16f;
	m_position.y = 0.1175f;
	setHeaderHeight(GetRenderer()->m_headerHeight);
	GetSubmenuHandler()->Init();
	setCanBeClosed(false);
	setCanBeMinimized(false);
}

void Menu::render() {
	using namespace LocalMenuVars;
	if (!m_open) return;
	GetRenderer()->SetOpacityVariable(m_opacity);

	/*Prepare menu*/
	DisablePhone();
	PrepareMenu();
	DisableControls();
	MenuControls();

	/*Render menu*/
	m_size = { GetRenderer()->m_width, GetRenderer()->m_headerHeight * 2 };
	PROFILER_START(MenuRender);
	GetRenderer()->Render();
	PROFILER_END(MenuRender);

	/*Update the menu*/
	PROFILER_START(MenuUpdate);
	GetSubmenuHandler()->Update(m_inputThisFrame);
	PROFILER_END(MenuUpdate);

	/*Calculate slider stuff*/
	float sliderX = m_position.x - m_size.x / 2 - 0.01f;
	float sliderTop = GetRenderer()->m_backgroundY - GetRenderer()->m_backgroundHeight / 2;
	float sliderBottom = GetRenderer()->m_backgroundY + GetRenderer()->m_backgroundHeight / 2;
	float sliderPosition = (((float)(GetSubmenuHandler()->m_currentOptionWithoutBreaks) / ((float)GetSubmenuHandler()->m_totalOptionsWithoutBreaks - 1)) * (GetRenderer()->m_backgroundHeight - GetRenderer()->m_optionHeight)) + GetRenderer()->m_optionHeight / 2;
	if (GetSubmenuHandler()->m_totalOptions < 2)sliderPosition = GetRenderer()->m_backgroundHeight - GetRenderer()->m_optionHeight + GetRenderer()->m_optionHeight / 2;

	/*Reset dragging*/
	if (!GetMouse()->ButtonDown(VK_MOUSE_LEFT)) {
		GetWindowManager()->GetFrame()->m_isHandlingComponent = false;
		m_draggingSlider = false;
	}

	/*If click within slider, start dragging*/
	if (!GetWindowManager()->GetFrame()->IsDragging() && GetMouse()->MouseWithinCentered(sliderX, sliderTop + sliderPosition, 0.008f, 0.022f)) {
		GetMouse()->SetCursor(Mouse::HAND_OPEN);
		if (GetMouse()->ButtonDown(VK_MOUSE_LEFT)) {
			GetWindowManager()->GetFrame()->m_isHandlingComponent = true;
			m_draggingSlider = true;
		}
	}

	/*If dragging slider, slide through options*/
	if (m_draggingSlider) {
		GetMouse()->SetCursor(Mouse::HAND_CLOSED);
		float posback = (GetMouse()->GetMouseY() + 0.022f / 2 - sliderTop) / (GetRenderer()->m_backgroundHeight - GetRenderer()->m_optionHeight);
		float positionback = posback * GetSubmenuHandler()->m_totalOptionsWithoutBreaks;
		Utils::Clamp(&positionback, 0, GetSubmenuHandler()->GetTotalOptions() - 1);
		m_currentOption = positionback;
		if (m_scrollOffset > m_currentOption) m_scrollOffset -= m_scrollOffset - m_currentOption;
		else if (m_currentOption > m_scrollOffset + m_maxOptions - 1) m_scrollOffset += m_currentOption - (m_scrollOffset + m_maxOptions - 1);
	}

	/*Magic easing*/
	static float easedSliderPosition = sliderPosition;
	//Utils::Ease(easedSliderPosition, sliderPosition, 6); //speed up
	easedSliderPosition = Utils::Lerp(easedSliderPosition, sliderPosition, 10 * Backend::GetDeltaTime());


	/*Render slider*/
	GetRenderer()->DrawRect(sliderX, sliderTop - 0.007f, 0.01f, 0.014f, { 0, 0, 0, 255 }); //Top
	GetRenderer()->DrawRect(sliderX, sliderBottom + 0.007f, 0.01f, 0.014f, { 0, 0, 0, 255 }); //Bottom
	GetRenderer()->DrawSpriteAspect({ "commonmenu", "arrowright" }, sliderX, sliderTop - 0.007f, 25, 25, -90, { 255, 255, 255, 255 }); //Top
	GetRenderer()->DrawSpriteAspect({ "commonmenu", "arrowright" }, sliderX, sliderBottom + 0.007f, 25, 25, 90, { 255, 255, 255, 255 }); //Bottom
	GetRenderer()->DrawRect(sliderX, GetRenderer()->m_backgroundY, 0.01f, GetRenderer()->m_backgroundHeight, { GetRenderer()->m_cPrimary.m_r, GetRenderer()->m_cPrimary.m_g, GetRenderer()->m_cPrimary.m_b, 100 }); //Whole
	if (GetSubmenuHandler()->m_totalOptions > 0) GetRenderer()->DrawRect(sliderX, sliderTop + easedSliderPosition, 0.008f, GetRenderer()->m_optionHeight - 0.006f, GetRenderer()->m_cSelection); //Level
	if (GetSubmenuHandler()->m_totalOptions > 0) GetRenderer()->DrawRect(sliderX, sliderTop + easedSliderPosition - GetRenderer()->m_optionHeight / 2 + 0.006f / 2, 0.008f, GetRenderer()->m_lineWidth, GetRenderer()->m_cSelection.getOffset(75)); //Level
	if (GetSubmenuHandler()->m_totalOptions > 0) GetRenderer()->DrawRect(sliderX, sliderTop + easedSliderPosition + GetRenderer()->m_optionHeight / 2 - 0.006f / 2, 0.008f, GetRenderer()->m_lineWidth, GetRenderer()->m_cSelection.getOffset(-75)); //Level
	m_inputThisFrame = false;
}

/*This function only gets called when the mouse is inside the window*/
void Menu::update() {
	m_inputThisFrame = true;
}

bool Menu::within(float x, float y) {
	if (!m_open) return false;
	return (Utils::Within(x, GetRenderer()->m_posX - GetRenderer()->m_width / 2, GetRenderer()->m_posX + GetRenderer()->m_width / 2)
		&& Utils::Within(y, GetRenderer()->m_posY - GetRenderer()->m_headerHeight / 2, GetRenderer()->m_posY + GetRenderer()->m_headerHeight / 2 + GetRenderer()->m_backgroundHeight + GetRenderer()->m_footerHeight));
}

bool Menu::withinHeaderY(float y) {
	return Utils::Within(y, GetRenderer()->m_posY - GetRenderer()->m_headerHeight / 2, GetRenderer()->m_posY + GetRenderer()->m_headerHeight / 2);
}

void Menu::scrollEvent(int scroll) {
	if (!m_open) return;
	if (scroll > 0 && GetMenu()->m_scrollOffset > 0) {
		GetMenu()->m_scrollOffset--;
		GetMenu()->m_currentOption--;
	}
	if (scroll < 0 && GetMenu()->m_scrollOffset < GetSubmenuHandler()->GetTotalOptions() - GetMenu()->m_maxOptions) {
		GetMenu()->m_scrollOffset++;
		GetMenu()->m_currentOption++;
	}
	if (GetSubmenuHandler()->GetTotalOptions() >= GetMenu()->m_maxOptions && GetMenu()->m_scrollOffset > GetSubmenuHandler()->GetTotalOptions() - GetMenu()->m_maxOptions) { //GetSubmenuHandler()->GetTotalOptions() >= 14 && GetMenu()->m_scrollOffset > GetSubmenuHandler()->GetTotalOptions() - GetMenu()->m_maxOptions
		GetMenu()->m_scrollOffset = GetSubmenuHandler()->GetTotalOptions() - GetMenu()->m_maxOptions;
		GetMenu()->m_currentOption = GetSubmenuHandler()->GetTotalOptions() - GetMenu()->m_maxOptions;
	}
}
void Menu::ASyncUpdate() {
	if (GetAuth()->IsAuthorized()) {
		GetPlayerManager()->Update();
	}
}

Menu* GetMenu() { return &g_menu; }