#pragma once
#include <array>

#include "../sdk/math/vector.hpp"
#include "../math/world_to_screen.hpp"

#include "../sdk/entities/CCSPlayerPawn.hpp"

class bounding_box {
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

	bounding_box() = default;
	bounding_box(CCSPlayerPawn* player);
	
	bool initialize(CCSPlayerPawn* player);
	bool transform_coordinates();
	inline const std::array<vector_2d, 4>& get_points() const {
		return points;
	}

	explicit operator bool() const {
		return initialized;
	}
};