#include "CCollisionProperty.hpp"

vector_3d CCollisionProperty::m_vecMaxs() const {
	return *reinterpret_cast<vector_3d*>(reinterpret_cast<uintptr_t>(this) + offsets::CCollisionProperty::m_vecMaxs);
}

vector_3d CCollisionProperty::m_vecMins() const {
	return *reinterpret_cast<vector_3d*>(reinterpret_cast<uintptr_t>(this) + offsets::CCollisionProperty::m_vecMins);
}