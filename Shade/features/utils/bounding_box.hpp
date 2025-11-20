#pragma once
#include <array>
#include <algorithm>
#define NOMINMAX

#include "../sdk/math/vector.hpp"
#include "../sdk/entities/CCSPlayerPawn.hpp"
#include "../math/world_to_screen.hpp"

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
	bounding_box(const CCSPlayerPawn* player);
	
	bool initialize(const CCSPlayerPawn* player);
	bool transform_coordinates();
	const std::array<vector_2d, 4>& get_points() const {
		return points;
	}

	explicit operator bool() const {
		return initialized;
	}
};