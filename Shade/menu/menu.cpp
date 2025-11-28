#include "menu.hpp"
#include "options.hpp"

draw_element render::element;
im_vec_2 menu_pos(200.0f, 200.0f);

//void render::draw_menu() {
//    ImGuiIO& io = ImGui::GetIO(); (void)io;
//
//    colors::state_colors common = {
//        { "thumb_inactive", ImColor(255, 255, 255, 255) },
//        { "thumb_hover",    ImColor(177, 217, 255, 255) },
//        { "track",          ImColor(14, 18, 29, 255) },
//
//        { "text_active",    ImColor(255, 255, 255, 255) }
//    };
//    colors::state_colors dropdown = {
//        { "tab",            ImColor(14, 18, 29, 255) },
//        { "text_inactive",  ImColor(55, 64, 91, 255) },
//        { "text_active",    ImColor(255, 255, 255, 255) }
//    };
//
//    draw.draw_rect(menu_pos, menu_pos + ImVec2(800.0f, 500.0f), IM_COL32(9, 12, 20, 255), 10.0f, true);
//    draw.draw_text(menu_pos + 30.0f, IM_COL32(255, 255, 255, 255), fonts.get("MuseoSans-900"), "Perfect Hack");
//
//    const std::string_view tabs[4] = {
//        "Aimbot",
//        "Visuals",
//        "Misc",
//        "Config"
//    };
//
//    types::im_vec_2 tab_size = { 150.0f, 40.0f };
//    float padding = 5.0f;
//    for (size_t i = 0; i < 4; ++i) {
//        draw.draw_tab(menu_pos + types::im_vec_2(30.0f, 81.0f) + types::im_vec_2(0, (float)i * (tab_size.y + 5.0f)), tab_size, IM_COL32(14, 22, 43, 255), IM_COL32(255, 255, 255, 255), tabs[i], fonts.get("MuseoSans-500"), gui::draw_object::left, 5.0f, true);
//    }
//
//    draw.draw_rect(menu_pos + types::im_vec_2(202.0f, 81.0f), menu_pos + types::im_vec_2(202.0f, 81.0f) + types::im_vec_2(193.0f, 247.0f), IM_COL32(14, 22, 43, 255), 5.0f);
//
//    auto mouse_in_menu = [](im_vec_2& pos, const im_vec_2& size) {
//        ImGuiIO& io = ImGui::GetIO();
//        im_vec_2 mouse_pos = io.MousePos;
//        im_vec_2 pos_end = pos + size;
//        return pos.x < mouse_pos.x && pos.y < mouse_pos.y && pos_end.x > mouse_pos.x && pos_end.y > mouse_pos.y;
//        };
//
//    gui::draw_element elements;
//    elements.set_draw(&draw);
//
//    draw.draw_text(menu_pos + im_vec_2(212.0f, 91.0f), ImColor(54, 62, 85, 255), fonts.get("MuseoSans-900_10"), "AIMBOT");
//    elements.draw_switcher("Enable", menu_pos + im_vec_2(212.0f, 123.0f), common, fonts.get("MuseoSans-500"));
//    elements.draw_selector("Select Hitboxes", menu_pos + im_vec_2(212.0f, 178.0f), dropdown, tabs[0], fonts.get("MuseoSans-500_12"));
//    elements.draw_slider("FOV", menu_pos + im_vec_2(212.0f, 230.0f), common, fonts.get("MuseoSans-500"));
//}

namespace ImGuiEx {
    inline bool ColorEdit4(const char* label, color* v, bool show_alpha = true)
    {
        auto clr = ImVec4{
            v->r / 255.0f,
            v->g / 255.0f,
            v->b / 255.0f,
            v->a / 255.0f
        };

        if (ImGui::ColorEdit4(label, &clr.x, show_alpha)) {
            v->r = clr.x, v->g = clr.y, v->b = clr.z, v->a = clr.w;
            return true;
        }
        return false;
    }
    inline bool ColorEdit3(const char* label, color* v)
    {
        return ColorEdit4(label, v, false);
    }
}

void menu::toggle() {
    *g_options.show_menu = !*g_options.show_menu;
}

float col[] = {255.f, 0.f, 0.f, 255.f};

void menu::setup_styles() {
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowPadding = ImVec2(15, 15);
    style.WindowRounding = 5.0f;
    style.FramePadding = ImVec2(5, 5);
    style.FrameRounding = 4.0f;
    style.ItemSpacing = ImVec2(12, 8);
    style.ItemInnerSpacing = ImVec2(8, 6);
    style.IndentSpacing = 25.0f;
    style.ScrollbarSize = 15.0f;
    style.ScrollbarRounding = 9.0f;
    style.GrabMinSize = 5.0f;
    style.GrabRounding = 3.0f;

    style.Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style.Colors[ImGuiCol_Tab] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style.Colors[ImGuiCol_TabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
}

void menu::draw_menu() {
    ImGui::GetIO().MouseDrawCursor = *g_options.show_menu;

    if (!(*g_options.show_menu))
        return;

    ImGui::Begin("yuki-external", g_options.show_menu);
    if (ImGui::BeginTabBar("##MainTabBar", ImGuiTabBarFlags_None)) {
        if (ImGui::BeginTabItem("Aimbot")) {
            //ImGui::Checkbox("Aimbot", &aimbotEnabled);
            //ImGui::Checkbox("Sticky Aim", &stickyAimEnabled);
            //ImGui::Checkbox("Use FOV", &useFOV);
            //ImGui::Combo("Part", &selectedPartIndex, partOptions, IM_ARRAYSIZE(partOptions));
            //ImGui::SliderFloat("Horizontal", &horizontalValue, 0.0f, 10.0f);
            //ImGui::SliderFloat("Vertical", &verticalValue, 0.0f, 10.0f);
            //ImGui::SliderFloat("Smoothness", &cameraSmoothness, 0.0f, 10.0f);
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Visuals")) {
            ImGui::Checkbox("Enable", g_options.esp_enabled);
            ImGui::Checkbox("Enemies Only", g_options.esp_enemies_only);
            ImGui::Checkbox("Bounding Boxes", g_options.esp_bounding_boxes);
            ImGui::SameLine();
            ImGui::ColorEdit3("Bounding Boxes", &col[3]);

            ImGui::Checkbox("Player Names", g_options.esp_player_names);
            ImGui::SameLine();
            ImGui::ColorEdit3("Player Names", &g_options.col_esp_player_names[3]);

            ImGui::Checkbox("Health", g_options.esp_player_health);

            ImGui::Checkbox("Skeleton", g_options.esp_player_skeleton);
            ImGui::SameLine();
            ImGui::ColorEdit3("Skeleton", &g_options.col_esp_player_skeleton[3]);


            ImGui::EndTabItem();
        }


        if (ImGui::BeginTabItem("Settings")) {

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();
}