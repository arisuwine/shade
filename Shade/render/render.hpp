#pragma once
#include "utils/gui.hpp"

extern FontMap  fonts;
extern GUI      gui;

void setup_fonts();

class RenderTarget {
private:
    RenderTarget() {};

public:
    static RenderTarget& get() {
        static RenderTarget instance;
        return instance;
    }

    void initialize();
    void begin_scene();
};