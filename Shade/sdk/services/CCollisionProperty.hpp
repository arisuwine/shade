#pragma once
#include "../sdk/math/vector.hpp"
#include "../sdk/offsets.hpp"

class CCollisionProperty {
public:
	CCollisionProperty() = delete;

	SCHEMA(vector_3d, offsets::client::CCollisionProperty::m_vecMaxs, m_vecMaxs);
	SCHEMA(vector_3d, offsets::client::CCollisionProperty::m_vecMins, m_vecMins);
};