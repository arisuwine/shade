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

void ESP::Initalize() {
	if (g_options.esp_bounding_boxes)
		RenderBox();

	if (g_options.esp_player_health)
		RenderHealth();

	if (g_options.esp_player_names)
		RenderName();

	if (g_options.esp_player_skeleton)
		RenderSkeleton();

	if (g_options.esp_player_weapon)
		RenderWeapon();

	if (g_options.esp_weapon_ammo)
		RenderAmmo();
}

void ESP::BeginRender() {
	LocalPlayer::Get().Update();
	C_CSPlayerPawn* local_player = LocalPlayer::Get().GetPawn();
	if (!local_player || local_player == nullptr)
		return;

	auto map = g_CGameEntitySystem->m_ClassesByName;
	auto all_entities = map["C_CSPlayerPawn"]->AllEntities<C_CSPlayerPawn>();

	for (auto identity = all_entities.begin(); identity != all_entities.end(); identity++) {
		player = *identity;

		if (player == local_player)
			continue;

		if (!bbox.Initialize(player))
			continue;

		if (g_options.esp_enemies_only && (local_player->m_iTeamNum == player->m_iTeamNum))
			continue;

		Initalize();
	}

	RenderDropperWeapons();
}

void ESP::RenderName() {
	if (!bbox.Initialize(player)) // Remove this line later
		return;

	if (player->m_iHealth <= 0)
		return;

	if (!bbox.TransformCoordinates())
		return;

	C_CSPlayerController* controller = player->m_hController.GetEntityFromHandle();
	if (!controller || controller == nullptr)
		return;

	std::string_view name = controller->m_sSanitizedPlayerName ? controller->m_sSanitizedPlayerName : "";

	im_vec_2 text_size = gui.get_text_size(fonts.get("MuseoSans-500-12"), name);
	vector_2d top_middle = bbox.GetPoints()[BoundingBox::TOP_MIDDLE];

	gui.draw_text(im_vec_2(top_middle.x - text_size.x * 0.5f, top_middle.y - text_size.y), ImColor(255, 255, 255, 255), fonts.get("MuseoSans-500-12"), true, name);
}

void ESP::RenderBox() {
	if (player->m_iHealth <= 0)
		return;

	if (!bbox.TransformCoordinates())
		return;

	std::array<vector_2d, 4> points = bbox.GetPoints();
	float width = points[BoundingBox::BOTTOM_RIGHT].x - points[BoundingBox::TOP_LEFT].x;
	float height = points[BoundingBox::BOTTOM_MIDDLE].y - points[BoundingBox::TOP_MIDDLE].y;

	auto color = (*g_options.col_esp_bounding_boxes).GetColor();
	auto outline = ImColor(0, 0, 0, 255);

	gui.draw_line(points[BoundingBox::TOP_LEFT], im_vec_2(points[BoundingBox::TOP_LEFT].x, points[BoundingBox::TOP_LEFT].y + height), outline, 3.0f);
	gui.draw_line(im_vec_2(points[BoundingBox::TOP_LEFT].x, points[BoundingBox::TOP_LEFT].y + height), im_vec_2(points[BoundingBox::TOP_LEFT].x + width, points[BoundingBox::TOP_LEFT].y + height), outline, 3.0f);
	gui.draw_line(im_vec_2(points[BoundingBox::TOP_LEFT].x + width, points[BoundingBox::TOP_LEFT].y + height), im_vec_2(points[BoundingBox::TOP_LEFT].x + width, points[BoundingBox::TOP_LEFT].y), outline, 3.0f);
	gui.draw_line(im_vec_2(points[BoundingBox::TOP_LEFT].x + width, points[BoundingBox::TOP_LEFT].y), points[BoundingBox::TOP_LEFT], outline, 3.0f);

	gui.draw_line(points[BoundingBox::TOP_LEFT], im_vec_2(points[BoundingBox::TOP_LEFT].x, points[BoundingBox::TOP_LEFT].y + height), color, 0.8f);
	gui.draw_line(im_vec_2(points[BoundingBox::TOP_LEFT].x, points[BoundingBox::TOP_LEFT].y + height), im_vec_2(points[BoundingBox::TOP_LEFT].x + width, points[BoundingBox::TOP_LEFT].y + height), color, 0.8f);
	gui.draw_line(im_vec_2(points[BoundingBox::TOP_LEFT].x + width, points[BoundingBox::TOP_LEFT].y + height), im_vec_2(points[BoundingBox::TOP_LEFT].x + width, points[BoundingBox::TOP_LEFT].y), color, 0.8f);
	gui.draw_line(im_vec_2(points[BoundingBox::TOP_LEFT].x + width, points[BoundingBox::TOP_LEFT].y), points[BoundingBox::TOP_LEFT], color, 0.8f);
}

void ESP::RenderHealth() {
	if (!bbox.Initialize(player))
		return;

	if (player->m_iHealth <= 0)
		return;

	if (!bbox.TransformCoordinates())
		return;

	std::array<vector_2d, 4> points = bbox.GetPoints();
	float height = points[BoundingBox::BOTTOM_MIDDLE].y - points[BoundingBox::TOP_MIDDLE].y;

	float width = 4.0f, health_width = 1.0f;
	vector_2d top_left = vector_2d(points[BoundingBox::TOP_LEFT].x - 3.0f - width, points[BoundingBox::TOP_MIDDLE].y);

	gui.draw_rect(top_left, im_vec_2(top_left.x + width, top_left.y + height), ImColor(34, 34, 34, 255));

	ImColor health_color = { 1.0f - (float)player->m_iHealth / 100.0f, (float)player->m_iHealth / 100.0f, 0.0f, 1.0f };
	gui.draw_rect(im_vec_2(top_left.x + 1.0f, top_left.y + (height * (1.0f - (float)player->m_iHealth / 100.0f)) + 1.0f), im_vec_2(top_left.x + 2.0f + health_width, top_left.y + height - 1.0f), health_color);
	//if (player->m_iHealth() < 93.0f)
		//gui.draw_text(im_vec_2(top_left.x + 1.0f, top_left.y + (height * (1.0f - (float)player->m_iHealth() / 100.0f)) + 1.0f), ImColor(255, 255, 255, 255), fonts.get("MuseoSans-500_12"), std::to_string(player->m_iHealth()));
}

void ESP::RenderSkeleton() {
	if (player->m_iHealth <= 0)
		return;

	vector_3d bone_position_start = { }, bone_position_end = { };
	vector_2d line_start = { }, line_end = { };
	
	ImColor color = (*g_options.col_esp_player_skeleton).GetColor();

	for (const auto& group : bones)
		for (size_t i = 0; i < group.size() - 1; i++) {
			if ((bone_position_start = CBone::GetBonePosition(player, group[i])).is_zero())
				return;

			if ((bone_position_end = CBone::GetBonePosition(player, group[i + 1])).is_zero())
				return;

			if (math::WorldToScreen(bone_position_start, line_start) && math::WorldToScreen(bone_position_end, line_end)) {
				gui.draw_line(im_vec_2(line_start.x, line_start.y), im_vec_2(line_end.x, line_end.y), color, 0.8f);
				continue;
			}

			return;
		}
}

void ESP::RenderFlags() {
	if (!bbox.Initialize(player))
		return;

	if (player->m_iHealth <= 0)
		return;

	if (!bbox.TransformCoordinates())
		return;

	std::vector<int> flags;

	auto is_ready = [](const auto& schema) -> bool {
		if (!schema)
			return false;

		return true;
	};
}

void ESP::RenderWeapon() {
	if (!bbox.Initialize(player))
		return;

	if (player->m_iHealth <= 0)
		return;

	if (!bbox.TransformCoordinates())
		return;

	C_CSWeaponBase* clipping_weapon = player->m_pClippingWeapon;
	if (!clipping_weapon)
		return;

	CCSWeaponBaseVData* weapon_data = clipping_weapon->m_pWeaponVData;
	if (!weapon_data)
		return;

	std::string_view name = weapon_data->m_szName ? weapon_data->m_szName : "";
	name = name.substr(7, name.size());
	
	im_vec_2 text_size = gui.get_text_size(fonts.get("MuseoSans-500-12"), name);
	vector_2d bottom_middle = bbox.GetPoints()[BoundingBox::BOTTOM_MIDDLE];

	gui.draw_text(im_vec_2(bottom_middle.x - text_size.x * 0.5f, bottom_middle.y + text_size.y / 2.0f), ImColor(255, 255, 255, 255), fonts.get("MuseoSans-500-12"), true, name);
}

void ESP::RenderAmmo() {
	if (!bbox.Initialize(player))
		return;

	if (player->m_iHealth <= 0)
		return;

	if (!bbox.TransformCoordinates())
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

	std::array<vector_2d, 4> points = bbox.GetPoints();
	float height = 4.0f, ammo_height = 1.0f, width = points[BoundingBox::BOTTOM_RIGHT].x - points[BoundingBox::TOP_LEFT].x;

	vector_2d bottom_left = vector_2d(points[BoundingBox::BOTTOM_RIGHT].x - width, points[BoundingBox::BOTTOM_RIGHT].y + 3.0f);

	auto color = (*g_options.col_esp_weapon_ammo).GetColor();

	gui.draw_rect(bottom_left, im_vec_2(bottom_left.x + width, bottom_left.y + height), ImColor(34, 34, 34, 255));
	gui.draw_rect(im_vec_2(bottom_left.x + 1.0f, bottom_left.y + 1.0f), im_vec_2(bottom_left.x - 1.0f + width * ammo_multiplier, bottom_left.y + height - 1.0f), color);
}

void ESP::RenderDropperWeapons() {
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
		if (!math::WorldToScreen(origin, screen_pos))
			continue;

		const char* name = weapon->m_pWeaponVData->m_szName + 7;
		if (name == nullptr)
			continue;

		gui.draw_text(screen_pos, ImColor(255, 255, 255, 255), fonts.get("MuseoSans-500-12"), true, name);
	}
}