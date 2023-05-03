#include "stdafx.h"

static MenuInput g_menuInput;
char g_name[128];
void MenuInput::Update() {
	if (!GetMenu()->IsOpen()) return;
	for (auto& func : m_functionQueue) func();
	m_functionQueue.clear();
}

void MenuInput::Setup() {
	GetFiberManager()->GoToMainFiber();
	GetWindowManager()->DisableAllInputThisFrame();
	GetRenderer()->Set2DLayer(7);
}

void MenuInput::GetInput(string& input, InputCombination keys[], int size, int maxLength) {
	static int timer;
	if (KeyDown(17/*LCTRL*/) && KeyJustUp('V')) {
		if (OpenClipboard(Backend::GetWindow()))input = (char*)GetClipboardData(CF_TEXT);
		CloseClipboard();
		return;
	}
	if (KeyJustUp(VK_SPACE)) input += " ";
	if (KeyJustUp(VK_BACK)) timer = 0;
	if (KeyDown(VK_BACK) && input.length() > 0) Utils::DoTimedFunction(&timer, 100, [&] {input.pop_back(); });
	for (int i = 0; i < size; i++) {
		const InputCombination& comb = keys[i];
		if (KeyJustDown(comb.m_input)) input += KeyDown(VK_SHIFT) || KeyDown(VK_CAPITAL) ? comb.m_outputWithCaps : comb.m_output;
	}
	if (input.length() > maxLength) input.pop_back();
}

TranslationString strInvalidNumber("Invalid number", true, true);
template bool MenuInput::Number<int>(String name, int*, int, bool, int, bool, String);
template bool MenuInput::Number<float>(String name, float*, float, bool, float, bool, String);
template bool MenuInput::Number<int64_t>(String name, int64_t*, int64_t, bool, int64_t, bool, String);
template bool MenuInput::Number<int32_t>(String name, int32_t*, int32_t, bool, int32_t, bool, String);

template <typename Type>
bool MenuInput::Number(String name, Type* output, Type min, bool hasMin, Type max, bool hasMax, String format) {
	strcpy(g_name, name);
	const static float x = 0.5f, y = 0.4f, width = 0.2f, height = 0.1f;
	bool accepted = false;
	bool exit = false;
	string input;
	while (!exit) {
		Setup();
		GetRenderer()->DrawBox(x, y, width, height, g_name, true, GetRenderer()->m_hDialogBox);
		GetRenderer()->DrawRect(0.5, y + 0.02f, width - 0.04f, 0.03f, { 80, 80, 80, 160 });
		GetRenderer()->DrawString(input.c_str(), x, y - 0.02f + 0.02f, FontChaletComprimeCologne2, 0.5f, { 255, 255, 255, 255 }, false, JustifyCenter, x - width / 2, x + width / 2);

		GetInput(input, numberCombinations, NUMOF(numberCombinations), 10);


		if (IsAJPressed(true)) {
			exit = 1;
			accepted = 1;
		} else if (KeyJustUp(VK_ESCAPE)) {
			exit = 1;
			accepted = 0;
		}
	}
	try {
		if (accepted && !input.empty()) {
			Type out = 0;

			if (is_same<Type, int>::value) out = (Type)stoi(input);
			else if (is_same<Type, float>::value) out = (Type)stof(input);
			else if (is_same<Type, int64_t>::value) out = (Type)stoll(input);
			else if (is_same<Type, int32_t>::value) out = (Type)stol(input);

			if (hasMin && out < min) *output = min;
			else if (hasMax && out > max) *output = max;
			else *output = out;
		}
	} catch (...) {
		GetRenderer()->NotifyBottom(strInvalidNumber.Get());
		return false;
	}
	return accepted;
}

TranslationString strTooShort("Input too short", true, true);
bool MenuInput::Text(String name, string& output, int min, int max) {
	strcpy(g_name, name);
	const static float x = 0.5f, y = 0.4f, width = 0.2f, height = 0.1f;
	bool accepted = false;
	bool exit = false;
	string input;
	while (!exit) {
		Setup();
		GetRenderer()->DrawBox(x, y, width, height, g_name, true, GetRenderer()->m_hDialogBox);
		GetRenderer()->DrawRect(0.5, y + 0.02f, width - 0.04f, 0.03f, { 80, 80, 80, 160 });
		GetRenderer()->DrawString(input.c_str(), x, y - 0.02f + 0.02f, FontChaletLondon, 0.5f, { 255, 255, 255, 255 }, false, JustifyCenter, x - width / 2, x + width / 2);

		GetInput(input, normalCombinations, NUMOF(normalCombinations), max);

		if (IsAJPressed(true)) {
			exit = 1;
			accepted = 1;
		} else if (KeyJustUp(VK_ESCAPE)) {
			exit = 1;
			accepted = 0;
		}
	}
	if (input.length() < min) {
		GetRenderer()->NotifyBottom(strTooShort.Get());
		return false;
	}
	if (accepted) output = input;
	return accepted;
}

TranslationString strDelete("Press backspace to delete hotkey", true, true);
bool MenuInput::Hotkey(String name, Option* option) {
	strcpy(g_name, name);
	const static float x = 0.5f, y = 0.4f, width = 0.2f, height = 0.13f;
	bool deleteHotkey = false;
	bool accepted = false;
	bool exit = false;
	int inputKey = 0;
	while (!exit) {
		Setup();
		GetRenderer()->DrawBox(x, y, width, height, g_name, true, GetRenderer()->m_hDialogBox);
		GetRenderer()->DrawRect(0.5, y + 0.02f, width - 0.04f, 0.03f, { 80, 80, 80, 160 });
		if (g_keyNames[inputKey] != "F12")GetRenderer()->DrawString(g_keyNames[inputKey], x, y - 0.02f + 0.02f, FontChaletLondon, 0.5f, { 255, 255, 255, 255 }, true, JustifyCenter);

		GetRenderer()->DrawString(strDelete.Get(), x - width / 2 + 0.005f, y + (height / 2) - 0.01f - GetRenderer()->m_dialogFooterHeight, 0, 0.26f, { 255, 255, 255, 255 });

		int lastKey = GetKeyboard()->GetLastKey();
		if (lastKey != VK_RETURN && lastKey != VK_ESCAPE && lastKey != VK_BACK && lastKey != VK_F10)inputKey = lastKey;

		if (IsAJPressed(true)) {
			accepted = 1;
			exit = 1;
		} else if (KeyJustUp(VK_ESCAPE)) {
			accepted = 0;
			exit = 1;
		} else if (KeyJustUp(VK_BACK)) {
			deleteHotkey = 1;
			accepted = 0;
			exit = 1;
		}
	}

	if (accepted && inputKey != 0) {
		GetHotkeyManager()->UnregisterHotkey(inputKey);
		GetHotkeyManager()->UnregisterHotkey(option->m_hotkey);
		option->m_hotkey = inputKey;
		GetHotkeyManager()->RegisterHotkey(inputKey, option);
	} else if (deleteHotkey) GetHotkeyManager()->UnregisterHotkey(option->m_hotkey);
	return accepted;
}

bool MenuInput::Key(String name, int* key, bool* isControllerOutput, bool controller) {
	strcpy(g_name, name);
	if (isControllerOutput) *isControllerOutput = false;
	const static float x = 0.5f, y = 0.4f, width = 0.2f, height = 0.1f;
	bool accepted = false;
	bool exit = false;
	int inputKey = 0;
	while (!exit) {
		Setup();
		GetRenderer()->DrawBox(x, y, width, height, g_name, true, GetRenderer()->m_hDialogBox);
		GetRenderer()->DrawRect(0.5, y + 0.02f, width - 0.04f, 0.03f, { 80, 80, 80, 160 });
		if (inputKey != 0) GetRenderer()->DrawString(g_keyNames[inputKey], x, y - 0.02f + 0.02f, FontChaletLondon, 0.5f, { 255, 255, 255, 255 }, true, JustifyCenter);

		int lastKey = GetKeyboard()->GetLastKey();
		if (lastKey != VK_RETURN && lastKey != VK_ESCAPE && lastKey != VK_DELETE && lastKey != VK_F10 && lastKey != VK_F9 && lastKey != VK_NUMPAD5 && lastKey != VK_BACK && lastKey != VK_NUMPAD0) {
			if (KeyJustUp(lastKey)) {
				if (isControllerOutput) *isControllerOutput = false;
				inputKey = lastKey;
			}
		}
		if (controller) {
			for (Control* a : GetController()->GetControls()) {
				if (a->m_button != GetController()->A.m_button && a->m_button != GetController()->B.m_button) {
					if (a->Pressed()) {
						if (isControllerOutput) *isControllerOutput = true;
						inputKey = a->m_button;
					}
				}
			}
		}



		if (IsAJPressed(true)) {
			exit = 1;
			accepted = 1;
		} else if (KeyJustUp(VK_ESCAPE)) {
			exit = 1;
			accepted = 0;
		}
	}
	if (accepted && inputKey != 0) *key = inputKey;
	return accepted;
}

bool MenuInput::Col(String name, Color& col) {
	strcpy(g_name, name);
	float x = 0.5f, y = 0.5f, width = 0.24f, height = 0.375f;
	bool accepted = false;
	bool exit = false;
	static int sX = 5, sY = 5;
	static int hueSlider = 0;
	static bool sliderSelected = false;
	Color originalCol = { col.m_r, col.m_g, col.m_b, col.m_a };
	bool wasUsing = GetMouse()->IsEnabled();
	if (!wasUsing) GetMouse()->ToggleMouse();
	bool mouseDragging = false;
	while (!exit) {
		Setup();
		GetRenderer()->DrawBox(x, y, width, height, g_name, true, GetRenderer()->m_hDialogBox);
		GetRenderer()->DrawRect(0.5, 0.55f, width - 0.04f, 0.034f, { 50, 50, 50, 160 });


		for (int xx = 0; xx <= 18; xx++) {
			GetRenderer()->DrawRect(x + xx * 0.011f - 0.099f, y - 2 * 0.022f - 0.055f, 0.011f, 0.02f, Utils::HSVToRGB(xx * 20, 1, 1));
		}

		for (int xx = 0; xx <= 9; xx++) {
			for (int yy = 0; yy <= 9; yy++) {
				if (!(xx == sX && yy == sY && !sliderSelected)) {
					GetRenderer()->DrawRect(x + xx * 0.022f - 0.099f, y + yy * 0.022f - 0.055f, 0.02f, 0.02f, Utils::HSVToRGB(hueSlider, xx * (1.0f / 9), yy*(1.0f / 9)));
				}
				if (GetMouse()->MouseWithinCentered(x + xx * 0.022f - 0.099f, y + yy * 0.022f - 0.055f, 0.02f, 0.02f)) {
					if (GetMouse()->ButtonJustDown(VK_MOUSE_LEFT)) {
						accepted = true;
						exit = true;
						break;
					}
					GetMouse()->SetCursor(Mouse::HAND_MIDDLEFINGER);
					sliderSelected = false;
					sX = xx;
					sY = yy;
				}
			}
		}

		/*Mouse slider dragging*/
		if (GetMouse()->MouseWithinCentered(x, y - 2 * 0.022f - 0.055f, 18 * 0.011f, 0.02f)) {
			sliderSelected = true;
			if (GetMouse()->ButtonDown(VK_MOUSE_LEFT)) {
				mouseDragging = true;
			}
		}
		if (!GetMouse()->ButtonDown(VK_MOUSE_LEFT))mouseDragging = false;
		if (mouseDragging) {
			GetMouse()->SetCursor(Mouse::HAND_MIDDLEFINGER);
			sliderSelected = true;
			float hue = ((GetMouse()->GetMouseX() - x + 9.25f * 0.011f) / (18 * 0.011f)) * 360;
			hueSlider = Utils::Clamp(hue, 0.0f, 360.0f);
			sY = 0;
		}

		if (sliderSelected) {
			GetRenderer()->DrawBox(x - 0.099f + (hueSlider * 0.00055f), y - 2 * 0.022f - 0.055f, 0.015f, 0.03f, "", false, { "", "" }, true, Utils::HSVToRGB(hueSlider, 1, 1));
		} else {
			GetRenderer()->DrawBox(x - 0.099f + (hueSlider * 0.00055f), y - 2 * 0.022f - 0.055f, 0.01f, 0.02f);
			GetRenderer()->DrawBox(x + sX * 0.022f - 0.099f, y + sY * 0.022f - 0.055f, 0.026f, 0.026f, false);
			GetRenderer()->DrawRect(x + sX * 0.022f - 0.099f, y + sY * 0.022f - 0.055f, 0.026f, 0.026f, Utils::HSVToRGB(hueSlider, sX * (1.0f / 9), sY *(1.0f / 9)));
		}
		static bool downDisabled = false;
		static bool leftDisabled = false;
		static bool rightDisabled = false;
		static int downTimer = 0;
		static int leftTimer = 0;
		static int rightTimer = 0;
		static int TIMER;

		static bool upDisabled = false;
		static int upTimer = 0;
		col = Utils::HSVToRGB(hueSlider, sX * (1.0f / 9), sY *(1.0f / 9));
		//Scroll up
		if (IsUJPressed(true)) {
			if (!upDisabled) {
				if (sY > 0) sY--;
				else sliderSelected = true;
			}
			upDisabled = false;
			upTimer = 0;
		}
		// Hold up
		if (IsUPressed(true)) {
			if (++upTimer > 20) {
				upDisabled = true;
				Utils::DoTimedFunction(&TIMER, 50, [&] { if (sY > 0) sY--; else sliderSelected = true;
				});
			}
		}
		// Scroll down
		if (IsDJPressed(true)) {
			if (!downDisabled) {
				if (sliderSelected) {
					sliderSelected = false;
				} else if (sY < 9) sY++;
			}
			downDisabled = false;
			downTimer = 0;
		}

		// Hold down
		if (IsDPressed(true)) {
			if (++downTimer > 20) {
				downDisabled = true;
				Utils::DoTimedFunction(&TIMER, 50, [&] { if (sliderSelected) sliderSelected = false; if (sY < 9) sY++; });
			}
		}

		//Scroll left
		if (IsLJPressed(true)) {
			if (!leftDisabled) {
				if (!sliderSelected) {
					if (sX > 0) sX--;
				} else {
					hueSlider -= 2;
					if (hueSlider < 0) hueSlider = 360;
				}

			}
			leftDisabled = false;
			leftTimer = 0;
		}
		// Scroll right
		if (IsRJPressed(true)) {
			if (!rightDisabled) {
				if (!sliderSelected) {
					if (sX < 9) sX++;
				} else {
					hueSlider += 2;
					if (hueSlider > 360) hueSlider = 0;
				}
			}
			rightDisabled = false;
			rightTimer = 0;
		}
		// Hold left
		if (IsLPressed(true)) {
			if (++leftTimer > 20) {
				leftDisabled = true;
				if (!sliderSelected) {
					Utils::DoTimedFunction(&TIMER, 50, [&] {if (sX > 0) sX--; });
				} else {
					hueSlider -= 2;
					if (hueSlider < 0) hueSlider = 360;
				}
			}
		}
		// Hold right
		if (IsRPressed(true)) {
			if (++rightTimer > 20) {
				rightDisabled = true;
				if (!sliderSelected) {
					Utils::DoTimedFunction(&TIMER, 50, [&] {if (sX < 9) sX++; });
				} else {
					hueSlider += 2;
					if (hueSlider > 360) hueSlider = 0;
				}
			}
		}

		if (IsAJPressed(true)) {
			exit = 1;
			accepted = 1;
		} else if (KeyJustUp(VK_ESCAPE) || GetMouse()->ButtonJustDown(VK_MOUSE_RIGHT)) {
			exit = 1;
			accepted = 0;
		}
	}
	if (accepted) col = Utils::HSVToRGB(hueSlider, sX * (1.0f / 9), sY *(1.0f / 9));
	else col = originalCol;
	if (!wasUsing) GetMouse()->ToggleMouse();
	return accepted;
}

bool MenuInput::Accept(String name, float x, float y, float width, float height, const char* title, float size[18], String text[18]) {
	strcpy(g_name, name);
	bool accepted = false;
	bool exit = false;
	int inputKey = 0;
	while (!exit) {
		Setup();
		GetRenderer()->DrawBox(x, y, width, height, title, true, GetRenderer()->m_hDialogBox);

		for (size_t i = 0; i < 18; i++) {
			GetRenderer()->DrawString(text[i], x, y - height / 2 + GetRenderer()->m_dialogHeaderHeight + i * 0.022f, 0, size[i], { 230, 230, 230, 255 }, true, JustifyCenter);
		}

		if (IsAJPressed(true)) {
			exit = 1;
			accepted = 1;
		} else if (KeyJustUp(VK_ESCAPE)) {
			exit = 1;
			accepted = 0;
		}
	}
	return accepted;
}

MenuInput* GetMenuInput() { return &g_menuInput; }