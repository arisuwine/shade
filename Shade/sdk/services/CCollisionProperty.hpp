#pragma once
#include "../sdk/math/vector_3d.hpp"
#include "../sdk/offsets.hpp"

class CCollisionProperty {
public:
	SCHEMA(Vector3D, offsets::client::CCollisionProperty::m_vecMaxs, m_vecMaxs);
	SCHEMA(Vector3D, offsets::client::CCollisionProperty::m_vecMins, m_vecMins);
};