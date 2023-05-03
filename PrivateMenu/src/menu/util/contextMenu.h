#pragma once

struct ContextMenuOption {
	char m_name[100];
	function<void(void)> m_onPress;

	ContextMenuOption(String name, function<void(void)> func) : m_onPress(func) {
		strcpy(m_name, name);
	}
};

class ContextMenu {
private:
	bool m_isDrawing;

	float m_width;
	float m_height;
	int m_position;
	float m_optionHeight;
	initializer_list<ContextMenuOption> m_options;

public:

	void DrawMenu(int position, initializer_list<ContextMenuOption> options);
	void Update();
	bool IsDrawing() { return m_isDrawing; }
};

ContextMenu* GetContextMenu();