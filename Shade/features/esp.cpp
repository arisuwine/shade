#include "esp.hpp"

#include <cmath>

#include "../hooks/entity_system.hpp"

#include "../menu/options.hpp"
#include "../render/render.hpp"

#include "../sdk/entities/C_CSPlayerPawn.hpp"
#include "../sdk/entities/C_CSPlayerController.hpp"
#include "../sdk/entities/C_CSWeaponBase.hpp"
#include "../sdk/entities/CEntityClass.hpp"

#include "../sdk/services/CCSWeaponBaseVData.hpp"
#include "../sdk/services/CGameSceneNode.hpp"

#include "../math/world_to_screen.hpp"

#include "../utils/debug.hpp"

void ESP::initialize() {
	if (g_options.esp_bounding_boxes)
		render_box();

	if (g_options.esp_player_health)
		render_health();

	if (g_options.esp_player_names)
		render_name();

	if (g_options.esp_player_skeleton)
		render_skeleton();

	if (g_options.esp_player_weapon)
		render_weapon();

	if (g_options.esp_weapon_ammo)
		render_ammo();

	auto p = &g_CViewRender->m_CurrentView;

	//g_CViewRender->m_CurrentView.m_flFov = 115.634f;
	//g_CViewRender->m_CurrentView.m_flFovViewModel = 94.390f;

	//g_CViewRender->m_CurrentView.m_flAspectRatio = 1.778f;
	//g_CViewRender->m_CurrentView.m_flFovViewModel = 80.0f;
	//g_CViewRender->m_CurrentView.m_nSomeFlags |= 0x2;


	//LOG("Ptr: %p, m_flFov: %p, addr: %p\n", g_CViewRender, p, &g_CViewRender->m_CurrentView.m_flFov);
}

void ESP::begin_render() {
	LocalPlayer::get().update();
	C_CSPlayerPawn* local_player = LocalPlayer::get().get_pawn();
	if (!local_player || local_player == nullptr)
		return;

	auto map = g_CGameEntitySystem->m_ClassesByName;
	auto all_entities = map["C_CSPlayerPawn"]->all_entities<C_CSPlayerPawn>();

	for (auto identity = all_entities.begin(); identity != all_entities.end(); identity++) {
		player = *identity;

		if (player == local_player)
			continue;

		if (!bbox.initialize(player))
			continue;

		if (g_options.esp_enemies_only && (local_player->m_iTeamNum == player->m_iTeamNum))
			continue;

		initialize();
	}

	render_dropped_weapon();
}

void ESP::render_name() {
	if (!bbox.initialize(player))
		return;

	if (player->m_iHealth <= 0)
		return;

	if (!bbox.transform_coordinates())
		return;

	C_CSPlayerController* controller = player->m_hController.GetEntityFromHandle();
	if (!controller || controller == nullptr)
		return;

	const char* name = controller->m_sSanitizedPlayerName;

	im_vec_2 text_size = gui.get_text_size(fonts.get("MuseoSans-500-12"), name);
	vector_2d top_middle = bbox.get_points()[bounding_box::TOP_MIDDLE];

	gui.draw_text(im_vec_2(top_middle.x - text_size.x * 0.5f, top_middle.y - text_size.y), ImColor(255, 255, 255, 255), fonts.get("MuseoSans-500-12"), true, name);
}

void ESP::render_box() {
	if (player->m_iHealth <= 0)
		return;

	if (!bbox.transform_coordinates())
		return;

	std::array<vector_2d, 4> points = bbox.get_points();
	float width = points[bounding_box::BOTTOM_RIGHT].x - points[bounding_box::TOP_LEFT].x;
	float height = points[bounding_box::BOTTOM_MIDDLE].y - points[bounding_box::TOP_MIDDLE].y;

	auto color = (*g_options.col_esp_bounding_boxes).get_color();
	auto outline = ImColor(0, 0, 0, 255);

	gui.draw_line(points[bounding_box::TOP_LEFT], im_vec_2(points[bounding_box::TOP_LEFT].x, points[bounding_box::TOP_LEFT].y + height), outline, 3.0f);
	gui.draw_line(im_vec_2(points[bounding_box::TOP_LEFT].x, points[bounding_box::TOP_LEFT].y + height), im_vec_2(points[bounding_box::TOP_LEFT].x + width, points[bounding_box::TOP_LEFT].y + height), outline, 3.0f);
	gui.draw_line(im_vec_2(points[bounding_box::TOP_LEFT].x + width, points[bounding_box::TOP_LEFT].y + height), im_vec_2(points[bounding_box::TOP_LEFT].x + width, points[bounding_box::TOP_LEFT].y), outline, 3.0f);
	gui.draw_line(im_vec_2(points[bounding_box::TOP_LEFT].x + width, points[bounding_box::TOP_LEFT].y), points[bounding_box::TOP_LEFT], outline, 3.0f);

	gui.draw_line(points[bounding_box::TOP_LEFT], im_vec_2(points[bounding_box::TOP_LEFT].x, points[bounding_box::TOP_LEFT].y + height), color, 0.8f);
	gui.draw_line(im_vec_2(points[bounding_box::TOP_LEFT].x, points[bounding_box::TOP_LEFT].y + height), im_vec_2(points[bounding_box::TOP_LEFT].x + width, points[bounding_box::TOP_LEFT].y + height), color, 0.8f);
	gui.draw_line(im_vec_2(points[bounding_box::TOP_LEFT].x + width, points[bounding_box::TOP_LEFT].y + height), im_vec_2(points[bounding_box::TOP_LEFT].x + width, points[bounding_box::TOP_LEFT].y), color, 0.8f);
	gui.draw_line(im_vec_2(points[bounding_box::TOP_LEFT].x + width, points[bounding_box::TOP_LEFT].y), points[bounding_box::TOP_LEFT], color, 0.8f);
}

void ESP::render_health() {
	if (!bbox.initialize(player))
		return;

	if (player->m_iHealth <= 0)
		return;

	if (!bbox.transform_coordinates())
		return;

	std::array<vector_2d, 4> points = bbox.get_points();
	float height = points[bounding_box::BOTTOM_MIDDLE].y - points[bounding_box::TOP_MIDDLE].y;

	float width = 4.0f, health_width = 1.0f;
	vector_2d top_left = vector_2d(points[bounding_box::TOP_LEFT].x - 3.0f - width, points[bounding_box::TOP_MIDDLE].y);

	gui.draw_rect(top_left, im_vec_2(top_left.x + width, top_left.y + height), ImColor(34, 34, 34, 255));

	ImColor health_color = { 1.0f - (float)player->m_iHealth / 100.0f, (float)player->m_iHealth / 100.0f, 0.0f, 1.0f };
	gui.draw_rect(im_vec_2(top_left.x + 1.0f, top_left.y + (height * (1.0f - (float)player->m_iHealth / 100.0f)) + 1.0f), im_vec_2(top_left.x + 2.0f + health_width, top_left.y + height - 1.0f), health_color);
	//if (player->m_iHealth() < 93.0f)
		//gui.draw_text(im_vec_2(top_left.x + 1.0f, top_left.y + (height * (1.0f - (float)player->m_iHealth() / 100.0f)) + 1.0f), ImColor(255, 255, 255, 255), fonts.get("MuseoSans-500_12"), std::to_string(player->m_iHealth()));
}

void ESP::render_skeleton() {
	if (player->m_iHealth <= 0)
		return;

	vector_3d bone_position_start = { }, bone_position_end = { };
	vector_2d line_start = { }, line_end = { };
	
	ImColor color = (*g_options.col_esp_player_skeleton).get_color();

	for (const auto& group : bones)
		for (size_t i = 0; i < group.size() - 1; i++) {
			if ((bone_position_start = CBone::get_bone_position(player, group[i])).is_zero())
				return;

			if ((bone_position_end = CBone::get_bone_position(player, group[i + 1])).is_zero())
				return;

			if (math::world_to_screen(bone_position_start, line_start) && math::world_to_screen(bone_position_end, line_end)) {
				gui.draw_line(im_vec_2(line_start.x, line_start.y), im_vec_2(line_end.x, line_end.y), color, 0.8f);
				continue;
			}

			return;
		}
}

void ESP::render_flags() {
	if (!bbox.initialize(player))
		return;

	if (player->m_iHealth <= 0)
		return;

	if (!bbox.transform_coordinates())
		return;

	std::vector<int> flags;

	auto is_ready = [](const auto& schema) -> bool {
		if (!schema)
			return false;

		return true;
	};
}

void ESP::render_weapon() {
	if (!bbox.initialize(player))
		return;

	if (player->m_iHealth <= 0)
		return;

	if (!bbox.transform_coordinates())
		return;

	C_CSWeaponBase* clipping_weapon = player->m_pClippingWeapon;
	if (!clipping_weapon)
		return;

	CCSWeaponBaseVData* weapon_data = clipping_weapon->m_pWeaponVData;
	if (!weapon_data)
		return;

	const char* name = weapon_data->m_szName + 7;
	
	im_vec_2 text_size = gui.get_text_size(fonts.get("MuseoSans-500-12"), name);
	vector_2d bottom_middle = bbox.get_points()[bounding_box::BOTTOM_MIDDLE];

	gui.draw_text(im_vec_2(bottom_middle.x - text_size.x * 0.5f, bottom_middle.y + text_size.y / 2.0f), ImColor(255, 255, 255, 255), fonts.get("MuseoSans-500-12"), true, name);
}

void ESP::render_ammo() {
	if (!bbox.initialize(player))
		return;

	if (player->m_iHealth <= 0)
		return;

	if (!bbox.transform_coordinates())
		return;

	C_CSWeaponBase* clipping_weapon = player->m_pClippingWeapon;
	if (!clipping_weapon)
		return;

	CCSWeaponBaseVData* weapon_data = clipping_weapon->m_pWeaponVData;
	if (!weapon_data)
		return;

	int ammo = std::max(0, clipping_weapon->m_iClip1);
	int max_ammo = std::max(1, weapon_data->m_iMaxClip1);
	float ammo_multiplier = (float)ammo / (float)max_ammo;

	std::array<vector_2d, 4> points = bbox.get_points();
	float height = 4.0f, ammo_height = 1.0f, width = points[bounding_box::BOTTOM_RIGHT].x - points[bounding_box::TOP_LEFT].x;

	vector_2d bottom_left = vector_2d(points[bounding_box::BOTTOM_RIGHT].x - width, points[bounding_box::BOTTOM_RIGHT].y + 3.0f);

	auto color = (*g_options.col_esp_weapon_ammo).get_color();

	gui.draw_rect(bottom_left, im_vec_2(bottom_left.x + width, bottom_left.y + height), ImColor(34, 34, 34, 255));
	gui.draw_rect(im_vec_2(bottom_left.x + 1.0f, bottom_left.y + 1.0f), im_vec_2(bottom_left.x - 1.0f + width * ammo_multiplier, bottom_left.y + height - 1.0f), color);
}

void ESP::render_dropped_weapon() {
	if (g_WeaponsCache.empty())
		return;

	for (auto& weapon : g_WeaponsCache) {
		if (weapon->m_hOwnerEntity.m_Index != -1)
			continue;

		CGameSceneNode* scene_node = weapon->m_pGameSceneNode;
		if (scene_node == nullptr)
			continue;

		vector_3d origin = scene_node->m_vecAbsOrigin;
		if (origin.is_zero())
			continue;

		CCSWeaponBaseVData* weapon_data = weapon->m_pWeaponVData;
		if (weapon_data == nullptr)
			continue;

		vector_2d screen_pos;
		if (!math::world_to_screen(origin, screen_pos))
			continue;

		const char* name = weapon->m_pWeaponVData->m_szName + 7;
		if (name == nullptr)
			continue;

		gui.draw_text(screen_pos, ImColor(255, 255, 255, 255), fonts.get("MuseoSans-500-12"), true, name);
	}
}