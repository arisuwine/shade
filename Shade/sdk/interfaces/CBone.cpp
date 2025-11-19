#include "CBone.hpp"

uintptr_t CBone::get_scene_node(const uintptr_t& pawn) {
	uintptr_t address = pawn + offsets::CCSPlayerPawn::m_pGameSceneNode;
	return *reinterpret_cast<uintptr_t*>(pawn + offsets::CCSPlayerPawn::m_pGameSceneNode);
}

uintptr_t CBone::get_model_state(const uintptr_t& scene_node) {
	return scene_node + offsets::CGameSceneNode::m_modelState;
}

uintptr_t CBone::get_bone_array(const uintptr_t& model_state) {
	return *reinterpret_cast<uintptr_t*>(model_state + offsets::CModelState::BoneArray);
}

vector_3d CBone::get_bone_position(const uintptr_t& pawn, bone_index index) {
	uintptr_t scene_node = get_scene_node(pawn);
	uintptr_t model_state = get_model_state(scene_node);

	uintptr_t bone_array = get_bone_array(model_state);
	if (!bone_array)
		return vector_3d();

	const vector_3d position = *reinterpret_cast<vector_3d*>(bone_array + static_cast<unsigned long long>(index) * 32);

	if (position.is_zero())
		return vector_3d();

	return position;
}