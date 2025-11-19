#include "menu.hpp"

draw_element render::element;
im_vec_2 menu_pos(200.0f, 200.0f);

void render::draw_menu() {
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    colors::state_colors common = {
        { "thumb_inactive", ImColor(255, 255, 255, 255) },
        { "thumb_hover",    ImColor(177, 217, 255, 255) },
        { "track",          ImColor(14, 18, 29, 255) },

        { "text_active",    ImColor(255, 255, 255, 255) }
    };
    colors::state_colors dropdown = {
        { "tab",            ImColor(14, 18, 29, 255) },
        { "text_inactive",  ImColor(55, 64, 91, 255) },
        { "text_active",    ImColor(255, 255, 255, 255) }
    };

    draw.draw_rect(menu_pos, menu_pos + ImVec2(800.0f, 500.0f), IM_COL32(9, 12, 20, 255), 10.0f, true);
    draw.draw_text(menu_pos + 30.0f, IM_COL32(255, 255, 255, 255), fonts.get("MuseoSans-900"), "Perfect Hack");

    const std::string_view tabs[4] = {
        "Aimbot",
        "Visuals",
        "Misc",
        "Config"
    };

    types::im_vec_2 tab_size = { 150.0f, 40.0f };
    float padding = 5.0f;
    for (size_t i = 0; i < 4; ++i) {
        draw.draw_tab(menu_pos + types::im_vec_2(30.0f, 81.0f) + types::im_vec_2(0, (float)i * (tab_size.y + 5.0f)), tab_size, IM_COL32(14, 22, 43, 255), IM_COL32(255, 255, 255, 255), tabs[i], fonts.get("MuseoSans-500"), gui::draw_object::left, 5.0f, true);
    }

    draw.draw_rect(menu_pos + types::im_vec_2(202.0f, 81.0f), menu_pos + types::im_vec_2(202.0f, 81.0f) + types::im_vec_2(193.0f, 247.0f), IM_COL32(14, 22, 43, 255), 5.0f);

    auto mouse_in_menu = [](im_vec_2& pos, const im_vec_2& size) {
        ImGuiIO& io = ImGui::GetIO();
        im_vec_2 mouse_pos = io.MousePos;
        im_vec_2 pos_end = pos + size;
        return pos.x < mouse_pos.x && pos.y < mouse_pos.y && pos_end.x > mouse_pos.x && pos_end.y > mouse_pos.y;
        };

    gui::draw_element elements;
    elements.set_draw(&draw);

    draw.draw_text(menu_pos + im_vec_2(212.0f, 91.0f), ImColor(54, 62, 85, 255), fonts.get("MuseoSans-900_10"), "AIMBOT");
    elements.draw_switcher("Enable", menu_pos + im_vec_2(212.0f, 123.0f), common, fonts.get("MuseoSans-500"));
    elements.draw_selector("Select Hitboxes", menu_pos + im_vec_2(212.0f, 178.0f), dropdown, tabs[0], fonts.get("MuseoSans-500_12"));
    elements.draw_slider("FOV", menu_pos + im_vec_2(212.0f, 230.0f), common, fonts.get("MuseoSans-500"));
}