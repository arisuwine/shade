#pragma once
#include "../utils/singleton.hpp"

class Menu : public Singleton<Menu> {
    friend class Singleton<Menu>;

private:
    void SetupStyles();

    bool m_bShow;

    Menu() = default;

public:
    void Initialize();
    void Toggle();
    void Render();
    bool IsShowing() const { return m_bShow; }
};