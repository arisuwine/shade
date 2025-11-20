#pragma once
#include "../sdk/math/vector.hpp"
#include "../sdk/offsets.hpp"

class CCollisionProperty {
public:
	vector_3d m_vecMins() const;
	vector_3d m_vecMaxs() const;
};