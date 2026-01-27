#pragma once
#include <array>

#include "../sdk/math/vector_2d.hpp"
#include "../sdk/math/vector_3d.hpp"

class C_CSPlayerPawn;

class BoundingBox {
private:
	bool m_bIsInitialized;

	Vector3D m_vMin;
	Vector3D m_vMax;

	std::array<Vector2D, 4> m_Points;

public:
	enum POINT : int {
		TOP_LEFT = 0,
		TOP_MIDDLE = 1,
		BOTTOM_RIGHT = 2,
		BOTTOM_MIDDLE = 3
	};

	BoundingBox() = default;
	BoundingBox(C_CSPlayerPawn* pawn);
	
	bool Initialize(C_CSPlayerPawn* pawn);
	bool TransformCoordinates();
	inline const std::array<Vector2D, 4>& GetPoints() const { return m_Points; }

	inline bool IsInitialized() const { return m_bIsInitialized; }
};