#pragma once
#include "imgui.h"
#include <unordered_map>
#include <string_view>

namespace render {
    namespace colors {
        class state_colors {
        private:
            std::unordered_map<std::string_view, ImColor> colors;

        public:
            state_colors() {}
            state_colors(const std::initializer_list<std::pair<std::string_view, ImColor>> init_list);

            void add(const std::string_view& name, const ImColor& color);
            void remove(const std::string_view& name);
            const ImColor& get(const std::string_view& name) const;
        };
    }
}
