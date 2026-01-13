#pragma once
#include <vector>

#include "utils/bounding_box.hpp"

#include "../sdk/services/CBone.hpp"

class ESP {
private:
	C_CSPlayerPawn* player;
	BoundingBox bbox;

	static inline std::vector<std::vector<bone_index>> bones = {
		{ Pelvis, Spine_1, Spine_2, Spine_3, Neck_0, Head },
		{ Neck_0, Arm_Upper_L, Arm_Lower_L, Hand_L },
		{ Neck_0, Arm_Upper_R, Arm_Lower_R, Hand_R },
		{ Pelvis, Leg_Upper_R, Leg_Lower_R, Ankle_R },
		{ Pelvis, Leg_Upper_L, Leg_Lower_L, Ankle_L }
	};

	void RenderName();
	void RenderBox();
	void RenderHealth();
	void RenderSkeleton();
	void RenderFlags();
	void RenderWeapon();
	void RenderAmmo();

	void Initalize();

	ESP() {}
public:

	static ESP& Get() {
		static ESP instance;
		return instance;
	}
	void BeginRender();
	static void RenderDropperWeapons();
};