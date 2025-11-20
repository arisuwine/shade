#pragma once
#include "../offsets.hpp"

class CModelState;

class CGameSceneNode {
public:
	inline CModelState* m_modelState() const {
		return reinterpret_cast<CModelState*>(reinterpret_cast<uintptr_t>(this) + offsets::CGameSceneNode::m_modelState);
	}
};