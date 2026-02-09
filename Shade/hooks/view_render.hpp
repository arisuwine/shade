#pragma once
#include "ihook.hpp"

class CViewRender;

class CViewRenderHook {
private:
    using OnRenderStartFunc = void*(__fastcall*)(CViewRender*);
    static inline OnRenderStartFunc m_pOnRenderStartOrig;

    static void* __fastcall hkOnRenderStart(CViewRender* pViewRender);

public:
    static void Register();
};

class COverrideFovHook {
private:
    using OverrideFovFunc = float (*__fastcall)(__int64, __int64);
    static inline OverrideFovFunc m_pOverrideFovOrig;

    static float __fastcall hkOverrideFov(__int64 a1, __int64 a2);

public:
    static void Register();
};

class CSetupViewModelHook {
private:
    using SetupViewModelFunc = void* (__fastcall*)(__int64, float*, float*);
    static inline SetupViewModelFunc m_pSetupViewModelOrig;

    static void* __fastcall hkSetupViewModel(__int64 unk, float* offsets, float* fov);

public:
    static void Register();
};