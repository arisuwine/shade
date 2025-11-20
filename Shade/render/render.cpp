#include "render.hpp"

using namespace render::gui;

HWND render::hwnd;
int width, height;

IDXGISwapChain*         render::g_SwapChain     = nullptr;
ID3D11Device*           render::g_Device        = nullptr;
ID3D11DeviceContext*    render::g_DeviceContext = nullptr;
ID3D11RenderTargetView* render::g_TargetView    = nullptr;

uintptr_t CGameEntitySystem::handle = modules::client.find(GAME_ENTITY_SYSTEM);
uintptr_t view_matrix::handle = modules::client.find(VIEW_MATRIX);
uintptr_t CCSPlayerPawn::local_controller_handle = modules::client.find(LOCAL_PLAYER_CONTROLLER);

font_map render::fonts;
draw_object render::draw;

void render::setup_fonts() {
    fonts.set_io();
    fonts.push("MuseoSans-500", "c:\\USERS\\ADMINISTRATOR\\APPDATA\\LOCAL\\MICROSOFT\\WINDOWS\\FONTS\\MuseoSansCyrl-500.ttf", 15.0f);
    fonts.push("MuseoSans-500_12", "c:\\USERS\\ADMINISTRATOR\\APPDATA\\LOCAL\\MICROSOFT\\WINDOWS\\FONTS\\MuseoSansCyrl-500.ttf", 12.0f);
    fonts.push("MuseoSans-900", "c:\\USERS\\ADMINISTRATOR\\APPDATA\\LOCAL\\MICROSOFT\\WINDOWS\\FONTS\\MuseoSansCyrl-900.ttf", 24.0f);
    fonts.push("MuseoSans-900_10", "c:\\USERS\\ADMINISTRATOR\\APPDATA\\LOCAL\\MICROSOFT\\WINDOWS\\FONTS\\MuseoSansCyrl-900.ttf", 13.0f);
}

std::vector<CCSPlayerPawn*> pawns;
LocalPlayer* local_player;

void render::draw_information() {
    uintptr_t controller, pawn;
    pawns.clear();

    LocalPlayer::get().update();

    for (size_t i = 0; i < 64; i++) {
        controller = CGameEntitySystem::GetEntityByIndex(i);
        if (!controller)
            continue;

        pawn = CGameEntitySystem::GetPawnByController(controller);
        if (!pawn)
            continue;

        if (pawn == reinterpret_cast<uintptr_t>(LocalPlayer::get().get_pawn())) {
            continue;
        }

        pawns.push_back(reinterpret_cast<CCSPlayerPawn*>(pawn));
    }

    size_t i = 0;
    for (const auto& pawn : pawns) {
        visuals draw_visuals(pawn);

        draw_visuals.render_name();
        draw_visuals.render_box();
        //draw_visuals.render_health();
        draw_visuals.render_skeleton();

        ++i;
    }
}

void render::present_scene(IDXGISwapChain* SwapChain, UINT syncInterval, UINT flags) {
    if (!g_Device) {
        ImGui_ImplWin32_EnableDpiAwareness();
        float main_scale = ImGui_ImplWin32_GetDpiScaleForMonitor(::MonitorFromPoint(POINT{ 0, 0 }, MONITOR_DEFAULTTOPRIMARY));

        ID3D11Texture2D* renderTarget = nullptr;
        ID3D11Texture2D* backBuffer = nullptr;
        D3D11_TEXTURE2D_DESC backBufferDesc = { 0 };

        SwapChain->GetDevice(__uuidof(g_Device), reinterpret_cast<void**>(&g_Device));
        g_Device->GetImmediateContext(&g_DeviceContext);

        SwapChain->GetBuffer(0, __uuidof(renderTarget), reinterpret_cast<void**>(&renderTarget));
        g_Device->CreateRenderTargetView(renderTarget, nullptr, &g_TargetView);
        renderTarget->Release();

        SwapChain->GetBuffer(0, __uuidof(backBuffer), reinterpret_cast<void**>(&backBuffer));
        backBuffer->GetDesc(&backBufferDesc);
        width = backBufferDesc.Width;
        height = backBufferDesc.Height;
        backBuffer->Release();

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        ImGui::StyleColorsDark();

        ImGuiStyle& style = ImGui::GetStyle();
        style.ScaleAllSizes(main_scale);
        style.FontScaleDpi = main_scale;

        // Setup Platform/Renderer backends
        ImGui_ImplWin32_Init(hwnd);
        ImGui_ImplDX11_Init(g_Device, g_DeviceContext);
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    draw.draw_list = ImGui::GetForegroundDrawList();

    setup_fonts();
    //draw_menu();
    draw_information();

    ImGui::Render();

    g_DeviceContext->OMSetRenderTargets(1, &g_TargetView, nullptr);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT render::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, bool& returnRes) {
    if (hWnd != hwnd)
        return false;

    returnRes = false;
    return ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
}
