#pragma once
#include "../offsets.hpp"
#include "CModelState.hpp"

class CGameSceneNode {
public:
	CGameSceneNode() = delete;

	PSCHEMA	(CModelState,	offsets::CGameSceneNode::m_modelState,		m_modelState);
	SCHEMA	(vector_3d,		offsets::CGameSceneNode::m_vecAbsOrigin,	m_vecAbsOrigin);
};