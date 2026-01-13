#pragma once
#include "../offsets.hpp"
#include "CModelState.hpp"

class CGameSceneNode {
public:
	CGameSceneNode() = delete;

	PSCHEMA	(CModelState,	offsets::client::CGameSceneNode::m_modelState,		m_modelState);
	SCHEMA	(vector_3d,		offsets::client::CGameSceneNode::m_vecAbsOrigin,	m_vecAbsOrigin);
};