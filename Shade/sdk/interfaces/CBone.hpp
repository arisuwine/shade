#pragma once
#include <Windows.h>
#include "../math/vector/vector_3d.hpp"
#include "../offsets.hpp"

enum bone_index : DWORD {
    Pelvis = 0,
    Spine_1 = 2,
    Spine_2 = 3,
    Spine_3 = 4,
    Neck_0 = 5,
    Head = 6,

    Arm_Upper_L = 8,
    Arm_Lower_L = 9,
    Hand_L = 10,

    Arm_Upper_R = 13,
    Arm_Lower_R = 14,
    Hand_R = 15,

    Leg_Upper_L = 22,
    Leg_Lower_L = 23,
    Ankle_L = 24,

    Leg_Upper_R = 25,
    Leg_Lower_R = 26,
    Ankle_R = 27,
};

class CBone {
private:
    static inline uintptr_t get_scene_node(const uintptr_t& pawn);
    static inline uintptr_t get_model_state(const uintptr_t& scene_node);
    static inline uintptr_t get_bone_array(const uintptr_t& model_state);

public:
    CBone() {}
    CBone(const uintptr_t& pawn);
    static vector_3d get_bone_position(const uintptr_t& pawn, bone_index index);
};