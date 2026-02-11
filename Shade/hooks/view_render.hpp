#pragma once
#include "ihook.hpp"

class CViewRender;
class Vector3D;

class CViewRenderHook {
private:
    using OnRenderStartFunc = void*(__fastcall*)(CViewRender*);
    static inline OnRenderStartFunc m_pOnRenderStartOrig;

    static void* __fastcall hkOnRenderStart(CViewRender* pViewRender);

public:
    static void Register();
};

class CSetupFovHook {
private:
    using SetupFovFunc = float (*__fastcall)(__int64);
    static inline SetupFovFunc m_pOverrideFovOrig;

    static float __fastcall hkSetupFov(__int64 a1);

public:
    static void Register();
};

class CSetupViewModelHook {
private:
    using SetupViewModelFunc = void* (__fastcall*)(__int64, Vector3D*, float*);
    static inline SetupViewModelFunc m_pSetupViewModelOrig;

    static void* __fastcall hkSetupViewModel(__int64 unk, Vector3D* viewmodel_offsets, float* viewmodel_fov);

public:
    static void Register();
};