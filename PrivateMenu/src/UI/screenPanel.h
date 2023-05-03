#pragma once

class ScreenPanel {
	float m_opacity = 0;
	const float xStart = 1;
	const float yStart = 0.1f;
	const float ySize = 0.035f;
	const float yDistance = 0.04f;
	const float baseSlide = 0.02f;
	const float maxSlide = 0.12f;
	struct ButtonStruct {
		float m_slide;
		TranslationString m_name;
		function<void()> m_onClick;
		function<bool()> m_requirement;
	};

	vector<ButtonStruct> m_buttons;

public:
	void addButton(String name, bool translation, function<void()> onClick, function<bool()> requirement) {
		m_buttons.push_back({ baseSlide, TranslationString(name, translation), onClick, requirement });
	}
	void Init();
	void FadeIn();
	void FadeOut();
	void Render();
	vector<ButtonStruct>& GetButtons() { return m_buttons; }
};

ScreenPanel* GetScreenPanel();