#pragma once
#include "../sdk/modules.hpp"
#include "../sdk/signatures.hpp"

#include "../sdk/math/QAngle.hpp"

class CViewRender;

static struct CViewSetupCache {
    float m_flFov;
    float m_flFovViewModel;
    QAngle m_angView;
    float m_flAspectRatio;
    BYTE m_nSomeFlags;
};

class ViewRenderHook {
private:

    using OnRenderStart = void*(__fastcall*)(CViewRender*);

    static inline uintptr_t pOnRenderStart = modules::client.find(ON_RENDER_START);

    static void* __fastcall OnRenderStartHk(CViewRender* pViewRender);

    static inline OnRenderStart oOnRenderStart;

    static bool is_init;

public:
    static bool Initialize();
    static bool Shutdown();
};

class OverrideViewModelHook {
private:
    using CalcViewModel = void* (__fastcall*)(__int64, float*, float*);

    static inline uintptr_t pCalcViewModel = modules::client.find(CALC_VIEWMODEL);

    static void* __fastcall CalcViewModelHk(__int64 unk, float* offsets, float* fov);

    static inline CalcViewModel oCalcViewModel;

    static bool is_init;

public:
    static bool Initialize();
    static bool Shutdown();
};