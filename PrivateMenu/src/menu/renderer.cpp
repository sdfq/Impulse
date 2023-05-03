#include "stdafx.h"
#include "menu\submenus\main\settingsMenu.h"

Renderer g_renderer;

float Renderer::m_globalOpacity;

float Renderer::GetOptionY(int pos) {
	return (pos * m_optionHeight) + m_subHeaderY + m_subHeaderHeight / 2;
}

float Renderer::GetOptionYText(int pos) {
	return GetOptionY(pos) + (m_optionHeight - 0.032f) / 2 - (m_textSize - 0.35f) / 32;
}
void Renderer::DrawString(String text, float x, float y, int font, float scale, Color color, bool outline, int justify, float textWrapMin, float textWrapMax) {
	HUD::SetTextFont(font);

	// justify: 0 - center, 1 - left, 2 - right (-1 = ignore)
	if (justify != -1) {
		if (justify == 2)
			HUD::SetTextWrap(m_posX - m_width / 2, m_posX + m_width / 2 - 0.015f / 2.0f);
		HUD::SetTextJustification(justify);
	}

	// fix for Chalet London sizing 
	if (font == FontChaletLondon) {
		scale *= 0.75f;
		y += 0.003f;
	}
	if (font == FontChaletComprimeCologne) {
		y += 0.003f;
	}

	HUD::SetTextScale(0.0f, scale);
	HUD::SetTextColour(color.m_r, color.m_g, color.m_b, color.m_a * *m_opacity);

	if (textWrapMin != 0 || textWrapMax != 0) HUD::SetTextWrap(textWrapMin, textWrapMax);

	if (!SettingsMenuVars::vars.unoutlinestoof) {
		if (outline) HUD::SetTextOutline();
	}

	HUD::BeginTextCommandDisplayText("STRING");
	HUD::AddTextComponentSubstringPlayerName(text);
	HUD::EndTextCommandDisplayText(x, y, 0);
}

void Renderer::DrawRect(float x, float y, float width, float height, Color color) {
	GRAPHICS::DrawRect(x, y, width, height, color.m_r, color.m_g, color.m_b, color.m_a * *m_opacity, 0);
}

void Renderer::DrawSprite(Texture texture, float x, float y, float w, float h, float heading, Color color, bool renderIfNotStreamed) {
	bool streamed = GRAPHICS::HasStreamedTextureDictLoaded(texture.dict);
	if (streamed || renderIfNotStreamed) GRAPHICS::DrawSprite(texture.dict, texture.id, x, y, w, h, heading, color.m_r, color.m_g, color.m_b, color.m_a * *m_opacity, 0);
	if (!streamed) GRAPHICS::RequestStreamedTextureDict(texture.dict, 0);
}

void Renderer::DrawSpriteUnsafe(Texture texture, float x, float y, float w, float h, float heading, Color color) {
	GRAPHICS::DrawSprite(texture.dict, texture.id, x, y, w, h, heading, color.m_r, color.m_g, color.m_b, color.m_a * *m_opacity, 0);
}

void Renderer::DrawSpriteAspect(Texture texture, float x, float y, float w, float h, float heading, Color color, bool renderIfNotStreamed) {
	bool streamed = GRAPHICS::HasStreamedTextureDictLoaded(texture.dict);
	if (streamed || renderIfNotStreamed) GRAPHICS::DrawSprite(texture.dict, texture.id, x, y, w / GetMouse()->m_resX, h / GetMouse()->m_resY, heading, color.m_r, color.m_g, color.m_b, color.m_a * *m_opacity, 0);
	if (!streamed) GRAPHICS::RequestStreamedTextureDict(texture.dict, 0);
}

void Renderer::DrawLine(float x1, float y1, float z1, float x2, float y2, float z2, Color color) {
	GRAPHICS::DrawLine(x1, y1, z1, x2, y2, z2, color.m_r, color.m_g, color.m_b, color.m_a);
}

void Renderer::DrawBox(float x, float y, float width, float height, String title, bool gradients, Texture texture, bool customColor, Color color) {
	if (gradients && m_cPrimary.m_r == 0 && m_cPrimary.m_g == 0 && m_cPrimary.m_b == 0 && m_cPrimary.m_a == 255) {
		DrawSprite(texture, x, y - height / 2 + m_dialogHeaderHeight / 2, width, m_dialogHeaderHeight, 0.0f, { m_cPrimary.m_r, m_cPrimary.m_g, m_cPrimary.m_b, m_cPrimary.m_a });
		DrawSprite(texture, x, y + height / 2 - m_dialogFooterHeight / 2, width, m_dialogFooterHeight, 180, { m_cPrimary.m_r, m_cPrimary.m_g, m_cPrimary.m_b, m_cPrimary.m_a });
		//DrawRect(x, y, width, height, { customColor ? color.m_r : m_cPrimary.m_r, customColor ? color.m_g : m_cPrimary.m_g, customColor ? color.m_b : m_cPrimary.m_b, customColor ? color.m_a : (int)m_bgOpacity * 255 / 100 });
		DrawRect(x, y + m_dialogHeaderHeight / 2 - m_dialogFooterHeight / 2, width, height - m_dialogHeaderHeight - m_dialogFooterHeight, { m_cPrimary.m_r, m_cPrimary.m_g, m_cPrimary.m_b, (int)m_bgOpacity * 255 / 100 });
	} else DrawRect(x, y, width, height, { customColor ? color.m_r : m_cPrimary.m_r, customColor ? color.m_g : m_cPrimary.m_g, customColor ? color.m_b : m_cPrimary.m_b, customColor ? color.m_a : (int)m_bgOpacity * 255 / 100 });


	GetRenderer()->DrawString(title, x - width / 2 + 0.01f, y - height / 2 + 0.005f, 7, 0.5f, GetRenderer()->m_cOption, true);

	DrawRect(x, y - height / 2, width + m_lineWidth * 2, m_lineWidth, m_cPrimary); //Top
	DrawRect(x, y + height / 2, width + m_lineWidth * 2, m_lineWidth, m_cPrimary); //Bottom
	DrawRect(x - width / 2, y, m_lineWidth, height + m_lineWidth * 2, m_cPrimary); //Left
	DrawRect(x + width / 2, y, m_lineWidth, height + m_lineWidth * 2, m_cPrimary); //Right

	DrawRect(x, y - height / 2 - m_lineWidth, width + m_lineWidth * 2, m_lineWidth, m_cOutline); //Top
	DrawRect(x, y + height / 2 + m_lineWidth, width + m_lineWidth * 2, m_lineWidth, m_cOutline); //Bottom
	DrawRect(x - width / 2 - m_lineWidth, y, m_lineWidth, height + m_lineWidth * 3, m_cOutline); //Left
	DrawRect(x + width / 2 + m_lineWidth, y, m_lineWidth, height + m_lineWidth * 3, m_cOutline); //Right
}

void Renderer::DrawBoxMinimized(float x, float y, float width, float height, String title, Texture texture) {
	DrawSprite(texture, x, y - height / 2 + m_dialogHeaderHeight / 2, width, m_dialogHeaderHeight, 0.0f, { 0, 0, 0, 255 });

	GetRenderer()->DrawString(title, x - width / 2 + 0.01f, y - height / 2 + 0.005f, 7, 0.5f, GetRenderer()->m_cOption, true);

	DrawRect(x, y - height / 2, width + m_lineWidth * 2, m_lineWidth, m_cPrimary); //Top
	DrawRect(x, y - height / 2 - m_lineWidth, width + m_lineWidth * 2, m_lineWidth, m_cOutline); //Top

	DrawRect(x, y - height / 2 + m_dialogHeaderHeight, width + m_lineWidth * 2, m_lineWidth, m_cOutline); //Bottom
	DrawRect(x, y - height / 2 + m_dialogHeaderHeight - m_lineWidth, width + m_lineWidth * 2, m_lineWidth, m_cPrimary); //Bottom

	DrawRect(x - width / 2, y - height / 2 + m_dialogHeaderHeight / 2 - m_lineWidth / 2, m_lineWidth, m_dialogHeaderHeight, m_cPrimary); //Left
	DrawRect(x - width / 2 - m_lineWidth, y - height / 2 + m_dialogHeaderHeight / 2 - m_lineWidth / 2, m_lineWidth, m_dialogHeaderHeight + m_lineWidth * 2, m_cOutline); //Left

	DrawRect(x + width / 2, y - height / 2 + m_dialogHeaderHeight / 2 - m_lineWidth / 2, m_lineWidth, m_dialogHeaderHeight, m_cPrimary); //Right
	DrawRect(x + width / 2 + m_lineWidth, y - height / 2 + m_dialogHeaderHeight / 2 - m_lineWidth / 2, m_lineWidth, m_dialogHeaderHeight + m_lineWidth * 2, m_cOutline); //Right
}

void Renderer::DrawTitle(String title) {
	DrawString(title, m_posX, m_subHeaderY - m_subHeaderHeight / 2 + 0.001f, FontChaletComprimeCologne, 0.3f, m_cTitle, false, 0, m_posX - m_width / 2, m_posX + m_width / 2);
}

void Renderer::NotifyBottom(String text, int duration) {
	LOG_PRINT("[NotifyB] %s", text);
	HUD::BeginTextCommandPrint("STRING");
	HUD::AddTextComponentSubstringPlayerName(text);
	HUD::EndTextCommandPrint(duration, 1);
}

void Renderer::NotifyMap(String text, boolean showInLog) {
	if (showInLog)
		LOG_PRINT("[NotifyM] %s", text);
	HUD::_SetNotificationTextEntry("STRING");
	HUD::AddTextComponentSubstringPlayerName(text);
	HUD::_SetNotificationMessage2("Bookmarks", "notify_generic", false, 0, "Impulse", "");
	HUD::_DrawNotification(false, true);
}

void Renderer::NotifyMapColor(String text, int color, boolean showInLog) {
	if (showInLog)
		LOG_PRINT("[NotifyMC] %s", text);
	HUD::_SetNotificationBackgroundColor(color);
	HUD::_SetNotificationTextEntry("STRING");
	HUD::AddTextComponentSubstringPlayerName(text);
	HUD::_SetNotificationMessage2("Bookmarks", "notify_generic", false, 0, "Impulse", "");
	HUD::_DrawNotification(false, true);
}

void Renderer::NotifyWarning(String warning, String text) {
	LOG_PRINT("[NotifyW] %s", text);
	HUD::_SetNotificationTextEntry("STRING");
	HUD::_SetNotificationMessageClanTag2(warning, warning, 0, 7, "Warning", text, 1, "~___WARN*", 5, 0);
	HUD::_DrawNotification3(true, true);
}

/*Set the opacity float for the following draw calls. Can be used to fade in or out*/
void Renderer::SetOpacityVariable(float& opacity) {
	m_opacity = &opacity;
}
void Renderer::Set2DLayer(int layer) {
	GRAPHICS::_Set2DLayer(layer);
	m_2DLayer = layer;
}

void Renderer::Render() {
	Utils::Clamp(m_opacity, 0.0f, 1.0f);

	m_posX = GetMenu()->m_position.x;
	m_posY = GetMenu()->m_position.y - m_headerHeight / 2;

	if (GetSubmenuHandler()->GetTotalOptions() > GetMenu()->m_maxOptions) m_renderOptions = GetMenu()->m_maxOptions; else m_renderOptions = GetSubmenuHandler()->GetTotalOptions();

	m_subHeaderY = m_posY + m_headerHeight / 2 + m_subHeaderHeight / 2;
	m_backgroundHeight = m_renderOptions * m_optionHeight;
	m_backgroundY = m_posY + m_headerHeight / 2 + m_subHeaderHeight + m_backgroundHeight / 2;
	m_footerY = m_backgroundY + m_backgroundHeight / 2 + m_footerHeight / 2;
	m_middle = m_backgroundHeight / 2;

	RenderHeader();
	RenderSubHeader();
	RenderBackground();
	RenderOptionHighlight();
	RenderFooter();
}

void Renderer::RenderHeader() {
	if (m_hAnimatedHeader) m_hAnimatedHeader->Draw(m_posX, m_posY, m_width, m_headerHeight);
	else DrawSprite(m_hHeader, m_posX, m_posY, m_width, m_headerHeight, 0.0f, { 255, 255, 255, 255 }, false);
	DrawRect(m_posX, m_posY - 0.0415f + 0.1175f - 0.035f + m_lineWidth / 2, m_width, m_lineWidth, m_cOutline);
}

void Renderer::RenderSubHeader() {
	DrawRect(m_posX, m_subHeaderY, m_width, m_subHeaderHeight, m_cSubHeader);
}

void Renderer::RenderBackground() {
	DrawRect(m_posX, m_backgroundY, m_width, m_backgroundHeight, { m_cPrimary.m_r, m_cPrimary.m_g, m_cPrimary.m_b, (int)m_bgOpacity * 255 / 100 });
	DrawRect(m_posX, m_backgroundY + m_backgroundHeight / 2 - m_lineWidth / 2, m_width, m_lineWidth, m_cOutline);
}

void Renderer::RenderOptionHighlight() {
	static float position = m_subHeaderHeight + 0.1415f, Y_coordTemp;
	int Y_coord = Utils::Clamp(GetMenu()->m_currentOption - GetMenu()->m_scrollOffset > GetMenu()->m_maxOptions ? GetMenu()->m_maxOptions : GetMenu()->m_currentOption - GetMenu()->m_scrollOffset, 0, GetMenu()->m_maxOptions);
	Y_coordTemp = (Y_coord * m_optionHeight) + m_subHeaderY + m_subHeaderHeight / 2 + m_optionHeight / 2;
	position = Utils::Lerp(position, Y_coordTemp, Backend::GetDeltaTime() * 10); //10
	if (SettingsMenuVars::vars.speedupsmoothscrolling) {
		Utils::Ease(position, Y_coordTemp, 6); //speeds up 
	}

	if (SettingsMenuVars::vars.disablesmoothscroll) {
		DrawRect(m_posX, Y_coordTemp, m_width, m_optionHeight, m_cSelection);
		DrawRect(m_posX, Y_coordTemp + m_optionHeight / 2 - m_lineWidth / 2, m_width, m_lineWidth, m_cSelection.getOffset(-75));
		DrawRect(m_posX, Y_coordTemp - m_optionHeight / 2 + m_lineWidth / 2, m_width, m_lineWidth, m_cSelection.getOffset(75));
	} else {
		DrawRect(m_posX, position, m_width, m_optionHeight, m_cSelection);
		DrawRect(m_posX, position + m_optionHeight / 2 - m_lineWidth / 2, m_width, m_lineWidth, m_cSelection.getOffset(-75));
		DrawRect(m_posX, position - m_optionHeight / 2 + m_lineWidth / 2, m_width, m_lineWidth, m_cSelection.getOffset(75));
	}
}

void Renderer::RenderFooter() {
	DrawRect(m_posX, m_footerY, m_width, m_footerHeight, m_cSubHeader);
	DrawSprite(m_hFooter, m_posX, m_footerY, m_width / 2.5, m_footerHeight / 1.5, 0, { 255, 255, 255, 200 });
	DrawString(va("%d / %d", GetSubmenuHandler()->m_currentOptionWithoutBreaks + 1, GetSubmenuHandler()->m_totalOptionsWithoutBreaks), m_posX - m_width / 2 + 0.006f, m_footerY - 0.013f, 0, 0.3f, m_cTitle, false);
	DrawString(va("%s %s", GetAuth()->IsTester() || GetAuth()->IsStaff() ? GetAuth()->SRole() : "", GetAuth()->GetCurrentMenuVersion()), m_posX + m_width / 2 - 0.006f, m_footerY - 0.013f, 0, 0.3f, m_cTitle, false, 2, 0, m_posX + m_width / 2 - 0.006f);
}

TranslationString strHotkey("Hotkey", true, true);
TranslationString strNotSet("not set", true, true);
TranslationString strSetHotkey("Set hotkey", true, true);
TranslationString strSaveOption("Save option", true, true);
void Renderer::RenderTooltip(String toRender, bool canBeSaved, bool hasHotkey, int key) {
	if (!SettingsMenuVars::vars.hideuitooltips) {
		int prefLayer = Get2DLayer();
		int offset = 0;
		Set2DLayer(8);
		//DrawSprite(m_hTooltip, 0.50f, 0.85f, 0.26f, 0.07f, 0, { 255, 255, 255, 255 });
		DrawBox(0.50f, 0.85f, 0.26f, 0.07f, "", true, m_hDialogBox, true, { m_cPrimary.m_r, m_cPrimary.m_g, m_cPrimary.m_b, 155 });
		DrawString(toRender, 0.38f, 0.822f, FontChaletLondon, 0.3f, { m_cOption.m_r, m_cOption.m_g, m_cOption.m_b, m_cOption.m_a }, false, 1, 0.38f, 0.4975f);
		if (canBeSaved)DrawString(va("%s: F11", strSaveOption.Get()), 0.38f, 0.822f + (0.015f * offset++), FontChaletLondon, 0.3f, { m_cOption.m_r, m_cOption.m_g, m_cOption.m_b, m_cOption.m_a }, false, 2, 0.38f, 0.615f);
		if (hasHotkey)DrawString(va("%s: F12", strSetHotkey.Get()), 0.38f, 0.822f + (0.015f * offset++), FontChaletLondon, 0.3f, { m_cOption.m_r, m_cOption.m_g, m_cOption.m_b, m_cOption.m_a }, false, 2, 0.38f, 0.615f);
		if (hasHotkey)DrawString(va("%s: %s", strHotkey.Get(), key == -1 ? strNotSet.Get() : g_keyNames[key]), 0.38f, 0.822f + (0.015f * offset++), FontChaletLondon, 0.3f, { m_cOption.m_r, m_cOption.m_g, m_cOption.m_b, m_cOption.m_a }, false, 2, 0.38f, 0.615f);
		Set2DLayer(prefLayer);
	}
}

void Renderer::RenderMouseTooltip(String tooltip) {
	static float fontSize = 0.4f, sizeOffset = 0.002f, xOffset = 0.012f, yOffset = 0.02f;;
	static int font = 0;
	if (strlen(tooltip) == 0) return;
	int prefLayer = Get2DLayer();
	Set2DLayer(8);
	float width = GetStringWidth(tooltip, font, fontSize);
	static float height = GetStringHeight(font, fontSize);
	DrawBox(GetMouse()->GetMouseX() + width / 2 + xOffset, GetMouse()->GetMouseY() - yOffset + height / 2 + 0.01f, width + sizeOffset, height + sizeOffset, "", false, m_hHeader, true, { 5, 0, 0, 200 });
	DrawString(tooltip, GetMouse()->GetMouseX() + xOffset, GetMouse()->GetMouseY() - yOffset + 0.005f, font, fontSize, { m_cOption.m_r, m_cOption.m_g, m_cOption.m_b, m_cOption.m_a }, true, JustifyLeft, 0, 1.2f);
	Set2DLayer(prefLayer);
}

float Renderer::GetStringWidth(String str, int font, float fontsize) {
	if (font == FontChaletLondon) fontsize *= 0.75f;
	HUD::_BeginTextCommandWidth("STRING");
	HUD::AddTextComponentSubstringPlayerName(str);
	HUD::SetTextFont(font);
	HUD::SetTextScale(fontsize, fontsize);
	return HUD::_EndTextCommandGetWidth(font);
}

float Renderer::GetStringHeight(int font, float fontsize) {
	return HUD::_GetTextScaleHeight(fontsize, font);
}

Texture Renderer::GetToggleTexture(bool toggle) {
	if (m_colorlessToggles)return toggle ? ColorlessToggleOn : ColorlessToggleOff;
	else return toggle ? ColoredToggleOn : ColoredToggleOff;
}

Renderer* GetRenderer() { return &g_renderer; }