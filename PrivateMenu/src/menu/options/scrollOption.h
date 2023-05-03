#pragma once

template <typename Type>
struct ScrollStruct {
	TranslationString m_name;
	Type m_result;
};

template <typename Type>
class ScrollOption : public Option {
private:
	function<void(ScrollOption*)> m_onUpdate;
	function<void()> m_currentOp;
	function<void()> m_function;

	ScrollOptionType m_type;
	int* m_number;
	shared_ptr<int> m_selectedNumberStorage;
	int* m_selectedNumber;
	bool* m_bool;
	int m_min;
	int m_max;

	DWORD m_scrollSpeed;

	bool m_hasMin;
	bool m_hasMax;
	bool m_loop;

	/*Scrolling*/
	bool leftDisabled = false;
	bool rightDisabled = false;
	int leftTimer = 0;
	int rightTimer = 0;

	ScrollStruct<Type>* m_scrollStruct;

public:
	ScrollOption(ScrollOptionType type, String name) : Option(name), m_type(type), m_hasMin(false), m_hasMax(false), m_loop(false), m_scrollSpeed(100), m_function([] {}), m_onUpdate([](ScrollOption* option) {}), m_currentOp([] {}) {}
	ScrollOption& addScroll(int& number, int min, int max, ScrollStruct<Type>* scrollStruct) {
		if (m_type == SELECT) {
			m_selectedNumberStorage = make_shared<int>(0);
			m_selectedNumber = m_selectedNumberStorage.get();
		}
		m_hasMin = true;
		m_hasMax = true;
		m_min = min;
		m_max = max;
		m_number = &number;
		m_scrollStruct = scrollStruct;
		return *this;
	}

	ScrollOption& addToggle(bool& toggle) {
		m_bool = &toggle;
		return *this;
	}

	ScrollOption& addSelectedNumber(int& selectedNumber) {
		m_selectedNumber = &selectedNumber;
		return *this;
	}

	ScrollOption& addRequirement(function<bool()> func) {
		m_requirement = func;
		return *this;
	}

	ScrollOption& addFunction(function<void()> func) {
		m_function = func;
		return *this;
	}

	ScrollOption& addOnUpdate(function<void(ScrollOption*)> update) {
		m_onUpdate = update;
		return *this;
	}

	ScrollOption& addOnUpdate(function<void()> update) {
		m_onUpdate = [=](ScrollOption* option) {update(); };
		return *this;
	}

	ScrollOption& addCurrentOp(function<void()> func) {
		m_currentOp = func;
		return *this;
	}

	ScrollOption& addHotkey() {
		m_hasHotkey = true;
		return *this;
	}

	ScrollOption &canBeSaved() {
		m_canBeSaved = true;
		if (SimpleIsValidAddress(m_number) && m_requirement()) {
			*m_number = GetConfig()->ReadInt("Numbers", m_name.GetOriginal(), *m_number);
			if (m_type == TOGGLE) *m_bool = GetConfig()->ReadBool("Toggles", m_name.GetOriginal(), *m_bool);
		}
		return *this;
	}

	ScrollOption& addTranslation() {
		m_name.SetHasTranslation(true);
		m_tooltip.SetHasTranslation(true);
		return *this;
	}

	ScrollOption &canLoop() {
		m_loop = true;
		return *this;
	}

	ScrollOption& addTooltip(String tooltip) {
		m_tooltip.Set(tooltip);
		return *this;
	}

	void GetInput() {
		GetMenuInput()->AddToQueue([this] {if (GetMenuInput()->Number<int>(getName().Get(), m_number, m_min, m_hasMin, m_max, m_hasMax, "%d")) {}
		});
	}

	void Input(int position) {
		if (GetMouse()->CanUse() && GetMouse()->MouseWithinCentered(GetRenderer()->m_posX, GetRenderer()->GetOptionY(position) + GetRenderer()->m_optionHeight / 2, GetRenderer()->m_width, GetRenderer()->m_optionHeight)) {
			if (m_hoverTimer > 30) GetRenderer()->RenderMouseTooltip(m_tooltip.Get());
			else m_hoverTimer++;
			GetMenu()->m_currentOption = position + GetMenu()->m_scrollOffset;
			if (GetMouse()->ButtonJustDown(VK_MOUSE_LEFT))
				switch (m_type) {
					case TOGGLE: *m_bool ^= true; break;
					case SELECT: *m_selectedNumber = *m_number; break;
					case SCROLL: GetInput(); break;
				}
			m_function();
		} else m_hoverTimer = 0;
	}

	void Render(int position) {
		m_onUpdate(this);
		static char nameBuffer[128];
		bool scrollLeft = m_loop || (m_hasMin && *m_number != m_min);
		bool scrollRight = m_loop || (m_hasMax && *m_number != m_max);
		vaBuff(nameBuffer, 128, "%s %s %s", scrollLeft ? "<" : "", m_scrollStruct[*m_number].m_name.Get(), scrollRight ? ">" : "");

		switch (m_type) {
			case TOGGLE:
				GetRenderer()->DrawString(nameBuffer, GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.025f, GetRenderer()->GetOptionYText(position), GetRenderer()->m_textFont, GetRenderer()->m_textSize, GetRenderer()->m_cOption.getOffset(-20), true, 2, 0, GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.025f);
				GetRenderer()->DrawSprite(GetRenderer()->GetToggleTexture(*m_bool), GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.013f, GetRenderer()->GetOptionY(position) + (GetRenderer()->m_optionHeight / 2), 0.02f, 0.015f, 0, { 255, 255, 255, 255 });
				break;
			case SELECT:
				GetRenderer()->DrawString(nameBuffer, GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.025f, GetRenderer()->GetOptionYText(position), GetRenderer()->m_textFont, GetRenderer()->m_textSize, GetRenderer()->m_cOption.getOffset(-20), true, 2, 0, GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.025f);
				GetRenderer()->DrawSprite(GetRenderer()->GetToggleTexture(*m_selectedNumber == *m_number), GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.013f, GetRenderer()->GetOptionY(position) + (GetRenderer()->m_optionHeight / 2), 0.02f, 0.015f, 0, { 255, 255, 255, 255 });
				break;
			case SCROLL:
			case SCROLLSELECT:
				GetRenderer()->DrawString(nameBuffer, GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.01f, GetRenderer()->GetOptionYText(position), GetRenderer()->m_textFont, GetRenderer()->m_textSize, GetRenderer()->m_cOption.getOffset(-20), true, 2, 0, GetRenderer()->m_posX + GetRenderer()->m_width / 2 - 0.01f);
				break;
		}
		GetRenderer()->DrawString(m_name.Get(), GetRenderer()->m_posX - GetRenderer()->m_width / 2 + 0.006f, GetRenderer()->GetOptionYText(position), GetRenderer()->m_textFont, GetRenderer()->m_textSize, GetRenderer()->m_cOption);
	}

	void RenderSelected(int position) {
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
				GetRenderer()->NotifyMap(va("%s saved", m_name.Get()));
				GetConfig()->WriteInt("Numbers", m_name.GetOriginal(), *m_number);
				if (m_type == TOGGLE)GetConfig()->WriteBool("Toggles", m_name.GetOriginal(), *m_bool);
			}
		}

		if (IsLJPressed()) {
			if (!leftDisabled) {
				*m_number -= 1;
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
				*m_number += 1;
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
					*m_number -= 1;
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
					*m_number += 1;
					if (m_loop) {
						if (*m_number > m_max) *m_number = m_min;
					} else if (*m_number > m_max && m_hasMax) *m_number = m_max;
					if (m_type == SCROLL || (m_type == TOGGLE && *m_bool)) m_function();
					TIMER = timeGetTime();
				}
			}
		}

		static char tooltipBuffer[128];
		vaBuff(tooltipBuffer, 128, "~c~[~s~%d/%d~c~] ~s~%s", *m_number + 1, m_max + 1, m_tooltip);
		strcpy(GetRenderer()->m_tooltip, tooltipBuffer);
	}

	void HandleHotkey() {
		if (!m_requirement()) return;
		switch (m_type) {
			case TOGGLE: *m_bool ^= true; break;
			case SELECT: *m_selectedNumber = *m_number; break;
			case SCROLL: GetInput(); break;
		}
		m_function();
		GetRenderer()->NotifyMap(va("~c~%s", m_name.Get()));
	}

	void WriteTranslation(json& jsonOb, bool def) {
		for (int i = 0; i < m_max + 1; i++) {
			if (m_scrollStruct[i].m_name.HasTranslation()) {
				String a = m_scrollStruct[i].m_name.GetOriginal();
				jsonOb[va("%s struct", m_name.GetOriginal())][a] = def ? a : m_scrollStruct[i].m_name.Get();
			}
		}
	}

	void ReadTranslation(json& jsonOb) {
		for (int i = 0; i < m_max + 1; i++) {
			if (m_scrollStruct[i].m_name.HasTranslation()) {
				auto name = m_scrollStruct[i].m_name.GetOriginal();
				m_scrollStruct[i].m_name.SetMapped(jsonGet<string>(jsonOb[va("%s struct", m_name.GetOriginal())], name, name).c_str());
			}
		}
	}

	void ResetTranslation() {
		for (int i = 0; i < m_max + 1; i++) {
			m_scrollStruct[i].m_name.Reset();
		}
	}
};