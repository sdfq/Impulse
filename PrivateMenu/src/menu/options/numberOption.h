#pragma once

template <typename Type>
class NumberOption : public Option {
private:
    void GetInput();

    function<void(NumberOption*)> m_onUpdate;
    function<void()> m_currentOp;
    function<void()> m_function;

    ScrollOptionType m_type;
    String m_format;
    Type* m_number;
    bool* m_bool;
    Type m_step;
    Type m_min;
    Type m_max;

    shared_ptr<int> m_selectedNumberStorage;
    int* m_selectedNumber;

    DWORD m_scrollSpeed;

    bool m_hasMin;
    bool m_hasMax;
    bool m_loop;

public:
    NumberOption(ScrollOptionType type, String name) : Option(name), m_type(type), m_hasMin(false), m_hasMax(false), m_loop(false), m_scrollSpeed(100), m_function([] {}), m_onUpdate([](NumberOption* option) {}), m_currentOp([] {}) {}
    NumberOption& addToggle(bool& toggle) {
        m_bool = &toggle;
        return *this;
    }

    NumberOption& addNumber(Type& number, String format, Type step) {
        if (m_type == SELECT) {
            m_selectedNumberStorage = make_shared<int>(0);
            m_selectedNumber = m_selectedNumberStorage.get();
        }
        m_number = &number;
        m_format = format;
        m_step = step;
        return *this;
    }

    NumberOption& addSelectedNumber(int& selectedNumber) {
        m_selectedNumber = &selectedNumber;
        return *this;
    }

    NumberOption& addMin(Type min) {
        m_min = min;
        m_hasMin = true;
        return *this;
    }
    NumberOption& addMax(Type max) {
        m_max = max;
        m_hasMax = true;
        return *this;
    }

    NumberOption& addRequirement(function<bool()> func) {
        m_requirement = func;
        return *this;
    }

    NumberOption& addFunction(function<void()> func) {
        m_function = func;
        return *this;
    }

    NumberOption& addOnUpdate(function<void(NumberOption*)> update) {
        m_onUpdate = update;
        return *this;
    }

    NumberOption& addOnUpdate(function<void()> update) {
        m_onUpdate = [=](NumberOption* option) {update(); };
        return *this;
    }

    NumberOption& addCurrentOp(function<void()> func) {
        m_currentOp = func;
        return *this;
    }

    NumberOption& addHotkey() {
        m_hasHotkey = true;
        return *this;
    }

    NumberOption& addTranslation() {
        m_name.SetHasTranslation(true);
        m_tooltip.SetHasTranslation(true);
        return *this;
    }

    NumberOption& setScrollSpeed(int speed) {
        m_scrollSpeed = speed;
        return *this;
    }

    NumberOption &canBeSaved() {
        m_canBeSaved = true;
        if (SimpleIsValidAddress(m_number) && m_requirement()) {
            if (is_same<Type, int>::value) *m_number = GetConfig()->ReadInt("Numbers", m_name.GetOriginal(), (int)*m_number);
            else if (is_same<Type, int64_t>::value) *m_number = (Type)GetConfig()->ReadInt64("Numbers", m_name.GetOriginal(), (int64_t)*m_number);
            else if (is_same<Type, float>::value) *m_number = GetConfig()->ReadFloat("Numbers", m_name.GetOriginal(), (float)*m_number);
            if (m_type == TOGGLE) *m_bool = GetConfig()->ReadBool("Toggles", m_name.GetOriginal(), *m_bool);
        }
        if (m_hasMin && *m_number < m_min) *m_number = m_min;
        if (m_hasMax && *m_number > m_max) *m_number = m_max;
        return *this;
    }

    NumberOption& addTooltip(String tooltip) {
        m_tooltip.Set(tooltip);
        return *this;
    }

    NumberOption& canLoop() {
        m_loop = true;
        return *this;
    }

    void Input(int position);
    void Render(int position);
    void RenderSelected(int position);
    void HandleHotkey();
};
