#pragma once
#include "../sdk/math/vector_2d.hpp"
#include "../sdk/math/vector_3d.hpp"

namespace math {
	bool WorldToScreen(const Vector3D& in, Vector2D& out);
}