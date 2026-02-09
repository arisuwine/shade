//#include "game_overlay.hpp"
//#include "glow.hpp"
//
//#include "imgui_impl_win32.h"
//#include "imgui_impl_dx11.h"
//
//#include "../sdk/data/CSwapChainDx11.hpp"
//
//#include "../sdk/sdk.hpp"
//#include "../render/render.hpp"
//#include "../menu/menu.hpp"

//bool GameOverlayHook::Initialize() {
//    if (m_bIsInit)
//        return true;
//
//    m_pCreateHook = modules::overlay_renderer.Find(CREATE_HOOK);
//    if (!m_pCreateHook)
//        LOG_AND_RETURN("[-] GameOverlayHook: Failed to find CREATE_HOOK signature.\n");
//
//    m_pHkPresent = modules::overlay_renderer.Find(HK_PRESENT);
//    if (!m_pHkPresent)
//        LOG_AND_RETURN("[-] GameOverlayHook: Failed to find HK_PRESENT signature.\n");
//
//    m_pUnHook = modules::overlay_renderer.Find(UN_HOOK);
//    if (!m_pUnHook)
//        LOG_AND_RETURN("[-] GameOverlayHook: Failed to find UN_HOOK signature.\n");
//
//    CreateHook = decltype(CreateHook)(m_pCreateHook);
//    UnHook = decltype(UnHook)(m_pUnHook);
//
//    m_hwnd = FindWindowA("SDL_APP", "Counter-Strike 2");
//    if (!m_hwnd)
//        m_hwnd = GetForegroundWindow();
//
//    m_pWndProc = reinterpret_cast<void*>(GetWindowLongPtrW(m_hwnd, GWLP_WNDPROC));
//    if (!m_pWndProc)
//        return false;
//
//    CreateHook(static_cast<unsigned __int64>(m_pHkPresent), reinterpret_cast<__int64>(&hkPresent), reinterpret_cast<unsigned __int64*>(&PresentOrig), 1, reinterpret_cast<__int64>("DXGISwapChain_Present"));
//    CreateHook(reinterpret_cast<unsigned __int64>(m_pWndProc), reinterpret_cast<__int64>(&hkWndProc), reinterpret_cast<unsigned __int64*>(&WndProcOrig), 1, reinterpret_cast <__int64>("WndProc"));
//
//    return true;
//}
//
//bool GameOverlayHook::Shutdown() {
//    UnHook(static_cast<unsigned __int64>(m_pHkPresent), true);
//    UnHook(reinterpret_cast<unsigned __int64>(m_pWndProc), true);
//
//    if (m_bIsInit) {
//        ImGui_ImplDX11_Shutdown();
//        ImGui_ImplWin32_Shutdown();
//        ImGui::DestroyContext();
//
//        g_Device->Release();
//        g_Device = nullptr;
//
//        g_DeviceContext->Release();
//        g_DeviceContext = nullptr;
//
//        g_TargetView->Release();
//        g_TargetView = nullptr;
//
//        m_bIsInit = false;
//    }
//
//    return true;
//}
//
//HRESULT __stdcall GameOverlayHook::hkPresent(IDXGISwapChain* SwapChain, UINT SyncInterval, UINT Flags) {
//    if (!g_Device) {
//        ID3D11Texture2D* renderTarget = nullptr;
//
//        SwapChain->GetDevice(__uuidof(g_Device), reinterpret_cast<void**>(&g_Device));
//        g_Device->GetImmediateContext(&g_DeviceContext);
//
//        SwapChain->GetBuffer(0, __uuidof(renderTarget), reinterpret_cast<void**>(&renderTarget));
//        g_Device->CreateRenderTargetView(renderTarget, nullptr, &g_TargetView);
//        renderTarget->Release();
//    }
//
//    if (!m_bIsInit) {
//        ImGui::CreateContext();
//
//        ImGui_ImplWin32_Init(m_hwnd);
//        ImGui_ImplDX11_Init(g_Device, g_DeviceContext);
//
//        CSwapChainDx11* cswapchain = g_EngineServiceMgr->GetEngineSwapChain();
//        IDXGISwapChain* swapchaintest = cswapchain->m_pDXGISwapChain;
//
//        RenderTarget::Get().Initialize();
//        Menu::Get().Initialize();
//
//        m_bIsInit = true;
//    }
//
//    RenderTarget::Get().BeginScene();
//
//    return PresentOrig(SwapChain, SyncInterval, Flags);
//}
//
//extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//LRESULT GameOverlayHook::hkWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
//    ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
//
//    return WndProcOrig(hWnd, msg, wParam, lParam);
//}