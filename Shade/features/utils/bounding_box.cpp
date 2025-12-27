#include "bounding_box.hpp"

#include <algorithm>

#include "../sdk/entities/C_CSPlayerPawn.hpp"

#include "../sdk/services/CGameSceneNode.hpp"
#include "../sdk/services/CCollisionProperty.hpp"
#include "../sdk/services/CPlayer_MovementServices.hpp"

#include "../math/world_to_screen.hpp"

bool bounding_box::initialize(C_CSPlayerPawn* player) {
	CCollisionProperty* collision = player->m_pCollision;
	if (!collision) {
		initialized = false;
		return 0;
	}

	CGameSceneNode* game_scene_node = player->m_pGameSceneNode;
	if (!game_scene_node) {
		initialized = false;
		return 0;
	}

	vector_3d origin = game_scene_node->m_vecAbsOrigin;
	vector_3d m_vecMaxs = collision->m_vecMaxs;
	m_vecMaxs.z -= player->m_pMovementServices->m_flDuckAmount * 18.0f;

	max = m_vecMaxs + origin;
	min = collision->m_vecMins + origin;
	initialized = true;
	return 1;
}

bounding_box::bounding_box(C_CSPlayerPawn* player) {
	initialize(player);
}

bool bounding_box::transform_coordinates() {
	points[TOP_LEFT].y = points[TOP_LEFT].x = FLT_MAX;
	points[BOTTOM_RIGHT].y = points[BOTTOM_RIGHT].x = -FLT_MAX;

	for (size_t i = 0; i < 8; ++i) {
		vector_3d point(i & 1 ? max.x : this->min.x, i & 2 ? max.y : min.y, i & 4 ? max.z : min.z);

		vector_2d screen_pos;
		if (!math::world_to_screen(point, screen_pos))
			return 0;

		points[TOP_LEFT] = vector_2d(std::min(points[TOP_LEFT].x, screen_pos.x), std::min(points[TOP_LEFT].y, screen_pos.y));
		points[BOTTOM_RIGHT] = vector_2d(std::max(points[BOTTOM_RIGHT].x, screen_pos.x), std::max(points[BOTTOM_RIGHT].y, screen_pos.y));
	}

	points[TOP_MIDDLE] = points[TOP_LEFT] + vector_2d((points[BOTTOM_RIGHT].x - points[TOP_LEFT].x) * 0.5f, 0.0f);
	points[BOTTOM_MIDDLE] = vector_2d(points[TOP_MIDDLE].x, points[TOP_MIDDLE].y + points[BOTTOM_RIGHT].y - points[TOP_LEFT].y);

	return 1;
}