#pragma once
#include "../render.hpp"
#include "../../sdk/entities/PlayerPawn.hpp"
#include "../../sdk/interfaces/CBone.hpp"

extern render::gui::draw_object draw;
extern render::gui::font_map	fonts;

class visuals {
private:
	static PlayerPawn* p_local_player;
	PlayerPawn pawn;

	static inline render::gui::draw_object& ref_to_draw = draw;
	static inline render::gui::font_map& ref_to_fonts = fonts;

	static inline std::vector<std::vector<bone_index>> bones = {
		{ Pelvis, Spine_1, Spine_2, Spine_3, Neck_0, Head },
		{ Neck_0, Arm_Upper_L, Arm_Lower_L, Hand_L },
		{ Neck_0, Arm_Upper_R, Arm_Lower_R, Hand_R },
		{ Pelvis, Leg_Upper_R, Leg_Lower_R, Ankle_R },
		{ Pelvis, Leg_Upper_L, Leg_Lower_L, Ankle_L }
	};

public:
	visuals(const PlayerPawn& _pawn);

	void render_line() const;
	void render_name() const;
	void render_box() const;
	void render_health() const;
	void render_skeleton() const;
};