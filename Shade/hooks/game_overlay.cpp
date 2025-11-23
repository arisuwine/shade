#include "game_overlay.hpp"
#include "../render/render.hpp"

__int64(__fastcall* game_overlay::CreateHook)(unsigned __int64 pFuncAddress, __int64 pDetourFuncAddress, unsigned __int64* pOriginalFuncAddressOut, int a4, __int64 sFuncName) = (decltype(CreateHook))(game_overlay::pCreateHook);
void(__fastcall* game_overlay::UnHook)(unsigned __int64 pOriginalFuncAddress, bool bLogFailures) = (decltype(UnHook))(game_overlay::pUnHook);

HRESULT __stdcall game_overlay::PresentHook(IDXGISwapChain* swap_chain, UINT SyncInterval, UINT Flags) {
    render::present_scene(swap_chain, SyncInterval, Flags);
    return OriginalPresentFunc(swap_chain, SyncInterval, Flags);
}

LRESULT game_overlay::WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    bool returnRes = false;
    LRESULT res = render::wndProc(hWnd, msg, wParam, lParam, returnRes);
    if (returnRes)
        return res;

    return OriginalWndProc(hWnd, msg, wParam, lParam);
}

BOOL game_overlay::init_hooks() {
    render::hwnd = FindWindowA("SDL_APP", "Counter-Strike 2");
    if (!render::hwnd)
        render::hwnd = GetForegroundWindow();

    void* wnd_proc = reinterpret_cast<void*>(GetWindowLongPtrW(render::hwnd, GWLP_WNDPROC));
    if (!wnd_proc)
        return FALSE;

    CreateHook(pHkPresent, (__int64)&PresentHook, (unsigned __int64*)&OriginalPresentFunc, 1, (__int64)"DXGISwapChain_Present");
    CreateHook((unsigned __int64)wnd_proc, (__int64)WndProcHook, (unsigned __int64*)&OriginalWndProc, 1, (__int64)"WndProc");

    return TRUE;
}

void game_overlay::unhook() {
    UnHook((__int64)&OriginalPresentFunc, 1);
    UnHook((__int64)&OriginalWndProc, 1);
}