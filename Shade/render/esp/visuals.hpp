#pragma once
#include <cmath>
#include <array>

#include "../render.hpp"
#include "../../sdk/interfaces/CGameEntitySystem.hpp"
#include "../../sdk/interfaces/CCollisionProperty.hpp"
#include "../../sdk/interfaces/CPlayer_MovementServices.hpp"
#include "../../sdk/interfaces/CGameSceneNode.hpp"
#include "../../sdk/interfaces/CModelState.hpp"
#include "../../sdk/interfaces/CCSPlayerController.hpp"
#include "../../sdk/entities/CCSPlayerPawn.hpp"
#include "../../sdk/interfaces/CBone.hpp"

extern render::gui::draw_object draw;
extern render::gui::font_map	fonts;

class visuals {
private:
	const CCSPlayerPawn* pawn;

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
	visuals(const CCSPlayerPawn* _pawn);

	void render_name() const;
	void render_box() const;
	void render_health() const;
	void render_skeleton() const;
};