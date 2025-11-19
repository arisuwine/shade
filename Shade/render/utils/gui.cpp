#include "gui.hpp"

using namespace render;

ImGuiIO* gui::font_map::io = nullptr;
std::unordered_map<std::string_view, ImFont*> gui::font_map::map;
void gui::font_map::set_io() {
    io = &(ImGui::GetIO());
}

ImFont* gui::font_map::get(const std::string_view& name) {
    if (map.find(name.data()) == map.end())
        return nullptr;

    return map.at(name.data());
}

gui::font_map::font_map(const std::string_view& name, const std::string_view& path, const float& size) {
    map.insert(std::make_pair(name, io->Fonts->AddFontFromFileTTF(path.data(), size)));
}

ImFont* gui::font_map::push(const std::string_view& name, const std::string_view& path, const float& size) {
    if (map.find(name.data()) != map.end())
        return map.at(name);

    map.insert(std::make_pair(name, io->Fonts->AddFontFromFileTTF(path.data(), size)));
    return map.at(name.data());
}

void gui::font_map::pop(const std::string_view& name) {
    if (map.find(name.data()) == map.end())
        return;

    map.erase(name.data());
}

ImFont* gui::font_map::replace(const std::string_view& name, const std::string_view& path, const float& size) {
    if (map.find(name.data()) == map.end())
        return nullptr;

    return map.at(name.data()) = io->Fonts->AddFontFromFileTTF(path.data(), size);
}

ImDrawList* gui::draw_object::draw_list = nullptr;
void gui::draw_object::draw_text(const im_vec_2& pos, const ImColor& col, ImFont* font, const std::string_view& text) {
    ImGui::PushFont(font, font->LegacySize);
    draw_list->AddText(pos, col, text.data(), text.data() + text.size());
    ImGui::PopFont();
}

im_vec_2 gui::draw_object::get_text_size(ImFont* font, const std::string_view& text) {
    return font->CalcTextSizeA(font->LegacySize, FLT_MAX, 0.0f, text.data(), text.data() + text.size());
}

void gui::draw_object::draw_rect(const im_vec_2& pos_start, const im_vec_2& pos_end, const ImColor& col, float rounding, bool filled, float thickness, ImDrawFlags flags) {
    if (filled == false)
        draw_list->AddRect(pos_start, pos_end, col, rounding, flags, thickness);
    else
        draw_list->AddRectFilled(pos_start, pos_end, col, rounding, flags);
}

void gui::draw_object::draw_circle(const im_vec_2& pos, float radius, const ImColor& col, bool filled, int num_segments, float thickness) {
    if (filled = false)
        draw_list->AddCircle(pos, radius, col, num_segments, thickness);
    else
        draw_list->AddCircleFilled(pos, radius, col, num_segments);
}

void gui::draw_object::draw_tab(const im_vec_2& pos, const im_vec_2& size, const ImColor& tab_col, const ImColor& text_col, const std::string_view& text, ImFont* font, text_alignment alignment, float rounding, bool filled, float thickness, ImDrawFlags flags) {
    float padding = 0;
    switch (alignment) {
    case left:
        padding = 10.0f;
        break;
    case center:
        padding = size.x * 0.5f - get_text_size(font, text).x * 0.5f;
        break;
    case right:
        padding = size.x - get_text_size(font, text).x - 10.0f;
        break;
    default:
        break;
    }

    draw_rect(pos, pos + size, tab_col, rounding, filled, thickness, flags);
    draw_text(pos + im_vec_2(padding, size.y * 0.5f - get_text_size(font, text).y * 0.5f), text_col, font, text.data());
}

void gui::draw_object::draw_line(const im_vec_2& pos_start, const im_vec_2& pos_end, const ImColor& col, float thickness) {
    draw_list->AddLine(pos_start, pos_end, col, thickness);
}

gui::draw_object* gui::draw_element::draw = nullptr;
void gui::draw_element::draw_slider(const std::string_view& name, const im_vec_2& pos, const state_colors& colors, ImFont* font) {
    im_vec_2 track_size(173.0f, 3.0f);

    draw->draw_text(pos, colors.get("text_active"), font, name);

    im_vec_2 text_size = draw->get_text_size(font, name);
    im_vec_2 corrected(pos.x, pos.y + text_size.y + 15.0f);

    draw->draw_rect(corrected, corrected + track_size, colors.get("track"), 5.0f);
    draw->draw_circle(im_vec_2(corrected.x + 7.0f, corrected.y + 2.0f), 5.0f, colors.get("thumb_inactive"));
}

void gui::draw_element::draw_switcher(const std::string_view& name, const im_vec_2& pos, const state_colors& colors, ImFont* font) {
    im_vec_2 track_size(24.0f, 11.0f);

    draw->draw_text(pos, colors.get("text_active"), font, name);

    im_vec_2 text_size = draw->get_text_size(font, name);
    im_vec_2 corrected(pos.x, pos.y + text_size.y + 15.0f);

    draw->draw_rect(corrected, corrected + track_size, colors.get("track"), 5.0f);
    draw->draw_circle(im_vec_2(corrected.x + 7.0f, corrected.y + 5.0f), 7.0f, colors.get("thumb_inactive"));
}

void gui::draw_element::draw_selector(const std::string_view& name, const im_vec_2& pos, const state_colors& colors, const std::string_view& elements, ImFont* font) {
    draw->draw_tab(pos, im_vec_2(173.0f, 32.0f), colors.get("tab"), colors.get("text_inactive"), name, font, draw->left, 5.0f);
}


void gui::draw_element::set_draw(draw_object* object) {
    draw = object;
}
