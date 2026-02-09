#include "esp.hpp"

#include <cmath>

#include "../hooks/entity_system.hpp"

#include "../menu/options.hpp"

#include "../render/utils/gui.hpp"

#include "../sdk/entities/C_CSPlayerPawn.hpp"
#include "../sdk/entities/CCSPlayerController.hpp"
#include "../sdk/entities/C_CSWeaponBase.hpp"
#include "../sdk/entities/CEntityClass.hpp"

#include "../sdk/services/CCSWeaponBaseVData.hpp"
#include "../sdk/services/CGameSceneNode.hpp"
#include "../sdk/services/CPlayer_WeaponServices.hpp"

#include "../sdk/utils/item_name.hpp"

#include "../math/world_to_screen.hpp"

#include "../utils/debug.hpp"

void ESP::Initialize() {
	if (g_Options->esp_player_skeleton)
		RenderSkeleton();

	if (!m_bbox.TransformCoordinates())
		return;

	if (g_Options->esp_bounding_boxes)
		RenderBoundingBox();

	if (g_Options->esp_player_health)
		RenderHealth();

	if (g_Options->esp_player_names)
		RenderName();

	if (g_Options->esp_player_weapon)
		RenderWeapon();

	if (g_Options->esp_weapon_ammo)
		RenderAmmo();
}

void ESP::BeginRender() {
	LocalPlayer::Get().Update();
	if (!LocalPlayer::Get().IsValid())
		return;

	for (auto controller : g_CGameEntitySystem->GetAll<CCSPlayerController>()) {
		if (!controller)
			break;

		m_pController = controller;
		m_pPawn = m_pController->m_hPawn.GetEntityFromHandle();

		if (!m_pPawn || m_pPawn == LocalPlayer::Get().GetPawn())
			continue;

		if (g_Options->esp_enemies_only && (LocalPlayer::Get().GetPawn()->m_iTeamNum == m_pPawn->m_iTeamNum))
			continue;

		if (!m_pPawn->IsAlive())
			continue;

		if (!m_bbox.Initialize(m_pPawn))
			continue;

		Initialize();
	}

	RenderDroppedWeapons();
}

void ESP::RenderName() {
	Vector2D pos = m_bbox.GetPoints()[BoundingBox::TOP_MIDDLE];
	Render::RenderText(ImVec2(pos.x, pos.y - 15.0f), Color(255, 255, 255, 255), Fonts::Find("MuseoSans-500-12"), Render::Center, true, m_pController->m_sSanitizedPlayerName);
} 

void ESP::RenderBoundingBox() {
	auto& points	= m_bbox.GetPoints();

	ImVec2 start	= ImVec2(points[BoundingBox::TOP_LEFT].x,		points[BoundingBox::TOP_LEFT].y);
	ImVec2 end		= ImVec2(points[BoundingBox::BOTTOM_RIGHT].x,	points[BoundingBox::BOTTOM_RIGHT].y);

	Color& color	= *g_Options->col_esp_bounding_boxes;

	Render::RenderBox(start, end, color, true);
}

void ESP::RenderHealth() {
	auto& points		= m_bbox.GetPoints();

	float height		= points[BoundingBox::BOTTOM_MIDDLE].y - points[BoundingBox::TOP_MIDDLE].y;
	float width			= 2.0f;
	float distance		= 3.0f;
	float health_offset = height * (1.0f - (float)m_pPawn->m_iHealth / 100.0f);

	ImVec2 start		= { points[BoundingBox::TOP_LEFT].x - width - distance, points[BoundingBox::TOP_MIDDLE].y };
	ImVec2 end			= { start.x + width,									points[BoundingBox::TOP_MIDDLE].y + height };
	
	Color health_color	= { 1.0f - (float)m_pPawn->m_iHealth / 100.0f, (float)m_pPawn->m_iHealth / 100.0f, 0.0f, 1.0f };

	Render::RenderFilledBox(start, end, {0, 0, 0, 255}, true);
	Render::RenderFilledBox(ImVec2(start.x, start.y + health_offset), end, health_color, false);

	if (m_pPawn->m_iHealth < 93)
		Render::RenderText(ImVec2(start.x, start.y + health_offset - 5.0f), Color(255, 255, 255, 255), Fonts::Find("MuseoSans-500-12"), Render::Center, true, std::to_string(m_pPawn->m_iHealth));
}

void ESP::RenderSkeleton() {
	static std::vector<std::vector<BoneIndex>> bones = {
		{ Pelvis, Spine_1, Spine_2, Spine_3, Neck_0, Head },
		{ Neck_0, Arm_Upper_L, Arm_Lower_L, Hand_L },
		{ Neck_0, Arm_Upper_R, Arm_Lower_R, Hand_R },
		{ Pelvis, Leg_Upper_R, Leg_Lower_R, Ankle_R },
		{ Pelvis, Leg_Upper_L, Leg_Lower_L, Ankle_L }
	};

	Vector3D bone_start;
	Vector3D bone_end;

	Vector2D line_start;
	Vector2D line_end;
	
	Color& color = *g_Options->col_esp_player_skeleton;

	for (const auto& group : bones) {
		for (size_t i = 0; i < group.size() - 1; i++) {
			if ((bone_start = CBone::GetBonePosition(m_pPawn, group[i])).IsZero())
				return;

			if ((bone_end = CBone::GetBonePosition(m_pPawn, group[i + 1])).IsZero())
				return;

			if (math::WorldToScreen(bone_start, line_start) && math::WorldToScreen(bone_end, line_end)) {
				Render::RenderLine(ImVec2(line_start.x, line_start.y), ImVec2(line_end.x, line_end.y), color, 0.8f);
				continue;
			}

			return;
		}
	}
}

void ESP::RenderFlags() {
	std::vector<int> flags;

	auto is_ready = [](const auto& schema) -> bool {
		if (!schema)
			return false;

		return true;
	};
}

void ESP::RenderWeapon() {
	CPlayer_WeaponServices* weapon_service = m_pPawn->m_pWeaponServices;
	if (!weapon_service)
		return;

	C_CSWeaponBase* active_weapon = weapon_service->m_hActiveWeapon.GetEntityFromHandle();
	if (!active_weapon)
		return;

	CCSWeaponBaseVData* weapon_data = weapon_service->m_hActiveWeapon.GetEntityFromHandle()->m_pWeaponVData;
	if (!weapon_data)
		return;

	std::string_view weapon_name	= !weapon_data->m_szName ? "" : GetItemName(weapon_data->m_szName);
	ImVec2 pos						= { m_bbox.GetPoints()[BoundingBox::BOTTOM_MIDDLE].x, m_bbox.GetPoints()[BoundingBox::BOTTOM_MIDDLE].y + 5.0f };

	Render::RenderText(ImVec2(pos.x, pos.y), { 255, 255, 255, 255 }, Fonts::Find("MuseoSans-500-12"), Render::Center, true, weapon_name);
}

void ESP::RenderAmmo() {
	CPlayer_WeaponServices* weapon_service = m_pPawn->m_pWeaponServices;
	if (!weapon_service)
		return;

	C_CSWeaponBase* active_weapon = weapon_service->m_hActiveWeapon.GetEntityFromHandle();
	if (!active_weapon)
		return;

	CCSWeaponBaseVData* weapon_data = weapon_service->m_hActiveWeapon.GetEntityFromHandle()->m_pWeaponVData;
	if (!weapon_data)
		return;

	auto& points			= m_bbox.GetPoints();

	int ammo				= std::max(0, active_weapon->m_iClip1);
	int max_ammo			= std::max(1, weapon_data->m_iMaxClip1);

	float height			= 2.0f;
	float distance			= 3.0f;
	float width				= points[BoundingBox::BOTTOM_RIGHT].x - points[BoundingBox::TOP_LEFT].x;
	float ammo_offset		= width * (float)ammo / max_ammo;

	Color& color			= *g_Options->col_esp_weapon_ammo;

	ImVec2 start			= { points[BoundingBox::BOTTOM_RIGHT].x - width, points[BoundingBox::BOTTOM_RIGHT].y + distance };
	ImVec2 end				= { start.x + width, start.y + height };

	Render::RenderFilledBox(start, end, { 0, 0, 0, 255 }, true);
	Render::RenderFilledBox(start, ImVec2(start.x + ammo_offset, end.y), color, false);
}

void ESP::RenderDroppedWeapons() {
	if (g_WeaponsCache.empty())
		return;

	for (auto weapon : g_WeaponsCache) {
		if (weapon->m_hOwnerEntity.m_Index != -1)
			continue;

		CGameSceneNode* scene_node = weapon->m_pGameSceneNode;
		if (!scene_node)
			continue;

		Vector3D origin = scene_node->m_vecAbsOrigin;
		if (origin.IsZero())
			continue;

		CCSWeaponBaseVData* weapon_data = weapon->m_pWeaponVData;
		if (!weapon_data)
			continue;

		Vector2D screen_pos;
		if (!math::WorldToScreen(origin, screen_pos))
			continue;

		std::string_view weapon_name = !weapon_data->m_szName ? "" : GetItemName(weapon_data->m_szName);

		Render::RenderText(ImVec2(screen_pos.x, screen_pos.y), {255, 255, 255, 255}, Fonts::Find("MuseoSans-500-12"), Render::Center, true, weapon_name);
	}
}