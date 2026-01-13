#include "game_overlay.hpp"
#include "glow.hpp"

#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include "../sdk/sdk.hpp"
#include "../render/render.hpp"
#include "../menu/menu.hpp"

__int64(__fastcall* GameOverlayHook::CreateHook)(unsigned __int64 pFuncAddress, __int64 pDetourFuncAddress, unsigned __int64* pOriginalFuncAddressOut, int a4, __int64 sFuncName) = (decltype(CreateHook))(GameOverlayHook::pCreateHook);
void(__fastcall* GameOverlayHook::UnHook)(unsigned __int64 pOriginalFuncAddress, bool bLogFailures) = (decltype(UnHook))(GameOverlayHook::pUnHook);

bool GameOverlayHook::is_init = false;
HRESULT __stdcall GameOverlayHook::PresentHook(IDXGISwapChain* SwapChain, UINT SyncInterval, UINT Flags) {
    if (!g_Device) {
        ID3D11Texture2D* renderTarget = nullptr;

        SwapChain->GetDevice(__uuidof(g_Device), reinterpret_cast<void**>(&g_Device));
        g_Device->GetImmediateContext(&g_DeviceContext);

        SwapChain->GetBuffer(0, __uuidof(renderTarget), reinterpret_cast<void**>(&renderTarget));
        g_Device->CreateRenderTargetView(renderTarget, nullptr, &g_TargetView);
        renderTarget->Release();
    }

    if (!is_init) {
        ImGui::CreateContext();

        ImGui_ImplWin32_Init(hwnd);
        ImGui_ImplDX11_Init(g_Device, g_DeviceContext);

        RenderTarget::Get().Initialize();
        Menu::Get().Initialize();

        is_init = true;
    }

    RenderTarget::Get().BeginScene();

    return OriginalPresentFunc(SwapChain, SyncInterval, Flags);
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT GameOverlayHook::WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);

    return OriginalWndProc(hWnd, msg, wParam, lParam);
}

HWND GameOverlayHook::hwnd;
bool GameOverlayHook::Initialize() {
    hwnd = FindWindowA("SDL_APP", "Counter-Strike 2");
    if (!hwnd)
        hwnd = GetForegroundWindow();

    void* wnd_proc = reinterpret_cast<void*>(GetWindowLongPtrW(hwnd, GWLP_WNDPROC));
    if (!wnd_proc)
        return FALSE;

    CreateHook(pHkPresent, (__int64)&PresentHook, (unsigned __int64*)&OriginalPresentFunc, 1, (__int64)"DXGISwapChain_Present");
    CreateHook((unsigned __int64)wnd_proc, (__int64)WndProcHook, (unsigned __int64*)&OriginalWndProc, 1, (__int64)"WndProc");

    return TRUE;
}

bool GameOverlayHook::Shutdown() {
    UnHook((__int64)pHkPresent, 1);
    UnHook((__int64)GetWindowLongPtrW(hwnd, GWLP_WNDPROC), 1);

    if (is_init) {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();

        SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(OriginalWndProc));

        g_Device->Release();
        g_Device = nullptr;

		g_DeviceContext->Release();
		g_DeviceContext = nullptr;

		g_TargetView->Release();
		g_TargetView = nullptr;

        is_init = FALSE;
    }

    return TRUE;
}