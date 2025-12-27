#include "gui.hpp"

using namespace render;

ImGuiIO* FontMap::io = nullptr;
std::unordered_map<std::string_view, ImFont*> FontMap::map;
void FontMap::set_io() {
    io = &(ImGui::GetIO());
}

ImFont* FontMap::get(const std::string_view& name) {
    if (map.find(name.data()) == map.end())
        return nullptr;

    return map.at(name.data());
}

FontMap::FontMap(const std::string_view& name, const std::string_view& path, const float& size) {
    map.insert(std::make_pair(name, io->Fonts->AddFontFromFileTTF(path.data(), size)));
}

ImFont* FontMap::push(const std::string_view& name, const std::string_view& path, const float& size) {
    if (map.find(name.data()) != map.end())
        return map.at(name);

    map.insert(std::make_pair(name, io->Fonts->AddFontFromFileTTF(path.data(), size)));
    return map.at(name.data());
}

void FontMap::pop(const std::string_view& name) {
    if (map.find(name.data()) == map.end())
        return;

    map.erase(name.data());
}

ImFont* FontMap::replace(const std::string_view& name, const std::string_view& path, const float& size) {
    if (map.find(name.data()) == map.end())
        return nullptr;

    return map.at(name.data()) = io->Fonts->AddFontFromFileTTF(path.data(), size);
}

ImDrawList* GUI::draw_list = nullptr;
im_vec_2 GUI::get_text_size(ImFont* font, const std::string_view& text) {
    return font->CalcTextSizeA(font->LegacySize, FLT_MAX, 0.0f, text.data(), text.data() + text.size());
}

void GUI::draw_text(const im_vec_2& pos, const ImColor& col, ImFont* font, bool outline, const std::string_view& text) {
    if (outline) {
        ImGui::PushFont(font, font->LegacySize);
        draw_list->AddText(pos + im_vec_2(1.0f, 1.0f), ImColor(0, 0, 0, 200), text.data(), text.data() + text.size());
        ImGui::PopFont();
    }

    ImGui::PushFont(font, font->LegacySize);
    draw_list->AddText(pos, col, text.data(), text.data() + text.size());
    ImGui::PopFont();
}

void GUI::draw_rect(const im_vec_2& pos_start, const im_vec_2& pos_end, const ImColor& col, float rounding, bool filled, float thickness, ImDrawFlags flags) {
    if (filled == false)
        draw_list->AddRect(pos_start, pos_end, col, rounding, flags, thickness);
    else
        draw_list->AddRectFilled(pos_start, pos_end, col, rounding, flags);
}

void GUI::draw_circle(const im_vec_2& pos, float radius, const ImColor& col, bool filled, int num_segments, float thickness) {
    if (filled = false)
        draw_list->AddCircle(pos, radius, col, num_segments, thickness);
    else
        draw_list->AddCircleFilled(pos, radius, col, num_segments);
}

void GUI::draw_line(const im_vec_2& pos_start, const im_vec_2& pos_end, const ImColor& col, float thickness) {
    draw_list->AddLine(pos_start, pos_end, col, thickness);
}