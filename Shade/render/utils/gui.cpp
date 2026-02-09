#include "gui.hpp"

#include <filesystem>

#include "imgui.h"

#include "../utils/debug.hpp"

ImVec2 Render::GetTextSize(ImFont* font, std::string_view text) {
    return font->CalcTextSizeA(font->LegacySize, FLT_MAX, 0.0f, text.data(), text.data() + text.size());
}

ImFont* Fonts::Add(const std::string& name, const std::string& path, float size, const ImFontConfig* config, const ImWchar* ranges) {
    auto iterator = m_FontMap.find(name);
    if (iterator != m_FontMap.end())
        return iterator->second;

    if (!std::filesystem::exists(path)) {
		lg::Error("[FONTS]", "Font not found: % s\n", path);
        return nullptr;
    }

    ImFont* font = ImGui::GetIO().Fonts->AddFontFromFileTTF(path.data(), size, config, ranges);
    if (font)
        m_FontMap[name] = font;
    else {
        lg::Error("[FONTS]", "Error loading font: %s\n", name);
        return nullptr;
    }

    return font;
}

ImFont* Fonts::Find(std::string_view name) {
    auto iterator = m_FontMap.find(std::string(name));
    if (iterator != m_FontMap.end())
        return iterator->second;

    lg::Error("[FONTS]", "Failed to find font: %s, loading default\n", name);

    return ImGui::GetIO().Fonts->Fonts[0];
}

void Render::RenderText(const ImVec2& pos, const Color& col, ImFont* font, Alignment align, bool outline, std::string_view text) {
    ImVec2 text_pos = pos;
    
    if (align == Center)
        text_pos.x -= GetTextSize(font, text).x / 2.0f;
    else if (align == Right)
        text_pos.x -= GetTextSize(font, text).x;

    ImGui::PushFont(font, font->LegacySize);

    if (outline) {
        m_pDrawList->AddText(text_pos + ImVec2( 1.0f,  1.0f), ImColor(0, 0, 0, col.a()), text.data(), text.data() + text.size());
        m_pDrawList->AddText(text_pos + ImVec2(-1.0f, -1.0f), ImColor(0, 0, 0, col.a()), text.data(), text.data() + text.size());
        m_pDrawList->AddText(text_pos + ImVec2( 1.0f, -1.0f), ImColor(0, 0, 0, col.a()), text.data(), text.data() + text.size());
        m_pDrawList->AddText(text_pos + ImVec2(-1.0f,  1.0f), ImColor(0, 0, 0, col.a()), text.data(), text.data() + text.size());
    }

    m_pDrawList->AddText(text_pos, col.GetColor(), text.data(), text.data() + text.size());

    ImGui::PopFont();
}

void Render::RenderLine(const ImVec2& start, const ImVec2& end, const Color& col, float thickness) {
    m_pDrawList->AddLine(start, end, col.GetColor(), thickness);
}

void Render::RenderOutlineBox(const ImVec2& start, const ImVec2& end, const Color& col, float thickness, float rounding) {
    ImVec2 out_start = start - ImVec2(1.0f, 1.0f);
    ImVec2 out_end = end + ImVec2(1.0f, 1.0f);

    ImVec2 in_start = start + ImVec2(1.0f, 1.0f);
    ImVec2 in_end = end - ImVec2(1.0f, 1.0f);

    m_pDrawList->AddRect(out_start, out_end, col.GetColor(), rounding, 0, thickness);
    m_pDrawList->AddRect(in_start, in_end, col.GetColor(), rounding, 0, thickness);
}

void Render::RenderBox(const ImVec2& start, const ImVec2& end, const Color& col, bool outline, float thickness, float rounding) {
    if (outline)
        RenderOutlineBox(start, end, {0, 0, 0, 255}, thickness, rounding);
    
    m_pDrawList->AddRect(start, end, col.GetColor(), rounding, 0, thickness);
}

void Render::RenderFilledBox(const ImVec2& start, const ImVec2& end, const Color& col, bool outline, float thickness, float rounding) {
    if (outline)
        RenderOutlineBox(start, end, { 0, 0, 0, 255 }, thickness, rounding);

    m_pDrawList->AddRectFilled(start, end, col.GetColor(), rounding);
}