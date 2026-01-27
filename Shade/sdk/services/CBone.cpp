#include "CBone.hpp"

#include "../offsets.hpp"

#include "../entities/C_CSPlayerPawn.hpp"

#include "../services/CGameSceneNode.hpp"
#include "../services/CModelState.hpp"

Vector3D CBone::GetBonePosition(C_CSPlayerPawn* m_pPawn, bone_index index) {
	uintptr_t bone_array = m_pPawn->m_pGameSceneNode->m_modelState.m_BoneArray;

	if (!bone_array)
		return Vector3D();

	Vector3D position = *reinterpret_cast<Vector3D*>(bone_array + static_cast<unsigned long long>(index) * 32);

	if (position.IsZero())
		return Vector3D();

	return position;
}