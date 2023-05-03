#include "stdafx.h"

Scaleform g_scaleform;

void Scaleform::DrawLargeMessage(String title, String message, int color, int duration) {
	GetFiberPool()->DoJob([duration, title, message, color] {
		float startPos = 0.0f;
		for (int i = 0; i < duration; i++) {
			int m_scaleForm = GRAPHICS::RequestScaleformMovie("MP_BIG_MESSAGE_FREEMODE");
			if (GRAPHICS::HasScaleformMovieLoaded(m_scaleForm)) {
				GRAPHICS::_PushScaleformMovieFunction(m_scaleForm, "OVERRIDE_Y_POSITION");
				GRAPHICS::_PushScaleformMovieFunctionParameterFloat(startPos - 0.75f);
				GRAPHICS::_PopScaleformMovieFunctionVoid();
				if (startPos < 0.5f)startPos += (0.5f - startPos) / 100.0f;
				if (i > duration - 150)startPos -= startPos / 50.0f;
				GRAPHICS::_PushScaleformMovieFunction(m_scaleForm, "SHOW_CENTERED_MP_MESSAGE_LARGE");
				GRAPHICS::_PushScaleformMovieFunctionParameterString(title);
				HUD::_SetNotificationColorNext(color);
				GRAPHICS::_PushScaleformMovieFunctionParameterString(message);
				GRAPHICS::_PushScaleformMovieFunctionParameterInt(100);
				GRAPHICS::_PushScaleformMovieFunctionParameterBool(1);
				GRAPHICS::_PopScaleformMovieFunction();
				GRAPHICS::DrawScaleformMovieFullscreen(m_scaleForm, 255, 255, 255, 0, 0);
			}
			GetFiberManager()->GoToMainFiber();
		}
	});
}

void Scaleform::PrepareInstructionalButtons() {
	m_scaleForm = GRAPHICS::RequestScaleformMovie("instructional_buttons");
	if (GRAPHICS::HasScaleformMovieLoaded(m_scaleForm)) {
		GRAPHICS::DrawScaleformMovieFullscreen(m_scaleForm, 255, 255, 255, 0, 0);
		GRAPHICS::_PushScaleformMovieFunction(m_scaleForm, "CLEAR_ALL");
		GRAPHICS::_PopScaleformMovieFunctionVoid();
		GRAPHICS::_PushScaleformMovieFunction(m_scaleForm, "SET_CLEAR_SPACE");
		GRAPHICS::_PushScaleformMovieFunctionParameterInt(200);
		GRAPHICS::_PopScaleformMovieFunctionVoid();
		GRAPHICS::_PushScaleformMovieFunction(m_scaleForm, "SET_MAX_WIDTH");
		GRAPHICS::_PushScaleformMovieFunctionParameterFloat(1);
		GRAPHICS::_PopScaleformMovieFunctionVoid();
		GRAPHICS::_PushScaleformMovieFunction(m_scaleForm, "SET_DATA_SLOT_EMPTY");
		GRAPHICS::_PopScaleformMovieFunctionVoid();
	}
	m_prepared = true;
}

void Scaleform::FinishInstructionalButtons() {

	if (!m_prepared) return;
	if (GRAPHICS::HasScaleformMovieLoaded(m_scaleForm)) {
		GRAPHICS::_PushScaleformMovieFunction(m_scaleForm, "DRAW_INSTRUCTIONAL_BUTTONS");
		GRAPHICS::_PopScaleformMovieFunctionVoid();
		GRAPHICS::_PushScaleformMovieFunction(m_scaleForm, "SET_BACKGROUND_COLOUR");
		GRAPHICS::_PushScaleformMovieFunctionParameterInt(/*GetRenderer()->m_cOutline.m_r*/ 0);
		GRAPHICS::_PushScaleformMovieFunctionParameterInt(/*GetRenderer()->m_cOutline.m_g*/ 0);
		GRAPHICS::_PushScaleformMovieFunctionParameterInt(/*GetRenderer()->m_cOutline.m_b*/ 0);
		GRAPHICS::_PushScaleformMovieFunctionParameterInt(80);
		GRAPHICS::_PopScaleformMovieFunctionVoid();
		m_offset = 0;
	}
	m_prepared = false;
}

void Scaleform::DrawInstructional(String text, String button) {
	if (!m_prepared) return;
	if (GRAPHICS::HasScaleformMovieLoaded(m_scaleForm)) {
		GRAPHICS::_PushScaleformMovieFunction(m_scaleForm, "SET_DATA_SLOT");
		GRAPHICS::_PushScaleformMovieFunctionParameterInt(m_offset);
		GRAPHICS::_PushScaleformMovieFunctionParameterString(("t_" + (string)button).c_str());
		GRAPHICS::_PushScaleformMovieFunctionParameterString(text);
		GRAPHICS::_PopScaleformMovieFunctionVoid();
		m_offset++;
	}
}

Scaleform* GetScaleform() { return &g_scaleform; }