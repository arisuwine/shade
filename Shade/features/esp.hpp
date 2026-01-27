#pragma once
#include <vector>
#include <string>
#include <mutex>
#include <unordered_map>

#include "utils/bounding_box.hpp"

#include "../sdk/services/CBone.hpp"

#include "../utils/singleton.hpp"

class C_CSPlayerPawn;
class CCSPlayerController;

class ESP : public Singleton<ESP> {
	friend class Singleton<ESP>;

private:
	CCSPlayerController*	m_pController;
	C_CSPlayerPawn*			m_pPawn;
	BoundingBox	m_bbox;

	static inline std::vector<std::vector<bone_index>> m_Bones = {
		{ Pelvis, Spine_1, Spine_2, Spine_3, Neck_0, Head },
		{ Neck_0, Arm_Upper_L, Arm_Lower_L, Hand_L },
		{ Neck_0, Arm_Upper_R, Arm_Lower_R, Hand_R },
		{ Pelvis, Leg_Upper_R, Leg_Lower_R, Ankle_R },
		{ Pelvis, Leg_Upper_L, Leg_Lower_L, Ankle_L }
	};

	void RenderName();
	void RenderBoundingBox();
	void RenderHealth();
	void RenderSkeleton();
	void RenderFlags();
	void RenderWeapon();
	void RenderAmmo();
	void RenderDroppedWeapons();

	void Initialize();

	ESP() {}

public:
	void BeginRender();
};