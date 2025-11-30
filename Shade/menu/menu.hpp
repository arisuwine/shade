#pragma once

class Menu {
private:
    void setup_styles();

    bool show;

    Menu() {}

public:
    void initialize();
    void toggle();
    void render();
    static Menu& get() {
        static Menu instance;
        return instance;
    }
};