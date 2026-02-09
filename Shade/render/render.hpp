#pragma once
#include "utils/gui.hpp"

#include "../utils/singleton.hpp"

class RenderTarget : public Singleton<RenderTarget> {
    friend class Singleton<RenderTarget>;

private:
    void SetupFonts();

public:
    void Initialize();
    void BeginScene();
};