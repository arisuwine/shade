#include "esp.hpp"

esp::esp(const CCSPlayerPawn* _pawn) : player(_pawn), bbox(_pawn) {}

void esp::initialize() {
	if (!g_options.esp_enabled)
		return;

	if (g_options.esp_enemies_only && (LocalPlayer::get().get_pawn()->m_iTeamNum() == player->m_iTeamNum()))
		return;

	if (g_options.esp_bouding_boxes)
		render_box();

	if (g_options.esp_player_health)
		render_health();

	if (g_options.esp_player_names)
		render_name();

	if (g_options.esp_player_skeleton)
		render_skeleton();
}

void esp::render_name() {
	if (!bbox.initialize(player))
		return;

	if (player->m_iHealth() <= 0)
		return;

	if (!bbox.transform_coordinates())
		return;

	const char* name = player->m_sSanitizedPlayerName() ? player->m_sSanitizedPlayerName() : "";

	im_vec_2 text_size = ref_to_draw.get_text_size(fonts.get("MuseoSans-500-12"), name);
	vector_2d top_middle = bbox.get_points()[bounding_box::TOP_MIDDLE];

	ref_to_draw.draw_text(im_vec_2(top_middle.x - text_size.x * 0.5f, top_middle.y - text_size.y), ImColor(255, 255, 255, 255), fonts.get("MuseoSans-500-12"), name);
}

void esp::render_box() {
	if (!bbox.initialize(player))
		return;

	if (player->m_iHealth() <= 0)
		return;

	if (!bbox.transform_coordinates())
		return;

	std::array<vector_2d, 4> points = bbox.get_points();
	float width = points[bounding_box::BOTTOM_RIGHT].x - points[bounding_box::TOP_LEFT].x;
	float height = points[bounding_box::BOTTOM_MIDDLE].y - points[bounding_box::TOP_MIDDLE].y;

	ref_to_draw.draw_line(points[bounding_box::TOP_LEFT], im_vec_2(points[bounding_box::TOP_LEFT].x, points[bounding_box::TOP_LEFT].y + height), ImColor(255, 255, 255, 255), 0.8f);
	ref_to_draw.draw_line(im_vec_2(points[bounding_box::TOP_LEFT].x, points[bounding_box::TOP_LEFT].y + height), im_vec_2(points[bounding_box::TOP_LEFT].x + width, points[bounding_box::TOP_LEFT].y + height), ImColor(255, 255, 255, 255), 0.8f);
	ref_to_draw.draw_line(im_vec_2(points[bounding_box::TOP_LEFT].x + width, points[bounding_box::TOP_LEFT].y + height), im_vec_2(points[bounding_box::TOP_LEFT].x + width, points[bounding_box::TOP_LEFT].y), ImColor(255, 255, 255, 255), 0.8f);
	ref_to_draw.draw_line(im_vec_2(points[bounding_box::TOP_LEFT].x + width, points[bounding_box::TOP_LEFT].y), points[bounding_box::TOP_LEFT], ImColor(255, 255, 255, 255), 0.8f);
}

void esp::render_health() {
	if (!bbox.initialize(player))
		return;

	if (player->m_iHealth() <= 0)
		return;

	if (!bbox.transform_coordinates())
		return;

	std::array<vector_2d, 4> points = bbox.get_points();
	float height = points[bounding_box::BOTTOM_MIDDLE].y - points[bounding_box::TOP_MIDDLE].y;

	float width = 4.0f, health_width = 1.0f;
	vector_2d top_left = vector_2d(points[bounding_box::TOP_LEFT].x - 3.0f - width, points[bounding_box::TOP_MIDDLE].y);

	ref_to_draw.draw_rect(top_left, im_vec_2(top_left.x + width, top_left.y + height), ImColor(34, 34, 34, 255));

	ImColor health_color = { 1.0f - (float)player->m_iHealth() / 100.0f, (float)player->m_iHealth() / 100.0f, 0.0f, 1.0f };
	ref_to_draw.draw_rect(im_vec_2(top_left.x + 1.0f, top_left.y + (height * (1.0f - (float)player->m_iHealth() / 100.0f)) + 1.0f), im_vec_2(top_left.x + 2.0f + health_width, top_left.y + height - 1.0f), health_color);
	//if (player->m_iHealth() < 93.0f)
		//ref_to_draw.draw_text(im_vec_2(top_left.x + 1.0f, top_left.y + (height * (1.0f - (float)player->m_iHealth() / 100.0f)) + 1.0f), ImColor(255, 255, 255, 255), fonts.get("MuseoSans-500_12"), std::to_string(player->m_iHealth()));
}

void esp::render_skeleton() {
	if (player->m_iHealth() <= 0)
		return;

	vector_3d bone_position_start = { }, bone_position_end = { };
	vector_2d line_start = { }, line_end = { };

	for (const auto& group : bones)
		for (size_t i = 0; i < group.size() - 1; i++) {
			if ((bone_position_start = CBone::get_bone_position(player, group[i])).is_zero())
				return;

			if ((bone_position_end = CBone::get_bone_position(player, group[i + 1])).is_zero())
				return;

			if (math::world_to_screen(bone_position_start, line_start) && math::world_to_screen(bone_position_end, line_end)) {
				ref_to_draw.draw_line(im_vec_2(line_start.x, line_start.y), im_vec_2(line_end.x, line_end.y), ImColor(255, 255, 255, 255), 0.8f);
				continue;
			}

			return;
		}
}