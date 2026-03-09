#pragma once
#include "../sdk/math/Vector2D.hpp"
#include "../sdk/math/Vector3D.hpp"

namespace math {
	bool WorldToScreen(const Vector3D& in, Vector2D& out);
}