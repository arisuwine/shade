#pragma once
#include "../sdk/math/Vector3D.hpp"
#include "../sdk/offsets.hpp"

class CCollisionProperty {
public:
	SCHEMA(Vector3D, offsets::client::CCollisionProperty::m_vecMaxs, m_vecMaxs);
	SCHEMA(Vector3D, offsets::client::CCollisionProperty::m_vecMins, m_vecMins);
};