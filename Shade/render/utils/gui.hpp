#pragma once
#include <unordered_map>
#include <string_view>

#include "imgui.h"
#include "im_vec_2.hpp"
#include "colors.hpp"

using namespace render::types;
using namespace render::colors;

namespace render {
    namespace gui {
        class font_map {
        private:
            static ImGuiIO* io;
            static std::unordered_map<std::string_view, ImFont*> map;

        public:
            font_map() {}
            font_map(const std::string_view& name, const std::string_view& path, const float& size = 0.0f);

            static void set_io();

            static ImFont*  push    (const std::string_view& name, const std::string_view& path, const float& size = 0.0f);
            static void     pop     (const std::string_view& name);
            static ImFont*  replace (const std::string_view& name, const std::string_view& path, const float& size = 0.0f);
            static ImFont*  get     (const std::string_view& name);
        };

        struct draw_object {
            static ImDrawList* draw_list;
            enum text_alignment : int {
                left = 0,
                center,
                right
            };

            static im_vec_2 get_text_size   (ImFont* font,          const std::string_view& text);

            static void     draw_text       (const im_vec_2& pos,       const ImColor& col,         ImFont* font,           const std::string_view& text);
            static void     draw_circle     (const im_vec_2& pos,       float radius,               const ImColor& col,     bool filled = true,         int num_segments = 0,   float thickness = 1.0f);
            static void     draw_rect       (const im_vec_2& pos_start, const im_vec_2& pos_end,    const ImColor& col,     float rounding = 0.0f,      bool filled = true,     float thickness = 1.0f, ImDrawFlags flags = 0);
            static void     draw_line       (const im_vec_2& pos_start, const im_vec_2& pos_end,    const ImColor& col,     float thickness = 1.0f);
            static void     draw_tab        (const im_vec_2& pos_start, const im_vec_2& pos_end,    const ImColor& tab_col, const ImColor& text_col,    const std::string_view& text, ImFont* font, text_alignment alignment = left, float rounding = 0.0f, bool filled = true, float thickness = 1.0f, ImDrawFlags flags = 0);

        };

        class draw_element {
        private:
            static draw_object* draw;

        public:
            static void     draw_slider     (const std::string_view& name, const im_vec_2& pos, const state_colors& colors, ImFont* font);
            static void     draw_switcher   (const std::string_view& name, const im_vec_2& pos, const state_colors& colors, ImFont* font);
            static void     draw_selector   (const std::string_view& name, const im_vec_2& pos, const state_colors& colors, const std::string_view& elements, ImFont* font);

            static void set_draw(draw_object* object);
        };
    }
}
