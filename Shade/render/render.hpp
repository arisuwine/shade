#pragma once
#include <d3d11.h>

#include "../hooks/game_overlay.hpp"

#include "utils/colors.hpp"
#include "utils/gui.hpp"
#include "utils/im_vec_2.hpp"

#include "../features/esp.hpp"

#include "../sdk/modules.hpp"
#include "../sdk/offsets.hpp"
#include "../sdk/entities/CCSPlayerPawn.hpp"
#include "../sdk/interfaces/CEntityIdentity.hpp"

#include "../math/world_to_screen.hpp"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"


namespace render {
    extern IDXGISwapChain*          g_SwapChain;
    extern ID3D11Device*            g_Device;
    extern ID3D11DeviceContext*     g_DeviceContext;
    extern ID3D11RenderTargetView*  g_TargetView;

    extern gui::font_map            fonts;
    extern gui::draw_object         draw;
    extern gui::draw_element        element;

	extern HWND                     hwnd;

    void present_scene(IDXGISwapChain* SwapChain, UINT syncInterval, UINT flags);
    LRESULT wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, bool& returnRes);
    
    void setup_fonts();
    void draw_menu();
    void draw_information();
}