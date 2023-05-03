#include "stdafx.h"

TranslationString strOS("Operating system", true, true);
TranslationString strCPUBrand("CPU brand", true, true);
TranslationString strCPUSpeed("CPU speed", true, true);
TranslationString strGPU("GPU", true, true);
TranslationString strVram("Vram", true, true);
TranslationString strBuild("Game build", true, true);
TranslationString strOnlineVersion("Online version", true, true);
TranslationString strMotherboard("Motherboard", true, true);
TranslationString strDX("DirectX version", true, true);
TranslationString strLanguage("Game language", true, true);
TranslationString strSCVersion("Social club version", true, true);
TranslationString strSCEmail("Social club email", true, true);


void UISystemdataComponent::drawInfo(float x, float width, int yOffset, String name, String value, Texture text, Color color) {
	const Color white = { GetRenderer()->m_cOption.m_r, GetRenderer()->m_cOption.m_g, GetRenderer()->m_cOption.m_b, GetRenderer()->m_cOption.m_a };
	const float offset = 0.0025f;
	float xPos = m_parent->m_position.x + x - m_parent->m_size.x / 2;
	float yPos = m_parent->m_position.y + 0.022f * yOffset - m_parent->m_size.y / 2 + m_parent->m_headerHeight;
	if (text.isEmpty()) {
		GetRenderer()->DrawString(name, xPos + offset, yPos, GetRenderer()->m_textFont, 0.35f, white, false, JustifyLeft, xPos + offset, xPos + width - offset);
		GetRenderer()->DrawString(va("~c~%s",value), xPos + offset, yPos, GetRenderer()->m_textFont, 0.35f, white, false, JustifyRight, xPos + offset, xPos + width - offset);
	} else {
		GetRenderer()->DrawSpriteAspect(text, xPos + offset * 2, yPos + 0.015f, 25, 25, 0, color);
		GetRenderer()->DrawString(name, xPos + offset + 0.005f, yPos, GetRenderer()->m_textFont, 0.35f, white, false, JustifyLeft, xPos + offset + 0.005f, xPos + width - offset);
		GetRenderer()->DrawString(va("~c~%s", value), xPos + offset + 0.005f, yPos, GetRenderer()->m_textFont, 0.35f, white, false, JustifyRight, xPos + offset + 0.005f, xPos + width - offset);
	}
}

void UISystemdataComponent::drawMiddleLine(int yOffset) {
	float xPos = m_parent->m_position.x;
	float yPos = m_parent->m_position.y + 0.022f * yOffset + 0.015f - m_parent->m_size.y / 2 + m_parent->m_headerHeight;
	GetRenderer()->DrawRect(xPos, yPos, GetRenderer()->m_lineWidth * 2, 0.022f, GetRenderer()->m_cOutline);
	GetRenderer()->DrawRect(xPos, yPos, GetRenderer()->m_lineWidth, 0.022f, { 0, 0, 0, 255 });
}

void UISystemdataComponent::drawMiddleLineTop(int yOffset) {
	float xPos = m_parent->m_position.x;
	float yPos = m_parent->m_position.y + 0.022f * yOffset + 0.015f - 0.022f / 2 - m_parent->m_size.y / 2 + m_parent->m_headerHeight;
	GetRenderer()->DrawRect(xPos, yPos, GetRenderer()->m_lineWidth * 2, GetRenderer()->m_lineWidth * 2, GetRenderer()->m_cOutline);
}
void UISystemdataComponent::drawMiddleLineBottom(int yOffset) {
	float xPos = m_parent->m_position.x;
	float yPos = m_parent->m_position.y + 0.022f * yOffset + 0.015f + 0.022f / 2 - m_parent->m_size.y / 2 + m_parent->m_headerHeight;
	GetRenderer()->DrawRect(xPos, yPos, GetRenderer()->m_lineWidth * 2, GetRenderer()->m_lineWidth * 2, GetRenderer()->m_cOutline);
}

void UISystemdataComponent::update() {}
void UISystemdataComponent::ASyncUpdate() {};
void UISystemdataComponent::render() {
	drawInfo(0, m_whole, 0, strOS.Get(), GetSystemdata()->m_operatingSystem);
	drawInfo(0, m_whole, 1, strMotherboard.Get(), GetSystemdata()->m_motherBoard);
	drawInfo(0, m_whole, 2, strCPUBrand.Get(), GetSystemdata()->m_CPUBrand);
	drawInfo(0, m_whole, 3, strCPUSpeed.Get(), GetSystemdata()->m_CPUSpeed);
	drawInfo(0, m_whole, 4, strGPU.Get(), GetSystemdata()->m_GPU);
	
	drawInfo(0, m_half, 5, strDX.Get(), GetSystemdata()->m_directXVersion);
	drawInfo(m_half, m_half, 5, strVram.Get(), GetSystemdata()->m_VRam);
	drawMiddleLineTop(5);
	drawMiddleLine(5);

	drawInfo(0, m_half, 6, strBuild.Get(), GetSystemdata()->m_gameBuild);
	drawInfo(m_half, m_half, 6, strOnlineVersion.Get(), GetSystemdata()->m_gameOnlineVersion);
	drawMiddleLine(6);
	drawMiddleLineBottom(6);

	drawInfo(0, m_whole, 7, strLanguage.Get(), GetSystemdata()->m_gameLanguage);
	drawInfo(0, m_whole, 8, strSCEmail.Get(), GetSystemdata()->m_socialClubEmail);
}