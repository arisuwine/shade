#pragma once
#include <d3d11.h>
#include "../sdk/modules.hpp"
#include "../sdk/signatures.hpp"

    //typedef HRESULT(*OriginalPresent)(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags);
    //extern OriginalPresent original_present;

    //extern pattern_scan overlay_renderer;

    //extern uintptr_t pHkPresent;

    //extern uintptr_t pCreateHook;
    //extern __int64(__fastcall* CreateHook)(unsigned __int64 pFuncAddress, __int64 pDetourFuncAddress, unsigned __int64* pOriginalFuncAddressOut, int a4, __int64 sFuncName);

    //extern uintptr_t pUnHook;
    //extern void(__fastcall* UnHook)(unsigned __int64 pOriginalFuncAddress, bool bLogFailures);

    //HRESULT __stdcall present_hook(IDXGISwapChain* swap_chain, UINT SyncInterval, UINT Flags);


    //LRESULT wnd_proc_hook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    //void init_hooks();
    //void unhook();

class game_overlay {
private:
    //typedef HRESULT(*OriginalPresent)(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags);
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

public:
    game_overlay() {}
    ~game_overlay() {}

    BOOL init_hooks();
};
