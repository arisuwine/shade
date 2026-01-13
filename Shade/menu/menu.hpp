#pragma once

class Menu {
private:
    void SetupStyles();

    bool show;

    Menu() {}

public:
    void Initialize();
    void Toggle();
    void Render();
    static Menu& Get() {
        static Menu instance;
        return instance;
    }
};