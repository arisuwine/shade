#pragma once
#include <unordered_map>
#include <string_view>
#include <string>

#include "imgui.h"
#include "../sdk/utils/color.hpp"

#include "../utils/singleton.hpp"

class Fonts : public Singleton<Fonts> {
    friend class Singleton<Fonts>;

private:
    ImGuiIO* m_io;
    std::unordered_map<std::string, ImFont*> m_FontMap;

    bool m_bIsInit;

public:
    void Initialize() { m_io = &(ImGui::GetIO()); m_bIsInit = true; };
    bool IsInitialized() const { return m_bIsInit; }

    ImFont* Add(const std::string& name, const std::string& path, float size, const ImFontConfig* config = nullptr, const ImWchar* ranges = nullptr);
    ImFont* Find(const std::string_view name);
    
    void    Shutdown()  { m_io = nullptr; }
    virtual ~Fonts()    { Shutdown(); }
};

class Render : public Singleton<Render> {
    friend class Singleton<Render>;

private:
    ImDrawList* m_pDrawList;

    ImVec2 GetTextSize(ImFont* font, const std::string_view& text);

public:
    enum Alignment : int {
        Left = 0,
        Center,
        Right
    };

    void SetDrawList(ImDrawList* draw_list) { m_pDrawList = draw_list; }

    void RenderText         (const ImVec2& pos, const Color& col, ImFont* font, Alignment align, bool outline, const std::string_view& text);
    void RenderLine         (const ImVec2& start, const ImVec2& end, const Color& col, float thickness = 1.0f);
    void RenderBox          (const ImVec2& start, const ImVec2& end, const Color& col, bool outline, float thickness = 1.0f, float rounding = 0.0f);
    void RenderOutlineBox   (const ImVec2& start, const ImVec2& end, const Color& col = { 0, 0, 0, 255 }, float thickness = 1.0f, float rounding = 0.0f);
    void RenderFilledBox    (const ImVec2& start, const ImVec2& end, const Color& col, bool outline, float thickness = 1.0f, float rounding = 0.0f);

    void    Shutdown()      { m_pDrawList = nullptr; }
    virtual ~Render()       { Shutdown(); }
};