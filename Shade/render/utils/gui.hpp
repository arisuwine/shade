#pragma once
#include <unordered_map>
#include <string_view>

#include "imgui.h"
#include "im_vec_2.hpp"

using namespace render::types;

class FontMap {
private:
    static ImGuiIO* io;
    static std::unordered_map<std::string_view, ImFont*> map;

public:
    FontMap() {}
    FontMap(const std::string_view& name, const std::string_view& path, const float& size = 0.0f);

    static void set_io();

    static ImFont* push(const std::string_view& name, const std::string_view& path, const float& size = 0.0f);
    static void     pop(const std::string_view& name);
    static ImFont* replace(const std::string_view& name, const std::string_view& path, const float& size = 0.0f);
    static ImFont* get(const std::string_view& name);
};

struct GUI {
    static ImDrawList* draw_list;
    enum text_alignment : int {
        left = 0,
        center,
        right
    };

    static im_vec_2 get_text_size(ImFont* font, const std::string_view& text);

    static void     draw_text(const im_vec_2& pos, const ImColor& col, ImFont* font, const std::string_view& text);
    static void     draw_circle(const im_vec_2& pos, float radius, const ImColor& col, bool filled = true, int num_segments = 0, float thickness = 1.0f);
    static void     draw_rect(const im_vec_2& pos_start, const im_vec_2& pos_end, const ImColor& col, float rounding = 0.0f, bool filled = true, float thickness = 1.0f, ImDrawFlags flags = 0);
    static void     draw_line(const im_vec_2& pos_start, const im_vec_2& pos_end, const ImColor& col, float thickness = 1.0f);
};
