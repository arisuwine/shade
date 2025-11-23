#pragma once
#include "../sdk/math/vector.hpp"
#include "../sdk/offsets.hpp"

class CCollisionProperty {
public:
	CCollisionProperty() = delete;

	inline vector_3d m_vecMaxs() const {
		return *reinterpret_cast<vector_3d*>(THIS_ADDR + offsets::CCollisionProperty::m_vecMaxs);
	}

	inline vector_3d m_vecMins() const {
		return *reinterpret_cast<vector_3d*>(THIS_ADDR + offsets::CCollisionProperty::m_vecMins);
	}
};