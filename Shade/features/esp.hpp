#pragma once
#include <vector>

#include "utils/bounding_box.hpp"

#include "../sdk/interfaces/CBone.hpp"

class ESP {
private:
	CCSPlayerPawn* player;
	bounding_box bbox;

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
	void render_flags();
	void render_weapon();
	void render_ammo();

	void initialize();

	ESP() {};
public:

	static ESP& get() {
		static ESP instance;
		return instance;
	}
	void begin_render();
};