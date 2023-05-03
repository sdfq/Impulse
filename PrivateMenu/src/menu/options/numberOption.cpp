#include "stdafx.h"

static bool leftDisabled = false;
static bool rightDisabled = false;
static int leftTimer = 0;
static int rightTimer = 0;

template <class Type>
void NumberOption<Type>::GetInput() {
	GetMenuInput()->AddToQueue([this] {if (GetMenuInput()->Number<Type>(getName().Get(), m_number, m_min, m_hasMin, m_max, m_hasMax, m_format))
	{}
	});
}

template <class Type>
void NumberOption<Type>::Input(int position) {
	if (GetMouse()->CanUse() && GetMouse()->MouseWithinCentered(GetRenderer()->m_posX, GetRenderer()->GetOptionY(position) + GetRenderer()->m_optionHeight / 2, GetRenderer()->m_width, GetRenderer()->m_optionHeight)) {
		if (m_hoverTimer > 30) GetRenderer()->RenderMouseTooltip(m_tooltip.Get());
		else m_hoverTimer++;
		GetMenu()->m_currentOption = position + GetMenu()->m_scrollOffset;
		if (GetMouse()->ButtonJustDown(VK_MOUSE_LEFT)) {
			switch (m_type) {
				case TOGGLE: *m_bool ^= true; break;
				case SELECT: *m_selectedNumber = *m_number; break;
				case SCROLL: GetInput(); break;
			}
			m_function();
		}
	} else m_hoverTimer = 0;
}

template <class Type>
void NumberOption<Type>::Render(int position) {
	m_onUpdate(this);

	static char formatBuffer[100];
	bool scrollLeft = m_loop || (m_hasMin && *m_number != m_min);
	bool scrollRight = m_loop || (m_hasMax && *m_number != m_max);
	vaBuff(formatBuffer, 100, "%s %s %s", scrollLeft ? "<" : "", m_format, scrollRight ? ">" : "");

	switch (m_type) {
		case TOGGLE:
			GetRenderer()->DrawString(va(formatBuffer, *m_number), GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.025f, GetRenderer()->GetOptionYText(position), GetRenderer()->m_textFont, GetRenderer()->m_textSize, GetRenderer()->m_cOption.getOffset(-20), true, 2, 0, GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.025f);
			GetRenderer()->DrawSprite(GetRenderer()->GetToggleTexture(*m_bool), GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.013f, GetRenderer()->GetOptionY(position) + (GetRenderer()->m_optionHeight / 2), 0.02f, 0.015f, 0, { 255, 255, 255, 255 });
			break;
		case SELECT:
			GetRenderer()->DrawString(va(formatBuffer, *m_number), GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.025f, GetRenderer()->GetOptionYText(position), GetRenderer()->m_textFont, GetRenderer()->m_textSize, GetRenderer()->m_cOption.getOffset(-20), true, 2, 0, GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.025f);
			GetRenderer()->DrawSprite(GetRenderer()->GetToggleTexture(*m_selectedNumber == *m_number), GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.013f, GetRenderer()->GetOptionY(position) + (GetRenderer()->m_optionHeight / 2), 0.02f, 0.015f, 0, { 255, 255, 255, 255 });
			break;
		case SCROLL:
		case SCROLLSELECT:
			GetRenderer()->DrawString(va(formatBuffer, *m_number), GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.01f, GetRenderer()->GetOptionYText(position), GetRenderer()->m_textFont, GetRenderer()->m_textSize, GetRenderer()->m_cOption.getOffset(-20), true, 2, 0, GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.01f);
			break;
	}

	GetRenderer()->DrawString(m_name.Get(), GetRenderer()->m_posX - GetRenderer()->m_width / 2 + 0.006f, GetRenderer()->GetOptionYText(position), GetRenderer()->m_textFont, GetRenderer()->m_textSize, GetRenderer()->m_cOption);
}

template <class Type>
void NumberOption<Type>::RenderSelected(int position) {
	m_currentOp();
	if (IsOptionPressed() && m_requirement()) {
		switch (m_type) {
			case TOGGLE: *m_bool ^= true; break;
			case SELECT: *m_selectedNumber = *m_number; break;
			case SCROLL: GetInput(); break;
		}
		m_function();
	}

	if (m_hasHotkey) {
		if (IsHotkeySavePressed()) {
			AUDIO::PlaySoundFrontend(-1, "ATM_WINDOW", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
			GetMenuInput()->AddToQueue([&] {GetMenuInput()->Hotkey(getName().Get(), this); });
		}
	}

	if (m_canBeSaved) {
		if (IsSavePressed()) {
			AUDIO::PlaySoundFrontend(-1, "ATM_WINDOW", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
			GetRenderer()->NotifyMap(va("%s saved", m_name));
			if (is_same<Type, int>::value) GetConfig()->WriteInt("Numbers", m_name.GetOriginal(), *m_number);
			else if (is_same<Type, int64_t>::value) GetConfig()->WriteInt64("Numbers", m_name.GetOriginal(), *m_number);
			else if (is_same<Type, float>::value) GetConfig()->WriteFloat("Numbers", m_name.GetOriginal(), *m_number);
			if (m_type == TOGGLE)GetConfig()->WriteBool("Toggles", m_name.GetOriginal(), *m_bool);
		}
	}

	if (IsLJPressed()) {
		if (!leftDisabled) {
			*m_number -= m_step;
			if (m_loop) {
				if (*m_number < m_min) *m_number = m_max;
			} else if (*m_number < m_min && m_hasMin) *m_number = m_min;
			if (m_type == SCROLL || (m_type == TOGGLE && *m_bool)) m_function();
		}
		leftDisabled = false;
		leftTimer = 0;
	}

	// Scroll right
	if (IsRJPressed()) {
		if (!rightDisabled) {
			*m_number += m_step;
			if (m_loop) {
				if (*m_number > m_max) *m_number = m_min;
			} else if (*m_number > m_max && m_hasMax) *m_number = m_max;
			if (m_type == SCROLL || (m_type == TOGGLE && *m_bool)) m_function();
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
				*m_number -= m_step;
				if (m_loop) {
					if (*m_number < m_min) *m_number = m_max;
				} else if (*m_number < m_min && m_hasMin) *m_number = m_min;
				if (m_type == SCROLL || (m_type == TOGGLE && *m_bool)) m_function();
				TIMER = timeGetTime();
			}
		}
	}
	// Hold right
	if (IsRPressed()) {
		if (++rightTimer > 20) {
			rightDisabled = true;
			if ((timeGetTime() - TIMER) > m_scrollSpeed) {
				*m_number += m_step;
				if (m_loop) {
					if (*m_number > m_max) *m_number = m_min;
				} else if (*m_number > m_max && m_hasMax) *m_number = m_max;
				if (m_type == SCROLL || (m_type == TOGGLE && *m_bool)) m_function();
				TIMER = timeGetTime();
			}
		}
	}
}

template <class Type>
void NumberOption<Type>::HandleHotkey() {
	if (!m_requirement()) return;
	switch (m_type) {
		case TOGGLE: *m_bool ^= true; break;
		case SELECT: *m_selectedNumber = *m_number; break;
		case SCROLL: GetInput(); break;
	}
	m_function();
	GetRenderer()->NotifyMap(va("~c~%s", m_name.Get()));
}

template class NumberOption<int>;
template class NumberOption<float>;
template class NumberOption<int64_t>;
template class NumberOption<int32_t>;
