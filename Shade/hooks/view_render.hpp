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

    static inline uintptr_t pOnRenderStart = modules::client.Find(ON_RENDER_START);

    static void* __fastcall hkOnRenderStart(CViewRender* pViewRender);

    static inline OnRenderStart OnRenderStartOrig;

    static bool m_bIsInit;

public:
    static bool Initialize();
    static bool Shutdown();

    inline bool IsInitialized() { return m_bIsInit; }
};

class OverrideViewModelHook {
private:
    using CalcViewModel = void* (__fastcall*)(__int64, float*, float*);

    static inline uintptr_t pCalcViewModel = modules::client.Find(CALC_VIEWMODEL);

    static void* __fastcall hkCalcViewModel(__int64 unk, float* offsets, float* fov);

    static inline CalcViewModel CalcViewModelOrig;

    static bool m_bIsInit;

public:
    static bool Initialize();
    static bool Shutdown();

    inline bool IsInitialized() { return m_bIsInit; }
};