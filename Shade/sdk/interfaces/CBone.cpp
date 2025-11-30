#include "CBone.hpp"

#include "../offsets.hpp"

#include "../interfaces/CGameSceneNode.hpp"
#include "../interfaces/CModelState.hpp"

#include "../entities/CCSPlayerPawn.hpp"

vector_3d CBone::get_bone_position(CCSPlayerPawn* player, bone_index index) {
	uintptr_t bone_array = player->m_pGameSceneNode->m_modelState.BoneArray;

	if (!bone_array)
		return vector_3d();

	vector_3d position = *reinterpret_cast<vector_3d*>(bone_array + static_cast<unsigned long long>(index) * 32);

	if (position.is_zero())
		return vector_3d();

	return position;
}