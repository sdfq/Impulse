#pragma once

class Option;

struct InputCombination {
	bool m_caps;
	DWORD m_input;
	String m_output;
	String m_outputWithCaps;
};

class MenuInput {
private:
	void Setup();
	vector<function<void()>> m_functionQueue;

public:
	void AddToQueue(function<void()> func) { m_functionQueue.push_back(func); }

	void Update();
	void GetInput(string& input, InputCombination keys[], int size, int maxLength);

	template <typename Type>
	bool Number(String name, Type* output, Type min, bool hasMin, Type max, bool hasMax, String format);
	bool Text(String name, string& output, int min, int max);
	bool Hotkey(String name, Option* option);
	bool Key(String name, int* key, bool* isControllerOutput, bool controller);
	bool Col(String name, Color& col);
	bool Accept(String name, float x, float y, float width, float height, const char* title, float size[18], String text[18]);
};

MenuInput* GetMenuInput();

static InputCombination numberCombinations[] = {
	{false, '1', "1", "1"},
	{false, '2', "2", "2"},
	{false, '3', "3", "3"},
	{false, '4', "4", "4"},
	{false, '5', "5", "5"},
	{false, '6', "6", "6"},
	{false, '7', "7", "7"},
	{false, '8', "8", "8"},
	{false, '9', "9", "9"},
	{false, '0', "0", "0"},
	{false, VK_OEM_PERIOD, ".", "."},
	{false, VK_OEM_COMMA, ".", "." },
	{false, VK_OEM_MINUS, "-", "-" },
	{false, VK_NUMPAD1, "1", "1" },
	{false, VK_NUMPAD2, "2", "2"},
	{false, VK_NUMPAD3, "3", "3"},
	{false, VK_NUMPAD4, "4", "4"},
	{false, VK_NUMPAD5, "5", "5"},
	{false, VK_NUMPAD6, "6", "6"},
	{false, VK_NUMPAD7, "7", "7"},
	{false, VK_NUMPAD8, "8", "8"},
	{false, VK_NUMPAD9, "9", "9"},
	{false, VK_NUMPAD0, "0", "0"}
};

static InputCombination normalCombinations[] = {
	{false, '1', "1", "!" },
	{false, '2', "2", "@" },
	{false, '3', "3", "#" },
	{false, '4', "4", "$" },
	{false, '5', "5", "%" },
	{false, '6', "6", "^" },
	{false, '7', "7", "&" },
	{false, '8', "8", "*" },
	{false, '9', "9", "(" },
	{false, '0', "0", ")" },
	{false, 'A', "a", "A" },
	{false, 'B', "b", "B" },
	{false, 'C', "c", "C" },
	{false, 'D', "d", "D" },
	{false, 'E', "e", "E" },
	{false, 'F', "f", "F" },
	{false, 'G', "g", "G" },
	{false, 'H', "h", "H" },
	{false, 'I', "i", "I" },
	{false, 'J', "j", "J" },
	{false, 'K', "k", "K" },
	{false, 'L', "l", "L" },
	{false, 'M', "m", "M" },
	{false, 'N', "n", "N" },
	{false, 'O', "o", "O" },
	{false, 'P', "p", "P" },
	{false, 'Q', "q", "Q" },
	{false, 'R', "r", "R" },
	{false, 'S', "s", "S" },
	{false, 'T', "t", "T" },
	{false, 'U', "u", "U" },
	{false, 'V', "v", "V" },
	{false, 'W', "w", "W" },
	{false, 'X', "x", "X" },
	{false, 'Y', "y", "Y" },
	{false, 'Z', "z", "Z" },
	{false, VK_OEM_7,"'", "@"},
	{false, VK_OEM_MINUS,"-", "_"},
	{false, VK_OEM_PLUS,"=", "+" },
	{false, VK_OEM_1, ";", ":" },
	{false, VK_OEM_2, "/", "?" },
	{false, VK_OEM_3, "`", "~" },
	{false, VK_OEM_4, "[", "{" },
	{false, VK_OEM_5, "\\", "|"},
	{false, VK_OEM_6, "]", "}" },
	{false, VK_OEM_7, "!", "§" },
	{false, VK_OEM_8, "]", "}" },
	{false, VK_OEM_COMMA,",", "<" },
	{false, VK_OEM_PERIOD, ".", ">" },
	{false, VK_NUMPAD1, "1", "1" },
	{false, VK_NUMPAD2, "2", "2"},
	{false, VK_NUMPAD3, "3", "3"},
	{false, VK_NUMPAD4, "4", "4"},
	{false, VK_NUMPAD5, "5", "5"},
	{false, VK_NUMPAD6, "6", "6"},
	{false, VK_NUMPAD7, "7", "7"},
	{false, VK_NUMPAD8, "8", "8"},
	{false, VK_NUMPAD9, "9", "9"},
	{false, VK_NUMPAD0, "0", "0"}
};
