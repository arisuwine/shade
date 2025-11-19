#include "visuals.hpp"

visuals::visuals(const PlayerPawn& _pawn) : pawn(_pawn) {}

void visuals::render_name() const {
	if (pawn.is_local_player())
		return;

	vector_3d head_position = { };
	if ((head_position = CBone::get_bone_position(pawn.get_address(), Head)).is_zero())
		return;

	head_position.z += 15.0f;

	vector_2d text_position = { };
	if (!math::world_to_screen(head_position, text_position))
		return;

	im_vec_2 text_size = ref_to_draw.get_text_size(fonts.get("MuseoSans-500_12"), pawn.data.name.string);
	ref_to_draw.draw_text(im_vec_2(text_position.x - text_size.x * 0.5f, text_position.y - text_size.y), ImColor(255, 255, 255, 255), fonts.get("MuseoSans-500_12"), pawn.data.name.string);
}

void visuals::render_box() const {
	if (pawn.is_local_player())
		return;

	vector_3d head_position = { };
	if ((head_position = CBone::get_bone_position(pawn.get_address(), Head)).is_zero())
		return;

	head_position.y -= 15.0f;
	head_position.z += 10.0f;

	vector_2d box_start = { };
	if (!math::world_to_screen(head_position, box_start))
		return;

	vector_2d box_end = { };
	if (!math::world_to_screen(vector_3d(pawn.data.origin.x, pawn.data.origin.y + 15.0f, pawn.data.origin.z), box_end))
		return;

	//LOG("Box Start: %f, %f; Box End: %f, %f; Head Position: %f, %f, %f; Origin: %f, %f, %f\n", box_start.x, box_start.y, box_end.x, box_end.y, head_position.x, head_position.y, head_position.z, pawn.data.origin.x, pawn.data.origin.y + 15.0f, pawn.data.origin.z);

	ref_to_draw.draw_rect(im_vec_2(box_start.x, box_start.y), im_vec_2(box_end.x, box_end.y), ImColor(255, 255, 255, 255), 0.0f, false, 0.8f);
}

void visuals::render_health() const {
	if (pawn.is_local_player())
		return;

	vector_3d head_position = { };
	if ((head_position = CBone::get_bone_position(pawn.get_address(), Head)).is_zero())
		return;

	head_position.y -= 25.0f;
	head_position.z += 5.0f;
	vector_2d bar_position_start = { };
	if (!math::world_to_screen(head_position, bar_position_start))
		return;

	vector_2d bar_position_end = { };
	if (!math::world_to_screen(vector_3d(pawn.data.origin.x, pawn.data.origin.y - 22.0f, pawn.data.origin.z), bar_position_end))
		return;

	float bar_width = 7.0f, health_bar_width = 3.0f;
	ref_to_draw.draw_rect(im_vec_2(bar_position_start.x, bar_position_start.y), im_vec_2(bar_position_end.x, bar_position_end.y), ImColor(34, 34, 34, 255));
	ImColor health_color = { 1.0f - (float)pawn.data.health / 100.0f, (float)pawn.data.health / 100.0f, 0.0f, 1.0f };
	//ref_to_draw.draw_rect(im_vec_2(bar_position_start.x, bar_position_start.y), im_vec_2(bar_position_end.x, bar_position_end.y), health_color);
}

void visuals::render_skeleton() const {
	if (pawn.is_local_player())
		return;

	vector_3d bone_position_start = { }, bone_position_end = { };
	vector_2d line_start = { }, line_end = { };

	for (const auto& group : bones)
		for (size_t i = 0; i < group.size() - 1; i++) {
			if ((bone_position_start = CBone::get_bone_position(pawn.get_address(), group[i])).is_zero())
				return;

			if ((bone_position_end = CBone::get_bone_position(pawn.get_address(), group[i + 1])).is_zero())
				return;

			if (math::world_to_screen(bone_position_start, line_start) && math::world_to_screen(bone_position_end, line_end)) {
				ref_to_draw.draw_line(im_vec_2(line_start.x, line_start.y), im_vec_2(line_end.x, line_end.y), ImColor(255, 255, 255, 255), 0.8f);
				continue;
			}

			return;
		}
}