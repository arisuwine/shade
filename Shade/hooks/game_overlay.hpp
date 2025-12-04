#pragma once
#include <d3d11.h>

#include "../sdk/modules.hpp"
#include "../sdk/signatures.hpp"

class GameOverlayHook {
private:
    using OriginalPresent = HRESULT(*)(IDXGISwapChain*, UINT, UINT);

    static inline uintptr_t pCreateHook         = modules::overlay_renderer.find(CREATE_HOOK);
    static inline uintptr_t pHkPresent          = modules::overlay_renderer.find(HK_PRESENT);
    static inline uintptr_t pUnHook             = modules::overlay_renderer.find(UN_HOOK);

    static __int64(__fastcall* CreateHook)(unsigned __int64 pFuncAddress, __int64 pDetourFuncAddress, unsigned __int64* pOriginalFuncAddressOut, int a4, __int64 sFuncName);
    static void(__fastcall* UnHook)(unsigned __int64 pOriginalFuncAddress, bool bLogFailures);

    static inline OriginalPresent OriginalPresentFunc;
    static HRESULT __stdcall PresentHook(IDXGISwapChain* swap_chain, UINT SyncInterval, UINT Flags);

    static inline WNDPROC OriginalWndProc;
    static LRESULT WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    static HWND hwnd;
    static bool is_init;

public:
    GameOverlayHook() = delete;

    static bool initialize();
    static void shutdown();
};
