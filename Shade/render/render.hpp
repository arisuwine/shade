#pragma once
#include "utils/gui.hpp"

#include "../utils/singleton.hpp"

class RenderTarget {
private:
    static void SetupFonts();

public:
    static void Initialize();
    static void BeginScene();
};