#pragma once
#include "../offsets.hpp"
#include "CModelState.hpp"

class CGameSceneNode {
public:
	PSCHEMA	(CModelState,	offsets::client::CGameSceneNode::m_modelState,		m_modelState);
	SCHEMA	(Vector3D,		offsets::client::CGameSceneNode::m_vecAbsOrigin,	m_vecAbsOrigin);
};