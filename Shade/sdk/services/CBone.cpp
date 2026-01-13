#include "CBone.hpp"

#include "../offsets.hpp"

#include "../entities/C_CSPlayerPawn.hpp"

#include "../services/CGameSceneNode.hpp"
#include "../services/CModelState.hpp"

vector_3d CBone::GetBonePosition(C_CSPlayerPawn* player, bone_index index) {
	uintptr_t bone_array = player->m_pGameSceneNode->m_modelState.m_BoneArray;

	if (!bone_array)
		return vector_3d();

	vector_3d position = *reinterpret_cast<vector_3d*>(bone_array + static_cast<unsigned long long>(index) * 32);

	if (position.is_zero())
		return vector_3d();

	return position;
}