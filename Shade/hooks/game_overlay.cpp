#include "game_overlay.hpp"
#include "glow.hpp"

#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include "../sdk/sdk.hpp"
#include "../render/render.hpp"
#include "../menu/menu.hpp"

__int64(__fastcall* GameOverlayHook::CreateHook)(unsigned __int64 pFuncAddress, __int64 pDetourFuncAddress, unsigned __int64* pOriginalFuncAddressOut, int a4, __int64 sFuncName) = (decltype(CreateHook))(GameOverlayHook::pCreateHook);
void(__fastcall* GameOverlayHook::UnHook)(unsigned __int64 pOriginalFuncAddress, bool bLogFailures) = (decltype(UnHook))(GameOverlayHook::pUnHook);
bool GameOverlayHook::m_bIsInit = false;
HWND GameOverlayHook::m_hwnd;

HRESULT __stdcall GameOverlayHook::hkPresent(IDXGISwapChain* SwapChain, UINT SyncInterval, UINT Flags) {
    if (!g_Device) {
        ID3D11Texture2D* renderTarget = nullptr;

        SwapChain->GetDevice(__uuidof(g_Device), reinterpret_cast<void**>(&g_Device));
        g_Device->GetImmediateContext(&g_DeviceContext);

        SwapChain->GetBuffer(0, __uuidof(renderTarget), reinterpret_cast<void**>(&renderTarget));
        g_Device->CreateRenderTargetView(renderTarget, nullptr, &g_TargetView);
        renderTarget->Release();
    }

    if (!m_bIsInit) {
        ImGui::CreateContext();

        ImGui_ImplWin32_Init(m_hwnd);
        ImGui_ImplDX11_Init(g_Device, g_DeviceContext);

        RenderTarget::Get().Initialize();
        Menu::Get().Initialize();

        m_bIsInit = true;
    }

    RenderTarget::Get().BeginScene();

    return PresentOrig(SwapChain, SyncInterval, Flags);
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT GameOverlayHook::hkWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);

    return WndProcOrig(hWnd, msg, wParam, lParam);
}

bool GameOverlayHook::Initialize() {
    m_hwnd = FindWindowA("SDL_APP", "Counter-Strike 2");
    if (!m_hwnd)
        m_hwnd = GetForegroundWindow();

    void* wnd_proc = reinterpret_cast<void*>(GetWindowLongPtrW(m_hwnd, GWLP_WNDPROC));
    if (!wnd_proc)
        return FALSE;

    CreateHook(pHkPresent, (__int64)&hkPresent, (unsigned __int64*)&PresentOrig, 1, (__int64)"DXGISwapChain_Present");
    CreateHook((unsigned __int64)wnd_proc, (__int64)hkWndProc, (unsigned __int64*)&WndProcOrig, 1, (__int64)"WndProc");

    return TRUE;
}

bool GameOverlayHook::Shutdown() {
    UnHook((__int64)pHkPresent, 1);
    UnHook((__int64)GetWindowLongPtrW(m_hwnd, GWLP_WNDPROC), 1);

    if (m_bIsInit) {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();

        g_Device->Release();
        g_Device = nullptr;

		g_DeviceContext->Release();
		g_DeviceContext = nullptr;

		g_TargetView->Release();
		g_TargetView = nullptr;

        m_bIsInit = FALSE;
    }

    return TRUE;
}