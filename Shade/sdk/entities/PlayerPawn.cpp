#include "PlayerPawn.hpp"

uintptr_t PlayerPawn::entity_system = CGameEntitySystem::get_entity_system();
uintptr_t PlayerPawn::local_controller_handle = modules::client.find(LOCAL_PLAYER_CONTROLLER);

uintptr_t __fastcall PlayerPawn::GetPawnByController(const uintptr_t& controller) {
	int v1; // edx
	__int64 v2; // r9
	__int32* v3; // rax

	uintptr_t EntityList = entity_system + 0x10;

	v1 = *(__int32*)(controller + offsets::CCSPlayerController::m_hPawn);
	if (v1 == -1 || !EntityList)
		return 0;
	if (v1 != -2
		&& (v2 = *(__int64*)(EntityList + 8 * ((unsigned __int64)(v1 & 0x7FFF) >> 9))) != 0
		&& (v3 = (__int32*)(v2 + 112LL * (v1 & 0x1FF))) != 0)
	{
		if (v3[4] != v1)
			v3 = 0;
	}
	else
	{
		v3 = 0;
	}
	if (v3)
		return *(__int64*)v3;
	else
		return 0;
}

PlayerPawn::PawnData::PawnData(const uintptr_t& controller, const uintptr_t& pawn) {
	using namespace offsets;

	if (name.string[0] == '\0')
		name = CUtlString(controller);

	health = get_data<int>(pawn, CCSPlayerPawn::m_iHealth);
	armor = get_data<int>(pawn, CCSPlayerPawn::m_ArmorValue);
	team_num = get_data<int>(pawn, CCSPlayerPawn::m_iTeamNum);

	origin = get_data<vector_3d>(pawn, CCSPlayerPawn::m_vOldOrigin);

	is_scoped = get_data<bool>(pawn, CCSPlayerPawn::m_bIsScoped);
	is_defusing = get_data<bool>(pawn, CCSPlayerPawn::m_bIsDefusing);
}

PlayerPawn::PlayerPawn(size_t idx) {
	controller = CGameEntitySystem::GetEntityByIndex(idx);
	if (!controller) {
		empty = true;
		return;
	}

	pawn = GetPawnByController(controller);
	if (!pawn) {
		empty = true;
		return;
	}

	empty = false;
	data = PawnData(controller, pawn);
}

uintptr_t PlayerPawn::get_address() const {
	return pawn;
}

bool PlayerPawn::is_empty() const {
	return empty;
}

bool PlayerPawn::is_local_player() const {
	uintptr_t local_controller = *reinterpret_cast<uintptr_t*>(local_controller_handle + *((int32_t*)(local_controller_handle + 3)) + 7);
	return (local_controller == controller) ? true : false;
}