#include "CBone.hpp"

vector_3d CBone::get_bone_position(const CCSPlayerPawn* pawn, bone_index index) {
	uintptr_t bone_array = pawn->m_pGameSceneNode()->m_modelState()->BoneArray();

	if (!bone_array)
		return vector_3d();

	const vector_3d position = *reinterpret_cast<vector_3d*>(bone_array + static_cast<unsigned long long>(index) * 32);

	if (position.is_zero())
		return vector_3d();

	return position;
}