#pragma once
#include <d3d11.h>

#include "../sdk/modules.hpp"
#include "../sdk/signatures.hpp"

class GameOverlayHook {
private:
    using OriginalPresent = HRESULT(*)(IDXGISwapChain*, UINT, UINT);

    static inline uintptr_t pCreateHook         = modules::overlay_renderer.Find(CREATE_HOOK);
    static inline uintptr_t pHkPresent          = modules::overlay_renderer.Find(HK_PRESENT);
    static inline uintptr_t pUnHook             = modules::overlay_renderer.Find(UN_HOOK);

    static __int64(__fastcall* CreateHook)(unsigned __int64 pFuncAddress, __int64 pDetourFuncAddress, unsigned __int64* pOriginalFuncAddressOut, int a4, __int64 sFuncName);
    static void(__fastcall* UnHook)(unsigned __int64 pOriginalFuncAddress, bool bLogFailures);

    static inline OriginalPresent PresentOrig;
    static HRESULT __stdcall hkPresent(IDXGISwapChain* swap_chain, UINT SyncInterval, UINT Flags);

    static inline WNDPROC WndProcOrig;
    static LRESULT hkWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    static HWND m_hwnd;
    static bool m_bIsInit;

public:
    static bool Initialize();
    static bool Shutdown();

    inline bool IsInitialized() { return m_bIsInit; }
};
