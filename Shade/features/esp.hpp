#pragma once
#include <cmath>
#include <array>
#include <memory>

#include "../render/render.hpp"
#include "../sdk/entities/CCSPlayerPawn.hpp"
#include "../sdk/interfaces/CBone.hpp"

#include "utils/bounding_box.hpp"

#include "../menu/options.hpp"

extern render::gui::draw_object draw;
extern render::gui::font_map	fonts;

class esp {
private:
	const CCSPlayerPawn* player;
	bounding_box bbox;

	static inline render::gui::draw_object& ref_to_draw = draw;
	static inline render::gui::font_map& ref_to_fonts = fonts;

	static inline std::vector<std::vector<bone_index>> bones = {
		{ Pelvis, Spine_1, Spine_2, Spine_3, Neck_0, Head },
		{ Neck_0, Arm_Upper_L, Arm_Lower_L, Hand_L },
		{ Neck_0, Arm_Upper_R, Arm_Lower_R, Hand_R },
		{ Pelvis, Leg_Upper_R, Leg_Lower_R, Ankle_R },
		{ Pelvis, Leg_Upper_L, Leg_Lower_L, Ankle_L }
	};

	void render_name();
	void render_box();
	void render_health();
	void render_skeleton();

public:
	esp(const CCSPlayerPawn* _pawn);
	void initialize();
};