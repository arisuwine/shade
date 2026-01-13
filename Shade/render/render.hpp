#pragma once
#include "utils/gui.hpp"

extern FontMap  fonts;
extern GUI      gui;

void setup_fonts();

class RenderTarget {
private:
    RenderTarget() {};

public:
    static RenderTarget& Get() {
        static RenderTarget instance;
        return instance;
    }

    void Initialize();
    void BeginScene();
};