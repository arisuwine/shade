#pragma once
#include <unordered_map>
#include <string>

#include "../sdk/utils/color.hpp"

class ImFont;
class ImFontConfig;
class ImDrawList;

class Fonts {
private:
    static inline std::unordered_map<std::string, ImFont*> m_FontMap;

public:
    static ImFont* Add(const std::string& name, const std::string& path, float size, const ImFontConfig* config = nullptr, const ImWchar* ranges = nullptr);
    static ImFont* Find(std::string_view name);
    
    Fonts() = delete;
    ~Fonts() = default;
};

class Render {
private:
    static inline ImDrawList* m_pDrawList;

    static ImVec2 GetTextSize(ImFont* font, std::string_view text);

public:
    enum Alignment : int {
        Left = 0,
        Center,
        Right
    };

    static void SetDrawList         (ImDrawList* draw_list) { m_pDrawList = draw_list; }

    static void RenderText          (const ImVec2& pos,     const Color& col,   ImFont* font,       Alignment align,    bool outline,           std::string_view text);
    static void RenderLine          (const ImVec2& start,   const ImVec2& end,  const Color& col,   float thickness     = 1.0f);
    static void RenderBox           (const ImVec2& start,   const ImVec2& end,  const Color& col,   bool outline,       float thickness = 1.0f, float rounding = 0.0f);
    static void RenderOutlineBox    (const ImVec2& start,   const ImVec2& end,  const Color& col = { 0, 0, 0, 255 },    float thickness = 1.0f, float rounding = 0.0f);
    static void RenderFilledBox     (const ImVec2& start,   const ImVec2& end,  const Color& col,   bool outline,       float thickness = 1.0f, float rounding = 0.0f);

    virtual ~Render() = default;
};