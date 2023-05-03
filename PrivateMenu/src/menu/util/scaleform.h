#pragma once

class Scaleform
{
private:
	int m_offset;
	bool m_prepared;
	int m_scaleForm;
public:
	void DrawLargeMessage(String title, String message, int color, int duration);
	void PrepareInstructionalButtons();
	void DrawInstructional(String text, String button);
	void FinishInstructionalButtons();
};

Scaleform* GetScaleform();