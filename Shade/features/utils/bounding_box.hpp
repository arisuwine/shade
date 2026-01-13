#pragma once
#include <array>

#include "../sdk/math/vector.hpp"

class C_CSPlayerPawn;

class BoundingBox {
private:
	bool initialized;

	vector_3d min;
	vector_3d max;

	std::array<vector_2d, 4> points;

public:
	enum POINT : int {
		TOP_LEFT = 0,
		TOP_MIDDLE = 1,
		BOTTOM_RIGHT = 2,
		BOTTOM_MIDDLE = 3
	};

	BoundingBox() = default;
	BoundingBox(C_CSPlayerPawn* player);
	
	bool Initialize(C_CSPlayerPawn* player);
	bool TransformCoordinates();
	inline const std::array<vector_2d, 4>& GetPoints() const {
		return points;
	}

	explicit operator bool() const {
		return initialized;
	}
};