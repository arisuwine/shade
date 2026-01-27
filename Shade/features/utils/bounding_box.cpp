#include "bounding_box.hpp"

#include <algorithm>

#include "../sdk/entities/C_CSPlayerPawn.hpp"

#include "../sdk/services/CGameSceneNode.hpp"
#include "../sdk/services/CCollisionProperty.hpp"
#include "../sdk/services/CPlayer_MovementServices.hpp"

#include "../math/world_to_screen.hpp"

bool BoundingBox::Initialize(C_CSPlayerPawn* pawn) {
	CCollisionProperty* collision = pawn->m_pCollision;
	if (!collision) {
		m_bIsInitialized = false;
		return FALSE;
	}

	CGameSceneNode* game_scene_node = pawn->m_pGameSceneNode;
	if (!game_scene_node) {
		m_bIsInitialized = false;
		return FALSE;
	}

	Vector3D origin = game_scene_node->m_vecAbsOrigin;
	Vector3D m_vecMaxs = collision->m_vecMaxs;
	m_vecMaxs.z -= pawn->m_pMovementServices->m_flDuckAmount * 18.0f;

	m_vMax = m_vecMaxs + origin;
	m_vMin = collision->m_vecMins + origin;
	m_bIsInitialized = true;
	return TRUE;
}

BoundingBox::BoundingBox(C_CSPlayerPawn* pawn) {
	Initialize(pawn);
}

bool BoundingBox::TransformCoordinates() {
	m_Points[TOP_LEFT].y = m_Points[TOP_LEFT].x = FLT_MAX;
	m_Points[BOTTOM_RIGHT].y = m_Points[BOTTOM_RIGHT].x = -FLT_MAX;

	for (size_t i = 0; i < 8; ++i) {
		Vector3D point(i & 1 ? m_vMax.x : this->m_vMin.x, i & 2 ? m_vMax.y : m_vMin.y, i & 4 ? m_vMax.z : m_vMin.z);

		Vector2D screen_pos;
		if (!math::WorldToScreen(point, screen_pos))
			return 0;

		m_Points[TOP_LEFT] = Vector2D(std::min(m_Points[TOP_LEFT].x, screen_pos.x), std::min(m_Points[TOP_LEFT].y, screen_pos.y));
		m_Points[BOTTOM_RIGHT] = Vector2D(std::max(m_Points[BOTTOM_RIGHT].x, screen_pos.x), std::max(m_Points[BOTTOM_RIGHT].y, screen_pos.y));
	}

	m_Points[TOP_MIDDLE] = m_Points[TOP_LEFT] + Vector2D((m_Points[BOTTOM_RIGHT].x - m_Points[TOP_LEFT].x) * 0.5f, 0.0f);
	m_Points[BOTTOM_MIDDLE] = Vector2D(m_Points[TOP_MIDDLE].x, m_Points[TOP_MIDDLE].y + m_Points[BOTTOM_RIGHT].y - m_Points[TOP_LEFT].y);

	return TRUE;
}