#pragma once

class SpriteAnimation;

class Renderer
{
private:
	static float m_globalOpacity;
	float* m_opacity;
	int m_2DLayer;

public:
	float GetOptionY(int pos);
	float GetOptionYText(int pos);

	void DrawString(String text, float x, float y, int font, float scale, Color color, bool outline = false, int justify = -1, float textWrapMin = 0, float textWrapMax = 0);
	void DrawSprite(Texture texture, float x, float y, float w, float h, float heading, Color color, bool renderIfNotStreamed = true);
	void DrawSpriteUnsafe(Texture texture, float x, float y, float w, float h, float heading, Color color);
	void DrawSpriteAspect(Texture texture, float x, float y, float w, float h, float heading, Color color, bool renderIfNotStreamed = false);
	void DrawRect(float x, float y, float width, float height, Color color);
	void DrawLine(float x1, float y1, float z1, float x2, float y2, float z2, Color color);
	void DrawBox(float x, float y, float width, float height, String title = "", bool gradients = false, Texture texture = {"", ""}, bool customColor = false, Color color = {255, 255, 255, 255});
	void DrawBoxMinimized(float x, float y, float width, float height, String title, Texture texture = { "", "" });
	void DrawTitle(String title);
	void NotifyBottom(String text, int duration = 4000);
	void NotifyMap(String text, boolean showInLog = true);
	void NotifyMapColor(String text, int color, boolean showInLog = true);
	void NotifyWarning(String warning, String text);

	void SetOpacityVariable(float& opacity = m_globalOpacity);

	void Set2DLayer(int layer);
	int Get2DLayer() { return m_2DLayer; }

	void Render();
	void RenderHeader();
	void RenderSubHeader();
	void RenderBackground();
	void RenderOptionHighlight();
	void RenderFooter();
	void RenderTooltip(String toRender, bool canBeSaved, bool hasHotkey, int key = -1);
	void RenderMouseTooltip(String tooltip);

	float GetStringWidth(String str, int font, float fontsize);
	float GetStringHeight(int font, float fontsize);

	char m_tooltip[256];

	//Color m_cHeader =		{ 255, 0, 0, 255 };
	Color m_cOutline =		{ 0, 246, 255, 255 }; //{ 255, 0, 0, 255 };
	Color m_cPrimary =		{ 0, 0, 0, 255 };
	Color m_cSelection =	{ 22, 192, 198, 200 }; //{ 200, 0, 0, 200 };
	Color m_cSubHeader =	{ 0, 0, 0, 200 };
	Color m_cTitle =		{ 225, 225, 225, 255 };
	Color m_cOption =		{ 255, 255, 255, 255 };
	float m_bgOpacity = 45;

	float m_lineWidth = 0.0009f;

	float m_posX = 0.15f;
	float m_posY = 0.12f;
	float m_width = 0.235f;

	float m_dialogHeaderHeight = 0.0415f;
	float m_dialogFooterHeight = 0.01725f;

	Texture m_hTooltip = { "Bookmarks", "Tooltipbox5" };
	Texture m_hInfo = { "shared", "info_icon_32" };
	Texture m_hHeader = { "Bookmarks", "ImpulseHeader5" };
	Texture m_hFooter = { "Bookmarks", "ImpulseLogoBottomMenu" };
	Texture m_hDialogBox = { "commonmenu", "gradient_bgd" };
	Texture test = { "commonmenu", "gradient_bgd" };
	SpriteAnimation* m_hAnimatedHeader;
		
	int m_arrows = 4;

	float m_renderOptions;
	float m_optionHeight = 0.032f;

	float m_headerHeight = 0.083f;
	float m_subHeaderY;
	float m_subHeaderHeight = m_optionHeight;
	float m_backgroundY;
	float m_backgroundHeight;
	float m_footerY;
	float m_footerHeight = m_optionHeight;
	int m_scrollspeed = 10;


	float m_textSize = 0.33f;
	int m_textFont = FontChaletComprimeCologne;
	int m_breakFont = FontWindlings;

	float m_optionY;

	float m_middle;

	/*Toggles*/
	bool m_colorlessToggles = false;
	Texture GetToggleTexture(bool m_bool);
	Texture ColorlessToggleOn = {"Bookmarks", "NewOnToggle3"};
	Texture ColorlessToggleOff = { "Bookmarks", "NewOffToggle3" };
	Texture ColoredToggleOn = { "Bookmarks", "UpdatedNewToggleOn" };
	Texture ColoredToggleOff = { "Bookmarks", "UpdatedNewToggleOff" };

	/*Arrows*/
	bool m_animatedArrows = false;
};

Renderer* GetRenderer();