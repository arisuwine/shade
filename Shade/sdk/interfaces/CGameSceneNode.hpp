#pragma once
#include "../offsets.hpp"

class CModelState;

class CGameSceneNode {
public:
	inline CModelState* m_modelState() const {
		return reinterpret_cast<CModelState*>(THIS_ADDR + offsets::CGameSceneNode::m_modelState);
	}

	inline vector_3d m_vecAbsOrigin() const {
		return *reinterpret_cast<vector_3d*>(THIS_ADDR + offsets::CGameSceneNode::m_vecAbsOrigin);
	}
};