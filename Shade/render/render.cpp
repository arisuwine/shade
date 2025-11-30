#include "render.hpp"

#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include "../sdk/sdk.hpp"

#include "../menu/menu.hpp"
#include "../menu/options.hpp"

#include "../features/esp.hpp"

void setup_fonts() {
    fonts.set_io();
    fonts.push("MuseoSans-500",     "c:\\USERS\\ADMINISTRATOR\\APPDATA\\LOCAL\\MICROSOFT\\WINDOWS\\FONTS\\MuseoSansCyrl-500.ttf", 15.0f);
    fonts.push("MuseoSans-500-12",  "c:\\USERS\\ADMINISTRATOR\\APPDATA\\LOCAL\\MICROSOFT\\WINDOWS\\FONTS\\MuseoSansCyrl-500.ttf", 12.0f);
    fonts.push("MuseoSans-900",     "c:\\USERS\\ADMINISTRATOR\\APPDATA\\LOCAL\\MICROSOFT\\WINDOWS\\FONTS\\MuseoSansCyrl-900.ttf", 24.0f);
    fonts.push("MuseoSans-900-10",  "c:\\USERS\\ADMINISTRATOR\\APPDATA\\LOCAL\\MICROSOFT\\WINDOWS\\FONTS\\MuseoSansCyrl-900.ttf", 13.0f);
}

void RenderTarget::initialize() {
    setup_fonts();
}

void RenderTarget::begin_scene() {
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    if (GetAsyncKeyState(VK_INSERT) & 1 || GetAsyncKeyState(VK_DELETE) & 1)
        Menu::get().toggle();

    Menu::get().render();

    gui.draw_list = ImGui::GetBackgroundDrawList();

    if (g_CNetworkClientService->m_pCNetworkGameClient->IsInGame() && g_options.esp_enabled)
        ESP::get().begin_render();

    ImGui::Render();

    g_DeviceContext->OMSetRenderTargets(1, &g_TargetView, nullptr);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}