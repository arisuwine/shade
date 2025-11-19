#include "colors.hpp"

using namespace render::colors;

state_colors::state_colors(const std::initializer_list<std::pair<std::string_view, ImColor>> init_list) {
    for (const auto& kv : init_list)
        colors[kv.first] = kv.second;
}

void state_colors::add(const std::string_view& name, const ImColor& color) {
    colors.insert(std::make_pair(name, color));
}

void state_colors::remove(const std::string_view& name) {
    if (colors.find(name.data()) == colors.end())
        return;

    colors.erase(name.data());
}

const ImColor& state_colors::get(const std::string_view& name) const {
    if (colors.find(name.data()) == colors.end())
        return ImColor(0.0f, 0.0f, 0.0f, 0.0f);

    return colors.at(name.data());
}
