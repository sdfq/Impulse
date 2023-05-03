#pragma once
#include "menu/submenus/main/spawn/spawnVehicleMenu.h"

class UIVehicleComponent : public UIComponent {
private:
	Hash m_vehicleHash;

	void drawInfo(float x, float width, int yOffset, String name, String value) {
		const Color white = { GetRenderer()->m_cOption.m_r, GetRenderer()->m_cOption.m_g, GetRenderer()->m_cOption.m_b, GetRenderer()->m_cOption.m_a };
		const float offset = 0.0025f;
		float xPos = m_parent->m_position.x + x - m_parent->m_size.x / 2;
		float yPos = m_parent->m_position.y + 0.022f * yOffset - m_parent->m_size.y / 2 + m_parent->m_headerHeight - 0.003f;
		GetRenderer()->DrawString(name, xPos + offset, yPos, 4, 0.35f, white, false, JustifyLeft, xPos + offset, xPos + width - offset);
		GetRenderer()->DrawString(value, xPos + offset, yPos, 4, 0.35f, white, false, JustifyRight, xPos + offset, xPos + width - offset);
	}

	void drawMiddleLine(int yOffset) {
		float xPos = m_parent->m_position.x;
		float yPos = m_parent->m_position.y + 0.022f * yOffset + 0.015f - m_parent->m_size.y / 2 + m_parent->m_headerHeight;
		GetRenderer()->DrawRect(xPos, yPos, GetRenderer()->m_lineWidth * 2, 0.022f, GetRenderer()->m_cOutline);
		GetRenderer()->DrawRect(xPos, yPos, GetRenderer()->m_lineWidth, 0.022f, { 0, 0, 0, 255 });
	}

	void drawMiddleLineTop(int yOffset) {
		float xPos = m_parent->m_position.x;
		float yPos = m_parent->m_position.y + 0.022f * yOffset + 0.015f - 0.022f / 2 - m_parent->m_size.y / 2 + m_parent->m_headerHeight;
		GetRenderer()->DrawRect(xPos, yPos, GetRenderer()->m_lineWidth * 2, GetRenderer()->m_lineWidth * 2, GetRenderer()->m_cOutline);
	}

	void DrawVehicleImage(Hash model) {
		int index = 0xFFFF;

		CVehicleModelInfo1290* modelInfo = (CVehicleModelInfo1290*)Backend::GetModelInfo(model, &index);

		auto vit = std::find(VehicleImages.begin(), VehicleImages.end(), model);
		if (vit != VehicleImages.end()) GetRenderer()->DrawSprite({ vit->dict, vit->imgName }, m_parent->m_position.x, m_parent->m_position.y - (0.221f - 0.165f) / 2, 0.187f, 0.165f, 0, { 255, 255, 255, 255 });
		else GetRenderer()->DrawSprite({ "Bookmarks", "NoVehiclePreview" }, m_parent->m_position.x, m_parent->m_position.y - (0.221f - 0.165f) / 2, 0.187f, 0.165f, 0, { 255, 255, 255, 255 });

		if (modelInfo) {
			float half = 0.187f / 2;
			float whole = 0.187f;
			drawInfo(0, half, 6, "Make", HUD::_GetLabelText(modelInfo->m_manufacturerName));
			drawInfo(half, half, 6, "Name", HUD::_GetLabelText(VEHICLE::GetDisplayNameFromVehicleModel(model)));
			drawInfo(0, half, 7, "Max Speed", va("%.0fMPH", VEHICLE::_GetVehicleModelMaxSpeed(model) * 2.4f));
			drawInfo(half, half, 7, "Seats", va("%d", VEHICLE::GetVehicleModelNumberOfSeats(model)));
			drawMiddleLineTop(6);
			drawMiddleLine(6);
			drawMiddleLine(7);
		}
	}

	void DrawScaleform(Hash model) {
		int index = 0xFFFF;
		CVehicleModelInfo1290* modelInfo = (CVehicleModelInfo1290*)Backend::GetModelInfo(model, &index);

		auto map = SpawnVehicleMenuVars::vars.m_map;

		int scaleform = GRAPHICS::RequestScaleformMovie("mp_car_stats_01");
		if (!GRAPHICS::HasScaleformMovieLoaded(scaleform)) {
			scaleform = GRAPHICS::RequestScaleformMovie("mp_car_stats_01");
		} else {
			GRAPHICS::_PushScaleformMovieFunction(scaleform, "SET_VEHICLE_INFOR_AND_STATS");
			GRAPHICS::_PushScaleformMovieFunctionParameterString(HUD::_GetLabelText(modelInfo->m_displayName));
			GRAPHICS::_PushScaleformMovieFunctionParameterString(HUD::_GetLabelText(modelInfo->m_manufacturerName));
			GRAPHICS::_PushScaleformMovieFunctionParameterString("MPCarHUD"); //MPCarHUD
			GRAPHICS::_PushScaleformMovieFunctionParameterString("fathom"); //fathom
			GRAPHICS::_PushScaleformMovieFunctionParameterString("Top Speed");
			GRAPHICS::_PushScaleformMovieFunctionParameterString("Acceleration");
			GRAPHICS::_PushScaleformMovieFunctionParameterString("Braking");
			GRAPHICS::_PushScaleformMovieFunctionParameterString("Traction");

			int val1 = round((VEHICLE::_GetVehicleModelMaxSpeed(model) * 1.5f));
			int val2 = VEHICLE::GetVehicleModelAcceleration(model) * 2.5f * 100;
			int val3 = VEHICLE::GetVehicleModelMaxBraking(model) / 4.0f * 100;
			int val4 = VEHICLE::GetVehicleModelMaxTraction(model) / 3.0f * 100;

			GRAPHICS::_PushScaleformMovieFunctionParameterInt(Utils::Clamp(val1, 0, 100));
			GRAPHICS::_PushScaleformMovieFunctionParameterInt(Utils::Clamp(val2, 0, 100));
			GRAPHICS::_PushScaleformMovieFunctionParameterInt(Utils::Clamp(val3, 0, 100));
			GRAPHICS::_PushScaleformMovieFunctionParameterInt(Utils::Clamp(val4, 0, 100));
			GRAPHICS::_PopScaleformMovieFunctionVoid();
		}
		GRAPHICS::DrawScaleformMovie(scaleform, m_parent->m_position.x, m_parent->m_position.y - 0.15f, 1.0f, 1.0f, 255, 255, 255, 255, 0);
	}

public:
	UIVehicleComponent() : UIComponent() {}

	void setParent(UIWindow* parent) {
		m_parent = parent;
	}

	void setModel(Hash model) { m_vehicleHash = model; }

	void update() {}
	void ASyncUpdate() {}
	void scrollEvent(int scroll) {}

	void render() {
		DrawVehicleImage(m_vehicleHash);
		//DrawScaleform(m_vehicleHash);
	}
};