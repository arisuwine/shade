#include "render.hpp"

#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include "../sdk/sdk.hpp"

#include "../menu/menu.hpp"
#include "../menu/options.hpp"

#include "../features/esp.hpp"

void RenderTarget::SetupFonts() {
    Fonts::Get().Initialize();
    Fonts::Get().Add("MuseoSans-500",       "c:\\USERS\\ADMINISTRATOR\\APPDATA\\LOCAL\\MICROSOFT\\WINDOWS\\FONTS\\MuseoSansCyrl-500.ttf", 15.0f);
    Fonts::Get().Add("MuseoSans-500-12",    "c:\\USERS\\ADMINISTRATOR\\APPDATA\\LOCAL\\MICROSOFT\\WINDOWS\\FONTS\\MuseoSansCyrl-500.ttf", 12.0f);
    Fonts::Get().Add("MuseoSans-900",       "c:\\USERS\\ADMINISTRATOR\\APPDATA\\LOCAL\\MICROSOFT\\WINDOWS\\FONTS\\MuseoSansCyrl-900.ttf", 24.0f);
    Fonts::Get().Add("MuseoSans-900-10",    "c:\\USERS\\ADMINISTRATOR\\APPDATA\\LOCAL\\MICROSOFT\\WINDOWS\\FONTS\\MuseoSansCyrl-900.ttf", 13.0f);
    Fonts::Get().Add("Verdana-12",          "C:\\WINDOWS\\FONTS\\VERDANA.TTF", 12.0f);
    Fonts::Get().Add("Verdana-13",          "C:\\WINDOWS\\FONTS\\VERDANA.TTF", 13.0f);
}

void RenderTarget::Initialize() {
    SetupFonts();
}

void RenderTarget::BeginScene() {
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();

    ImGui::NewFrame();

    if (GetAsyncKeyState(VK_INSERT) & 1)
        Menu::Get().Toggle();

    Menu::Get().Render();
    Render::Get().SetDrawList(ImGui::GetBackgroundDrawList());

    if (g_CNetworkClientService->m_pCNetworkGameClient->IsInGame() && g_Options.esp_enabled)
        ESP::Get().BeginRender();

    ImGui::Render();

    g_DeviceContext->OMSetRenderTargets(1, &g_TargetView, nullptr);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}