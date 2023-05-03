#pragma once

class UIFrame;

class UIWindow {
protected:
	UIFrame * m_parent;
	vector<UIComponent*> m_components;
	TranslationString m_name;
	bool m_renderEveryFrame;
	function<bool()> m_renderThisFrame;
	bool m_minimized;
	bool m_canBeClosed;
	bool m_canBeMinimized;

public:
	bool m_isFading;
	bool m_renderName;
	float m_opacity;
	float m_headerHeight;
	Vector2 m_position;
	Vector2 m_size;

	UIWindow() : m_name(TranslationString("")), m_headerHeight(GetRenderer()->m_dialogHeaderHeight), m_opacity(0), m_minimized(false), m_position({ 0, 0 }), m_size({ 0, 0 }), m_renderEveryFrame(true), m_canBeClosed(true), m_canBeMinimized(true), m_isFading(false), m_renderName(true){ }
	UIWindow(String name, bool translate, float x, float y, float w, float h) : m_name(TranslationString(name, translate)), m_headerHeight(GetRenderer()->m_dialogHeaderHeight), m_opacity(0), m_minimized(false), m_position({ x, y }), m_size({ w, h }), m_renderEveryFrame(true), m_canBeClosed(true), m_canBeMinimized(true),m_isFading(false), m_renderName(true) { }

	template<typename T>
	void addComponent(T* component) {
		m_components.push_back((UIComponent*)component);
		component->setParent(this);
	}

	void renderEveryFrame(bool toggle) { m_renderEveryFrame = toggle; }
	void renderThisFrameRequirement(function<bool()> func) { m_renderThisFrame = func; }
	bool shouldRenderThisFrame() { return m_renderEveryFrame || m_renderThisFrame(); }

	void setCanBeClosed(bool toggle) { m_canBeClosed = toggle; }
	bool canBeClosed() { return m_canBeClosed; }
	void setCanBeMinimized(bool toggle) { m_canBeMinimized = toggle; }
	bool canBeMinimized() { return m_canBeMinimized; }

	virtual void update() {
		if (m_minimized) return;
		for (auto& component : m_components) {
			component->update();
		}
	}

	void ASyncUpdate() {
		if (m_minimized) return;
		for (auto& component : m_components) {
			component->ASyncUpdate();
		}
	}

	void minimize() {
		m_minimized ^= true;
	}

	bool isMinimized() { return m_minimized; }

	void setHeaderHeight(float height) {
		m_headerHeight = height;
	}

	virtual void setName(String name) {
		m_name.Set(name);
	}

	TranslationString& getName() { return m_name; }

	virtual bool within(float x, float y) {
		bool within = (Utils::Within(x, m_position.x - m_size.x / 2, m_position.x + m_size.x / 2) && Utils::Within(y, m_position.y - m_size.y / 2, m_position.y + m_size.y / 2));
		if (m_minimized) return within && Utils::Within(y, m_position.y - m_size.y / 2, m_position.y - m_size.y / 2 + m_headerHeight);
		return within;
	}

	virtual bool withinHeaderY(float y) {
		return Utils::Within(y, m_position.y - m_size.y / 2, m_position.y - m_size.y / 2 + m_headerHeight);
	}

	virtual void render() {
		GetRenderer()->SetOpacityVariable(m_opacity);
		static float xSize = 0.02f * 1.2f, ySize = 0.03f * 1.2f, xOffset = 0.01f, xOffset2 = 0.0225f, yOffset = 0.015f;
		if (m_minimized) {
			GetRenderer()->DrawBoxMinimized(m_position.x, m_position.y, m_size.x, m_size.y, m_name.Get(), GetRenderer()->m_hDialogBox);
			GetRenderer()->DrawSprite({ "mpleaderboard", "leaderboard_plus_icon" }, m_position.x + m_size.x / 2 - (canBeClosed() ? xOffset2 : xOffset), m_position.y - m_size.y / 2 + yOffset, xSize, ySize, 0, { 255, 255, 255, 255 });
		} else {
			GetRenderer()->DrawBox(m_position.x, m_position.y, m_size.x, m_size.y, m_renderName ? m_name.Get() : "", true, GetRenderer()->m_hDialogBox);
			for (auto& component : m_components) {
				component->render();
			}
			GetRenderer()->DrawSprite({ "mpleaderboard", "leaderboard_minus_icon" }, m_position.x + m_size.x / 2 - (canBeClosed() ? xOffset2 : xOffset), m_position.y - m_size.y / 2 + yOffset, xSize, ySize, 0, { 255, 255, 255, 255 });
		}
		if (canBeClosed())GetRenderer()->DrawSprite({ "mpleaderboard", "leaderboard_plus_icon" }, m_position.x + m_size.x / 2 - xOffset, m_position.y - m_size.y / 2 + yOffset, xSize, ySize, 45, { 255, 255, 255, 255 });
		if (canBeClosed())GetRenderer()->DrawSprite({ "mpleaderboard", "leaderboard_voteblank_icon" }, m_position.x + m_size.x / 2 - xOffset, m_position.y - m_size.y / 2 + yOffset, xSize, ySize, 0, { 255, 255, 255, 255 });
		GetRenderer()->DrawSprite({ "mpleaderboard", "leaderboard_voteblank_icon" }, m_position.x + m_size.x / 2 - (canBeClosed() ? xOffset2 : xOffset), m_position.y - m_size.y / 2 + yOffset, xSize, ySize, 0, { 255, 255, 255, 255 });
	}

	virtual void scrollEvent(int scroll) {
		for (auto& component : m_components) component->scrollEvent(scroll);
	}

	void setParent(UIFrame* frame) {
		m_parent = frame;
	}

	void fadeIn(function<void(void)> callback) {
		GetFiberPool()->DoJob([this, callback] {
			while (m_opacity < 1.0f) {
				m_isFading = true;
				m_opacity = Utils::Clamp(m_opacity + 1.5f * Backend::GetDeltaTime(), 0.0, 1.0); GetFiberManager()->GoToMainFiber();
			}callback(); m_isFading = false; });
	}

	void fadeOut(function<void(void)> callback) {
		GetFiberPool()->DoJob([this, callback] {
			while (m_opacity > 0.0f) {
				m_isFading = true;
				m_opacity = Utils::Clamp(m_opacity - 1.5f * Backend::GetDeltaTime(), 0.0, 1.0); GetFiberManager()->GoToMainFiber();
			}callback(); m_isFading = false; });
	}
};