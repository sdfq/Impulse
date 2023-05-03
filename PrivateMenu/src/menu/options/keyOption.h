#pragma once

class KeyOption : public Option {
private:
	function<void(KeyOption*)> m_onUpdate;
	function<void()> m_currentOp;
	function<void()> m_function;
	int* m_key;
	bool* m_isController;
	bool m_controllerSupport;

public:

	KeyOption(String name) : Option(name), m_function([] {}), m_onUpdate([](KeyOption* option) {}), m_key(nullptr), m_currentOp([] {}), m_controllerSupport(false), m_isController(nullptr) {}

	KeyOption& addFunction(function<void()> func) {
		m_function = func;
		return *this;
	}

	KeyOption& addRequirement(function<bool()> func) {
		m_requirement = func;
		return *this;
	}

	KeyOption& addOnUpdate(function<void(KeyOption*)> update) {
		m_onUpdate = update;
		return *this;
	}

	KeyOption& addCurrentOp(function<void()> func) {
		m_currentOp = func;
		return *this;
	}

	KeyOption& addKey(int& key) {
		key = GetConfig()->ReadInt("Keys", m_name.GetOriginal(), key);
		m_key = &key;
		return *this;
	}

	KeyOption& addKeyWithControllerSupport(int& key, bool& isController) {
		isController = GetConfig()->ReadBool("KeysController", m_name.GetOriginal(), isController);
		key = GetConfig()->ReadInt("Keys", m_name.GetOriginal(), key);
		m_isController = &isController;
		m_controllerSupport = true;
		m_key = &key;
		return *this;
	}

	KeyOption& addControllerSupport(bool& isController) {
		isController = GetConfig()->ReadBool("KeysController", m_name.GetOriginal(), isController);
		m_isController = &isController;
		m_controllerSupport = true;
		return *this;
	}

	KeyOption& addHotkey() {
		m_hasHotkey = true;
		return *this;
	}

	KeyOption& addTranslation() {
		m_name.SetHasTranslation(true);
		m_tooltip.SetHasTranslation(true);
		return *this;
	}

	KeyOption &canBeSaved() {
		m_canBeSaved = true;
		return *this;
	}

	KeyOption& addTooltip(String tooltip) {
		m_tooltip.Set(tooltip);
		return *this;
	}

	void Input(int position);
	void Render(int position);
	void RenderSelected(int position);
	void HandleHotkey();
};
